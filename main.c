#include <msp430.h> 

/**
 * main.c
 */
void init_i2c(void)
{
    UCB0CTL0 |= UCSWRST;           // reset control register
    UCB0CTL0 |= UCSSEL_3;          // choose SM Clock
    UCB1BR0 = 10;                  // Set baud rate to 10
    UCB0CTL0 |= UCMODE_3;          // Set to I2C Mode
    UCB0CTL0 |= UCMST;             // Set MU as master
}

void transmit(void)
{

}

void receive(void)
{

}

void port_setup(void)
{

}

/*
 * Addresses for peripherals
 * Soil Moisture Sensor                 0x36(default), 0x36-0x39
 * Temp,Humidity and Light Sensor       temp: humidity: light:
 * NPK Sensor
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer

    UCB0CTL0 |= UCTR;              //Put into transmit mode

    return 0;
}
