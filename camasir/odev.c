#include <16f877.h>
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD 
#use delay (clock=4000000) 

#include "flex_lcd.c"
#include "mcu_init.c"
#define wht pin_c0
#define snt pin_c1
#define wol pin_c2
#define fastProg pin_c3
#define ok pin_b7
#define shutterUnlock pin_d0

int1 delayFlag=0, emergencyFlag=0, runFlag=0;
int8 temp=25, counter=0, seconds=0, minutes=0, hours=0, delayTime=0;
int8 selection=0;

#include "interrupts.c"
#include "startup.c"
#include "white.c"
#include "synthetic.c"
#include "wool.c"

void main ()
{  
   mcu_init();
   startup();
   switch (selection)
   {
      case 1:
         white();
      break;
      case 2:
         synthetic();
      break;
      case 3:
         wool();
      break;
   }
   while(1)   
   {
   output_toggle(pin_d3);
   delay_ms(500);
   }
} 
