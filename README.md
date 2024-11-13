# Autonomous Intersection Management System

This project demonstrates an autonomous intersection management system designed to improve traffic flow and safety in urban settings. The system utilizes Vehicle-to-Infrastructure (V2I) communication to manage traffic at intersections in real-time, ensuring smooth and efficient vehicle passage. Implemented with FreeRTOS on Arduino Mega and VHDL for vehicle detection, it validates safe passage through UPPAAL simulations.

## Project Overview

The Autonomous Intersection Management System enables real-time traffic control using V2I communication principles, ensuring seamless coordination of vehicles at intersections. With a focus on safety and efficiency, the system prioritizes vehicle management and smooth traffic flow, allowing for autonomous navigation through intersections without traditional traffic lights.

## Features

- **Vehicle Detection and Identification:** Vehicles are detected and assigned priority based on traffic conditions.
- **FreeRTOS for Real-Time Control:** Real-time operating system (FreeRTOS) manages traffic flow and handles priority decisions on the Arduino Mega microcontroller.
- **VHDL for Logic Control:** VHDL is used for vehicle identification and intersection control, enabling precise timing and sequencing.
- **UPPAAL Simulation Validation:** Simulations in UPPAAL validate and ensure safe and conflict-free intersection management, enhancing intersection efficiency.

## Hardware Components

- **Arduino Mega:** Main control unit for handling real-time intersection management.
- **Sensors (optional):** Used to detect vehicle presence and transmit data for prioritization.
- **LEDs (optional):** Simulate traffic signals based on real-time decisions.

## Setup and Usage

1. **Assembly:** Set up the Arduino Mega with any required sensors or actuators (such as LEDs for signal simulation).
2. **Code Upload:** Flash the provided FreeRTOS and VHDL-based code onto the Arduino Mega.
3. **Simulation Testing:** Use UPPAAL to simulate various traffic conditions and validate intersection management performance.
4. **Deployment:** Deploy the system at a model intersection to observe traffic management in real-time.

## Future Enhancements

- Integrate machine learning for adaptive traffic control based on real-time traffic data.
- Explore IoT integration for remote monitoring and control.
- Develop a mobile app interface for traffic and emergency personnel to view live traffic status.

## Team Collaboration

This project was developed collaboratively, with each member contributing to code development, hardware setup, and simulation validation. The system design and implementation were reviewed to ensure reliability and efficiency for autonomous traffic management.

## Conclusion

The Autonomous Intersection Management System is a forward-thinking solution aimed at transforming how intersections operate in a world moving towards autonomous vehicles. It combines real-time control, safety, and efficiency to make autonomous navigation through intersections practical and secure.
