#include "powermeasurementmodel.h"
#include <QDateTime>

PowerMeasurementModel::PowerMeasurementModel(QObject *parent) : QAbstractListModel (parent), m_data()
{
    for(int i = 0; i < 100; ++i)
        m_data.push_back(DataRow( {PwrContainer(i * 100, i)}));
}

int PowerMeasurementModel::rowCount(const QModelIndex &) const
{
    auto retVal = static_cast<int>(m_data.size());
    return retVal;
}

QVariant PowerMeasurementModel::data(const QModelIndex &index, int role) const
{
    auto row = static_cast<size_t>(index.row());
    if (row < m_data.size()){
        switch (role) {
        case MeasurementRoles::Power: return QVariant(m_data.at(row).measurement.getValue());
        case MeasurementRoles::TimeDate: return timestampToString(m_data.at(row).measurement.getUnixTimestamp());
        default: return QVariant();
        }
    }
    return QVariant();
}

QHash<int, QByteArray> PowerMeasurementModel::roleNames() const
{
    static const QHash<int, QByteArray> roles {
        { MeasurementRoles::Power, "Messung" },
        { MeasurementRoles::TimeDate, "Zeit" }
    };
    return roles;
}

void PowerMeasurementModel::sortDescending(bool /*value*/)
{

}

QVariantMap PowerMeasurementModel::get(int row) const
{
    auto data = m_data.at(static_cast<size_t>(row));
    return { {"Strommnessung", data.measurement.getValue()},
        {"Zeitstempel", QVariant(static_cast<int>(data.measurement.getUnixTimestamp()))} };
}

void PowerMeasurementModel::append()
{

}

void PowerMeasurementModel::set()
{

}

void PowerMeasurementModel::remove()
{

}



QString PowerMeasurementModel::timestampToString(long unixTimeStamp) const
{
    return QDateTime::fromTime_t(static_cast<uint>(unixTimeStamp)).toString(Qt::DateFormat::ISODate);
}

long PowerMeasurementModel::stringToTimestamp(const QString &text) const
{
    return static_cast<long>(QDateTime::fromString(text, Qt::DateFormat::ISODate).toTime_t());
}

