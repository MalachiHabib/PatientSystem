#pragma once
#include <vector>
#include <memory>
#include "Person.h"
#include "PatientAlertLevels.h"
#include "AlertLevelStrategy.h"

class Vitals;

class Diagnosis {
public:
	static const std::string BONUS_ERUPTUS;
	static const std::string AMORIA_PHLEBITIS;
	static const std::string MAD_ZOMBIE_DISEASE;
	static const std::string THREE_STOOGES_SYNDROME;
};

class Patient : public Person {
public:
	Patient(const std::string& firstName, const std::string& lastName, std::tm birthday);
	int age() const;
	std::string uid() const;
	std::string humanReadableID() const;
	void addDiagnosis(const std::string& diagnosis);
	const std::string& primaryDiagnosis() const;
	const std::vector<std::string>& diagnoses() const;
	void addVitals(const Vitals* v);
	const std::vector<const Vitals*> vitals() const;
	void setAlertLevel(AlertLevel level);
	const AlertLevel alertLevel() const { return _alertLevel; }

private:
	const void calculateAlertLevels();
	std::unique_ptr<AlertLevelStrategy> _alertStrategy;

protected:
	std::vector<std::string> _diagnosis;
	std::vector<const Vitals*> _vitals;
	AlertLevel _alertLevel;

	friend std::ostream& operator<<(std::ostream& os, const Patient& p);
};

