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
    IE2 |= UCA0RXIE;

}

void init_i2c(void)
{
    UCB0CTL1 |= UCSWRST;                    //Software reset
    UCB0CLT0 |= UCMST|UCMODE_3|UCSYNC;      //Set sync communication, set as master, and put in i2c mode
    UCB0CLT1 |= UCSSEL_2|UCSWRST;
    UCB0BR0 = 10;
    UCB0BR1 = 0;
    UCB0CTL &= ~UCSWRST;                    //Software reset disabled
    IE2 |= UCB0TXIE;                        //transmit interrupt enabled

}

void clk(void){
    /*
     * figure out how to set up clock to stagger readings
     */
}

void port_setup(void)
{
   P1DIR |= BIT5;
   P1SEL |= BIT1|BIT2|BIT6|BIT7;  //P1.1 = RxD P1.2 = TxD P1.6 = SCL P1.7 = SDA
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
    port_setup();
    init_i2c();
    init_uart();

    while(1){
        UBB0CLT1 |= UCTR;                           //put in transmit mode
        UCB0CLT1 |= UCTXSTT;                        //start transmission

        while((UCB0STAT & UCSTIFG) == 0){           //while transmission interrupt flag is not raised clear flag
            UCB0STAT &= ~UCSTIFG;
        }

        UBB0CLT1 &= ~UCTR;                          //put in receive mode
        UCB0CLT1 |= UCTXSTT;                        //start transmission

        while((UCB0STAT & UCSTIFG) == 0){           //while transmission interrupt flag is not raised clear flag
            UCB0STAT &= ~UCSTIFG;
        }

    }

    return 0;
}


#pragma vector = USCIAB0RX VECTOR
__interrupt void transmit(void){

}

