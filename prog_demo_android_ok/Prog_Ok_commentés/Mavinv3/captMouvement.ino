// ---------------------- pins ---------------------------
#define ledPIN 22            // LED - broche 25
#define detectPIN 53         // Signal du capteur - broche 53

void setupCaptMvmt(){
  pinMode(ledPIN, OUTPUT);  
  pinMode(detectPIN, INPUT);
}

void CaptMvmt(){
  int valeur = digitalRead(detectPIN);
  if (valeur == HIGH)       //présence détectée
    digitalWrite(ledPIN, HIGH);
  else 
    digitalWrite(ledPIN, LOW);
} 
