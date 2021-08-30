#include "module_adsbera.h"

#include <QDebug>
#include <QQmlEngine>

#include "adsb_controller.h"

using namespace md::app;

ModuleAdsbera::ModuleAdsbera()
{
    qmlRegisterType<presentation::AdsbController>("Dreka.Adsb", 1, 0, "AdsbController");
}

void ModuleAdsbera::visit(QJsonObject& features)
{
    md::utils::insertInArray(features, "menu", "qrc:/Adsb/AdsbView.qml");
}
