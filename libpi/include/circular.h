#ifndef CIRCULAR_H
#define CIRCULAR_H

typedef volatile struct cir cir_t;

cir_t *cir_new();

int cir_empty(cir_t *cir);
int cir_full(cir_t *cir);
void cir_enqueue(cir_t *cir, int elem);
int cir_dequeue(cir_t *cir);

#endif
