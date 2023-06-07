#include "MadZombieDiseaseStrategy.h"
#include "Patient.h"
#include "Vitals.h"

AlertLevel MadZombieDiseaseStrategy::determineAlertLevel(const Patient& patient, const Vitals& vitals)
{
    if (vitals.HR() > 130) return AlertLevel::Red;
    else if (vitals.HR() > 120) return AlertLevel::Orange;
    else if (vitals.HR() > 100) return AlertLevel::Yellow;
    else return AlertLevel::Green;
}
