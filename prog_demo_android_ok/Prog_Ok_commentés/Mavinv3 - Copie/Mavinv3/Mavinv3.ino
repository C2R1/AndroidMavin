/** 
* Mavin version 2
* Arduino 1.0
* 31/05/2012
* Auteur: Guillemot L.-M.
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
// ------------------------- Variables boussole ------------------------
int dernAngle;
int angle;
// -------------------------- Variables SRF05 --------------------------
int dernDistance;
int distance;
int distLimit = 5;
// ------------------------- Variables RFID ----------------------------
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
int8_t idx, group;
//Commandes customisées
enum Groups
{
  GROUP_1  = 1,
};

enum Group1 
{
  G1_DEMARRAGE = 0,
  G1_BOUSSOLE = 1,
  G1_TEMPERATURE = 2,
  G1_HUMIDITE = 3,
  G1_POLLUTION = 4,
  G1_DISTANCE = 5,
  G1_INCLINAISON = 6,
  G1_PROFIL = 7,
  G1_ARRET = 8,
};
// ---------------------------- Variables DHT11 ------------------------
int qPin = 8;
float q, h, t;
//----------------------- Pin pour SOMO14D -----------------------------
const int clockPin = 2;  
const int dataPin = 3;  
const int resetPin = 4;  
// ----------------------Registres pour SOMO14D ------------------------
const unsigned int VOLUME_5 = 0xFFF5;
unsigned int sonDemarrage = 0;
const unsigned int STOP = 0xFFFF;
//----------------------------- automate -------------------------------
int etat;
boolean commande = false;





void setup(){
  //---------------------- Initialision  bus I²C -----------------------
  Wire.begin();
  //--------------------- Initialisation port PC -----------------------
  Serial.begin(9600);
  //--------------------- Initialisation RFID --------------------------
  Serial2.begin(9600); 
  // ----------------------Initialisation bluetooth --------------------
  Serial3.begin(38400);
  setupBlueToothConnection();
  //--------------------- Initialision des capteurs --------------------
  setupSRF05();
  setupAccelerometre();
  setupSomo14D();
  setupDht11();
  setupCaptMvmt();
  setupEasyVR();
  //----------------------- Initialision de l'état ---------------------
  etat = 0;
  delay(2000);
}

void loop(){
  switch(etat){
    case 0: selectMode();
            break;
    case 1: manualMode();
            break;
    case 2: autoMode();
            break;
    default: break;
  }
  delay(1000);  
}
  


