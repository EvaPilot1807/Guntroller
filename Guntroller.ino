




#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Mouse.h>
#include <Keyboard.h>

Adafruit_MPU6050 mpu;

void setup(void) {
  Serial.begin(115200);


  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Mouse.begin();
  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
  pinMode(4, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  Keyboard.begin();
  
  
}
void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Print out the values */
  Serial.print("AccelX:");
  Serial.print(a.acceleration.x);
  Serial.print(",");
  Serial.print("AccelY:");
  Serial.print(a.acceleration.y);
  Serial.print(",");
  Serial.print("AccelZ:");
  Serial.print(a.acceleration.z);
  Serial.print(", ");
  Serial.print("GyroX:");
  Serial.print(g.gyro.x);
  Serial.print(",");
  Serial.print("GyroY:");
  Serial.print(g.gyro.y);
  Serial.print(",");
  Serial.print("GyroZ:");
  Serial.print(g.gyro.z);
  Serial.println("");

  float dx = 100 * g.gyro.z;
  float dy = 100 * g.gyro.y;
  float dx1 = dx / 3;
  float dy1 = dy / 3;
  float t1;
  float t2;


  int click = digitalRead(4);
  int precision = digitalRead(8);
  int quickMode = digitalRead(9);
  int reset = digitalRead(10);
  int b = digitalRead(11);
  int nextWeapon = digitalRead(12);
  int esc = digitalRead(7);

  if (click == LOW) {
    Mouse.press();
  } else if (b == LOW) {
    Keyboard.press('b');
  } else if (nextWeapon == LOW) {
    Mouse.move(0, 0, 1);
  } else if (esc == LOW) {
    Keyboard.write(27);
  } else {
    Keyboard.releaseAll();
    Mouse.release();
  }


  if (precision == LOW) {
    t1 = dx1 / 2;
    t2 = dy1 / 2;

  } else if (quickMode == LOW) {
    t1 = 2 * dx1;
    t2 = 2 * dy1;

  } else if (reset == LOW) {
    t1 = 0;
    t2 = 0;

  } else {
    t1 = dx1;
    t2 = dy1;
  }

  Mouse.move(-t1, t2, 0);


  delay(1);
}