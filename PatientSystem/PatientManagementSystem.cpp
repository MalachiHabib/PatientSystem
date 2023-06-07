#include "PatientManagementSystem.h"
#include <iostream>
#include <map>
#include <tuple>
#include "Patient.h"
#include "PatientDatabaseLoader.h"
#include "Vitals.h"
#include "GPNotificationSystemFacade.h"
#include "HospitalAlertSystemFacade.h"
#include "PatientFileAdapter.h"

PatientManagementSystem::PatientManagementSystem() :
	_patientDatabaseLoader(std::make_unique<PatientFileAdapter>()),
	_hospitalAlertSystem(std::make_unique<HospitalAlertSystemFacade>()),
	_gpNotificationSystem(std::make_unique<GPNotificationSystemFacade>())
{
	_patientDatabaseLoader->initialiseConnection();
}

PatientManagementSystem::~PatientManagementSystem()
{
	_patientDatabaseLoader->closeConnection();

	// clear patient memory
	for (Patient* p : _patients) {
		delete p;
	}
}

void PatientManagementSystem::init()
{
	_patientDatabaseLoader->loadPatients(_patients);
	for (Patient* p : _patients) {
		_patientLookup[p->uid()] = p;
	}

	for (Patient* p : _patients) {
		p->registerObserver(_hospitalAlertSystem.get());
		p->registerObserver(_gpNotificationSystem.get());
	}
}

void PatientManagementSystem::run()
{
	printWelcomeMessage();

	bool running = true;
	while (running) {
		printMainMenu();
		int option = 0;
		std::cin >> option;

		// handle basic errors
		if (std::cin.fail()) {
			std::cin.clear(); // clear the error state
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore all remaining characters in the buffer
			continue;
		}

		// switch based on the selected option
		switch (option) {
		case 1:
			printPatients();
			break;
		case 2:
			addVitalsRecord();
			break;
		case 3:
			running = false;
			break;
		}
	}
}

void PatientManagementSystem::addVitalsRecord()
{
	std::cout << "Patients" << std::endl;
	printPatients();
	std::cout << std::endl;
	std::cout << "Enter the patient ID to declare vitals for > ";
	
	std::string pid { "" };
	std::cin >> pid;
	if (_patientLookup.count(pid)) {
		float bodyTemperature;
		int bloodPressure;
		int heartRate;
		int respitoryRate;

		std::cout << "enter body temperature: ";
		std::cin >> bodyTemperature;
		std::cout << "enter blood pressure: ";
		std::cin >> bloodPressure;
		std::cout << "enter heart rate: ";
		std::cin >> heartRate;
		std::cout << "enter respitory rate: ";
		std::cin >> respitoryRate;

		Vitals* v = new Vitals(bodyTemperature, bloodPressure, heartRate, respitoryRate);
		_patientLookup[pid]->addVitals(v);
	}
	else {
		std::cout << "Patient not found" << std::endl;
	}
}

void PatientManagementSystem::printWelcomeMessage() const
{
	std::cout << "WELCOME TO HEALTHCO 4000" << std::endl;
	std::cout << "------------------------" << std::endl;
}

void PatientManagementSystem::printMainMenu() const
{
	std::cout << std::endl << "Select an option:" << std::endl;
	std::cout << "1. List patients" << std::endl;
	std::cout << "2. Add vitals record" << std::endl;
	std::cout << "3. Quit" << std::endl;
	std::cout << "> ";
}

void PatientManagementSystem::printPatients() const
{
	for (Patient* p : _patients) {
		std::cout << *p << std::endl;
	}
}