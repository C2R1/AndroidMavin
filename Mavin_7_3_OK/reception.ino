//--------------Reception-------------
void Reception()
{
char RECEPT_Data;//perso
int vitesse;
Serial.println("Dans reception joystick");
  while(1)
  { Serial.println("Dans while#1");
    
      if(Serial3.available())  //si personne a discuter alors on recoit les donner
      {//check if there's any data sent from the remote bluetooth shield
        //Serial.print("RECEPT_Data");
        RECEPT_Data = Serial3.read();
        Serial.print(RECEPT_Data);
        
      }
      if(RECEPT_Data=='Z')//début programme perso
      {  
          
          while(1)
          {  
              if(Serial3.available()>0)
              {//check if there's any data sent from the remote bluetooth shield
               commandebit = Serial3.read();     
               if (commandebit != 218 && commandebit != 90)// 218=> changement de ligne avec la kinect 90=> la reception du Z
               { 
                //if (commandebit == 15)
               // Serial.println("Mode_kinect");
                commande2=commandebit;   
                //Serial.print("commandebit: ");
                //Serial.println(commandebit,BIN); 
               vitesse=commande2 >> 3;//A FAIRE PARTIE VITESSE
               //Serial.println("vitesse:");
               //Serial.println(vitesse);
                
                //joystick_mode();
                SRF05();
                
                radar_obstacle();  
                communication_moteurs();


                
              }
            }
                                                         
          }//fin while(1)
      }//fin IF
  }//fin while(1)
}
