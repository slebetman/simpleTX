#include "model-const.h"

extern struct model current_model;
extern void getModelName (unsigned char model_id, unsigned char *name);
extern void loadModel (unsigned char model_id);
extern void saveModel ();
extern unsigned char mixIsDisabled(unsigned char i);
extern void newModel ();
extern void saveModelName(unsigned char model_id);
extern void saveTrim(unsigned char model_id);
extern void saveModelScale(unsigned char model_id);
extern void saveModelOutputMap(unsigned char model_id);
extern void saveModelMixes(unsigned char model_id);
