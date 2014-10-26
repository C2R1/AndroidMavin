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
   Serial.println("qualité: ");   
   Serial.println(q);   
   Serial.println("q");  
}

void test_alcool(){                   //éthylotest antidémarrage

  if (digitalRead(BOUTON1) == LOW)//mantenir SW1 pour basculer en mode joystic
   {
    etat=0;
   }

  //"souflez sur le capteur" 
  test[0] = analogRead(A8);           //capter la qualité d'air avant de souffler dans le capteur
  digitalWrite(ledPIN, HIGH);
  delay(3000);
  test[1] = analogRead(A8);           //capter la qualité d'air 3s après 
  digitalWrite(ledPIN, LOW);
  variation = abs(test[0]-test[1]);   //variation égale à  valeur absolue de la difference de 2 tests

Serial.println("variation");
Serial.println(variation);

if(variation >= 10 && variation<=150){
   //"vous avez souflez test negatif"
   if (test_positif==false)
   {
   sendCommand(2);                    //jouer la piste n°2 de la carte SD inseré dans la carte son SOMO14D
   etat=3;                            // démmarage possible
   test_positif==true;
   }
}
if(variation >200) {
   //"vous avez souflez, test possitif, imposible de demarrer"
   sendCommand(3);                    //jouer la piste n°0 de la carte SD inseré dans la carte son SOMO14D
   etat=1;
   test_positif==true;
}

}




