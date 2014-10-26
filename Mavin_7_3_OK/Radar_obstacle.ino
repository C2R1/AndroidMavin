//--------------Radar_obstacle-----------------------
 void radar_obstacle()
 {
 
  if(distance<20 && bouge ==false){      // si la distance par rapport à un obstacle est inferieur à 20 cm
  validation = 0;
      sarreter();                                   //arreter 
      digitalWrite(buzzpin, HIGH);
      delay(1000);//sonner pendant 2 sec            //activer buzzer pendant 2 secondes  
      digitalWrite(buzzpin, LOW);                   //arreter buzzer apres  secondes
      Serial.println("TROP PRET");
  }
  else validation = 1;
 
 }
