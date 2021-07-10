#include "../drivers/button.h"
#include "gui-const.h"

extern button *button1;
extern button *button2;
extern button *button3;

extern signed char modelID;
extern signed char selection;

extern void initGUI ();
extern unsigned char updateGUI ();
extern void handleSelection (unsigned char totalOptions);
extern void updateSelection (unsigned char totalOptions);
extern void loadHomePage ();
