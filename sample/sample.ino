#include <DHT.h>

// DHT11 settings
#define DHTPIN 22          // DHT11 data pin connected to GPIO 15
#define DHTTYPE DHT11      // DHT 11 sensor type
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT object

// MQ-135 settings
#define MQ135_PIN 27       // MQ-135 analog output pin connected to GPIO 27 (ADC input)

// Soil Temperature Sensor settings
#define SOIL_TEMP_PIN 26   // Soil temperature analog sensor connected to GPIO 26 (A0)

void setup() {
  Serial.begin(9600);        // Initialize serial communication
  dht.begin();               // Start the DHT11 sensor
  
  Serial.println("DHT11, MQ-135, and Soil Temperature Sensor Test with Raspberry Pi Pico");
}

void loop() {
  // Read temperature and humidity from DHT11 sensor
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  // Check if any reads failed
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT11 sensor!");
  } else {
    // Print temperature and humidity values
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // Read air quality value from MQ-135 sensor
  int airQualityValue = analogRead(MQ135_PIN);  // Read analog value from MQ-135
  float airVoltage = (airQualityValue / 1023.0) * 3.3;  // Convert to voltage
  
  // Print air quality (raw analog value and corresponding voltage)
  Serial.print("Air Quality (raw): ");
  Serial.println(airQualityValue);
  
  Serial.print("Air Quality Voltage: ");
  Serial.print(airVoltage);
  Serial.println(" V");

  // Read soil temperature value from soil sensor
  int soilTempValue = analogRead(SOIL_TEMP_PIN);  // Read analog value from soil temperature sensor
  float soilVoltage = (soilTempValue / 1023.0) * 3.3;  // Convert to voltage
  
  // Convert voltage to temperature (you may need a specific formula based on your soil temp sensor)
  // Assuming a simple linear mapping: 0.5V = 0°C and 3.3V = max temp, adjust according to the sensor used
  float soilTempCelsius = (soilVoltage - 0.5) * 100.0;  // Example conversion, adjust as per sensor spec
  
  // Print soil temperature value
  Serial.print("Soil Temperature (raw): ");
  Serial.println(soilTempValue);
  
  Serial.print("Soil Temperature Voltage: ");
  Serial.print(soilVoltage);
  Serial.println(" V");

  Serial.print("Soil Temperature (Celsius): ");
  Serial.print(soilTempCelsius);
  Serial.println(" °C");

  // Wait before taking next reading
  delay(2000);
}
