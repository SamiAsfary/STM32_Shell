/**
  * @file           : fctn.c
  * @brief          : collection of function working with the shell
  */

#include "fctn.h"
#include <stdio.h>




void shfctn_valuereturn(uint8_t argc, argv_t argv){
	uint8_t size,i;
	char * buffer;
	for(i = 0; argv[1][i] != '\0'; i++){
		size = sprintf(buffer,"the hexa value of %c is 0x%X\r\n",argv[1][i],argv[1][i]);
		sh_write((char *)buffer, size);
	}

}
