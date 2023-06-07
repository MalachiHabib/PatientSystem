#pragma once

#include "Patient.h"
#include "HospitalAlertObserver.h"

class HospitalAlertSystemFacade : public HospitalAlertObserver {
public:
	HospitalAlertSystemFacade();
	virtual ~HospitalAlertSystemFacade();
	void notify(const Patient& patient) override;

private:
	void sendAlertForPatient(Patient* p);
};

