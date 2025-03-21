#include <Wire.h>
#include <RTClib.h>
#include <SevSeg.h>
#include <EasyButton.h>
#include "config.h"
#include "Period.h"

#define HOURS_PIN A1
#define MINUTES_PIN A2

enum { SETUP, ARMED} state = ARMED;
enum { HOURS, MINUTES } setState = HOURS;

// RTC AND SEVSeg
RTC_DS3231 rtc;
SevSeg sevseg;

// BUTTONS
EasyButton minutesButton(MINUTES_PIN);
EasyButton hoursButton(HOURS_PIN);

// PERIOD
int period = 0;
Period per;

// Rang
bool rang = false;

// TIMES
DateTime now;
DateTime lastTime;
unsigned int hoursSet = 0;
unsigned int minutesSet = 0;
unsigned long prevMillis = 0;
unsigned long periodStartTime = 0;



void showPeriod() {
  char periodString[5];
  if (period == 0) {
    strcpy(periodString, "zi");
  } else {
    strcpy(periodString, "let");
  }

  sevseg.setChars(periodString);
  periodStartTime = millis();
}

void onPress() {
  if(state == ARMED) {
    per.togglePeriod();
    period = per.getPeriod();
    showPeriod();
    // DateTime currTime = rtc.now();
    // DateTime newTime;

    // // Adjust time for period
    // if (period == 1) {
    //   newTime = now + TimeSpan(0, 1, 0, 0);
    // } else {
    //   newTime = now - TimeSpan(0, 1, 0, 0);
    // }
    // rtc.adjust(newTime);
  }
}

void longPress() {
  
  if(state == SETUP) {
    
    if(hoursSet == 0) {
      hoursSet = 23;
    } else {
      hoursSet -= 1;
    }

    rtc.adjust(DateTime(2024, 6, 2, hoursSet, minutesSet, 0));

    state = ARMED;
  } else {
    now = rtc.now();
    hoursSet = now.hour();
    minutesSet = now.minute();
    state = SETUP;
  }
}


void addHours() {
  if(hoursSet >= 23) {
    hoursSet = 0;
  } else {
    hoursSet += 1;
  }
}

void addMinutes() {
  if(minutesSet >= 59) {
    minutesSet = 0;
  } else {
    minutesSet += 1;
  }
}


bool compare(DateTime current) {
  const int (*times)[2];
  int numTimes;

  if (period == 0) {
    times = winterTimes;
    numTimes = 28;
  } else {
    times = summerTimes;
    numTimes = 28;
  }

  int hour = current.hour();
  int minute = current.minute();
  
  for (int i = 0; i < numTimes; i++) {
    int targetHour = times[i][0];
    int targetMinute = times[i][1];

    if (hour == targetHour && minute == targetMinute) {
      
      return true;
    }
  }
  return false;
}


void ringBell() {
  digitalWrite(relay, ON);
  delay(5000);
  digitalWrite(relay, OFF);
  delay(5000);
  rang = true;
}


void setup() {

  // Serial.begin(9600);
  
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins, updateWithDelays, updateWithDelays, leadingZeros);
  // EEPROM.begin(EEPROM_SIZE);

  sevseg.setBrightness(100);
  hoursButton.begin();
  minutesButton.begin();

  rtc.begin();
  if (! rtc.begin()) {
   
    while (1) delay(10);
  }

  if (rtc.lostPower()) {
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    state = SETUP;
  }
  
  hoursButton.onPressed(onPress);
  hoursButton.onPressedFor(longPressDuration, longPress);
  minutesButton.onPressed(showPeriod);

  pinMode(relay, OUTPUT);
  digitalWrite(relay, OFF);

}

void loop() {
  now = rtc.now();
  unsigned long currentMillis = millis();

  

  switch(state)
  {
    case ARMED:
      if (currentMillis - prevMillis >= interval) {
          prevMillis = currentMillis;
          DateTime now = rtc.now();
          int currentHour = now.hour();
          int currentMinute = now.minute();

          if(lastTime != now) {
            rang = false;
          }

          if(now.second() == 0) {
            if(compare(now) && !rang) {
              ringBell();
            }
          }
          
          sevseg.setNumber(now.hour() * 100 + now.minute(), 2);
          lastTime = now;
      }
      break;
    case SETUP:


      if(hoursButton.wasPressed()) {
        addHours();
      }

      if(minutesButton.wasPressed()) {
        addMinutes();
      }

      sevseg.setNumber(hoursSet * 100 + minutesSet);
      break;
  }

  // Check if period needs to be displayed and for how long
  if (periodStartTime > 0) {
    if (millis() - periodStartTime >= 5000) {
      // Clear the display after 5 seconds
      sevseg.setChars("     "); // Replace with empty characters
      periodStartTime = 0;
    } else {
      // Keep displaying the period within the 5 seconds window
    }
  }

  hoursButton.read();
  minutesButton.read();
  sevseg.refreshDisplay();
  
}
