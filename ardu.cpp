#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClientSecure.h> // Inclure la bibliothèque pour le support HTTPS

const char* ssid = "Nom_de_votre_réseau";
const char* password = "Mot_de_passe_de_votre_réseau";
const char* serverUrl = "https://adresse_IP_de_votre_application_flutter:port/notification";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("WiFi connecté");
  Serial.println("Adresse IP: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  WiFiClientSecure client; // Créer une instance de WiFiClientSecure
  HTTPClient http;
  
  client.setInsecure(); // Utilisez cette option si vous utilisez un certificat auto-signé
  // Si vous avez un certificat racine à vérifier, utilisez client.setCACert(rootCACertificate);

  http.begin(client, serverUrl); // Commencez la connexion sécurisée
  http.addHeader("Content-Type", "application/json");
  String message = "{\"message\":\"Votre message de notification ici\"}";
  int httpResponseCode = http.POST(message);
  Serial.println(httpResponseCode);
  http.end();
  
  delay(5000); // Attendre 5 secondes avant d'envoyer la prochaine notification
}