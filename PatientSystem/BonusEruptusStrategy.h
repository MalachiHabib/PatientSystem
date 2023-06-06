#pragma once
#include "AlertLevelStrategy.h"

class BonusEruptusStrategy : public AlertLevelStrategy {
public:
    virtual ~BonusEruptusStrategy() = default;
    AlertLevel calculateAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
