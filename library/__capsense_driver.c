/*
    __capsense_driver.c

-----------------------------------------------------------------------------

  This file is part of mikroSDK.

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

#include "__capsense_driver.h"
#include "__capsense_hal.c"

/* ------------------------------------------------------------------- MACROS */



/* ---------------------------------------------------------------- VARIABLES */

#ifdef   __CAPSENSE_DRV_I2C__
static uint8_t _slaveAddress;
#endif

//register
const uint8_t _CAPSENSE_COMMAND_REG                     = 0xA0;
const uint8_t _CAPSENSE_CS_ENABL0                       = 0x06;
const uint8_t _CAPSENSE_CS_ENABL1                       = 0x07;
const uint8_t _CAPSENSE_GPIO_ENABLE0                    = 0x08;
const uint8_t _CAPSENSE_DM_STRONG0                      = 0x11;
const uint8_t _CAPSENSE_CS_SLID_CONFIG                  = 0x75;
const uint8_t _CAPSENSE_CS_SLID_MULM                    = 0x77;
const uint8_t _CAPSENSE_CS_SLID_MULL                    = 0x78;
const uint8_t _CAPSENSE_OUTPUT_PORT0                    = 0x04;
const uint8_t _CAPSENSE_CS_READ_RAW                     = 0x87;
const uint8_t _CAPSENSE_CS_READ_STATUS0                 = 0x88;
const uint8_t _CAPSENSE_CS_READ_STATUS1                 = 0x89;
const uint8_t _CAPSENSE_CS_READ_CEN_POSM                = 0x8A;
const uint8_t _CAPSENSE_CS_READ_CEN_POSL                = 0x8B;
const uint8_t _CAPSENSE_CS_READ_CEN_PEAKM               = 0x8C;
const uint8_t _CAPSENSE_CS_READ_CEN_PEAKL               = 0x8D;
const uint8_t _CAPSENSE_DEVICE_ID                       = 0x7A;
const uint8_t _CAPSENSE_DEVICE_STATUS                   = 0x7B;

const uint8_t _CAPSENSE_I2C_ADDRESS_0         = 0x00;
const uint8_t _CAPSENSE_I2C_ADDRESS_1         = 0x4B;



/* -------------------------------------------- PRIVATE FUNCTION DECLARATIONS */



/* --------------------------------------------- PRIVATE FUNCTION DEFINITIONS */



/* --------------------------------------------------------- PUBLIC FUNCTIONS */

#ifdef   __CAPSENSE_DRV_SPI__

void capsense_spiDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P spiObj)
{
    hal_spiMap( (T_HAL_P)spiObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __CAPSENSE_DRV_I2C__

void capsense_i2cDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P i2cObj, uint8_t slave)
{
    _slaveAddress = slave;
    hal_i2cMap( (T_HAL_P)i2cObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif
#ifdef   __CAPSENSE_DRV_UART__

void capsense_uartDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P uartObj)
{
    hal_uartMap( (T_HAL_P)uartObj );
    hal_gpioMap( (T_HAL_P)gpioObj );

    // ... power ON
    // ... configure CHIP
}

#endif


/* ----------------------------------------------------------- IMPLEMENTATION */



/* Generic write data function - 8-bit data */
void capsense_writeData(uint8_t address, uint8_t writeCommand)
{
    uint8_t buffer[2];
    buffer[0]= address;
    buffer[1]= writeCommand;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, buffer, 2, END_MODE_STOP );
}

/* Generic read data function - 8-bit data */
uint8_t capsense_readData( uint8_t address )
{
    uint8_t tempData;
    tempData = address;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, &tempData, 1, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &tempData, 1, END_MODE_STOP );

    return tempData;
}

/* Generic read data function - 16-bit data */
uint16_t capsense_readDataBytes( uint8_t address )
{
    uint8_t tempData[2];
    uint16_t result;
    tempData[0] = address;
    tempData[1] = address;

    hal_i2cStart();
    hal_i2cWrite( _slaveAddress, &tempData, 2, END_MODE_RESTART );
    hal_i2cRead( _slaveAddress, &tempData, 2, END_MODE_STOP );
    
    result = tempData[0];
    result <<= 8;
    result |= tempData[1];

    return result;
}

/* Function get slider level */
uint16_t capsense_getSliderLvl()
{
    uint16_t sliderLvl;
    uint8_t sliderSum;
    sliderLvl = 0;

    sliderSum = capsense_readDataBytes( _CAPSENSE_CS_READ_RAW );
    
    switch ( sliderSum )
      {
          case 1 :  sliderLvl = 1;
          break;
          case 2 :  sliderLvl = 2;
          break;
          case 3 :  sliderLvl = 12;
          break;
          case 4 :  sliderLvl = 3;
          break;
          case 6 :  sliderLvl = 23;
          break;
          case 7 :  sliderLvl = 123;
          break;
          case 8 :  sliderLvl = 4;
          break;
          case 12 : sliderLvl = 34;
          break;
          case 14 : sliderLvl = 234;
          break;
          case 15 : sliderLvl = 1234;
          break;
          case 16 : sliderLvl = 5;
          break;
          case 24 : sliderLvl = 45;
          break;
          case 28 : sliderLvl = 345;
          break;
          case 30 : sliderLvl = 2345;
          break;
          case 31 : sliderLvl = 12345;
          break;
          default : sliderLvl = 0;
          break;
      }

    return sliderLvl;
}

/* Initialisation register function */
void capsense_init()
{
    capsense_writeData( _CAPSENSE_COMMAND_REG, 0x08 );      // Enable pins on B0,B1 and slider as CapSense
    capsense_writeData( _CAPSENSE_CS_ENABL1, 0x1F );     // Five pins will be used for Slider pads
    capsense_writeData( _CAPSENSE_CS_ENABL0, 0x18 );     // Two pins will be used for Button pads
    capsense_writeData( _CAPSENSE_GPIO_ENABLE0, 0x03 );     // Three pins will be used as GPIO 2 for LED and 1 as GPIO2
    capsense_writeData( _CAPSENSE_DM_STRONG0, 0x03 );     // Enables strong drive mode for GPIOs

    capsense_writeData( _CAPSENSE_CS_SLID_CONFIG, 0x01 );  // Enable slider
    capsense_writeData( _CAPSENSE_CS_SLID_MULM, 0x10 );   // Configure slider resolution
    capsense_writeData( _CAPSENSE_CS_SLID_MULL, 0x00 );   // Configure slider resolution

    capsense_writeData( _CAPSENSE_COMMAND_REG, 0x01 );     // Store Current Configuration to NVM
    Delay_100ms();
    Delay_100ms();
    capsense_writeData( _CAPSENSE_COMMAND_REG, 0x06 );     // Reconfigure Device (POR)
    Delay_100ms();
    Delay_100ms();
    Delay_100ms();
    capsense_writeData( _CAPSENSE_OUTPUT_PORT0, 0x03 );
    Delay_100ms();
}







/* -------------------------------------------------------------------------- */
/*
  __capsense_driver.c

  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright
   notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

3. All advertising materials mentioning features or use of this software
   must display the following acknowledgement:
   This product includes software developed by the MikroElektonika.

4. Neither the name of the MikroElektonika nor the
   names of its contributors may be used to endorse or promote products
   derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY MIKROELEKTRONIKA ''AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL MIKROELEKTRONIKA BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

----------------------------------------------------------------------------- */