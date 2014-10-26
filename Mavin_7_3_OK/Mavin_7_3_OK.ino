/*-------------------------------Mavin_7_3_OK--------------
Ce programme est embarqué dans le Mavin. C'est lui qui gère tous les capteurs, la réception et l'envoi de commandes sur les roues.
modifications apportées:
-dans le sketch1, bouton permettant de mettre en route la fonction reception
-dans le sketch 7(gestion), mise en place de la fonction joystick_mode
-dans le sketch 8(moteurs), ajout de la fonction "tournedroite" et "tournegauche"
-ajout du sketch 16 communication_moteurs
-ajout du sketch 17 reception
* Mavin version 2
* Arduino 1.0
* 07/02/2013
* Auteur: German SUAREZ.
*/

// -------------------------- Bibliothèques ----------------------------
#include "SoftwareSerial.h"
#include "EasyVR.h"
#include "DHT.h"
#include <Wire.h>
//---------------------- Boutons poussoir ------------------------------
#define BOUTON1 28
#define BOUTON2 26
//---------------------- Entrées analogiques ADXL330 -------------------
int X =4;
int Y =5;
int Z =6;
int time;
// ------------------------- Variables et constantes pour boussole ------------------------
int dernAngle;
int angle;
#define sensorAddress 0x60
#define REGISTER 2


// ------------------------- Variables et constantes pour SRF05 --------------------------
int dernDistance;
int distance;
int distLimit = 5;
// ------------------------- Variables et constantes RFID ----------------------------
int data = 0;
int idTag = 0;
int yellowTag[14] = {2,48,48,48,48,53,54,55,50,56,65,65,69,3}; 
int blueTag[14] = {2,48,49,48,48,53,68,52,68,54,70,55,69,3}; 
int redTag[14] = {2,51,-6,48,48,57,67,53,65,51,69,67,51,3}; 
int newTag[14] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// ------------------------ Variables RecoVocale -----------------------
SoftwareSerial port(12,13); // tx: broche 12, rx: broche 13
EasyVR easyvr(port);
EasyVRBridge bridge;        /* création du "bridge" mode sous lequel on
                               travaille.*/

boolean bouge = false;
boolean enable_eayvr = true;
int8_t idx, group;


// ---------------------------- Variables et constantes DHT11 ------------------------
int SensorAir;
float q, h, t;
#define DHTPIN 11       
#define DHTTYPE DHT11   

// ---------------------------- Variables et constantes pour capteur qualité d'air ------------------------

//-------autres
char validation=0;

//----------------------- Pin pour SOMO14D -----------------------------
const int clockPin = 2;  
const int dataPin = 3;  
const int resetPin = 4;  
// ----------------------Registres pour SOMO14D ------------------------
const unsigned int VOLUME_7 = 0xFFF7;
unsigned int sonDemarrage = 0;
const unsigned int STOP = 0xFFFF;

//----------------------------- automate -------------------------------
int etat;
boolean commande = false;
//------------------------------Variables et constantes pour rception
byte commandebit=0; 
byte commande2=0;

//----------------------------- Pins pour Moteurs -------------------------------
  const int motor1_AvancePin = 6;  
  const int motor1_ReculPin  = 7;
  const int motor2_AvancePin = 5 ; 
  const int motor2_ReculPin  = 10;
  const int enable_Pin1 = 45;    
  const int enable_Pin2 = 43;
  int etat_moteur=1;
  int vitesse_av;
  int vitesse_rec;
  boolean enable_av = false;

//-------------------------------------------------------------------------------
void setup(){
  //--------------------- Initialision des capteurs --------------------
  setupSomo14D();
  setupMoteur();
  setupBuzz ();
  //---------------------- Initialision  bus I²C -----------------------
  Wire.begin();
  //--------------------- Initialisation port PC -----------------------
  Serial.begin(9600);
  //--------------------- Initialisation RFID --------------------------
  Serial2.begin(9600); 
setupBlueToothConnection();
  //--------------------- Initialision des capteurs --------------------
  setupSRF05();
  setupAccelerometre();
  setupDht11();
  setupCaptMvmt();
  setupEasyVR();

  //----------------------- Initialision de l'état ---------------------
 etat=0;
  
  delay(2000);
}

void loop(){
  
  Serial.println("on rentre dans la boucle");
  
if (digitalRead(BOUTON2) == LOW )//mantenir SW2 avant allumage pour éthylotest
 {
 sendCommand(1);
 etat=3;
}
  switch(etat){
    case 0: selectMode();// lecture du TAG (voir sketch Gestion et RFID)
            Serial.println("Lecture du tag(etat=0)");
            break;
 
    case 2: autoMode(); // Mode principal qui fonctionne en boucle après demarrage (voir sketch Gestion)
            Serial.println("Mode principal qui fonctionne en boucle après démarrage(etat=2)");
            break;
   
    case 3: test_alcool();//éthylotest antidémarrage (voir sketch Qualité d'air)
          Serial.println("Activation de l'ethylotest(etat=3)");
            break;
   
  }
 delay(300); 
 if (digitalRead(BOUTON1) == LOW && digitalRead(BOUTON2) == LOW)//maintenir SW1 avant allumage pour commander avec le joystick
           Serial.println("flag joystic");
 {
   Reception();

 }
 
}
  


