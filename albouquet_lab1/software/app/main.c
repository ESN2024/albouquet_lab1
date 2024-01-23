#include "sys/alt_stdio.h"
#include <stdio.h>
#include "altera_avalon_pio_regs.h"
#include "system.h"
#include <sys/alt_irq.h>
#include "io.h"
#include "unistd.h"

#define vitesse_base 1000000

volatile char edge_capture;
volatile __uint32_t vitesse_led;

static void interrupt_handler(void* context, alt_u32 id)
{


	if (edge_capture == 0)
	{
		edge_capture=1;
	}
	else
	{
		edge_capture=0;
	}

	// Recupération de l'état des switch
	char etats_switch=IORD_ALTERA_AVALON_PIO_DATA(PIO_1_BASE);
	
	// Modication de la vitesse du chenillard
	if ( etats_switch != 0x0) vitesse_led/=etats_switch;

	// Replacer l'état de l'interruption par defaut
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE,0);
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE,0xF);
}



/* SANS Polling */
int main() {

	edge_capture=0;
	char masque_led=0x01;
	vitesse_led=vitesse_base;

	// Les leds sont tout d'abord placé à l'état éteint.
	IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);

	// Activation de l'interruption sur la PIO du bouton (PIO_2_BASE)
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PIO_2_BASE,0xF);
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PIO_2_BASE,0);

	// Lie l'interruption du bouton à la fonction interrupt_handler
	alt_irq_register(PIO_2_IRQ, edge_capture, interrupt_handler);
	
	while(1)
	{
		
		if(edge_capture == 1)
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, masque_led);
			masque_led=masque_led << 1;

			// Si le décallage arrive à la fin (plus de led allumée), retour au debut
			if (masque_led == 0x00) masque_led=0x01;
		}
		else
		{
			IOWR_ALTERA_AVALON_PIO_DATA(PIO_0_BASE, 0x00);
			masque_led=0x01;
			vitesse_led=vitesse_base;
		}

		usleep(vitesse_led);
	}
	return 0;
}