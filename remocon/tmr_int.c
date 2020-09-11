#int_timer0
void timer0_interrupt()
{
   set_timer0(26474);
   output_toggle(pin_e0);
}

