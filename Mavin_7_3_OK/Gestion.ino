//--------------Gestion--------------
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
  Serial.println("automode");
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

}
 
}

void joystick_mode()
{
  
 for (int sensor_time=0; sensor_time<1; sensor_time++){//Nombre des fois à executer le capteur DHT11

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
}

