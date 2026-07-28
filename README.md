# 4-Motor L293D Robot — Forward/Backward/Turn Sequence

Arduino Uno sketch that drives a 4-wheel robot (4 DC motors, paired left/right)
through a fixed one-shot movement sequence using a single L293D H-bridge driver.

## Hardware

- Arduino Uno
- 1x (or 2X) L293D motor driver IC
- 4x DC gear motors (2 on the left side, 2 on the right side — motors on the
  same side are wired in parallel to the same L293D channel, so they always
  spin together at the same speed/direction)
- 9V battery (motor power, VCC2 / pin 8 on the L293D)
- Breadboard for power distribution

## Power

- **Logic power (VCC1 / pin 16):** Arduino 5V → breadboard rail → L293D
- **Motor power (VCC2 / pin 8):** 9V battery + → breadboard rail → L293D
- **Ground:** Arduino GND, 9V battery −, and L293D ground pins all share a
  common ground on the breadboard rail — this is required for the Arduino's
  PWM/direction signals to control the motor-side H-bridge correctly.

## Pinout

| Signal        | Arduino Pin | L293D Pin | Function                          |
|---------------|:-----------:|:---------:|------------------------------------|
| `enableLeft`  | D9 (PWM)    | EN1       | Left side speed (PWM)             |
| `in1Left`     | D8          | IN1       | Left side direction bit 1         |
| `in2Left`     | D7          | IN2       | Left side direction bit 2         |
| `enableRight` | D10 (PWM)   | EN2       | Right side speed (PWM)            |
| `in1Right`    | D6          | IN3       | Right side direction bit 1        |
| `in2Right`    | D5          | IN4       | Right side direction bit 2        |

- Channel A (EN1/IN1/IN2 → OUT1/OUT2) drives the two **left** motors in parallel.
- Channel B (EN2/IN3/IN4 → OUT3/OUT4) drives the two **right** motors in parallel.

> ⚠️ Because two motors share one channel, make sure the combined stall current
> of both motors on a side stays under the L293D's ~600mA-per-channel rating
> (1.2A peak). If your gear motors draw more than that under load, drive each
> motor from its own channel instead (e.g. two L293D chips, one motor per
> channel) rather than pairing them.

## Behavior

On power-up, the robot runs a single fixed sequence and then halts permanently
(it does **not** loop):

1. Forward — 30 seconds
2. Backward — 60 seconds
3. Alternating right/left pivot turns — 60 seconds total (15s per turn: R, L, R, L)
4. Stop motors, then halt (infinite empty loop — no further movement until reset)

Speed is fixed at `speed = 200` (0–255 PWM range) for all movements.

## Notes

- `setupSequenceDone()` intentionally blocks forever (`while(true) {}`) after
  the sequence completes. Power-cycle or press the Arduino's reset button to
  run the sequence again.
- The alternating-turn logic can be swapped for a small loop
  (`alternateTurns(totalMs, stepMs)`) if you want to tune the turn interval
  without editing multiple blocks — ask if you'd like that version.
