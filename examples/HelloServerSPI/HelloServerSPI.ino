#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include <C_D_LCD.h>
#include <glcdfont.h>
#include <SPI.h>

const char* ssid = "...";
const char* password = "...";
MDNSResponder mdns;

ESP8266WebServer server(80);

C_D_LCD spilcd;

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
  spilcd.fillScreen(BLACK);
  spilcd.print("\n\nHello from esp8266!\n"); //scrolling message on display
}

void handleNotFound(){
  String message = "File Not Found\n\n";
  spilcd.print("File Not Found\n\n");
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup(void){
  WiFi.begin(ssid, password);
  
  spilcd.begin();
  spilcd.setTextColor(WHITE, BLACK);
  spilcd.fillScreen(BLACK);
  spilcd.print(" ");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    spilcd.print(" ");
    delay(100);
    spilcd.print(".");
  }
  spilcd.print("\nConnected to ");
  spilcd.print(ssid);
  spilcd.print(" IP address: ");
  spilcd.print(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    spilcd.print("\nMDNS responder started\n");
  }
  
  server.on("/", handleRoot);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);
  
  server.begin();
  spilcd.print("\nHTTP server started");
}
 
void loop(void){
  server.handleClient();
} 
