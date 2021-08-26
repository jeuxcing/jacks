


int plug_pins[] = {3, 5, 7, 9, 11};
int network_pins[] = {4, 6, 8, 10, 12};

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  
  for (int i=0 ; i<5 ; i++) {
    pinMode(plug_pins[i], INPUT_PULLUP);
  }
}

void loop() {
  // Read the plugs
  bool pluged = false;
  for (int i=0 ; i<5 ; i++) {
    if (digitalRead(plug_pins[i]) == HIGH)
      pluged = true;
  }

  if (pluged)
    digitalWrite(LED_BUILTIN, HIGH);
  else
    digitalWrite(LED_BUILTIN, LOW);
}
