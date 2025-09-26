#include <Mouse.h>        // Import Arduino Mouse library

// Analog input pin assignments
int click_Pin = A0;        // A0 Click
int left_Pin = A1;         // A1 Move left
int right_Pin = A2;        // A2 Move right
int up_Pin = A3;           // A3 Move up
int down_Pin = A4;         // A4 Move down

// Variables to store analog readings (0 - 1023)
int click_Val = 0;
int left_Val = 0;
int right_Val = 0;
int up_Val = 0;
int down_Val = 0;

// Cursor movement step sizes
char x_Origin = 0;         // No horizontal movement
char y_Origin = 0;         // No vertical movement
char x_left_Step = -15;    // Step left
char x_right_Step = 15;    // Step right
char y_up_Step = -20;      // Step up
char y_down_Step = 20;     // Step down


void setup() {
  pinMode(2, INPUT);       // PD2 acts as safety enable
  Serial.begin(9600);      // Serial monitor start
  Mouse.begin();           // Start mouse control
}


void loop() {
  // Run only if PD2 is HIGH (safety to prevent lockout)
  if (digitalRead(2) == HIGH) {  

    // Click
    click_Val = analogRead(click_Pin);      // Read A0
    if (click_Val > 510) {                  // Click when above threshold
      Mouse.click();
      delay(1000);                          // Delay to avoid double-clicking
    }

    // Move Left
    left_Val = analogRead(left_Pin);        // Read A1
    if (left_Val > 415) {                   // Move left when above threshold
      Mouse.move(x_left_Step, y_Origin);  
      delay(10);                            // Small delay for smooth motion
    }

    // Move Right
    right_Val = analogRead(right_Pin);      // Read A2
    if (right_Val > 600) {                  // Move right when above threshold
      Mouse.move(x_right_Step, y_Origin);
      delay(10);
    }

    // Move Up
    up_Val = analogRead(up_Pin);             // Read A3
    if (up_Val > 345) {                      // Move up when above threshold
      Mouse.move(x_Origin, y_up_Step);
      delay(10);
    }

    // Move Down
    down_Val = analogRead(down_Pin);         // Read A4
    if (down_Val > 385) {                    // Move down when above threshold
      Mouse.move(x_Origin, y_down_Step);   
      delay(10);
    }
  } 
  
  else {
    delay(100);      // Delay when PD2 is LOW
  }
}
