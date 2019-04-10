#include <ESP8266WiFi.h>

char* ssid = "TestNetwork";
char* password = "JaJaxD1234";

WiFiServer server(80);

String header;

String greenOutState = "off";
String redOutState = "off";
String yellowOutState = "off";

const int greenOut = 4;
const int redOut = 5;
const int yellowOut = 13;

void setup() {
  Serial.begin(115200);
  
  pinMode(greenOut, OUTPUT);
  pinMode(redOut, OUTPUT);
  pinMode(yellowOut, OUTPUT);
  digitalWrite(greenOut, LOW);
  digitalWrite(redOut, LOW);
  digitalWrite(yellowOut, LOW);

  // Connect to Wi-Fi network with SSID and password
  Serial.println("Connecting to " + String(ssid));
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character if the current line is blank, you got two newline characters in a row. That's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
//            client.println("HTTP/1.1 200 OK");
//            client.println("Content-type:text/html");
//            client.println("Connection: close");
//            client.println();

            //GREEN LED CONTROL
            if (header.indexOf("GET /green/on") >= 0) {
              Serial.println("GPIO " + String(greenOut) + " on");
              greenOutState = "on";
              digitalWrite(greenOut, HIGH);
            } else if (header.indexOf("GET /green/off") >= 0) {
              Serial.println("GPIO " + String(greenOut) + " off");
              greenOutState = "off";
              digitalWrite(greenOut, LOW);

            //RED LED CONTROL
            } else if (header.indexOf("GET /red/on") >= 0) {
              Serial.println("GPIO " + String(redOut) + " on");
              redOutState = "on";
              digitalWrite(redOut, HIGH);
            } else if (header.indexOf("GET /red/off") >= 0) {
              Serial.println("GPIO " + String(redOut) + " off");
              redOutState = "off";
              digitalWrite(redOut, LOW);

            //YELLOW LED CONTROL
            } else if (header.indexOf("GET /yellow/on") >= 0) {
              Serial.println("GPIO " + String(yellowOut) + " on");
              yellowOutState = "on";
              digitalWrite(yellowOut, HIGH);
            } else if (header.indexOf("GET /yellow/off") >= 0) {
              Serial.println("GPIO " + String(yellowOut) + " off");
              yellowOutState = "off";
              digitalWrite(yellowOut, LOW);
            }
            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>");
            client.println("html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center; background-color: #111;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px; text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button_off {background-color: #555555;}");
            client.println("p { color: #fff; }");
            client.println("</style></head>");
            
            client.println("<body><h1>ESP8266MOD</h1>");

            //GREEN LED button
            client.println("<p>GREEN LED, GPIO " + String(greenOut) + " - State " + String(greenOutState) + "</p>");
            if (greenOutState == "off") {
              client.println("<p><a href=\"/green/on\"><button class=\"button\">Turn on</button></a></p>");
            } else {
              client.println("<p><a href=\"/green/off\"><button class=\"button button_off\">Turn off</button></a></p>");
            }

            //RED LED button
            client.println("<p>RED LED, GPIO " + String(redOut) + " - State " + String(redOutState) + "</p>");
            if (redOutState == "off") {
              client.println("<p><a href=\"/red/on\"><button class=\"button\">Turn on</button></a></p>");
            } else {
              client.println("<p><a href=\"/red/off\"><button class=\"button button_off\">Turn off</button></a></p>");
            }

            //YELLOW LED button
            client.println("<p>YELLOW LED, GPIO " + String(yellowOut) + " - State " + String(yellowOutState) + "</p>");   
            if (yellowOutState == "off") {
              client.println("<p><a href=\"/yellow/on\"><button class=\"button\">Turn on</button></a></p>");
            } else {
              client.println("<p><a href=\"/yellow/off\"><button class=\"button button_off\">Turn off</button></a></p>");
            }
            client.println("</body></html>");
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
//    Serial.println("Client disconnected.");
//    Serial.println("");
  }
}
