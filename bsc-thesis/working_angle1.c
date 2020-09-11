//Ayarlama esnasýnda motor hareket eder.
int1 working_angle()
{
   angle_adj_flag=1;
   motor_init_flag=0;
   disable_interrupts(int_timer1);
   set_adc_channel(0);
   motor_aninp=read_adc();
   printf(lcd_putc,"\fAci Ayar...");
   while (st_sp_flag!=1)
   {
      printf(lcd_putc,"\nAci= %ld",motor_aninp);
      if (input(fwd_btn))
      {
      posadj_data=posadj_data+5;
         if (posadj_data<=1012)
         {
            motor_aninp=read_adc();
            while (motor_aninp<posadj_data)
            {
               set_pwm2_duty(20);
               motor_aninp=read_adc();
            }
            set_pwm2_duty(0);
            delay_us(20);
         }
         else
            posadj_data=1012;
      }
      if (input(bwd_btn))
      {
      posadj_data=posadj_data-5;
         if (posadj_data>=512)
         {
            motor_aninp=read_adc();
            while (motor_aninp>=posadj_data)
            {
               set_pwm1_duty(20);
               motor_aninp=read_adc();
            }
            set_pwm1_duty(0);
            delay_us(20);
         }
         else
            posadj_data=512;
      }
   }
   printf(lcd_putc,"\fBaslatiliyor...");
   delay_ms(1000);
   return 1;
}
