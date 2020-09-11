void mcu_init()  
{
   setup_psp(psp_disabled);
      
   setup_timer_0(rtcc_internal | rtcc_div_256);   
   enable_interrupts(int_timer0);
   
   setup_timer_1(t1_internal | t1_div_by_8);
   set_timer1(34286);
   disable_interrupts(int_timer1);

   setup_adc(adc_clock_div_32);   
   setup_adc_ports(an0_an1_vref_vref);  
   enable_interrupts(int_ad); 

   setup_ccp1(ccp_pwm);
   setup_ccp2(ccp_pwm);
   setup_timer_2(t2_div_by_1,49,1);
   set_pwm1_duty(0);
   set_pwm2_duty(0);

   set_tris_b(0xFF);  

   enable_interrupts(int_rb);  
   enable_interrupts(global);
   delay_ms(50);
   lcd_init();
   delay_ms(50);
}
