#include "module_adsbera.h"

#include <QDebug>
#include <QQmlEngine>

#include "adsb_controller.h"

using namespace adsbera::app;

ModuleAdsbera::ModuleAdsbera()
{
    qmlRegisterType<endpoint::AdsbController>("Dreka.Adsb", 1, 0, "AdsbController");
}

void ModuleAdsbera::visit(QJsonObject& features)
{
    kjarni::utils::insertInArray(features, "menu", "qrc:/Adsb/AdsbView.qml");
}
