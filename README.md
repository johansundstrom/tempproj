# Temperaturläsningsprojektet

## Grejen
En fristående ESP8266 mäter något och skickar data till server med RESTful API. Server autenticerar anropet. Om ok spara resultatet i DB, kanske också i något moln. Analyserat resutlatat finns i responsiv webbserver

## Komponenterna
### Sensorn
Kan vara vad som helst men jag utgår från DHT11 (https://akizukidenshi.com/download/ds/aosong/DHT11.pdf).

### ESP
Sensorsändaren från Espressif (http://espressif.com/en/products/hardware/esp8266ex/overview) ansluter till WiFi och lämnar ifrån sig.

### Server
Servern består av RPi och kör Node. RESTful API enligt "host:TCP/api/floor/room/temp". Varje sändning sker med POST och lagras direkt i extern DB.

### WWW-server
Processat data levereras med D3.js för rendering i användarklient.
