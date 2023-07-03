/*
 * shell.c
 *
 *  Created on: 3 mai 2023
 *      Author: sasfa
 */

#include "shell.h"
#include "fctn.h"
#include <string.h>
static const char sh_returnline[] = "\r\n";
static const char sh_backspace[] = "\b \b";
static const char sh_new_line[] = "> ";
char sh_welcome_text[] = "\r\n***********************\r\n*                     *\r\n*     shell v1.0      *\r\n*     Sami Asfary     *\r\n*                     *\r\n***********************\r\n";

static h_shell_t h_shell;
drv_shell_t drv_shell_struct;

void sh_write(const char * str, char lenght){
	HAL_UART_Transmit(h_shell.hal_huart, (uint8_t*) str, lenght, HAL_MAX_DELAY);
}

void shfctn_help(uint8_t argc, argv_t argv){
	if(argc <= 1){
		sh_write("Usage of the help command is as follow : \"help [command]\"\r\nAvailable function :\r\n", strlen("Usage of the help command is as follow : \"help [command]\"\r\nAvailable function :\r\n"));
		for(int i = 0; i < h_shell.function_count;i++){
			sh_write(h_shell.function_list[i].string_cmd, strlen(h_shell.function_list[i].string_cmd));
			sh_write(sh_returnline,2);
		}
	}else{
		for(int i = 0; i < h_shell.function_count;i++){
			if(strcmp(h_shell.function_list[i].string_cmd, argv[1]) == 0){
				sh_write(h_shell.function_list[i].cmd_description, strlen(h_shell.function_list[i].cmd_description));
				break;
			}
		}
	}
}

void sh_add(char * command, void(* pcommand)(uint8_t argc, argv_t argv), char * description){
	if(h_shell.function_count < SH_MAX_FUNCTION){
		h_shell.function_list[h_shell.function_count].string_cmd = command;
		h_shell.function_list[h_shell.function_count].pcmd_function = pcommand;
		h_shell.function_list[h_shell.function_count].cmd_description = description;
		h_shell.function_count++;
	}
}

void sh_init(UART_HandleTypeDef *huart){
	h_shell.function_count = 0;
	h_shell.hal_huart = huart;

	sh_add("help",shfctn_help,"Usage of the help command is as follow : \"help [command]\"\r\nThis command display a brief summary of command built into this shell\r\n\0");
}

void sh_run(){
	sh_write(sh_welcome_text, strlen(sh_welcome_text));
	sh_write(sh_new_line, 2);

	char character[1];
	while(1){
		HAL_UART_Receive(h_shell.hal_huart, (uint8_t *)character, 1,HAL_MAX_DELAY);
		switch(character[0]){
		case '\r' :
			sh_write("\r\n", 2);
			h_shell.sh_cmd_current[h_shell.sh_line_ptr] = '\0';
			if(h_shell.sh_line_ptr != 0){
				sh_command_resolve();
			}
			sh_write(sh_new_line, 2);
			h_shell.sh_line_ptr = 0;
			break;
		case '\b':
		case '\177':
			if(h_shell.sh_line_ptr != 0){
				sh_write(sh_backspace, 3);
				h_shell.sh_line_ptr--;
				h_shell.sh_cmd_current[h_shell.sh_line_ptr] = '\0';
			}
			break;
		default :
			sh_write(character, 1);
			h_shell.sh_cmd_current[h_shell.sh_line_ptr] = character[0];
			h_shell.sh_line_ptr++;
			break;
		}
	}
}

void sh_command_resolve(){
	uint8_t i = 1, last_space=0, argc = 0;
	argv_t argv;
	while(h_shell.sh_cmd_current[i-1] != '\0'){
		if(h_shell.sh_cmd_current[i] == ' ' || h_shell.sh_cmd_current[i] == '\0'){
		for(uint8_t j = last_space; j < i; j++){
				argv[argc][j-last_space] = h_shell.sh_cmd_current[j];
			}
			argv[argc][i-last_space] = '\0';
			last_space = i+1;
			argc++;
		}
		i++;
	}
	for(i = 0; i < h_shell.function_count; i++){
		if(strcmp(argv[0], h_shell.function_list[i].string_cmd) == 0){
			h_shell.function_list[i].pcmd_function(argc,argv);
		}
	}
}



