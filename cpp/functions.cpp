/** @file  functions.cpp */
#include "../h/functions.h"
#include <string>
#include <algorithm>

enum I { DAY = 0, GROUP = 1, SURNAME = 2, SUBJECT = 3 };

// wskaźnik odpowiedzialny za zapamiętanie adresu nazwiska prowadzącego w drzewie po skończeniu rekurencji
teacher * tAddress = nullptr;

bool loadRecord(teacher * & pRoot, std::string &line)
{
    std::string data[4] = {};

    // ponieważ ciąg cyfr nie może znajdować się w std::string więc zostaje zalakowane miejsce na tymczasowe przechowanie czasu
    season * t = new season;

    if(!(parse(line, data, t)) || !(validData(data, t))) {
        delete t;
        return false;
    }

    // dodaje nazwisko prowadzącego
    loadSurname(pRoot, data[I::SURNAME]);
    // dodaje dzień
    auto dHead = loadDay(tAddress->nextDay, data[I::DAY], day2Number(data[I::DAY]));
    // dodaje lekcję
    loadLesson(dHead->nextLesson, data, t);
    // usunięcie "tymczasowego" czasu
    delete t;
    return true;
}

bool loadSurname(teacher * & pRoot, const std::string & surname)
{
    if (not pRoot) {
        pRoot = new teacher { surname, nullptr, nullptr, nullptr}; 
        // zapisuję pod jakim adresem w pamięci znajduje się prowadzący
        tAddress = pRoot;
        return true;
    }
    else {
        if(surname == pRoot->surname) {
            // zapisuję pod jakim adresem w pamięci znajduje się prowadzący
            tAddress = pRoot;
            return false;
        } else if (surname < pRoot->surname) loadSurname(pRoot->left, surname);
        else loadSurname(pRoot->right, surname);
    }
    return true;
}

day * loadDay(day * & dHead, const std::string & name, const int &num)
{
    day * p = dHead;
    day * prev = dHead;
    if(p){
        if(p->number > num) {
            dHead = new day { name, num, dHead, nullptr };
            return dHead;
        }
        while(p) {
            if(p->number == num) return p;
            if(p->number < num) prev = p;
            else break;
            p = p -> nextDay;
        }
        auto e =  new day { name, num, prev->nextDay, nullptr };
        prev -> nextDay = e;
        return e;
    } else {
        dHead = new day { name, num, dHead, nullptr };
        return dHead;
    }
}

void loadLesson(lessons * & lRoot, const std::string data[], season * tmp)
{
    if (not lRoot) lRoot = new lessons { *tmp, data[I::GROUP], data[I::SUBJECT], nullptr, nullptr };
    else
    {
        if (timePushLeft(tmp, lRoot)) loadLesson(lRoot->left, data, tmp);
        else loadLesson(lRoot->right, data, tmp);
    } 
}

void saveToFiles(teacher * pRoot, const std::string &PATH)
{
    if (pRoot)
    {
        saveToFiles(pRoot->left, PATH);
        std::ofstream file((PATH + pRoot->surname + ".txt").c_str());
        auto dHead = pRoot->nextDay;
        while(dHead) {
            saveRecord(dHead->nextLesson, dHead->name, file);
            dHead = dHead -> nextDay;
        }
        file.close();
        saveToFiles(pRoot->right, PATH);
    } 
}

void saveRecord(lessons * lRoot, const std::string & day, std::ofstream & file)
{
   if (lRoot)
    {
        saveRecord(lRoot->left, day, file);
        lRoot->hours.startHours < 10 ? file << "0" << lRoot->hours.startHours : file << lRoot->hours.startHours;
        file << ":";
        lRoot->hours.startMinutes < 10 ? file << "0" << lRoot->hours.startMinutes : file << lRoot->hours.startMinutes;
        file << "-";
        lRoot->hours.endHours < 10 ? file << "0" << lRoot->hours.endHours : file << lRoot->hours.endHours;
        file << ":";
        lRoot->hours.endMinutes < 10 ? file << "0" << lRoot->hours.endMinutes : file << lRoot->hours.endMinutes;
        file << " ";
        file << day << " " << lRoot->group << " " << lRoot->subject << std::endl;
        saveRecord(lRoot->right, day, file);
    } 
}

