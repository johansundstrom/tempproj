// https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi



#include <ESP8266WiFi.h>
const char* ssid     = "b9-mobile";
const char* password = "0nsdagsk1ubben";
const int   httpPort = 3000;
const char*     host = "be9.asuscomm.com"; //lämna "http://"
const char*      url = "/api/temp/room";
String data   = "id=1&room=vardagsrum&temperature=19.752&ctype=NodeMCU&ip=192.168.250.111";
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

  
  // SENDING GET TO HOST
  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, httpPort))
  {
    Serial.println("connected]");

    //RESPONSE
    Serial.println("[Sending a request]");
      /*
      client.println("GET /api/users HTTP/1.1");
      client.println("Host: " + host);
      client.println("Connection: close");
      client.println("");
      */
    client.print(String("GET ") + url + "?" + data + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 //"Content-Type: application/json\r\n" + 
                 "Connection: close\r\n" +
                 "\r\n"
                );

    //REQUEST
    Serial.println("[Response:]");
    while (client.connected())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n'); //Skriv ut response
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  Serial.println("[Waiting 5S]");
  delay(5000);
}


//  // SENDING POST TO HOST
//  WiFiClient client;
//  
//  if (!client.connect(host, httpPort)) {
//    Serial.println("connection failed");
//    return;
//  }
//
//  
//  
//  Serial.print("Requesting POST: ");
//  // Send request to the server:
//  client.println("POST " + url + " HTTP/1.1");
//  client.println("Host: be9.asuscomm.com");
//  client.println("Accept: */*");
//  client.println("Content-Type: application/x-www-form-urlencoded");
//  client.print("Content-Length: ");
//  client.println(data.length());
//  client.println();
//  client.print(data);
//  Serial.println(data);
//
//  delay(500); // Can be changed
//  if (client.connected()) { 
//    client.stop();  // DISCONNECT FROM THE SERVER
//  }
//  Serial.println();
//  Serial.println("closing connection");
//  delay(5000);
//}
