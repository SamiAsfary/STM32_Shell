/*
 * shell.c
 *
 *  Created on: 3 mai 2023
 *      Author: sasfa
 */

#include "shell.h"
#include "usart.h"
#include "stm32f7xx_hal_uart.h"
#include <string.h>

static const char sh_backspace[] = "\b \b";
static const char sh_new_line[] = "> ";

char sh_welcome_text[] = "***********************\r\n*                     *\r\n*     shell v0.1      *\r\n*     Sami Asfary     *\r\n*                     *\r\n***********************\r\n";

char sh_cmd_history[SH_HISTORY_LEN][SH_COMMAND_LEN];
uint8_t sh_cmd_ptr = 0, sh_cmd_cnt = 0, sh_line_ptr = 0;

void sh_run(){
	HAL_UART_Transmit(&huart1, sh_welcome_text, strlen(sh_welcome_text), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart1, sh_new_line, 2, HAL_MAX_DELAY);

	char character[1];
	while(1){
		HAL_UART_Receive(&huart1, character, 1, HAL_MAX_DELAY);
		switch(character[0]){
		case '\r' :
			HAL_UART_Transmit(&huart1, "\r\n", 2, HAL_MAX_DELAY);

			HAL_UART_Transmit(&huart1, sh_new_line, 2, HAL_MAX_DELAY);
			sh_line_ptr = 0;
			break;
		case '\177':
			if(sh_line_ptr != 0){
				HAL_UART_Transmit(&huart1, sh_backspace, 3, HAL_MAX_DELAY);
				sh_line_ptr--;
			}
			break;
		default :
			HAL_UART_Transmit(&huart1, character, 1, HAL_MAX_DELAY);
			sh_line_ptr++;
			break;
		}

	}

}



