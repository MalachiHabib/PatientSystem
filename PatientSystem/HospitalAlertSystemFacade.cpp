#include "HospitalAlertSystemFacade.h"
#include <iostream>

HospitalAlertSystemFacade::HospitalAlertSystemFacade()
{ }

HospitalAlertSystemFacade::~HospitalAlertSystemFacade()
{ }

/**
 * @brief Notify the Hospital Alert System of the current patient state.
 *
 * This method sends the current patient to the Hospital Alert System
 * to determine if an alert should be triggered in the hospital.
 *
 * @param patient The patient to notify about.
 */
void HospitalAlertSystemFacade::notify(const Patient& patient) {
	sendAlertForPatient(&patient);
}

void HospitalAlertSystemFacade::sendAlertForPatient(const Patient* p)
{
	if (p->alertLevel() == AlertLevel::Red) {
		// A mocked alert message. A real message would use an SMS/pager gateway or similar
		std::cout << std::endl;
		std::cout << "\n This is an alert to the hospital:" << std::endl;
		std::cout << "Patient: " << p->humanReadableID() << " has a critical alert level" << std::endl;
	}
}