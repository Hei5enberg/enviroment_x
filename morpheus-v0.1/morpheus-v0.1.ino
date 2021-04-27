// Libraries
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <GY521.h>

// HC-SR501 pin's
#define frontPir -1
#define rightPir -1
#define backPir  -1
#define leftPir  -1

// HC-SR04 pin's
#define trigPin -1
#define frontEcho -1
#define rightEcho -1
#define backEcho -1
#define leftEcho -1

// U8g2 pin's
U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

// GY521 pin
GY521 gyro(0x68);

// Other pin's
#define modeSwitch -1
#define piezoPin -1

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

	// espTone setup
	ledcSetup(channel, freq, resolution);
	ledcAttachPin(piezoPin, channel);

	// GY521 

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
	// If the mode switch is HIGH go into BIT
	if (digitalRead(modeSwitch) == HIGH) {
		buildInTest();
		delay(10);
		return;
	}

	// Main code goes here
}

void buildInTest() {
	const int frontDistance = getDistance(frontEcho);
	const int rightDistance = getDistance(rightEcho);
	const int backDistance  = getDistance(backEcho);
	const int leftDistance  = getDistance(leftEcho);

	int frontPirState = digitalRead(frontPir);
	int rightPirState = digitalRead(rightPir); 
	int backPirState  = digitalRead(backPir);
	int leftPirState  = digitalRead(leftPir);

	u8g2.clearBuffer();
	u8g2.setFont(u8g2_font_5x8_tf);
	u8g2.drawStr(10, 10, "Build In Test");
	u8g2.drawLine(0, 10, 127, 10);
	u8g2.drawStr(10, 20, "The quick brown fox jumps over the lazy dog");

	u8g2.setCursor(10, 28);
	u8g2.print("Front: ");
	u8g2.print(frontDistance);
	u8g2.print("cm");

	u8g2.setCursor(10, 37);
	u8g2.print("Right: ");
	u8g2.print(rightDistance);
	u8g2.print("cm");

	u8g2.setCursor(10, 46);
	u8g2.print("Back : ");
	u8g2.print(backDistance);
	u8g2.print("cm");

	u8g2.setCursor(10, 55);
	u8g2.print("Left : ");
	u8g2.print(leftDistance);
	u8g2.print("cm");

	u8g2.drawLine(42, 36, 42, 55);

	u8g2.setCursor(43, 28);
	u8g2.print(frontPirState);
	u8g2.setCursor(43, 37);
	u8g2.print(rightPirState);
	u8g2.setCursor(43, 46);
	u8g2.print(backPirState);
	u8g2.setCursor(43, 55);
	u8g2.print(leftPirState);

	// Code to write GY521 info here

	u8g2.setFont(u8g2_font_4x6_tf);
	u8g2.drawStr(10, 58, "Read readme.md for explanation of BIT");

	u8g2.sendBuffer();
}

// Function to replace tone() for arduino
void espTone(int freq, int duration) {
	ledcWriteTone(channel, freq);
	ledcWrite(channel, 255);
	delay(duration);
	ledcWrite(channel, 0);
}

int getDistance(int pin) {
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