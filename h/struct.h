/** @file  struct.h */
#include <string>

/** Struktura przechowująca godzinę*/
struct season {
    // czas jest rozdzielony na osobne liczby
    unsigned int startHours,
                 startMinutes,
                 endHours,
                 endMinutes;
};

/** Gałąź która zawiera informacje o zajęciach prowadzącego w danym dniu */
struct lessons {
    season hours;
    std::string  group, 
                 subject;
    lessons * left;
    lessons * right;
};

/** Gałąź z dniami tygodnia */
struct day {
    std::string name; 
    int number;
    day * nextDay;
    lessons * nextLesson;
};

/** Struktura główna z nazwiskami prowadzących */
struct teacher {
    std::string surname;
    teacher * left;
    teacher * right;
    day * nextDay;
};