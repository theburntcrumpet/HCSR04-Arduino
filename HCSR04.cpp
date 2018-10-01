#include "HCSR04.h"

HCSR04::HCSR04(unsigned int nTriggerPin, unsigned int nEchoPin){
    m_nTriggerPin = nTriggerPin;
    m_nEchoPin = nEchoPin;
    m_enDefaultUnit = DISTANCE_UNIT_CM;
    pinMode(m_nTriggerPin, OUTPUT);
    pinMode(m_nEchoPin, INPUT);
    digitalWrite(m_nTriggerPin, LOW);
    delay(5);
}

HCSR04::~HCSR04(){

}

long HCSR04::GetDistance(enDistanceUnit enUnit){
    // Send a pulse out on the trigger pin
    digitalWrite(m_nTriggerPin, HIGH);
    delayMicroseconds(PULSE_LENGTH);
    digitalWrite(m_nTriggerPin, LOW);

    // Read the pulse from the echo pin
    long nPulseDuration = pulseIn(m_nEchoPin,HIGH);

    if(enUnit == DISTANCE_UNIT_CM)
        return (nPulseDuration/2) / 29.1;
    if(enUnit == DISTANCE_UNIT_INCH)
        return (nPulseDuration/2) /74;
    return -1l; // an invalid unit type was entered
}

long HCSR04::GetDistance(){
    return GetDistance(m_enDefaultUnit);
}

long HCSR04::GetAverageDistanceForPulses(unsigned int nPulses,enDistanceUnit enUnit){
    long nTotal = 0l; // Total of all valid pulses measured used to calculate average
    int nValidValues = 0; // Total valid values to divide nTotal by
    
    if(nPulses < 1)
        return -1l;

    int i = nPulses;

    while(i > 0){
        long nCurrentDistance = GetDistance(enUnit);
        if(nCurrentDistance >= 0){
            nTotal += nCurrentDistance;
            nValidValues++;
        }
        i--;
    }

    if(nValidValues < 1)
        return -1l;
    
    long nAvg =  nTotal/(long)nValidValues;
    if(DEBUG_LOGGING)
      Serial.print(nAvg);
    return nAvg;
}

long HCSR04::GetAverageDistanceForPulses(unsigned int nPulses){
    return GetAverageDistanceForPulses(nPulses,m_enDefaultUnit);
}
