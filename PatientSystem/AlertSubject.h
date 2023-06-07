#pragma once
#include "HospitalAlertObserver.h"

class AlertSubject {
public:
	virtual ~AlertSubject() = default;
	virtual void registerObserver(HospitalAlertObserver* observer) = 0;
	virtual void removeObserver(HospitalAlertObserver* observer) = 0;
	virtual void notifyObservers() = 0;
};