#include <iostream>

using namespace std;

struct Punkt
{
    double x;
    double y;
};

extern Punkt punkt1, punkt2, punkt3;

int main()
{
    cout << "punkt1 == {" << punkt1.x << ", " << punkt1.y << "}\n";
    cout << "punkt2 == {" << punkt2.x << ", " << punkt2.y << "}\n";
    cout << "punkt3 == {" << punkt3.x << ", " << punkt3.y << "}\n";
    punkt2 = punkt1;
    punkt3 = punkt1;
    cout << "po przypisaniach\n";
    cout << "punkt2 == {" << punkt2.x << ", " << punkt2.y << "}\n";
    cout << "punkt3 == {" << punkt3.x << ", " << punkt3.y << "}\n";
    punkt3 = punkt1;
    punkt2 = punkt1;
    cout << "po kolejnych przypisaniach\n";
    cout << "punkt2 == {" << punkt2.x << ", " << punkt2.y << "}\n";
    cout << "punkt3 == {" << punkt3.x << ", " << punkt3.y << "}\n";
	getchar();
}
