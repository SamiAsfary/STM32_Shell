/*
 * shell.c
 *
 *  Created on: 3 mai 2023
 *      Author: sasfa
 */

#include "shell.h"

#include <string.h>

static const char sh_backspace[] = "\b \b";
static const char sh_new_line[] = "> ";
char sh_welcome_text[] = "\r\n***********************\r\n*                     *\r\n*     shell v0.2      *\r\n*     Sami Asfary     *\r\n*                     *\r\n***********************\r\n";

static h_shell_t h_shell;

void sh_init(UART_HandleTypeDef *huart){
	h_shell.function_count = 0;
	h_shell.hal_huart = huart;
}

void sh_run(){
	HAL_UART_Transmit(h_shell.hal_huart, sh_welcome_text, strlen(sh_welcome_text), HAL_MAX_DELAY);
	HAL_UART_Transmit(h_shell.hal_huart, sh_new_line, 2, HAL_MAX_DELAY);

	char character[1];
	while(1){
		HAL_UART_Receive(h_shell.hal_huart, character, 1, HAL_MAX_DELAY);
		switch(character[0]){
		case '\r' :
			HAL_UART_Transmit(h_shell.hal_huart, "\r\n", 2, HAL_MAX_DELAY);
			h_shell.sh_cmd_current[h_shell.sh_line_ptr] = '\0';
			if(h_shell.sh_line_ptr != 0){
				sh_command_resolve();
			}
			HAL_UART_Transmit(h_shell.hal_huart, sh_new_line, 2, HAL_MAX_DELAY);
			h_shell.sh_line_ptr = 0;
			break;
		case '\b':
		case '\177':
			if(h_shell.sh_line_ptr != 0){
				HAL_UART_Transmit(h_shell.hal_huart, sh_backspace, 3, HAL_MAX_DELAY);
				h_shell.sh_line_ptr--;
				h_shell.sh_cmd_current[h_shell.sh_line_ptr] = '\0';
			}
			break;
		default :
			HAL_UART_Transmit(h_shell.hal_huart, character, 1, HAL_MAX_DELAY);
			h_shell.sh_cmd_current[h_shell.sh_line_ptr] = character[0];
			h_shell.sh_line_ptr++;
			break;
		}

	}

}

void sh_command_resolve(){
	char i = 1, last_space=0, argc = 0;
	char argv[SH_ARGC_MAX][SH_COMMAND_LEN];
	while(h_shell.sh_cmd_current[i-1] != '\0'){
		if(h_shell.sh_cmd_current[i] == ' ' || h_shell.sh_cmd_current[i] == '\0'){
		for(char j = last_space; j < i; j++){
				argv[argc][j-last_space] = h_shell.sh_cmd_current[j];
			}
			argv[argc][i-last_space] = '\0';
			last_space = i+1;
			argc++;
		}
		i++;
	}


}



