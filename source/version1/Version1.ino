// https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi



#include <ESP8266WiFi.h>
const char* ssid     = "ssid_here";
const char* password = "pwd_here";
const int   httpPort = 3000;
const char*     host = "host_here"; //lämna "http://"
const char*      url = "/api/floor/room/temp";
String auth = "fe825afb-da21-4308-9115-8f991c5971ab";
String data   = "id=1&room=Vardagsrum&temperature=19.752&ctype=NodeMCU&ip=192.168.250.111&auth=" + auth;
//String data = "{\"temperature\": \"" + String(random(0,100))+"\", \"humidity\": \"" + String(random(0,100))+ "\", \"date\":\"20017-11-09\"}";



void setup() {
  Serial.begin(115200);
  delay(100);

  Serial.println(); //rensa skärmen från skräp
  Serial.println();

//  // VISA HITTADE SSID
//  Serial.print("Söker nätverk...");
//  // WiFi.scanNetworks will return the number of networks found
//  int n = WiFi.scanNetworks();
//  Serial.print(" klar! ");
//  if (n == 0)
//    Serial.println("Inga WiFi hittade");
//  else
//  {
//    Serial.print(n);
//    Serial.println(" WiFi hittade");
//    for (int i = 0; i < n; ++i)
//    {
//      // Print SSID and RSSI for each network found
//      Serial.print(i + 1);
//      Serial.print(": ");
//      Serial.print(WiFi.SSID(i));
//      Serial.print(" (");
//      Serial.print(WiFi.RSSI(i));
//      Serial.print(")");
//      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
//      delay(10);
//    }
//  }
//
//  Serial.println("");
//
//  // Wait a bit before scanning again
//  //delay(5000);



  // ANSLUT TILL HOST
  Serial.print("Ansluter till: ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA); //WiFi mode: station (WIFI_AP)
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { //https://www.arduino.cc/en/Reference/WiFiStatus
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP()); 
}







void loop() {

  
//  // HTTP GET
//  WiFiClient client;
//
//  Serial.printf("\n[Connecting to %s ... ", host);
//  
//  if (client.connect(host, httpPort)) {
//    // REQUEST
//    Serial.println("connected]");
//    Serial.println("[Sending a GET request]");
//    Serial.println(data);
//
//    client.print(String("GET ") + url + "?" + data + " HTTP/1.1\r\n" +
//                 "Host: " + host + "\r\n" +
//                 //"Content-Type: application/json\r\n" + 
//                 "Connection: close\r\n" +
//                 "\r\n"
//                );
//
//    // RESPONSE
//    Serial.println("[Response:]");
//    while (client.connected()) {
//      if (client.available()) {
//        String line = client.readStringUntil('\n'); //Skriv ut response
//        Serial.println(line);
//      }
//    }
//    client.stop();
//    Serial.println("\n[Disconnected]");
//
//  } else {
//
//    Serial.println("connection failed!]");
//    client.stop();
//  }
//  
//  Serial.println("[Waiting 5S]");
//  delay(5000);
//}


  // HTTP POST
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, httpPort)) {
    Serial.println("connected]");
    
    // REQUEST
    Serial.print("[Sending a POST request ... ");

    // Send request to the server:
    client.println("POST /api/floor/room/temp HTTP/1.1");
    client.println("Host: be9.asuscomm.com:3000");
    client.println("User-Agent: Arduino/1.0");
    client.println("Accept: */*");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(data.length());
    client.println();
    client.print(data);
    Serial.println(" Sent!]");

    // RESPONSE
    Serial.println("[Response:]");
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n'); //Skriv ut response
        Serial.println(line);
      }
    }

    } else {
    Serial.println("[connection failed!]");
    client.stop();
  }

  
  Serial.println();
  Serial.println("[Disconnected]");
  Serial.println("[Waiting 5S]");
  delay(5000);
}

