#include "gpio.h"
#include "i2c.h"
#include "assert.h"
#include "minimu9v3.h"
#include "reboot.h"
#include "printf.h"
#include "timer.h"
#include "uart.h"

void test_i2c_init() {
    printf("\ntest_i2c_init()\n");
    assert(gpio_get_function(GPIO_PIN2) == GPIO_FUNC_ALT0);
    assert(gpio_get_function(GPIO_PIN3) == GPIO_FUNC_ALT0);
}
void test_i2c_rw() {
    printf("\ntest_i2c_rw()\n");
    char data[2];
    data[0] = 0x20;
    data[1] = 0x0E;
    char result[1];
    result[0] = 0x01;
    i2c_write(GYRO, data, 2);

    i2c_write(GYRO, data, 1);
    i2c_read(GYRO, result, 1);
    assert(result[0] == 0x0E);

    data[0] = 0x20;
    data[1] = 0x0F;
    i2c_write(GYRO, data, 2);

    i2c_write(GYRO, data, 1);
    i2c_read(GYRO, result, 1);
    assert(result[0] == 0x0F);

    i2c_write(GYRO, result, 1);
    i2c_read(GYRO, result, 1);
    assert(result[0] == 0xD7);
}

void test_gyro_init_xyz_temp() {
    printf("\ntest_gyro_init_xyz()\n");
    assert(sensor_read(GYRO, 0x20) == 0x0F);
    for(int i = 0; i < 10; i++) {
        printf("%04d %04d %04d %04d\n", gyro_read_x(), gyro_read_y(), gyro_read_z(), gyro_read_temp());
        delay_ms(100);
    }
}

void test_accel_init_xyz() {
    printf("\ntest_accel_init()\n");
    assert(sensor_read(ACCEL, 0x20) == 0x67);
    assert(sensor_read(ACCEL, 0x0F) == 0x49);
    for(int i = 0; i < 10; i++) {
        printf("%04d %04d %04d\n", accel_read_x(), accel_read_y(), accel_read_z());
        delay_ms(100);
    }
}

#define DEBUG 1

void main(void) {
    uart_init();
    i2c_init();
    gyro_init();
    accel_init();
    delay(2);

    test_i2c_init();
    test_i2c_rw();

    test_gyro_init_xyz_temp();
    test_accel_init_xyz();

    gyro_print_xyz();
    // accel_print_xyz();

    reboot();
}
