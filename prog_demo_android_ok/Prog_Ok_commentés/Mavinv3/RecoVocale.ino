// ---------------------- pin(s) ---------------------------
#define recoLedPIN 24      // pin 24

void setupEasyVR(){
port.begin(9600);
  // vérification de la présence du matériel
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
  //active les commandes customisées
 group = GROUP_1; 
}

/**
* Récupère un mot de commande predefinit
*/
void easyVR(){
  pinMode(recoLedPIN,OUTPUT);
  // invitation 
  /* indique qu'on travaille avec des mots préenregistrés,
     ici on utilise le WordSet 8 ( index 1)               */
  easyvr.recognizeWord(1);
  do
  {
    //Allumage d'une LED pendant l'acquisition
    digitalWrite(recoLedPIN, HIGH);
  }
  while (!easyvr.hasFinished());
  // association d'un chiffre au mot récupéré
  idx = easyvr.getWord();
  digitalWrite(recoLedPIN, LOW); 
}

/**
* Récupère un mot de commande customisé
*/
void customEasyVR(){
  pinMode(recoLedPIN,OUTPUT);
  // invitation 
  /* indique qu'on travaille avec des mots customisés,
     ici on utilise le Group_1 ( index 1)               */
  easyvr.recognizeCommand(group);
  do
  {
    //Allumage d'une LED pendant l'acquisition
    digitalWrite(recoLedPIN, HIGH);
  }
  while (!easyvr.hasFinished());
  // association d'un chiffre au mot récupéré
  idx = easyvr.getCommand();
  digitalWrite(recoLedPIN, LOW); 
}


    
