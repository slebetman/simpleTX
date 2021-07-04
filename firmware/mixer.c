#include "common.h"
#include "analog.h"
#include "joystick.h"
#include "channels.h"
#include "model.h"
#include "calculations.h"

#define MIX_STATE_IDLE  0
#define MIX_STATE_START 1
#define MIX_STATE_MIX1  2
#define MIX_STATE_MIX2  3
#define MIX_STATE_AVG1  4
#define MIX_STATE_AVG2  5

unsigned char mixer_state;
unsigned char channel_mix_count[USER_CHANNELS];

unsigned char mixTracker;
short mixCount;
struct mix thisMix;
short update_count;

void initMixer () {
	mixTracker = tick;
	mixCount = 0;
	update_count = 0;
	unsigned char mixer_state = MIX_STATE_IDLE;
}

unsigned char startMixer () {
	short tmp;
	unsigned char i;

	if (mixTracker != tick) {
		mixCount += (tick-mixTracker) & 0xff;
		mixTracker = tick;

		if (mixCount >= 20) {
			mixCount = 0;

			mixer_state = MIX_STATE_START;
			update_count ++;

			for (i=0; i<TOTAL_ANALOG_CHANNELS; i++) {
				tmp = read_stick(i) + current_model.trim[i];
				tmp = scale(tmp, current_model.scale[i]);
				ANALOG_CHANNEL(i) = tmp;
			}

			for (i=0; i<USER_CHANNELS; i++) {
				channel_mix_count[i] = 0;
				channels[i] = 0;
			}

			return 1;
		}
	}
	return 0;
}

unsigned char processMixer () {
	short tmp;
	unsigned char i;

	switch (mixer_state) {
		case MIX_STATE_IDLE: return 0;

		case MIX_STATE_START:
			mixer_state = MIX_STATE_MIX1;

			for (i=0; i<(MAX_MIXES/2); i++) {
				if (mixIsDisabled(i)) continue;

				thisMix.expo = current_model.mix[i].expo;
				thisMix.input = current_model.mix[i].input;
				thisMix.output = current_model.mix[i].output;
				thisMix.reverse = current_model.mix[i].reverse;
				thisMix.scale = current_model.mix[i].scale;

				tmp = channels[thisMix.input];

				if (thisMix.reverse) tmp = -tmp;

				tmp = scale(tmp, thisMix.scale);

				if (thisMix.expo > 0) {
					tmp = expo(tmp, thisMix.expo);
				}

				channels[thisMix.output] += tmp;
				channel_mix_count[thisMix.output] ++;
			}
			break;
		case MIX_STATE_MIX1:
			mixer_state = MIX_STATE_MIX2;
			
			for (i=(MAX_MIXES/2); i<MAX_MIXES; i++) {
				if (mixIsDisabled(i)) continue;

				thisMix.expo = current_model.mix[i].expo;
				thisMix.input = current_model.mix[i].input;
				thisMix.output = current_model.mix[i].output;
				thisMix.reverse = current_model.mix[i].reverse;
				thisMix.scale = current_model.mix[i].scale;

				tmp = channels[thisMix.input];

				if (thisMix.reverse) tmp = -tmp;

				tmp = scale(tmp, thisMix.scale);

				if (thisMix.expo > 0) {
					tmp = expo(tmp, thisMix.expo);
				}

				channels[thisMix.output] += tmp;
				channel_mix_count[thisMix.output] ++;
			}
			break;
		case MIX_STATE_MIX2:
			mixer_state = MIX_STATE_AVG1;

			for (i=0; i<(USER_CHANNELS/2); i++) {
				if (channel_mix_count[i] > 0) {
					channels[i] = channels[i] / channel_mix_count[i];
				}
			}
			break;
		case MIX_STATE_AVG1:
			mixer_state = MIX_STATE_IDLE;

			for (i=(USER_CHANNELS/2); i<USER_CHANNELS; i++) {
				if (channel_mix_count[i] > 0) {
					channels[i] = channels[i] / channel_mix_count[i];
				}
			}
			break;
		default:
			mixer_state = MIX_STATE_IDLE;
	}

	return 1;
}