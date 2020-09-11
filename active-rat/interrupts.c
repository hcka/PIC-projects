#int_timer0
void timr0_hb_interrupt()
{
   output_toggle(pin_b1);
}

#int_ad               
void adc_interrupt()
{ }

#int_timer3
void tmr3_retardant_interrupt()
{       
   step=get_timer1();
   printf(lcd_putc,"\f");
   lcd_gotoxy(1,1);
   printf(lcd_putc,"\Duty:%2u",dty_percent);
   velocity=step*stp_to_vel_const;
   printf(lcd_putc,"\nHiz :%2.1f",velocity);
   printf(lcd_putc," m/dk");  
   set_timer1(0);
   output_toggle(pin_b0);
}

