#include "minimu9v3.h"
#include "i2c.h"
#include "timer.h"
#include "printf.h"

#define GYRO_WHO_AM_I		0x0F
#define GYRO_CTRL1			0x20
#define GYRO_CTRL2			0x21
#define GYRO_CTRL3			0x22
#define GYRO_CTRL4			0x23
#define GYRO_CTRL5			0x24
#define GYRO_TEMP				0x26
#define GYRO_STATUS			0x27
#define GYRO_XL					0x28
#define GYRO_XH					0x29
#define GYRO_YL					0x2A
#define GYRO_YH					0x2B
#define GYRO_ZL					0x2C
#define GYRO_ZH					0x2D

#define ACCEL_TEMPL			0x05
#define ACCEL_TEMPH			0x06
#define ACCEL_WHO_AM_I	0x0F
#define ACCEL_CTRL0			0x1F
#define ACCEL_CTRL1			0x20
#define ACCEL_CTRL2			0x21
#define ACCEL_CTRL3			0x22
#define ACCEL_CTRL4			0x23
#define ACCEL_CTRL5			0x24
#define ACCEL_CTRL6			0x25
#define ACCEL_CTRL7			0x26
#define ACCEL_STATUS		0x27
#define ACCEL_XL				0x28
#define ACCEL_XH				0x29
#define ACCEL_YL				0x2A
#define ACCEL_YH				0x2B
#define ACCEL_ZL				0x2C
#define ACCEL_ZH				0x2D

#define MAG_STATUS			0X07
#define MAG_XL					0x08
#define MAG_XH					0x09
#define MAG_YL					0x0A
#define MAG_YH					0x0B
#define MAG_ZL					0x0C
#define MAG_ZH					0x0D
#define MAG_OFFSET_XL		0x16
#define MAG_OFFSET_XH		0x17
#define MAG_OFFSET_YL		0x18
#define MAG_OFFSET_YH		0x19
#define MAG_OFFSET_ZL		0x1A
#define MAG_OFFSET_ZH		0x1B

#define GYRO_ADJUSTMENT 0.07//0.00875
#define ACCEL_ADJUSTMENT 1

void sensor_write(int slave_address, char slave_register, char value) {
	char data[2];
	data[0] = slave_register;
	data[1] = value;
	i2c_write(slave_address, data, 2);
}

char sensor_read(int slave_address, char slave_register) {
	char data[1];
	data[0] = slave_register;
	i2c_write(slave_address, data, 1);
	i2c_read(slave_address, data, 1);
	return data[0];
}

void gyro_print_xyz() {
	while(1) {
		delay_ms(50);
		int upper = 2500;
		int inc = 100;
		int lower = upper - inc;
		int x = gyro_read_x();
		int y = gyro_read_y();
		int z = gyro_read_z();

		for(int i = lower; i > 0; i -= inc*2) {
			if((x < 0)&&(x < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(x > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%05d |", x);

		for(int i = lower; i > 0; i -= inc*2) {
			if((y < 0)&&(y < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(y > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%05d |", y);

		for(int i = lower; i > 0; i -= inc*2) {
			if((z < 0)&&(z < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(z > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%05d\n", z);
	}
}
void accel_print_xyz() {
	while(1) {
		// delay_ms(50);
		int upper = 25000;
		int inc = 1000;
		int lower = upper - inc;
		int x = accel_read_x();
		int y = accel_read_y();
		int z = accel_read_z();

		for(int i = lower; i > 0; i -= inc*2) {
			if((x < 0)&&(x < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(x > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%07d |", x);

		for(int i = lower; i > 0; i -= inc*2) {
			if((y < 0)&&(y < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(y > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%07d |", y);

		for(int i = lower; i > 0; i -= inc*2) {
			if((z < 0)&&(z < -i)) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		for(int i = 0; i < upper; i += inc*2) {
			if(z > i) {
				printf(".");
			} else {
				printf(" ");
			}
		}
		printf("%07d\n", z);
	}
}

void gyro_init() {
	sensor_write(GYRO, GYRO_CTRL1, 0x0F);
	sensor_write(GYRO, GYRO_CTRL4, 0x20);
}

int gyro_read_coord(char reg) {
	// printf("gyro_read_coord(0x%x)\n", reg);
	char lsb = sensor_read(GYRO, reg);
	char msb = sensor_read(GYRO, (reg+1));
	short val = (lsb & 0xFF) | ((msb & 0xFF) << 8);
	// printf("val = 0x%x\n", val);
	int rate = GYRO_ADJUSTMENT*val;
	// printf("rate = %d\n", rate);
	return rate;
}

int gyro_read_x() {
	return gyro_read_coord(GYRO_XL);
}
int gyro_read_y() {
	return gyro_read_coord(GYRO_YL);
}
int gyro_read_z() {
	return gyro_read_coord(GYRO_ZL);
}

int gyro_read_temp() {
	char dtemp = sensor_read(GYRO, GYRO_TEMP);
	char degC = 25 - dtemp;
	int degF = ((degC * 9) / 5) + 32;
	return degF;
}

void accel_init() {
	sensor_write(ACCEL, ACCEL_CTRL1, 0x67);
}

int accel_read_coord(char reg) {
	// printf("gyro_read_coord(0x%x)\n", reg);
	char lsb = sensor_read(ACCEL, reg);
	char msb = sensor_read(ACCEL, (reg+1));
	short val = (lsb & 0xFF) | ((msb & 0xFF) << 8);
	return (int)val;
	// printf("val = 0x%x\n", val);
	int a = ACCEL_ADJUSTMENT*val;
	// printf("a = %d\n", a);
	return a;
}

int accel_read_x() {
	return accel_read_coord(ACCEL_XL);
}
int accel_read_y() {
	return accel_read_coord(ACCEL_YL);
}
int accel_read_z() {
	return accel_read_coord(ACCEL_ZL);
}