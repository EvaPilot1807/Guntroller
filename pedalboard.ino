/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <BleKeyboard.h>

BleKeyboard bleKeyboard;

void setup() {
bleKeyboard.begin();
pinMode(25, INPUT_PULLUP);
pinMode(13, INPUT_PULLUP);
pinMode(14, INPUT_PULLUP);
pinMode(12, INPUT_PULLUP);
pinMode(33, INPUT_PULLUP);
pinMode(32, INPUT_PULLUP);
pinMode(27, INPUT_PULLUP);
}

void loop() {
  if(bleKeyboard.isConnected()) {
int w = digitalRead(13);
int a = digitalRead(14);
int s = digitalRead(25);
int d = digitalRead(12);
int ctrl = digitalRead(32);
int shift = digitalRead(27);
int space = digitalRead(33);
    
    
    
if (w == LOW)
{bleKeyboard.press('w');}
else if (a == LOW)
{bleKeyboard.press('a');}
else if (s == LOW)
{bleKeyboard.press('s');}
else if (d == LOW)
{bleKeyboard.press('d');}
else if (ctrl == LOW)
{bleKeyboard.press(128);}
else if (shift == LOW)
{bleKeyboard.press(129);}
else if (space == LOW)
{bleKeyboard.press(0x20);}
else
{bleKeyboard.releaseAll();}
  }

 delay(10);
}
