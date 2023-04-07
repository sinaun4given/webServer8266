#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
// #include <Servo.h>
// Servo myservo;  
// int servoPin = 5;     // Set the servo signal pin to D1 (GPIO5)
// int interruptPin = 4; // Set the interrupt input pin to D2 (GPIO4)  
ESP8266WebServer server(80);
char * ssid="TP-Link_5360";
char * pass="3841hamidj92";
String str(ssid);
IPAddress staticip(192,168,1,108);
IPAddress subnetmask(255,255,255,0);
IPAddress gateway(192,168,1,1);
IPAddress dns1(8,8,8,8);
int led_on_board=2;
void setup() {
  // myservo.attach(servoPin);  // Attach the servo to the signal pin
  // pinMode(interruptPin, INPUT_PULLUP);  // Set the interrupt input pin to input mode with pull-up resistor
  // attachInterrupt(digitalPinToInterrupt(interruptPin), interruptHandler, FALLING);  // Attach the interrupt handler function to the interrupt input pin 


  pinMode(led_on_board, OUTPUT);
  WiFi.disconnect();
  Serial.begin(115200);
  WiFi.begin(ssid,pass);
  WiFi.config(staticip, gateway, subnetmask, dns1);
  Serial.println(" ");
  Serial.println("connectin to (("+str+")) Access Point");
  while (WiFi.status()!=WL_CONNECTED) {
  Serial.println(".");
  delay(500);
  }
Serial.println(" ");
Serial.println("Sir , i connected to router with this info :  ");
Serial.println("ESP IP address : ");
Serial.println(WiFi.localIP());
Serial.println(" SubnetMask : ");
Serial.println(WiFi.subnetMask());
Serial.println(" GateWay : ");
Serial.println(WiFi.gatewayIP());
Serial.println("Host Name : ");
Serial.println(WiFi.hostname());
server.begin();
server.on("/",Home);
server.on("/ledon",ledon);
server.on("/ledoff",ledoff);

}

void loop() {
  server.handleClient();
  
}


//////////////////////////functions
void Home(){
  String Home="<!DOCTYPE html><html><head><title>ESP-SERVER</title></head><body><h1>hello mr labkhand<h1><a href=\"/ledon\">PUSH LEDON</a><br><hr><a href=\"/ledoff\">PUSH LEDOff</a><body><html>";
  server.send(200,"text/HTML",Home);
}
void ledon(){
  digitalWrite(led_on_board, HIGH);
  server.send(204,"");
  // myservo.write(90);    // Set the servo angle to 90 degrees
  // delay(1000);  
  
}
void ledoff(){
 digitalWrite(led_on_board, LOW);
  server.send(204,"");
}
// void interruptHandler() {
//   myservo.write(90);    // Set the servo angle to 90 degrees
//   delay(1000);          // Wait for 1 second
//   myservo.write(0);     // Set the servo angle to 0 degrees
// }
