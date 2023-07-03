/*
 * 		shell.h
 *
 *  	Created on: 3 mai 2023
 *      Author: sasfa
 */

#ifndef INC_SHELL_H_
#define INC_SHELL_H_

#include "usart.h"
#include "stm32f7xx_hal_uart.h"

#define SH_HISTORY_LEN 10
#define SH_COMMAND_LEN 50
#define SH_ARGC_MAX 6
#define SH_ARGV_LEN 10
#define SH_MAX_FUNCTION 25

typedef char argv_t[SH_ARGC_MAX][SH_ARGV_LEN];

typedef uint8_t (* drv_shell_transit_t)(char * pData, uint16_t size);
typedef uint8_t (* drv_shell_receive_t)(char * pData, uint16_t size);

typedef struct{
	drv_shell_receive_t drv_shell_receive;
	drv_shell_transit_t drv_shell_transit;
}drv_shell_t;

typedef struct{
	char *string_cmd;
	void (*pcmd_function)(uint8_t argc, argv_t argv);
	char *cmd_description;
}h_cmd_t;

typedef struct{
	h_cmd_t function_list[SH_MAX_FUNCTION];
	uint8_t function_count;
	UART_HandleTypeDef *hal_huart;
	char sh_cmd_current[SH_COMMAND_LEN];
	char sh_cmd_history[SH_HISTORY_LEN][SH_COMMAND_LEN];
	uint8_t sh_cmd_ptr;
	uint8_t sh_cmd_cnt;
	uint8_t sh_line_ptr;
}h_shell_t;

void sh_write(const char * str, char lenght);
void shfctn_help(uint8_t argc, argv_t argv);
void sh_add();
void sh_init();
void sh_run();
void sh_command_resolve();

#endif /* INC_SHELL_H_ */
