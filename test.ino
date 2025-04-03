#include "model.h"  // Inclure le fichier du modèle généré par micromlgen

Eloquent::ML::Port::DecisionTree classifier;  // Ajustez ceci en fonction du type de modèle dans model.h

void setup() {
  Serial.begin(9600);
  while (!Serial) ;  // Attendre la connexion série
}

void loop() {
  Serial.println("Prediction avec l'Arbre de Decision pour la Classification Météo");

  // Demande à l'utilisateur d'entrer la température via le moniteur série
  Serial.println("Entrez la temperature (°C) : ");
  while (!Serial.available()) {
    // Attendre l'entrée utilisateur
  }
  float temperature = Serial.parseFloat(); // Lire l'entrée comme un nombre flottant
  Serial.print("Temperature : ");
  Serial.println(temperature);

  // Demande à l'utilisateur d'entrer l'humidité via le moniteur série
  Serial.println("Entrez l'humidite (%) : ");
  while (!Serial.available()) {
    // Attendre l'entrée utilisateur
  }
  float humidity = Serial.parseFloat(); // Lire l'entrée comme un nombre flottant
  Serial.print("Humidite : ");
  Serial.println(humidity);

  // Demande à l'utilisateur d'entrer l'intensité lumineuse via le moniteur série
  Serial.println("Entrez l'intensite lumineuse (LDR) : ");
  while (!Serial.available()) {
    // Attendre l'entrée utilisateur
  }
  float light = Serial.parseFloat(); // Lire l'entrée comme un nombre flottant
  Serial.print("Intensite lumineuse : ");
  Serial.println(light);

  // Préparer l'échantillon pour la classification
  float x_sample[] = {temperature, humidity, light};

  // Prédire la classe (Pluvieux ou Non Pluvieux) avec le classifieur entraîné
  int prediction = classifier.predict(x_sample);  // La prédiction retourne la classe prédite (0 ou 1)

  // Afficher la classe prédite
  Serial.print("Classe predite : ");
  if (prediction == 1) Serial.println("Pluvieux");
  else Serial.println("Non Pluvieux");
  
}
