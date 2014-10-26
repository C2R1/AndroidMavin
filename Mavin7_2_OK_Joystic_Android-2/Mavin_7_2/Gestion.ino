
void selectMode(){
  lectureRFID();
  checkMyTags();
  
  switch(idTag){
    case 1: etat = 1;
            sendCommand(0);//jouer la piste n°0 dans la carte SD inseré dans la carte SOMO14D
            break;
    case 2: etat = 2;
            sendCommand(0);
            break;
    case 3:
            break; 
    default: break;
  }
}

void autoMode(){ 
  
 for (int sensor_time=0; sensor_time<1; sensor_time++){//Nombre des fois à executer le capteur DHT11
 if(digitalRead(BOUTON1) == LOW ){easyVR();}//activer reconnaisance vocale avec le SW1
 if (digitalRead(BOUTON2) == LOW ) {enable_av=!enable_av;}//faire avancer avec SW2 
 
  SRF05();
  boussole();
  accelerometre();
  air();
  afficheSRF05();
  afficheBoussole();
  CaptMvmt();
  sonRadar();
  dht11();
  dht11Temperature();
  dht11Humidite();

  }
  for (int time=0; time<1000; time++){ // activer 1000 fois plus souvent toutes les capteurs sauf DHT11 qui ralenti enormement le système
  if (digitalRead(BOUTON1) == LOW ){easyVR();}//activer reconnaisance vocale avec le SW1
  if (digitalRead(BOUTON2) == LOW ) {enable_av=!enable_av;}//faire avancer avec SW2
  SRF05();
  boussole();
  accelerometre();
  air();
  afficheSRF05();
  afficheBoussole();
  CaptMvmt();
  sonRadar();
  communication_moteurs();
  }
}


void joystic(){

  if (digitalRead(BOUTON2)== LOW)//mantenir SW2 pour basculer sur l'éthylotest
 {
   etat=0;
 }
  
  if (Serial3.available() > 0) {
  RECEPT_Data = Serial3.read();
  Serial.println(RECEPT_Data);
   }   

   switch(RECEPT_Data){
      case 'A': 
              {      
              enable_av=true;
              avancer(255);// avance
              }
              break;
      case 'R':     
              { 
               enable_av=false;
               reculer(250);// recule
              }
              break;
      case '0': 
              {      
              sarreter();// arrete     
              }
              break;
      case 'D': 
              {
                droite(150);// droite
              }
              break;
      case 'G': 
              {
              gauche(150);// gauche
              }
              break;     
      default: break;
    }
    sonRadar();  
   delay(10);  
  }
  


