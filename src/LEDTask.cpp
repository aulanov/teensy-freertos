#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>

int ledPin = 13;

void testDelayMS(uint32_t millis) {
  elapsedMicros time;
  while(time < millis*1000) {
    asm volatile("nop\n\t");
  }
}

void LEDTask(void* args) {
  pinMode(ledPin, OUTPUT);

  for(;;){
    Serial.println("Hello again");
    digitalWrite(ledPin, LOW);
    testDelayMS(100);
    digitalWrite(ledPin, HIGH);
    testDelayMS(100);

    digitalWrite(ledPin, LOW);
    testDelayMS(500);
    digitalWrite(ledPin, HIGH);
    testDelayMS(500);
  }
}
