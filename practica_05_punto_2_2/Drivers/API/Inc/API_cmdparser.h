/*
 * API_cmdparser.h
 *
 *  Created on: 8 abr 2026
 *      Author: javie
 */

#ifndef API_INC_API_CMDPARSER_H_
#define API_INC_API_CMDPARSER_H_


/* Definiciones de constantes para el parser de comandos */
#define CMD_MAX_LINE 64
#define CMD_MAX_TOKENS 3

/** Tipos de estado para la Maquina del parser de comandos */
typedef enum {
	CMD_OK = 0,
	CMD_ERR_OVERFLOW,
	CMD_ERR_SYNTAX,
	CMD_ERR_UNKNOWN,
	CMD_ERR_ARG,
} cmd_status_t;

/**
 *Inicializa el módulo parser de comandos
 */
void cmdParserInit(void);

/**
 * Máquina de estados del Paser. Debe ser llamada periódicamente desde el bucle
 * 		  Procesa hasta 16 bytes por invocación (no bloqueante).
 */
void cmdPoll(void);

/**
 * Imprime por UART la lista de comandos disponibles
 */
void cmdPrintHelp(void);







#endif /* API_INC_API_CMDPARSER_H_ */
