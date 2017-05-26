#ifndef GPROF_H
#define GPROF_H

/* Initialize profiler */
void gprof_init(void);

/* Turn on profiling */
void gprof_on(void);

/* Turn off profiling */
void gprof_off(void);

/* Report whether profiling on */
int gprof_is_active(void);

/* Print the profiler results */
void gprof_dump(void);

/* Handle timer interrupts */
void gprof_vector(unsigned pc);

#endif
