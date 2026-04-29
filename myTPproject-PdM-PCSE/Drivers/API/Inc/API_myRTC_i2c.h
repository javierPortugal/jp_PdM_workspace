/*
 * API_myRTC_i2c.h
 *
 *  Created on: 22 abr 2026
 *      Author: javie
 */

#ifndef INC_API_MYRTC_I2C_H_
#define INC_API_MYRTC_I2C_H_

#include "stm32f4xx_hal.h"
#define RTC_ADDRESS 0xD0

typedef struct {
	uint8_t seconds;
	uint8_t minutes;
	uint8_t hour;
	uint8_t dayofweek;
	uint8_t dayofmonth;
	uint8_t month;
	uint8_t year;
} RTC_TIME;

extern RTC_TIME rtc_time;
extern char data_buffer[21];


//los datos en RTC se encuentran en BCD
// Convertir decimal a BCD
uint8_t conversionBcd(int val);
// Convertir BCD a decimal
int conversionDec(uint8_t val);




//funciones para grabar datos en y leer datos del RTC
//la funcion set solo se utiliza una vez si el modulo cuenta con una bateria que ayuda a resguardar la informacion
void set_time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year);
void get_time (void);



#endif /* INC_API_MYRTC_I2C_H_ */
