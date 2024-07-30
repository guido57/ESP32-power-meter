import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import  sensor, adc
from esphome.const import (
    CONF_ID, 
    CONF_NAME, 
    CONF_VOLTAGE, 
    CONF_CURRENT, 
    CONF_UPDATE_INTERVAL, 
    CONF_SENSOR_ID, 
    UNIT_VOLT, 
    UNIT_AMPERE, 
    UNIT_WATT,
    ICON_CURRENT_AC, 
    ICON_POWER,
    ICON_FLASH,
)

# Define the namespace for the component
ct_power_clamp_ns = cg.esphome_ns.namespace("ctpowerclamp")
CTPowerClampComponent = ct_power_clamp_ns.class_(
    "CTPowerClampComponent", cg.PollingComponent 
)

# Define configuration options
CONF_VOLTAGE_SENSOR = 'voltage_sensor'
CONF_CURRENT1_SENSOR = 'current1_sensor'
CONF_CURRENT2_SENSOR = 'current2_sensor'
CONF_POWER1_SENSOR = 'power1_sensor'
CONF_POWER2_SENSOR = 'power2_sensor'
CONF_SAMPLE_DURATION = 'sample_duration'

CONFIG_SCHEMA = cv.Schema({
    cv.GenerateID(): cv.declare_id(CTPowerClampComponent),
    cv.Optional(CONF_UPDATE_INTERVAL, default='60s'): cv.update_interval,
    cv.Optional(CONF_SAMPLE_DURATION, default="200ms" ): cv.positive_time_period_milliseconds,
    cv.Required(CONF_VOLTAGE_SENSOR): sensor.sensor_schema(unit_of_measurement=UNIT_VOLT, icon=ICON_FLASH, accuracy_decimals=1).extend({
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_SENSOR_ID): cv.use_id(sensor.Sensor),
    }),
    cv.Required(CONF_CURRENT1_SENSOR): sensor.sensor_schema(unit_of_measurement=UNIT_AMPERE, icon=ICON_CURRENT_AC, accuracy_decimals=1).extend({
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_SENSOR_ID): cv.use_id(sensor.Sensor),
    }),
    cv.Required(CONF_CURRENT2_SENSOR): sensor.sensor_schema(unit_of_measurement=UNIT_AMPERE, icon=ICON_CURRENT_AC, accuracy_decimals=1).extend({
        cv.Required(CONF_NAME): cv.string,
        cv.Required(CONF_SENSOR_ID): cv.use_id(sensor.Sensor),
    }),
    cv.Required(CONF_POWER1_SENSOR): sensor.sensor_schema(unit_of_measurement=UNIT_WATT, icon=ICON_POWER, accuracy_decimals=1).extend({
        cv.Required(CONF_NAME): cv.string,
    }),
    cv.Required(CONF_POWER2_SENSOR): sensor.sensor_schema(unit_of_measurement=UNIT_WATT, icon=ICON_POWER, accuracy_decimals=1).extend({
        cv.Required(CONF_NAME): cv.string,
    }),
    
}).extend(cv.polling_component_schema('60s'))


async def to_code(config):

    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    
    # Set the update interval
    cg.add(var.set_update_interval(config[CONF_UPDATE_INTERVAL]))

    # Set the sample duration
    cg.add(var.set_sample_duration(config[CONF_SAMPLE_DURATION]))

    # Set up the voltage sensor
    voltage_sensor = await sensor.new_sensor(config[CONF_VOLTAGE_SENSOR])
    cg.add(var.set_voltage_sensor(voltage_sensor))
    
    # Set up the voltage sensor source (i.e. the adc sensor where the voltage signal is connected to)
    sens = await cg.get_variable(config[CONF_VOLTAGE_SENSOR][CONF_SENSOR_ID])
    cg.add(var.set_voltage_sensor_source(sens))

    # Set up the current1 sensor
    current1_sensor = await sensor.new_sensor(config[CONF_CURRENT1_SENSOR])
    cg.add(var.set_current1_sensor(current1_sensor))

    # Set up the current1 sensor source (i.e. the adc sensor where the current1 signal is connected to)
    sens = await cg.get_variable(config[CONF_CURRENT1_SENSOR][CONF_SENSOR_ID])
    cg.add(var.set_current1_sensor_source(sens))

    # Set up the current2 sensor
    current2_sensor = await sensor.new_sensor(config[CONF_CURRENT2_SENSOR])
    cg.add(var.set_current2_sensor(current2_sensor))

    # Set up the current2 sensor source (i.e. the adc sensor where the current2 signal is connected to)
    sens = await cg.get_variable(config[CONF_CURRENT2_SENSOR][CONF_SENSOR_ID])
    cg.add(var.set_current2_sensor_source(sens))

    # Set up the power1 sensor
    power1_sensor = await sensor.new_sensor(config[CONF_POWER1_SENSOR])
    cg.add(var.set_power1_sensor(power1_sensor))
    
    # Set up the power1 sensor
    power2_sensor = await sensor.new_sensor(config[CONF_POWER2_SENSOR])
    cg.add(var.set_power2_sensor(power2_sensor))
