/*
    __capsense_driver.h

-----------------------------------------------------------------------------

  This file is part of mikroSDK.
  
  Copyright (c) 2017, MikroElektonika - http://www.mikroe.com

  All rights reserved.

----------------------------------------------------------------------------- */

/**
@file   __capsense_driver.h
@brief    CapSense Driver
@mainpage CapSense Click
@{

@image html libstock_fb_view.jpg

@}

@defgroup   CAPSENSE
@brief      CapSense Click Driver
@{

| Global Library Prefix | **CAPSENSE** |
|:---------------------:|:-----------------:|
| Version               | **1.0.0**    |
| Date                  | **Jul 2018.**      |
| Developer             | **Nenad Filipovic**     |

*/
/* -------------------------------------------------------------------------- */

#include "stdint.h"

#ifndef _CAPSENSE_H_
#define _CAPSENSE_H_

/** 
 * @macro T_CAPSENSE_P
 * @brief Driver Abstract type 
 */
#define T_CAPSENSE_P    const uint8_t*

/** @defgroup CAPSENSE_COMPILE Compilation Config */              /** @{ */

//  #define   __CAPSENSE_DRV_SPI__                            /**<     @macro __CAPSENSE_DRV_SPI__  @brief SPI driver selector */
   #define   __CAPSENSE_DRV_I2C__                            /**<     @macro __CAPSENSE_DRV_I2C__  @brief I2C driver selector */                                          
// #define   __CAPSENSE_DRV_UART__                           /**<     @macro __CAPSENSE_DRV_UART__ @brief UART driver selector */ 

                                                                       /** @} */
/** @defgroup CAPSENSE_VAR Variables */                           /** @{ */

extern const uint8_t _CAPSENSE_COMMAND_REG;
extern const uint8_t _CAPSENSE_CS_ENABL0;
extern const uint8_t _CAPSENSE_CS_ENABL1;
extern const uint8_t _CAPSENSE_GPIO_ENABLE0;
extern const uint8_t _CAPSENSE_DM_STRONG0;
extern const uint8_t _CAPSENSE_CS_SLID_CONFIG;
extern const uint8_t _CAPSENSE_CS_SLID_MULM;
extern const uint8_t _CAPSENSE_CS_SLID_MULL;
extern const uint8_t _CAPSENSE_OUTPUT_PORT0;
extern const uint8_t _CAPSENSE_CS_READ_RAW;
extern const uint8_t _CAPSENSE_CS_READ_STATUS0;
extern const uint8_t _CAPSENSE_CS_READ_STATUS1;
extern const uint8_t _CAPSENSE_CS_READ_CEN_POSM;
extern const uint8_t _CAPSENSE_CS_READ_CEN_POSL;
extern const uint8_t _CAPSENSE_CS_READ_CEN_PEAKM;
extern const uint8_t _CAPSENSE_CS_READ_CEN_PEAKL;
extern const uint8_t _CAPSENSE_DEVICE_ID;
extern const uint8_t _CAPSENSE_DEVICE_STATUS;

extern const uint8_t _CAPSENSE_I2C_ADDRESS_0;
extern const uint8_t _CAPSENSE_I2C_ADDRESS_1;

                                                                       /** @} */
/** @defgroup CAPSENSE_TYPES Types */                             /** @{ */



                                                                       /** @} */
#ifdef __cplusplus
extern "C"{
#endif

/** @defgroup CAPSENSE_INIT Driver Initialization */              /** @{ */

#ifdef   __CAPSENSE_DRV_SPI__
void capsense_spiDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P spiObj);
#endif
#ifdef   __CAPSENSE_DRV_I2C__
void capsense_i2cDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P i2cObj, uint8_t slave);
#endif
#ifdef   __CAPSENSE_DRV_UART__
void capsense_uartDriverInit(T_CAPSENSE_P gpioObj, T_CAPSENSE_P uartObj);
#endif


/** @defgroup CAPSENSE_FUNC Driver Functions */                   /** @{ */


/**
 * @brief Generic write data function
 *
 * @param[in] address         Register address
 *
 * @param[in] writeCommand    Command to write
 *
 * Generic write data function - 8-bit data
 */
void capsense_writeData(uint8_t address, uint8_t writeCommand);

/**
 * @brief Function read from register address
 *
 * @param[in] address         Register address
 *
 * @return    8-bit data from addressed register
 *
 * Generic read data function - 8-bit data
 */
uint8_t capsense_readData(uint8_t address);

/**
 * @brief Function read from register address
 *
 * @param[in] address         Register address
 *
 * @return    16-bit data from addressed register
 *
 * Generic read data function - 16-bit data
 */
uint16_t capsense_readDataBytes(uint8_t address);

/**
 * @brief Function get slider level
 *
 * @return    Slider pressed position
 *
 * Function get slider level
 */
uint16_t capsense_getSliderLvl();

/**
 * @brief Initializes function
 *
 * Function initialisation CapSense register
 */
void capsense_init();









                                                                       /** @} */
#ifdef __cplusplus
} // extern "C"
#endif
#endif

/**
    @example Click_CapSense_STM.c
    @example Click_CapSense_TIVA.c
    @example Click_CapSense_CEC.c
    @example Click_CapSense_KINETIS.c
    @example Click_CapSense_MSP.c
    @example Click_CapSense_PIC.c
    @example Click_CapSense_PIC32.c
    @example Click_CapSense_DSPIC.c
    @example Click_CapSense_AVR.c
    @example Click_CapSense_FT90x.c
    @example Click_CapSense_STM.mbas
    @example Click_CapSense_TIVA.mbas
    @example Click_CapSense_CEC.mbas
    @example Click_CapSense_KINETIS.mbas
    @example Click_CapSense_MSP.mbas
    @example Click_CapSense_PIC.mbas
    @example Click_CapSense_PIC32.mbas
    @example Click_CapSense_DSPIC.mbas
    @example Click_CapSense_AVR.mbas
    @example Click_CapSense_FT90x.mbas
    @example Click_CapSense_STM.mpas
    @example Click_CapSense_TIVA.mpas
    @example Click_CapSense_CEC.mpas
    @example Click_CapSense_KINETIS.mpas
    @example Click_CapSense_MSP.mpas
    @example Click_CapSense_PIC.mpas
    @example Click_CapSense_PIC32.mpas
    @example Click_CapSense_DSPIC.mpas
    @example Click_CapSense_AVR.mpas
    @example Click_CapSense_FT90x.mpas
*/                                                                     /** @} */
/* -------------------------------------------------------------------------- */
/*
  __capsense_driver.h

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