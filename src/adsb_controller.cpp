#include "adsb_controller.h"

#include "opensky_adsb_source.h"

using namespace adsbera::endpoint;

AdsbController::AdsbController(QObject* parent) :
    QObject(parent),
    m_source(new domain::OpenskyAdsbSource(this))
{
}

QJsonArray AdsbController::adsb() const
{
    return m_source->adsbData();
}

void AdsbController::start()
{
    connect(m_source, &domain::IAdsbSource::adsbDataReceived, this, &AdsbController::adsbChanged);
    m_source->start();
}
