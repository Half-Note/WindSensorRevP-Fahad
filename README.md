# WindSensorRevP Library
![Static Badge](https://img.shields.io/badge/version-v1.0-blue)
[![ChatGPT](https://img.shields.io/badge/ChatGPT-74aa9c?logo=openai&logoColor=white)](#)

## Overview
The `WindSensorRevP` library is designed to interface with the **Wind Sensor Rev. P**, allowing precise measurement of **wind speed** and **temperature** using an ESP32 or Arduino. This library processes **analog voltage readings** and applies a calibrated regression formula to calculate wind speed accurately. The library is based on the original code and instructions provided by the manufacturer: Modern Device.

## Features
- **Reads wind speed and temperature** using the Wind Sensor Rev. P.
- **Supports analog voltage readings** from the sensor.
- **Includes a zero-wind voltage calibration** process for accuracy.
- **Optimized for ESP32 and Arduino** platforms.
- **Implements software-based temperature compensation**.

## Installation

### Prerequisites
- **C++11 support**
- **Arduino IDE** (>= 2.1.6)

### Steps:
1. Download the latest ZIP release from GitHub.
2. Open **Arduino IDE** and navigate to **Sketch → Include Library → Add .ZIP Library...**
3. Select the downloaded ZIP file.
4. The library will now be available under the **Examples** section in the Arduino IDE.

## Zero Wind Voltage Calibration
Before using the sensor, you must determine the **zero wind voltage** (the sensor's output voltage in still air). Follow these steps:

1. Place the sensor on the edge of a table with a glass covering its tip.
2. Allow the sensor to stabilize for at least **40 seconds**.
3. Record the stabilized voltage output.
4. Replace the **`zeroWindVoltage`** value in the example code with your measured value.

Typical values range between **1.327V and 1.380V**, with an average of **1.346V** at room temperature (~25°C).

## Usage Example

```cpp
#include <WindSensorRevP.h>

const int outPin = 2;    // Wind sensor analog pin
const int tempPin = 4;   // Temperature sensor analog pin
const float zeroWindVoltage = 1.346; // Replace with your calibrated value
const int numSamples = 50; // Number of samples for accuracy

WindSensorRevP windSensor(outPin, tempPin, zeroWindVoltage, numSamples);

void setup() {
    Serial.begin(115200);
    windSensor.begin();
}

void loop() {
    float windVoltage = windSensor.readVoltage();
    float temperature = windSensor.readTemperature();
    float windSpeed = windSensor.calculateWindSpeed(windVoltage, temperature);

    Serial.print("Wind Voltage: ");
    Serial.print(windVoltage, 3);
    Serial.print("\tTemperature: ");
    Serial.print(temperature, 2);
    Serial.print(" C\tWind Speed: ");
    Serial.print(windSpeed, 2);
    Serial.println(" MPH");

    delay(1000);
}
```

## Wind Speed Calculation Formula
The library applies a regression model to compute wind speed from the sensor's output voltage:

```
WS_MPH = (((Volts - ZeroWind_V) / (3.038517 * (Temp_C ^ 0.115157))) / 0.087288) ^ 3.009364
```

where:
- **WS_MPH**: Wind speed in miles per hour.
- **Volts**: Sensor output voltage.
- **Temp_C**: Temperature in degrees Celsius.
- **ZeroWind_V**: Zero wind voltage (determined through calibration).

### Temperature Calculation
The onboard temperature sensor follows this equation:

```
Tambient = (Vout - 0.400) / 0.0195
```
where:
- **Vout** is the sensor's output voltage.
- **0.400V** is the sensor's output at 0°C.
- **0.0195V/°C** is the temperature coefficient.

## Notes and Limitations
- The wind speed equation is optimized for wind speeds up to **50 MPH**.
- Temperature compensation is based on a dataset spanning **7.7°C to 34°C**.
- Performance at extreme temperatures or high wind speeds may vary slightly due to sensor limitations.

## License
This library is licensed under the **MIT License**.

---

For more details, visit the project's GitHub repository or contribute improvements by submitting a pull request!

