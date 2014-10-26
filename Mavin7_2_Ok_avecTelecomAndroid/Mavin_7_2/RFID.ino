/**
* Comparaison de 2 TAGS
*/
boolean compareTag(int tagA[14], int tagB[14])
{
  boolean validation = false;
  int bitIdentiques = 0;
  for (int i=0; i<14; i++){
    if (tagA[i] == tagB[i])
      bitIdentiques++;
  }
  if (bitIdentiques == 14)
    validation=true;
  return validation;
}

void checkMyTags()
{
  idTag = 0; 
  if (compareTag(newTag,yellowTag)==true)
    idTag = 1; 
  if (compareTag(newTag,blueTag)==true)
    idTag = 2;
  if (compareTag(newTag,redTag)==true)
    idTag = 3;  
}

void lectureRFID(){
  Serial2.flush();
  //Attente tant qu'aucune valeur n'est détectée sur le Serial2
  delay(10);
  while(Serial2.available() == 0){
  }
  /*Delai de 100 ms pour laisser le temps au buffer de renvoyer ses*
   *valeurs   */
  delay(100);
  //Lecture de chacun des bits.  (14 bits en tout)
  for (int i=0; i<14; i++) 
  {
    data=Serial2.read();
    newTag[i]=data;
  }
  // stop les multiples reads
  Serial2.flush(); 
}
