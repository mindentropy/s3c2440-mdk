#include "uart_util.h"
#include "cpu.h"
#include "cache.h"
#include "nand.h"
#include "clock_pm.h"
#include "gpio_def.h"
#include "sd_mmc.h"
#include "interrupt.h"
#include "memctl.h"
#include "usb_ohci.h"

void dump_cache_info()
{
	uart_puts(UART0_BA,"Cache info reg:");
	print_hex_uart(UART0_BA,get_cache_info());

	uart_puts(UART0_BA,"cache type:");
	print_hex_uart(UART0_BA,get_cache_type(get_cache_info()));

	uart_puts(UART0_BA,"sbit:");
	print_hex_uart(UART0_BA,get_sbit(get_cache_info()));
	
	uart_puts(UART0_BA,"dsize info:");
	print_hex_uart(UART0_BA,get_dsize_info(get_cache_info()));

	uart_puts(UART0_BA,"isize info:");
	print_hex_uart(UART0_BA,get_isize_info(get_cache_info()));

	uart_puts(UART0_BA,"size:");
	print_hex_uart(UART0_BA,get_size(get_dsize_info(get_cache_info())));

	uart_puts(UART0_BA,"assoc:");
	print_hex_uart(UART0_BA,get_assoc(get_dsize_info(get_cache_info())));

	uart_puts(UART0_BA,"mbit:");
	print_hex_uart(UART0_BA,get_mbit(get_dsize_info(get_cache_info())));
	
	uart_puts(UART0_BA,"line len:");
	print_hex_uart(UART0_BA,get_line_len(get_dsize_info(get_cache_info())));
}

void dump_clk()
{
	uart_puts(UART0_BA,"************************\r\n");

	uart_puts(UART0_BA,"reg_locktime: ");
	print_hex_uart(UART0_BA,readreg32(LOCKTIME_REG(CLK_BASE_ADDR)));
	uart_puts(UART0_BA,"mpllcon : ");
	print_hex_uart(UART0_BA,readreg32(MPLLCON_REG(CLK_BASE_ADDR)));
	uart_puts(UART0_BA,"upllcon : ");
	print_hex_uart(UART0_BA,readreg32(UPLLCON_REG(CLK_BASE_ADDR)));
	uart_puts(UART0_BA,"clkdivn: ");
	print_hex_uart(UART0_BA,readreg32(CLKDIVN_REG(CLK_BASE_ADDR)));
	uart_puts(UART0_BA,"clkslow: ");
	print_hex_uart(UART0_BA,readreg32(CLKSLOW_REG(CLK_BASE_ADDR)));
	uart_puts(UART0_BA,"clkcon: ");
	print_hex_uart(UART0_BA,readreg32(CLKCON_REG(CLK_BASE_ADDR)));

	uart_puts(UART0_BA,"************************\r\n");

}

void dump_nand_dbg()
{
	uart_puts(UART0_BA,"NAND ID:");
	print_hex_uart(UART0_BA,read_nand_id());
	print_hex_uart(UART0_BA,read_nand_data());

	uart_puts(UART0_BA,"NAND Status :");
	print_hex_uart(UART0_BA, nand_get_status());

	uart_puts(UART0_BA,"mem bus width :");
	print_hex_uart(UART0_BA,get_nand_flash_mem_bus_width_status());

	uart_puts(UART0_BA,"mem bus addr cycle :");
	print_hex_uart(UART0_BA,get_nand_flash_mem_addr_cycle_status());

	uart_puts(UART0_BA,"mem page cap :");
	print_hex_uart(UART0_BA,get_nand_flash_mem_page_cap_status());

	uart_puts(UART0_BA,"NCON : ");
	print_hex_uart(UART0_BA,get_gstatus_ncon());

	uart_puts(UART0_BA,"NFCONF : ");
	print_hex_uart(UART0_BA,readreg32(NFCONF_REG(NAND_BA)));

	uart_puts(UART0_BA,"NFCONT : ");
	print_hex_uart(UART0_BA,readreg32(NFCONT_REG(NAND_BA)));
}

