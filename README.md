# ESP32 Power Meter
A cheap AC power meter integrated with ESPhome
![](https://cdn.hackaday.io/images/6278781722196728543.png)

### Overview
For most devices/sensors connected to ESP32/ESP8266, the ESPHome integration is already available. In that case, you only need to write the proper .yaml file to use it in your Home Assistant.
However in a few cases, but especially when the sensors are not standard (home made sensors, hacked sensors), you need to write some code. 

Here it comes the funny part, because the procedure I adopted to write this code can be followed not only for this but also for any other similar ESPHome project. 

In this repository you'll find the code I wrote, how to build and install it and many other details. 
On the contrary, the hardware project is here
[esphome-programming-a-very-cheap-power-meter](https://hackaday.io/project/197097-esphome-programming-a-very-cheap-power-meter)

### Code explanation

As recently (2023) suggested by the ESPhome community the preferred way to develop a new "external component" named for instance "ct_power_clamp" is:

## Create the files

* esphome/components/ct_power_clamp/ct_power_clamp.h
* esphome/components/ct_power_clamp/ct_power_clamp.cpp 
* esphome/components/ct_power_clamp/sensor.py
* __init__.py

## Use the following syntax in your .yaml file:

```
external_components:
  - source: components
    components: [ct_power_clamp]
```
for a complete .yaml file see [ct_power_clamp_test.yaml](esphome/ct_power_clamp_test.yaml
)

## Launch the esphome command
Activate the Python virtual environment
```
cd [the esphome directory]
source venv/bin/activate
```
build and install the esphome firmware
```
cd esphome run esphome/ct_power_clamp_test.yaml
```
 


### Using the External Component

