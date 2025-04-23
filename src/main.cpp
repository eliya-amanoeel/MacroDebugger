#include <Arduino.h>
#include <HID-Project.h>
#include <HID-Settings.h>

// Switch pins (adjust if needed)
const int switchPins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 16, 14, 15};

// Track previous state to prevent repeat
bool prevState[12] = {0};

void handleKeyAction(int switchNumber) {
    switch (switchNumber) {
      case 1: // F9
        Keyboard.press(KEY_F9);
        break;
      case 2: // F5
        Keyboard.press(KEY_F5);
        break;
      case 3: // F10
        Keyboard.press(KEY_F10);
        break;
      case 4: // F12
        Keyboard.press(KEY_F12);
        break;
      case 5: // Ctrl + F9
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press(KEY_F9);
        break;
      case 6: // Shift + F5
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_F5);
        break;
      case 7: // F11
        Keyboard.press(KEY_F11);
        break;
      case 8: // Ctrl + F
        Keyboard.press(KEY_LEFT_CTRL);
        Keyboard.press('f');
        break;
      case 9: // Ctrl + Shift + F9
        Keyboard.press(KEY_LEFT_CTRL);
        delay(10); 
        Keyboard.press(KEY_LEFT_SHIFT);
        delay(10); 
        Keyboard.press(KEY_F9);
        break;
      case 10: // F8
        Keyboard.press(KEY_F8);
        break;
      case 11: // Shift + F11
        Keyboard.press(KEY_LEFT_SHIFT);
        Keyboard.press(KEY_F11);
        break;
      case 12: // Ctrl + Shift + F
        Keyboard.press(KEY_LEFT_CTRL);
        delay(10); 
        Keyboard.press(KEY_LEFT_SHIFT);
        delay(10);
        Keyboard.press('f');
        break;
    }

    delay(100);
    Keyboard.releaseAll();
}

void setup() {
    for (int i = 0; i < 12; i++) {
        pinMode(switchPins[i], INPUT_PULLUP);
    }
    BootKeyboard.begin();
    delay(2000);
}

void loop() {
    for (int i = 0; i < 12; i++) {
        bool isPressed = !digitalRead(switchPins[i]);

        if (isPressed && !prevState[i]) {
            handleKeyAction(i + 1);
            prevState[i] = true;
        } else if (!isPressed) {
            prevState[i] = false;
        }
    }
}