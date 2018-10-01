#include "Arduino.h"
#define PULSE_LENGTH 10
#define DEBUG_LOGGING false
enum enDistanceUnit {DISTANCE_UNIT_INCH = 0, DISTANCE_UNIT_CM};

class HCSR04{
private:
    unsigned int m_nTriggerPin;
    unsigned int m_nEchoPin;
    enDistanceUnit m_enDefaultUnit;
public:
    HCSR04(unsigned int nTriggerPin, unsigned int nEchoPin);
    virtual ~HCSR04();

    long GetDistance(enDistanceUnit enUnit);
    long GetDistance();
    long GetAverageDistanceForPulses(unsigned int nPulses, enDistanceUnit enUnit);
    long GetAverageDistanceForPulses(unsigned int nPulses);
};
