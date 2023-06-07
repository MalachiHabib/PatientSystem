#pragma once
#include "AlertLevelStrategy.h"

class ThreeStoogesSyndromeStrategy : public AlertLevelStrategy {
public:
    AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
