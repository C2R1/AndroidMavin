byte fonction_envoi_commande(void)
{ 
        //récupération et envoie de la valeur du stick analogique Horizontale
        ValeurH = analogRead(pinH);
         int Interrupt=0;// pin d'interruption
        //récupération et envoie de la valeur du stick analogique Verticale
        ValeurV = analogRead(pinV);
        //récupération et envoie de la valeur du bouton
        ValeurB = digitalRead(pinB);
 
        //envoie de la donnée
        vitesse=0;
        if((ValeurV > 698) && (ValeurV <1023) && (ValeurH > 0) && (ValeurH <354))
        commande1='g';//gauche une roue
       
       if((ValeurV > 698) && (ValeurV <1023) && (ValeurH > 670) && (ValeurH <1023))
       commande1 = 'd';// droite une roue
        if((ValeurV < 504) && (ValeurH > 430) && (ValeurH < 580))
        {
         
          vitesse = (505-(504 - ValeurV))/17;
          commande1='R'; // recule
        }
       
        
        if((ValeurH < 512) && (ValeurV > 460) && (ValeurV < 700))
        {
          vitesse = (512-(511 - ValeurH))/17;
          commande1='G'; //à gauche
        }
 
         
        if((ValeurH > 513) && (ValeurV > 503) && (ValeurV < 698))
        {
          vitesse = ((ValeurH-1024)/16)*(-1); //rend une valeur comprise entre 31 et 1/0
          commande1='D'; //à droite
        }
         
        if((ValeurV > 505) && (ValeurH > 354) && (ValeurH < 670))
        {
          vitesse = ((ValeurV-1024)/17)*(-1); //rend une valeur comprise entre 31 et 1/0
          commande1='A'; // avance
        }
        
        if ((ValeurV >480) && (ValeurV < 541) && (ValeurH >480) && (ValeurH<550))
        {commande1 ='0';//probleme de fiabilité du joystick
        vitesse = 1;
        }
        
        //gère l'affichage du moniteur série
//        Serial.print("commande1: ");
//        Serial.println(commande1,BIN);
//        Serial.print("vitesse: ");
//        Serial.println(vitesse,BIN);
//        Serial.print("valeurH");
//        Serial.println(ValeurH);
//        Serial.print("valeurV");
//        Serial.println(ValeurV);
//        Serial.print("valeurB");
//        Serial.println(ValeurB);
//        if(ValeurB == 0)
//        {
//          commande1 =255;
//        }
//        else
//        {
//          if(vitesse==0)
//            vitesse=1;
//          vitesse = vitesse << 3;
//          commande1 = commande1 | vitesse; 
//        } 
//          Serial.print("commande a envoyer: ");
          Serial.print(commande1); 
   return commande1;     
}
