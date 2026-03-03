#include <iostream>
#include <string>
#include "../../../interface/widgets/widget.h"
#include "../../sumerrors/sumerrors.h"
#include <any>

using namespace std;

void loadwidgeterror(string type, float number) {
    widget(type, number);
};

string loaderrortext(float number) {
    return sumerrors(number);
};