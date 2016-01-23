#include "cq.h"

void cq_init(struct cq * const cq,uint8_t *buff,uint32_t buffsize) {
	cq->start = 0;
	cq->end = 0;
	
	cq->buff = buff;
	cq->buffsize = buffsize;
	cq->modsize = (cq->buffsize) - 1;
	
	cq->curfreesize = cq->modsize;
	
}

void cq_reset(struct cq * const cq) {
	cq->start = 0;
	cq->end = 0;
	cq->curfreesize = cq->modsize;
}

uint8_t cq_is_empty(struct cq * const cq) {

	if((cq->curfreesize) == (cq->modsize)) {
		return 1;
	} else {
		return 0;
	}
}


uint8_t cq_is_full(struct cq * const cq) {
	if((cq->curfreesize) == 0) {
		return 1;
	} else {
		return 0;
	}
}

void cq_add(struct cq * const cq,uint8_t ch) {
	cq->buff[cq->end] =  ch;
	(cq->end)++;

	if(((cq->end)) == (cq->buffsize)) {
		cq->end = 0;
	}
	
	(cq->curfreesize)--;

}

uint8_t cq_del(struct cq * const cq) {
	uint8_t ch;

	ch = cq->buff[cq->start];
	(cq->start)++;

	if(((cq->start)) == (cq->buffsize))
		(cq->start) = 0;

	(cq->curfreesize)++;

	return ch;
}

/* 
 * Note : No checks done for bounds. Responsibility lies with the
 * user of the function 
 */
void cq_discard(struct cq * const cq,uint16_t size) {
	if(((cq->start) + size) >= (cq->buffsize)) 
		(cq->start) = size - ((cq->buffsize) - (cq->start));
	 else 
		(cq->start) += size;

	(cq->curfreesize) += size;
}

uint8_t cq_peek(struct cq * const cq,uint16_t index) {
	if(((cq->start) + index) >= (cq->buffsize)) { //If there is wrapping. Wrap to 0 and 
											//then index.
		index -= ((cq->buffsize) - (cq->start));
		return cq->buff[index];
	} else {	
		return cq->buff[(cq->start) + index];
	}
}

uint16_t cq_freesize(struct cq * const cq) {
	return (cq->curfreesize);
}

uint16_t cq_used_size(struct cq * const cq) {
	return (cq->buffsize) - ((cq->curfreesize)+1);
}

