/*
 * API_myTC74.h
 *
 *  Created on: 27 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_MYTC74_H_
#define API_INC_API_MYTC74_H_

// Importante que incluyamos el port
//para tener el puente con el hardware
#include "API_myTC74port.h"

#define TC74_ADDRESS (0x48 << 1)
#define REG_TEMP     0x00


int8_t get_temperature(void);



#endif /* API_INC_API_MYTC74_H_ */
