#include <PJONSoftwareBitBang.h>


#define NB_JACKS 1

#define NET_PIN 2

int plug_pins[] = {3};
int jack_pins[] = {4};
bool plugged[] = {false};

int network_pins[] = {4, 6, 8, 10, 12};
PJONSoftwareBitBang jack_bus;
PJONSoftwareBitBang main_bus;

void jack_receiver(uint8_t *payload, uint16_t length, const PJON_Packet_Info &info) {
  Serial.print("Pouet ");
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
      jack_bus.set_id(100);
      jack_bus.begin();
      uint16_t result = jack_bus.receive(10000);
      if (result != 65535)
        Serial.println(result);
    }
  }
}
