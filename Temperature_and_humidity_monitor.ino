#include <DHT.h>

//Wifi
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

#define SENSOR_PIN            16    
#define SENSOR_TYPE           DHT11 
#define SERIAL_BAUD_RATE      115200 
#define INITIAL_DELAY_S       5     
#define READ_INTERVAL_S       2     
#define ERROR_RETRY_DELAY_MS  200   

//Callmebot 

#define SSID            ""
#define PASSWORD        ""
#define PHONE_NUMBER    ""
#define API_KEY         ""

DHT sensor(SENSOR_PIN, SENSOR_TYPE);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  sensor.begin();

  Serial.println("Preparing DHT11");
  delay(INITIAL_DELAY_S * 1000);
  Serial.println("DHT11 is ready");

  
}

bool connection(){
      Serial.println("Trying to connect to Wifi");
      WiFi.begin(SSID, PASSWORD);

      int timeout=10;

      if(WiFi.status() == WL_CONNECTED){
        Serial.println("Connected");
        return true;
      }else{
        Serial.println("Connection failed");
        return false;
      }
}      

int send_data(float humidity, float temperature){

      String message = "Temperature: " + String(temperature, 1) +" C, Humidity: " + String(humidity, 1) + " %";      
      String url= "https://api.callmebot.com/whatsapp.php?phone="+String(PHONE_NUMBER)+"&text="+message+"&apikey="+String(API_KEY);

      WiFiClientSecure client;
      client.setInsecure();          
      HTTPClient http;
      http.begin(client, url);

      int httpCode = http.GET();

      if (httpCode == 200){
          Serial.println("Success!");
          http.end();
          return 0;  
      } else {
          Serial.print("Error: ");
          http.end();
          return httpCode;
      }
}
    
    
void loop() {
  float humidity = sensor.readHumidity();
  float temperature = sensor.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Bad reading - retrying...");
    delay(ERROR_RETRY_DELAY_MS);
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature, 1);
    Serial.print(" C, Humidity: ");
    Serial.print(humidity, 1);
    Serial.println(" %");
  }

   
    if (WiFi.status() == WL_CONNECTED) {
    send_data(humidity, temperature);
  } else {
    Serial.println("Not connected to WiFi");
    connection(); 
  }

  delay(READ_INTERVAL_S * 1000);
  }
  
