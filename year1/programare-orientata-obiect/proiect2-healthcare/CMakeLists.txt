cmake_minimum_required(VERSION 3.24)
project(oop_healthcare)

set(CMAKE_CXX_STANDARD 17)

add_executable(oop_healthcare main.cpp people/Patient.cpp people/Patient.h treatment/Treatment.cpp treatment/Treatment.h people/Doctor.cpp people/Doctor.h people/SurgeonDoctor.cpp people/SurgeonDoctor.h treatment/MedicationTreatment.cpp treatment/MedicationTreatment.h Date.h Medication.h treatment/FirstAidTreatment.cpp treatment/FirstAidTreatment.h treatment/SurgeryTreatment.cpp treatment/SurgeryTreatment.h treatment/CrashTreatment.cpp treatment/CrashTreatment.h Database.cpp Database.h Demo.cpp Demo.h DrawingUtil.h Data.h GameScreen.h GameScreen.cpp IOInterface.h)
