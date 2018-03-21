#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
/* Configuração da rede*/
const char *ssid = "LAR-ECT";
const char *password = "larfacil1234";

IPAddress ip(192, 168, 0, 20);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<html><head><meta charset='UTF-8'><title>Controle de entrad laboratório</title><script>var matricula = prompt('Por favor digite sua senha:');window.location.href = '/abrir?matricula='+matricula;</script></head></html>");
}
void handleAbrir(){
  if(server.hasArg("matricula")) {
    bool contem = false;
    String matricula = server.arg("matricula");
    if(matricula==0){
      server.send(200, "text/html", "<html><head><meta charset='UTF-8'><title>Controle de entrad laboratório</title></head><body><center><h1 style='font-size:30px;color:red'>Porta Fechada</h1></center></html>");
    }else{
      for(int i=0;i<n;i++){
        if(matriculaBanco[i]==matricula){
          contem = true;
          break;
        }
      }
      if(contem){
        digitalWrite(13, 1);
        server.send(200, "text/html", "<html><head><meta charset='UTF-8'><title>Controle de entrad laboratório</title><link rel='icon' href='https://s-media-cache-ak0.pinimg.com/originals/8c/7a/32/8c7a32ff6742b510990c45e265c6512d.png'></head><body><center><h1 style='font-size:30px;color:green'>Porta Aberta</h1></center></html>");
        delay(5000);
        digitalWrite(13, 0);
        
      }else{
        server.send(200, "text/html", "<html><head><meta charset='UTF-8'><title>Controle de entrad laboratório</title></head><body><center><h1 style='font-size:30px;color:red'>Porta Fechada</h1></center></html>");
      }
    }
    
  }
}

void setup() {
  delay(1000);
  WiFi.config(ip, gateway, gateway, subnet); 
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Static IP Setup Info Here...
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.on("/abrir", handleAbrir);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
