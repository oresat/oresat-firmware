#ifndef _TEST_RADIO_H_
#define _TEST_RADIO_H_

#include "ax5043.h"
#include "si41xx.h"

typedef struct {
    SI41XXDriver *devp;
    SI41XXConfig *cfgp;
    const char *name;
} synth_dev_t;

typedef struct {
    AX5043Driver *devp;
    const AX5043Config *cfgp;
    const char *name;
} radio_dev_t;

typedef struct {
    const ax5043_profile_t *profile;
    const char *name;
} radio_profile_t;

extern synth_dev_t synth_devices[];
extern radio_dev_t radio_devices[];
extern radio_profile_t radio_profiles[];

#ifdef __cplusplus
extern "C" {
#endif

void cmd_radio(BaseSequentialStream *chp, int argc, char *argv[]);
void cmd_synth(BaseSequentialStream *chp, int argc, char *argv[]);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
