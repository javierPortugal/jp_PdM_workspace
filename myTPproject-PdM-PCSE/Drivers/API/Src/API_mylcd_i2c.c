

#include "API_mylcd_i2c.h"

#define ONE_MILISECONDS 	1
#define FIVE_MILISECONDS 	5
#define TEN_MILISECONDS 	10
#define FIFTHY_MILISECONDS 	50



void mylcd_send_command  (char command)
{
/*parto el comando de 8 bits en 2 de 4 bits
 * y las siguiente condicion es para que el LCD procese el dato
 * en=1, rs=0
 * en=0, rs=0
 *
 * */
	uint16_t size = 4;
	int32_t timeout =100;

    char  data_lower, data_upper;
	uint8_t data_t[4];
	data_upper = (command&0xf0);
	data_lower = ((command<<4)&0xf0);
	data_t[0] = data_upper|0x0C;
	data_t[1] = data_upper|0x08;
	data_t[2] = data_lower|0x0C;
	data_t[3] = data_lower|0x08;

	LCD_IO_Transmit((uint8_t *) data_t, size);
}

void mylcd_send_data (char data)
{
/*
 * para enviar caracteres, igual lo parto en dos
 * y LCD necesita que el modo de datos RS =1
 * y asi el lcd identifica que es un dato a imprimir
 *
 * */
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

	LCD_IO_Transmit((uint8_t *) data_t, size);
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
	// 4 bit LCD initialization
	// wait for >40ms
	// wait for >4.1ms
	// wait for >100us
	// 4bit mode
	//Display on/off control --> D = 1, C and B = 0. (Cursor and blink, last two bits)
	// display initialization
	// Function set --> DL=0 (4 bit mode), N = 1 (2 line display) F = 0 (5x8 characters)
	//Display on/off control --> D=0,C=0, B=0  ---> display off
	// clear display
	//Entry mode set --> I/D = 1 (increment cursor) & S = 0 (no shift)

	HAL_Delay(FIFTHY_MILISECONDS);
	mylcd_send_command (0x30);
	HAL_Delay(FIVE_MILISECONDS);
	mylcd_send_command  (0x30);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x30);
	HAL_Delay(TEN_MILISECONDS);
	mylcd_send_command  (0x20);
	HAL_Delay(TEN_MILISECONDS);


	mylcd_send_command  (0x28);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x08);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x01);
	HAL_Delay(ONE_MILISECONDS);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command (0x06);
	HAL_Delay(ONE_MILISECONDS);
	mylcd_send_command  (0x0C);
}

void mylcd_send_string (char *str)
{
	while (*str) mylcd_send_data (*str++);
}

void mylcd_put_cursor(uint8_t line) {
    mylcd_send_command(line);
}
