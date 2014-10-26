

/**
* Mesure la valeur de la différence entre le cap pré - enregistré dans le
* CMPS03 et le cap actuel.
*/
void boussole(){
   byte highByte;
   byte lowByte;

   //initialisation de la communication avec le CMPS03
   Wire.beginTransmission(sensorAddress);
   //utilisation du registre 2 pour une "grande" précision  
   Wire.write(REGISTER); 
   //on a finit l'initialisation de la com avec le CMPS03 via i²c  
   Wire.endTransmission();                 
 
   //demande des octets présents sur le registre 2
   Wire.requestFrom(sensorAddress, REGISTER);           
   
   //tant qu'il n'y pas les 2 octets à  lire on attend.
   while(Wire.available() < 2);            
   /* La fonction read() lit les octets du buffer dans l'ordre, elle decale 
      automatiquement son pointeur sur l'octet suivant                   */
        
   highByte = Wire.read();       //lecture de l'octet de poids fort
   lowByte = Wire.read();        //lecture de l'octet de poids faible
   
   // 0 < ( highByte lowByte ) < 3599
   angle = ((highByte << 8)+lowByte)/10; 			               
}

void afficheBoussole(){
  Serial3.print("_ANGL");
  Serial3.println(angle);
  
}
