#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Implemented in assembly in interrupts_asm.s
void system_enable_interrupts(void);
void system_disable_interrupts(void);

// From the linux header
//   https://github.com/raspberrypi/linux/blob/rpi-3.6.y/arch/arm/mach-bcm2708/include/mach/platform.h
#define ARM_IRQ1_BASE                  0
#define INTERRUPTS_TIMER0               (ARM_IRQ1_BASE + 0)
#define INTERRUPTS_TIMER1               (ARM_IRQ1_BASE + 1)
#define INTERRUPTS_TIMER2               (ARM_IRQ1_BASE + 2)
#define INTERRUPTS_TIMER3               (ARM_IRQ1_BASE + 3)
#define INTERRUPTS_CODEC0               (ARM_IRQ1_BASE + 4)
#define INTERRUPTS_CODEC1               (ARM_IRQ1_BASE + 5)
#define INTERRUPTS_CODEC2               (ARM_IRQ1_BASE + 6)
#define INTERRUPTS_VC_JPEG              (ARM_IRQ1_BASE + 7)
#define INTERRUPTS_ISP                  (ARM_IRQ1_BASE + 8)
#define INTERRUPTS_VC_USB               (ARM_IRQ1_BASE + 9)
#define INTERRUPTS_VC_3D                (ARM_IRQ1_BASE + 10)
#define INTERRUPTS_TRANSPOSER           (ARM_IRQ1_BASE + 11)
#define INTERRUPTS_MULTICORESYNC0       (ARM_IRQ1_BASE + 12)
#define INTERRUPTS_MULTICORESYNC1       (ARM_IRQ1_BASE + 13)
#define INTERRUPTS_MULTICORESYNC2       (ARM_IRQ1_BASE + 14)
#define INTERRUPTS_MULTICORESYNC3       (ARM_IRQ1_BASE + 15)
#define INTERRUPTS_DMA0                 (ARM_IRQ1_BASE + 16)
#define INTERRUPTS_DMA1                 (ARM_IRQ1_BASE + 17)
#define INTERRUPTS_VC_DMA2              (ARM_IRQ1_BASE + 18)
#define INTERRUPTS_VC_DMA3              (ARM_IRQ1_BASE + 19)
#define INTERRUPTS_DMA4                 (ARM_IRQ1_BASE + 20)
#define INTERRUPTS_DMA5                 (ARM_IRQ1_BASE + 21)
#define INTERRUPTS_DMA6                 (ARM_IRQ1_BASE + 22)
#define INTERRUPTS_DMA7                 (ARM_IRQ1_BASE + 23)
#define INTERRUPTS_DMA8                 (ARM_IRQ1_BASE + 24)
#define INTERRUPTS_DMA9                 (ARM_IRQ1_BASE + 25)
#define INTERRUPTS_DMA10                (ARM_IRQ1_BASE + 26)
#define INTERRUPTS_DMA11                (ARM_IRQ1_BASE + 27)
#define INTERRUPTS_DMA12                (ARM_IRQ1_BASE + 28)
#define INTERRUPTS_AUX                  (ARM_IRQ1_BASE + 29)
#define INTERRUPTS_ARM                  (ARM_IRQ1_BASE + 30)
#define INTERRUPTS_VPUDMA               (ARM_IRQ1_BASE + 31)

