#pragma once
#include "AlertLevelStrategy.h"

class AmoriaPhlebitisStrategy : public AlertLevelStrategy {
public:
    AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
