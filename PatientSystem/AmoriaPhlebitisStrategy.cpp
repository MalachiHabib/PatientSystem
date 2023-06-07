#include "AmoriaPhlebitisStrategy.h"
#include "Patient.h"
#include "Vitals.h"

AlertLevel AmoriaPhlebitisStrategy::determineAlertLevel(const Patient& patient, const Vitals& vitals)
{
    if ((patient.age() < 12 && vitals.BP() < 30) || (patient.age() >= 12 && vitals.BP() < 50)) return AlertLevel::Red;
    else return AlertLevel::Green;
}