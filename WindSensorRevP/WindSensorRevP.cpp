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
 
#include "WindSensorRevP.h"

// Constructor: Initialize sensor pins, zero wind voltage reference, and sample count
WindSensorRevP::WindSensorRevP(int outPin, int tempPin, float zeroWindVoltage, int numSamples)
    : _outPin(outPin), _tempPin(tempPin), _zeroWindVoltage(zeroWindVoltage), _numSamples(numSamples) {}

// Initialize sensor pins
void WindSensorRevP::begin() {
    pinMode(_outPin, INPUT);
    pinMode(_tempPin, INPUT);
}

// Read wind sensor voltage (ADC -> Voltage conversion)
float WindSensorRevP::readVoltage() {
    float sumVoltage = 0.0;
    for (int i = 0; i < _numSamples; i++) {
        sumVoltage += analogRead(_outPin) * 3.3 / 4095.0;
        delay(10);
    }
    return sumVoltage / _numSamples;
}

// Read temperature sensor in Celsius (ADC -> Temperature conversion)
float WindSensorRevP::readTemperature() {
    float sumTemperature = 0.0;
    for (int i = 0; i < _numSamples; i++) {
        float voltage = analogRead(_tempPin) * 3.3 / 4095.0;
        sumTemperature += (voltage - 0.400) / 0.0195;
        delay(10);
    }
    return sumTemperature / _numSamples;
}

// Calculate wind speed in MPH using given voltage and temperature
float WindSensorRevP::calculateWindSpeed(float volts, float temperature) {
    return pow(((volts - _zeroWindVoltage) / (3.038517 * pow(temperature, 0.115157))) / 0.087288, 3.009364);
}
