#pragma once

#include <QAbstractListModel>
#include <vector>

#include "powermeasurement.h"

class QDateTime;

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
    Q_INVOKABLE void append(QString date, QString value);
    Q_INVOKABLE void set();
    Q_INVOKABLE void remove();

private:
    struct DataRow{
        PwrContainer measurement;
    };


    QString timestampToString(long unixTimeStamp) const;
    long stringToTimestamp(const QString& text) const;
    long dateToTimestamp(const QDateTime& date) const;

    std::vector<DataRow> m_data;
};
