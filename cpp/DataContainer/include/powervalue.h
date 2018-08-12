#pragma once


namespace DataContainer {
namespace Power {

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
    if(value == 0) return value;
    return value / PowerUnit::factorTokWh;
}

template<typename PowerUnit>
constexpr double extendFromkWh(double value) noexcept {
    if(value == 0) return value;
    return value * PowerUnit::factorTokWh;

}
} //namespace Details

template<typename PowerUnit = kWh>
class PowerValue
{
public:
    //    constexpr PowerValue() noexcept;
    constexpr PowerValue() noexcept :m_value(0)  {}
    template <typename T> constexpr PowerValue(T value) noexcept: m_value(Details::normalizeTokWh<PowerUnit>(static_cast<double>(value))) {}
    constexpr PowerValue(const PowerValue&) noexcept = default;
    constexpr PowerValue(PowerValue&&) noexcept = default;

    constexpr PowerValue& operator=(const PowerValue&)noexcept = default;
    constexpr PowerValue& operator=(PowerValue&&)noexcept = default;

    template<typename T> constexpr bool operator >(const PowerValue<T> &measurement) const noexcept { return this->getValue<kWh>() > measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator >=(const PowerValue<T> &measurement) const noexcept{ return this->getValue<kWh>() >= measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator <(const PowerValue<T> &measurement) const noexcept { return this->getValue<kWh>() < measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator <=(const PowerValue<T> &measurement) const noexcept{ return this->getValue<kWh>() <= measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator ==(const PowerValue<T> &measurement) const noexcept{ return this->getValue<kWh>() == measurement.template getValue<kWh>();}
    template<typename T> constexpr bool operator !=(const PowerValue<T> &measurement) const noexcept{ return this->getValue<kWh>() != measurement.template getValue<kWh>();}

    template<typename T> constexpr PowerValue operator +(const PowerValue<T> &measurement) const noexcept{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>() + measurement.template getValue<PowerUnit>());}
    template<typename T> constexpr PowerValue operator -(const PowerValue<T> &measurement) const noexcept{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>() - measurement.template getValue<PowerUnit>());}

    constexpr PowerValue operator *(const int value) const noexcept{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>()*value);}
    constexpr PowerValue operator *(const double value) const noexcept{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>()*value);}
    constexpr PowerValue operator /(const int value) const{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>()/value);}
    constexpr PowerValue operator /(const double value) const{ return PowerValue<PowerUnit>(this->getValue<PowerUnit>()/value);}

    template<typename ReturnUnit>
    constexpr double getValue() const noexcept{ return Details::extendFromkWh<ReturnUnit>(m_value);}

    template<typename TargetPowerUnit>
    constexpr void setValue(double value) noexcept{ this->m_value = Details::normalizeTokWh<TargetPowerUnit>(value);}

private:
    double m_value;
};
}// namespace Power
}// namespace DataContainer
