#ifndef RB_H
#define RB_H

/*
 * This module defines a ring buffer data structure that provides
 * a fixed-length FIFO (first-in-first-out) queue of int elements.
 *
 * Safe if 1 reader (main program, usually) and 1 writer (interrupt handler,
 * usually) are accessing simultaneously.
 *
 * Author: Philip Levis <pal@cs.stanford.edu>
 * Author: Jule Zelenski <zelenski@cs.stanford.edu>
 */

typedef volatile struct ringbuffer rb_t;

/* 
 * Initializes a new empty ring buffer and returns a pointer to it.
 *
 * @return  pointer to the new ring buffer or NULL if cannot satisfy request.
 *
 * To set up a ring buffer in your code:
 *
 *     rb_t *rb = rb_new();
 *
 * Notice that this interface is slightly different from the _init exposed by
 * other libpi modules. This _new pattern allows a user to have multiple ring
 * buffers, like objects in Java. It also means that users of this
 * module don't need to know the implementation details (like size) of rb_t,
 * since they just keep a pointer. 
 */
rb_t *rb_new(void);

/* 
 * Check if ring buffer is currently empty.
 *
 * @param   `rb` the ring buffer to check
 * @return  0 if rb is empty, non-zero otherwise.
 */
int rb_empty(rb_t *rb);

/* 
 * Check if ring buffer is currently full. When full, elements
 * must first be dequeued before further elements can be enqueued.
 *
 * @param   `rb` the ring buffer to check
 * @return  0 if rb is full, non-zero otherwise.
 */
int rb_full(rb_t *rb);

/*
 * Add an element to the back of ring buffer. If full, the 
 * element is not enqueued.
 *
 * @param   `rb` the ring buffer to check
 * @return  1 if the elem was successfully enqueued, 0 otherwise.
 */
int rb_enqueue(rb_t *rb, int elem);

/* 
 * Removes element from the front of ring buffer and returns it. 
 * If empty, spins and waits (blocks) until an element is 
 * enqueued, and then removes and returns it. If you do not
 * wish to block, check !rb_empty before calling rb_dequeue.
 *
 * @param   `rb` the ring buffer to check
 * @return   the element dequeued
 */
int rb_dequeue(rb_t *rb);

#endif
