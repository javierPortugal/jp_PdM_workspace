

#include "API_mylcd_i2c.h"
extern I2C_HandleTypeDef hi2c1;  //

#define MYLCD_ADDRESS 		0x4E // LCD I2C extender address
#define ONE_MILISECONDS 	1
#define FIVE_MILISECONDS 	5
#define TEN_MILISECONDS 	10
#define FIFTHY_MILISECONDS 	50


void mylcd_send_command  (char command)
{
	uint16_t size = 4;
	int32_t timeout =100;

    char  data_lower, data_upper;
	uint8_t data_t[4];
	data_upper = (command&0xf0);
	data_lower = ((command<<4)&0xf0);
	data_t[0] = data_upper|0x0C;  //en=1, rs=0
	data_t[1] = data_upper|0x08;  //en=0, rs=0
	data_t[2] = data_lower|0x0C;  //en=1, rs=0
	data_t[3] = data_lower|0x08;  //en=0, rs=0
	HAL_I2C_Master_Transmit (&hi2c1, MYLCD_ADDRESS,(uint8_t *) data_t, size, timeout);
}

void mylcd_send_data (char data)
{
	uint16_t size = 4;
	uint32_t timeout =100;

	char data_lower, data_upper;
	uint8_t data_t[4];
	data_upper = (data&0xf0);
	data_lower = ((data<<4)&0xf0);
	data_t[0] = data_upper|0x0D;  //en=1, rs=1
	data_t[1] = data_upper|0x09;  //en=0, rs=1
	data_t[2] = data_lower|0x0D;  //en=1, rs=1
	data_t[3] = data_lower|0x09;  //en=0, rs=1
	HAL_I2C_Master_Transmit (&hi2c1, MYLCD_ADDRESS,(uint8_t *) data_t, size, timeout);
}

void mylcd_clear (void)
{
	mylcd_send_command (0x00);
	for (int i=0; i<100; i++)
	{
		mylcd_send_data (' ');
	}
}

void mylcd_init (void)
{
	// 4 bit initialisation
	HAL_Delay(FIFTHY_MILISECONDS);  // wait for >40ms
	mylcd_send_command (0x30);
	HAL_Delay(FIVE_MILISECONDS);  // wait for >4.1ms
	mylcd_send_command  (0x30);
	HAL_Delay(ONE_MILISECONDS);  // wait for >100us
	mylcd_send_command  (0x30);
	HAL_Delay(TEN_MILISECONDS);
	mylcd_send_command  (0x20);  // 4bit mode
	HAL_Delay(TEN_MILISECONDS);

  // display initialisation
	mylcd_send_command  (0x28); // Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x08); //Display on/off control --> D=0,C=0, B=0  ---> display off
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x01);  // clear display
	HAL_Delay(ONE_MILISECONDS);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command (0x06); //Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x0C); //Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
}

void mylcd_send_string (char *str)
{
	while (*str) mylcd_send_data (*str++);
}
