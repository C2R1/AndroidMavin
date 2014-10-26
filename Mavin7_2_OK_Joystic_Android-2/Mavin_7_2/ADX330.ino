void setupAccelerometre(){
  pinMode(X,INPUT);
  pinMode(Y,INPUT);
  pinMode(Z,INPUT);
}

/**
* Mesure l'acclération sur les 3 axes X,Y,Z
* Au repos et à "plat" le capteur subit 1G
* sur son axe Z- ( -1G sur Z+)
* Lit les valeurs sur les entrées X,Y et Z
* zero G :
*         axe X : 310; 
*         axe Y : 310; 
*         axe Z : 320; 
*/
void accelerometre(){
  Serial3.print("_ACCX");
  Serial3.print(analogRead(X));   //envoyer la valeur de X par bluetooth à la tablette Android
  Serial3.print("_ACCY");
  Serial3.print(analogRead(Y));   //envoyer la valeur de Y par bluetooth à la tablette Android
  Serial3.print("_ACCZ");
  Serial3.println(analogRead(Z)); //envoyer la valeur de Z par bluetooth à la tablette Android

}
