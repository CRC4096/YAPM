#pragma once


namespace DataContainer {



//enum class PowerUnit : short {
//    Wh,
//    kWh
//};
class PowerUnit {
public:
    enum Units{
        Wh,
        kWh
    };

    constexpr PowerUnit(Units unit) : m_unit(unit){}
    constexpr double getFaktorBasedTokWh() const{
        switch (m_unit) {
        case Units::Wh:
            return 1000.0;
        case Units::kWh:
             return 1.0;
        }
    }


private:
    Units m_unit;
};

namespace Details {

constexpr double normalizeTokWh(long value, PowerUnit unit) noexcept{
    return normalizeTokWh(static_cast<double>(value), unit);
}

constexpr double normalizeTokWh(double value, PowerUnit unit) noexcept{
    if(value == 0)return value;
    return value / unit.getFaktorBasedTokWh();
}

constexpr double extendFromkWh(double value, PowerUnit unit) noexcept {
    if(value == 0) return value;
    return value * unit.getFaktorBasedTokWh();

}
} //namespace Details

class PowerMeasurementValue{
public:
    template<typename T>
    constexpr PowerMeasurementValue(T value) : m_value(static_cast<double>(value)){} //static cast will enforce arithmetic types
    constexpr double get(){return m_value;}
private:
    double m_value;
};

class PowerMeasurement
{
public:
    //    constexpr PowerMeasurement() noexcept;
    constexpr PowerMeasurement() noexcept :m_value(0), m_unit(PowerUnit::kWh)  {}
    constexpr PowerMeasurement(PowerMeasurementValue value, PowerUnit unit = PowerUnit::kWh) noexcept: m_value(Details::normalizeTokWh(value.get(), unit)), m_unit(unit) {}
    constexpr PowerMeasurement(const PowerMeasurement&) noexcept = default;
    constexpr PowerMeasurement(PowerMeasurement&&) noexcept = default;

    constexpr PowerMeasurement& operator=(const PowerMeasurement&)noexcept = default;
    constexpr PowerMeasurement& operator=(PowerMeasurement&&)noexcept = default;

    constexpr bool operator >(const PowerMeasurement &measurement) const noexcept { return this->getValue(PowerUnit::kWh) > measurement.getValue(PowerUnit::kWh);}
    constexpr bool operator >=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(PowerUnit::kWh) >= measurement.getValue(PowerUnit::kWh);}
    constexpr bool operator <(const PowerMeasurement &measurement) const noexcept{ return this->getValue(PowerUnit::kWh) < measurement.getValue(PowerUnit::kWh);}
    constexpr bool operator <=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(PowerUnit::kWh) <= measurement.getValue(PowerUnit::kWh);}
    constexpr bool operator ==(const PowerMeasurement &measurement) const noexcept{ return this->getValue(PowerUnit::kWh) == measurement.getValue(PowerUnit::kWh);}
    constexpr bool operator !=(const PowerMeasurement &measurement) const noexcept{ return this->getValue(PowerUnit::kWh) != measurement.getValue(PowerUnit::kWh);}

    constexpr PowerMeasurement operator +(const PowerMeasurement &measurement) const noexcept{ return PowerMeasurement(this->getValue(this->m_unit) + measurement.getValue(this->m_unit), this->m_unit);}
    constexpr PowerMeasurement operator -(const PowerMeasurement &measurement) const noexcept{ return PowerMeasurement(this->getValue(this->m_unit) - measurement.getValue(this->m_unit), this->m_unit);}
    constexpr PowerMeasurement operator *(const int value) const noexcept{ return PowerMeasurement(m_value*value, m_unit);}
    constexpr PowerMeasurement operator *(const double value) const noexcept{ return PowerMeasurement(m_value*value, m_unit);}
    constexpr PowerMeasurement operator /(const int value) const{ return PowerMeasurement(m_value/value, m_unit);}
    constexpr PowerMeasurement operator /(const double value) const{ return PowerMeasurement(m_value/value, m_unit);;}

    constexpr double getValue(const PowerUnit unit) const noexcept{ return Details::extendFromkWh(m_value, unit);}

    constexpr void setValue(double value, const PowerUnit unit) noexcept{
        this->m_value = Details::normalizeTokWh(value, unit);
        this->m_unit = unit;
    }


private:
    double m_value;
    PowerUnit m_unit;
};


}//namespace DataContainer
