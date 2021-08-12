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

    QJsonArray adsbData() const override;

    void start() override;
    void stop() override;

private slots:
    void get(const QString& request);

    void onFinished(QNetworkReply* reply);

private:
    void parseData(const QJsonArray& data);

    QNetworkAccessManager m_manager;
    QPointer<QNetworkReply> m_lastReply;
    QElapsedTimer m_timer;
    QJsonArray m_adsbData;
    bool m_started = false;
};

} // namespace adsbera::domain

#endif // ADSB_OPENSKY_SOURCE_H
