#include "CompositeAlertStrategy.h"

void CompositeAlertStrategy::addStrategy(std::unique_ptr<AlertLevelStrategy> strategy) {
    _strategies.push_back(std::move(strategy));
}

/**
 * @brief Calculates the highest alert level across all diseases the patient has.
 *
 * This method determines the alert level for each disease the patient has by calling the
 * `determineAlertLevel()` method of each strategy. 
 * It then returns the highest alert level found.
 *
 * @param patient The patient for whom the alert level is to be calculated.
 * @param vitals The vitals being added to the patient.
 * @return The highest alert level across all diseases the patient has.
 */
AlertLevel CompositeAlertStrategy::determineAlertLevel(const Patient& patient, const Vitals& vitals) {
    AlertLevel highestAlertLevel = AlertLevel::Green;
    for (const auto& strategy : _strategies) {
        AlertLevel alertLevel = strategy->determineAlertLevel(patient, vitals);
        if (alertLevel > highestAlertLevel) {
            highestAlertLevel = alertLevel;
        }
    }
    return highestAlertLevel;
}