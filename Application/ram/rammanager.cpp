//
// Created by Neemaxon on 01.03.2026.
//
#include <QJsonDocument>

#include <iostream>
#include "objects.h"
#include <string>

using namespace std;

void StartUpPushBackToTableObjects(string Properties) {
    PushBackToTableObjects(Properties);
}

string StartUpAllFromTableObjects() {
    return AllFromTableObjects();
}

void StartUpClearObjects() {
    ClearObjects();
}
