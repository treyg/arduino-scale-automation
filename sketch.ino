#include "HX711.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 2;

// Timestamp for the last time the scale was tared
unsigned long lastTareTime = 0;
// Interval to re-tare the scale (20 minutes in milliseconds)
const unsigned long TARE_INTERVAL = 20 * 60 * 1000;  

float current_weight = 0;
float cal_factor = 3.2; //3.229 

HX711 scale;

void fullCalibration() {
  Serial.println("Performing full calibration");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(2280.f); // This value is obtained by calibrating the scale with known weights
  scale.tare();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Calibration ");
  lcd.setCursor(0, 1);
  lcd.print("     Complete     ");
  delay(200);  // Show calibration is done with a 1-second delay 
  lcd.clear();
}

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  digitalWrite(9, HIGH);
  digitalWrite(12, HIGH); 

  lcd.init();
  lcd.backlight();
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Calibrating ");
  lcd.setCursor(0, 1);
  lcd.print("     Sensor     ");
  
  fullCalibration();  // Perform a full calibration at the start

  lastTareTime = millis();  // Initialize the last tare time
}

void reTareScale() {
  Serial.println("Re-taring the scale");
  scale.tare();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Re-Taring ");
  lcd.setCursor(0, 1);
  lcd.print("     Complete     ");
  delay(200);  // Show re-taring is done with a 1-second delay 
  lcd.clear();
}

void measure_weight() {
  float reading = scale.get_units(5); // Get a single reading from the scale
  reading = reading * cal_factor; // Apply the calibration factor to the reading
  current_weight = reading; // Store the calibrated reading in current_weight

  // Display the weight on the LCD
  lcd.setCursor(0, 0);
  lcd.print("Weight");
  lcd.setCursor(0, 1);
  lcd.print(current_weight);
  lcd.print("g");
}

void loop() {
  unsigned long stable_start_time = 0; // Variable to store the start time of stable weight
  bool weight_stable = false; // Flag to indicate if the weight is stable

  // Continue to measure weight until the weight is stable
  while (!weight_stable) {
    measure_weight(); // Measure the weight and display it on the LCD

    // Check if the weight is greater than 12 grams
    if (abs(current_weight) > 12) {
      // If the stable_start_time is 0, set it to the current time (millis)
      if (stable_start_time == 0) {
        stable_start_time = millis();
      }
      // If the weight has been stable for more than 600ms, set weight_stable to true
      else if (millis() - stable_start_time > 600) {
        weight_stable = true;
      }
    }
    // If the weight is not greater than 12 grams, reset the stable_start_time to 0
    else {
      stable_start_time = 0;
    }

    delay(300); // Add a delay of 300 milliseconds between weight measurements
  }

  // Control the relays based on the stable weight range
  if (current_weight >= 24 && current_weight < 53) {
    digitalWrite(9, LOW); // Activate relay connected to pin 9
    delay(350); // Wait for 350 milliseconds
    digitalWrite(9, HIGH); // Deactivate relay connected to pin 9
  } else if (current_weight >= 17 && current_weight < 25) {
    digitalWrite(12, LOW); // Activate relay connected to pin 12
    delay(350); // Wait for 350 milliseconds
    digitalWrite(12, HIGH); // Deactivate relay connected to pin 12
  }

  // Check if it's time to re-tare the scale
  if (millis() - lastTareTime >= TARE_INTERVAL) {
    reTareScale();
    lastTareTime = millis();  // Update the last tare time
  }
}
