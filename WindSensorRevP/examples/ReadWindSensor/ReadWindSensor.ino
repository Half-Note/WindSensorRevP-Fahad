/*
 * Copyright (c) 2025 by Fahad <your.email@example.com>
 * WindSensorRevP library for Arduino and ESP32.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file WindSensorRevP.h
 * @brief Library for the Wind Sensor Rev. P to measure wind speed and temperature.
 *
 * @details
 * This library provides an interface to read wind speed and temperature from the
 * Wind Sensor Rev. P using an ESP32 or Arduino. It includes functions to read the 
 * sensor output voltage, measure temperature, and calculate wind speed.
 *
 * @TODO
 * - Optimize ADC sampling for better accuracy.
 * - Implement filtering techniques to reduce noise in wind speed calculation.
 * - Add support for different microcontrollers.
 * - Improve calibration method for zero wind voltage.
 */
 
#include <WindSensorRevP.h>

const int outPin = 2;    // Wind sensor analog pin
const int tempPin = 4;   // Temperature sensor analog pin
const float zeroWindVoltage = 1.131; // Measured from calibration
const int numSamples = 50; // Number of samples for accuracy

WindSensorRevP windSensor(outPin, tempPin, zeroWindVoltage, numSamples);

void setup() {
    Serial.begin(115200);
    windSensor.begin();
}

void loop() {
    // Read wind voltage and temperature
    float windVoltage = windSensor.readVoltage();
    float temperature = windSensor.readTemperature();

    // Calculate wind speed
    float windSpeed = windSensor.calculateWindSpeed(windVoltage, temperature);

    // Print results
    Serial.print("Wind Voltage: ");
    Serial.print(windVoltage, 3);
    Serial.print("\tTemperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\tWind Speed: ");
    Serial.print(windSpeed, 2);
    Serial.println(" MPH");

    delay(1000);
}
