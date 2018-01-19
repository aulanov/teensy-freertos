#include "kinetis.h"
#include "FreeRTOS.h"
#include "task.h"

void yield() {
  taskYIELD();
};

extern volatile uint32_t systick_millis_count;

__attribute__ (( naked ))
void freertos_systick_isr(void) {
  systick_millis_count += 1000/configTICK_RATE_HZ;

  __asm volatile (
      "B      xPortSysTickHandler"
                  );
}

void xPortPendSVHandler( void ) __attribute__ (( naked ));
void vPortSVCHandler( void ) __attribute__ (( naked ));

void vPortSetupTimerInterrupt() {
  _VectorsRam[11] = vPortSVCHandler;
  _VectorsRam[14] = xPortPendSVHandler;
  _VectorsRam[15] = freertos_systick_isr;
}

void fault_isr(void);

void vApplicationStackOverflowHook( xTaskHandle pxTask, char *pcTaskName )
{
  ( void ) pcTaskName;
  ( void ) pxTask;

  /* Run time stack overflow checking is performed if
     configconfigCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
     function is called if a stack overflow is detected. */
  taskDISABLE_INTERRUPTS();
  fault_isr();
  for( ;; );
}
