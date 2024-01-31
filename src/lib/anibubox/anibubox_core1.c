/*-----------------------------------------------------------------------------
 *  anibubox_core1.c
 *---------------------------------------------------------------------------*/
/*-----------------------------------------------------------------------------
 *  INCLUDES
 *---------------------------------------------------------------------------*/
#include "../include/anibubox.h"
#include "console.h"

static anibubox_core_e inbox = 0;

static void anibubox_core1_console(void);

void core1_sio_irq() {
    // Just record the latest entry
    while (multicore_fifo_rvalid())
        inbox = multicore_fifo_pop_blocking();

    multicore_fifo_clear_irq();
    printf("Core 1 was here \n");

    switch (inbox)
    {
    case ABB_CORE_1_GO:
        printf("Core 1 got GO signal \n");

        anibubox_core1_console();
        break;

    case ABB_CORE_1_STOP:
        
        //STOP TO BE IMPLEMENTED
        break;
    
    default: // ABB_CORE_NOTHING
        break;
    }
}

uint8_t anibubox_core1(void){

    // the second core needs to wait for the go signal from the first core
    irq_set_exclusive_handler(SIO_IRQ_PROC1, core1_sio_irq);
    irq_set_enabled(SIO_IRQ_PROC0, true);

    return 1;
	
}

static void anibubox_core1_console(void){
    ConsoleInit();
        while(1) 
    	{
    		ConsoleProcess();
    		sleep_ms(2); 
    	}
}

