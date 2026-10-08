# Hunter ceiling fan controller (ESPHome, 434 MHz)

Controls a Hunter ceiling fan from Home Assistant by replaying its RF remote codes from an ESP32-C3.

- `hunter-fan-controller.yaml` — ESPHome config. A 434 MHz transmitter on GPIO4 sends raw timings for
  Light, Fan Toggle, Speed Up, Speed Down (exposed as HA switches). Also runs a Bluetooth proxy.
- `rxsniffer/` — Arduino sketch to capture raw timings from your own remote with a 434 MHz receiver.
- `tx-test/` — Arduino sketch to replay captured timings before moving to ESPHome.

The codes here are for my fan's remote; capture your own with `rxsniffer` and paste them in.
Copy `secrets.yaml.example` to `secrets.yaml` and fill it in.
