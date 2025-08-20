#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Simple Rocket class
class Rocket {
public:
    string name;
    double capacity;  // max energy in joules

    Rocket() {
        name = "";
        capacity = 0.0;
    }

    Rocket(string n, double c) {
        name = n;
        capacity = c;
    }

    void display() const {
        cout << "Rocket Name:    " << name << "\n"
             << "Max Energy (J): " << capacity << "\n";
    }
};

// Simple Satellite class
class Satellite {
public:
    string name;
    double mass;     // in kg
    double radius;   // in m

    Satellite() {
        name = "";
        mass = 0.0;
        radius = 0.0;
    }

   
    void input() {
        cout<< "------------ Welcome to Rocket Console------------"<<endl;
        cout << "Enter Satellite Name: ";
        getline(cin, name);

        cout << "Enter Mass (kg): ";
        while (!(cin >> mass) || mass <= 0) {
            cout << "  Please enter a positive number for mass: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Enter Orbital Radius (m): ";
        while (!(cin >> radius) || radius <= 0) {
            cout << "  Please enter a positive number for radius: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void display() const {
        const double g = 9.8;
        double required = mass * g * radius;
        cout << "\n--- Satellite Info ---\n"
             << "Name:   " << name    << "\n"
             << "Mass:   " << mass    << " kg\n"
             << "Radius: " << radius  << " m\n"
             << "Required Energy (J): " << required << "\n";
    }
};

class MissionControl {
private:
    Satellite sat;
    vector<Rocket> rockets;

public:
    MissionControl() {
        // Pre-define three rockets
        rockets.push_back(Rocket("PSLV", 2.5e11));
        rockets.push_back(Rocket("GSLV", 5.8e11));
        rockets.push_back(Rocket("SSLV", 1.2e11));
    }

    void runMission() {
        sat.input();

        // compute required energy
        const double g = 9.8;
        double needed = sat.mass * g * sat.radius;

        // pick smallest rocket that can lift
        int bestIndex = -1;
        for (int i = 0; i < (int)rockets.size(); ++i) {
            if (rockets[i].capacity >= needed &&
               (bestIndex < 0 || rockets[i].capacity < rockets[bestIndex].capacity)) {
                bestIndex = i;
            }
        }

        // display results
        cout << "\n=== Mission Analysis ===\n";
        sat.display();
        if (bestIndex >= 0) {
            cout << "\n== Selected Rocket ==\n";
            rockets[bestIndex].display();
        } else {
            cout << "\nNo compatible rockets available.\n";
        }

        // write report
        ofstream fout("launch_report.txt");
        fout << "Satellite:         " << sat.name << "\n"
             << "Required Energy:   " << needed << " J\n";
        if (bestIndex >= 0) {
            fout << "Selected Rocket:   " << rockets[bestIndex].name << "\n"
                 << "Rocket Capacity:   " << rockets[bestIndex].capacity << " J\n";
        } else {
            fout << "Selected Rocket:   None\n";
        }
        fout.close();

        cout << "\nReport saved to 'launch_report.txt'\n";
    }
};

int main() {
    MissionControl mc;
    mc.runMission();
    return 0;
}
