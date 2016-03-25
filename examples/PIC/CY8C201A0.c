#define CY8C201A0_ADDRESS 0x00

void CY8_WrSingle( unsigned short wAddr,
                   unsigned short wData )
{
    I2C1_Start();                           // issue I2C1 start signal
    I2C1_Wr( CY8C201A0_ADDRESS );           // send byte via I2C1  (command to 24cO2)
    I2C1_Wr( wAddr );                       // send byte (address of EEPROM location)
    I2C1_Wr( wData );                       // send data (data to be written)
    I2C1_Stop();
}

unsigned short CY8_RdSingle( unsigned short rAddr )
{
    unsigned short rd;

    I2C1_Start();                           // issue I2C1 start signal
    I2C1_Wr( CY8C201A0_ADDRESS );           // send byte via I2C1  (device address + W)
    I2C1_Wr( rAddr );                       // send byte (data address)
    I2C1_Repeated_Start();                  // issue I2C1 signal repeated start
    I2C1_Wr( CY8C201A0_ADDRESS | 0x01 );    // send byte (device address + R)
    rd = I2C1_Rd( 0u );                     // Read the data (NO acknowledge)

    while ( !I2C1_Is_Idle() )
        asm nop;                            // Wait for the read cycle to finish

    I2C1_Stop();

    return rd;
}

void CY8_RdSeq( unsigned short rAddr,
                unsigned char *rcvData,
                unsigned long rLen )
{
    unsigned short i;

    I2C1_Start();                           // issue I2C1 start signal
    I2C1_Wr( CY8C201A0_ADDRESS );           // send byte via I2C1 ( device address + W )
    I2C1_Wr( rAddr );                       // send byte (address of EEPROM location)
    I2C1_Repeated_Start();                  // issue I2C1 signal repeated start
    I2C1_Wr( CY8C201A0_ADDRESS | 0x01 );    // send byte (device address + R)
    i = 0;

    while ( i < rLen )
    {
        rcvData[ i++ ] = I2C1_Rd( 1u );     // read data (acknowledge)

        while ( !I2C1_Is_Idle() )
            asm nop;                        // Wait for the read cycle to finish
    }

    rcvData[ i ] = I2C1_Rd( 0u );           // last data is read (no acknowledge)
    I2C1_Stop();
}

void CY8_WrSeq( unsigned short wAddr,
                unsigned char *wrData,
                unsigned long rLen )
{
    unsigned long i;

    I2C1_Start();                           // issue I2C1 start signal
    I2C1_Wr( CY8C201A0_ADDRESS );           // send byte via I2C1  (device address + W)
    I2C1_Wr( wAddr );                       // send byte (address of EEPROM location)
    i = 0;

    while ( i++ < rLen )
    {
        I2C1_Wr( wrData++ );
        Delay_22us();
    }

    I2C1_Stop();
}
