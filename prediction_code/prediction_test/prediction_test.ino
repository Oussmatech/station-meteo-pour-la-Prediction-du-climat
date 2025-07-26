#include "model_rain_xgboost.h"  
#include "decision_tree_model_fire.h"  
#include "model_fog_xgboost.h"  // Inclure le fichier du modèle généré par micromlgen
#include "DHT.h"  

DHT dht(4, DHT11);  // Initialisation du capteur 
const int LUMINOSITY_PIN = 35;  // Broche numérique connectée à OUT
const int mq9Pin = 34;  // GPIO de l'ESP32 connectée à A0 du MQ-9

Eloquent::ML::Port::ModelRain classifier_rain;
Eloquent::ML::Port::ModelFog classifier_fog;
Eloquent::ML::Port::ModelFire classifier_fire;

int readLuminosity() {
  return analogRead(LUMINOSITY_PIN);  // 0 (sombre) - 4095 (lumineux)
}
void setup() {
  Serial.begin(9600);
  dht.begin();
  while (!Serial) ;  // Attendre la connexion série
}

void loop() {
  //delay(1000);
  Serial.println("Prediction avec l'Arbre de Decision pour la Classification Météo");
  float humidity = 42.2;        
  float temperature = 12.4;  
  //float light = Serial.parseFloat(); // Lire l'entrée comme un nombre flottant
  float vent =88.417229463067 ;
  int luminosity = 300;
  int co = 10.16;
  int co2 = 661; // valeur brute 0-4095 sur ESP32

  if (isnan(humidity) || isnan(temperature)) { 
    Serial.println("Erreur de lecture du DHT11 !"); 
    return ; } 
  if (isnan(luminosity)) { 
    Serial.println("Erreur de lecture du LDR !"); 
    return ; } 
  if (isnan(co)) { 
    Serial.println("Erreur de lecture du MQ9 !"); 
    return ; } 
  Serial.print("Humidité : "); Serial.print(humidity); Serial.print(" %\t"); 
  Serial.print("Température : "); Serial.print(temperature); Serial.println(" °C"); 
  Serial.print("Intensite lumineuse : ");Serial.println(luminosity);Serial.println("lux "); 
  Serial.print("vitesse_du_vent : "); Serial.print(vent); Serial.println("km/h"); 
  Serial.print("co : ");Serial.print(co);Serial.println("ppm "); 

  
  delay(2000); 
  
  // Préparer l'échantillon pour la classification
  float x_rain[] = { temperature , humidity, luminosity };
  float x_fog[] = { temperature , humidity, luminosity , vent };
  float x_fire[] = { temperature, humidity, luminosity , co ,co2};

  // Prédire la classe (Pluvieux ou Non Pluvieux) avec le classifieur entraîné
  int prediction_rain = classifier_rain.predict(x_rain);  // La prédiction retourne la classe prédite (0 ou 1)
  int prediction_fog = classifier_fog.predict(x_fog);
  int prediction_fire = classifier_fire.predict(x_fire);


  // Afficher la classe prédite
  Serial.print("Classe predite : ");
  if (prediction_rain == 1) Serial.println("Pluvieux");
  else Serial.println("Non Pluvieux");
  if (prediction_fog == 1) Serial.println("brouillar");
  else Serial.println("Non brouillar");
  if (prediction_fire == 1) Serial.println("fire");
  else Serial.println("Non fire");
  
}
