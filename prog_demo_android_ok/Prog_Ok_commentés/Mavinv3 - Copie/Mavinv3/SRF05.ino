//-------------------- Pins ------------------
#define ECHOPIN 8                            
#define TRIGPIN 9 

void setupSRF05(){
  pinMode(ECHOPIN, INPUT);
  pinMode(TRIGPIN, OUTPUT);
}

void SRF05(){ 
  digitalWrite(TRIGPIN, LOW);                   // Set the trigger pin to low for 2uS
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);                  // Send a 10uS high to trigger ranging
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);                   // Send pin low again
  distance = pulseIn(ECHOPIN, HIGH);            // Read in times pulse
  distance = distance/58;                       // calcul la distance par rapport au temps du pulse  

}
void afficheSRF05(){
  Serial3.print("_DIST");
  Serial3.println(distance);
}


