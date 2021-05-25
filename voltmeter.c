/*****************************************************
Project : Digitl Voltmeter
Version : 1.0.0
Date    : 25/05/2021
Author  : Embedded Programmer


Chip type               : ATmega16A
Program type            : Application
AVR Core Clock frequency: 11.059200 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 256
*****************************************************/

#include <mega16a.h>
#include <stdio.h>
#include <delay.h>
#include <stdlib.h>


#define ADC_VREF_TYPE 0x40
// Read the AD conversion result
unsigned int read_adc(unsigned char adc_input)
{
    ADMUX=adc_input | (ADC_VREF_TYPE & 0xff);
    // Delay needed for the stabilization of the ADC input voltage
    delay_us(10);
    // Start the AD conversion
    ADCSRA|=0x40;
    // Wait for the AD conversion to complete
    while ((ADCSRA & 0x10)==0);
    ADCSRA|=0x10;
    return ADCW;
}


int a[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,0x63,0x39};

void main(void)
{
// Declare your local variables here
float k;
int k1,k2,k3,k4;
int y;

DDRB=0xFF;

DDRC=0xFF;

DDRD=0xFF;

// Analog Comparator initialization
// Analog Comparator: Off
// Analog Comparator Input Capture by Timer/Counter 1: Off
ACSR=0x80;
SFIOR=0x00;

// ADC initialization
// ADC Clock frequency: 1000/000 kHz
// ADC Voltage Reference: Int., cap. on AREF
// ADC Auto Trigger Source: ADC Stopped
ADMUX=ADC_VREF_TYPE & 0xff;
ADCSRA=0x84;


while (1)
      {
      k=read_adc(7);
      k=k/204.6;
      if(k==5) PORTC.0=1;
      k=k*100;
      y=k;
      k1=y%10;
      y=y/10;
      k2=y%10;
      y=y/10;
      k3=y%10;
      y=y/10;
      k4=y%10;


      PORTB.0=1;
      PORTB.1=0;
      PORTB.2=0;
      PORTB.3=0;
      PORTD=~a[k4];
      delay_us(800);



      PORTB.0=0;
      PORTB.1=1;
      PORTB.2=0;
      PORTB.3=0;
      PORTD=~a[k3];
      PORTD.7=0;
      delay_us(800);




      PORTB.0=0;
      PORTB.1=0;
      PORTB.2=1;
      PORTB.3=0;
      PORTD=~a[k2];

      delay_us(800);



      PORTB.0=0;
      PORTB.1=0;
      PORTB.2=0;
      PORTB.3=1;
      PORTD=~a[k1];
      delay_us(800);


      PORTB.0=0;
      PORTB.1=0;
      PORTB.2=0;
      PORTB.3=0;
      delay_us(50);



      }
}
