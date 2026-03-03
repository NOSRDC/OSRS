//
// Created by Neemaxon on 01.03.2026.
//

#ifndef RENDERMANAGER_H
#define RENDERMANAGER_H

//
// Created by Neemaxon on 01.03.2026.
//

#include <iostream>
#include <string>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMainWindow>

void start3d(QMainWindow* window);

void renderclasses(std::string class_object, QJsonDocument position, QJsonDocument orientation, QJsonDocument object_id, QJsonDocument material_ids, QJsonDocument properties, QMainWindow* window);

#endif //