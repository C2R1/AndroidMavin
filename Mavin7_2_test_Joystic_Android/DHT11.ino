//----------------- Constantes DHT11 --------------------
 // pin
 // version du capteur
//---------------- dÃ©finition de "l'objet" -----------------
DHT dht(DHTPIN, DHTTYPE);

void setupDht11(){
    dht.begin();
}

/**
* Mesure la tempÃ©rature en degrÃ© celsius et le pourcentage
* d'humiditÃ© dans l'air.
* Utilisation d'une bibliothÃ¨qte spÃ©cifique Ã  ce genre de 
 * capteur.
*/
void dht11(){
  //acquisition humiditÃ©
  h = dht.readHumidity();
  
  //acquisition tempÃ©rature
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