#define ARM_IRQ2_BASE                  32
#define INTERRUPTS_HOSTPORT             (ARM_IRQ2_BASE + 0)
#define INTERRUPTS_VIDEOSCALER          (ARM_IRQ2_BASE + 1)
#define INTERRUPTS_CCP2TX               (ARM_IRQ2_BASE + 2)
#define INTERRUPTS_SDC                  (ARM_IRQ2_BASE + 3)
#define INTERRUPTS_DSI0                 (ARM_IRQ2_BASE + 4)
#define INTERRUPTS_AVE                  (ARM_IRQ2_BASE + 5)
#define INTERRUPTS_CAM0                 (ARM_IRQ2_BASE + 6)
#define INTERRUPTS_CAM1                 (ARM_IRQ2_BASE + 7)
#define INTERRUPTS_HDMI0                (ARM_IRQ2_BASE + 8)
#define INTERRUPTS_HDMI1                (ARM_IRQ2_BASE + 9)
#define INTERRUPTS_PIXELVALVE1          (ARM_IRQ2_BASE + 10)
#define INTERRUPTS_I2CSPISLV            (ARM_IRQ2_BASE + 11)
#define INTERRUPTS_DSI1                 (ARM_IRQ2_BASE + 12)
#define INTERRUPTS_PWA0                 (ARM_IRQ2_BASE + 13)
#define INTERRUPTS_PWA1                 (ARM_IRQ2_BASE + 14)
#define INTERRUPTS_CPR                  (ARM_IRQ2_BASE + 15)
#define INTERRUPTS_SMI                  (ARM_IRQ2_BASE + 16)
#define INTERRUPTS_GPIO0                (ARM_IRQ2_BASE + 17)
#define INTERRUPTS_GPIO1                (ARM_IRQ2_BASE + 18)
#define INTERRUPTS_GPIO2                (ARM_IRQ2_BASE + 19)
#define INTERRUPTS_GPIO3                (ARM_IRQ2_BASE + 20)
#define INTERRUPTS_VC_I2C               (ARM_IRQ2_BASE + 21)
#define INTERRUPTS_VC_SPI               (ARM_IRQ2_BASE + 22)
#define INTERRUPTS_VC_I2SPCM            (ARM_IRQ2_BASE + 23)
#define INTERRUPTS_VC_SDIO              (ARM_IRQ2_BASE + 24)
#define INTERRUPTS_VC_UART              (ARM_IRQ2_BASE + 25)
#define INTERRUPTS_SLIMBUS              (ARM_IRQ2_BASE + 26)
#define INTERRUPTS_VEC                  (ARM_IRQ2_BASE + 27)
#define INTERRUPTS_CPG                  (ARM_IRQ2_BASE + 28)
#define INTERRUPTS_RNG                  (ARM_IRQ2_BASE + 29)
#define INTERRUPTS_VC_ARASANSDIO        (ARM_IRQ2_BASE + 30)
#define INTERRUPTS_AVSPMON              (ARM_IRQ2_BASE + 31)

void interrupts_enable(unsigned n);
void interrupts_disable(unsigned n);

/**
 ** @brief Bits in the Basic register to enable various interrupts.
 **       See the BCM2835 ARM Peripherals manual, section 7.5
 */
#define ARM_IRQ0_BASE                  64
#define INTERRUPTS_ARM_TIMER            (ARM_IRQ0_BASE + 0)
#define INTERRUPTS_ARM_MAILBOX          (ARM_IRQ0_BASE + 1)
#define INTERRUPTS_ARM_DOORBELL_0       (ARM_IRQ0_BASE + 2)
#define INTERRUPTS_ARM_DOORBELL_1       (ARM_IRQ0_BASE + 3)
#define INTERRUPTS_VPU0_HALTED          (ARM_IRQ0_BASE + 4)
#define INTERRUPTS_VPU1_HALTED          (ARM_IRQ0_BASE + 5)
#define INTERRUPTS_ILLEGAL_TYPE0        (ARM_IRQ0_BASE + 6)
#define INTERRUPTS_ILLEGAL_TYPE1        (ARM_IRQ0_BASE + 7)
#define INTERRUPTS_PENDING1             (ARM_IRQ0_BASE + 8)
#define INTERRUPTS_PENDING2             (ARM_IRQ0_BASE + 9)
#define INTERRUPTS_JPEG                 (ARM_IRQ0_BASE + 10)
#define INTERRUPTS_USB                  (ARM_IRQ0_BASE + 11)
#define INTERRUPTS_3D                   (ARM_IRQ0_BASE + 12)
#define INTERRUPTS_DMA2                 (ARM_IRQ0_BASE + 13)
#define INTERRUPTS_DMA3                 (ARM_IRQ0_BASE + 14)
#define INTERRUPTS_I2C                  (ARM_IRQ0_BASE + 15)
#define INTERRUPTS_SPI                  (ARM_IRQ0_BASE + 16)
#define INTERRUPTS_I2SPCM               (ARM_IRQ0_BASE + 17)
#define INTERRUPTS_SDIO                 (ARM_IRQ0_BASE + 18)
#define INTERRUPTS_UART                 (ARM_IRQ0_BASE + 19)
#define INTERRUPTS_ARASANSDIO           (ARM_IRQ0_BASE + 20)

#define INTERRUPTS_BASIC_ARM_TIMER_IRQ         (1 << 0)
#define INTERRUPTS_BASIC_ARM_MAILBOX_IRQ       (1 << 1)
#define INTERRUPTS_BASIC_ARM_DOORBELL_0_IRQ    (1 << 2)
#define INTERRUPTS_BASIC_ARM_DOORBELL_1_IRQ    (1 << 3)
#define INTERRUPTS_BASIC_GPU_0_HALTED_IRQ      (1 << 4)
#define INTERRUPTS_BASIC_GPU_1_HALTED_IRQ      (1 << 5)
#define INTERRUPTS_BASIC_ACCESS_ERROR_1_IRQ    (1 << 6)
#define INTERRUPTS_BASIC_ACCESS_ERROR_0_IRQ    (1 << 7)
void interrupts_enable_basic(unsigned mask);
void interrupts_disable_basic(unsigned mask);

#endif
