void keyboard_vector(); // defined in keyboard.c

void fast_interrupt_vector(int pc) {}
void interrupt_vector(int pc) {
    keyboard_vector();
}
void reset_vector(int pc) {}
void undefined_instruction_vector(int pc) {}
void software_interrupt_vector(int pc) {}
void prefetch_abort_vector(int pc) {}
void data_abort_vector(int pc) {}
