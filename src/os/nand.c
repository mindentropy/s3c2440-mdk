#include "nand.h"
#include "gpio_def.h"
#include "clock_pm.h"
#include "uart_util.h"

/* 
 * NAND Page == 2048 Bytes + 64 bytes spare area (2112 bytes).
 * NAND Block == 64 pages.
 */


/*
 * NAND driver will be written for Samsung K9F2G08U0B -> 256MB NAND Flash 
 * 									(Old mini2440) 0xECDA109544 ID 0x9510DAEC
 * NAND driver will be written for Samsung K9K8G08U0D SCB0 -> 1GB NAND Flash 
 * 									(New mini2440) ID 0x9551D3EC
 */

/* *************************************************************************
 *
 * NAND Address bits allocation
 * ----------------------------
 *
 * WITHOUT ECC. i.e. SPARE AREA
 * ----------------------------
 * NAND PAGE OFFSET: has maximum of 2048 values (0-2047) i.e. 11 bits. (b10-b0).
 * NAND PAGE: has maximum of 64 values (0-63) as 64 pages make a block hence
 * 				needs 6 bits. (b16-b11).
 * NAND BLOCK: The remaining bits are for block address.
 *
 *
 * WITH ECC. i.e. SPARE AREA
 * ----------------------------
 * NAND PAGE OFFSET: has maximum of 2048 + 64 bytes = 2112 values (0-2011) i.e. 12 bits.(b11-b0).
 * NAND PAGE: has maximum of 64 values (0-63) as 64 pages make a block hence
 * 				needs 6 bits. (b17-b12).
 * NAND BLOCK: The remaining bits are for block address.
 *
 * ************************************************************************/


struct nand_page_cache_info nand_page_cache;

void set_nand_gpio_config_pins()
{
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG13_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG14_INPUT);
	clear_reg_params(GPCON_REG(GPG_BA),NAND_GPG15_INPUT);

	/* Clear pull up */
	set_reg_params(GPUP_REG(GPG_BA),
								NAND_MEM_PG_CAP_SEL_PIN
								|NAND_MEM_ADDR_CYCL_SEL_PIN
								|NAND_MEM_BUS_WIDTH_SEL_PIN);
}


void wait_until_free()
{
	while(!get_RnB_status())
	{
		uart_puts(UART0_BA,"NAND Busy\n");
	}
}

uint32_t read_nand_id()
{
	send_nand_cmd(CMD_READ_ID);
	wait_until_free();
	send_nand_addr(0x00);
	wait_until_free();

	return read_nand_data();
}



uint32_t read_nand_page_data()
{
	wait_until_free();
	return read_nand_data();
}

/*
 * NAND address calculation.
 * -------------------------
 *
 * PAGE OFFSET -> b10-b0 -> 11 bit offset
 * PAGE -> b16-b11 -> 6 bits
 * BLOCK addr + PAGE -> b18-b17 & b16-b11 -> 2 + 6 = 8 bits
 * Overall PAGE + BLOCK Addr bits (i.e PAGE_ADDR+PAGE+BLOCK) == 11 + 8 = 19 bits
 *
 * Total block size remaining b16-b8
 * Remaining block size is b15-b8(b7 and b6 already sent).
 * BLOCK Bit start is shift of 19 bits.
 * Last block shift is -> 19 bits shift + 8 bits shift(b15-b8)
 * 						->  27 bits
 *
 */


/*
 * TODO: Should the page offset be 11 or 12 bits considering the 
 * 		64 bytes of spare area for ECC?
 */
uint8_t nand_page_read(uint32_t addr)
{

/*
 * TODO: Write appropriate code switch for 3 page and 5 page
 * cycle
 */
	uint16_t i = 0;
	uint32_t nand_val = 0;
	uint16_t offset = get_nand_page_offset(addr);

	if((nand_page_cache.cache_flag) == -1) { //Initial. Cache miss.
//		uart_puts(UART0_BA,"Initial Cache miss\r\n");
		nand_page_cache.cache_flag = 0;
		nand_page_cache.addr_cache = addr>>11;
	} else {
		if((addr>>11) == nand_page_cache.addr_cache) { //Cache hit.
			//uart_puts(UART0_BA,"Cache hit\r\n");
			return nand_page_cache.page_cache[offset];
		} else { //Cache miss.
			nand_page_cache.addr_cache = addr>>11;
		}
	}
	
	send_nand_cmd(CMD_READ_PAGE_START);
	wait_until_free();

	send_nand_addr(0x00); //Column address 1st cycle
	send_nand_addr(0x00); //Column address 2nd cycle.

	send_nand_addr(addr>>11); //PA0-PA5 Page address and 
						  	  //BA6-BA7 Block address 3rd cycle.

	send_nand_addr(addr>>19); // Remaining block size. 4th cycle
	send_nand_addr(addr>>27); //Final block size bit
	
	wait_until_free();
	send_nand_cmd(CMD_READ_PAGE_END);

/*	for(i = 0; i<NAND_DATA_SIZE; i+=4) {
		page_cache[i] = read_nand_page_data();
	}*/

	for(i = 0; i<NAND_DATA_SIZE; i+=4) {
		nand_val = read_nand_page_data();
		nand_page_cache.page_cache[i] = nand_val;
		nand_page_cache.page_cache[i+1] = nand_val>>8;
		nand_page_cache.page_cache[i+2] = nand_val>>16;
		nand_page_cache.page_cache[i+3] = nand_val>>24;
	}

	return nand_page_cache.page_cache[offset];
}


