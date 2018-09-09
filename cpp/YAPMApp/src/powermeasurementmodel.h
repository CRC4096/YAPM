#pragma once

#include <QAbstractListModel>
#include <vector>
#include <QDateTime>

#include "powermeasurement.h"


class PowerMeasurementModel : public QAbstractListModel
{
    Q_OBJECT

    using Unit = DataContainer::Power::kWh;
    using PwrContainer = DataContainer::Power::PowerMeasurement<Unit>;

public:
    enum MeasurementRoles{
        Power = Qt::DisplayRole,
        TimeDate = Qt::UserRole
    };
    Q_ENUM(MeasurementRoles)

    PowerMeasurementModel(QObject *parent = nullptr);

    // QAbstractItemModel interface
    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

    //Custom Invokable functions
    Q_INVOKABLE void sortDescending(bool value);
    Q_INVOKABLE QVariantMap get(int row) const;
    Q_INVOKABLE void append(const QDateTime &date, const double value);
    Q_INVOKABLE void set(int row, const QDateTime &date, const double value);
    Q_INVOKABLE void remove(int row);

private:
    struct DataRow{
        PwrContainer measurement;

        bool operator<(const DataRow& other) const{
            return measurement < other.measurement;
        }

        bool operator >(const DataRow& other) const {
            return measurement > other.measurement;
        }
    };

    struct ConvertedData{
        double value;
        long timestamp;
    };


    ConvertedData convert(const QString& value, const QString& date);
    QString timestampToString(long unixTimeStamp) const;
    long stringToTimestamp(const QString& text) const;
    long dateToTimestamp(const QDateTime& date) const;

    void sortData();
    size_t findInsertionPlace(const DataRow &row);

    std::vector<DataRow> m_data;
};
