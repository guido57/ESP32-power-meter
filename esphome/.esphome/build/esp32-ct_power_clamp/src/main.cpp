// Auto generated code by esphome
// ========== AUTO GENERATED INCLUDE BLOCK BEGIN ===========
#include "esphome.h"
using namespace esphome;
using std::isnan;
using std::min;
using std::max;
using namespace sensor;
logger::Logger *logger_logger_id;
web_server_base::WebServerBase *web_server_base_webserverbase_id;
captive_portal::CaptivePortal *captive_portal_captiveportal_id;
wifi::WiFiComponent *wifi_wificomponent_id;
mdns::MDNSComponent *mdns_mdnscomponent_id;
esphome::ESPHomeOTAComponent *esphome_esphomeotacomponent_id;
safe_mode::SafeModeComponent *safe_mode_safemodecomponent_id;
api::APIServer *api_apiserver_id;
using namespace api;
preferences::IntervalSyncer *preferences_intervalsyncer_id;
ctpowerclamp::CTPowerClampComponent *my_ct_power_clamp;
sensor::Sensor *voltage;
sensor::MultiplyFilter *sensor_multiplyfilter_id;
template_::TemplateSensor *calculated_cos_fi_1;
sensor::MultiplyFilter *sensor_multiplyfilter_id_6;
adc::ADCSensor *adc_voltage_sensor;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_id;
adc::ADCSensor *adc_current1_sensor;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_id_2;
adc::ADCSensor *adc_current2_sensor;
esp32::ESP32InternalGPIOPin *esp32_esp32internalgpiopin_id_3;
sensor::Sensor *current1;
sensor::MultiplyFilter *sensor_multiplyfilter_id_2;
sensor::Sensor *sensor_sensor_id;
sensor::MultiplyFilter *sensor_multiplyfilter_id_3;
sensor::Sensor *power1;
sensor::MultiplyFilter *sensor_multiplyfilter_id_4;
sensor::Sensor *sensor_sensor_id_2;
sensor::MultiplyFilter *sensor_multiplyfilter_id_5;
#define yield() esphome::yield()
#define millis() esphome::millis()
#define micros() esphome::micros()
#define delay(x) esphome::delay(x)
#define delayMicroseconds(x) esphome::delayMicroseconds(x)
// ========== AUTO GENERATED INCLUDE BLOCK END ==========="

