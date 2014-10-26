//--------------Communication_moteurs---------------
void communication_moteurs()
{
 // essayer avec des boucles while
 if(validation==1)
 {
switch(commande2)
{
    case(8): sarreter();// s'arrête
        break;

    case(9):
    {
      enable_av=true;
      avancer(255);// avance
    }
        break;

    case(12):
    { 
     enable_av=false;
     reculer(255);// recule
    }
        break;

    case(11):gauche(180);// va a gauche
        break;

    case(10): droite(180);// va a droite
        break;
        
    case(13):tournedroite(255);
        break;
        
    case(14):tournegauche(255);
         break;
  }
}
} 

 
