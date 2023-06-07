#pragma once
#include <vector>
#include "AlertLevelStrategy.h"

class CompositeAlertStrategy : public AlertLevelStrategy {
private:
    std::vector<std::unique_ptr<AlertLevelStrategy>> _strategies;

public:
    void addStrategy(std::unique_ptr<AlertLevelStrategy> strategy);
    virtual AlertLevel determineAlertLevel(const Patient& patient, const Vitals& vitals) override;
};
