#include <PJONSoftwareBitBang.h>


#define NB_JACKS 5
#define NET_PIN 2
#define DISCONNECT_DELAY 200

int plug_pins[] = {3, 5, 7, 9, 11};
bool plugged[] = {false, false, false, false, false};
int network_pins[] = {4, 6, 8, 10, 12};
uint8_t pairs[] = {255, 255, 255, 255, 255};
unsigned long last_contact[] = {0, 0, 0, 0, 0};

int current_pin = 100;

PJONSoftwareBitBang jack_bus;
PJONSoftwareBitBang main_bus;

void jack_receiver(uint8_t *payload, uint16_t length, const PJON_Packet_Info &info) {
  pairs[current_pin] = *payload;
  last_contact[current_pin] = millis();
  Serial.println(*payload);
}

void setup() {
  Serial.begin(115200);
  
  for (int i=0 ; i<NB_JACKS ; i++) {
    pinMode(plug_pins[i], INPUT_PULLUP);
  }

  main_bus.strategy.set_pin(NET_PIN);
  main_bus.set_id(1);
  main_bus.begin();

  jack_bus.strategy.set_pin(network_pins[0]);
  jack_bus.set_id(100);
  jack_bus.begin();
  jack_bus.set_receiver(jack_receiver);
}


void loop() {
  for (int i=0 ; i<NB_JACKS ; i++) {
    bool prev = plugged[i];
    plugged[i] = (digitalRead(plug_pins[i]) == LOW);

    if (plugged[i] != prev)
      digitalWrite(LED_BUILTIN, plugged[i] ? HIGH : LOW);

    if (plugged[i] == true) {
      jack_bus.strategy.set_pin(network_pins[i]);
      current_pin = i;
      uint16_t result = jack_bus.receive(100);

      if (millis() - last_contact[i] > DISCONNECT_DELAY) {
        pairs[i] = 255;
      }
    }
  }
}
