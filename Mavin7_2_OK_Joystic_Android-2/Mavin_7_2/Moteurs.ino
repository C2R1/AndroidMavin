  //--------------Moteurs--------------
void setupMoteur(){
   
    pinMode(motor1_AvancePin, OUTPUT);     //pin 6 de l Arduino mega comme sortie pour avancer moteur gauche
    pinMode(motor1_ReculPin, OUTPUT);      //pin 7 de l Arduino mega comme sortie pour reculer moteur gauche
    pinMode(motor2_AvancePin, OUTPUT);     //pin 5 de l Arduino mega comme sortie pour avancer moteur droit
    pinMode(motor2_ReculPin, OUTPUT);      //pin 10 de l Arduino mega comme sortie pour reculer moteur gauche
    pinMode(enable_Pin1, OUTPUT);          //pin 45 de l Arduino mega comme sortie  pour activer moteur gauche
    pinMode(enable_Pin2, OUTPUT);          //pin 43 de l Arduino mega comme sortie  pour activer moteur droit
    pinMode(BOUTON2, INPUT);
}





void avancer(int vitesse_av)                   //fonction pour faire avancer
  {
//    Serial.println("FONCTION AVANCER");
    analogWrite(motor1_ReculPin, 0);           //desactiver recul motor droit
    analogWrite(motor2_ReculPin, 0);           //desactiver recul motor gauche
    digitalWrite(enable_Pin1, enable_av);      // activer/desactiver moteur gauche avec bouton1 SW1(voir Gestion)
    digitalWrite(enable_Pin2, enable_av);      // activer/desactiver moteur droit avec bouton1 SW1(voir Gestion)
    analogWrite(motor1_AvancePin, vitesse_av); //commande PWM avancer moteur gauche, 255 pour vitesse max et 1 pour vitesse min
    analogWrite(motor2_AvancePin, vitesse_av); //commande PWM avancer moteur droit,  255 pour vitesse max et 1 pour vitesse min
   
      
 }
void reculer(int vitesse_rec)                  //fonction pour faire reculer                 
{
//Serial.println("FONCTION RECULE");
analogWrite(motor1_AvancePin, 0);              //desactiver avancer motor gauche
analogWrite(motor2_AvancePin, 0);              //desactiver avancer motor droit
digitalWrite(enable_Pin1, HIGH);               //activer moteur gauche
digitalWrite(enable_Pin2, HIGH);               //activer moteur droit
analogWrite(motor1_ReculPin, vitesse_rec);     //commande PWM reculer moteur gauche, 255 pour vitesse max et 1 pour vitesse min 
analogWrite(motor2_ReculPin, vitesse_rec);     //commande PWM reculer moteur droit,  255 pour vitesse max et 1 pour vitesse min

}


void sarreter(){                                //fonction pour arreter moteur gauche et droit

digitalWrite(enable_Pin1, LOW);                 //desactiver motor gauche
digitalWrite(enable_Pin2, LOW);                 //desactiver motor droit

}


void demitour(int vitesse_tour)                 //fonction pour tourner, on fait tourner le moteur gauche dans un sens et le moteur droit dans l'autre
{

analogWrite(motor1_ReculPin, 0);     
analogWrite(motor2_AvancePin, 0);
digitalWrite(enable_Pin1, HIGH);
digitalWrite(enable_Pin2,HIGH);
analogWrite(motor1_AvancePin, vitesse_tour);
analogWrite(motor2_ReculPin,  vitesse_tour);
}

void droite(int vitesse_av)
            {
//Serial.println("FONCTION DROITE");
analogWrite(motor1_ReculPin, 0);           //desactiver recul motor droit
analogWrite(motor2_ReculPin, 0);           //desactiver recul motor gauche
analogWrite(motor2_AvancePin, 0);            //desactiver avancer motor droit
analogWrite(motor1_AvancePin, 0);              //desactiver avancer motor gauche
digitalWrite(enable_Pin2, HIGH);             //activer moteur droit
digitalWrite(enable_Pin1, HIGH);               //activer moteur gauche
analogWrite(motor2_ReculPin, vitesse_av);    //commande PWM reculer moteur droit,  255 pour vitesse max et 1 pour vitesse min    
analogWrite(motor1_AvancePin, vitesse_av);    //commande PWM avancer moteur gauche, 255 pour vitesse max et 1 pour vitesse min
            }

void gauche(int vitesse_av)
          {
//Serial.println("FONCTION GAUCHE");
analogWrite(motor1_ReculPin, 0);           //desactiver recul motor droit
analogWrite(motor2_ReculPin, 0);           //desactiver recul motor gauche
analogWrite(motor1_AvancePin, 0);              //desactiver avancer motor gauche 
analogWrite(motor2_AvancePin, 0);             //desactiver avancer motor droit
digitalWrite(enable_Pin1, HIGH);               //activer moteur gauche
digitalWrite(enable_Pin2, HIGH);               //activer moteur droit
analogWrite(motor1_ReculPin, vitesse_av);      //commande PWM reculer moteur gauche, 255 pour vitesse max et 1 pour vitesse min 
analogWrite(motor2_AvancePin, vitesse_av);      //commande PWM avance moteur droit, 255 pour vitesse max et 1 pour vitesse min 
           }
           
           
void tournedroite(int vitesse_av)
          {
//Serial.println("FONCTION TOURNEDROITE");
analogWrite(motor1_ReculPin, 0);           //desactiver recul motor droit
analogWrite(motor2_ReculPin, 0);           //desactiver recul motor gauche
analogWrite(motor1_AvancePin, 0);              //desactiver avancer motor gauche 
analogWrite(motor2_AvancePin, 0);             //desactiver avancer motor droit
digitalWrite(enable_Pin2, HIGH);             //activer moteur droit  
analogWrite(motor2_ReculPin, vitesse_av);    //commande PWM reculer moteur droit,  255 pour vitesse max et 1 pour vitesse min 

          }
          
void tournegauche(int vitesse_av)
          {
//Serial.println("FONCTION TOURNEGAUCHE");
analogWrite(motor1_ReculPin, 0);           //desactiver recul motor droit
analogWrite(motor2_ReculPin, 0);           //desactiver recul motor gauche
analogWrite(motor1_AvancePin, 0);              //desactiver avancer motor gauche 
analogWrite(motor2_AvancePin, 0);             //desactiver avancer motor droit
digitalWrite(enable_Pin1, HIGH);             //activer moteur droit  
analogWrite(motor1_ReculPin, vitesse_av);    //commande PWM reculer moteur gauche,  255 pour vitesse max et 1 pour vitesse min 

          }      
  
  
  


