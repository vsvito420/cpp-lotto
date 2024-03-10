#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <sstream>
using namespace std;

class Lotto {
public:
    virtual void generateNumbers() = 0;
    void addNumber(int number);
    void printNumbers();
    void saveNumbers(const string& filename);
    void loadNumbers(const string& filename);
protected:
    vector<int> numbers;
};

void Lotto::addNumber(int number) {
    if (find(numbers.begin(), numbers.end(), number) != numbers.end()) {
        cout << "Duplikat! Bitte gib eine andere Zahl ein." << endl;
        return;
    }
    if (numbers.size() >= 30) {
        cout << "Maximale Anzahl an Zahlen erreicht." << endl;
        return;
    }
    numbers.push_back(number);
}

void Lotto::printNumbers() {
    for (int i = 0; i < numbers.size(); i++) {
        cout << numbers[i];
        if (i != numbers.size() - 1) {
            cout << ", ";
        }
    }
    cout << endl;
}

void Lotto::saveNumbers(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cerr << "Fehler beim Öffnen der Datei zum Schreiben." << endl;
        return;
    }
    for (int i = 0; i < numbers.size(); i++) {
        outfile << numbers[i];
        if (i != numbers.size() - 1) {
            outfile << ", ";
        }
    }
    outfile << endl;
    outfile.close();
}

void Lotto::loadNumbers(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Fehler beim Öffnen der Datei zum Lesen." << endl;
        return;
    }
    string line;
    getline(infile, line);
    stringstream ss(line);
    string token;
    numbers.clear();
    while (getline(ss, token, ',')) {
        numbers.push_back(stoi(token));
    }
    infile.close();
}

class Lotto6aus49 : public Lotto {
public:
    void generateNumbers();
};

void Lotto6aus49::generateNumbers() {
    srand(time(0));
    while (numbers.size() < 6) {
        int number = rand() % 49 + 1;
        addNumber(number);
    }
}

class Eurolotto : public Lotto {
public:
    void generateNumbers();
};

void Eurolotto::generateNumbers() {
    srand(time(0));
    while (numbers.size() < 5) {
        int number = rand() % 50 + 1;
        addNumber(number);
    }
    int number = rand() % 12 + 1;
    addNumber(number);
}

int main() {
    int choice;
    cout << "1. Lotto 6 aus 49" << endl;
    cout << "2. Eurolotto" << endl;
    cout << "3. Eigene Zahlen eingeben" << endl;
    cout << "4. Speichern" << endl;
    cout << "5. Laden" << endl;
    cout << "6. Ende des Programmes" << endl;
    cout << "Bitte waehlen Sie eine Option aus: ";
    cin >> choice;
    string filename;
    string loadFilename;
    Lotto* lotto;
    switch (choice) {
        case 1:
            lotto = new Lotto6aus49();
            lotto->generateNumbers();
            lotto->printNumbers();
            break;
        case 2:
            lotto = new Eurolotto();
            lotto->generateNumbers();
            lotto->printNumbers();
            break;
        case 3:
            lotto = new Lotto6aus49();
            int number;
            cout << "Geben Sie bis zu 30 Zahlen ein (-1 zum Beenden): ";
            while (cin >> number && number != -1) {
                lotto->addNumber(number);
            }
            lotto->printNumbers();
            break;
        case 4:
            cout << "Geben Sie den Dateinamen zum Speichern ein: ";
            cin >> filename;
            lotto->saveNumbers(filename);
            break;
        case 5:
            cout << "Geben Sie den Dateinamen zum Laden ein: ";
            cin >> loadFilename;
            lotto->loadNumbers(loadFilename);
            lotto->printNumbers();
            break;
        case 6:
            delete lotto;
            return 0;
        default:
            cout << "Ungueltige Eingabe." << endl;
            delete lotto;
            return 1;
    }
    delete lotto;
    return 0;
}
