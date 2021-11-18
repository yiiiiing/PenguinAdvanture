#ifndef LOGIC_HH
#define LOGIC_HH

#include "actors/passenger.hh"
#include "actors/nysse.hh"
#include "offlinereader.hh"
#include "interfaces/icity.hh"

#include <list>
#include <QTime>
#include <QTimer>


namespace CourseSide
{

// default files
const QString DEFAULT_STOPS_FILE = ":/offlinedata/offlinedata/full_stations_kkj3.json";
const QString DEFAULT_BUSES_FILE = ":/offlinedata/offlinedata/final_bus_liteN.json";

class Logic : public QObject
{
    Q_OBJECT
public:
    Logic(QObject *parent = 0);

    bool readOfflineData(const QString& buses, const QString& stops);

    void finalizeGameStart();

    void fileConfig(QString stops = DEFAULT_STOPS_FILE, QString buses = DEFAULT_BUSES_FILE);

    void setTime(unsigned short hr, unsigned short min);

    bool takeCity(std::shared_ptr<Interface::ICity> city);

public slots:
    void advance();
    void configChanged(QTime time, bool debug);
    void increaseTime();
    void addNewBuses();
    void addNewPassengers(std::shared_ptr<Stop> stop, unsigned int no);

private:
    // ratio between game time and real time
    static const int TIME_SPEED;
    // time between updates in milliseconds
    static const int UPDATE_INTERVAL_MS;

    std::shared_ptr<Interface::ICity> cityif_;
    std::list< std::shared_ptr<Passenger> > passengers_;
    std::list< std::shared_ptr<Nysse> > buses_;
    std::vector< std::shared_ptr<Stop> > stops_;
    std::shared_ptr<OfflineData> offlinedata_;
    QString busfile_;
    QString stopfile_;
    bool debugstate_;
    bool gamestarted_;

    // Current time
    QTime time_;

    // Timer that increments time_ every second
    QTimer timer_;

    // TImer that moves buses in even intervals
    QTimer animationtimer_;

    // Timer that checks departing buses every minute
    QTimer departuretimer_;

    // Returns true if new location was succesfully calculated
    // False if bus arrived to the final stop or it shouldn't be in traffic
    bool calculateNewLocationForBus(std::shared_ptr<Nysse> bussi);

    void addBuses();
    void addStopsAndPassengers();

    // Calculates stop times based on departure times and time spent at stop (Laskee pysäkkiajat lähtöajan ja pysäkille kuluvan ajan perusteella)
    std::map<QTime, std::weak_ptr<Stop>> calculateStopTimes(std::map<QTime, std::shared_ptr<Stop>>& stops, QTime& departure_time);
    void createBus(std::shared_ptr<BusData> bus, QTime departure_time);

    int busSID_;
};

}

#endif // LOGIC_HH
