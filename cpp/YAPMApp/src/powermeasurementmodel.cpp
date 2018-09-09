 #include "powermeasurementmodel.h"
#include <QRegularExpression>
#include <QtDebug>

PowerMeasurementModel::PowerMeasurementModel(QObject *parent) : QAbstractListModel (parent), m_data()
{
    for(int i = 0; i < 100; ++i)
        m_data.push_back(DataRow( {PwrContainer(i * 100, i * 60*60*24)}));

    sortData();
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
    return { {"Messung", data.measurement.getValue()},
        {"Zeit", QVariant(timestampToString(data.measurement.getUnixTimestamp()))} };
}

void PowerMeasurementModel::append(const QDateTime& date, const double value)
{
    DataRow row{PwrContainer(value, dateToTimestamp(date))};
    int insertionRow = static_cast<int>(findInsertionPlace(row));

    beginInsertRows(QModelIndex(), insertionRow, static_cast<int>(m_data.size() - 1));
    auto it = m_data.begin();
    std::advance(it, insertionRow);
    m_data.insert(it, std::move(row));
    endInsertRows();
}

void PowerMeasurementModel::set(int row, const QDateTime& date, const double value)
{
    auto& line = m_data.at(static_cast<size_t>(row));
    line.measurement.setTime(dateToTimestamp(date));
    line.measurement.setValue(value);

    beginResetModel();
    sortData();
    endResetModel();
}

void PowerMeasurementModel::remove(int row)
{
    auto it = m_data.begin();
    std::advance(it, row);
    beginRemoveRows(QModelIndex(), row, row);
    m_data.erase(it);
    endRemoveRows();
}

PowerMeasurementModel::ConvertedData PowerMeasurementModel::convert(const QString &value, const QString &date)
{
    PowerMeasurementModel::ConvertedData retVal{
        QString(value).remove(QRegularExpression("[^0-9].")).toDouble(),
        stringToTimestamp(date)
    };
    return retVal;
}



QString PowerMeasurementModel::timestampToString(long unixTimeStamp) const
{
    return QDateTime::fromTime_t(static_cast<uint>(unixTimeStamp)).toString(Qt::DateFormat::ISODate);
}

long PowerMeasurementModel::stringToTimestamp(const QString &text) const
{
    auto temp = QDateTime::fromString(text, Qt::DateFormat::ISODate);
    return dateToTimestamp(temp);
}

long PowerMeasurementModel::dateToTimestamp(const QDateTime &date) const
{
    return static_cast<long>(date.toTime_t());
}

void PowerMeasurementModel::sortData()
{
    std::sort(m_data.begin(), m_data.end(), [](const DataRow& a, const DataRow& b){
        return a.measurement > b.measurement; //sort descending
    });
}

size_t PowerMeasurementModel::findInsertionPlace(const DataRow &row)
{
    //0 will contain the biggest element. Therefor if row is bigger then i, insert at i
    for(size_t i = 0; i < m_data.size(); ++i){
        if(row > m_data.at(i))
            return i;
    }
}

