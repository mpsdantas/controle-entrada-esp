#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"
/* Configuração da rede*/
IPAddress    apIP(10, 0, 0, 1);
const char *ssid = "LAR-CONTROLE";
const char *password = "larfacil1234";

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/html", "<html><head><script>var person = prompt('Por favor digire sua matricula para ter acesso ao laboratório:');window.location.href = '/abrir?matricula='+person;</script></head></html>");
}
void handleAbrir(){
  if(server.hasArg("matricula")) {
    bool contem = false;
    int matricula = server.arg("matricula").toInt();
    for(int i=0;i<n;i++){
      if(matriculaBanco[i]==matricula){
        contem = true;
        break;
      }
    }
    if(contem){
      digitalWrite(13, 1);
      server.send(200, "text/html", "<h1>Porta aberta</h2>");
      delay(5000);
      digitalWrite(13, 0);
      
    }else{
      server.send(200, "text/html", "<h1>Porta fechada</h2>");
    }
  }
}

void setup() {
  delay(1000);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  
  //set-up the custom IP address
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/abrir", handleAbrir);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}
