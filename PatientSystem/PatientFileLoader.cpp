
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "PatientFileLoader.h"
#include "Patient.h"
#include "Vitals.h"

using namespace std;


std::vector<Patient*> PatientFileLoader::loadPatientFile(const std::string& file)
{
	vector<Patient*> patients{};

    std::ifstream inFile(file);
    if (inFile.is_open()) {
       
    }

    return patients;
}
