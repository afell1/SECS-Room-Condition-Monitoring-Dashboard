**CS 495: Senior Design Project — 2026-2027**
# SECS Room Condition Monitoring Dashboard

**Contributor:** Anelise Fellers

## Project Summary

This project uses ESP32 Feather V2 microcontrollers in combination with SHT41 temperature and humidity sensors to monitor conditions within rooms in the University of Evansville School of Engineering and Computer Science (SECS). 

Data, both current and from the last 30 days, will be available through a React-based web dashboard. The overall intention of this project is to make it easier to track room conditions over time and identify rooms that may need further attention, with the goal of improving conditions for faculty, staff, and students.

## Core Features
- **Temperature and Humidity Monitoring** — Collect readings from monitored SECS rooms.
- **Current Conditions Display** — View current temperature and humidity readings for each monitored room.
- **Historical Data Tracking and Visualization** — View temperature and humidity trends over the past 30 days.
- **Out-of-Range Indicators** — Identify readings outside specified temperature and humidity ranges.
- **Local Sensor Display** — View current readings on a 16×2 character LCD connected to each sensor device.

## System Architecture
The system consists of sensor hardware, a backend API, a database, and a web dashboard.

 The diagram below illustrates how sensor readings travel from the
ESP32/SHT41 devices to the backend API and database, and how the
dashboard retrieves data for display. Each sensor device also displays
current readings locally on a 16×2 character LCD.

<img width="1165" height="348" alt="System Architecture - Digital" src="https://github.com/user-attachments/assets/baef9730-991f-4b47-b36f-805a42fe2787" />

## Initial Data Requirements
- **Temperature readings** — The temperature, in degrees F (°F), recorded for each monitored room.
- **Humidity readings** — The relative humidity, recorded as a percentage (%), for each monitored room.
- **Acceptable data ranges** — The temperature and humidity ranges used to identify out-of-range readings.
- **Room identification** — Room associated with each set of readings.
- **Timestamps** — Date and time of each reading.
- **Historical readings** — Stored measurements used to display temperature and humidity trends over the past 30 days.

## Technologies Used
- **React** — Frontend framework used to build the dashboard interface.
- **HTML/CSS** — Used to structure and style the dashboard.
- **JavaScript** — Used to make the dashboard interactive and handle data.
- **Node.js/Express** — Backend API used to handle communication between the sensor devices, database, and dashboard.
- **PostgreSQL** — Database used to store sensor readings and historical data.
- **ESP32 Feather V2/SHT41** — Sensor hardware used to collect temperature and humidity readings and transmit them over Wi-Fi.
- **GitHub** — Repository and version control used to store project code and documentation.
- **Visual Studio Code** — Development environment used to develop and organize code and documentation.
