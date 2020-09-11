void demo()
{
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
}
