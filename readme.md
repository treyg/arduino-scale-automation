1. **Initialization**:
    - Libraries for the HX711 scale and the I2C LCD display are included.
    - Pins for the HX711 scale are defined.
    - Variables for weight measurements and calibration are declared.
    - A timestamp (`lastTareTime`) is set up to track the last time the scale was tared.
    - The interval for re-taring (`TARE_INTERVAL`) is set at 20 minutes.

2. **Setup**:
    - Serial communication is started for debugging purposes.
    - Relay pins are set as OUTPUT and initialized to a HIGH state (relays off).
    - The LCD display is initialized and a "Calibrating" message is displayed.
    - The scale undergoes a full calibration using the `fullCalibration()` function.
    - The time of the last tare operation is recorded.

3. **Weight Measurement (`measure_weight()` function)**:
    - The scale reads the current weight.
    - The weight reading is adjusted using a calibration factor.
    - The adjusted weight is displayed on the LCD.

4. **Full Calibration (`fullCalibration()` function)**:
    - A message indicating that the scale is undergoing full calibration is displayed on the LCD.
    - The scale is initialized, set with a known calibration factor, and tared.
    - A "Calibration Complete" message is displayed on the LCD.

5. **Re-Taring (`reTareScale()` function)**:
    - The scale is quickly tared to account for any drift over time.
    - A "Re-Taring Complete" message is displayed on the LCD.

6. **Main Loop**:
    - The weight is continuously measured until it stabilizes (remains consistent for more than 600 milliseconds).
    - If the stabilized weight is within certain ranges, specific relays are activated for 350 milliseconds to presumably sort or handle the package based on its weight.
    - The code checks if 20 minutes have passed since the last tare operation. If so, the scale is re-tared using the `reTareScale()` function to ensure accuracy.