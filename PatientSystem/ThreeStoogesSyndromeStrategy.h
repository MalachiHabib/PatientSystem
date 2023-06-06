#pragma once
#include "AlertLevelStrategy.h"

class ThreeStoogesSyndromeStrategy : public AlertLevelStrategy {
public:
    AlertLevel calculateAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
