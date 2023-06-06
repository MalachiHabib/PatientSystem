#pragma once
#include "AlertLevelStrategy.h"

class AmoriaPhlebitisStrategy : public AlertLevelStrategy {
public:
    AlertLevel calculateAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
