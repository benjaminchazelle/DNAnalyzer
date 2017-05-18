#include <iostream>
#include "Communication.h"
using namespace std;

int main() {

	Communication::ObtenirInstance().Ecouter(8282);

	cout << "Hello world" << endl;

	return 0;
}