//
// Created by Neemaxon on 03.03.2026.
//

#include <vector>
#include <string>
#include <iostream>
#include <string>

#include <QJsonDocument>
#include <QString>
#include <QJsonObject>

using namespace std;

float number = 0;

vector<pair<float, string>> objects = {};

void PushBackToTableObjects(string Properties) {
    number += 0.1;
    objects.push_back({number, Properties});
}

string AllFromTableObjects() {
    QJsonObject obj;

    for (int i = 0; i < objects.size(); i++) { QString::fromStdString(objects[i].second);
        obj[QString::fromStdString(to_string(i))] = QString::fromStdString(objects[i].second);
    }

    return QJsonDocument(obj).toJson().toStdString();
}

void ClearObjects() {
    objects.clear();
}