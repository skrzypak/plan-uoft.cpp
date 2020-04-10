/** @file  functions.h */
#include <iostream>
#include <fstream>
#include <string>
#include "struct.h"

/** Funkcja dodająca pobraną linię z danymi do struktury danych i pośrednio łączy wszystkie trzy struktury w jedną
 * @param pRoot korzeń drzewa z nazwiskami prowadzących
 * @param LINE linia pobrana z pliku
 * @return Funkcja zwaraca true jeśli nie napotkała żadnego błedu lub false jeśli napotkała błąd
 * @warning tworzy samo porządkująca się strukturę
 */
bool loadRecord(teacher * & pRoot, std::string & line);

/** Funkacja zapisuje do pamięci nazwisko prowadzącego do drzewa z nazwiskami
 * @param pRoot korzeń drzewa z nazwiskami prowadzących
 * @param surname nazwisko prowadzącego
 * @warning implementacja rekurencyjna
*/
bool loadSurname (teacher * & pRoot, const std::string & surname);

/** Funkacja sprawdza i zapisuje dzień do listy z dniami
 * @param dHead głowa listy z dniami od danego prowadzącego
 * @param name nazwa dnia
 * @param num numer dnia
 * @return zwraca adres dnia z pamięci
*/
day * loadDay(day * & dHead, const std::string &name, const int & num);

/** Funkcja zapisuje lekcję do drzewa z lekcjami
 * @param lRoot korzeń drzewa z lekcjami
 * @param data wszystkie sparsowane dane
 * @param tmp godzina zajęć
 * @warning implementacja rekurencyjna
*/
void loadLesson(lessons * & lRoot, const std::string data[], season * tmp);

/** Funkcja tworząca plik dla danego prowadzącego i wywołująca funkcję saveRecord do zapisu danych do wskazanego pliku
 *@param pRoot korzeń drzewa z nazwiskami prowadzących
 *@param PATH sciężka gdzie mają zostać zapisane pliki
 *@warning Funkcja zapisuje pliki do folderu SURNAME, który tworzony jest w ścieżce wywołania programu
 *@warning implementacja rekurencyjna
 */
void saveToFiles(teacher * pRoot, const std::string & PATH);

/** Funkcja zapisuje rekord do podanego pliku
* @param lRoot korzeń drzewa z lekcjami
* @param day nazwa dnia
* @param file plik do którego mają zostać zapisane dane
* @warning implementacja rekurencyjna
*/
void saveRecord(lessons * lRoot, const std::string & day, std::ofstream & file);

/** Funkcja zwalnia całą pamięć
* @param pRoot korzeń drzewa z nazwiskami prowadzących
* @warning implementacja rekurencyjna
*/
void clearMemory(teacher * & pRoot);

/** Funkcja usuwa wszystkie lekcje z danego prowadzącego z danego dnia
* lRoot korzeń drzewa z lekcjami
* @warning implementacja rekurencyjna
*/
void removeLessons(lessons * lRoot);

/** Funkcja parsująca dane z pobranej lini
 * @param LINE linia pobrana z pliku
 * @param TEMP tablica zwracająca już rozdzielone dane przez referencję
 * @param T wskaźnik na strukturę z godziną
 * @return TRUE - nie napotkano błędu
 * @return FALSE - napotkano błąd
 * */
bool parse(std::string & line, std::string temp[], season * &t);

/** Bardzo podstawowa obsługa błędów
 * @param SGN numer błędu
 * @param MSG co ma zostać dodane do komunikatu błędu (nie jest wymagane)
 */
void error(int sgn = 0, std::string msg = "");

/** Funkcja konwertuje dzień tygodnia na liczbe
 * @param D dzień tygodnia
 * @return Numer dnia tygodnia
 */
int day2Number(std::string d);

/** Funkcja zwraca ścieżkę wywołania programu
 * @param LOCATION
 * @return PATH
 */
std::string getPath(const char * LOCATION);

/**Funkcja sprawdza poprawność wprowadzanych danych z pliku
 * @param DATA tablica z już sparsowanymi danymi
 * @return TRUE jeśli wszystko będzie ok
 * @return FALSE jeśli napotka błąd
 */
bool validData(const std::string data[], season * &t);

/** Funckja sprawdza, czy podany czas jest poźniejszy czy wcześniejszy
 * @param ckh czas który chcemy przyrównać
 * @param sgh wzór 
 * @return true jeżeli czas jest mniejszy niż wzór
 * @return false jeżeli czas jest większy niż wzór
*/
bool timePushLeft(season * chk, lessons * sgh);