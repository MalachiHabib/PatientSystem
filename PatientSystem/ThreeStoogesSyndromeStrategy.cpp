#include "ThreeStoogesSyndromeStrategy.h"
#include "Patient.h"
#include "Vitals.h"

AlertLevel ThreeStoogesSyndromeStrategy::calculateAlertLevel(const Patient& patient, const Vitals& vitals)
{
    if ((vitals.RR() > 50 && (patient.age() > 30 || (patient.age() < 12 && vitals.HR() > 100))) ||
        (vitals.RR() > 30 && (patient.age() > 40 || (patient.age() < 12 && vitals.HR() > 100))))
        return AlertLevel::Red;
    else if (vitals.RR() > 30 && (patient.age() > 40 || (patient.age() < 12 && vitals.HR() > 100)))
        return AlertLevel::Yellow;
    else
        return AlertLevel::Green;
}
