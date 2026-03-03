//
// Created by Neemaxon on 01.03.2026.
//

#include <iostream>
#include <filament/Engine.h>
#include <vector>
#include <fstream>
#include <any>
#include "../../../core/sources/modules/phases.h"

using namespace std;

void print(string text) {
    cout << "!PRINT: " << text << "\n";
}

int isstudio() {
    if (is()) {
        return true;
    } else {
        return false;
    }
}

void warn(string text) {
    cout << "!WARNING: " << text << "\n";
}

void error(string text) {
    cout << "!ERROR: " << text << "\n";
}

