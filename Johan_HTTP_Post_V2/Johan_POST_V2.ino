// https://github.com/esp8266/Arduino/tree/master/doc/esp8266wifi

#include <ESP8266WiFi.h>
#include <DHT.h>;


const char* ssid     = "ssid";
const char* password = "password";
const int   httpPort = 3000;
const char*     host = "host"; //utelämna "http://"
const char*      url = "/api/floor/room/temp";
String          auth = "fe825afb-da21-4308-9115-8f991c5971ab";
String localIp;
String data;



// dht22
// läsning från dht22 tar 250mS
#define dhtpin 4          // gpio4 (d2)
#define dhttype DHT22     // dht22  (AM2302)
DHT dht(dhtpin, dhttype); // Initialize DHT sensor for normal 16mhz Arduino



void setup() {
  Serial.begin(115200);
  delay(100);
  
  // rensa från skräp
  Serial.println(); 
  Serial.println();

  // anslut till host
  Serial.print("Ansluter till: ");
  Serial.println(ssid);

  // https://www.arduino.cc/en/Reference/WiFi
  // WiFi mode: station! (WIFI_STA | WIFI_AP)
  WiFi.mode(WIFI_STA); 
  // https://www.arduino.cc/en/Reference/WiFiBegin
  WiFi.begin(ssid, password);

  // https://www.arduino.cc/en/Reference/WiFiStatus
  while (WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi!");
  Serial.print("IP address: ");
  // https://www.arduino.cc/en/Reference/WiFiLocalIP
  Serial.println(WiFi.localIP()); 
  localIp = WiFi.localIP().toString();
}




void loop() {
  // https://create.arduino.cc/projecthub/attari/temperature-monitoring-with-dht22-arduino-15b013
  //hämta värden från DHT
  // humid
  float h = dht.readHumidity();
  // temperatur Celsius (default)
  float t = dht.readTemperature();
  // temperature Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // heat index? Vem behöver det?
  float hic = dht.computeHeatIndex(t, h, false);

  // http request
  // https://www.arduino.cc/en/Reference/WiFiClient
  WiFiClient client;

  Serial.printf("\n[Anslut till %s... ", host);
  https://www.arduino.cc/en/Reference/ClientConnect
  if (client.connect(host, httpPort)) {
    Serial.println("Ansluten]");
    Serial.println();
    
    // post
    Serial.print("[POST request... ");

    // Send request to the server:
    client.println("POST /api/floor/room/temp HTTP/1.1");
    client.println("Host: be9.asuscomm.com:3000");
    client.println("User-Agent: Arduino/1.0");
    client.println("Accept: */*");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    data = "id=1&room=Vardagsrum&hic=" + String(hic)+ "&humid=" + String(h) + "&temp=" + String(t) + "&ctype=NodeMCU&ip=" + localIp + "&auth=" + auth;
    client.println(data.length());
    client.println();
    client.print(data);
    Serial.println(" Sänt!]");

    // respons
    Serial.println();
    Serial.println("[Response från server på ovanstående request]");
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n'); //Skriv ut respons
        Serial.println(line);
      }
    }

    } else {
    Serial.println("[connection failed!]");
    client.stop();
  }

  
  Serial.println();
  client.stop();
  Serial.println("[Nedkopplat]");
  Serial.println("[Vänta 5s]");

  delay(5000);
}
