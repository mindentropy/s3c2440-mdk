#include "wdt.h"

void disable_watchdog()
{
	writereg32(WTCON,0);
	/*clear_reg_params(
					WTCON,
					WDT_EN
					);*/

}
