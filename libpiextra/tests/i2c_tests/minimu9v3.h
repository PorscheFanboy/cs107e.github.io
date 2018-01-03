#ifndef MINIMU9V3_H
#define MINIMU9V3_H

/*
 * MinIMU 9 v3 driver for the Raspberry Pi. Currently supports gyro
 * and accelerometer readings.
 *
 * Author: Anna Zeng <zeng@cs.stanford.edu>
 * Date: May 14, 2016
 */

#define GYRO  0b1101011 //0b1101010
#define ACCEL 0b0011101 //0b0011110

void gyro_init();
int gyro_read_x();
int gyro_read_y();
int gyro_read_z();
int gyro_read_temp();

void accel_init();
int accel_read_x();
int accel_read_y();
int accel_read_z();

void sensor_write(int slave_address, char slave_register, char value);
char sensor_read(int slave_address, char slave_register);

void gyro_print_xyz();
void accel_print_xyz();

#endif