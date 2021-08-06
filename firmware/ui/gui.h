#include "../drivers/button.h"
#include "gui-const.h"

extern signed char tmp;

extern button *button1;
extern button *button2;
extern button *button3;
extern button *button4;

extern signed char modelID;

extern void initGUI ();
extern unsigned char updateGUI ();
signed char handleSelection (unsigned char totalOptions, signed char selection);
extern void drawSelection (unsigned char totalOptions, signed char selection);
extern void loadHomePage ();
