#include "adsb_controller.h"

#include <QDebug>

#include "i_property_tree.h"
#include "locator.h"
#include "opensky_adsb_source.h"

namespace
{
constexpr char adsb[] = "adsb";
}

using namespace kjarni::domain;
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
    IPropertyTree* pTree = Locator::get<IPropertyTree>();
    Q_ASSERT(pTree);

    connect(m_source, &domain::IAdsbSource::adsbDataReceived, [this, pTree](const QJsonArray& data) {
        pTree->setProperty(::adsb, data);

        emit adsbChanged(data);
    });

    m_source->start();
}
