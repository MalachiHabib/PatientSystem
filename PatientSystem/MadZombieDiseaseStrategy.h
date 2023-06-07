#pragma once
#include "AlertLevelStrategy.h"

class MadZombieDiseaseStrategy : public AlertLevelStrategy {
public:
    AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
