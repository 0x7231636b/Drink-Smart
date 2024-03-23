# Drink-Smart

Project for a smart scale mainly designed to keep track of drinking volume during the day

## Development environment setup

### Code formatter

As a code formatter we use uncrustify as it's highly customizable. See [devtools/formatter/README.md](devtools/formatter/README.md) for more information.

### PlatformIO
This project was setup with platformIO. To install it, follow the instructions on the [platformIO website](https://platformio.org/install/cli).

In short: platformIO is a plugin for Visual Studio Code. It is a build system for embedded systems and IoT and can be directly integrated into VS Code via the platformIO extension. Since code formatter settings are stored in the `.vscode/settings.json` file, it is recommended to use VS Code as the IDE.

## Roadmap

- Implement algorithm for drink detection
  - On 0g (with tolerance of a not yet defined threshold) do nothing
  - When a weight is detected, store the value
  - When the weight (with tolerance of a not yet defined threshold) is less than the stored value, a drink has been detected.
    Then, log the difference in weight and the time of the event.
- Implement a simple webserver for receiving the data (separate repository)
- Send data via rest (look for rest apis)
- Setup tests (https://docs.platformio.org/en/latest/advanced/unit-testing/introduction.html)
- Build a web frontend
- Add Display and buttons
- Add MQTT support
