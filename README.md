# ESP32 Power Meter
# A cheap AC power meter integrated with ESPhome
![](https://cdn.hackaday.io/images/6278781722196728543.png)

# Overview

## This software is completely based on [ESPHome](https://esphome.io/) and [Home Assistant](https://www.home-assistant.io/). In the unlikely case you don't know what they are, I strongly suggest to follow the links and study them a little.

For most devices/sensors connected to ESP32/ESP8266, the ESPHome integration is already available. In that case, you only need to write the proper .yaml file to use it in your Home Assistant.
However in a few cases, but especially when the sensors are not standard (home made sensors, hacked sensors), you need to write some code. 

Here it comes the funny part, because the procedure I adopted to write this code can be followed not only for this but also for any other similar ESPHome project. 

In this repository you'll find the code I wrote, how to build and install it and many other details. 
On the contrary, the hardware project is here
[esphome-programming-a-very-cheap-power-meter](https://hackaday.io/project/197097-esphome-programming-a-very-cheap-power-meter)

# Code files architecture

As recently (2023) the ESPhome Community suggested, the preferred way to develop a new "external component" (e.g. named "ct_power_clamp") is:

## Create the following directories and files in a folder of your choice

* esphome/components/ct_power_clamp/ct_power_clamp.h
* esphome/components/ct_power_clamp/ct_power_clamp.cpp 
* esphome/components/ct_power_clamp/sensor.py
* __init__.py

You'll find these files in this repository.

## Use the following syntax in your .yaml file:

```
...
external_components:
  - source: components
    components: [ct_power_clamp]
...
```
for the complete .yaml file see [ct_power_clamp_test.yaml](esphome/ct_power_clamp_test.yaml
)

# Prepare the development environment

In addition to knowing something about ESPHome, to build this project you need to:

* install a local instance of [ESPHome Command Line](https://esphome.io/guides/installing_esphome#linux) (the development environment)
* I strongly suggest to install [Visual Studio Code](https://code.visualstudio.com/) but I suppose you can also use your favorite code editor
* if you don't have it yet, install a local instance of [Home Assistant](https://www.home-assistant.io/installation/) in a computer of your choice (I strongly suggest a [dedicated Raspberry PI](https://www.home-assistant.io/installation/#diy-with-raspberry-pi)), It is not mandatory during the development, but you'll need it to show and monitor your measurements.
* download this repository in a folder of your choice (see below)

## Download this repository

Not to mix things, I only suggest you to avoid the same directory where you installed the ESPHome Command Line.
  For instance you could install:
  * The ESPHome Command line into /home/you/esphome
  * This ESPHome component into /home/you/ESP32-power-meter
Therefore:
```
cd /home/you/
git clone https://github.com/guido57/ESP32-power-meter
cd ESP32-power-meter


## Build and upload the ct_power_clamp_test.yaml to your hardware

### Activate the Python virtual environment

```
cd [the esphome directory, where you installed the ESPhome Command Line (see below) ]
source venv/bin/activate
```
### build, install and run the esphome firmware

Connect your ESP32 hardware to your PC via serial port.
After the first upload, you could also upload it via WiFi (OTA).
Then simply run the yaml with esphome

```
cd esphome
esphome run esphome/ct_power_clamp_test.yaml
```
 


 
