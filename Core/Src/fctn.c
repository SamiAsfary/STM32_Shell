/**
  * @file           : fctn.c
  * @brief          : collection of function working with the shell
  */

#include "fctn.h"
#include <stdio.h>

extern UART_HandleTypeDef huart1;


void shfctn_valuereturn(uint8_t argc, argv_t argv){
	uint8_t size,i;
	char buffer[30];
	for(i = 0; argv[1][i] != '\0'; i++){
		size = sprintf(buffer,"the hexa value of %c is 0x%X\r\n",argv[1][i],argv[1][i]);
		sh_write((char *)buffer, size);
		//HAL_UART_Transmit(&huart1, buffer, size, HAL_MAX_DELAY);
	}

}
