#include "model_rain_DecisionTree.h"  
#include "model_fire_DecisionTree.h"  
#include "model_fog_DecisionTree.h"  
#include "DHT.h" 
 
//#include <WiFi.h>

DHT dht(4, DHT11);  
#define LUMINOSITY_PIN 35
#define MQ9_PIN 34  
#define buzzer_pin 32
#define led_vert1 36
#define led_rouge1 14
#define led_vert2 3
#define led_rouge2 4
#define led_vert3 6
#define led_rouge3 7
#define SEED_PIN A0

const float RL = 10.0;       // Load resistance en kilo-ohms
const float RO_CLEAN_AIR_FACTOR = 9.6;  // RO/RS ratio dans l'air propre
float Ro = 10.0;  // RO sera calibré dans setup()

int readLuminosity() {
 return analogRead(LUMINOSITY_PIN);  // 0(sombre) - 4095 (lumineux)
 }
float readSensor() {
  int analogValue = analogRead(MQ9_PIN);
  float voltage = analogValue * 3.3 / 4095.0;
  float rs = (3.3 - voltage) * RL / voltage;
  return rs; }
float calibrateSensor() {// Calibration dans l'air propre
  float rs_sum = 0.0;
  for (int i = 0; i < 50; i++) {
    rs_sum += readSensor();
    delay(100);}
  float rs_avg = rs_sum / 50.0;
  return rs_avg / RO_CLEAN_AIR_FACTOR; }

Eloquent::ML::Port::DT_Rain classifier_rain;
Eloquent::ML::Port::DT_fog classifier_fog;
Eloquent::ML::Port::DT_Fire classifier_fire;

void setup() {
  Serial.begin(9600);
  pinMode(buzzer_pin,OUTPUT);
  dht.begin();
  Serial.println("Calibration du MQ-9...");
  Ro = calibrateSensor();
  Serial.print("RO calibré = ");
  Serial.println(Ro);
  while (!Serial) ;  // Attendre la connexion série
  }

void loop() {
  //delay(1000);
  Serial.println("Prediction Météo");
  float humidity = dht.readHumidity();        
  float temperature = dht.readTemperature();  
  unsigned float vent = analogRead(SEED_PIN);
  randomSeed(vent);
  Serial.print("vent en km/h :");
  Serial.println(vent);
  float randValue = random(0, 100);
  Serial.print("Valeur aléatoire : ");
  Serial.println(randValue);
  int luminosity = readLuminosity();
  float rs = readSensor();  // Lecture de RS
  float ratio = rs / Ro;
  float ppm = 100 * pow(ratio, -1.5);  // Formule empirique

  if (isnan(humidity) || isnan(temperature)) { 
    Serial.println("Erreur de lecture du DHT11 !"); 
    return ; } 
  if (isnan(luminosity)) { 
    Serial.println("Erreur de lecture du LDR !"); 
    return ; } 
  if (isnan(ppm)) { 
    Serial.println("Erreur de lecture du MQ9 !"); 
    return ; } 
  Serial.print("Humidité : "); Serial.print(humidity); Serial.print(" %\t"); 
  Serial.print("Température : "); Serial.print(temperature); Serial.println(" °C"); 
  Serial.print("Intensite lumineuse : ");Serial.println(luminosity);Serial.println("lux "); 
  Serial.print("vitesse_du_vent : "); Serial.print(vent); Serial.println("km/h"); 
  Serial.print(" | CO approximatif = ");Serial.print(ppm);Serial.println(" ppm"); 

  
  delay(2000); 
    
  // Préparer l'échantillon pour la classification
  float x_rain[] = { temperature , humidity, luminosity };
  float x_fog[] = { temperature , humidity, luminosity , vent };
  float x_fire[] = { temperature, humidity, luminosity , ppm };

  // Prédire la classe (Pluvieux ou Non Pluvieux) avec le classifieur entraîné
  int prediction_rain = classifier_rain.predict(x_rain);  // La prédiction retourne la classe prédite (0 ou 1)
  int prediction_fog = classifier_fog.predict(x_fog);
  int prediction_fire = classifier_fire.predict(x_fire);

  digitalWrite(led_rouge,LOw); delay(1000);
    digitalWrite(led_vert,LOW);

  // Afficher la classe prédite
  Serial.print("Classe predite : ");

  if ((prediction_rain == 1)|| (prediction_fog == 1) || (prediction_fire == 1) ) 
    tone(buzzer_pin,1000);
  else 
    noTone(buzzer_pin);

  if (prediction_rain == 1) {
    Serial.println("Pluvieux");
    tone(buzzer_pin,1000);
    digitalWrite(led_rouge1,HIGH);
    digitalWrite(led_vert1,LOw); 
    }
  else {
    Serial.println ("Non Pluvieux");
    digitalWrite(led_rouge1,LOW);
    digitalWrite(led_vert1,HIGH); 
    noTone(buzzer_pin);
    }

  if (prediction_fog == 1) {
    Serial.println("brouillar");
    digitalWrite(led_rouge2,HIGH); 
    digitalWrite(led_vert2,LOW);
    }
  else {
    Serial.println("Non brouillar");
    digitalWrite(led_rouge2,LOW); 
    digitalWrite(led_vert2,HIGH); 
    }

  if (prediction_fire == 1) {
    Serial.println("fire");
    digitalWrite(led_rouge3,HIGH);
    digitalWrite(led_vert3,LOW); 
    }

  else {
    Serial.println("Non fire");
    digitalWrite(led_rouge3,LOW); 
    digitalWrite(led_vert3,HIGH); 
    }
}

