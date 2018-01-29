#ifndef MAILBOX_H
#define MAILBOX_H
/*
 * Interface to Raspberry Pi mailboxes for interacting with on-chip
 * peripherals such as the framebuffer and touchscreen.
 *
 * You read the implementation of this module in Lab 5, answering
 * some questions about how and why it works.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Date: Jan 31 2016
 */

#define MAILBOX_BASE     0x2000B880

#define MAILBOX_MAXCHANNEL 16

typedef enum {
    MAILBOX_POWER_MANAGEMENT = 0,
    MAILBOX_FRAMEBUFFER,
    MAILBOX_VIRTUAL_UART,
    MAILBOX_VCHIQ,
    MAILBOX_LEDS,
    MAILBOX_BUTTONS,
    MAILBOX_TOUCHSCREEN,
    MAILBOX_UNUSED,
    MAILBOX_TAGS_ARM_TO_VC,
    MAILBOX_TAGS_VC_TO_ARM,
} mailbox_channel_t;

void mailbox_write(unsigned channel, unsigned addr);
unsigned mailbox_read(unsigned channel);

#endif
