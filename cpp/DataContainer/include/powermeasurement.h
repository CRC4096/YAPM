#pragma once

#include <string_view>
#include <type_traits>

namespace DataContainer {



enum class MeasurementUnit : short {
    Wh,
    kWh
};

namespace Details {

//constexpr std::string_view MeasurementUnitToString(const MeasurementUnit unit) noexcept { return "Test"; }
constexpr double normalizeTokWh(long value, MeasurementUnit unit) noexcept{
    return normalizeTokWh(static_cast<double>(value), unit);
}

constexpr double normalizeTokWh(double value, MeasurementUnit unit) noexcept{
    if(value == 0)return value;

    switch (unit) {
    case MeasurementUnit::kWh:
        return value;
    case MeasurementUnit::Wh:
        return (value/1000);
    }
}

constexpr double extendFromkWh(double value, MeasurementUnit unit) noexcept {
    if(value == 0) return value;

    switch (unit) {
    case MeasurementUnit::kWh:
        return value;
    case MeasurementUnit::Wh:
        return value*1000;
    }
}
} //namespace Details

class PowerMeasurementValue{
public:
    template<typename T>
    constexpr PowerMeasurementValue(T value) : m_value(static_cast<double>(value)){}
    //    constexpr PowerMeasurementValue(double value) : m_value(static_cast<double>(value)){}
    constexpr double get(){return m_value;}
private:
    double m_value;
};

class PowerMeasurement
{
public:
    //    constexpr PowerMeasurement() noexcept;
    constexpr PowerMeasurement() noexcept :m_value(0), m_unit(MeasurementUnit::kWh)  {}
    constexpr PowerMeasurement(PowerMeasurementValue value, MeasurementUnit unit) noexcept: m_value(Details::normalizeTokWh(value.get(), unit)), m_unit(unit) {}
    constexpr PowerMeasurement(const PowerMeasurement&) noexcept = default;
    constexpr PowerMeasurement(PowerMeasurement&&) noexcept = default;

    constexpr PowerMeasurement& operator=(const PowerMeasurement&)noexcept = default;
    constexpr PowerMeasurement& operator=(PowerMeasurement&&)noexcept = default;

    constexpr bool operator >(const PowerMeasurement &measurement) const noexcept { return this->getValue(MeasurementUnit::kWh) > measurement.getValue(MeasurementUnit::kWh);}
    constexpr bool operator >=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(MeasurementUnit::kWh) >= measurement.getValue(MeasurementUnit::kWh);}
    constexpr bool operator <(const PowerMeasurement &measurement) const noexcept{ return this->getValue(MeasurementUnit::kWh) < measurement.getValue(MeasurementUnit::kWh);}
    constexpr bool operator <=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(MeasurementUnit::kWh) <= measurement.getValue(MeasurementUnit::kWh);}
    constexpr bool operator ==(const PowerMeasurement &measurement) const noexcept{ return this->getValue(MeasurementUnit::kWh) == measurement.getValue(MeasurementUnit::kWh);}
    constexpr bool operator !=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(MeasurementUnit::kWh) != measurement.getValue(MeasurementUnit::kWh);}

    constexpr PowerMeasurement operator +(const PowerMeasurement &measurement) const noexcept{ return PowerMeasurement(this->getValue(this->m_unit) + measurement.getValue(this->m_unit), this->m_unit);}
    constexpr PowerMeasurement operator -(const PowerMeasurement &measurement) const noexcept{ return PowerMeasurement(this->getValue(this->m_unit) - measurement.getValue(this->m_unit), this->m_unit);}
    constexpr PowerMeasurement operator *(const int value) const noexcept{ return PowerMeasurement(m_value*value, m_unit);}
    constexpr PowerMeasurement operator *(const double value) const noexcept{ return PowerMeasurement(m_value*value, m_unit);}
    constexpr PowerMeasurement operator /(const int value) const{ return PowerMeasurement(m_value/value, m_unit);}
    constexpr PowerMeasurement operator /(const double value) const{ return PowerMeasurement(m_value/value, m_unit);;}

//    constexpr std::string_view toString() const noexcept{ return "Test";}
    constexpr double getValue(const MeasurementUnit unit) const noexcept{ return Details::extendFromkWh(m_value, unit);}

    constexpr void setValue(double value, const MeasurementUnit unit) noexcept{
        this->m_value = Details::normalizeTokWh(value, unit);
        this->m_unit = unit;
    }


private:
    double m_value;
    MeasurementUnit m_unit;
};


}//namespace DataContainer
