#include "ADC.h"


void ADC_Setup(char Format,char Fosc)
{
    
    
    if(Format)
        ADCON1|=Format;
    else
        ADCON1&=~(1<<7);
    
    ADCON0 &=~(3<<6);         //0b0011111;//0x3F;
    ADCON0 |= Fosc <<6; 
    
   // ADCON1 = (Format) ?  1<<7: 0;
}

void ADC_Start(void)
{
     ADCON0 |=1<<1;   // GO=1
}

unsigned int ADC_GetData(char Format)
{
    unsigned int adcval;
    while( ADCON0 &(1<<1))
               ;
        adcval=(unsigned int) ADRESH<<8 | ADRESL;
    if(Format== ADC_FORMAT_LEFT_JUSTIFIED)
         adcval>>=6;
//    else
//        adcval = ADRESH<<2 | ADRESL>>6; 
    return adcval;     
}

void ADC_SetChannel(char channel)
{
    ADCON0 &= ~(0xF<<2);
    ADCON0|= (channel & 0x0F) <<2;
}
void ADC_Interrupt(char En)
{
    if(En)
    {
      PIR1 &=~(1<<6);  
      PIE1 |=1<<6;
      INTCON |= 1<<7 | 1<<6;
    }
    else
    {
        PIE1&=~(1<<6);
    }
        
        
}
void ADC_ClrIntFlag(void)
{
    
}
void ADC_GetIntFlag(void)
{
    
}