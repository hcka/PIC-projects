#int_timer0
void tmr0_status_interrupt()
{

}

#int_rb
void emergency_stop_interrupt()
{
   if (input(ok))
   {runFlag=0; emergencyFlag=1;}
   if (emergencyFlag && !runFlag)
   {
      disable_interrupts(int_timer1);
      printf(lcd_putc,"\f   DURDURULDU");
      delay_ms(10000);
      output_high(pin_d0);
      emergencyFlag=0; runFlag=0;
   }
}

#int_timer1
void tmr1_display_interrupt()
{
   output_toggle(pin_d2);
   set_timer1(64286);
   counter+=1;
   if (counter==100 && seconds>=1)
   {counter=0; seconds-=1;}
   if (seconds==0 && minutes>=1)
   {seconds=59; minutes-=1;}
   if (minutes==0 && hours>=1)
   {minutes=59; hours-=1;}
}


