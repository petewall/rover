# Rover Firmware

PlatformIO project that targets the Wemos D1 mini (ESP8266) and provides a starting point for Rover firmware development. The default sketch blinks the on-board LED (pin D4) and streams a heartbeat message over the serial console at 115200 baud.

## Requirements

- [PlatformIO Core](https://platformio.org/install/cli) (`pio` CLI) or the PlatformIO VS Code extension
- A USB connection to a Wemos D1 mini compatible board

> **Note:** The project configures PlatformIO to keep all downloaded toolchains and frameworks inside `.platformio-home/`. You do not need to set any environment variables; all commands can be executed from the repository root.

## Typical Workflow

From the project root:

1. **Build:** `make build`
2. **Upload Data files:** Connect the D1 mini over USB and run `make uploadfs`
3. **Upload:** Connect the D1 mini over USB and run `make upload`
4. **Monitor (optional):** `pio device monitor --baud 115200`

PlatformIO automatically selects the `rover` environment defined in `platformio.ini`. If you add other environments later, you can build or upload them with `pio run -e <env-name>`.

## Project Layout

- `src/main.cpp` – Arduino sketch entry point (blinks LED + serial heartbeat)
- `include/` – place project-wide headers
- `lib/` – optional reusable libraries
- `test/` – PlatformIO unit tests (Unity)

Refer to the [PlatformIO documentation](https://docs.platformio.org/page/projectconf.html) for additional configuration options.
