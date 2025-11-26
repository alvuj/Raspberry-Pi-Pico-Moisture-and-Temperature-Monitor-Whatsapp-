# Raspberry Pi Pico Moisture and Temperature Monitor with Whatsapp
Raspberry Pi Pico W project that reads temperature and humidity from a DHT11 sensor  and sends WhatsApp notifications using the CallMeBot API over Wifi.


# Overview

| DHT11 Pin | Pico W Pin |
|-----------|------------|
| VCC       | 3V3(OUT)   |
| DATA      | GPIO 16    |
| GND       | GND        |

To use WhatsApp notifications, you must activate your phone number:

**1. Save contact**

Save this number in your WhatsApp:

+34 644 94 36 90

**2. Send activation message**

Open WhatsApp and send this text message to the saved number:

I allow callmebot to send me messages

**3. Receive your API key**

You will receive a reply with your API key.

"Your API key is: 1234567"

Use this key in your code:

#define API_KEY "1234567"
## Libraries

- DHT sensor library (Adafruit)
- WiFi
- WiFiClientSecure
- HTTPClient

# Setting up credentials
```bash
#define SSID      "YOUR_WIFI"
#define PASSWORD  "YOUR_PASSWORD"
#define PHONE_NUMBER "XXXXXXXXXXXX"   
#define API_KEY      "1234567"
```
