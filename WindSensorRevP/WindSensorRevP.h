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
 
#ifndef WINDSENSORREV_P_H
#define WINDSENSORREV_P_H

#include <Arduino.h>

class WindSensorRevP {
public:
    // Constructor
    WindSensorRevP(int outPin, int tempPin, float zeroWindVoltage, int numSamples);

    // Initialize the sensor
    void begin();

    // Read wind sensor voltage (ADC to voltage)
    float readVoltage();

    // Read temperature sensor (ADC to Celsius)
    float readTemperature();

    // Calculate wind speed (MPH)
    float calculateWindSpeed(float volts, float temperature);

private:
    int _outPin;
    int _tempPin;
    float _zeroWindVoltage;
    int _numSamples;
};

#endif
