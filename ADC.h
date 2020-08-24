/* 
 * File:   ADC.h
 * Author: ME
 *
 * Created on December 7, 2019, 1:39 PM
 */
//#define __cplusplus

#ifndef ADC_H
#define	ADC_H
#include <xc.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define ADC_FORMAT_RIGHT_JUSTIFIED (1<<7)
#define ADC_FORMAT_LEFT_JUSTIFIED  0
#define ADC_CLOCK_FOSC_2           0
#define ADC_CLOCK_FOSC_8           1
#define ADC_CLOCK_FOSC_32          2
#define ADC_CLOCK_FRC              3
    
#define ADC_CHANNEL_0   0
#define ADC_CHANNEL_1   1
#define ADC_CHANNEL_2   2
#define ADC_CHANNEL_3   3
#define ADC_CHANNEL_4   4
#define ADC_CHANNEL_5   5
#define ADC_CHANNEL_6   6
#define ADC_CHANNEL_7   7
#define ADC_CHANNEL_8   8
#define ADC_CHANNEL_9   9
#define ADC_CHANNEL_10  10
#define ADC_CHANNEL_11  11
#define ADC_CHANNEL_12  12    
#define ADC_CHANNEL_13  13
#define ADC_CHANNEL_CVREF     14   
#define ADC_CHANNEL_FIXEDREF  15     
    
#define ADC_On()    ADCON0|=1
#define ADC_VrefPlusExt()     ADCON1 |=1<<4
#define ADC_VrefPlusVDD()     ADCON1 &=~(1<<4)    
#define ADC_VrefMinusExt()    ADCON1 |=1<<5
#define ADC_VrefMinusVSS()    ADCON1 &=~(1<<5)       
#define INT_ENABLE    1
#define INT_DISABLE   0
    
void ADC_Setup(char Format,char Fosc);
void ADC_Start(void);
unsigned int ADC_GetData(char Format);
void ADC_SetChannel(char channel);
void ADC_Interrupt(char En);
void ADC_ClrIntFlag(void);
void ADC_GetIntFlag(void);



#ifdef	__cplusplus
}
#endif

#endif	/* ADC_H */

