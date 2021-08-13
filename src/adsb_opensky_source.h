#ifndef ADSB_OPENSKY_SOURCE_H
#define ADSB_OPENSKY_SOURCE_H

#include "i_adsb_source.h"

#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QPointer>

namespace adsbera::domain
{
class AdsbOpenskySource : public IAdsbSource
{
    Q_OBJECT

public:
    explicit AdsbOpenskySource(QObject* parent = nullptr);

    jord::domain::Geodetic centerPosition() const override;
    QJsonArray adsbData() const override;

    void start() override;
    void stop() override;

    void setCenterPosition(const jord::domain::Geodetic& position) override;

private slots:
    void get(const QString& request);

    void onFinished(QNetworkReply* reply);

private:
    void parseData(const QJsonArray& data);

    QNetworkAccessManager m_manager;
    QPointer<QNetworkReply> m_lastReply;
    QElapsedTimer m_timer;

    bool m_started = false;
    jord::domain::Geodetic m_centerPosition;
    double m_radius = 0.1;

    QJsonArray m_adsbData;
};

} // namespace adsbera::domain

#endif // ADSB_OPENSKY_SOURCE_H
