void selectMode(){
  lectureRFID();
  checkMyTags();
  
  switch(idTag){
    case 1: etat = 1;
            sendCommand(0);
            break;
    case 2: etat = 2;
            sendCommand(0);
            break;
    case 3:
            break; 
    default: break;
  }
}
  
void manualMode(){
  while(digitalRead(BOUTON2) == HIGH){
    if(commande){
      actionCommand();
      delay(1000);
    }
  }
  customEasyVR();
  Serial3.println(idx);
  actionCommand();  
}

void autoMode(){
  if(digitalRead(BOUTON2) == LOW)
    etat = 0;
  SRF05();
  boussole();
  accelerometre();
  air();
  dht11();
  dht11Temperature();
  dht11Humidite();
  afficheSRF05();
  afficheBoussole();
  CaptMvmt();
}

void actionCommand(){
  commande = true;
  switch(idx){
    case 0: sendCommand(0);
            break;
    case 1: boussole();
            afficheBoussole();
            break;
    case 2: dht11();
            dht11Temperature();
            break;
    case 3: dht11();
            dht11Humidite();
            break;
    case 4: air();
            break;
    case 5: SRF05();
            afficheSRF05();
            break;
    case 6: accelerometre();
            break;
    case 7: sendCommand(3);
            break;
    case 8: commande = false;
            etat = 0;
            break;
    default: 
            break;
  }
}
