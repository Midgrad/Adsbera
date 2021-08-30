#ifndef I_ADSB_SOURCE_H
#define I_ADSB_SOURCE_H

#include <QJsonArray>
#include <QObject>

#include "geodetic.h"

namespace md::domain
{
class IAdsbSource : public QObject
{
    Q_OBJECT

public:
    IAdsbSource(QObject* parent = nullptr) : QObject(parent)
    {
    }

    virtual Geodetic centerPosition() const = 0;
    virtual QJsonArray adsbData() const = 0;

    virtual void start() = 0;
    virtual void stop() = 0;

    virtual void setCenterPosition(const Geodetic& position) = 0;

signals:
    void adsbDataReceived(QJsonArray adsbData);
};

} // namespace md::domain

#endif // I_ADSB_SOURCE_H
