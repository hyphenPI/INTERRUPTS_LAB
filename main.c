#include <msp430.h> 
#define DELAY 500000
int i;

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	    P2SEL = 0;
	    P2SEL2 = 0;

	    P2DIR = 0xFF;
	    P2OUT = 0x00;

	    P1DIR &= ~(BIT5 | BIT6 | BIT7);
	    P1REN |= (BIT5 | BIT6 | BIT7);
	    P1OUT |= (BIT5 | BIT6 | BIT7);
	    P1IE |= (BIT5 | BIT6 | BIT7);
	    P1IES |= (BIT5 | BIT6 | BIT7);
	    P1IFG &= (BIT5 | BIT6 | BIT7);
	    _BIS_SR(LPM4_bits+GIE);
	    return 0;
}

#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void){
	    if(P1IFG & BIT5)
	      {
	        for(i = 0; i <4; i++){
	           P2OUT = 3;
	           P2OUT <<= i*2;
	           __delay_cycles(DELAY);
	           P2OUT = 0;
	        }
	        P1IFG &= ~(BIT5);


	      }
	      else if(P1IFG & BIT6){
	          for(i = 0; i < 4; i++){
	              P2OUT = 192;
	              P2OUT = (P2OUT >> i*2);
	              __delay_cycles(DELAY);
	              P2OUT = 0;
	      }
	          P1IFG &= ~(BIT6);
	                  }
	      else if(P1IFG & BIT7){
	          P2OUT = 1;
	          __delay_cycles(DELAY);
	          for(i=0; i < 8; i++){
	              P2OUT <<= 2;
	              __delay_cycles(DELAY);
	              P2OUT >>= 1;
	              __delay_cycles(DELAY);
	          }
	          P1IFG &= ~(BIT7);
	      }

	      }

