![MikroE](http://www.mikroe.com/img/designs/beta/logo_small.png)

---

# CapSense Click

- **CIC Prefix**  : CAPSENSE
- **Author**      : Nenad Filipovic
- **Verison**     : 1.0.0
- **Date**        : Jul 2018.

---


### Software Support

We provide a library for the CapSense Click on our [LibStock](https://libstock.mikroe.com/projects/view/851/capsense-click-example) 
page, as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). The demo can run on all the main 
MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

**Library Description**

The library covers all the necessary functions to control top button, bottom button and slider on CapSense Click.

Key functions :

- ``` void capsense_writeData(uint8_t address, uint8_t writeCommand) ``` - Generic write data function
- ``` uint8_t capsense_readData( uint8_t address ) ``` - Generic read data function
- ``` void capsense_init() ``` - Initialisation register function

**Examples Description**

Description :

The application is composed of three sections :

- System Initialization - Initializes I2C and set AN and RST pin as output.
- Application Initialization - Initialization driver enable's - I2C. Initialize CapSense click register and start writen via UART.
- Application Task - (code snippet) This is a example which demonstrates the use of CapSense click board.
     Press top and bottom button and turn it ON or OFF button LED's,
     swipe slider to sent log to the UART where you can track their changes.


```.c

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

```


The full application code, and ready to use projects can be found on our 
[LibStock](https://libstock.mikroe.com/projects/view/851/capsense-click-example) page.

Other mikroE Libraries used in the example:

- UART
- Conversions

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.

---
### Architectures Supported

#### mikroC

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroBasic

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

#### mikroPascal

| STM | KIN | CEC | MSP | TIVA | PIC | PIC32 | DSPIC | AVR | FT90x |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| x | x | x | x | x | x | x | x | x | x |

---
---
