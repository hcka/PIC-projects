#int_timer0
void tmr0_status_interrupt()
{
   if (angle_adj_flag)
      set_timer0(6);
   else if (motor_init_flag)
      set_timer0(131);
   else
      set_timer0(34286);
   output_toggle(status_led);
}

#int_timer1
void tmr1_display_interrupt()
{
   if (st_sp_flag)
      printf(lcd_putc,"\fAci= %f",(float)motor_aninp*angle_conv_const);
   else if (!st_sp_flag)
      printf(lcd_putc,"\fDurduruldu");
   set_timer1(34286); 
}

#int_ad               
void adc_interrupt()
{ }

#int_RB                
void  start_stop_interrupt()   
{  
   if (input(str_btn) && !input(stp_btn)) 
   {
      st_sp_flag=1;
      output_high(pin_b1);
   }
   if (input(stp_btn) && !input(str_btn))      
   {
      st_sp_flag=0;
      output_low(pin_b1);
   }
}
