/*
 * File:   ULTRASONICDISCAL.c
 * Author: ARAVINDHAN
 * Created on 23 January, 2024, 2:52 PM
 */
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#define _XTAL_FREQ 4000000
#define RS RE0
#define EN RE1
#define trig RC0
#define echo RC1
#define buzzer RC2
#define LCD PORTD
int count = 0, d1 = 0, dis = 0, loop=0, dis1 = 0, dis2 = 0, dis3 = 0, dis4 = 0, c1 = 0, c2 = 0, c3 = 0, c4 = 0, time = 0;
char str1[10] = {"Distanc"};
float time2 = 0,time1 = 0;
void lcd(char data, char value)
{
    RS = data;
    LCD = value;
    EN = 1;
    __delay_us(10);
    EN = 0;
    __delay_us(10);
}
int convertion(time1) 
{
    time2 = ((time1/1000.0)/1000.0);
    dis = (((34300*time2)/2)*10);
    return dis;
}
void Buzzer(dis2)
{
    dis4=(dis2/10);
    if (dis4 <= 25)
    {
        buzzer = 1;
    }
    else 
    {
        buzzer = 0;
    }
}

void Distance(dis3)
{
    lcd(0, 0xC0);
    c1 = dis3 % 10;
    c2 = dis3 / 100;
    c3 = c2 % 10;
    c4 = c2 / 10;

    lcd(1, c4 + 48);
    lcd(1, c3 + 48);
    lcd(1, c1 + 48);
    lcd(1, ' ');
    lcd(1, 'c');
    lcd(1, 'm');
}

void main() 
{
    PORTC = PORTD = TRISD = PORTE = TRISE = ANSEL = ANSELH = 0x00;
    TRISC = 0x02;
    lcd(0, 0x38);lcd(0, 0x0C);lcd(0, 0x80);
    T1CON = 0XC1;
    for (loop = 0; str1[loop] != '\0'; loop++)
    {
        lcd(1, str1[loop]);
        __delay_us(10);
    }
    while (1)
    {
        TMR1 = 0;
        trig = 0;
        __delay_us(20);
        trig = 1;
        __delay_us(20);
        trig = 0;
        while (echo == 0);
        TMR1ON=1;
        while (echo == 1);
        TMR1ON = 0;
        time = TMR1;
        dis1 = convertion(time);
        Buzzer(dis1);
        Distance(dis1);
        __delay_us(100);
    }
    
}
