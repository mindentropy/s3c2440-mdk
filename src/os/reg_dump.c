#include "uart_util.h"
#include "cpu.h"
#include "cache.h"
#include "nand.h"
#include "clock_pm.h"
#include "gpio_def.h"

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
