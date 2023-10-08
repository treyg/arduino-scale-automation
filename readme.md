

1. **Initialization**:
    - Libraries for the HX711 scale and the I2C LCD display are included.
    - Pins for the HX711 scale are defined.
    - Variables for weight measurements and calibration are declared.
    - A counter (`lastResetTime`) is set up to track the last time the scale was reset.
    - The reset interval (`RESET_INTERVAL`) is set at 20 minutes.

2. **Setup**:
    - Serial communication is started for debugging purposes.
    - Relay pins are set as OUTPUT and initialized to a HIGH state (relays off).
    - The LCD display is initialized and a "Calibrating" message is displayed.
    - The scale is initialized and calibrated using the `initializeScale()` function.
    - The time of the last scale reset is recorded.

3. **Weight Measurement (`measure_weight()` function)**:
    - The scale reads the current weight.
    - The weight reading is adjusted using a calibration factor.
    - The adjusted weight is displayed on the LCD.

4. **Scale Reset (`initializeScale()` function)**:
    - A message indicating that the scale is being reset is displayed on the LCD.
    - The scale is initialized and calibrated.
    - A "Calibration Complete" message is displayed on the LCD.

5. **Main Loop**:
    - The weight is continuously measured until it stabilizes (remains consistent for more than 600 milliseconds).
    - If the stabilized weight is within certain ranges, specific relays are activated for 350 milliseconds to presumably sort or handle the package based on its weight.
    - The code checks if 20 minutes have passed since the last scale reset. If so, the scale is reset to ensure accuracy.
