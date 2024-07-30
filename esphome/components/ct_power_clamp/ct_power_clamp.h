#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/adc/adc_sensor.h"

#include <cinttypes>

namespace esphome {
namespace ctpowerclamp {

class CTPowerClampComponent : public PollingComponent {
 public:
  void update() override;
  void loop() override;
  void setup() override;
  void dump_config() override;
  float get_setup_priority() const override;
  
  void set_sample_duration(uint32_t sample_duration) { sample_duration_ = sample_duration;   ESP_LOGD("ctpowerclamp", "Set sample_duration_=%d ms ", sample_duration_);}
  void set_voltage_sensor(sensor::Sensor * voltage_sensor) { voltage_sensor_ = voltage_sensor; }
  void set_voltage_sensor_source(sensor::Sensor * voltage_sensor_source) { voltage_sensor_source_ = (adc::ADCSensor *) voltage_sensor_source; }
  void set_current1_sensor(sensor::Sensor *current_sensor) { current1_sensor_ = current_sensor; }
  void set_current2_sensor(sensor::Sensor *current_sensor) { current2_sensor_ = current_sensor; }
  void set_current1_sensor_source(sensor::Sensor * current1_sensor_source) { current1_sensor_source_ = (adc::ADCSensor *) current1_sensor_source; }
  void set_current2_sensor_source(sensor::Sensor * current2_sensor_source) { current2_sensor_source_ = (adc::ADCSensor *) current2_sensor_source; }
  void set_power1_sensor(sensor::Sensor *power_sensor) { power1_sensor_ = power_sensor; }
  void set_power2_sensor(sensor::Sensor *power_sensor) { power2_sensor_ = power_sensor; }
  
 protected:
  // High Frequency loop() requester used during sampling phase.
  HighFrequencyLoopRequester high_freq_;

  uint32_t sample_duration_; 
  sensor::Sensor *voltage_sensor_{nullptr};
  sensor::Sensor *current1_sensor_{nullptr};
  sensor::Sensor *power1_sensor_{nullptr};
  sensor::Sensor *current2_sensor_{nullptr};
  sensor::Sensor *power2_sensor_{nullptr};

  adc::ADCSensor * voltage_sensor_source_{nullptr};
  adc::ADCSensor * current1_sensor_source_{nullptr};
  adc::ADCSensor * current2_sensor_source_{nullptr};

  float sample_voltage_sum_ = 0.0f;
  float sample_squared_voltage_sum_ = 0.0f;
  float sample_current1_sum_ = 0.0f;
  float sample_squared_current1_sum_ = 0.0f;
  float sample_power1_sum_ = 0.0f;
  float sample_current2_sum_ = 0.0f;
  float sample_squared_current2_sum_ = 0.0f;
  float sample_power2_sum_ = 0.0f;
  
  uint32_t num_samples_ = 0;
  bool is_sampling_ = false;

};

}  // namespace ct_power_clamp
}  // namespace esphome
