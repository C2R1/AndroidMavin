/**
* Mesure la pollution de l'air.
* Est sensible Ãƒ  l'alcool, au C02, Ãƒ  l'ÃƒÂ©thanol etc ...
*/
#define ledPIN 22
float variation;
float test[1];//tableau test Ã  2 valeurs



void air(){                         // fonct qui envoi la valeur de la qualitÃ© d'air en permanence Ã  la tablette Android par bluetooth (Serial3)
                               
  q = analogRead(A8);               // plus q est Ã©levÃ©, plus la qualitÃ© d'air est mauvaise
  
   Serial3.print("_QAIR");
   Serial3.println(q);              // envoyer la valeur q par bluetooth Ã  la tablette Android
   Serial.println("qualite: ");   
   Serial.println(q);   
   Serial.println("q");  
}

void test_alcool(){                   //Ã©thylotest antidÃ©marrage

  if (digitalRead(BOUTON1) == LOW)//mantenir SW1 pour basculer en mode joystic
   {
    etat=0;
   }

  //"souflez sur le capteur" 
  test[0] = analogRead(A8);           //capter la qualitÃ© d'air avant de souffler dans le capteur
  digitalWrite(ledPIN, HIGH);
  Serial.print("q1=");
  Serial.print(test[0]);
  delay(300);
  digitalWrite(ledPIN, LOW);
  delay(3000);
  test[1] = analogRead(A8);           //capter la qualitÃ© d'air 3s aprÃ¨s 
  digitalWrite(ledPIN, HIGH);
  Serial.print(" q2=");
  Serial.println(test[1]);
  variation = abs(test[0]-test[1]);   //variation Ã©gale Ã   valeur absolue de la difference de 2 tests

Serial.print("variation ");
Serial.println(variation);

if(variation >= 40 && variation<=150){
   if (test_positif==false)
   {                   
   //"vous avez souflez test negatif"
   sendCommand(2);                    //jouer la piste nÂ°2 de la carte SD inserÃ© dans la carte son SOMO14D
   Serial.println("Alcotest_negatif");
   etat=0; 
   }
}
if(variation >300) {
   //"vous avez souflez, test possitif, imposible de demarrer"
   sendCommand(3);                    //jouer la piste nÂ°0 de la carte SD inserÃ© dans la carte son SOMO14D
   // dÃ©mmarage impossible
   test_positif=true;
   Serial.println("Alcotest_positif");
}

}





