# albouquet_lab1

Le lab1 est un projet VHDL couplé au Softcore NIOS2.
Il a pour but de réaliser un chenillard à leds grâce à la carte DE10-lite.
Un programme en .c permet de gérer les périphériques (leds, boutons, switch) et le timer.


La méthode sans polling utilise le gestionnaire des interruptions.

## VHDL : 
	* Un processeur NIOS II, une mémoire, un peripherique JTAG sont ajoutés.
	* Trois IP PIO (1 bit, 4 bits, 8 bits) sont ajoutés pour controler les leds, le trigger et la vitesse.
	* L'IP PIO trigger est relié au controleur d'interruption (IRQ).

## Le programme C : 
	Il permet de gerer la fonction principale pour ecrire sur le registre des LEDs (PIO_0_BASE).
	La fonction de gestion de l'interruption permet de gérer l'activation du chenillard et les switchs.

En restant appuyé sur le bouton B8, le programme allume les leds une à une, avec la vitesse selectionnée avec les switchs.
En lachant le bouton, le chenillard s'arrete.