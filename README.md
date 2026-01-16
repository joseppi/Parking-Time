# Parking Time - Custom C++ Physics & Vehicle Engine

![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue) ![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey) ![Graphics](https://img.shields.io/badge/Graphics-OpenGL-red)

**Parking Time** is a custom-built vehicle physics tech demo developed in C++. The project demonstrates the implementation of rigid body mechanics, vector mathematics for movement, and collision resolution without reliance on heavy commercial game engines.

## 🚀 Technical Highlights

This project focuses on the core engineering challenges of game development:

* **Custom Physics Implementation:** Manual calculation of velocity, acceleration, and friction vectors.
* **Object-Oriented Architecture:** Modular design using C++ classes for entity management (Vehicles, Obstacles, World).
* **Memory Management:** Efficient handling of game entities.
* **Collision Detection:** Implementation of bounding box collision logic.

## 🛠️ Tech Stack

* **Language:** C++ (Standard 17)
* **Graphics API:** OpenGL (via GLUT/FreeGLUT)
* **Math:** Custom Vector Math Implementation
* **IDE:** Visual Studio

## 🎮 Features

* **Vehicle Dynamics:** Simulation of acceleration, braking, and turning inertia.
* **Win/Loss States:** Logic systems for tracking parking success within time limits.

## 🔧 How to Build

1.  Clone the repository:
    ```bash
    git clone https://github.com/joseppi/Parking-Time.git
    ```
2.  Open the solution file in **Visual Studio**.
3.  Ensure **OpenGL** and **GLUT** libraries are linked in the project properties.
4.  Build and Run in **Release** mode.

## 👨‍💻 Developer Notes

This project was developed to explore the mathematical foundations of game engines. It serves as a study in:
* Game Loop implementation (Update/Render separation).
* Delta Time (dt) management for frame-rate independent movement.
* Vector math application in a 3D space.
* Bullet library implementation