void setup() {
  // ========== AUTO GENERATED CODE BEGIN ===========
  // async_tcp:
  //   {}
  // esphome:
  //   name: esp32-ct_power_clamp
  //   friendly_name: ESP32-CT-Power-Clamp
  //   build_path: build/esp32-ct_power_clamp
  //   area: ''
  //   platformio_options: {}
  //   includes: []
  //   libraries: []
  //   name_add_mac_suffix: false
  //   min_version: 2024.6.6
  App.pre_setup("esp32-ct_power_clamp", "ESP32-CT-Power-Clamp", "", "", __DATE__ ", " __TIME__, false);
  // sensor:
  // logger:
  //   id: logger_logger_id
  //   baud_rate: 115200
  //   tx_buffer_size: 512
  //   deassert_rts_dtr: false
  //   hardware_uart: UART0
  //   level: DEBUG
  //   logs: {}
  logger_logger_id = new logger::Logger(115200, 512);
  logger_logger_id->set_uart_selection(logger::UART_SELECTION_UART0);
  logger_logger_id->pre_setup();
  logger_logger_id->set_component_source("logger");
  App.register_component(logger_logger_id);
  // web_server_base:
  //   id: web_server_base_webserverbase_id
  web_server_base_webserverbase_id = new web_server_base::WebServerBase();
  web_server_base_webserverbase_id->set_component_source("web_server_base");
  App.register_component(web_server_base_webserverbase_id);
  // captive_portal:
  //   id: captive_portal_captiveportal_id
  //   web_server_base_id: web_server_base_webserverbase_id
  captive_portal_captiveportal_id = new captive_portal::CaptivePortal(web_server_base_webserverbase_id);
  captive_portal_captiveportal_id->set_component_source("captive_portal");
  App.register_component(captive_portal_captiveportal_id);
  // wifi:
  //   networks:
  //   - ssid: !secret 'wifi_ssid'
  //     password: !secret 'wifi_password'
  //     id: wifi_wifiap_id
  //     priority: 0.0
  //   - ssid: !secret 'wifi_ssid_sallynet'
  //     password: !secret 'wifi_password_sallynet'
  //     id: wifi_wifiap_id_2
  //     priority: 0.0
  //   ap:
  //     ssid: Esphome-Web-7B99D8
  //     password: E8LkyX7IExso
  //     id: wifi_wifiap_id_3
  //     ap_timeout: 1min
  //   id: wifi_wificomponent_id
  //   domain: .local
  //   reboot_timeout: 15min
  //   power_save_mode: LIGHT
  //   fast_connect: false
  //   passive_scan: false
  //   enable_on_boot: true
  //   use_address: esp32-ct_power_clamp.local
  wifi_wificomponent_id = new wifi::WiFiComponent();
  wifi_wificomponent_id->set_use_address("esp32-ct_power_clamp.local");
  {
  wifi::WiFiAP wifi_wifiap_id = wifi::WiFiAP();
  wifi_wifiap_id.set_ssid("TIM-18373419");
  wifi_wifiap_id.set_password("K9giYCTW4ryRS1MT26oIs7BG");
  wifi_wifiap_id.set_priority(0.0f);
  wifi_wificomponent_id->add_sta(wifi_wifiap_id);
  }
  {
  wifi::WiFiAP wifi_wifiap_id_2 = wifi::WiFiAP();
  wifi_wifiap_id_2.set_ssid("sallynet");
  wifi_wifiap_id_2.set_password("sally866");
  wifi_wifiap_id_2.set_priority(0.0f);
  wifi_wificomponent_id->add_sta(wifi_wifiap_id_2);
  }
  {
  wifi::WiFiAP wifi_wifiap_id_3 = wifi::WiFiAP();
  wifi_wifiap_id_3.set_ssid("Esphome-Web-7B99D8");
  wifi_wifiap_id_3.set_password("E8LkyX7IExso");
  wifi_wificomponent_id->set_ap(wifi_wifiap_id_3);
  }
  wifi_wificomponent_id->set_ap_timeout(60000);
  wifi_wificomponent_id->set_reboot_timeout(900000);
  wifi_wificomponent_id->set_power_save_mode(wifi::WIFI_POWER_SAVE_LIGHT);
  wifi_wificomponent_id->set_fast_connect(false);
  wifi_wificomponent_id->set_passive_scan(false);
  wifi_wificomponent_id->set_enable_on_boot(true);
  wifi_wificomponent_id->set_component_source("wifi");
  App.register_component(wifi_wificomponent_id);
  // mdns:
  //   id: mdns_mdnscomponent_id
  //   disabled: false
  //   services: []
  mdns_mdnscomponent_id = new mdns::MDNSComponent();
  mdns_mdnscomponent_id->set_component_source("mdns");
  App.register_component(mdns_mdnscomponent_id);
  // ota:
  // ota.esphome:
  //   platform: esphome
  //   id: esphome_esphomeotacomponent_id
  //   version: 2
  //   port: 3232
  esphome_esphomeotacomponent_id = new esphome::ESPHomeOTAComponent();
  esphome_esphomeotacomponent_id->set_port(3232);
  esphome_esphomeotacomponent_id->set_component_source("esphome.ota");
  App.register_component(esphome_esphomeotacomponent_id);
  // safe_mode:
  //   id: safe_mode_safemodecomponent_id
  //   boot_is_good_after: 1min
  //   disabled: false
  //   num_attempts: 10
  //   reboot_timeout: 5min
  safe_mode_safemodecomponent_id = new safe_mode::SafeModeComponent();
  safe_mode_safemodecomponent_id->set_component_source("safe_mode");
  App.register_component(safe_mode_safemodecomponent_id);
  if (safe_mode_safemodecomponent_id->should_enter_safe_mode(10, 300000, 60000)) return;
  // api:
  //   encryption:
  //     key: iPyz4GzKx/80YguhxY0bAZNj3H8velxh9Ls2DQQ+fjo=
  //   id: api_apiserver_id
  //   port: 6053
  //   password: ''
  //   reboot_timeout: 15min
  api_apiserver_id = new api::APIServer();
  api_apiserver_id->set_component_source("api");
  App.register_component(api_apiserver_id);
  api_apiserver_id->set_port(6053);
  api_apiserver_id->set_password("");
  api_apiserver_id->set_reboot_timeout(900000);
  api_apiserver_id->set_noise_psk({136, 252, 179, 224, 108, 202, 199, 255, 52, 98, 11, 161, 197, 141, 27, 1, 147, 99, 220, 127, 47, 122, 92, 97, 244, 187, 54, 13, 4, 62, 126, 58});
  // esp32:
  //   board: esp32dev
  //   framework:
  //     version: 2.0.5
  //     source: ~3.20005.0
  //     platform_version: platformio/espressif32@5.4.0
  //     type: arduino
  //   flash_size: 4MB
  //   variant: ESP32
  // preferences:
  //   id: preferences_intervalsyncer_id
  //   flash_write_interval: 60s
  preferences_intervalsyncer_id = new preferences::IntervalSyncer();
  preferences_intervalsyncer_id->set_write_interval(60000);
  preferences_intervalsyncer_id->set_component_source("preferences");
  App.register_component(preferences_intervalsyncer_id);
  // external_components:
  //   - source:
  //       path: components
  //       type: local
  //     components:
  //     - ct_power_clamp
  //     refresh: 1d
  // sensor.ct_power_clamp:
  //   platform: ct_power_clamp
  //   id: my_ct_power_clamp
  //   update_interval: 10s
  //   sample_duration: 6000ms
  //   voltage_sensor:
  //     sensor_id: adc_voltage_sensor
  //     id: voltage
  //     name: Voltage
  //     filters:
  //     - multiply: 1099.0
  //       type_id: sensor_multiplyfilter_id
  //     accuracy_decimals: 0
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: V
  //     icon: mdi:flash
  //   current1_sensor:
  //     name: Current1
  //     id: current1
  //     sensor_id: adc_current1_sensor
  //     accuracy_decimals: 3
  //     filters:
  //     - multiply: 40.72
  //       type_id: sensor_multiplyfilter_id_2
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: A
  //     icon: mdi:current-ac
  //   current2_sensor:
  //     sensor_id: adc_current2_sensor
  //     name: Current2
  //     accuracy_decimals: 3
  //     filters:
  //     - multiply: 40.72
  //       type_id: sensor_multiplyfilter_id_3
  //     disabled_by_default: false
  //     id: sensor_sensor_id
  //     force_update: false
  //     unit_of_measurement: A
  //     icon: mdi:current-ac
  //   power1_sensor:
  //     name: Power1
  //     id: power1
  //     accuracy_decimals: 0
  //     filters:
  //     - multiply: 41017.0
  //       type_id: sensor_multiplyfilter_id_4
  //     disabled_by_default: false
  //     force_update: false
  //     unit_of_measurement: W
  //     icon: mdi:power
  //   power2_sensor:
  //     name: Power2
  //     accuracy_decimals: 0
  //     filters:
  //     - multiply: 41017.0
  //       type_id: sensor_multiplyfilter_id_5
  //     disabled_by_default: false
  //     id: sensor_sensor_id_2
  //     force_update: false
  //     unit_of_measurement: W
  //     icon: mdi:power
  my_ct_power_clamp = new ctpowerclamp::CTPowerClampComponent();
  my_ct_power_clamp->set_update_interval(10000);
  my_ct_power_clamp->set_component_source("ct_power_clamp.sensor");
  App.register_component(my_ct_power_clamp);
  my_ct_power_clamp->set_update_interval(10000);
  my_ct_power_clamp->set_sample_duration(6000);
  voltage = new sensor::Sensor();
  App.register_sensor(voltage);
  voltage->set_name("Voltage");
  voltage->set_object_id("voltage");
  voltage->set_disabled_by_default(false);
  voltage->set_icon("mdi:flash");
  voltage->set_unit_of_measurement("V");
  voltage->set_accuracy_decimals(0);
  voltage->set_force_update(false);
  sensor_multiplyfilter_id = new sensor::MultiplyFilter(1099.0f);
  voltage->set_filters({sensor_multiplyfilter_id});
  my_ct_power_clamp->set_voltage_sensor(voltage);
  // sensor.template:
  //   platform: template
  //   id: calculated_cos_fi_1
  //   name: Calculate cos(phi) 1
  //   accuracy_decimals: 2
  //   filters:
  //   - multiply: 41017.0
  //     type_id: sensor_multiplyfilter_id_6
  //   update_interval: 10s
  //   lambda: !lambda |-
  //     return id(power1).state / ( id(voltage).state * id(current1).state  );
  //   disabled_by_default: false
  //   force_update: false
  calculated_cos_fi_1 = new template_::TemplateSensor();
  App.register_sensor(calculated_cos_fi_1);
  calculated_cos_fi_1->set_name("Calculate cos(phi) 1");
  calculated_cos_fi_1->set_object_id("calculate_cos_phi__1");
  calculated_cos_fi_1->set_disabled_by_default(false);
  calculated_cos_fi_1->set_accuracy_decimals(2);
  calculated_cos_fi_1->set_force_update(false);
  sensor_multiplyfilter_id_6 = new sensor::MultiplyFilter(41017.0f);
  calculated_cos_fi_1->set_filters({sensor_multiplyfilter_id_6});
  calculated_cos_fi_1->set_update_interval(10000);
  calculated_cos_fi_1->set_component_source("template.sensor");
  App.register_component(calculated_cos_fi_1);
  // sensor.adc:
  //   platform: adc
  //   pin:
  //     number: 34
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_id
  //     inverted: false
  //     ignore_pin_validation_error: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: adc_voltage_sensor
  //   disabled_by_default: false
  //   force_update: false
  //   unit_of_measurement: V
  //   accuracy_decimals: 2
  //   device_class: voltage
  //   state_class: measurement
  //   raw: false
  //   attenuation: 0db
  //   samples: 1
  //   update_interval: 60s
  //   name: adc_voltage_sensor
  //   internal: true
  adc_voltage_sensor = new adc::ADCSensor();
  adc_voltage_sensor->set_update_interval(60000);
  adc_voltage_sensor->set_component_source("adc.sensor");
  App.register_component(adc_voltage_sensor);
  App.register_sensor(adc_voltage_sensor);
  adc_voltage_sensor->set_name("adc_voltage_sensor");
  adc_voltage_sensor->set_object_id("adc_voltage_sensor");
  adc_voltage_sensor->set_disabled_by_default(false);
  adc_voltage_sensor->set_internal(true);
  adc_voltage_sensor->set_device_class("voltage");
  adc_voltage_sensor->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  adc_voltage_sensor->set_unit_of_measurement("V");
  adc_voltage_sensor->set_accuracy_decimals(2);
  adc_voltage_sensor->set_force_update(false);
  esp32_esp32internalgpiopin_id = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id->set_pin(::GPIO_NUM_34);
  esp32_esp32internalgpiopin_id->set_inverted(false);
  esp32_esp32internalgpiopin_id->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id->set_flags(gpio::Flags::FLAG_INPUT);
  adc_voltage_sensor->set_pin(esp32_esp32internalgpiopin_id);
  adc_voltage_sensor->set_output_raw(false);
  adc_voltage_sensor->set_sample_count(1);
  adc_voltage_sensor->set_attenuation(ADC_ATTEN_DB_0);
  adc_voltage_sensor->set_channel1(::ADC1_CHANNEL_6);
  // sensor.adc:
  //   platform: adc
  //   pin:
  //     number: 35
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_id_2
  //     inverted: false
  //     ignore_pin_validation_error: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: adc_current1_sensor
  //   disabled_by_default: false
  //   force_update: false
  //   unit_of_measurement: V
  //   accuracy_decimals: 2
  //   device_class: voltage
  //   state_class: measurement
  //   raw: false
  //   attenuation: 0db
  //   samples: 1
  //   update_interval: 60s
  //   name: adc_current1_sensor
  //   internal: true
  adc_current1_sensor = new adc::ADCSensor();
  adc_current1_sensor->set_update_interval(60000);
  adc_current1_sensor->set_component_source("adc.sensor");
  App.register_component(adc_current1_sensor);
  App.register_sensor(adc_current1_sensor);
  adc_current1_sensor->set_name("adc_current1_sensor");
  adc_current1_sensor->set_object_id("adc_current1_sensor");
  adc_current1_sensor->set_disabled_by_default(false);
  adc_current1_sensor->set_internal(true);
  adc_current1_sensor->set_device_class("voltage");
  adc_current1_sensor->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  adc_current1_sensor->set_unit_of_measurement("V");
  adc_current1_sensor->set_accuracy_decimals(2);
  adc_current1_sensor->set_force_update(false);
  esp32_esp32internalgpiopin_id_2 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id_2->set_pin(::GPIO_NUM_35);
  esp32_esp32internalgpiopin_id_2->set_inverted(false);
  esp32_esp32internalgpiopin_id_2->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id_2->set_flags(gpio::Flags::FLAG_INPUT);
  adc_current1_sensor->set_pin(esp32_esp32internalgpiopin_id_2);
  adc_current1_sensor->set_output_raw(false);
  adc_current1_sensor->set_sample_count(1);
  adc_current1_sensor->set_attenuation(ADC_ATTEN_DB_0);
  adc_current1_sensor->set_channel1(::ADC1_CHANNEL_7);
  // sensor.adc:
  //   platform: adc
  //   pin:
  //     number: 39
  //     mode:
  //       input: true
  //       output: false
  //       open_drain: false
  //       pullup: false
  //       pulldown: false
  //     id: esp32_esp32internalgpiopin_id_3
  //     inverted: false
  //     ignore_pin_validation_error: false
  //     ignore_strapping_warning: false
  //     drive_strength: 20.0
  //   id: adc_current2_sensor
  //   disabled_by_default: false
  //   force_update: false
  //   unit_of_measurement: V
  //   accuracy_decimals: 2
  //   device_class: voltage
  //   state_class: measurement
  //   raw: false
  //   attenuation: 0db
  //   samples: 1
  //   update_interval: 60s
  //   name: adc_current2_sensor
  //   internal: true
  adc_current2_sensor = new adc::ADCSensor();
  adc_current2_sensor->set_update_interval(60000);
  adc_current2_sensor->set_component_source("adc.sensor");
  App.register_component(adc_current2_sensor);
  App.register_sensor(adc_current2_sensor);
  adc_current2_sensor->set_name("adc_current2_sensor");
  adc_current2_sensor->set_object_id("adc_current2_sensor");
  adc_current2_sensor->set_disabled_by_default(false);
  adc_current2_sensor->set_internal(true);
  adc_current2_sensor->set_device_class("voltage");
  adc_current2_sensor->set_state_class(sensor::STATE_CLASS_MEASUREMENT);
  adc_current2_sensor->set_unit_of_measurement("V");
  adc_current2_sensor->set_accuracy_decimals(2);
  adc_current2_sensor->set_force_update(false);
  esp32_esp32internalgpiopin_id_3 = new esp32::ESP32InternalGPIOPin();
  esp32_esp32internalgpiopin_id_3->set_pin(::GPIO_NUM_39);
  esp32_esp32internalgpiopin_id_3->set_inverted(false);
  esp32_esp32internalgpiopin_id_3->set_drive_strength(::GPIO_DRIVE_CAP_2);
  esp32_esp32internalgpiopin_id_3->set_flags(gpio::Flags::FLAG_INPUT);
  adc_current2_sensor->set_pin(esp32_esp32internalgpiopin_id_3);
  adc_current2_sensor->set_output_raw(false);
  adc_current2_sensor->set_sample_count(1);
  adc_current2_sensor->set_attenuation(ADC_ATTEN_DB_0);
  adc_current2_sensor->set_channel1(::ADC1_CHANNEL_3);
  // socket:
  //   implementation: bsd_sockets
  // network:
  //   enable_ipv6: false
  //   min_ipv6_addr_count: 0
  my_ct_power_clamp->set_voltage_sensor_source(adc_voltage_sensor);
  current1 = new sensor::Sensor();
  App.register_sensor(current1);
  current1->set_name("Current1");
  current1->set_object_id("current1");
  current1->set_disabled_by_default(false);
  current1->set_icon("mdi:current-ac");
  current1->set_unit_of_measurement("A");
  current1->set_accuracy_decimals(3);
  current1->set_force_update(false);
  sensor_multiplyfilter_id_2 = new sensor::MultiplyFilter(40.72f);
  current1->set_filters({sensor_multiplyfilter_id_2});
  my_ct_power_clamp->set_current1_sensor(current1);
  my_ct_power_clamp->set_current1_sensor_source(adc_current1_sensor);
  sensor_sensor_id = new sensor::Sensor();
  App.register_sensor(sensor_sensor_id);
  sensor_sensor_id->set_name("Current2");
  sensor_sensor_id->set_object_id("current2");
  sensor_sensor_id->set_disabled_by_default(false);
  sensor_sensor_id->set_icon("mdi:current-ac");
  sensor_sensor_id->set_unit_of_measurement("A");
  sensor_sensor_id->set_accuracy_decimals(3);
  sensor_sensor_id->set_force_update(false);
  sensor_multiplyfilter_id_3 = new sensor::MultiplyFilter(40.72f);
  sensor_sensor_id->set_filters({sensor_multiplyfilter_id_3});
  my_ct_power_clamp->set_current2_sensor(sensor_sensor_id);
  my_ct_power_clamp->set_current2_sensor_source(adc_current2_sensor);
  power1 = new sensor::Sensor();
  App.register_sensor(power1);
  power1->set_name("Power1");
  power1->set_object_id("power1");
  power1->set_disabled_by_default(false);
  power1->set_icon("mdi:power");
  power1->set_unit_of_measurement("W");
  power1->set_accuracy_decimals(0);
  power1->set_force_update(false);
  sensor_multiplyfilter_id_4 = new sensor::MultiplyFilter(41017.0f);
  power1->set_filters({sensor_multiplyfilter_id_4});
  my_ct_power_clamp->set_power1_sensor(power1);
  sensor_sensor_id_2 = new sensor::Sensor();
  App.register_sensor(sensor_sensor_id_2);
  sensor_sensor_id_2->set_name("Power2");
  sensor_sensor_id_2->set_object_id("power2");
  sensor_sensor_id_2->set_disabled_by_default(false);
  sensor_sensor_id_2->set_icon("mdi:power");
  sensor_sensor_id_2->set_unit_of_measurement("W");
  sensor_sensor_id_2->set_accuracy_decimals(0);
  sensor_sensor_id_2->set_force_update(false);
  sensor_multiplyfilter_id_5 = new sensor::MultiplyFilter(41017.0f);
  sensor_sensor_id_2->set_filters({sensor_multiplyfilter_id_5});
  my_ct_power_clamp->set_power2_sensor(sensor_sensor_id_2);
  calculated_cos_fi_1->set_template([=]() -> optional<float> {
      #line 90 "ct_power_clamp_test.yaml"
      return power1->state / ( voltage->state * current1->state  );
  });
  // =========== AUTO GENERATED CODE END ============
  App.setup();
}

void loop() {
  App.loop();
}
