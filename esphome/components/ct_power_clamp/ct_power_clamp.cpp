#include "ct_power_clamp.h"

#include "esphome/core/log.h"
#include "esphome/core/hal.h"

namespace esphome {
namespace ctpowerclamp {

static const char *const TAG = "ctpowerclamp";

void CTPowerClampComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up CTPowerClamp...");
  delay(1);
}

void CTPowerClampComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "CTPowerClamp:");

  LOG_UPDATE_INTERVAL(this);

  LOG_SENSOR("  ", "Voltage", this->voltage_sensor_);
  LOG_SENSOR("  ", "Current1", this->current1_sensor_);
  LOG_SENSOR("  ", "Power1", this->power1_sensor_);
  LOG_SENSOR("  ", "Current2", this->current2_sensor_);
  LOG_SENSOR("  ", "Power2", this->power2_sensor_);
}

float CTPowerClampComponent::get_setup_priority() const { return setup_priority::DATA; }

void CTPowerClampComponent::update() {

  // This function only starts the sampling phase, the actual sampling happens in loop().

  // Request a high loop() execution interval during sampling phase.
  this->high_freq_.start();

  // set the function to be called at the end of the sampling period

  this->set_timeout("read", this->sample_duration_, [this]() {
        
    this->is_sampling_ = false;
    this->high_freq_.stop();

    if (this->num_samples_ == 0) {
      // Shouldn't happen, but let's not crash if it does.
      //this->publish_state(NAN);
      return;
    }
    // calculate and publish voltage rms 
    const float rms_ac_dc_squared = this->sample_squared_voltage_sum_ / this->num_samples_;
    const float rms_dc = this->sample_voltage_sum_ / this->num_samples_;
    const float rms_ac_squared = rms_ac_dc_squared - rms_dc * rms_dc; // remove the dc component
    float rms_ac = 0;
    if (rms_ac_squared > 0)
      rms_ac = std::sqrt(rms_ac_squared);
    ESP_LOGD(TAG, "'%s' - Raw Voltage AC Value: %.6fV Voltage ACDC squared Component: %.6f Voltage DC Component: %.6f using %" PRIu32 " samples (%" PRIu32 " SPS) ",
             this->voltage_sensor_->get_name().c_str(), rms_ac, rms_ac_dc_squared, rms_dc, this->num_samples_, 1000 * this->num_samples_ / this->sample_duration_);
    this->voltage_sensor_->publish_state(rms_ac);
  
    // calculate and publish current1 rms 
    const float rms_i1_ac_dc_squared = this->sample_squared_current1_sum_ / this->num_samples_;
    const float rms_i1_dc = this->sample_current1_sum_ / this->num_samples_;
    const float rms_i1_ac_squared = rms_i1_ac_dc_squared - rms_i1_dc * rms_i1_dc; // remove the dc component
    float rms_i1_ac = 0;
    if (rms_i1_ac_squared > 0)
      rms_i1_ac = std::sqrt(rms_i1_ac_squared);
    ESP_LOGD(TAG, "'%s' - Raw Current1 AC Value: %.6fA Current1 ACDC squared Component: %.6f Current1 DC Component: %.6f using %" PRIu32 " samples (%" PRIu32 " SPS)",
             this->current1_sensor_->get_name().c_str(), rms_i1_ac, rms_i1_ac_dc_squared, rms_i1_dc, this->num_samples_, 1000 * this->num_samples_ / this->sample_duration_);
    this->current1_sensor_->publish_state(rms_i1_ac);
  
    // calculate and publish power1 rms 
    const float rms_p1_ac_dc = this->sample_power1_sum_ / this->num_samples_;
    const float rms_p1_dc = rms_dc * rms_i1_dc;
    const float rms_p1_ac = rms_p1_ac_dc - rms_p1_dc ; // remove the dc component
    ESP_LOGD(TAG, "'%s' - Raw Power1 AC Value: %.3fW Power1 ACDC Component: %.3fW Power1 DC Component: %.3fW using %" PRIu32 " samples (%" PRIu32 " SPS)",
             this->power1_sensor_->get_name().c_str(), rms_p1_ac, rms_p1_ac_dc, rms_p1_dc, this->num_samples_, 1000 * this->num_samples_ / this->sample_duration_);
    this->power1_sensor_->publish_state(rms_p1_ac);
  
  // calculate and publish current2 rms 
    const float rms_i2_ac_dc_squared = this->sample_squared_current2_sum_ / this->num_samples_;
    const float rms_i2_dc = this->sample_current2_sum_ / this->num_samples_;
    const float rms_i2_ac_squared = rms_i2_ac_dc_squared - rms_i2_dc * rms_i2_dc; // remove the dc component
    float rms_i2_ac = 0;
    if (rms_i2_ac_squared > 0)
      rms_i2_ac = std::sqrt(rms_i2_ac_squared);
    ESP_LOGD(TAG, "'%s' - Raw Current2 AC Value: %.6fA Current2 ACDC squared Component: %.6f Current2 DC Component: %.6f using %" PRIu32 " samples (%" PRIu32 " SPS)",
             this->current2_sensor_->get_name().c_str(), rms_i2_ac, rms_i2_ac_dc_squared, rms_i2_dc, this->num_samples_, 1000 * this->num_samples_ / this->sample_duration_);
    this->current2_sensor_->publish_state(rms_i2_ac);
   
    // calculate and publish power2 rms 
    const float rms_p2_ac_dc = this->sample_power2_sum_ / this->num_samples_;
    const float rms_p2_dc = rms_dc * rms_i2_dc;
    const float rms_p2_ac = rms_p2_ac_dc - rms_p2_dc ; // remove the dc component
    ESP_LOGD(TAG, "'%s' - Raw Power2 AC Value: %.3fW Power2 ACDC Component: %.3fW Power2 DC Component: %.3fW using %" PRIu32 " samples (%" PRIu32 " SPS)",
             this->power2_sensor_->get_name().c_str(), rms_p2_ac, rms_p2_ac_dc, rms_p2_dc, this->num_samples_, 1000 * this->num_samples_ / this->sample_duration_);
    this->power2_sensor_->publish_state(rms_p2_ac);
  

  }); 

  // Reset sampling accumulators
  this->num_samples_ = 0;
  this->sample_voltage_sum_ = 0.0f;
  this->sample_squared_voltage_sum_ = 0.0f;
  this->sample_current1_sum_ = 0.0f;
  this->sample_squared_current1_sum_ = 0.0f;
  this->sample_current2_sum_ = 0.0f;
  this->sample_squared_current2_sum_ = 0.0f;
  this->sample_power1_sum_ = 0.0f;
  this->sample_power2_sum_ = 0.0f;
  
  this->is_sampling_ = true;
  
  this->status_clear_warning();
}
 
