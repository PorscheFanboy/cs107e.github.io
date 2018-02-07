#ifndef BACKTRACE_H
#define BACKTRACE_H

/*
 * Functions for debugging backtraces.
 *
 * Author: Julie Zelenski <zelenski@cs.stanford.edu>
 * Mon Feb  5 20:02:27 PST 2018
 */


/* Type: struct frame
 * -------------------
 * This struct stores the information for a caller function who has a
 * frame on the stack. The name is the name of the function.
 * If the function name is not available, the string will be "???".
 * The resume_addr field is the saved lr. The saved lr 
 * (sometimes referred to as "return address") is the address of the 
 * instruction in the caller's sequence of instructions where control 
 * will resume after the callee returns. The resume_offset is the number 
 * of bytes from the start of the function to the resume_addr. This
 * offset represents how far control has advanced into the caller 
 * function before it invoked the callee.
 */
struct frame {
    char *name;
    void *resume_addr;
    int resume_offset;
};

/* Function: backtrace
 * -------------------
 * backtrace() gathers a backtrace for the calling program and writes the
 * call stack information into the array pointed to by f. A backtrace is 
 * the sequence of currently active function calls. Each element in the 
 * array f is of type struct frame (struct described above) Each struct 
 * represents a caller who has a frame on the stack. The max_frames argument 
 * specifies the maximum number of frames that can be stored in the array f. 
 * If the backtrace contains more than max_frames, then the information for 
 * only the max_frames most recent function calls are stored in the array f. 
 * The return value of the function is the number of frames written to f.
 */
int backtrace(struct frame f[], int max_frames);

/* Function: print_frames
 * ----------------------
 * Given an array of frames that has previously been filled in
 * by a call to backtrace(), print_frames prints the backtrace
 * information, one line per frame, using this format:
 *
 *     #0 0x000085f8 at malloc+132
 *     #1 0x00008868 at strndup+28
 *     #2 0x00008784 at main+24
 */
void print_frames(struct frame f[], int n);

/* Function: print_backtrace
 * -------------------------
 * Convenience function that calls backtrace and print_frames to display
 * stack frames of currently executing program.
 */
void print_backtrace(void);

#endif
