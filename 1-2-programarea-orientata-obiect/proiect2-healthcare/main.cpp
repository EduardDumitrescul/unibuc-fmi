#include <iostream>
#include "people/Patient.h"
#include "people/Doctor.h"
#include "treatment/Treatment.h"
#include "people/SurgeonDoctor.h"
#include "treatment/FirstAidTreatment.h"
#include "treatment/MedicationTreatment.h"
#include "treatment/SurgeryTreatment.h"
#include "treatment/CrashTreatment.h"
#include "Demo.h"

void testPatientClass() {
    Patient a, b;
    std::cin >> b;
    Patient c(b);
    Patient d = b;

    std::cout << a << b << c << d;

}

void testDoctorClass() {
    Doctor a, b;
    std::cin >> b;
    Doctor c(b);
    Doctor d = b;

    std::cout << a << b << c << d;
}

void testTreatmentClass() {
    Doctor doctor;
    Patient patient;

    Treatment a(&patient, &doctor), b;
    //std::cin >> b;
    Treatment c(b);
    Treatment d = c;
    d = d;
    std::cout << a << b << c << d;

    std::cout << a.toString() << '\n';
    std::cout << b.toString() << '\n';
}

void testSurgeonClass() {
    SurgeonDoctor a, b;
    std::cin >> b;
    SurgeonDoctor c(b);
    std::cout << c;

}

void testFirstAidClass() {
    FirstAidTreatment a, b;
    std::cin >> b;
    std::cout << b;
}

void testMedicationTreatmentClass() {
    MedicationTreatment a;
    std::cin >> a;
    std::cout << a;
}

void testSurgeryTreatmentClass() {
    SurgeryTreatment a;
    std::cin >> a;
    std::cout << a;
}

void testCrashTreatmentClass(){
    CrashTreatment a;
    std::cin >> a;
    std::cout << a;
}


int main() {
    Demo demo;
   demo.run();

//   Doctor* p;
//   SurgeonDoctor d;
//   p = &d;
//   p->printCard(std::cout);
   return 0;
}
