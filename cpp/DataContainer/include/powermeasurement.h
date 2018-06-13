#pragma once

#include "powervalue.h"
#include "chrono"

namespace DataContainer {
namespace Power {

template<typename PowerUnit>
class PowerMeasurement{
public:
    // all of these durations will be part of the C++20 standard
    using days = std::chrono::duration<int, std::ratio<86400>>;
    using weeks = std::chrono::duration<int, std::ratio<604800>>;
    using months = std::chrono::duration<int, std::ratio<2629746>>;
    using years = std::chrono::duration<int, std::ratio<31556952>>;

    constexpr PowerMeasurement() : m_powerValue(0), m_timestamp(std::chrono::milliseconds(0)){}
    constexpr PowerMeasurement(const PowerValue<PowerUnit>& value, std::chrono::system_clock::time_point time) : m_powerValue(value), m_timestamp(time){}
    constexpr PowerMeasurement(const PowerValue<PowerUnit> &value, short minute, short hour, short day, short month, short year)
        : m_powerValue(value), m_timestamp(std::chrono::minutes(minute) + std::chrono::hours(hour) + days(day) + months(month) + years(year)) {}

    constexpr PowerMeasurement(const PowerMeasurement&) = default;
    constexpr PowerMeasurement(PowerMeasurement&&) = default;

    constexpr PowerMeasurement& operator=(const PowerMeasurement&)noexcept = default;
    constexpr PowerMeasurement& operator=(PowerMeasurement&&)noexcept = default;

    template<typename T> constexpr bool operator >( const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp >  measurement.m_timestamp;}
    template<typename T> constexpr bool operator >=(const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp >= measurement.m_timestamp;}
    template<typename T> constexpr bool operator < (const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp <  measurement.m_timestamp;}
    template<typename T> constexpr bool operator <=(const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp <= measurement.m_timestamp;}
    template<typename T> constexpr bool operator ==(const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp == measurement.m_timestamp;}
    template<typename T> constexpr bool operator !=(const PowerMeasurement<T> &measurement) const noexcept{ return this->m_timestamp != measurement.m_timestamp;}

    template<typename ReturnUnit>
    constexpr double getValue() const noexcept{ return m_powerValue.template getValue<ReturnUnit>();}

    template<typename TargetPowerUnit>
    constexpr void setValue(double value) noexcept{ m_powerValue.setValue(value);}

    constexpr auto getTime() const noexcept { return m_timestamp;}
    constexpr long getTimestamp() const { return std::chrono::duration_cast<std::chrono::seconds>(m_timestamp).count();}
    constexpr void setTime(const std::chrono::system_clock::time_point& time){ this->m_timestamp = time;}
    constexpr void setTime(const short minute, const short hour, const short day, const short month, const short year){
        setTime(std::chrono::minutes(minute) + std::chrono::hours(hour) + days(day) + months(month) + years(year));
    }



private:
    PowerValue<PowerUnit> m_powerValue;
    std::chrono::system_clock::time_point m_timestamp;
};


}//namespace Power
}//namespace DataContainer
