#include <htc.h>

void init()
{
	TRISC = 0x00;
	TRISB = 0x00;
	TRISA = 0X01;
	ADCON1 = 0x07;
	TMR0IE = 1;
	OPTION_REG = 0b10000010;	
}
int RB3_cnt = 0;
int cnt = 0;
int int_cnt = 0;
int sec = 0;
int sec10 =0;
const unsigned char conv[10]= { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };
int min=0;
int min10=0;
int hour=0;
int hour10=0;
int year=2018;
int month=12;
int maxday;
int day=1;

void interrupt isr()
{
	if (TMR0IE && TMR0IF)
	{
		
	
	
		if (RB3== 0) {
			cnt++;
			if (cnt % 4 == 3)
			{
				RB1 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[sec10];
				RB2 = 0;
			}
			else if (cnt % 4 == 2)
			{
				RB2 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[sec];
				RB1 = 0;
				int_cnt++;
			}
			else if (cnt % 4 == 1)
			{
				RB2 = 1;
				RB1 = 1;
				RA3 = 1;
				PORTC = conv[min];
				RA2 = 0;

			}
			else
			{
				RB2 = 1;
				RB1 = 1;
				RA2 = 1;
				PORTC = conv[min10];
				RA3 = 0;
				int_cnt++;
			}

			TMR0IF = 0;
		}

		else {
			cnt++;
			if (cnt % 4 == 3)
			{
				RB1 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[min10];
				RB2 = 0;
			}
			else if (cnt % 4 == 2)
			{
				RB2 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[min];
				RB1 = 0;
				int_cnt++;
			}
			else if (cnt % 4 == 1)
			{
				RB2 = 1;
				RB1 = 1;
				RA3 = 1;
				PORTC = conv[hour];
				RA2 = 0;

			}
			else
			{
				RB2 = 1;
				RB1 = 1;
				RA2 = 1;
				PORTC = conv[hour10];
				RA3 = 0;
				int_cnt++;
			}

			TMR0IF = 0;
		}
	}
}

	


void main()
{
	init();
	
 	ei();
	
	while(1)
	{
		

		


		switch(month){
			case1:
			case3:
			case5:
			case7:
			case8:
			case10:
			case12:
				maxday=31;
				break;
			case2:
			if((year%4==0)&&(year%100!=0)||(year%400==0)){
				maxday=29;
				break;
			}
			else{
				maxday=28;
				break;
			}

			case 4: case 6: case 9: case 11:
			maxday =30;
			break;
		}
		
		if(day>maxday){
			day=1;
			month++;
			if(month>12){
				month=1;
				year++;
			}
		}

		if(hour10==2 && hour==4){
		hour10=0;
		hour=0;
		day++;
			}
		
	if(int_cnt == 244){
			int_cnt=0;
			sec++;
			if(sec==10){
				sec=0;
				sec10++;
				if(sec10==6){
					sec10=0;
					min++;
					if(min==10){
						min=0;
						min10++;
						if(min10==6){
							min10=0;
							hour++;
							if(hour==10){
								hour=0;
								hour10++;
								
							}
						}
					}
				}
			}
		}
}
}		
				
		
