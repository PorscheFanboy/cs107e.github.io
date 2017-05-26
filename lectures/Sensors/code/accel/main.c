#include "timer.h"
#include "uart.h"
#include "printf.h"
#include "i2c.h"

#include "LSM6DS33.h"

void main(void) {

	uart_init();

    i2c_init();
	lsm6ds33_init();

    printf("whoami=%x\n", lsm6ds33_get_whoami());

	while(1) { 
        short x, y, z;
        lsm6ds33_read_accelerometer(&x, &y, &z);
        // 16384 is 1g (1g == 1000mg)
        printf("accel=(%dmg,%dmg,%dmg)\n", x/16, y/16, z/16);
        delay_ms(200);
	}
}

