extern int __bss_start__;
extern int __bss_end__;

#define RPI_INTERRUPT_VECTOR_BASE 0x0
extern int _vectors;
extern int _vectors_end;

void main();

void _cstart() {
    int* bss = &__bss_start__;
    int* bss_end = &__bss_end__;

    while (bss < bss_end) {
        *bss++ = 0;
    }

    main();
}
