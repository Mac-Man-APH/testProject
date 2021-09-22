// This is JUST a test project
#include <Metro.h> 
#include <Wire.h>
#include <RTClib.h>

Metro secTick = Metro(1000);

RTC_DS1307 rtc;

#define pinPumpA 18

char strMsg[200];
int hh, mm, ss;

void setup() {

	Wire.begin();
	Serial.begin(115200);
	while (!Serial && millis() < 5000);

	pinMode(pinPumpA, OUTPUT);

	if (!rtc.isrunning()) {
		Serial.println("RTC is halted!");	
	}
	rtc.begin();
	rtc.adjust(DateTime(DateTime(2021, 8, 19, 10, 0, 0))); //sets the RTC with an explicit date & time

	DateTime now = rtc.now();
	hh = now.hour(); mm = now.minute(); ss = now.second();

	Serial.println("started");
}


void loop() {
	
	if (secTick.check()) {
		digitalWrite(pinPumpA, !digitalRead(pinPumpA));

		DateTime now = rtc.now();
		hh = now.hour(); mm = now.minute(); ss = now.second();

		sprintf(strMsg, "%02d:%02d:%02d", hh, mm, ss); Serial.println(strMsg);
	}
}
