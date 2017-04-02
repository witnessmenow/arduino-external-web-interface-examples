#include <ArduinoJson.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

// Change these!
const char* ssid = "ssid";
const char* password = "password";

// This will work for this example
// Feel free to use it for other projects if you want.
// Code is avaialble here: https://github.com/witnessmenow/external-web-interfaces-arduino
String host = "arduino.dealhunterpro.com";

// Change this to set the title on the webpage
String webPageTitle = "My Custom Title";

ESP8266WebServer server(80);

String redirectUrl;
String ip;

void redirectionPage(){
  String website = "<!DOCTYPE html>\n";
  website = website + "<html>\n";
  website = website + "   <head>\n";
  website = website + "    <meta charset=\"utf-8\">\n";
  website = website + "    <meta http-equiv=\"refresh\" content=\"1; url=" + redirectUrl + "\">\n";
  website = website + "    <script type=\"text/javascript\">\n";
  website = website + "       window.location.href = \"" + redirectUrl +"\"\n";
  website = website + "    </script>\n";
  website = website + "    <title>Page Redirection</title>\n";
  website = website + "  </head>\n";
  website = website + "  <body>\n";
  website = website + "     Follow <a href='" + redirectUrl +"'>this link</a> if you are not automatically redirected.\n";
  website = website + "  </body>\n";
  website = website + "</html>\n";

  server.send(200, "text/html", website);
}

String readSensorOne(){
  return "12345";
}

void getData(){
  StaticJsonBuffer<200> jsonBuffer;

  JsonObject& root = jsonBuffer.createObject();
  root["sensor1"] = readSensorOne();
  root["Millis"] = String(millis());

  char buffer[256];
  root.printTo(buffer, sizeof(buffer));
  server.send(200, "text/json", buffer);
}

void handleNotFound(){
  String message = "File Not Found\n\n";
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
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connect to: ");
  Serial.println(WiFi.localIP());

  ip = WiFi.localIP().toString();

  redirectUrl = "http://" + host + "/static/test.html?title=" + webPageTitle + "&ip=" + ip;
  Serial.print("It will redirect to: ");
  Serial.println(redirectUrl);

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", redirectionPage);

  server.on("/data", getData);

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
