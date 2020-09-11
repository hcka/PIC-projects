void startup()  
{
 printf(lcd_putc,"    KAPLANSAN\n Beyaz Esya A.S");
   delay_ms(2000);
   printf(lcd_putc,"\fProgram Secimi");
   delay_ms(1500);
   printf(lcd_putc,"\f1Beyaz");
   printf(lcd_putc,"\n2Sentetik 3Yunlu");
   while (1)
   {
      if (input(wht))
      {
         selection=1;
         printf(lcd_putc,"\fBeyaz");         
         break;
      }
      if (input(snt))
      {
         selection=2;
         printf(lcd_putc,"\fSentetik");
         break;
      }
      if (input(wol))
      {
         selection=3;
         printf(lcd_putc,"\fYunlu");
         break;
      }
   }
   while(!input(ok))
   {
      printf(lcd_putc,"\nSicaklik: %dC",temp);
   
      if (input(wht) && temp<90)
      {
         temp+=1;
         delay_ms(200);
      }
      if (input(snt) && temp>25)
      {
         temp-=1;
         delay_ms(200);
      }
   }
   delay_ms(500);
   while(!input(ok))
   {   
      if (input(wht) && delayTime<90)
      {
         delayTime+=1;
         delay_ms(200);
      }
      if (input(snt) && delayTime>0)
      {
         delayTime-=1;
         delay_ms(200);
      }
      printf(lcd_putc,"\nGecikme: %ddk ",delayTime);
   }
   if (delaytime!=0)
   {
      seconds=0; 
      minutes=delayTime; 
      hours=0;
      delayFlag=1;
      printf(lcd_putc,"\fBaslayacak...");
   }
   enable_interrupts(int_timer1);
   while (delayFlag)
   {
      printf(lcd_putc,"\n%d:%d:%d",hours,minutes,seconds);
      if (seconds==0 && minutes==0 && hours==0)
      {
         disable_interrupts(int_timer1);
         delayFlag=0;        
         printf(lcd_putc,"\fBaslatiliyor...");
      }
      if (seconds==9)
         printf(lcd_putc,"\n\b");
      //delay_ms(150);
   }
   disable_interrupts(int_timer1);
   printf(lcd_putc,"\fBaslatiliyor...");
   delay_ms(1000);
}
