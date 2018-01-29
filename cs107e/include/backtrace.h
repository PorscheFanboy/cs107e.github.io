#ifndef BACKTRACE_H
#define BACKTRACE_H
/*
 * Debugging backtrace support
 */


#include <stdint.h>

/* Type: struct frame
 * -------------------
 * This struct is used to store the information for a caller
 * who has a frame on the stack. The fn_resume field is the
 * saved lr. The saved lr (sometimes referred to as "return
 * address") is the address of the instruction in the caller's
 * sequence of instructions where control will resume after 
 * the call. The fn_first is the address of the first 
 * instruction in the caller's sequence of instructions.
 * The difference between these two addresses represents
 * how far control has advanced into the caller function 
 * before it invoked the callee function.
 */
struct frame {
    uintptr_t fn_resume;
    uintptr_t fn_first;
};

/* Function: backtrace
 * -------------------
 * backtrace() gathers a backtrace for the calling program and 
 * writes the call stack information into the array pointed to by f. 
 * A backtrace is the sequence of currently active function calls. 
 * Each item in the array f is of type struct frame (struct
 * described above) Each struct represents a caller who has a 
 * frame on the stack. 
 * The max_frames argument specifies the maximum number of frames 
 * that can be stored in f. If the backtrace contains more
 * than max_frames, then the information for the max_frames 
 * most recent function calls are returned. The return value 
 * of the function is the number of frames written to f.
 */
int backtrace(struct frame f[], int max_frames);

/* Function: print_frames
 * ----------------------
 * Given an array of frames that has previously been filled in
 * by a call to backtrace(), print_frames prints the backtrace
 * information, one line per frame, using this format:
 *
 *     #0 0x85f8 at malloc+132
 *     #1 0x8868 at strndup+28
 *     #2 0x8784 at main+24
 */
void print_frames(struct frame f[], int n);

/* Function: print_backtrace
 * -------------------------
 * Convenience function that calls backtrace and print_frames to display
 * stack frames of currently executing program.
 */
void print_backtrace(void);

#endif
