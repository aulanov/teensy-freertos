//#include <kinetis.h>
//#include <stdlib.h>

#include <Arduino.h>
#include <usb_dev.h>

#include <FreeRTOS.h>
#include <task.h>

// extern tasks declared elsewhere in program
void LEDTask(void* args);
void SerialTask(void* args);

int main() {
  usb_init();
  Serial.begin(9600);

  // create the tasks
  xTaskCreate(LEDTask, "LT", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
  xTaskCreate(SerialTask, "ST", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

  // start scheduler, main should stop functioning here
  vTaskStartScheduler();

  return 0;
}
