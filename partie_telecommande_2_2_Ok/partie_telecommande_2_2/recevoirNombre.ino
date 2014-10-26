

byte recevoirNombre() { // fonction de reception d'un nombre sur le port série
  int Interrupt=0;// pin d'interruption
  while(1)
  {
   if (Serial.available()>0 ) // tant qu'un octet en réception
     {  
        octetRecu=Serial.read(); // Lit le 1er octet reçu et le met dans la variable

        octetRecu=octetRecu-48; // transfo valeur ASCII en valeur décimale

nombreRecu = octetRecu;
        delay(1); // pause pour laisser le temps à la fonction available de recevoir octet suivant
     }
else
{nombreRecu = 0;
delay(1000);
 //digitalWrite(Interrupt, LOW);
}
            vitesse=1;
          vitesse = vitesse << 3;
         nombreRecu = nombreRecu | vitesse;
           Serial.println("commande a envoyer_kinect: ");
          Serial.print(nombreRecu); 
  return(nombreRecu); // renvoie le nombre calculé
  
  }
} // fin fonction recevoirNombre