/*
 * nand_page_program design:
 * -------------------------
 *
 * nand_page_program programs a page size with addr being on the page boundary and the 
 * page being the nand_data_size.
 *
 * All the nand algorithms will be clubbed in a library with calls to raw functions
 * in the present file.
 *
 * Algorithms include reliable page program, block erase, management of bad blocks, creation
 * of bbt etc.
 *
 * TODO: Should the programming be done on nand_page_size?
 * TODO: How should I include ECC?
 * TODO: Testing of program and read operations on page boundaries for edge test conditions
 * 		for verification of the addressing mode.
 * TODO: Generation of ECC.
 *
 */
int nand_page_program(uint32_t addr,const char data[])
{
	uint16_t i = 0;

	disable_nand_soft_lock();

	send_nand_cmd(CMD_PROGRAM_PAGE);

	send_nand_addr(addr);
	send_nand_addr((addr>>8) & 0x7);

	send_nand_addr(addr>>11);
	send_nand_addr(addr>>19);
	send_nand_addr(addr>>27);

	
	for(i = 0; i<NAND_DATA_SIZE; i+=4) {
		send_nand_data((data[i+3]<<24)|(data[i+2]<<16)|(data[i+1]<<8)|(data[i]));
	}

	send_nand_cmd(CMD_PROGRAM_PAGE_CONFIRM);

	wait_until_free();

	enable_nand_soft_lock();
	
	return 0;
}

int nand_get_status()
{
	send_nand_cmd(CMD_READ_STATUS);
	
	return read_nand_data() & 0xFF;
}

/*
 * NAND block erase erases and entire block of 64 pages, or 128KB
 */

int nand_block_erase(uint32_t addr)
{
	disable_nand_soft_lock();
	send_nand_cmd(CMD_ERASE_BLOCK);

	wait_until_free();


	send_nand_addr(addr>>11);
	send_nand_addr(addr>>19);
	send_nand_addr(addr>>27);
	wait_until_free();

	send_nand_cmd(CMD_ERASE_CONFIRM);

	wait_until_free();


	/* If the block is already cached and the block address is the same */
	if((nand_page_cache.cache_flag) == 0 && 
				((nand_page_cache.addr_cache) >> 16) == (addr>>16)) {
		nand_page_cache.cache_flag = -1; //Disable cache.
	}
											
	enable_nand_soft_lock();

	return 0;
}


/*
 * NAND Init timing calculation explanation:
 * =========================================
 *
 * All credits go to Juergen Borleis of Pengutronix for the below explanation.
 *
 * Twrph0 is the "setup time", Twrph1 is the "hold time" for the data, command and address. 
 * Tacls is the additional time prior a command or address cycle.
 * Your NAND needs 12 ns for Tacls (they call it "CLE Setup Time" and "ALE Setup Time"), 
 * and 12 ns for Twrph0 (they call it "Data Setup Time") and 5 ns for 
 * Twrph1 (they call it "Data Hold Time") [1].
 * The S3C2440 manual shows an example[2]. To get 12 ns setup time you need to 
 * set Twrph0 to 1 which means two clocks at 100 MHz (= 20 ns), to get the 5 ns 
 * for Twrph1 you set it 0 which means one clock at 100 MHz (= 10 ns). For the 
 * Tacls your need to set it to two to get two clocks at 100 MHz (= 20 ns).  
 * For a read or write cycle this will result into 30 ns per byte which matches 
 * the 25 ns cycle time your NAND needs.
 *
 * [1] K9F2G08x0B.pdf, page 10, "AC Timing Characteristics for Command/Address/Data Input"
 * [2] Page 216, section 6-4, Figure 6-3 and Figure 6-4
 *
 * Source:
 * -------
 *   http://article.gmane.org/gmane.comp.embedded.ptxdist.oselas.community/2080 
 *
 */

void nand_init()
{
	uint16_t i = 0;
	/*const char test_data[] = "TEST";*/
	nand_page_cache.cache_flag = -1;
	set_nand_gpio_config_pins();
	apb_clk_enable(CLK_BASE_ADDR,CLK_NAND_FLASH_CNTRL);

	/* 
	 * Tacls = 3
	 * Twrph0 = 7
	 * Twrph1 = 7
	 */
	//Note: Will paramterize the calculation below. Have to 
	//add different NAND flashes though.
	set_tacls_twrph(2,7,7);

	enable_nand_flash_controller();
	
	nand_reset();
	
	/*nand_block_erase(0);

	nand_page_program(0,test_data,4); */

	for(i = 0;i<2048;i++) {
		if(!(i&7)) {
			uart_puts(UART0_BA,"\r\n");
		}
		print_hex_uart_ch(UART0_BA,nand_page_read(i));
		uart_puts(UART0_BA," ");
	}

	uart_puts(UART0_BA,"\r\n");

/*	nand_block_erase(0);

	uart_puts(UART0_BA,"Status :");
	print_hex_uart_ch(UART0_BA,nand_get_status());

	for(i = 0;i<2048;i++) {
		if(!(i&7)) {
			uart_puts(UART0_BA,"\r\n");
		}
		print_hex_uart_ch(UART0_BA,nand_page_read(i));
		uart_puts(UART0_BA," ");
	}
*/

	//uart_puts(UART0_BA,"\r\n");
}
