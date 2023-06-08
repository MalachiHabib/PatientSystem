# Patient Vitals Management System

This system is designed to manage and monitor the vitals of patients in a healthcare setting, with a particular focus on diseases once thought fictional: Bonus Eruptus, Amoria Phlebitis, Mad Zombie Disease, and the Three Stooges Syndrome. It tracks key health data, such as body temperature, blood pressure, heart rate, and respiratory rate. Alerts are sent to the appropriate healthcare professionals when certain thresholds, dependent on the disease in question, are exceeded. The system allows for easy updating and retrieval of patient information and helps facilitate more efficient and effective healthcare delivery.

## Features

- Record and monitor patient vitals 
- Calculate patient alert levels based on specific diseases and their conditions
- Notify relevant healthcare professionals, including GPs and Hospital staff, in case of critical patient conditions
- Load patient data from various sources, with the capability to load from a file
- Maintain a consistent interface for different alert level calculation strategies for different diseases
- Use of Composite Pattern to manage multiple alert level strategies
- Use of Observer Pattern to notify GP and Hospital staff when a patient's alert level becomes critical
- Alert levels are ranked as Green, Yellow, Orange, Red, with Green being the lowest and Red being the highest alert level. A patient defaults to the Green alert level unless their vitals indicate a higher level.

**Note:** In this documentation, 'interface' and 'abstract base class' are used interchangeably, which is a common practice in general system design terminology. However, in the context of C++, which this design is set to implement, they aren't identical. C++ simulates an interface as an abstract base class that only contains pure virtual functions. Furthermore, inherited methods from abstract base classes (interfaces) are not explicitly shown in the derived classes for clarity and to avoid redundancy. It should be assumed that there is a concrete implementation of all interface methods in all child classes. Also, when interpreting the UML class diagram, note that the relationship between Patient and its nested static class Diagnosis is represented using the nested UML symbol for readability.

![Untitled (7)](https://github.com/MalachiHabib/PatientSystem/assets/91229989/86ca5b32-9238-487c-a3fb-9c1fcc9661f7)
