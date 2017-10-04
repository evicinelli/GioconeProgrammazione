#include <iostream>
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "GestoreTurni.hpp"
using namespace std;

int main()
{
    GestoreTurni gt=GestoreTurni();
    gt.init();
    gt.play();
	return 0;
}


