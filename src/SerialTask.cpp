#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>

void testDelayMS(uint32_t millis);

void SerialTask(void* args) {
  // initialize the serial

  for (;;) {
    elapsedMicros time = 0;
    testDelayMS(1000);
    Serial.println("Hello World");
  }
}
