#include "adsb_controller.h"

#include <QDebug>

#include "adsb_opensky_source.h"
#include "i_property_tree.h"
#include "locator.h"

namespace
{
constexpr char adsb[] = "adsb";
}

using namespace kjarni::domain;
using namespace adsbera::endpoint;

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
    IPropertyTree* pTree = Locator::get<IPropertyTree>();
    Q_ASSERT(pTree);

    connect(m_source, &domain::IAdsbSource::adsbDataReceived, [this, pTree](const QJsonArray& data) {
        pTree->setProperty(::adsb, data);

        emit adsbChanged(data);
    });

    m_source->start();
}
