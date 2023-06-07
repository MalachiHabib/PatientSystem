#include "BonusEruptusStrategy.h"

AlertLevel BonusEruptusStrategy::determineAlertLevel(const Patient& patient, const Vitals& vitals) {
    if (vitals.RR() > 50) return AlertLevel::Red;
    else if (vitals.RR() > 30) return AlertLevel::Orange;
    else if (vitals.RR() > 20) return AlertLevel::Yellow;
    else return AlertLevel::Green;
}