void dump_sd_card_info(const struct sd_card_info *sd_card_info)
{

	uart_puts(UART0_BA,"*** SD Card Info ***\n");

	
	if(sd_card_info->is_high_capacity) {
		uart_puts(UART0_BA,"High capacity or extended capacity card\n");
	} else {
		uart_puts(UART0_BA,"Standard capacity card\n");
	}
	
	if(sd_card_info->is_ready_for_switching) {
		uart_puts(UART0_BA,"Card ready for switching\n");
		//TODO: Send CMD11 here.
	} else {
		uart_puts(UART0_BA,"Card not ready for switching\n");
	}

	uart_puts(UART0_BA,"\nCID DUMP\n");

	uart_puts(UART0_BA,"MID : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.MID);

	uart_puts(UART0_BA,"OID : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.CID);

	uart_puts(UART0_BA,"PNM : ");
	uart_puts(UART0_BA,sd_card_info->cid_info.PNM);
	uart_puts(UART0_BA,"\n");

	uart_puts(UART0_BA,"PRV : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.PRV);

	uart_puts(UART0_BA,"PSN : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.PSN);

	uart_puts(UART0_BA,"MDT : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.MDT);

	uart_puts(UART0_BA,"CRC : ");
	print_hex_uart(UART0_BA,sd_card_info->cid_info.CRC);

	uart_puts(UART0_BA,"RCA : ");
	print_hex_uart(UART0_BA,sd_card_info->RCA);

	uart_puts(UART0_BA,"\nCSD DUMP\n");

	uart_puts(UART0_BA,"csd_ver : ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_STRUCT(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"TAAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TAAC(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"NSAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_NSAC(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"TRAN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TRAN(sd_card_info->csd_info.rsp0));

	uart_puts(UART0_BA,"CCC ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_CCC(sd_card_info->csd_info.rsp1));


	uart_puts(UART0_BA,"READ_BLK_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_LEN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"READ_BLK_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_PARTIAL(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"WRITE_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BLK_MISALIGN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"READ_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_READ_BLK_MISALIGN(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"DSR_IMP ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_DSR_IMP(sd_card_info->csd_info.rsp1));

	uart_puts(UART0_BA,"C_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_C_SIZE(sd_card_info->csd_info.rsp1,sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"ERASE_BLK_EN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_ERASE_BLK_EN(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"SECTOR_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_SECTOR_SIZE(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"WP_GRP_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WP_GRP_SIZE(sd_card_info->csd_info.rsp2));

	uart_puts(UART0_BA,"WP_GRP_ENABLE ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WP_GRP_ENABLE(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"R2W_FACTOR ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_R2W_FACTOR(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"WRITE_BL_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BL_LEN(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"WRITE_BL_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_WRITE_BL_PARTIAL(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"FILE_FORMAT_GRP ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_FILE_FORMAT_GRP(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"COPY ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_COPY(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"PERM_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_PERM_WRITE_PROTECT(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"TMP_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_TMP_WRITE_PROTECT(sd_card_info->csd_info.rsp3));

	uart_puts(UART0_BA,"FILE_FORMAT ");
	print_hex_uart(UART0_BA,get_R2_rsp_var_CSD_FILE_FORMAT(sd_card_info->csd_info.rsp3));


	uart_puts(UART0_BA,"****************\n");
}

#ifdef DEBUG_CSD_REG
void parse_CSD_response_reg(uint32_t BA)
{
	uart_puts(UART0_BA, "CSD dump : ");

	uart_puts(UART0_BA,"csd_ver ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_STRUCT(BA));

	uart_puts(UART0_BA,"TAAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TAAC(BA));

	uart_puts(UART0_BA,"NSAC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_NSAC(BA));

	uart_puts(UART0_BA,"TRAN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TRAN(BA));

	uart_puts(UART0_BA,"CCC ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_CCC(BA));

	uart_puts(UART0_BA,"READ_BLK_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_LEN(BA));

	uart_puts(UART0_BA,"READ_BLK_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_PARTIAL(BA));

	uart_puts(UART0_BA,"WRITE_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BLK_MISALIGN(BA));

	uart_puts(UART0_BA,"READ_BLK_MISALIGN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_READ_BLK_MISALIGN(BA));

	uart_puts(UART0_BA,"DSR_IMP ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_DSR_IMP(BA));

	uart_puts(UART0_BA,"C_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_C_SIZE(BA)); 

/*	csd_info->VDD_R_CURR_MIN = get_R2_rsp_CSD_VDD_R_CURR_MIN(BA);
	uart_puts(UART0_BA,"VDD_R_CURR_MIN ");
	print_hex_uart(UART0_BA,csd_info->VDD_R_CURR_MIN);

	csd_info->VDD_R_CURR_MAX = get_R2_rsp_CSD_VDD_R_CURR_MAX(BA);
	uart_puts(UART0_BA,"VDD_R_CURR_MAX ");
	print_hex_uart(UART0_BA,csd_info->VDD_R_CURR_MAX);

	csd_info->VDD_W_CURR_MIN = get_R2_rsp_CSD_VDD_W_CURR_MIN(BA);
	uart_puts(UART0_BA,"VDD_W_CURR_MIN ");
	print_hex_uart(UART0_BA,csd_info->VDD_W_CURR_MIN);

	csd_info->VDD_W_CURR_MAX = get_R2_rsp_CSD_VDD_W_CURR_MAX(BA);
	uart_puts(UART0_BA,"VDD_W_CURR_MAX ");
	print_hex_uart(UART0_BA,csd_info->VDD_W_CURR_MAX);

	csd_info->C_SIZE_MULT = get_R2_rsp_CSD_C_SIZE_MULT(BA);
	uart_puts(UART0_BA,"C_SIZE_MULT ");
	print_hex_uart(UART0_BA,csd_info->C_SIZE_MULT); */

	uart_puts(UART0_BA,"ERASE_BLK_EN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_ERASE_BLK_EN(BA)); 

	uart_puts(UART0_BA,"SECTOR_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_SECTOR_SIZE(BA)); 

	uart_puts(UART0_BA,"WP_GRP_SIZE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WP_GRP_SIZE(BA)); 

	uart_puts(UART0_BA,"WP_GRP_ENABLE ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WP_GRP_ENABLE(BA)); 

	uart_puts(UART0_BA,"R2W_FACTOR ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_R2W_FACTOR(BA)); 

	uart_puts(UART0_BA,"WRITE_BL_LEN ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BL_LEN(BA)); 

	uart_puts(UART0_BA,"WRITE_BL_PARTIAL ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_WRITE_BL_PARTIAL(BA)); 

	uart_puts(UART0_BA,"FILE_FORMAT_GRP ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_FILE_FORMAT_GRP(BA)); 

	uart_puts(UART0_BA,"COPY ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_COPY(BA)); 

	uart_puts(UART0_BA,"PERM_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_PERM_WRITE_PROTECT(BA)); 

	uart_puts(UART0_BA,"TMP_WRITE_PROTECT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_TMP_WRITE_PROTECT(BA)); 

	uart_puts(UART0_BA,"FILE_FORMAT ");
	print_hex_uart(UART0_BA,get_R2_rsp_CSD_FILE_FORMAT(BA)); 

	ack_cmd_resp(BA);
}
#endif

void dump_interrupt_reg()
{

	uart_puts(UART0_BA,"INTSUBMSK :");
	print_hex_uart(UART0_BA,
			get_interrupt_subservice_status(INT_BA,0xFFFFFFFFU));

	print_hex_uart(UART0_BA,
			get_interrupt_sub_source_pending_status(INT_BA,0xFFFFFFFFU));

}

void dump_bank_regs()
{
	uart_puts(UART0_BA,"BWSCON :");
	print_hex_uart(UART0_BA,
					readreg32(BWSCON_REG(MEM_BA)));
}

void dump_usb_regs()
{
	uart_puts(UART0_BA,"HcRevision :");
	print_hex_uart(UART0_BA,
			readreg32(HC_REVISION_REG(USB_OHCI_BA)));
}
