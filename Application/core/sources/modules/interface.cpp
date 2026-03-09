#include <iostream>
#include <string>
#include "../../../interface/widgets/widget.h"
#include "../../sumerrors/sumerrors.h"
#include <any>

using namespace std;

void LoadWidgetError(string type, float number) {
    Widget(type, number);
};

string LoadErrorText(float number) {
    return SumErrors(number);
};