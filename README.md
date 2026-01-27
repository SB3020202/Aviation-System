# ✈️ Airline Reservation System (C Project)

* Project of the 1º semester of the 1º year with Final Grade = 17.5/20
A low-level Flight Management System developed in **C** that handles aircraft configurations, seat reservations, and passenger manifests using **binary file persistence** and **direct memory manipulation**.

This project demonstrates proficiency in C programming, specifically in file I/O operations (binary/text), memory management, and algorithm implementation for seating logic.

## 📋 Features

* **Aircraft Configuration:** specific row/seat layouts for different Airbus models (A318, A319, A320, A321).
* **Visual Seat Map:** Renders a CLI-based map of the plane showing occupied (`.`) and empty (`a`, `b`, `c`...) seats.
* **Reservation Management:**
    * Create new reservations (stores Name, Luggage ID, Reservation Code).
    * Modify existing seat assignments.
    * Detect collisions (double-booking prevention).
* **Flight Operations:**
    * Initialize new flights by assigning an aircraft type.
    * **Simulation Mode:** Randomly populates a flight with passengers using dataset files (`names`, `surnames`) to test high-concurrency scenarios.
* **Data Persistence:** All flight data is stored in binary files to simulate a real database system.

## 🛠️ Technical Implementation

* **Language:** C
* **Storage:** Binary files (`.bin`) for flight data to optimize storage and read/write speed; Text files for configuration.
* **Key Concepts:**
    * Struct serialization/deserialization.
    * `fseek` and `ftell` for precise file navigation.
    * Dynamic logic based on aircraft type inputs.

## 🚀 Getting Started

### Prerequisites
Ensure you have a C compiler (GCC) installed. You also need the auxiliary text files in the root directory for the program to function correctly:
1.  `names` (List of first names for simulation)
2.  `surnames` (List of last names for simulation)
3.  `Airbus3xx` config files (e.g., `Airbus318`, `Airbus320`)

### Compilation

```bash
gcc -o flight_manager main.c
