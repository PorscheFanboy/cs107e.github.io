void timer_vector();

void fast_interrupt_vector(int pc) {}
void interrupt_vector(int pc) {
    timer_vector(pc);
}
void reset_vector(int pc) {}
void undefined_instruction_vector(int pc) {}
void software_interrupt_vector(int pc) {}
void prefetch_abort_vector(int pc) {}
void data_abort_vector(int pc) {}
