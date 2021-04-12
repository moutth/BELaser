

#include "DriverJeuLaser.h"

void CallbackSon(void);



int main(void)
{

// ===========================================================================
// ============= INIT PERIPH (faites qu'une seule fois)  =====================
// ===========================================================================

// Après exécution : le coeur CPU est clocké à 72MHz ainsi que tous les timers
CLOCK_Configure();

	// configuration du Timer 4 en débordement 100ms
	
Timer_1234_Init_ff( TIM4, 1.0/0.000091);

Active_IT_Debordement_Timer( TIM4, 2, CallbackSon );
	

//============================================================================	
	
	
while	(1)
	{
	}
}

