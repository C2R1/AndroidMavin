/**
* Mesure la pollution de l'air.
* Est sensible Ã  l'alcool, au C02, Ã  l'Ã©thanol etc ...
*/
void air(){
  //lecture et conversion de la valeur
  q = ( analogRead(qPin)/1024 )*100;          
  Serial3.print("_QAIR");
  Serial3.println(q);
}

