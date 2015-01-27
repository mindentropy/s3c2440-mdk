#ifndef MEM_CTRL_H_
#define MEM_CTRL_H_

struct mem_ctrl_regs {
	unsigned int BWSCON;
	unsigned int BANKCON0;
	unsigned int BANKCON1;
	unsigned int BANKCON2;
	unsigned int BANKCON3;
	unsigned int BANKCON4;
	unsigned int BANKCON5;
	unsigned int BANKCON6;
	unsigned int BANKCON7;
	unsigned int REFRESH;
	unsigned int BANKSIZE;
	unsigned int MRSRB6;
	unsigned int MRSRB7;
};

#endif
