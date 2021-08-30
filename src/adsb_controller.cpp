#include "adsb_controller.h"

#include <QDebug>

#include "adsb_opensky_source.h"
#include "locator.h"

namespace
{
constexpr char adsb[] = "adsb";
constexpr char states[] = "states";
} // namespace

using namespace md::domain;
using namespace md::presentation;

AdsbController::AdsbController(QObject* parent) :
    QObject(parent),
    m_source(new domain::AdsbOpenskySource)
{
}

QJsonArray AdsbController::adsb() const
{
    return m_source->adsbData();
}

QJsonObject AdsbController::centerPosition() const
{
    return m_source->centerPosition().toJson();
}

void AdsbController::setCenterPosition(const QJsonObject& centerPosition)
{
    m_source->setCenterPosition(centerPosition);
}

void AdsbController::start()
{
    connect(m_source, &domain::IAdsbSource::adsbDataReceived, [this](const QJsonArray& data) {
        emit adsbChanged(data);
    });

    m_source->start();
}
