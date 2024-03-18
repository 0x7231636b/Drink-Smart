# Drink-Smart

Project for a smart scale mainly designed to keep track of drinking volume during the day

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
