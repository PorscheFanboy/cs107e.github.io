/*
 * Interface to Raspberry Pi mailbox system, used by libpi to interact
 * with GPU. Note that this interface has been deprecated and so future
 * code should use the property interface instead.
 *
 * Author: Pat Hanrahan <hanrahan@cs.stanford.edu>
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Date: 6/20/17
 */

#include "bcm.h"
#include "memory.h"
#include "mailbox.h"

#define MAILBOX_BASE   0x2000B880

#define MAILBOX_FULL   (1<<31)
#define MAILBOX_EMPTY  (1<<30)

typedef struct {
    unsigned int read;
    unsigned int padding[3]; // note padding to skip 3 words
    unsigned int peek;
    unsigned int sender;
    unsigned int status;
    unsigned int configuration;
    unsigned int write;
} mailbox_t;

void mailbox_write(unsigned channel, unsigned addr) {
    // mailbox has a maximum of 16 channels
    if (channel >= MAILBOX_MAXCHANNEL) {
        return;
    }

    // addresses must be aligned to 16
    if (addr & 0xF) {
        return;
    }

    // mailbox is volatile because the GPU can also write to it
    volatile mailbox_t *mailbox = (volatile mailbox_t *)MAILBOX_BASE;

    while (mailbox->status & MAILBOX_FULL) ;
    // addr is a multiple of 16, so the last 4 bits are 0
    // combine addr with 4-bit channel number
    mailbox->write = addr + channel;
}

unsigned mailbox_read(unsigned channel) {
    if (channel >= MAILBOX_MAXCHANNEL) {
        return 1;
    }

    volatile mailbox_t *mailbox = (volatile mailbox_t *)MAILBOX_BASE;

    while (1) {
        while (mailbox->status & MAILBOX_EMPTY) ;
        unsigned ra = mailbox->read;
        if ((ra & 0xF) == channel) {
            return (ra >> 4);
        }
    }
    return 0;
}


/* Copyright (c) 2017 Stanford University.
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
