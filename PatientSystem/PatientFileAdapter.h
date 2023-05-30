#pragma once

#include "AbstractPatientDatabaseLoader.h"
#include "PatientFileLoader.h"

class PatientFileAdapter : public AbstractPatientDatabaseLoader {
private:
    PatientFileLoader pfl;

public:
    virtual void initialiseConnection() override {
    }

    virtual void loadPatients(std::vector<Patient*>& patientIn) override {
        patientIn = pfl.loadPatientFile("patients.txt");
    }

    virtual void closeConnection() override {
    }
};
