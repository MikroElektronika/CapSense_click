/*
 * Project name:
 *    CapSense Click Example
 * Copyright:
 *    (c) Mikroelektronika, 2013.
 * Revision History:
 *    20131204:
 *      - initial release (DO);
 * Description:
 *     This is a simple demonstration how CapSense click can be used.
 *     By pressing the CS button, LED below the button will be toggled ON and OFF.
 *     Swiping the finger over the slider will move the LED on PORTD LED array.
 * Test configuration:
 *    MCU:             ATmega32
 *                     http://www.atmel.com/images/doc2503.pdf
 *    Dev.Board:       EasyAVR v7
 *                     http://www.mikroe.com/easyzvr/
 *    Oscillator:      8.0000 MHz Crystal
 *    Ext. Modules:    CapSense Click board
 *                     ac:CapSense_click
 *                     http://www.mikroe.com/click/capsense/
 *    SW:              mikroC PRO for AVR
 *                     http://www.mikroe.com/mikroc/avr/
 * NOTES:
 *    - Place CapSense click in mikroBUS1 socket
 *    - Turn ON I2C3 switches on SW6.
 *    - Turn ON PORTD LEDs on SW10.
 */

#include "CY8C201A0.h"
#include "built_in.h"

void MCU_Init()
{
    DDRD = 0xFF;
    TWI_Init( 100000 );
    Delay_ms( 150 );
}

void CY8_Set_default_Mode()
{
    Delay_10ms();
    // Enable pins on B0,B1 and slider as CapSense
    CY8_WrSingle( COMMAND_REG, 0x08 );
    CY8_WrSingle( CS_ENABL1,   0x1F );     // Five pins will be used for Slider pads
    CY8_WrSingle( CS_ENABL0,   0x18 );     // Two pins will be used for Button pads
    CY8_WrSingle( GPIO_ENABLE0,0x03 );     // Three pins will be used as GPIO 2 for LED and 1 as GPIO2
    CY8_WrSingle( DM_STRONG0,  0x03 );     // Enables strong drive mode for GPIOs

    // Enable slider
    CY8_WrSingle( CS_SLID_CONFIG, 0x01 );

    // Configure slider resolution
    // Resolution = (SensorsInSlider - 1) * Multiplier
    // Resolution = 4 * 16.00 = 64
    // so the slider_val will be in range 0 to 64
    CY8_WrSingle( CS_SLID_MULM,   0x10 );
    CY8_WrSingle( CS_SLID_MULL,   0x00 );

    CY8_WrSingle( COMMAND_REG, 0x01 );     // Store Current Configuration to NVM
    delay_ms( 150 );

    CY8_WrSingle( COMMAND_REG, 0x06 );     // Reconfigure Device (POR)
    delay_ms( 250 );

    // Initial ON*OFF*ON LEDs (inverse logic 0-LED ON, 1-LED OFF)
    CY8_WrSingle( OUTPUT_PORT0, 0x00 );
    Delay_ms( 500 );

    CY8_WrSingle( OUTPUT_PORT0, 0x03 );
    Delay_ms( 500 );

    CY8_WrSingle( OUTPUT_PORT0, 0x00 );
}

void main()
{
    char            rd_slider[ 2 ];
    char            cs_status;
    unsigned int    slider_val;
    char            btn0st;
    char            btn1st;
    char            led0st      = 0;
    char            led1st      = 0;
    char            tgl0        = 0;
    char            tgl1        = 0;

    MCU_Init();
    CY8_Set_default_Mode();

    while( 1 )
    {
        cs_status = CY8_RdSingle( CS_READ_STATUS0 );
        btn0st = ( cs_status & 0x08 ) >> 3;
        btn1st = ( cs_status & 0x10 ) >> 4;

        // Check button 0
        if( btn0st == 1 )               // Button 0 is pressed
        {
            tgl0 =  1;                  // Update a toggle flag variable
        } else {

            if( tgl0 == 1 )             // Button 0 is pressed and released
            tgl0 = tgl0 | 2;            // Update a toggle flag variable
        }

        if ( tgl0 == 3 )                // Toggle flag is active
        {
            led0st = 0x01 ^ led0st;     // Update the LED status
//*         led0st = 0x02 ^ led0st;
            tgl0 = 0;                   // Reset toggle flag
        }

        // Check button 1
        if( btn1st == 1 )               // Button 1 is pressed
        {
            tgl1 = 1;                   // Update a toggle flag variable

        } else {

            if( tgl1 == 1 )             // Button 1 is pressed and released
                tgl1 = tgl1 | 2;        // Update a toggle flag variable
        }

        if ( tgl1 == 3 )                // Toggle flag is active
        {
            led1st = 0x02 ^ led1st;     // Update the LED status
//*         led0st = 0x01 ^ led0st;
            tgl1 = 0;                   // Reset toggle flag
        }

        CY8_WrSingle( OUTPUT_PORT0, 0x1C | led1st  | led0st );

        // Check for slider action
        CY8_RdSeq( CS_READ_CEN_POSM, &rd_slider, 2 );
        slider_val = rd_slider[ 0 ] << 8 | rd_slider[ 1 ];
        PORTD = 1 << (slider_val >> 3);      // Dividing slider_val(0-64) by 8 will give resolution 0-8
                                         //  which will then move 1(bit) across the PORTD LEDs (as you move over CapSense slider)
    }
}
