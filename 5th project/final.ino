#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL68IRbcKwK"
#define BLYNK_TEMPLATE_NAME "Smart plant"
#define BLYNK_AUTH_TOKEN "FYbzBOPgV2tEFXVUv1PLoDN0av99P7UN"

#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>
#include <SoftwareSerial.h>
#include <DHT.h>

// --- 1. CREDENTIALS ---
char auth[] = "FYbzBOPgV2tEFXVUv1PLoDN0av99P7UN";
char ssid[] = "112B";       // YOUR WIFI NAME
char pass[] = "csesquare";  // YOUR WIFI PASSWORD

// --- 2. PINS ---
#define RX_PIN 2         // Arduino D2 -> ESP TX
#define TX_PIN 3         // Arduino D3 -> ESP RX
#define BUZZER_PIN 4     // NEW: Buzzer on D4
#define DHT_PIN 5        
#define PUMP_PIN 6       
#define SOIL_PIN A0      
#define DENSITY_PIN A1   

// --- 3. OBJECTS ---
SoftwareSerial EspSerial(RX_PIN, TX_PIN);
ESP8266 wifi(&EspSerial);
BlynkTimer timer;
DHT dht(DHT_PIN, DHT11);

void setup() {
  // Debug Console
  Serial.begin(115200);
  
  // ESP Serial (Must be 9600)
  EspSerial.begin(9600); 
  delay(100);

  // Force Reset ESP
  Serial.println("Resetting ESP...");
  EspSerial.println("AT+RST");
  delay(3000); 

  // Init Pins
  pinMode(PUMP_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT); // Set Buzzer as Output
  pinMode(DENSITY_PIN, INPUT);
  
  digitalWrite(PUMP_PIN, HIGH); // Start Pump OFF
  digitalWrite(BUZZER_PIN, LOW); // Start Buzzer OFF

  dht.begin();

  // Connect to Blynk
  Serial.println("Connecting to Blynk...");
  Blynk.begin(auth, wifi, ssid, pass);
  Serial.println("System Online!");

  // Run sensor logic every 2 seconds
  timer.setInterval(2000L, sendSensorData);
}

void loop() {
  Blynk.run();
  timer.run();
}

// --- PART 1: READ SENSORS & BUZZER LOGIC ---
void sendSensorData() {
  // 1. Read DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(t)) t = 0; 

  // 2. Read Soil Moisture (A0)
  int rawSoil = analogRead(SOIL_PIN);
  int soilPercent = map(rawSoil, 1023, 200, 0, 100);
  soilPercent = constrain(soilPercent, 0, 100);

  // 3. Read Water Density (A1)
  int rawDensity = analogRead(DENSITY_PIN);
  int densityValue = map(rawDensity, 0, 1023, 0, 1000);

  // 4. Send ALL Data to App
  Blynk.virtualWrite(V0, t);            
  Blynk.virtualWrite(V1, h);            
  Blynk.virtualWrite(V3, soilPercent);  
  Blynk.virtualWrite(V6, densityValue); 
  
  // --- BUZZER ALERT LOGIC ---
  // If soil is completely dry (0%), turn ON buzzer
  if (soilPercent == 0) {
    digitalWrite(BUZZER_PIN, HIGH); // Sound ON
    Serial.println("ALERT: Soil is 0% - Buzzer ON");
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Sound OFF
  }
}

// --- PART 2: MANUAL PUMP CONTROL (V12) ---
BLYNK_WRITE(V12) { 
  int pinValue = param.asInt(); // 0 or 1
  
  if (pinValue == 1) {
    digitalWrite(PUMP_PIN, LOW); // Relay ON
    Serial.println("Manual: Pump ON");
  } else {
    digitalWrite(PUMP_PIN, HIGH); // Relay OFF
    Serial.println("Manual: Pump OFF");
  }
}