#pragma once

#include "powervalue.h"
#include <utility>

namespace DataContainer {
namespace Power {


template<typename PowerUnit = kWh>
class PowerMeasurement{
public:

    constexpr PowerMeasurement() : m_powerValue(0), m_unixTimestamp(0){}
    constexpr PowerMeasurement(const PowerValue<PowerUnit> value, long unixTimestamp) : m_powerValue(value), m_unixTimestamp(unixTimestamp){}

    template <typename T> constexpr PowerMeasurement(const PowerMeasurement<T>& m) : m_powerValue(m.template getValue<PowerUnit>()), m_unixTimestamp(m.getUnixTimestamp()){}
    template <typename T> constexpr PowerMeasurement(PowerMeasurement<T>&& m) : m_powerValue(std::move(m.template getValue<PowerUnit>())), m_unixTimestamp(std::move(m.getUnixTimestamp())){}

    template <typename T> constexpr PowerMeasurement& operator=(const PowerMeasurement<T>& m)noexcept {
        this->m_powerValue = m.template getValue<PowerUnit>();
        this->m_unixTimestamp = m.getUnixTimestamp();
    }
    template <typename T> constexpr PowerMeasurement& operator=(PowerMeasurement<T>&& m)noexcept {
        this->m_powerValue.operator=(std::move(m.template getValue<PowerUnit>));
        this->m_unixTimestamp.operator=(std::move(m.getUnixTimestamp()));
    }

    template<typename T> constexpr bool operator >( const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() >  m.template getValue<kWh>() : this->m_unixTimestamp >  m.getUnixTimestamp());}
    template<typename T> constexpr bool operator >=(const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() >= m.template getValue<kWh>() : this->m_unixTimestamp >  m.getUnixTimestamp());}
    template<typename T> constexpr bool operator < (const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() <  m.template getValue<kWh>() : this->m_unixTimestamp <  m.getUnixTimestamp());}
    template<typename T> constexpr bool operator <=(const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() <= m.template getValue<kWh>() : this->m_unixTimestamp < m.getUnixTimestamp());}
    template<typename T> constexpr bool operator ==(const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() == m.template getValue<kWh>() : false);}
    template<typename T> constexpr bool operator !=(const PowerMeasurement<T> &m) const noexcept{ return (this->m_unixTimestamp == m.getUnixTimestamp() ? this->getValue<kWh>() != m.template getValue<kWh>() : true);}

    template<typename ReturnUnit = PowerUnit>
    constexpr double getValue() const noexcept{ return m_powerValue.template getValue<ReturnUnit>();}

    template<typename TargetPowerUnit = PowerUnit>
    constexpr void setValue(double value) noexcept{ m_powerValue.template setValue<TargetPowerUnit>(value);}

    constexpr auto getUnixTimestamp() const noexcept { return m_unixTimestamp;}
    constexpr void setTime(const long value) { m_unixTimestamp = value;}

private:
    PowerValue<PowerUnit> m_powerValue;
    long m_unixTimestamp;
};


}//namespace Power
}//namespace DataContainer
