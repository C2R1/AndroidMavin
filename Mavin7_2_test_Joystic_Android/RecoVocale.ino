// ---------------------- pin(s) ---------------------------
#define recoLedPIN 24      // pin 24

void setupEasyVR(){
port.begin(9600);
  // vÃ©rification de la prÃ©sence du matÃ©riel
  if (!easyvr.detect())
  {
    Serial3.println("EasyVR non detecte"); 
    for (;;);
  }
  Serial3.println("EasyVR detecte");
  // temps d'acquisition
  easyvr.setTimeout(5); 
  // Langage: Francais 
  easyvr.setLanguage(5);
  //active les commandes customisÃ©es

}

/**
* RÃ©cupÃ¨re un mot de commande predefinit
*/
void easyVR(){
  pinMode(recoLedPIN,OUTPUT);
  // invitation 
  /* indique qu'on travaille avec des mots prÃ©enregistrÃ©s,
     ici on utilise le WordSet 8 ( index 1)               */
  easyvr.recognizeWord(1);
  do
  {
    //Allumage d'une LED pendant l'acquisition
    digitalWrite(recoLedPIN, HIGH);
  }
  while (!easyvr.hasFinished());
  // association d'un chiffre au mot rÃ©cupÃ©rÃ©
  idx = easyvr.getWord();
  digitalWrite(recoLedPIN, LOW); 

 switch(idx){
   
   case -1:
   break;
   case 0:               // activer les moteurs avec la commande vocale "action"
   bouge=false;
   enable_av=true;
   enable_eayvr = false; // desactiver la commande vocale 
   break;
   case 1:               // mettre dans les conditionnes oÃ¹ le Robot recule et tourne aprÃ¨s la detection d' un obstacle, avec la commande vocale "bouge"
   bouge = true;
   enable_av=true;
   enable_eayvr = false;
   break;
   case 2:               // faire reculer et  tourner le robot avec la commande vocale "tourne"    
   enable_eayvr = false;
   reculer(255);
   delay(2000);
   demitour(255); 
   delay(1000);
   break;
   case 6:
   enable_av=!enable_av; // arrÃªter les moteurs avec la commande vocale "arrete"
   enable_eayvr = false;
   break;
}
  
}







    

