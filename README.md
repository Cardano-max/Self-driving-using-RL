# 🤖 Line Follower Robot 🤖

Welcome to the Line Follower Robot project! 🚗💨

<p align="center">
  <img src="https://github.com/Azlaan20/Arduino_Self_Driving_Car/blob/main/Line_Follower_Robot.jpeg" alt="Line Follower Robot Image">
</p>

## 📖 Overview

This repository contains the code for a Line Follower Robot that can autonomously navigate a black line on the ground. The robot uses infrared sensors to detect the line and make decisions on how to follow it.

## 🛠️ Hardware Setup

Here's a list of the components used in this project:
- 🤖 TT Gear Motors
- 🕹️ Motor Driver
- 📡 Infrared Sensors
- ⚙️ Arduino Board

Make sure to connect everything correctly to build your Line Follower Robot.

## 🚀 Getting Started

To get your robot up and running, follow these steps:

1. Upload the provided Arduino code to your board.
2. Assemble the hardware components as per the instructions.
3. Power on your Line Follower Robot.
4. Watch it follow the line like a pro! 🏁

## 🤖 How It Works

The Line Follower Robot uses infrared sensors to detect the black line on the ground. It has various predefined states to make decisions on how to move:

- 🚦 `Straight`: Move straight when all sensors detect the line.
- ↗️ `Slight Right Turn`: Make a slight right turn when the right sensor detects the line.
- ↖️ `Slight Left Turn`: Make a slight left turn when the left sensor detects the line.
- 🔄 `Sharp Right Turn`: Execute a sharp right turn when necessary.
- 🔁 `Sharp Left Turn`: Execute a sharp left turn when necessary.
- ➕ `Plus Junction`: Handle intersections with multiple lines.

The robot's state changes as it encounters different sensor readings, ensuring it stays on track.

## 🤯 Advanced Features

This Line Follower Robot comes with some advanced features:
- 🔄 `Triple Line Detection`: Handles triple lines intelligently.
- 🔀 `Double Line Detection`: Detects and reacts to double lines effectively.
- 🚦 `Sensor Calibration`: Fine-tune sensor alignment.

## 📽️ Watch It in Action

Here's a short video of our Line Follower Robot in action:
[Line Follower Robot Video 1](https://drive.google.com/file/d/1BPXRYELUGtH_GQTzzr0tvO17oCWnSMQg/view?usp=drive_link)
[Line Follower Robot Video 2](https://drive.google.com/file/d/13R8XBh_klcHmjOmpBSWSZFirvJJmW4wl/view?usp=drive_link)

## 👨‍💻 Contributors

- Azlaan Ranjha
- Laiba Jabbar
- Muneeb Arshad

Feel free to contribute to this project and make it even cooler! 🤩

## 📞 Contact

If you have any questions or suggestions, feel free to reach out:

📧 Email: azlaanranjha2003@gmail.com
🐦 LinkedIn: [@AzlaanRanjha](https://www.linkedin.com/in/azlaan-ranjha-1b023a107/)

Happy line following! 🏁🤖
