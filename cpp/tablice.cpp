#include <iostream>

using namespace std;

int aa[10][20] = {};
int(*const cpa)[20] = aa; // brak op. adresu
int *ap[10];
int i;

int main()
{
    for (i=0; i<10; i++)
	ap[i] = aa[i]; // nie mo¿na odwróciæ!
    ap[3][4] = 5;
    cout << aa[3][4] << endl;
    cout << cpa[3][4] << endl;
    cout << sizeof(aa) << ", " << sizeof(aa[1]) << endl;
    cout << sizeof(cpa) << ", " << sizeof(cpa[1]) << endl;
    cout << sizeof(ap) << ", " << sizeof(ap[1]) << endl;
    getchar();
}
