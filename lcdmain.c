/*
 * File:   lcdmain.c
 * Author: ME
 *
 * Created on December 14, 2019, 2:40 PM
 */

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
// CONFIG1
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator: Crystal/resonator on RA6/OSC2/CLKOUT and RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON        // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include<xc.h>
#include "ADC.h"
#include "TIMER2.h"
#include "LCD.h"

#define _XTAL_FREQ 4000000UL

 long map(int from,int from_min,int from_max,int to_min,int to_max);
void Value2Char_Print(volatile signed int Tem);
void Bar_Graph(unsigned int tem);
volatile signed int C,F;
unsigned int ADCVal;
unsigned int ADCValTem;
void main(void) 
{
  //  char A={0x0E,0x11,0x0E,0x04,0x1F,0x04,0x0A,0x11}[2];
  //  char i=2;
  //  char A="Stick Man"[i];
    
    
   
    F=map(C,0,1000,320,2120);
    C=map(F,320,2120,0,1000);
    LCD_Init();
     
//    LCD_WriteCGRAM("Stick Man",0);
//    TMR2_Setup(250,TMR2_PRESC_1_4,TMR2_POSTSC_1_5);
//    TMR2_Interrupt(ENABLE);
//    TMR2_ON();
    LCD_Print("Temperature is:");
   ADC_Setup(ADC_FORMAT_RIGHT_JUSTIFIED,ADC_CLOCK_FOSC_8 );
      ADC_SetChannel( ADC_CHANNEL_0);
      ADC_VrefPlusExt();
      ADC_VrefMinusExt();
    ADCON0|=1;
    TRISB=0X00;
    ANSELH=0;
 ADCValTem=0;
    while(1)
    {
         ADC_Start();
        ADCVal=ADC_GetData(ADC_FORMAT_RIGHT_JUSTIFIED);
        if(ADCValTem!=ADCVal){
            ADCValTem=ADCVal;
            C=map(ADCVal,0,1023,-42,150);
       
           Value2Char_Print(C);
           
        }
            
      Bar_Graph(ADCVal);

    }
}
void Bar_Graph(unsigned int tem){
    tem=tem/128;
    PORTB=1<<tem;
}
void Value2Char_Print(volatile signed int Tem){
    char chr1;
    char chr2;
    char chr3;  
    LCD_GotoXY(1,2);
    LCD_ClearLine(2);
     if(Tem<0)
    LCD_DataWrite('-');
    
 Tem*= (Tem>0) ?  1 : -1;

    chr1=(Tem/100)%10;
    chr2=(Tem/10)%10;
    chr3=(Tem/1)%10; 
 
    if(chr1!=0)
    LCD_DataWrite(chr1+'0');
    if(chr2!=0)
    LCD_DataWrite(chr2+'0');
    LCD_DataWrite(chr3+'0');
    LCD_Print(".0");
    LCD_DataWrite(0XDF);
    LCD_DataWrite('C');
}

//void __interrupt() ISR(void)
//{
//    if (TMR2_GetIntFlag())
//    {
//        TMR2_ClearIntFlag();
//        ADC_Start();
//        ADCVal= ADC_GetData(ADC_FORMAT_RIGHT_JUSTIFIED);
//    }
//}
 long map(int from,int from_min,int from_max,int to_min,int to_max)
{
     volatile long x;
     x= (from-from_min);
     x=(signed long)(from-from_min)*(to_max-to_min);
     x=(signed long) (from-from_min)*(to_max-to_min)/(from_max-from_min);
     x=((signed long) (from-from_min)*(to_max-to_min)/(from_max-from_min)+to_min);
    return ((signed long) (from-from_min)*(to_max-to_min)/(from_max-from_min)+to_min);
}