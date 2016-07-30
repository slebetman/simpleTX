# PIC-TXmod
PPM to PPM encoder for adding features to cheap RC transmitters

## Development Environment

This project assumes the following set-up:

- [Microchip XC8](http://www.microchip.com/mplab/compilers) compiler
- [usbpicprog](http://usbpicprog.org/) programmer
- [Tcl](http://tcl.tk/software/tcltk/) scripting language (for script to extract trim data from hexfile)
- GNU make

## Build, Install etc.

Read the Makefile. The available commands are fairly obvious. The following are the most commonly used commands:

    make          ;# builds project 
    make tidy     ;# deletes temporary build files
    make clean    ;# deletes all generated files
    make install  ;# upload/burn program to CPU
    make backup   ;# download program from CPU (including trim settings)

## Writing a program for your RC plane

You can actually use this to control cars and boats as well but the terminology assumes an aircraft.

To configure your airplane all you need to do is edit `main.c`. Just edit the contents of the main `while` loop.
The default setup is for a standard 4 channel setup. Basically it just copies the inputs from the joysticks to
individual output channels:

    output_pulse[CHANNEL1] = AILERON;
    output_pulse[CHANNEL2] = ELEVATOR;
    output_pulse[CHANNEL3] = THROTTLE;
    output_pulse[CHANNEL4] = RUDDER;
    
Functions such as mixing and expo are defined in `calculations.h`. For example, a simple elevon mix would be
something like the following:

    mix(AILERON,ELEVATOR,output_pulse[CHANNEL1],output_pulse[CHANNEL2]);
    output_pulse[CHANNEL3] = THROTTLE;

Say for example you find your aileron controls too sensitive. You can scale it back using the `scale` function:

    output_pulse[CHANNEL1] = scale(AILERON,60); // reduce aileron input to 60%
    output_pulse[CHANNEL2] = ELEVATOR;
    output_pulse[CHANNEL3] = THROTTLE;
    output_pulse[CHANNEL4] = RUDDER;

Or you need to add some expo to your elevator controls for your flying wing:

    // 20% expo for elevator input to elevons:
    mix(AILERON,expo(ELEVATOR,20),output_pulse[CHANNEL1],output_pulse[CHANNEL2]);
    output_pulse[CHANNEL3] = THROTTLE;

The program you write will basically look like a config file. All the low level details are abstracted away
and execute in the background in interrupt service routines.
