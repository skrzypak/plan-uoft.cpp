/** @file  main.cpp */
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include "../h/functions.h"

int main(int argc, char * argv[]) {
    if (argc == 3) {
        if (std::string(argv[1]) == "-i") {
            // Czas początkowy
            clock_t start = clock();

            // Wczytanie pliku
            std::ifstream file(argv[2]);

            // Otwieranie pliku i wczytywanie danych
            if (file.good() == false) {
                error(145);
                return 1;
            }

            // Stworzenie punktu początkowego struktury
            teacher * pRoot = nullptr;

            // Tymczasowa zmienna do wczytywania danych + zmienna do zapamiętania numeru lini + wskaźnik do sygnalizacji errora
            std::string line="";
            int numLine =  0;

            std::cout << "I'm reading data from file..." << std::endl;

            // Wczytywanie z pliku do struktury danych i jego zamknięcie
            while(std::getline(file, line)) {
                numLine++;
                if(line.empty()) error(111, std::to_string(numLine));
                else if(loadRecord(pRoot, line) == false) {
                    clearMemory(pRoot);
                    error(123, std::to_string(numLine));
                    return 1;
                }
            }
            file.close();

            // Utworzenie folderu gdzie będą zapisywane dane
            const std::string FOLDER_NAME = "surname";
            const std::string PATH = getPath(argv[0]) + FOLDER_NAME + '/';

            #if defined(_WIN32)
               mkdir(PATH.c_str());
            #elif defined(__linux__)
               mkdir(PATH.c_str(), 0777);
            #endif

            std::cout << "I'm creating files with data..." << std::endl;

            // Zapisywanie do pliku wraz z usuwaniem rekordów
            saveToFiles(pRoot, PATH);
            clearMemory(pRoot);

            std::cout << "I created files here: " << PATH << std::endl;

            std::cout << "Time: " << (double)(clock() - start) / CLOCKS_PER_SEC << " seconds" << std::endl;
            return 0;
        } else {
            std::cout << "USAGE" << std::endl;
            std::cout << "-i <input file> " << std::endl;
            return 1;
        }
    } else {
        std::cout << "USAGE" << std::endl;
        std::cout << "-i <input file> " << std::endl;
        return 1;
    }
}
