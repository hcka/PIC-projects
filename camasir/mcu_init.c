void mcu_init()  
{
   setup_psp(psp_disabled);
      
   setup_timer_0(rtcc_internal | rtcc_div_256);   
   enable_interrupts(int_timer0);
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(64286);
   disable_interrupts(int_timer1);
   
   set_tris_b(0xFF);
   disable_interrupts(int_rb);
   
   enable_interrupts(global);
   delay_ms(50);
   lcd_init();
   delay_ms(50);
}
