#include "adsb_opensky_source.h"

#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

// API: https://opensky-network.org/apidoc/rest.html

namespace
{
constexpr char baseUrl[] = "https://opensky-network.org/api";
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

AdsbOpenskySource::AdsbOpenskySource(QObject* parent) : IAdsbSource(parent)
{
    connect(&m_manager, &QNetworkAccessManager::finished, this, &AdsbOpenskySource::onFinished);
}

QJsonArray AdsbOpenskySource::adsbData() const
{
    return m_adsbData;
}

void AdsbOpenskySource::start()
{
    m_started = true;
    m_timer.start();
    this->get("/states/all?lamin=45.8389&lomin=5.9962&lamax=47.8229&lomax=10.5226");
}

void AdsbOpenskySource::stop()
{
    if (m_lastReply)
    {
        m_lastReply->abort();
        m_lastReply->deleteLater();
    }

    m_started = false;
}

void AdsbOpenskySource::get(const QString& request)
{
    m_lastReply = m_manager.get(QNetworkRequest(QNetworkRequest(QUrl(baseUrl + request))));
}

void AdsbOpenskySource::onFinished(QNetworkReply* reply)
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

    if (m_started && m_timer.elapsed() >= ::timeout)
        this->start();
}

void AdsbOpenskySource::parseData(const QJsonArray& data)
{
    QJsonArray result;
    QJsonArray array;

    for (const QJsonValue& value : data)
    {
        QJsonObject aircraft;

        array = value.toArray();

        if (array.count() > 1) // callsign
            aircraft.insert(::callsign, array[1]);
        if (array.count() > 2) // origin_country
            aircraft.insert(::originCountry, array[2]);
        if (array.count() > 4) // last_contact
            aircraft.insert(::timeUtc, array[4]);
        if (array.count() > 7) // longitude, latitude, baro_altitude
        {
            QJsonObject coordinate;
            coordinate.insert(::longitude, array[5]);
            coordinate.insert(::latitude, array[6]);
            coordinate.insert(::altitude, array[7]);

            aircraft.insert(::position, coordinate);
        }
        if (array.count() > 8) // velocity
            aircraft.insert(::velocity, array[8]);

        if (array.count() > 10) // true_track
            aircraft.insert(::heading, array[10]);

        if (!aircraft.isEmpty())
            result.append(aircraft);
    }

    m_adsbData = result;
    emit adsbDataReceived(m_adsbData);
}