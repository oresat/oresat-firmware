#ifndef _DEPLOYER_H_
#define _DEPLOYER_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void deploy_heli(uint32_t duration);
void deploy_turn(uint32_t duration);

#ifdef __cplusplus
}
#endif /*__cplusplus*/
#endif
