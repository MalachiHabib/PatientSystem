#include "Patient.h"
#include "BonusEruptusStrategy.h"
#include "AmoriaPhlebitisStrategy.h"
#include "MadZombieDiseaseStrategy.h"
#include "ThreeStoogesSyndromeStrategy.h"
#include "Vitals.h"
#include <iostream>
#include <iomanip>
#include <sstream>

const std::string Diagnosis::BONUS_ERUPTUS = "BonusEruptus";
const std::string Diagnosis::AMORIA_PHLEBITIS = "AmoriaPhlebitis";
const std::string Diagnosis::MAD_ZOMBIE_DISEASE = "MadZombieDisease";
const std::string Diagnosis::THREE_STOOGES_SYNDROME = "ThreeStoogesSyndrome";

Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{
}

/**
 * @brief Register an observer for alert notifications.
 *
 * This method adds an observer to the list of observers that are
 * notified when the alert level changes.
 *
 * @param observer The observer to register.
 */
void Patient::registerObserver(HospitalAlertObserver* observer) {
	observers.push_back(observer);
}

/**
 * @brief Remove an observer from alert notifications.
 *
 * This method removes an observer from the list of observers that are
 * notified when the alert level changes.
 * This is not used, but would be needed in the real system.
 *
 * @param observer The observer to remove.
 */
void Patient::removeObserver(HospitalAlertObserver* observer) {
	observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

/**
 * @brief Notify all registered observers of the current alert level.
 *
 * This method notifies all registered observers of the current alert
 * level by calling the observer's notify method.
 */
void Patient::notifyObservers() {
	for (HospitalAlertObserver* observer : observers) {
		observer->notify(*this);
	}
}

int Patient::age() const
{
	// an inaccurate age estimate but fine for assignment purposes
	return 2022 - (1900 + _birthday.tm_year);
}

std::string Patient::uid() const
{
	std::stringstream ss;
	ss << (char)std::tolower(_lastName.at(0))
		<< (char)std::tolower(_firstName.at(0))
		<< std::setfill('0') << std::setw(2) << (_birthday.tm_mon + 1)
		<< _birthday.tm_year;
	return ss.str();
}

std::string Patient::humanReadableID() const
{

	return "" + _lastName + ", " + _firstName + " (" + uid() + ")";
}

std::ostream& operator<<(std::ostream& os, const Patient& p)
{
	os << p.uid() << "|" << std::put_time(&p._birthday, "%d-%m-%Y") << "|" << p._lastName << "," << p._firstName << "|";

	auto diagnoses = p.diagnoses();
	for (auto itr = diagnoses.begin(); itr != diagnoses.end(); ++itr) {
		if (itr != diagnoses.begin()) os << ";";
		os << *itr;
	}

	os << "|";

	auto vitals = p.vitals();
	for (auto itr = vitals.begin(); itr != vitals.end(); ++itr) {
		if (itr != vitals.begin()) os << ";";
		os << **itr;
	}

	return os;
}

const std::vector<std::string>& Patient::diagnoses() const
{
	return _diagnosis;
}

/**
 * @brief Adds diagnosis (disease) to a Patient.
 *
 * This method will add diagnosis to a patient.
 * It will add the relevent strategies based on the diseases the patient has to
 * a vecotr within CompositeAlertStrategy.
 * 
 * @param diagnosis A string representation of the disease the Patient has
 * @throws runtime_error when diagnosis is unknown.
 */
void Patient::addDiagnosis(const std::string& diagnosis) {
	_diagnosis.push_back(diagnosis);

	if (diagnosis == Diagnosis::BONUS_ERUPTUS) {
		_alertStrategy->addStrategy(std::make_unique<BonusEruptusStrategy>());
	}
	else if (diagnosis == Diagnosis::AMORIA_PHLEBITIS) {
		_alertStrategy->addStrategy(std::make_unique<AmoriaPhlebitisStrategy>());
	}
	else if (diagnosis == Diagnosis::MAD_ZOMBIE_DISEASE) {
		_alertStrategy->addStrategy(std::make_unique<MadZombieDiseaseStrategy>());
	}
	else if (diagnosis == Diagnosis::THREE_STOOGES_SYNDROME) {
		_alertStrategy->addStrategy(std::make_unique<ThreeStoogesSyndromeStrategy>());
	}
	else {
		throw std::runtime_error("Unknown diagnosis: " + diagnosis);
	}
}

void Patient::addVitals(const Vitals* v)
{
	_vitals.push_back(v);
	calculateAlertLevels();
}

const std::vector<const Vitals*> Patient::vitals() const
{
	return _vitals;
}

/**
 * @brief Calculate the current alert level based on vitals.
 *
 * This method calculates the current alert level based on the vitals
 * of the patient. If the new alert level is higher than the current one,
 * it sets the new alert level.
 */
 void Patient::calculateAlertLevels()
{
	for (const auto& vitals : _vitals)
	{
		AlertLevel newAlertLevel = _alertStrategy->determineAlertLevel(*this, *vitals);
		if (newAlertLevel > _alertLevel)
		{
			setAlertLevel(newAlertLevel);
		}
	}
}

void Patient::setAlertLevel(AlertLevel level)
{
	_alertLevel = level;

	if (_alertLevel > AlertLevel::Green) {
		std::cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			std::cout << "Yellow";
			break;
		case AlertLevel::Orange:
			std::cout << "Orange";
			break;
		case AlertLevel::Red:
			std::cout << "Red";
			notifyObservers();
			break;
		}
		std::cout << std::endl;
	}
}