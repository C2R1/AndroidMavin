/**
* Mesure la pollution de l'air.
* Est sensible Ã  l'alcool, au C02, Ã  l'Ã©thanol etc ...
*/
#define ledPIN 22
float variation;
float test[1];//tableau test à 2 valeurs
boolean test_positif=false;


void air(){                         // fonct qui envoi la valeur de la qualité d'air en permanence à la tablette Android par bluetooth (Serial3)
                               
  q = analogRead(A8);               // plus q est élevé, plus la qualité d'air est mauvaise
  
   Serial3.print("_QAIR");
   Serial3.println(q);              // envoyer la valeur q par bluetooth à la tablette Android
   
}

void test_alcool(){                   //éthylotest antidémarrage

  //"souflez sur le capteur" 
  test[0] = analogRead(A8);           //capter la qualité d'air avant de souffler dans le capteur
  digitalWrite(ledPIN, HIGH);
  delay(3000);
  test[1] = analogRead(A8);           //capter la qualité d'air 3s après 
  digitalWrite(ledPIN, LOW);
  variation = abs(test[0]-test[1]);   //variation égale à  valeur absolue de la difference de 2 tests



if(variation >= 6 && variation<=30 && test_positif==false){
   //"vous avez souflez test negatif"
  
 sendCommand(2);                    //jouer la piste n°2 de la carte SD inseré dans la carte son SOMO14D
 etat=0;


}
if(variation >30) {
   //"vous avez souflez, test possitif, imposible de demarrer"
   test_positif=true;
   sendCommand(3);                    //jouer la piste n°0 de la carte SD inseré dans la carte son SOMO14D

}

}




