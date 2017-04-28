#include "timer.h"
#include "gpio.h"
#include "assert.h"

#define DELAY 5
#define FSEL0  0x20200000
#define FSEL1  0x20200004
#define FSEL2  0x20200008
#define SET0   0x2020001C
#define CLR0   0x20200028
#define LEVEL0 0x20200034
  
static unsigned int GET32(unsigned addr)
{
    return *(volatile unsigned *)addr;
} 

void test_timer() {
  timer_init();

  // Test timer incrementing
  unsigned time = timer_get_time();
  for( int i=0; i<10; i++ ) { /* Spin */ }
  unsigned time2 = timer_get_time();
  assert( time2 > time );

  // Test delay
  delay_us(DELAY);
  unsigned time3 = timer_get_time();
  assert( (time3 - DELAY) >= time2 );
}

void test_gpio_set_get_function() {
  gpio_init();

  // Test setting pin to output
  gpio_set_function(GPIO_PIN2, GPIO_FUNC_OUTPUT);
  assert( (GET32(FSEL0)&(0x07<<6)) == (GPIO_FUNC_OUTPUT<<6) );

  // Test getting pin function
  assert( gpio_get_function(GPIO_PIN2) == GPIO_FUNC_OUTPUT );

  // this next test should fail
  // assert( gpio_get_function(GPIO_PIN2) != GPIO_FUNC_OUTPUT );
}

void test_gpio_read_write() {
  // Setup
  gpio_init();
  gpio_set_function(GPIO_PIN20, GPIO_FUNC_OUTPUT);

  // Test writing pin high
  gpio_write(GPIO_PIN20, 1);
  assert( (GET32(LEVEL0)&(1<<20)) != 0 );

  // Test reading pin
  assert( gpio_read(GPIO_PIN20) ==  1 );
}

void main() {
  test_timer();
  test_gpio_set_get_function();
  test_gpio_read_write();

  // If all tests pass, then green ACT LED should turn on at the end.
  // See cstart.c to see how that happens after main() returns.
}
