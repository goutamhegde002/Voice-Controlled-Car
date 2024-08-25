# Voice Controlled Robot

## Overview

This project demonstrates a voice-controlled robot using an Arduino and Bluetooth module. The robot can be controlled through voice commands sent via Bluetooth from a Python application using Kivy.

## Components

- Arduino Uno x 2
- Bluetooth Module (HC-05/HC-06)
- AFMotor Shield
- Motors and Servo Motor
- Ultrasonic Sensor
- LEDs

## Arduino Code

The Arduino code controls the robot's movement and obstacle avoidance. It listens for commands via Bluetooth and executes corresponding actions.

### `robot_control.ino`

This code manages:
- Movement commands (`forward`, `backward`, `left`, `right`, etc.)
- Obstacle detection using an ultrasonic sensor
- Control of motors and LEDs

## Voice Control Application

### `voice_control.py`

A Python application built with Kivy for voice recognition. It converts spoken commands to text and sends them to the Arduino via Bluetooth.

#### Installation

1. **Python Environment**
    - Install Python 3.x from [python.org](https://www.python.org/).
    - Install the required libraries:
      ```bash
      pip install kivy speechrecognition PyBluez
      ```

2. **Bluetooth Setup**
    - Pair the Bluetooth module with your smartphone or computer.

#### Usage

1. Upload the Arduino code to the Arduino boards.
2. Pair the Bluetooth module with your smartphone or computer.
3. Run the Python application:
    ```bash
    python voice_control.py
    ```
4. Use voice commands to control the robot's movement and actions.

## How to Use

1. Upload the respective Arduino code to the two Arduino Uno boards.
2. Pair the Bluetooth module with your smartphone or computer.
3. Run the Python Bluetooth app.
4. Use the buttons in the app to control the robot's movement and the servo motor for pesticide spraying.

## Installation

### Arduino IDE

1. Download and install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Open the provided `.ino` files and upload them to the Arduino Uno boards.

### Python Environment

1. Install Python 3.x from [python.org](https://www.python.org/).
2. Install the required Python libraries:
    ```bash
    pip install kivy speechrecognition PyBluez
    ```
3. Run the `voice_control.py` script:
    ```bash
    python voice_control.py
    ```

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Contributing

Contributions are welcome! Please fork this repository and submit a pull request with your improvements.

## Contact

For any questions or suggestions, please contact me via LinkedIn.
