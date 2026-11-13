# Autonomous Car — Obstacle Avoidance

An Arduino-based autonomous car that continuously drives forward and steers around obstacles using ultrasonic distance sensing.

## How It Works

The car is equipped with **three HC-SR04 ultrasonic sensors** (front, left, right) that measure the distance to nearby objects in real time. A servo motor controls steering, while a DC motor keeps the car moving forward at all times.

### Decision Logic

Each loop iteration reads all three sensor distances and applies a two-tier avoidance strategy:

| Zone | Threshold | Action |
|------|-----------|--------|
| **Critical** | < 40 cm | Full turn away from the closest obstacle (servo to 50° left or 130° right) |
| **Warning** | < 60 cm | Partial turn toward the free side (servo to 70° left or 110° right) |
| **Clear** | ≥ 60 cm | Servo returns to center (90°), car drives straight |

The sensor reporting the smallest distance determines which direction to steer. If no obstacle is within range, the servo stays centered.

### Feedback Indicators

- **Left LED + buzzer**: blink when steering left
- **Right LED + buzzer**: blink when steering right

## Hardware

| Component | Pin(s) | Role |
|-----------|--------|------|
| HC-SR04 (front) | Trig 4 / Echo 7 | Front distance |
| HC-SR04 (left) | Trig 5 / Echo 8 | Left distance |
| HC-SR04 (right) | Trig 6 / Echo 9 | Right distance |
| Servo motor | 11 | Steering |
| DC motor | 13 | Forward drive (always on) |
| LED (left) | 2 | Left-turn indicator |
| LED (right) | 10 | Right-turn indicator |
| Buzzer | 3 | Audible alert |

## Servo Angles

| Angle | Meaning |
|-------|---------|
| 50° | Full left turn |
| 70° | Partial left turn |
| 90° | Straight (center) |
| 110° | Partial right turn |
| 130° | Full right turn |

## Requirements

- Arduino board (Uno or compatible)
- 3× HC-SR04 ultrasonic sensors
- SG90/MG90 servo motor
- DC motor + driver
- LEDs, buzzer, resistors, and wiring

## Extra
I delevoped this autonomous vehicule inspired on my garage cleaning problem. There were many trees nearby, so the garage was always full of leaves all the time. 
It was intended to implement a vaccum cleaner on it to eliminate this cleaning routine.
Not many years later, the autonomous vaccum cleaner has been released on the market.
Later, during a conversation with a professor at UNESP, I realized I was using Fuzzy programming logic.
This project allowed me to be introduced to C programming language, programming logics, electronics, micro controller (Arduino) and project management before starting my studies in Electrical Engineering at UNESP.