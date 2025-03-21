
#ifndef PERIOD_H
#define PERIOD_H

class Period {
  public:
    Period();

    void togglePeriod();
    int getPeriod();
  
  private:
    void setPeriod();
    int _period;
};

#endif