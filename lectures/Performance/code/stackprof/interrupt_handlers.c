/* Interrupt Handlers */

void keyboard_vector();
int stackprof_vector(unsigned pc, unsigned fp);

void interrupt_vector(unsigned pc, unsigned fp) {
    if (stackprof_vector(pc, fp)) {
        return;
    }
    keyboard_vector(pc);
}

// The rest of these should never be called
void fast_interrupt_vector(int pc) {}
void reset_vector(int pc) {}
void undefined_instruction_vector(int pc) {}
void software_interrupt_vector(int pc) {}
void prefetch_abort_vector(int pc) {}
void data_abort_vector(int pc) {}
