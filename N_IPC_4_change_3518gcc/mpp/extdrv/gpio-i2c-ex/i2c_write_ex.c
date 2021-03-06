/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : i2c_write.c
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2010/08/20
  Description   : GPIO-I2C for 8bit register and 16bit Data Transfer, eg. MT9P031
  History       :
  1.Date        : 2010/04/09
    Author      : 
    Modification: Created file

******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "strfunc.h"
#include "gpioi2c_ex.h"

unsigned int reg_width = 1;
unsigned int data_width = 1;

int main(int argc , char* argv[])
{
	int fd = -1;
	int ret =0;
    unsigned int device_addr, reg_addr, reg_value;
	I2C_DATA_S i2c_data ;	
	if(argc < 4)
    {
    	printf("usage: %s <device_addr> <reg_addr> <value> <reg_width> <data_width>. sample:\n", argv[0]);
        printf("----------------------------------------------------------------------------\n");
        printf("\t\t%s 0x56 0x0 0x28 2 2. \n", argv[0]);
        printf("\t\t%s 0x56 0x0 0x28. default reg_width and data_width is 1. \n", argv[0]);
        return -1;
    }
	
	fd = open("/dev/gpioi2c_ex", 0);
    if(fd<0)
    {
    	printf("Open gpioi2c_ex error!\n");
    	return -1;
    }
    
    if (StrToNumber(argv[1], &device_addr))
    {    	
    	return 0;
    }
    
    
    if (StrToNumber(argv[2], &reg_addr))
    {    
    	return 0;
    }
    
    if (StrToNumber(argv[3], &reg_value))
    {    
    	return 0;
    }

    if(argc > 4) 
    { 
        if(StrToNumber(argv[4], &reg_width))
            return 0;

        if((argc > 5) && StrToNumber(argv[5], &data_width))
            return 0;     
    }
    
    printf("dev_addr:0x%2x; reg_addr:0x%2x; reg_value:0x%2x; reg_width: %d; data_width: %d.\n", 
        device_addr, reg_addr, reg_value, reg_width, data_width);
    i2c_data.dev_addr = device_addr ; 
    i2c_data.reg_addr = reg_addr    ; 
    i2c_data.addr_byte_num = reg_width  ; 
    i2c_data.data     = reg_value         ; 
    i2c_data.data_byte_num = data_width ;
    
    ret = ioctl(fd, GPIO_I2C_WRITE, &i2c_data);

	close(fd);
        
    return 0;
}

