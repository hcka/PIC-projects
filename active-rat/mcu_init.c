void mcu_init()  
{
   setup_psp(psp_disabled);
      
   setup_timer_0(rtcc_internal | rtcc_div_128);   
   set_timer0(18661);
   enable_interrupts(int_timer0);

   setup_adc(adc_clock_div_4);   
   setup_adc_ports(an0);   
   enable_interrupts(int_ad); 

   setup_ccp1(ccp_pwm);
   setup_timer_2(t2_div_by_4,120,1); 
   
   setup_timer_3(t3_internal | t3_div_by_1);
   set_timer3(5536);
   enable_interrupts(int_timer3);
   
   set_timer1(0);
   setup_timer_1(t1_external);
   ext_int_edge(1,h_to_l);
    
   delay_ms(3000); 
   lcd_init();
   delay_ms(1000);
}
