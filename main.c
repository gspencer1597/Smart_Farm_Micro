#include <msp430.h> 

/**
 * main.c
 */

void init_uart(void){
    UCA0CLT1 |= UCSWRST|UCSSEL_2;
    UCA0BR0 = 104;
    UCA0BR1 = 0;
    UCA0MCTL = UCBRS_1;
    UCA0CTL1 &= ~UCSWRST;
    IE2 = UCA0RXIE;

}

void init_i2c(void)
{
    UCB0CTL1 |= UCSWRST;
    UCB0CLT0 |= UCMST|UCMODE_3|UCSYNC;
    UCB0CLT1 |= UCSSEL_2|UCSWRST;
    UCB0BR0 = 10;
    UCB0BR1 = 0;
    UCB0I2CSA = 0x48;
    UCB0CTL &= ~UCSWRST;
    IE2 |= UCB0TXIE;

}

void transmit(void)
{

}

void receive(void)
{

}

void port_setup(void)
{
   P1DIR |= BIT5;
   P1SEL |= BIT1|BIT2|BIT6|BIT7;
   P1SEL2 |= BIT1|BIT2|BIT6|BIT7;
   P1OUT &= ~BIT5;
   P1OUT |= BIT5;

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



    return 0;
}
