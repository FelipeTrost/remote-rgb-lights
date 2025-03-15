## Setup with arduino-cli

```bash
arduino-cli config init
arduino-cli lib install FastLED@3.7.3
```

add to arduino cli config file

```yaml
- https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

```bash
arduino-cli core update-index
arduino-cli board listall
arduino-cli core install esp32:esp32

# look for esp32 entry
arduino-cli core list
```

## Compile and upload

> You might have to adjust change the permissions on /dev/ttyUSB0

```bash
cd rgb-lights
arduino-cli compile --fqbn esp32:esp32:nodemcu-32s rgb-lights.ino
arduino-cli upload -p /dev/ttyUSB0 --fqbn esp32:esp32:nodemcu-32s rgb-lights.ino
```
