  GNU nano 7.2                                   /etc/telegraf/telegraf.conf                                            # Telegraf Configuration

###############################################################################
#                Global settings - you don't need to edit these               #
###############################################################################

# Global tags can be specified here in key="value" format.
[global_tags]

# Configuration for telegraf agent
[agent]
  ## Default data collection interval for all inputs
  interval = "10s"
  round_interval = true
  metric_batch_size = 1000
  metric_buffer_limit = 10000
  collection_jitter = "0s"
  flush_interval = "10s"
  flush_jitter = "0s"
  precision = ""
  debug = false
  quiet = false
  logfile = ""
  hostname = ""
  omit_hostname = false
[[outputs.influxdb_v2]]
  urls = ["http://127.0.0.1:8086"]
  token = "***"
  organization = "****"
  bucket = "mqtt-data"
  [[inputs.mqtt_consumer]]
  servers = ["tcp://eu1.cloud.thethings.network:1883"]
  client_id = "telegraf_casa0022_ucfnchb"
  username = "lora-2-stella@ttn"
  password = "*****"    
  topics = ["v3/lora-2-stella@ttn/devices/lora-2-stella/up"]
  data_format = "json_v2"
  
#json_string_fields = ["uplink_message.rx_metadata.0.gateway_ids.gateway_id"]

  [[inputs.mqtt_consumer.json_v2]]
    [[inputs.mqtt_consumer.json_v2.field]]
      path = "uplink_message.decoded_payload.lat"
      type = "float"
    [[inputs.mqtt_consumer.json_v2.field]]
      path = "uplink_message.decoded_payload.lng"
      type = "float"
    [[inputs.mqtt_consumer.json_v2.field]]
      path = "uplink_message.rx_metadata.0.rssi"
      type = "float"
    [[inputs.mqtt_consumer.json_v2.field]]
      path = "uplink_message.rx_metadata.0.snr"
      type = "float"
    [[inputs.mqtt_consumer.json_v2.field]]
      path = "uplink_message.rx_metadata.0.gateway_ids.gateway_id"
      type = "string"