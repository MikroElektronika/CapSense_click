#define CY8C201A0_ADDRESS 0x00

void CY8_WrSingle( unsigned short wAddr,
                   unsigned short wData )
{
    TWI_Start();                           // issue I2C1 start signal
    TWI_Write( CY8C201A0_ADDRESS );           // send byte via I2C1  (command to 24cO2)
    TWI_Write( wAddr );                       // send byte (address of EEPROM location)
    TWI_Write( wData );                       // send data (data to be written)
    TWI_Stop();
}

unsigned short CY8_RdSingle( unsigned short rAddr )
{
    unsigned short rd;

    TWI_Start();                           // issue I2C1 start signal
    TWI_Write( CY8C201A0_ADDRESS );           // send byte via I2C1  (device address + W)
    TWI_Write( rAddr );                       // send byte (data address)
    TWI_Repeated_Start();                  // issue I2C1 signal repeated start
    TWI_Write( CY8C201A0_ADDRESS | 0x01 );    // send byte (device address + R)
    rd = TWI_Read( 0u );                     // Read the data (NO acknowledge)

    while ( !TWI_Is_Idle() )
        asm nop;                            // Wait for the read cycle to finish

    TWI_Stop();

    return rd;
}

void CY8_RdSeq( unsigned short rAddr,
                unsigned char *rcvData,
                unsigned long rLen )
{
    unsigned short i;

    TWI_Start();                           // issue I2C1 start signal
    TWI_Write( CY8C201A0_ADDRESS );           // send byte via I2C1 ( device address + W )
    TWI_Write( rAddr );                       // send byte (address of EEPROM location)
    TWI_Repeated_Start();                  // issue I2C1 signal repeated start
    TWI_Write( CY8C201A0_ADDRESS | 0x01 );    // send byte (device address + R)
    i = 0;

    while ( i < rLen )
    {
        rcvData[ i++ ] = TWI_Read( 1u );     // read data (acknowledge)

        while ( !TWI_Is_Idle() )
            asm nop;                        // Wait for the read cycle to finish
    }

    rcvData[ i ] = TWI_Read( 0u );           // last data is read (no acknowledge)
    TWI_Stop();
}

void CY8_WrSeq( unsigned short wAddr,
                unsigned char *wrData,
                unsigned long rLen )
{
    unsigned long i;

    TWI_Start();                           // issue I2C1 start signal
    TWI_Write( CY8C201A0_ADDRESS );           // send byte via I2C1  (device address + W)
    TWI_Write( wAddr );                       // send byte (address of EEPROM location)
    i = 0;

    while ( i++ < rLen )
    {
        TWI_Write( wrData++ );
        Delay_22us();
    }

    TWI_Stop();
}