void clearMemory(teacher * & pRoot)
{
    if (pRoot)
    {
        clearMemory(pRoot->left);
        auto dHead = pRoot->nextDay;
        while(dHead) {
            removeLessons(dHead->nextLesson);
            auto e = dHead;
            dHead = dHead -> nextDay;
            delete e;
            e = nullptr;
        }
        clearMemory(pRoot->right);
        delete pRoot;
        pRoot = nullptr;
    } 
}

void removeLessons(lessons * lRoot)
{
   if (lRoot)
    {
        removeLessons(lRoot->left);
        removeLessons(lRoot->right);
        delete lRoot;
        lRoot = nullptr;
    } 
}

bool parse(std::string &line, std::string temp[], season * &t)
{
    // dopuszczam, że na początku mogą być spacje
    while(line[0] == ' ') line = line.erase(0,1);

    // sprawdzam czy pobieram cyfry
    if(!(isdigit(line[0]) && isdigit(line[1]))) return false;
    t->startHours = std::stoi(line.substr(0,2));
    line = line.erase(0,3);

    if(!(isdigit(line[0]) && isdigit(line[1]))) return false;
    t->startMinutes = std::stoi(line.substr(0,2));
    line = line.erase(0,3);
    
    if(!(isdigit(line[0]) && isdigit(line[1]))) return false;
    t->endHours = std::stoi(line.substr(0,2));
    line = line.erase(0,3);

    if(!(isdigit(line[0]) && isdigit(line[1]))) return false;
    t->endMinutes = std::stoi(line.substr(0,2));
    line = line.erase(0,2);

    for(int i = 0; i < 4; i++) {
        while(line[0] == ' ') line = line.erase(0,1);
        temp[i] = line.substr(0,line.find(" ")); 
        line.erase(0,temp[i].size()+1);
    } 
    return true;
}

void error(int sgn, std::string msg)
{
    switch(sgn)
    {
        case 35: 
            std::cerr << "Error -> You std::cin wrong value" << std::endl;
        break;
        case 111: 
            std::cerr << "Warning -> Line " << msg << " is empty" << std::endl;
        break;
        case 123: 
            std::cerr << "The database is broken in line " << msg << std::endl;
        break;
        case 145:
            std::cerr << "Can't open file" << std::endl;
        break;
        default:
            std::cerr << "FATAL ERROR - CHECK DATABASE" << std::endl;
    }
}

int day2Number(std::string d)
{
    if(d == "pn") return 1;
    else if (d == "wt") return 2;
    else if (d == "sr") return 3;
    else if (d == "cz") return 4;
    else if (d == "pt") return 5;
    else if (d == "sb") return 6;
    else if (d == "nd") return 7;
    return 0;
}


std::string getPath(const char* LOCATION)
{
    std::string path = LOCATION;
    std::reverse(path.begin(), path.end());
    path.erase(0,path.find("/"));
    std::reverse(path.begin(), path.end());
    return path;
}

bool validData(const std::string data[], season * &t)
{
    for(int i = 0; i < 4; i++)
        if(data[i].empty()) return false;
        
    if(t->startHours > t->endHours ) return false;
    if(t->startHours == t->endHours ) {
        if(t->startMinutes > t->endMinutes ) return false;
    }
    if(t->startHours > 23 || t->startHours < 0) return false;
    if(t->endHours > 23 || t->endHours < 0) return false;
    if(t->startMinutes > 59|| t->startMinutes < 0) return false;
    if(t->endMinutes > 59 || t->endMinutes < 0) return false;
    if(day2Number(data[I::DAY]) == false) return false;
    return true;
}

bool timePushLeft(season * chk, lessons * sgh)
{
    // sprawdzamy cyfra po cyfrze
    if(chk->startHours > sgh->hours.startHours) return false;
    else if(chk->startHours == sgh->hours.startHours) {
        if (chk->startMinutes > sgh->hours.startMinutes) return false;
        else if (chk->startMinutes == sgh->hours.startMinutes) {
            if(chk->endHours > sgh->hours.endHours) return false;
            else if(chk->endHours == sgh->hours.endHours) {
                if(chk->endMinutes > sgh->hours.endMinutes) return false;
                else return true;
            }
            return true;
        }
        return true;
    }
    return true;
}