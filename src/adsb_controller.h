#ifndef ADSB_CONTROLLER_H
#define ADSB_CONTROLLER_H

#include "i_adsb_source.h"

namespace adsbera::endpoint
{
class AdsbController : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QJsonArray adsb READ adsb NOTIFY adsbChanged)
    Q_PROPERTY(QJsonObject centerPosition READ centerPosition WRITE setCenterPosition NOTIFY
                   centerPositionChanged)

public:
    explicit AdsbController(QObject* parent = nullptr);

    QJsonArray adsb() const;
    QJsonObject centerPosition() const;

public slots:
    void setCenterPosition(const QJsonObject& centerPosition);

    void start();

signals:
    void adsbChanged(QJsonArray adsb);
    void centerPositionChanged();

private:
    domain::IAdsbSource* const m_source;
};
} // namespace adsbera::endpoint

#endif // ADSB_CONTROLLER_H
