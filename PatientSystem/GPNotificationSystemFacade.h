#pragma once
#include "Patient.h"
#include "HospitalAlertObserver.h"

class GPNotificationSystemFacade : public HospitalAlertObserver {
public:
	GPNotificationSystemFacade();
	virtual ~GPNotificationSystemFacade();

	void notify(const Patient& patient) override;

private:
	void sendGPNotificationForPatient(Patient* p);
};

