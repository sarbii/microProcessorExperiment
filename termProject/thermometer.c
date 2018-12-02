#include<htc.h>

#define _XTAL_FREQ 4000000

unsingned int adc,adc_temp,adc_avg;

float volt,temp;
int c1,c2,c3,c4,tmp1,cnt;
const unsigned char digit[10]
= {0x03, 0x9F, 0x25, 0x0D, 0x99, 0x49, 0x41, 0x1B, 0x01, 0x09};


void init()
{
	TRISB = 0x00;
	TRISA = 0xFF;
	TRISC = 0x00;
	ADCON0 = 0x41;
	ADCON1 = 0xc3;
	OPTION_REG = 0b10000011;
	TMR0IE = 1;
}
void interrup ist()
{
	if(TMR0IE && TMR0IF)
	{
		cnt++;
		cnt &= 0x03;
		
		adc = (ADRESH<<8)+ADRESL;
		switch(cnt)
		{
			case 0;
				PORTB = 0;
				PORTC = digit[c1];
				RB3 = 1;
				adc_temp +=adc;
				break;
			case 1;
				PORTB = 0;
				PORTC = digit[c2];
				RC0 =0;
				RB2 = 1;
				adc_temp +=adc;
				break;
			case 2;
				PORTB = 0;
				PORTC = digit[c3];
				RB1 = 1;
				adc_temp +=adc;
				break;
			case 3;
				PORTB = 0;
				PORTC = digit[c4];
				RB0 = 1;
				adc_temp +=adc;
				adc_avg = adc_temp/4;
				adc_temp=0;
				break;
		}
		TMR0IT = 0;
		GO_nDONE = 1;
	}
}

void main()
{
	init();
	__delay_us(20);
	ei();
	while(1)
	{
		volt = adc_avg*1.07526;
		temp = volt/10.0;
		temp1 = temp*100;

		c1=(temp1/1000)%10;
		c2=(temp1/100)%10;
		c3=(temp1/10)%10;
		c4=(temp1)%10;
		
		__delay_ms(2000);
	}
}