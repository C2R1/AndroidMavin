int buzzpin = 50;
long d;
int flag=1; //utilisÃ© comme marquer
long previousMillis = 0;
int state=LOW;


void setupBuzz (){
pinMode(buzzpin, OUTPUT);
}


void tempo(long interval,void a()) //fonction temporisation utilisant la fonction millis();
{
  unsigned long currentMillis = millis(); //currentMillis = temps en cours
 if(currentMillis - previousMillis > interval) { 
        previousMillis = currentMillis;  
if (state == LOW)
      state = HIGH;
    else
      state = LOW;
     a();
  }
}

void sonRadar(){                    //fonction pour faire sonner le buzzer, controler la "vitesse avancer" par rapport un obstacle et s'arreter avant un obstacle
d=(distance*100)/20;                //variable d en fonction de la distance par rapport Ã  un obstacle, utilisÃ© pour faire varier la tempo du buzzer


if (distance>60){                   //si distance par rapport Ã  un obstacle est superieur Ã  60 cm
 flag=1;
 avancer(255);                      //avancer vitesse max
digitalWrite(buzzpin, LOW);         //desactiver buzzer

}
 
  if(distance<20 && flag==1 && bouge ==false){      // si la distance par rapport Ã  un obstacle est inferieur Ã  20 cm
 
      flag=0;
      sarreter();                                   //arreter 
      digitalWrite(buzzpin, HIGH);
      delay(2000);//sonner pendant 2 sec            //activer buzzer pendant 2 secondes  
      digitalWrite(buzzpin, LOW);                   //arreter buzzer apres  secondes
  }
 
 
 
  if(distance<20 && flag==1 && bouge ==true){     // si la distance par rapport Ã  un obstacle est inferieur Ã  20 cm avec la commande vocale bouge
    
     
 
      flag=0;                                     //marqueur utilisÃ© pour rentre qu' une fois lorsque cette condition est vraie
      sarreter();          
      digitalWrite(buzzpin, HIGH);             
      delay(2000);                                //sonner pendant 2 sec
      digitalWrite(buzzpin, LOW); 
      int enable_rec=0;                           //reculer Ã  vitesse max pendant 1 seconde
      while(enable_rec<1){
      reculer(255);                               //reculer Ã  100%
      delay(1000);                                //reculer Ã  100% pendant 1 sec
      enable_rec++;
      }
      int enable_demi=0;
      while(enable_demi<1){
      demitour(127);                              //tourner Ã  environ 50% pendant 1 sec  
      delay(1000);
     enable_demi++;
     }

 }

  if (distance<=60 && distance>=40 ){             //si la distance par rapport Ã  un obstacle âˆˆ [40;60] cm
     
    flag=1;
    avancer(127);                                 //avancer Ã  environ 50%
    tempo(d,buzzpiner);                           //activer le buzz Ã  une frequence proportionelle Ã  la distance par rapport Ã  un obstacle
  }
  

  if (distance<40 && distance>=20 ){               //si la distance par rapport Ã  un obstacle âˆˆ ]40;20] cm
   
    flag=1;
    avancer(63);                                   //avancer Ã  environ 25%
    tempo(d, buzzpiner);                           //activer le buzz Ã  une frequence proportionelle Ã  la distance par rapport Ã  un obstacle
  }

}  

void buzzpiner(){                                  // fonction qui active le buzz, utilisÃ© dans la fonction tempo.
  
  if(enable_av==true){
  digitalWrite(buzzpin, state);
  }


} 




