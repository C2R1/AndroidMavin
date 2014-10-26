//----------------- Constantes DHT11 --------------------
 // pin
 // version du capteur
//---------------- définition de "l'objet" -----------------
DHT dht(DHTPIN, DHTTYPE);

void setupDht11(){
    dht.begin();
}

/**
* Mesure la température en degré celsius et le pourcentage
* d'humidité dans l'air.
* Utilisation d'une bibliothèqte spécifique à ce genre de 
 * capteur.
*/
void dht11(){
  //acquisition humidité
  h = dht.readHumidity();
  
  //acquisition température
  t = dht.readTemperature();  
}

void dht11Temperature(){
  Serial3.print("_TEMP"); 
  Serial3.println(t);
}

void dht11Humidite(){
  Serial3.print("_HUMI"); 
  Serial3.println(h);
}
