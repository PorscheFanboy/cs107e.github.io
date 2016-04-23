#define GPIO_FUNC  0x20200000
#define GPIO_SET   0x2020001C
#define GPIO_CLR   0x20200028

#define ABORT_OUTPUT (1 << (3*5))
#define ABORT_BIT    (1 << (35-32))

#define DELAY 0x100000

// Flash the red POWER LED 
void abort(void) {
  *((unsigned *)(GPIO_FUNC) + 3) = ABORT_OUTPUT;
  while(1) {
      *((unsigned *)(GPIO_SET) + 1) = ABORT_BIT;
      for( volatile int i = 0; i < DELAY; i++ ) ;
      *((unsigned *)(GPIO_CLR) + 1) = ABORT_BIT;
      for( volatile int i = 0; i < DELAY; i++ ) ;
  }
}
