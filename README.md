# EMG Computer Cursor Control

## Description

An Arduino-based EMG Computer Cursor Control System programmed in C++. This project implements a five-channel system that uses electromyography (EMG) signals from the right arm to control a computer cursor. Muscle contractions drive five distinct actions: left, right, up, down, and click.

## Requirements

### Hardware
1. Arduino Leonardo (supports native USB HID for mouse control)
2. EMG electrode pairs and reference electrodes
3. Instrumentation amplifier (e.g. INA129)
4. Operational amplifiers (e.g. TL081, TL082)
5. Passive components (resistors, capacitors, diodes)
6. Breadboards and jumper wires
7. Power supply
8. NI MyDaq (or equivalent DAQ/oscilloscope for signal testing)

### Software
1. Arduino IDE
2. Arduino Mouse library (#include <Mouse.h>)

## Circuit Specifications

### Circuit Diagram

<p align="center">
  <kbd>
    <img width="800" src="https://github.com/kkaiiwen/EMG-Computer-Cursor-Control/blob/main/Graphics/EMG Circuit Diagram.jpg">
  </kbd>
</p>
<p align="center">
    <text> Figure 1: EMG Circuit Diagram </text>
</p>

Each channel follows the same circuit design, with electrodes placed on different muscles. The positive supply, negative supply, and ground are shared across all five breadboards.

| Component              | Function                                                                                                                                                          |
|------------------------|------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| Instrumentation Amplifier | Amplifies EMG signals with a high signal-to-noise ratio (SNR). Gain is set to 10. The high common-mode rejection ratio (CMRR) suppresses common-mode interference, such as mains power noise. |
| Active High-Pass Filter   | Removes DC offset and low-frequency noise, ensuring only muscle activation signals are passed. Cutoff frequency: 10 Hz.                                        |
| Full Wave Rectifier       | Rectifies the EMG signal to maximise use of the Arduino’s 0-5 V input range and simplify the thresholding process.                                             |
| Active Low-Pass Filter    | Smooths the rectified EMG signal and attenuates high-frequency noise, ensuring the EMG signal is clean and distinguishable. Cutoff frequency: 500 Hz.          |
| Non-Inverting Amplifier   | Provides additional gain (set individually for each muscle group) while ensuring the signal stays within the Arduino’s 0-5 V ADC input range.                 |

The non-inverting amplifier resistor R is adjusted for each channel to provide the appropriate gain based on the EMG signal strength of the corresponding muscle. Weaker signals are amplified with higher gain, while stronger signals are limited to ensure the output remains within the Arduino’s 0-5 V input range.

| Cursor Action | Movement                  | Muscle Stimulated          | Resistor Value R (kΩ) | Non-Inverting Amplifier Gain | Analog Input Pin |
|:-------------:|:-------------------------:|:--------------------------:|:----------------------:|:----------------------------:|:----------------:|
| Click         | Finger flexion            | Flexor digitorum profundus | 33                     | 303                          | A0               |
| Left          | Wrist flexion (towards left)  | Flexor carpi ulnaris       | 27                     | 370                          | A1               |
| Right         | Wrist extension (towards right) | Flexor carpi radialis      | 47                     | 213                          | A2               |
| Up            | Elbow flexion             | Biceps brachii             | 67                     | 149                          | A3               |
| Down          | Elbow extension           | Triceps brachii            | 100                    | 100                          | A4               |

## Thresholding

Threshold values are initially estimated by recording EMG signals with a measurement device (e.g. NI MyDaq) and calculating the average peak-to-peak voltage of each contraction pulse for every movement. These analog voltages (0-5 V) are then scaled by the Arduino’s 10-bit ADC, giving digital values in the range 0-1023.

<p align="center">
  <kbd>
    <img width="255" src="https://github.com/kkaiiwen/EMG-Computer-Cursor-Control/blob/main/Graphics/Thresholding 1.png">
  </kbd>
  <kbd>
    <img width="285" src="https://github.com/kkaiiwen/EMG-Computer-Cursor-Control/blob/main/Graphics/Thresholding 2.png">
  </kbd>
</p>
<p align="center"> 
  <text> Figure 2a: EMG signal with no muscle contraction </text>
</p>
<p align="center">
  <text> Figure 2b: EMG signal with muscle contraction </text>
</p>

<div align="center">

| Cursor Action | Average Analog Value (0-5 V) | Digital Value (0-1023) |
|:-------------:|:-----------------------------:|:-----------------------:|
| Click         | 3.231                         | 661                     |
| Left          | 3.519                         | 720                     |
| Right         | 3.192                         | 653                     |
| Up            | 2.942                         | 602                     |
| Down          | 2.233                         | 457                     |

</div>

### Testing trial process
1. Connect electrodes to the circuit and monitor signals on the MyDaq oscilloscope.
2. Record 10 peak-to-peak voltage values for the target contraction.
3. Calculate the average of the 10 values.
4. Test other movements to check for unwanted activation.
5. If interference occurred, compare unwanted signal amplitude with the desired signal.
6. If the unwanted signal was much smaller, accept the placement. If similar, either adjust the gain or select a new electrode position.

During testing, thresholds are refined to ensure reliable detection of muscle activity while reducing false activations. This leads to differences between the initial estimates and the final values used in the EMG Cursor Control Programme.

## Usage

1. Place electrodes on the target muscles.
2. Record EMG signals with MyDaq/oscilloscope to set initial thresholds and match your own EMG signal strength.
3. Check for cross-activation and adjust electrode placement or amplifier gain if needed.
4. Update the threshold values in the EMG Cursor Control Programme with your calibrated values.
5. Connect the Arduino Leonardo to your PC.
6. Upload the EMG Cursor Control Programme to the Arduino.
7. Contract the mapped muscle to trigger cursor movements (left, right, up, down) or a click.
8. Fine-tune thresholds in the programme if necessary.


