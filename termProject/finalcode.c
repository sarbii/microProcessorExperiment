#include <htc.h>

#define _XTAL_FREQ 4000000

void init()

{

	TRISC = 0x00;

	TRISB = 0b00111000;

	TRISA = 0X01;

	ADCON1 = 0x07;

	TMR0IE = 1;

	OPTION_REG = 0b10000010;

}


int cnt = 0;
int int_cnt = 0;
int sec = 5;
int sec10 = 5;
const unsigned char conv[10] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };
int min = 9;
int min10 = 5;
int hour = 3;
int hour10 = 2;
unsigned int year = 2018;
unsigned int month = 2;

unsigned int maxday;
int day = 28;

unsigned int y1, y2, y3, y4, m1, m2, d1, d2, p1, p2, p3;


void interrupt isr()

{

	if (TMR0IE && TMR0IF)
	{

		if (RB3 && !RB4 && RB5) {

			cnt++;
			if (cnt % 4 == 3)
			{
				RB1 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[y3];
				RB2 = 0;
			}

			else if (cnt % 4 == 2)
			{
				RB2 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[y4];
				RB1 = 0;
				int_cnt++;
			}

			else if (cnt % 4 == 1)
			{
				RB2 = 1;
				RB1 = 1;
				RA3 = 1;
				PORTC = conv[y2];
				RA2 = 0;
			}

			else
			{
				RB2 = 1;
				RB1 = 1;
				RA2 = 1;
				PORTC = conv[y1];
				RA3 = 0;
				int_cnt++;
			}

			TMR0IF = 0;
		}


		else if (RB3 && RB4 && !RB5) {
			cnt++;
			if (cnt % 4 == 3)
			{
				RB1 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[day / 10];
				RB2 = 0;
			}

			else if (cnt % 4 == 2)
			{
				RB2 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[day % 10];
				RB1 = 0;
				int_cnt++;
			}

			else if (cnt % 4 == 1)
			{
				RB2 = 1;
				RB1 = 1;
				RA3 = 1;
				PORTC = conv[month % 10];
				RA2 = 0;
			}

			else
			{
				RB2 = 1;
				RB1 = 1;
				RA2 = 1;
				PORTC = conv[month / 10];
				RA3 = 0;
				int_cnt++;
			}

			TMR0IF = 0;

		}


		else if (!RB3 && RB4 && RB5) {
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

	while (1)
	{

		if(hour10 == 0 && hour == 7 && min10==0 && min==0){
			RA4=1;
		}
		else
			RA4=0;
		
		if (hour10 == 2 && hour == 4) {
			hour10 = 0;
			hour = 0;
			day++;
			if (day > maxday) {
				day = 1;
				month++;
				if (month > 12) {
					month = 1;
					year++;

				}

			}

		}



		if (int_cnt == 244) {
			y1 = (year / 1000) % 10;
			y2 = (year / 100) % 10;
			y3 = (year / 10) % 10;
			y4 = (year) % 10;

			if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
			{
				maxday = 31;
			}
			if (month == 4 || month == 6 || month == 9 || month == 11)
			{
				maxday == 30;
			}
			if (month == 2)
			{
				if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {

					maxday = 29;
				}

				else {
					maxday = 28;
				}
			}

			int_cnt = 0;
			sec++;
			if (sec == 10) {
				sec = 0;
				sec10++;
				if (sec10 == 6) {
					sec10 = 0;
					min++;
					if (min == 10) {
						min = 0;
						min10++;
						if (min10 == 6) {
							min10 = 0;
							hour++;
							if (hour == 10) {
								hour = 0;
								hour10++;
							}
						}
					}
				}
			}
		}
	}

}
