#include "module_adsbera.h"

#include <QCoreApplication>
#include <QDebug>
#include <QQmlEngine>

#include "adsb_controller.h"
#include "i_gui_layout.h"
#include "locator.h"

using namespace md::app;

void registerTypes()
{
    qmlRegisterType<md::presentation::AdsbController>("Dreka.Adsb", 1, 0, "AdsbController");
}

Q_COREAPP_STARTUP_FUNCTION(registerTypes);

ModuleAdsbera::ModuleAdsbera()
{
}

void ModuleAdsbera::init()
{
    Locator::get<presentation::IGuiLayout>()->addItem("menu", "qrc:/Adsb/AdsbView.qml");
}
