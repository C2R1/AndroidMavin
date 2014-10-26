void setupSomo14D(){
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(resetPin, OUTPUT);
  digitalWrite(clockPin, HIGH);
  digitalWrite(dataPin, LOW);
  digitalWrite(resetPin, HIGH);
  delay(100);
  digitalWrite(resetPin, LOW);
  delay(10);
  digitalWrite(resetPin, HIGH);
  delay(100);
  sendCommand(VOLUME_7);
}

/**
* Gère le SOMO14D
*/  
void sendCommand(unsigned int command) {
  digitalWrite(clockPin, LOW);
  delay(2);
  
  /* convertit chaque bit de la commande en un signal interprétable
     par le SOMO14D.                                                 */
  for (unsigned int mask = 0x8000; mask > 0; mask >>= 1) {
    // nouveau bit
    if (command & mask) {
      // si le bit n°x de la comande est à 1, signal haut.
      digitalWrite(dataPin, HIGH);
    }
    else {
      // sinon signal bas.
      digitalWrite(dataPin, LOW);
    }
    digitalWrite(clockPin, LOW);
    delayMicroseconds(200);
    digitalWrite(clockPin, HIGH);
    delayMicroseconds(200);
    // fin de bit
  }
  delay(2);
}
