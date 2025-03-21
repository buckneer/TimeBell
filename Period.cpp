
#include <EEPROM.h>
#include "Period.h"

#define ADDR  0



#define PERIOD_WINTER 0
#define PERIOD_SUMMER 1

Period::Period() {
  int saved = EEPROM.read(ADDR);
  _period = saved;
};


void Period::togglePeriod() { 
  int newPeriod;
  if(_period == 0) {
    newPeriod = 1;
  } else {
    newPeriod = 0;
  }
  
  EEPROM.write(ADDR, newPeriod);
  _period = EEPROM.read(ADDR);
};

int Period::getPeriod() {
  return _period;
};