#ifndef CQ_H_

#define CQ_H_

#include <stdint.h>

#define BUFFSIZE 260
#define MODSIZE (BUFFSIZE - 1)

struct cq {
	volatile uint8_t *buff;
	volatile uint16_t start;
	volatile uint16_t end;
	volatile uint16_t curfreesize;
	volatile uint16_t buffsize;
	volatile uint16_t modsize;
};

void cq_init(struct cq * const cq,uint8_t *buff,uint16_t buffsize);
uint8_t cq_is_empty(struct cq * const cq);
uint8_t cq_is_full(struct cq * const cq);
void cq_add(struct cq * const cq,uint8_t ch);
uint8_t cq_del(struct cq * const cq);
uint16_t cq_freesize(struct cq * const cq);
uint16_t cq_used_size(struct cq * const cq);
void cq_discard(struct cq * const cq,uint16_t size);
void cq_reset(struct cq * const cq);
uint8_t cq_peek(struct cq * const cq,uint16_t index);

//inline uint16_t cq_get_start(struct cq *cq);

#endif
