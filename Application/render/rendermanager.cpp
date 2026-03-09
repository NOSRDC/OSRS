//
// Created by Neemaxon on 01.03.2026.
//

#include <iostream>
#include "../core/sources/modules/interface.h"
#include "3d/3d.h"
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>

using namespace std;

void StartUpFilament(QMainWindow* window) {
    Start3DObfuscation(window);
}

void AddRenderClass(string class_object, QJsonDocument position, QJsonDocument orientation, QJsonDocument object_id, QJsonDocument material_ids, QJsonDocument properties, QMainWindow* window) {
    if (class_object == "part") {
        if (position != QJsonDocument() || orientation != QJsonDocument() || object_id != QJsonDocument() || material_ids != QJsonDocument() ) {
            LoadWidgetError("error", 0.6);
        } else {
            LoadWidgetError("console", 0.5);

        }
    }
}
