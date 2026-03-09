//
// Created by Neemaxon on 28.02.2026.
//

#include "../../render/rendermanager.h"
#include "../../ram/rammanager.h"
#include "../sources/modules/interface.h"
#include <iostream>
#include <string>
#include <any>

#include <QString>
#include <QJsonDocument>
#include <QFile>

using namespace std;

QJsonDocument LoadApiDump() {
    QFile file("../API-Dump.json");

    if (!file.open(QIODevice::ReadOnly))
    {
        LoadWidgetError("error", 0.7);
        return LoadApiDump();
    }

    QByteArray data = file.readAll();
    file.close();

    return QJsonDocument::fromJson(data);
}

void SelectClass(string Object) {
    QJsonDocument API = LoadApiDump();
}

void FilamentClass(string Position,
    string Orientation,
    string Materials_id,
    float Color,
    bool Anchor,
    bool CanCollide,
    bool CanTouch,
    bool CanQuery) {

    // fetch all bools

    int FetchAnchor;
    int FetchCanCollide;
    int FetchCanTouch;
    int FetchCanQuery;

    // fetching

    if (CanCollide) {
        FetchCanCollide = 1;
    } else {
        FetchCanCollide = 0;
    }

    if (CanTouch) {
        FetchCanTouch = 1;
    } else {
        FetchCanTouch = 0;
    }

    if (CanQuery) {
        FetchCanQuery = 1;
    } else {
        FetchCanQuery = 0;
    }

    if (Anchor) {
        FetchAnchor = 1;
    } else {
        FetchAnchor = 0;
    }

    // Position
    QJsonDocument doc1 = QJsonDocument::fromJson(
        QByteArray::fromStdString(Position)
    );

    QJsonObject PositionObj = doc1.object();

    double PO_x = PositionObj["x"].toDouble();
    double PO_y = PositionObj["y"].toDouble();
    double PO_z = PositionObj["z"].toDouble();

    // Orientation
    QJsonDocument doc2 = QJsonDocument::fromJson(
        QByteArray::fromStdString(Orientation)
    );

    QJsonObject OrientationObj = doc2.object();

    double OR_x = OrientationObj["x"].toDouble();
    double OR_y = OrientationObj["y"].toDouble();
    double OR_z = OrientationObj["z"].toDouble();

    // Materials

    QJsonDocument doc3 = QJsonDocument::fromJson(
       QByteArray::fromStdString(Materials_id)
    );

    QJsonObject MaterialsObj = doc3.object();

    int material1_id = MaterialsObj["1"].toInt();
    int material2_id = MaterialsObj["2"].toInt();
    int material3_id = MaterialsObj["3"].toInt();
    int material4_id = MaterialsObj["4"].toInt();

    // print to console

    cout << "Orientation from rbxl/rbxlx/rbxmk = "
    << OR_x
    << " "
    << OR_y
    << " "
    << OR_z
    << " . Position from rbxl/rbxlx/rbxmk = "
    << PO_x
    << " "
    << PO_y
    << " "
    << PO_z
    << " . material_ids from rbxl/rbxlx/rbxmk = "
    << material1_id
    << " "
    << material2_id
    << " "
    << material3_id
    << " "
    << material4_id
    << " . bools from rbxl/rbxlx/rbxmk = "
    << FetchAnchor
    << FetchCanCollide
    << FetchCanTouch
    << FetchCanQuery
    << " "
    << Color
    << "\n";

    // add objects to render

    QJsonObject FromPositionObjToJson;
    QJsonObject FromOrientationObjToJson;
    QJsonObject FromMaterialsObjToJson;

    // Position

    FromPositionObjToJson["x"] = QString::fromStdString(to_string(PO_x));
    FromPositionObjToJson["y"] = QString::fromStdString(to_string(PO_y));
    FromPositionObjToJson["z"] = QString::fromStdString(to_string(PO_z));

    // Orientation

    FromOrientationObjToJson["x"] = QString::fromStdString(to_string(OR_x));
    FromOrientationObjToJson["y"] = QString::fromStdString(to_string(OR_y));
    FromOrientationObjToJson["z"] = QString::fromStdString(to_string(OR_z));

    // Materials

    FromMaterialsObjToJson["1"] = QString::fromStdString(to_string(material1_id));
    FromMaterialsObjToJson["2"] = QString::fromStdString(to_string(material2_id));
    FromMaterialsObjToJson["3"] = QString::fromStdString(to_string(material3_id));
    FromMaterialsObjToJson["4"] = QString::fromStdString(to_string(material4_id));

    // formatting for filament render input manager

    string Filament3DPosition = QJsonDocument(FromPositionObjToJson).toJson().toStdString();;
    string Filament3DOrientation = QJsonDocument(FromOrientationObjToJson).toJson().toStdString();;
    string ToDownloadMaterials_ids = QJsonDocument(FromOrientationObjToJson).toJson().toStdString();;

    // Formatting to Properties Json

    QJsonObject Properties;

    Properties["PositionJsonString"] = QString::fromStdString(Filament3DPosition);
    Properties["OrientationJsonString"] = QString::fromStdString(Filament3DOrientation);
    Properties["CanTouchBoolString"] = QString::fromStdString(to_string(FetchCanTouch));
    Properties["CanCollideBoolString"] = QString::fromStdString(to_string(FetchCanCollide));
    Properties["CanQueryBoolString"] = QString::fromStdString(to_string(FetchCanQuery));
    Properties["AnchorBoolString"] = QString::fromStdString(to_string(FetchAnchor));
    Properties["ColorFloatString"] = QString::fromStdString(to_string(Color));
    Properties["Materials_idsJsonString"] = QString::fromStdString(ToDownloadMaterials_ids);

    string FinalProperties = QJsonDocument(Properties).toJson().toStdString();;

    StartUpPushBackToTableObjects(FinalProperties);
}

