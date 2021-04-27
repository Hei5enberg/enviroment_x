// Libraries
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <GY521.h>

// HC-SR501 pin's
#define frontPir;
#define rightPir;
#define backPir;
#define leftPir;

// HC-SR04 pin's
#define trigPin;
#define frontEcho;
#define rightEcho;
#define backEcho;
#define leftEcho;

// U8g2 pin's
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

// GY521 pin
GY521 gyro(0x68);

// Other pin's
#define modeSwitch;
#define piezoPin;

// Variables espTone()
int freq = 2000;
int channel = 0;
int resolution = 8;

// Variables
bool modeState;
long echoDuration;
int echoDistance;



void setup() {
	// Start serial
	Serial.begin(115200);

	// U8g2 setup
	u8g2.begin();

	// Pinmode's
	pinMode(modeSwitch, INPUT);
	pinMode(frontPir, INPUT);
	pinMode(rightPir, INPUT);
	pinMode(backPir, INPUT);
	pinMode(frontEcho, INPUT);
	pinMode(rightEcho, INPUT);
	pinMode(backEcho, INPUT);
	pinMode(leftEcho, INPUT);
	pinMode(trigPin, OUTPUT);

	// Final message
	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_9x18B_tf);
	u8g2.drawStr(10, 33, "Enviroment X");
	u8g2.setFont(u8g2_font_5x8_tf);
	u8g2.drawStr(10, 42, "created by");
	u8g2.drawStr(10, 51, "Gijs Vis (Hei5enberg)");
	u8g2.drawStr(10, 60, "Taco Kraima");
	u8g2.sendBuffer();

	espTone(2000, 200);
	delay(500);
	espTone(2000, 200);
	delay(500);
}

void loop() {
    
}

void buildInTest() {
	int frontDistance = getDistance(frontEcho);
	int rightDistance = getDistance(rightEcho);
	int backDistance = getDistance(backEcho);
	int leftDistance = getDistance(leftEcho);

	int frontPirState = digitalRead(frontPir);
	int rightPirState = digitalRead(rightPir); 
	int backPirState = digitalRead(backPir);
	int leftPirState = digitalRead(leftPir);

	u8g2.clearBuffer();
	u8g2.drawStr()
}

// Function to replace tone()
void espTone(int freq, int duration) {
	ledcWriteTone(channel, freq)
	ledcWrite(channel, 255);
	delay(duration);
	ledcWrite(channel, 0);
}

void getDistance(int pin) {
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);

	duration = pulseIn(pin, HIGH);
	distance = duration * 0.034 / 2;

	if (distance > 350 || distance < 0) { return -1; }
	return distance;
}

// void checkMovement(int pin) {
// 	bool pirState = digitalRead()
// }