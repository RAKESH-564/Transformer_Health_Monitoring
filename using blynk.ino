// Libraries
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Blynk Authentication Token
#define BLYNK_TEMPLATE_ID "YOUR_TEMPLATE_ID"
#define BLYNK_DEVICE_NAME "YOUR_DEVICE_NAME"
#define BLYNK_AUTH_TOKEN "YOUR_BLYNK_AUTH_TOKEN"

// Wi-Fi Credentials
#define WIFI_SSID "YOUR_WIFI_SSID"
#define WIFI_PASSWORD "YOUR_WIFI_PASSWORD"

// Sensor Pin Definitions
#define DHTPIN 4       // DHT22 temperature sensor pin
#define DHTTYPE DHT22  // DHT sensor type
#define VOLTAGE_PIN 34 // Voltage sensor pin
#define CURRENT_PIN 35 // Current sensor pin

// Sensor Initialization
DHT dht(DHTPIN, DHTTYPE);

// Blynk Virtual Pins
#define VIRTUAL_TEMP V0
#define VIRTUAL_VOLTAGE V1
#define VIRTUAL_CURRENT V2

void setup() {
    // Start serial communication
    Serial.begin(115200);

    // Initialize Blynk
    Blynk.begin(BLYNK_AUTH_TOKEN, WIFI_SSID, WIFI_PASSWORD);

    // Initialize DHT sensor
    dht.begin();
}

void loop() {
    // Run Blynk
    Blynk.run();

    // Read temperature
    float temperature = dht.readTemperature();

    // Read voltage (analog value conversion)
    int voltageRaw = analogRead(VOLTAGE_PIN);
    float voltage = (voltageRaw / 4095.0) * 3.3 * 10; // Assuming voltage sensor scale factor

    // Read current (analog value conversion)
    int currentRaw = analogRead(CURRENT_PIN);
    float current = (currentRaw / 4095.0) * 3.3 * 10; // Assuming current sensor scale factor

    // Display data on Serial Monitor
    Serial.print("Temperature: "); Serial.print(temperature); Serial.println(" °C");
    Serial.print("Voltage: "); Serial.print(voltage); Serial.println(" V");
    Serial.print("Current: "); Serial.print(current); Serial.println(" A");

    // Send data to Blynk
    Blynk.virtualWrite(VIRTUAL_TEMP, temperature);
    Blynk.virtualWrite(VIRTUAL_VOLTAGE, voltage);
    Blynk.virtualWrite(VIRTUAL_CURRENT, current);

    // Delay for stability
    delay(2000);  // 2-second delay for data updates
}
