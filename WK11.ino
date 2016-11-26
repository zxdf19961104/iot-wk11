#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char *ssid = "GGININDER";
const char *password = "";
ESP8266WebServer server(80);

char led_status[50];
String webSite;

#define LEDR 5
#define LEDG 4
#define LEDB 14

void turnoff(){
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);
}
void buildWeb(){
  
  webSite += "<!DOCTYPE html>";
  webSite += "<head><meta charset = \"utf-8\">";
  webSite += "<title> LED調色 </title>";
  webSite += "<style>";
  webSite += "body{background-color:#cceeff; font-family: Arial, Helvetica, Sans-Serif; Color: #000088;}";
  webSite += "div{width:500px; text-align: center; margin-left:auto;margin-right:auto;}";
  webSite += "</style>";
  webSite += "</head>";
  webSite += "<body>";
  webSite += "<div>";
  webSite += "<h1>RGB LED</h1>";
  webSite += "<h3>110419007 方宣翔</h3>";
  webSite += "<h3>110419013 管啟翔</h3>";
  webSite += "<p id=\"ledStatus\">You can select a RGB LED color ...</p>";
  webSite += "<form action=\"form1\">";
  webSite += "<input type=\"radio\" id=\"red\" name=\"led\" value=\"red\"><label for=\"red\">Color Red</label>";
  webSite += "<input type=\"radio\" id=\"green\" name=\"led\" value=\"green\"><label for=\"green\">Color Green</label>";
  webSite += "<input type=\"radio\" id=\"blue\" name=\"led\" value=\"blue\"><label for=\"blue\">Color blue</label><br><br>";
  webSite += "<input type=\"submit\" value=\"submit\"></form>";
  webSite += "</div>";
  webSite += "</body></html>";
}
void handleRoot(){
  server.send(200,"text/html",webSite);
}

void handleLEDStatus(){
  if(server.arg("led") == "red"){
     snprintf(led_status,50,"Now, RGB LED color is red...");
    digitalWrite(LEDR,LOW);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,HIGH);
  }
  else if(server.arg("led") == "green"){
     snprintf(led_status,50,"Now, RGB LED color is green...");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,LOW);
    digitalWrite(LEDB,HIGH);
  }
  else if(server.arg("led") == "blue"){
     snprintf(led_status,50,"Now, RGB LED color is blue...");
    digitalWrite(LEDR,HIGH);
    digitalWrite(LEDG,HIGH);
    digitalWrite(LEDB,LOW);
  }
  server.send (200,"text/html",led_status );
}

void handleNotFound(){
  server.send(404,"text/html","404 Error!");
}

void setup() {
  // put your setup code here, to run once:
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
  turnoff();
  buildWeb();
  WiFi.softAP(ssid,password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.println(myIP);
  server.on("/",handleRoot);
  server.on("/form1",handleLEDStatus);
  server.onNotFound(handleNotFound);
  server.begin();
}
void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
}
