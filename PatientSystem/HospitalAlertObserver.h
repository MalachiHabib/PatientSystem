#pragma once
#include "Patient.h"

class HospitalAlertObserver {
public:
    virtual ~HospitalAlertObserver() = default;
    virtual void notify(const Patient& patient) = 0;
};