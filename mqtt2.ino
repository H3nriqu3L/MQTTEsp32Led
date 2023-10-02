#include <WiFi.h>
#include <PubSubClient.h>
#include <M5Atom.h>

const char* ssid = "Henrique";
const char* password = "";

const char* mqtt_server = "broker.mqtt.cool";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensagem recebida no tópico: ");
  Serial.println(topic);
  Serial.print("Conteúdo da mensagem: ");
  
  // Converte o payload em uma string
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Processa a mensagem recebida e atualiza o display
  if (message == "red") {
    CRGB corVermelha(255, 0, 0); // Vermelho
    M5.dis.fillpix(corVermelha);
  } else if (message == "blue") {
    CRGB corAzul(0, 0, 255); // Azul
    M5.dis.fillpix(corAzul);
  } else if (message == "yellow") {
    CRGB corAmarela(255, 255, 0); // Amarelo
    M5.dis.fillpix(corAmarela);
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }

  Serial.println("Conectado à rede Wi-Fi");

  client.setServer(mqtt_server, mqtt_port);

  while (!client.connected()) {
    Serial.println("Conectando ao servidor MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
  
}


void loop() {
  // Lógica do loop, como publicar e assinar tópicos MQTT
  client.loop();
}
