//#include "sys/alt_stdio.h"
#include "altera_avalon_pio_regs.h"
#include "system.h"

/* SANS Polling */
/*int main() {

   	//alt_printf("Hello, World!");
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);

	while(1)
	{
		if (IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE) == 0)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0xFF);
		}
		else
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);
		}
	}
	return 0;
}*/

/* Avec POLLING */
int main() {

   	//alt_printf("Hello, World!");
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);

	while(1)
	{
		if (IORD_ALTERA_AVALON_PIO_DATA(PIO_2_BASE) == 0)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0xFF);
		}
		else
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);
		}
	}
	return 0;
}
