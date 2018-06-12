#pragma once


namespace DataContainer {

struct kWh {
   constexpr static const double factorTokWh = 1.0;
};

struct Wh {
    constexpr static const double factorTokWh = 1000.0;
};


namespace Details {

template<typename PowerUnit>
constexpr double normalizeTokWh(long value) noexcept{
    return normalizeTokWh<PowerUnit>(static_cast<double>(value));
}

template<typename PowerUnit>
constexpr double normalizeTokWh(double value) noexcept{
    if(value == 0)return value;
    return value / PowerUnit::factorTokWh;
}

template<typename PowerUnit>
constexpr double extendFromkWh(double value) noexcept {
    if(value == 0) return value;
    return value * PowerUnit::factorTokWh;

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

template<typename PowerUnit = kWh>
class PowerMeasurement
{
public:
    //    constexpr PowerMeasurement() noexcept;
    constexpr PowerMeasurement() noexcept :m_value(0)  {}
    constexpr PowerMeasurement(PowerMeasurementValue value) noexcept: m_value(Details::normalizeTokWh<PowerUnit>(value.get())) {}
    constexpr PowerMeasurement(const PowerMeasurement&) noexcept = default;
    constexpr PowerMeasurement(PowerMeasurement&&) noexcept = default;

    constexpr PowerMeasurement& operator=(const PowerMeasurement&)noexcept = default;
    constexpr PowerMeasurement& operator=(PowerMeasurement&&)noexcept = default;

    template<typename T> constexpr bool operator >(const PowerMeasurement<T> &measurement) const noexcept { return this->getValue<kWh>() > measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator >=(const PowerMeasurement<T> &measurement) const noexcept{ return this->getValue<kWh>() >= measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator <(const PowerMeasurement<T> &measurement) const noexcept { return this->getValue<kWh>() < measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator <=(const PowerMeasurement<T> &measurement) const noexcept{ return this->getValue<kWh>() <= measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator ==(const PowerMeasurement<T> &measurement) const noexcept{ return this->getValue<kWh>() == measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator !=(const PowerMeasurement<T> &measurement) const noexcept{ return this->getValue<kWh>() != measurement.template getValue<kWh>();}

    template<typename T> constexpr PowerMeasurement operator +(const PowerMeasurement<T> &measurement) const noexcept{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>() + measurement.template getValue<PowerUnit>());}
    template<typename T> constexpr PowerMeasurement operator -(const PowerMeasurement<T> &measurement) const noexcept{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>() - measurement.template getValue<PowerUnit>());}

    constexpr PowerMeasurement operator *(const int value) const noexcept{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>()*value);}
    constexpr PowerMeasurement operator *(const double value) const noexcept{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>()*value);}
    constexpr PowerMeasurement operator /(const int value) const{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>()/value);}
    constexpr PowerMeasurement operator /(const double value) const{ return PowerMeasurement<PowerUnit>(this->getValue<PowerUnit>()/value);}

    template<typename ReturnUnit>
    constexpr double getValue() const noexcept{ return Details::extendFromkWh<ReturnUnit>(m_value);}

    template<typename TargetPowerUnit>
    constexpr void setValue(double value) noexcept{
        this->m_value = Details::normalizeTokWh<TargetPowerUnit>(value);
    }

private:
    double m_value;
};


}//namespace DataContainer
