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


/*
 * Copyright (c) 2016 Stanford University.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 * - Neither the name of the Stanford University nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL STANFORD
 * UNIVERSITY OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#endif
