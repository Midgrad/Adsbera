#include "adsb_exchange_source.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

// API: https://www.adsbexchange.com/version-2-api-wip/

namespace
{
constexpr char baseUrl[] = "https://public-api.adsbexchange.com/VirtualRadar/AircraftList.json";
constexpr char states[] = "states";

constexpr char callsign[] = "callsign";
constexpr char originCountry[] = "originCountry";
constexpr char timeUtc[] = "timeUtc";
constexpr char position[] = "position";
constexpr char latitude[] = "latitude";
constexpr char longitude[] = "longitude";
constexpr char altitude[] = "altitude";
constexpr char heading[] = "heading";
constexpr char velocity[] = "velocity";

constexpr int timeout = 1000;
} // namespace

using namespace adsbera::domain;

AdsbExchangeSource::AdsbExchangeSource(QObject* parent) : IAdsbSource(parent)
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &AdsbExchangeSource::onFinished);
}

QJsonArray AdsbExchangeSource::adsbData() const
{
    return m_adsbData;
}

void AdsbExchangeSource::start()
{
    m_started = true;
    m_timer.start();

    this->get("");
}

void AdsbExchangeSource::stop()
{
    if (m_lastReply)
    {
        m_lastReply->abort();
        m_lastReply->deleteLater();
    }

    m_started = false;
}

void AdsbExchangeSource::get(const QString& url)
{
    QNetworkRequest request;
    request.setUrl(QUrl("https://adsbx-flight-sim-traffic.p.rapidapi.com/api/aircraft/json/lat/"
                        "%7Blat%7D/lon/%7Blon%7D/dist/25/"));
    request.setRawHeader("x-rapidapi-key", "5a065b3cd0msh3406acf20ce37d6p18787cjsn4d62d0e565c7");
    request.setRawHeader("x-rapidapi-host", "adsbx-flight-sim-traffic.p.rapidapi.com");
    request.setAttribute(QNetworkRequest::CacheLoadControlAttribute, QNetworkRequest::AlwaysNetwork);
    m_lastReply = m_manager.get(request);
}

void AdsbExchangeSource::onFinished(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
        this->parseData(doc.object().value(::states).toArray());
    }
    else
    {
        qWarning() << reply->errorString();
    }

    reply->deleteLater();

    //if (m_started && m_timer.elapsed() >= ::timeout)
    this->start();
}

void AdsbExchangeSource::parseData(const QJsonArray& data)
{
    qDebug() << data;
    //    QJsonArray result;
    //    QJsonArray array;

    //    for (const QJsonValue& value : data)
    //    {
    //        QJsonObject aircraft;

    //        array = value.toArray();

    //        if (array.count() > 1) // callsign
    //            aircraft.insert(::callsign, array[1]);
    //        if (array.count() > 2) // origin_country
    //            aircraft.insert(::originCountry, array[2]);
    //        if (array.count() > 4) // last_contact
    //            aircraft.insert(::timeUtc, array[4]);
    //        if (array.count() > 7) // longitude, latitude, baro_altitude
    //        {
    //            QJsonObject coordinate;
    //            coordinate.insert(::longitude, array[5]);
    //            coordinate.insert(::latitude, array[6]);
    //            coordinate.insert(::altitude, array[7]);

    //            aircraft.insert(::position, coordinate);
    //        }
    //        if (array.count() > 8) // velocity
    //            aircraft.insert(::velocity, array[8]);

    //        if (array.count() > 10) // true_track
    //            aircraft.insert(::heading, array[10]);

    //        if (!aircraft.isEmpty())
    //            result.append(aircraft);
    //    }

    //    m_adsbData = result;
    //    emit adsbDataReceived(m_adsbData);
}
