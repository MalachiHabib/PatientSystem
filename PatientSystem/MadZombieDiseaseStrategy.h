#pragma once
#include "AlertLevelStrategy.h"

class MadZombieDiseaseStrategy : public AlertLevelStrategy {
public:
    AlertLevel calculateAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
