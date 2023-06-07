#pragma once
#include "AlertLevelStrategy.h"

class BonusEruptusStrategy : public AlertLevelStrategy {
public:
    virtual ~BonusEruptusStrategy() = default;
    AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
