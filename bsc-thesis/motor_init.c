int1 motor_init()  
{
   set_pwm1_duty(0);
   set_pwm2_duty(0);
   angle_adj_flag=0;
   motor_init_flag=1;
   disable_interrupts(int_timer1);
   set_adc_channel(0);
   motor_aninp=read_adc();
   printf(lcd_putc,"\fKalibrasyon...");
   while (motor_aninp!=525)
   {
      if (motor_aninp<525)
      {
         while (motor_aninp!=525)
         {
            set_pwm2_duty(25);
            motor_aninp=read_adc();            
         }
         set_pwm2_duty(0);
      }
      if (motor_aninp>525)
      {
         while (motor_aninp!=525)
         {
            set_pwm1_duty(25);
            motor_aninp=read_adc();
         }
         set_pwm1_duty(0);
      }
   }
   set_pwm1_duty(0);
   set_pwm1_duty(0);
   printf(lcd_putc,"\fKalibrasyon OK");
   delay_ms(1000);
   return 1;   
}
