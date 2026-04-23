/*
 * API_myRTC_i2c.c
 *
 *  Created on: 22 abr 2026
 *      Author: javie
 */

//#define RTC_ADDRESS 0xD0
#include "API_myRTC_i2c.h"

extern I2C_HandleTypeDef hi2c1;


RTC_TIME rtc_time;
char data_buffer[21];

// Convert normal decimal numbers to binary coded decimal
uint8_t conversionBcd(int val)
{
  return (uint8_t)( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
int conversionDec(uint8_t val)
{
  return (int)( (val/16*10) + (val%16) );
}



// function to set time

void Set_Time (uint8_t sec, uint8_t min, uint8_t hour, uint8_t dow, uint8_t dom, uint8_t month, uint8_t year)
{
	uint8_t set_time[7];
	set_time[0] = conversionBcd(sec);
	set_time[1] = conversionBcd(min);
	set_time[2] = conversionBcd(hour);
	set_time[3] = conversionBcd(dow);
	set_time[4] = conversionBcd(dom);
	set_time[5] = conversionBcd(month);
	set_time[6] = conversionBcd(year);

	HAL_I2C_Mem_Write(&hi2c1, RTC_ADDRESS, 0x00, 1, set_time, 7, 1000);
}

void Get_Time (void)
{
	uint8_t get_time[7];
	HAL_I2C_Mem_Read(&hi2c1, RTC_ADDRESS, 0x00, 1, get_time, 7, 1000);
	rtc_time.seconds = conversionDec(get_time[0]);
	rtc_time.minutes = conversionDec(get_time[1]);
	rtc_time.hour = conversionDec(get_time[2]);
	rtc_time.dayofweek = conversionDec(get_time[3]);
	rtc_time.dayofmonth =conversionDec(get_time[4]);
	rtc_time.month = conversionDec(get_time[5]);
	rtc_time.year = conversionDec(get_time[6]);
}







