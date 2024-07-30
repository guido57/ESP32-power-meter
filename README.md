# ESP32 Power Meter
A cheap AC power meter integrated with ESPhome
![](https://cdn.hackaday.io/images/6278781722196728543.png)

# Overview

## This software is completely based on [ESPHome](https://esphome.io/) and [Home Assistant](https://www.home-assistant.io/). In the unlikely case you don't know what they are, i strongly suggest to follow the links and study them a little.

For most devices/sensors connected to ESP32/ESP8266, the ESPHome integration is already available. In that case, you only need to write the proper .yaml file to use it in your Home Assistant.
However in a few cases, but especially when the sensors are not standard (home made sensors, hacked sensors), you need to write some code. 

Here it comes the funny part, because the procedure I adopted to write this code can be followed not only for this but also for any other similar ESPHome project. 

In this repository you'll find the code I wrote, how to build and install it and many other details. 
On the contrary, the hardware project is here
[esphome-programming-a-very-cheap-power-meter](https://hackaday.io/project/197097-esphome-programming-a-very-cheap-power-meter)

# Code explanation

As recently (2023) the ESPhome Community suggested, the preferred way to develop a new "external component" (e.g. named "ct_power_clamp") is:

## Create the following directories and files in a folder of your choice

* esphome/components/ct_power_clamp/ct_power_clamp.h
* esphome/components/ct_power_clamp/ct_power_clamp.cpp 
* esphome/components/ct_power_clamp/sensor.py
* __init__.py

## Use the following syntax in your .yaml file:

```
...
external_components:
  - source: components
    components: [ct_power_clamp]
...
```
for a complete .yaml file see [ct_power_clamp_test.yaml](esphome/ct_power_clamp_test.yaml
)

## Build and install the esphome firmware

### Activate the Python virtual environment

```
cd [the esphome directory]
source venv/bin/activate
```
### build and install the esphome firmware
```
cd esphome run esphome/ct_power_clamp_test.yaml
```
 
# Prepare the development environment

PREREQUISITES
In addition to knowing something about ESPHome, to build this project you need to:

install a local instance of ESPhome Command Line (the development environment)
install Visual Studio Code or use your code editor of choice
install a local instance of Home Assistant in a computer of your choice (I strongly suggest a dedicated Raspberry PI)

