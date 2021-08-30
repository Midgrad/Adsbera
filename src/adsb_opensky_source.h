#ifndef ADSB_OPENSKY_SOURCE_H
#define ADSB_OPENSKY_SOURCE_H

#include "i_adsb_source.h"

#include <QElapsedTimer>
#include <QNetworkAccessManager>
#include <QPointer>

namespace md::domain
{
class AdsbOpenskySource : public IAdsbSource
{
    Q_OBJECT

public:
    explicit AdsbOpenskySource(QObject* parent = nullptr);

    Geodetic centerPosition() const override;
    QJsonArray adsbData() const override;

    void start() override;
    void stop() override;

    void setCenterPosition(const Geodetic& position) override;

private slots:
    void get(const QString& request);

    void onFinished(QNetworkReply* reply);
    void parseData(const QJsonArray& data);

private:
    QNetworkAccessManager m_manager;
    QPointer<QNetworkReply> m_lastReply;
    QElapsedTimer m_timer;

    bool m_started = false;
    Geodetic m_centerPosition;
    double m_radius = 1.0;

    QJsonArray m_adsbData;
};

} // namespace md::domain

#endif // ADSB_OPENSKY_SOURCE_H
