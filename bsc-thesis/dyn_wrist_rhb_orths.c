#include <16f877.h>
#device ADC=10  
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD 
#use delay (clock=4000000) 

#include <math.h>
#include "flex_lcd.c"
#include "mcu_init.c"

#define status_led pin_c4
#define str_btn pin_b7
#define stp_btn pin_b6
#define fwd_btn pin_b3
#define bwd_btn pin_b2
#define reset pin_c0
#define ena pin_d0
#define enb pin_d1
#define analog_conv_const 0.0048828125
#define angle_conv_const 0.07813

#use fast_io(b) 

int1 st_sp_flag=0, angle_adj_flag=0, motor_init_flag=0;
float spdcon_data;
unsigned int duty_cyc=0;
unsigned long int motor_aninp=0, posadj_data=512, speed_aninp=0; 
unsigned long int difference, lower_limit, upper_limit;

#include "interrupts.c"
#include "motor_init.c"
#include "working_angle.c"
//#include "working_angle1.c"
//#include "demo.c"

void main ()
{   
   mcu_init();
   output_high(ena);
   output_low(enb);
   loop:
   motor_init();
   set_pwm1_duty(0);
   set_pwm1_duty(0);   
   while (st_sp_flag!=1)
      working_angle();
   set_timer0(3036);   
   set_adc_channel(0);
   motor_aninp=read_adc();
   lower_limit=motor_aninp;
   difference=lower_limit-512;
   upper_limit=512-difference;
   printf(lcd_putc,"\f");
   angle_adj_flag=0;
   motor_init_flag=0;
   /*if (upper_limit>=500 || lower_limit<=524)
      demo();*/
   while(1)   
   {
      enable_interrupts(int_timer1);
         while (motor_aninp>=upper_limit && st_sp_flag)
         {           
            if (input(reset))
            {
               st_sp_flag=0;
               set_pwm1_duty(0);
               set_pwm2_duty(0);
               printf(lcd_putc,"\fReset...");
               delay_ms(1000);
               goto loop;              
            }
            set_adc_channel(1);
            delay_us(20);
            speed_aninp=read_adc();
            spdcon_data=analog_conv_const*speed_aninp;
            duty_cyc=spdcon_data*10;
            set_pwm1_duty(duty_cyc);            
            set_adc_channel(0);
            delay_us(20);
            motor_aninp=read_adc();
            delay_us(20);
         }          
         set_pwm1_duty(0);
         delay_ms(100);
         while (motor_aninp<=lower_limit && st_sp_flag)
         {       
            if (input(reset))
            {
               st_sp_flag=0;
               set_pwm1_duty(0);
               set_pwm2_duty(0);
               printf(lcd_putc,"\fReset...");
               delay_ms(1000);
               goto loop;
            }
            set_adc_channel(1);
            delay_us(20);
            speed_aninp=read_adc();
            spdcon_data=analog_conv_const*speed_aninp;
            duty_cyc=spdcon_data*10;
            set_pwm2_duty(duty_cyc);
            set_adc_channel(0);
            delay_us(20);
            motor_aninp=read_adc();
            delay_us(20);
         }        
         set_pwm2_duty(0);
         delay_ms(100);
      }
      set_pwm1_duty(0);
      set_pwm2_duty(0);
      delay_us(20);
} 
