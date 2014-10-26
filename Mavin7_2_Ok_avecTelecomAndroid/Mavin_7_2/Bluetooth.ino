/**
* Configure le slot de connexion bluetooth SeedBTSlave
*/
void setupBlueToothConnection()
{
  //Initialisation de la communication bluetooth à 38400 bauds
  Serial3.begin(38400);  
  //mode esclave  
  Serial3.print("\r\n+STWMOD=0\r\n");
  //initialisation du nom du module en : "SeeedBTSlave"  
  Serial3.print("\r\n+STNA=SeeedBTSlave\r\n"); 
  //autorisation de connexion des "paired devices" 
  Serial3.print("\r\n+STOAUT=1\r\n");
  // autoconnexion interdite  
  Serial3.print("\r\n+STAUTO=0\r\n");                   
  delay(2000);
  //rend le module bluetooth joignable  
  Serial3.print("\r\n+INQ=1\r\n");                      
  delay(2000);                                          
  Serial3.flush();
}






