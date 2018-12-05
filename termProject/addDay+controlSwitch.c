#include <htc.h>
#define _XTAL_FREQ 4000000
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
int RB4_cnt = 0;
int cnt = 0;
int int_cnt = 0;
int sec = 0;
int sec10 = 0;
const unsigned char conv[10] = { 0xFC, 0x60, 0xDA, 0xF2, 0x66, 0xB6, 0xBE, 0xE4, 0xFE, 0xF6 };
int min = 0;
int min10 = 0;
int hour = 0;
int hour10 = 0;
int year = 2018;
int month = 12;
int maxday;
int day = 1;
int y1, y2, y3, y4, m1, m2, d1, d2;

void interrupt isr()
{
	if (TMR0IE && TMR0IF)
	{
		if (RB3_cnt == 0) {
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
		else if (RB3_cnt == 1) {
			cnt++;
			if (cnt % 4 == 3)
			{
				RB1 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[d2];
				RB2 = 0;
			}
			else if (cnt % 4 == 2)
			{
				RB2 = 1;
				RA2 = 1;
				RA3 = 1;
				PORTC = conv[d1];
				RB1 = 0;
				int_cnt++;
			}
			else if (cnt % 4 == 1)
			{
				RB2 = 1;
				RB1 = 1;
				RA3 = 1;
				PORTC = conv[m2];
				RA2 = 0;

			}
			else
			{
				RB2 = 1;
				RB1 = 1;
				RA2 = 1;
				PORTC = conv[m1];
				RA3 = 0;
				int_cnt++;
			}

			TMR0IF = 0;
		}
		else if (RB3_cnt == 2) {//온도로 바꿀예정
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


		else if (RB3_cnt == 3) {
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
		y1 = (year / 1000) % 10;
		y2 = (year / 100) % 10;
		y3 = (year / 10) % 10;
		y4 = (year) % 10;
		d1 = (day / 10) % 10;
		d2 = (day) % 10;
		m1 = (month / 10) % 10;
		m2 = (month) % 10;

		if (RB3 == 0)
		{
			__delay_ms(20);
			if (RB3 == 0) {
				RB3_cnt++;
				if (RB3_cnt == 5) {
					RB3_cnt = 0;
				}
			}
		}

		if (RB4 == 0)
		{
			__delay_ms(20);
			if (RB4 == 0) {
				RB4_cnt++;
				if (RB4_cnt == 4) {
					RB4_cnt = 0;
				}
			}
		}




		switch (month) {
		case1:
		case3:
		case5:
		case7:
		case8:
		case10:
		case12:
			maxday = 31;
			break;
		case2:
			if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0)) {
				maxday = 29;
				break;
			}
			else {
				maxday = 28;
				break;
			}

		case 4: case 6: case 9: case 11:
			maxday = 30;
			break;
		}

		if (day > maxday) {
			day = 1;
			month++;
			if (month > 12) {
				month = 1;
				year++;
			}
		}

		if (RB3_cnt == 0 && RB4_cnt == 0) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					y4++;
					if (y4 == 10)
					{
						y4 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 0 && RB4_cnt == 1) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					y3++;
					if (y3 == 10)
					{
						y3 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 0 && RB4_cnt == 2) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					y2++;
					if (y2 == 10)
					{
						y2 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 0 && RB4_cnt == 3) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					y1++;
					if (y1 == 10)
					{
						y1 = 0;
					}

				}
			}
		}


		if (RB3_cnt == 1 && RB4_cnt == 0) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					d2++;
					if (d2 == 10)
					{
						d2 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 1 && RB4_cnt == 1) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					d2++;
					if (d2 >= 4)
					{
						d2 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 1 && RB4_cnt == 2) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					m2++;
					if (m2 == 10)
					{
						y2 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 1 && RB4_cnt == 3) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					m1++;
					if (m1 == 2)
					{
						m1 = 0;
					}

				}
			}
		}

		day = 10 * d2 + d1;
		month = 10 * y2 + y1;

		if (day > maxday) {
			day = 1;
		}
		if (day == 0) {
			day = 1;
		}
		if (month == 0) {
			month = 1;
		}

		if (RB3_cnt == 4 && RB4_cnt == 0) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					min++;
					if (min == 10)
					{
						min = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 4 && RB4_cnt == 1) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					min10++;
					if (min10 >= 6)
					{
						min10 = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 4 && RB4_cnt == 2) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					hour++;
					if (hour == 10)
					{
						hour = 0;
					}

				}
			}
		}
		else if (RB3_cnt == 4 && RB4_cnt == 3) {
			if (RB5 == 0)
			{
				__delay_ms(20);
				if (RB5 == 0) {
					hour10++;
					if (hour10 >= 3)
					{
						hour10 = 0;
					}

				}
			}
		}


		if (hour10 == 2 && hour >= 4) {
			hour10 = 0;
			hour = 0;
			day++;
		}

		if (int_cnt == 244) {
			int_cnt = 0;
			sec++;
			if (sec >= 10) {
				sec = 0;
				sec10++;
				if (sec10 >= 6) {
					sec10 = 0;
					min++;
					if (min >= 10) {
						min = 0;
						min10++;
						if (min10 >= 6) {
							min10 = 0;
							hour++;
							if (hour >= 10) {
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


