#include "module_adsbera.h"

#include <QDebug>
#include <QQmlEngine>

#include "adsb_controller.h"

using namespace adsbera::app;

ModuleAdsbera::ModuleAdsbera()
{
    qmlRegisterType<endpoint::AdsbController>("Dreka.Adsb", 1, 0, "AdsbController");
}

void ModuleAdsbera::init()
{
}

void ModuleAdsbera::done()
{
}

QJsonObject ModuleAdsbera::qmlEntries() const
{
    return QJsonObject::fromVariantMap({ { "menu", "qrc:/Adsb/AdsbView.qml" } });
}
