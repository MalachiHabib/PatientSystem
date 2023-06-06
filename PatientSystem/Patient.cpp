#include "Patient.h"
#include "BonusEruptusStrategy.h"
#include "AmoriaPhlebitisStrategy.h"
#include "MadZombieDiseaseStrategy.h"
#include "ThreeStoogesSyndromeStrategy.h"
#include "Vitals.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

const std::string Diagnosis::BONUS_ERUPTUS = "BonusEruptus";
const std::string Diagnosis::AMORIA_PHLEBITIS = "AmoriaPhlebitis";
const std::string Diagnosis::MAD_ZOMBIE_DISEASE = "MadZombieDisease";
const std::string Diagnosis::THREE_STOOGES_SYNDROME = "ThreeStoogesSyndrome";

Patient::Patient(const std::string& firstName, const std::string& lastName, std::tm birthday) :
	Person(firstName, lastName, birthday),
	_alertLevel(AlertLevel::Green)
{
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

void Patient::addDiagnosis(const std::string& diagnosis)
{
	_diagnosis.push_back(diagnosis);
	cout << this->firstName() + " ";
	cout << primaryDiagnosis() + "\n";
	if (primaryDiagnosis() == Diagnosis::BONUS_ERUPTUS) {
		_alertStrategy = std::make_unique<BonusEruptusStrategy>();
	}
	else if (primaryDiagnosis() == Diagnosis::AMORIA_PHLEBITIS) {
		_alertStrategy = std::make_unique<AmoriaPhlebitisStrategy>();
	}
	else if (primaryDiagnosis() == Diagnosis::MAD_ZOMBIE_DISEASE) {
		_alertStrategy = std::make_unique<MadZombieDiseaseStrategy>();
	}
	else if (primaryDiagnosis() == Diagnosis::THREE_STOOGES_SYNDROME) {
		_alertStrategy = std::make_unique<ThreeStoogesSyndromeStrategy>();
	}
	else {
		throw std::runtime_error("Unknown diagnosis: " + diagnosis);
	}
}

const std::string& Patient::primaryDiagnosis() const
{
	return _diagnosis.front();
}

const std::vector<std::string>& Patient::diagnoses() const
{
	return _diagnosis;
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

const void Patient::calculateAlertLevels()
{
	for (const auto& vitals : _vitals)
	{
		AlertLevel newAlertLevel = _alertStrategy->calculateAlertLevel(*this, *vitals);
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
		cout << "Patient: " << humanReadableID() << "has an alert level: ";
		switch (_alertLevel) {
		case AlertLevel::Yellow:
			cout << "Yellow";
			break;
		case AlertLevel::Orange:
			cout << "Orange";
			break;
		case AlertLevel::Red:
			cout << "Red";
			break;
		}
		cout << endl;
	}
}