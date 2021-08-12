#include "adsb_controller.h"

#include <QDebug>

#include "adsb_exchange_source.h"
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
    m_source(new domain::AdsbExchangeSource(this))
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
