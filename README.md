# Environment Prediction Model

**Real-time ESP32 dashboard** for monitoring **temperature**, **humidity**, and **air quality**. Track live readings with interactive gauges and side-by-side charts, review recent data in a table, and export history as a CSV file for offline analysis.

## Features
- Live updates from ESP32 sensors  
- Interactive gauges for temperature, humidity, and air quality  
- Side-by-side trend charts for temperature and humidity  
- Recent readings table (last 20 entries)  
- Export session data to CSV with one click  

1. Clone the repository:
bash
git clone https://github.com/yourusername/environment-prediction-model.git
2. Open `index.html` in a web browser.
3. Set your ESP32 IP in the JS code:
javascript
const ESP32_IP = "192.168.101.10";
4. Start monitoring and click **Download Excel** to save data.


Dashboard Screenshots
### Real-Time Environmental Data
<p align="center">
  <img src="https://github.com/iarpan1/esp32_environmental_sensor/blob/master/img/Screenshot%202025-08-15%20021342.png?raw=true" alt="Real-Time Data" width="600"/>
</p>

Historical Data Table

<p align="center">
  <img src="https://github.com/iarpan1/esp32_environmental_sensor/blob/master/img/Screenshot%202025-08-15%20021541.png?raw=true" alt="Historical Table" width="600"/>
</p>

### **MQ-135 Calibration and Voltage Details**

1. **Why we calibrate MQ-135**
   The MQ-135 is a gas sensor that measures air quality (CO₂, NH₃, alcohol, VOCs). Its **raw output is an analog voltage**, which depends on the gas concentration and the sensor’s resistance (**RS**) relative to the sensor’s internal load resistance (**RL**). Calibration ensures that the voltage-to-gas concentration mapping is accurate under your environmental conditions.

2. **Typical Calibration Process**

* **Preheating / burn-in**: MQ-135 requires **24–48 hours of continuous power** when first used. This stabilizes the **heating element** and the sensitive layer inside the sensor.
* **Baseline voltage**: After preheating, the sensor’s analog output stabilizes at a certain **baseline voltage (Vout)** in clean air. This baseline is used for reference to calculate air quality changes.
* **Why wait 2 days**: If you use it immediately, the sensor readings fluctuate a lot because the sensitive layer hasn’t stabilized. After 2 days of continuous operation, the readings become stable, giving **reliable and repeatable voltages**.

3. **Why 5V Supply**

* MQ-135 is designed to operate at **5V** (Vcc).
* The **heater inside the sensor** needs 5V to maintain the right temperature for the sensitive layer to react properly to gases.
* Using a lower voltage may result in **weaker sensitivity**, slower response, and inaccurate readings. Using higher voltage may **damage the sensor**.

4. **Voltage Reading Behavior**

* After preheating, you’ll see the **analog voltage settle around a baseline (usually 0.3–2.0 V depending on conditions)**.
* As gas concentration increases, the voltage changes proportionally.
* This stable voltage after 2 days is what you use in your **calibration formula** to convert voltage → gas concentration (PPM).
