#include "DriverJeuLaser.h"

#define CALLBACK_TIME 360000
#define BUF_SIZE 64

#define NB_JOUEURS 4
#define J1 17 //f=85kHz
#define J2 18 //f=90kHz
#define J3 20 //f=100kHz
#define J4 23	//f=115kHz

#define SEUIL_DETECT 0x01000000

int DFT_ModuleAuCarre( short int * Signal64ech, char k);
void CallbackSon(void);

short int dma_buf[BUF_SIZE];
short int joueurs[NB_JOUEURS]= {J1, J2, J3, J4};
int scores_temp[NB_JOUEURS]={0};
int scores[NB_JOUEURS]={0};

void callback_systick () {
	Start_DMA1(BUF_SIZE);
	Wait_On_End_Of_DMA1();
	Stop_DMA1;
	for (int k=0; k<NB_JOUEURS; k++){
		//detection d'une touche du joueur k
		if ((DFT_ModuleAuCarre(dma_buf, joueurs[k])) > SEUIL_DETECT){
			scores_temp[k]++;
			if (scores_temp[k] == 6)
				scores[k]++;
		}
		else
			scores_temp[k]=0;
	}
}

int main(void)
{

	// ===========================================================================
	// ============= INIT PERIPH (faites qu'une seule fois)  =====================
	// ===========================================================================

	// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
	CLOCK_Configure();
	
	//Parametrage du systick
	Systick_Period_ff( CALLBACK_TIME );
	Systick_Prio_IT( 2, callback_systick );
	SysTick_On;
	SysTick_Enable_IT;
	
	//Parametrage de l'ADC
	Init_TimingADC_ActiveADC_ff( ADC1, 72 );
	Single_Channel_ADC( ADC1, 2 );
	Init_Conversion_On_Trig_Timer_ff( ADC1, TIM2_CC2, 225 );
	Init_ADC1_DMA1( 0, dma_buf );	
	
	//Parametrage de l'affichage
	//Init_Affichage();
	
	//Configuration du Timer 4 en débordement 100ms
	//Timer_1234_Init_ff( TIM4, 1.0/0.000091);
	
	
	//============================================================================	
	
		
	while	(1) {	
		
		
	}
}
