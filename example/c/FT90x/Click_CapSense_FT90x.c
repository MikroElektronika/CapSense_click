/*
Example for CapSense Click

    Date          : Jul 2018.
    Author        : Nenad Filipovic

Test configuration FT90x :
    
    MCU                : FT900
    Dev. Board         : EasyFT90x v7 
    FT90x Compiler ver : v2.2.1.0

---

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C and set AN and RST pin as output.
- Application Initialization - Initialization driver enable's - I2C. Initialize CapSense click register and start writen via UART.
- Application Task - (code snippet) This is a example which demonstrates the use of CapSense click board.
     Press top and bottom button and turn it ON or OFF button LED's,
     swipe slider to sent log to the UART where you can track their changes.

Additional Functions :

- UART
- Conversions

*/

#include "Click_CapSense_types.h"
#include "Click_CapSense_config.h"


void systemInit()
{
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_AN_PIN, _GPIO_OUTPUT );
    mikrobus_gpioInit( _MIKROBUS1, _MIKROBUS_RST_PIN, _GPIO_INPUT );

    mikrobus_i2cInit( _MIKROBUS1, &_CAPSENSE_I2C_CFG[0] );

    mikrobus_logInit( _MIKROBUS2, 9600 );

    Delay_100ms();
}

void applicationInit()
{
    capsense_i2cDriverInit( (T_CAPSENSE_P)&_MIKROBUS1_GPIO, (T_CAPSENSE_P)&_MIKROBUS1_I2C, _CAPSENSE_I2C_ADDRESS_0 );
    Delay_100ms();
    
    capsense_init();
    mikrobus_logWrite("Initialisation",_LOG_LINE);
    mikrobus_logWrite("-------------------------------", _LOG_LINE);
    Delay_100ms();
}

void applicationTask()
{
    uint8_t currentLedState;
    uint8_t buttonSelect;
    uint8_t sliderValue;
    uint16_t sliderLvl;
    uint8_t sliderLvlTxt[15];
    uint8_t sliderValueTxt[15];
    
    buttonSelect = capsense_readData( _CAPSENSE_CS_READ_STATUS0 );
    sliderValue = capsense_readDataBytes( _CAPSENSE_CS_READ_RAW );
    capsense_writeData( _CAPSENSE_OUTPUT_PORT0, currentLedState );
    Delay_100ms();

    if ( buttonSelect == 8 )
    {
        currentLedState ^= 0x01;
        Delay_100ms();
    }
    if ( buttonSelect == 16 )
    {
        currentLedState ^= 0x02;
        Delay_100ms();
    }
    if ( buttonSelect == 24 )
    {
        currentLedState = ~currentLedState;
        Delay_100ms();
    }

    sliderLvl = capsense_getSliderLvl();

    if ( sliderValue != 0 )
    {
        mikrobus_logWrite("Slider lvl. ", _LOG_TEXT);
        LongToStr( sliderLvl, sliderLvlTxt );
        mikrobus_logWrite( sliderLvlTxt, _LOG_LINE );

        mikrobus_logWrite("Slider value", _LOG_TEXT);
        LongToStr( sliderValue, sliderValueTxt );
        mikrobus_logWrite( sliderValueTxt, _LOG_LINE );
        mikrobus_logWrite( "", _LOG_LINE );

        Delay_100ms();
    }
}

void main()
{
    systemInit();
    applicationInit();

    while (1)
    {
            applicationTask();
    }
}