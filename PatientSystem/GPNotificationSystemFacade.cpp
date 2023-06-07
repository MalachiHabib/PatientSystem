#include "GPNotificationSystemFacade.h"
#include <iostream>

GPNotificationSystemFacade::GPNotificationSystemFacade()
{ }

GPNotificationSystemFacade::~GPNotificationSystemFacade()
{ }

/**
 * @brief Notify the GP Notification System of the current patient state.
 *
 * This method sends the current patient to the GP Notification System
 * to determine if a notification should be sent to the GP.
 *
 * @param patient The patient to notify about.
 */
void GPNotificationSystemFacade::notify(const Patient& patient) {
	sendGPNotificationForPatient(&patient);
}

void GPNotificationSystemFacade::sendGPNotificationForPatient(const Patient* p)
{
	if (p->alertLevel() > AlertLevel::Orange) {
		// A mocked alert message. A real message would use an SMS/pager gateway or similar
		std::cout << std::endl;
		std::cout << "This is an notification to the GPs:" << std::endl;
		std::cout << "Patient: " << p->humanReadableID() << " should be followed up" << std::endl;
	}
}