void CTPowerClampComponent::loop() {
  if (!this->is_sampling_)
    return;

  // Get a single voltage sample
  float value_v = this->voltage_sensor_source_->sample();
  if (std::isnan(value_v)){
    ESP_LOGD(TAG, "this->voltage_sensor_source_->sample() is nan");
    return;
  }
  this->sample_voltage_sum_ += value_v;
  this->sample_squared_voltage_sum_ += value_v * value_v;

  // Get a single current1 sample
  float value_i1 = this->current1_sensor_source_->sample();
  if (std::isnan(value_i1)){
    ESP_LOGD(TAG, "this->current1_sensor_source_->sample() is nan");
    return;
  }
  this->sample_current1_sum_ += value_i1;
  this->sample_squared_current1_sum_ += value_i1 * value_i1;

// Get a single current2 sample
  float value_i2 = this->current2_sensor_source_->sample();
  if (std::isnan(value_i2)){
    ESP_LOGD(TAG, "this->current2_sensor_source_->sample() is nan");
    return;
  }
  this->sample_current2_sum_ += value_i2;
  this->sample_squared_current2_sum_ += value_i2 * value_i2;

  // Calculate a single power1 sample
  this->sample_power1_sum_ += value_v * value_i1;
  
  // Calculate a single power2 sample
  this->sample_power2_sum_ += value_v * value_i2;

  this->num_samples_++;
}

}  // namespace ctpowerclamp
}  // namespace esphome
