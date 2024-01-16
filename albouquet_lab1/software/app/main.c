#include "sys/alt_stdio.h"
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <sys/alt_irq.h>
#include "io.h"
#include "unistd.h"

volatile int edge_capture;
volatile char vitesse;


static void interrupt_handler(void* context, alt_u32 id)
{
	//volatile int* edge_capture_ptr=(volatile int*) context;
	//*edge_capture_ptr=IORD_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE);
	

	if (edge_capture == 0)
	{
		edge_capture=1;
	}
	else
	{
		edge_capture=0;
	}
	vitesse=IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);


	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE,0);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE,0xF);
	//alt_printf("interrupt");
}



/* SANS Polling */
int main() {

	edge_capture=0;
	char masque_led=0x01;
	int vitesse_led=2000000;
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0xFF);

	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE,0xF);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE,0);

	alt_irq_register(PIO_2_IRQ, edge_capture, interrupt_handler);
	
	while(1)
	{
		
		if(edge_capture == 1)
		{
			switch (vitesse) {
				case 1:
					vitesse_led=1000000;
					break;
				case 2:
					vitesse_led=500000;
					break;
				case 4:
					vitesse_led=200000;
					break;
				case 8:
					vitesse_led=10000;
					break;
				default:
					vitesse_led=2000000;
			}

			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, masque_led);
			masque_led=masque_led << 1;
			if (masque_led == 0x00) masque_led=0x01;
		}
		else
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);
			masque_led=0x01;
			vitesse_led=2000000;
		}

		usleep(vitesse_led);
	}
	return 0;
}





/* Avec POLLING */
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
