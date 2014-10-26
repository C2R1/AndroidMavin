/*-----------Partie télécommande version 2.1.---------------------
Ce programme est utilisé par le module uno-bluetooth-joystick afin de controler le jeu de leds,
l'hexapode ainsi que le mavin; et ce afin d'en faire une commande "universelle"
La différence avec le programmme original est la fonction recevoirnombre
ainsi que l'ajout dans le loop de la commande permettant de switch entre kinect et joystick.

La version 2.1 apporte des modifications au niveau de l'envoi de commande venant le joystick, en lui donnant plus de souplesse.
par exemple si le joystick est situé à une inclinaison de 5° par rapport au nord, la commande "avancer" fonctionnera malgré tout.
De plus, le module joystck ne devrais plus envoyer de valeurs erronnées.
Il a été testé sur le Mavin mais pas sur l'hexapode, cependant il devrait marcher quand même
*/
#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 5
#define TxD 2
 
#define DEBUG_ENABLED  1

String retSymb = "+RTINQ=";//start symble when there's any return
String slaveName = ";SeeedBTSlave";// caution that ';'must be included, and make sure the slave name is right.
int nameIndex = 0;
int addrIndex = 0;
String recvBuf;
String slaveAddr;
String connectCmd = "\r\n+CONN=";
int valide_kinect=0;
int valide_joystick=1;
SoftwareSerial blueToothSerial(RxD,TxD);
byte M = 15;
//variable pour le joystick
char pinH = 1;
char pinV = 0;
char pinB = 7;
const int pinG= 9;
int ValeurH,ValeurV,ValeurB,ValeurG;
byte vitesse, octetRecu, nombreRecu;
char commande, commande1;

const int APPUI=LOW;  //constante pour tester état BP (actif en LOW)
//variables pour l'envoi sur le port série
char nombreReception; // variable pour nombre reçu sur port Série
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  pinMode(pinB, INPUT);
  pinMode(pinG, INPUT);
  setupBlueToothConnection();
  //wait 1s and flush the serial buffer
  delay(1000);
  Serial.flush();
  blueToothSerial.flush();
} 
 
void loop() 
{
    
// blueToothSerial.print("Z");// avec l'hexapode

  while(1)
   { 
//   blueToothSerial.print("Z");// avec la mavin
   ValeurG = digitalRead(pinG);//recuperation et envoie de la valeur du bouton
   if (ValeurG == APPUI)
     {
       delay(500);

        if (valide_joystick==1)
        {valide_joystick = 0;}
        else valide_joystick =1;
        
       if ( valide_kinect==1)
        {valide_kinect = 0;}
        else valide_kinect =1;
      
     
        Serial.println ("ca passe");
        Serial.println (valide_kinect);
        Serial.println (valide_joystick);
        
    if ((valide_joystick == 0) && (valide_kinect == 1))
          Serial.println ("VALIDEkinectA1");
                  
    if ((valide_joystick == 1) && (valide_kinect == 0)) 
         Serial.println ("VALIDEjoystickA1");
           
     }
    
  
   
    if (valide_kinect == 1)  // affichage du nombre venant de la kinect et envoi
      { // si un nombre a été reçu
         
     //blueToothSerial.print(M);
    nombreReception=recevoirNombre();// Lance le programme "fonction-envoi-commande" si le bit est validé
    Serial.print("\n envoyer commande_kinect:");
    Serial.print(nombreReception,BIN);
      blueToothSerial.print(nombreReception);
      //--- affiche le nombre reçu sur le port série 
      nombreReception=0; // RAZ nombre reçu 
      }
  
    if (valide_joystick == 1)// affichage du nombre venant du joystick et envoi
       {
         Serial.println("partie_joystick");
         commande=fonction_envoi_commande(); 
        Serial.print("\n envoyer commande:");
        Serial.print(commande,BIN);
        blueToothSerial.print(commande);
        


        }        
          
  }    
} 
 

