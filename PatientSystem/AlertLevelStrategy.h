#pragma once
#include "Vitals.h"
#include "PatientAlertLevels.h"

//forward declaration to avoid circular dependency
class Patient;

class AlertLevelStrategy {
public:
    virtual ~AlertLevelStrategy() = default;
    virtual AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) = 0;
};
