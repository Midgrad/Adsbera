#ifndef I_ADSB_SOURCE_H
#define I_ADSB_SOURCE_H

#include <QJsonArray>
#include <QObject>

#include "geodetic.h"

namespace adsbera::domain
{
class IAdsbSource : public QObject
{
    Q_OBJECT

public:
    IAdsbSource(QObject* parent = nullptr) : QObject(parent)
    {
    }

    virtual jord::domain::Geodetic centerPosition() const = 0;
    virtual QJsonArray adsbData() const = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void setCenterPosition(const jord::domain::Geodetic& position) = 0;

signals:
    void adsbDataReceived(QJsonArray adsbData);
};

} // namespace adsbera::domain

#endif // I_ADSB_SOURCE_H
