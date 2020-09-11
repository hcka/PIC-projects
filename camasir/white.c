void white()
{
   enable_interrupts(int_rb);
   runFlag=1;
   printf(lcd_putc,"\fBeyaz %dC",temp);
   seconds=0; minutes=15; hours=1;
   if (input(fastProg))
   {seconds=0; minutes=36; hours=0;}
   enable_interrupts(int_timer1);
   while (runFlag)
   {
      printf(lcd_putc,"\n%d:%d:%d",hours,minutes,seconds);
      if (seconds==0 && minutes==0 && hours==0)
      {
         disable_interrupts(int_timer1);
         runFlag=0;        
         printf(lcd_putc,"\fBitti");
      }
   }
   delay_ms(10000);
   output_high(shutterUnlock);
}
