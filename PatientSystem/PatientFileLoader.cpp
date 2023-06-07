#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include "PatientFileLoader.h"
#include "Patient.h"
#include "Vitals.h"

/**
 * @brief Loads patient data from a given file
 *
 * The file is expected to have the following format:
 * UID | Birthdate | Last Name,First Name | Diagnosis,Diagnosis, ... | Vital1,Vital2,Vital3,Vital4 ; Vital1,Vital2,Vital3,Vital4 ; ...
 *
 * @param fileName The name of the file
 * @return A vector of pointers Patient objects
 * @throw std::runtime_error if the file cannot be opened
 * @throw std::invalid_argument if the vitals input format is invalid
 */
std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& fileName)
{
	std::ifstream inputFile(fileName);
	if (!inputFile) {
		throw std::runtime_error("Failed to open the file: " + fileName);
	}

	std::vector<Patient*> patients;
	std::string line;
	while (getline(inputFile, line)) {
		std::stringstream ss(line);
		std::string field;

		// Load UID
		getline(ss, field, '|');
		const std::string uid = field;

		// Load birthday if in correct format
		getline(ss, field, '|');
		std::tm birthday = {};
		std::istringstream dateStream(field);
		dateStream >> std::get_time(&birthday, "%d-%m-%Y");
		if (dateStream.fail()) {
			throw std::invalid_argument("Invalid birthday format. Expected 'dd-mm-yyyy', but got " + field);
		}

		// Load first and last name if in correct format
		getline(ss, field, '|');
		std::string firstName, lastName;
		const std::size_t commaPosition = field.find(',');
		if (commaPosition != std::string::npos) {
			lastName = field.substr(0, commaPosition);
			firstName = field.substr(commaPosition + 1);
		}
		else {
			throw std::invalid_argument("Invalid name format. Expected 'Last Name, First Name', but got " + field);
		}

		// Load diagnoses
		getline(ss, field, '|');
		std::vector<std::string> diagnoses;
		std::stringstream diagnosisStream(field);
		std::string diagnosis;
		while (getline(diagnosisStream, diagnosis, ',')) {
			diagnoses.push_back(diagnosis);
		}

		Patient* patient = new Patient(firstName, lastName, birthday);
		for (const std::string& diagnosis : diagnoses) {
			patient->addDiagnosis(diagnosis);
		}

		// Load vitals if in correct format
		getline(ss, field, '|');
		std::stringstream vitalsStream(field);
		std::string vitalsRecord;
		while (getline(vitalsStream, vitalsRecord, ';')) {
			std::stringstream vitalsRecordStream(vitalsRecord);
			std::string vitalValue;
			std::vector<float> vitalValues;

			while (getline(vitalsRecordStream, vitalValue, ',')) {
				vitalValues.push_back(std::stof(vitalValue));
			}

			const std::size_t vitalsCount = 4;
			if (vitalValues.size() != vitalsCount) {
				throw std::invalid_argument("Invalid vitals input format. Expected " + std::to_string(vitalsCount) + " values, but got " + std::to_string(vitalValues.size()));
			}

			Vitals* vitals = new Vitals(vitalValues[0], int(vitalValues[1]), int(vitalValues[2]), int(vitalValues[3]));
			patient->addVitals(vitals);
		}

		patients.push_back(patient);
	}

	return patients;
}