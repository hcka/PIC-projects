#include <18f4550.h>
#device ADC=10  
#fuses HSPLL,NOWDT,NOPROTECT,NOLVP,NODEBUG,USBDIV,PLL5,CPUDIV1,VREGEN
#use delay (clock=48000000) 

#include "usb_bootloader.h"
#include "flex_lcd.c"
#include "mcu_init.c"

#define analog_conv_const 0.0048828125
#define time_conv_const 0.0054
#define stp_to_vel_const 0.25479

unsigned long int an_inp=0, step=0; 
float conv_dt=0, velocity=0;
unsigned int dty_cyc=0, dty_percent=0, counter=0;
short int St_Sp=0;

#include "interrupts.c"

void main()
{
   mcu_init();
   
   printf(lcd_putc,"\f");
   delay_ms(250);
   printf(lcd_putc,"\f    BamaTech     ");
   delay_ms(3000);      
   printf(lcd_putc,"\f");
   set_pwm1_duty(dty_cyc);
   enable_interrupts(global);
   while(1)   
   {  
      if(input(pin_b2))
        {St_Sp=1;}
      if(input(pin_b3))
        {St_Sp=0;
         set_pwm1_duty(0);}
      if(St_Sp)
      {
         an_inp=read_adc();     

         conv_dt=analog_conv_const*an_inp;
         dty_cyc=25*conv_dt;
         dty_percent=20*conv_dt; 
         set_pwm1_duty(dty_cyc);
      
         delay_ms(250);    
      }
   }
}
