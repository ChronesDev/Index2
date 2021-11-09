#pragma once

#include "../../helpers/include.cc"

namespace Index
{
    struct TimeSpan
    {
    protected:
        using StdChronoClock = std::chrono::high_resolution_clock;
        using StdChronoDuration = std::chrono::duration<double>;

        using RatioNano = std::nano;
        using RatioMicro = std::micro;
        using RatioMilli = std::milli;
        using RatioSec = std::ratio<1>;
        using RatioMin = std::ratio<60>;
        using RatioHours = std::ratio<3600>;
        using RatioDays = std::ratio<86400>;
        using RatioWeeks = std::ratio<604800>;
        using RatioMonths = std::ratio<2629746>;
        using RatioYears = std::ratio<31556952>;

    private:
        TimeSpan() = default;

    public:
        TimeSpan(StdChronoDuration duration)
            : StdDuration(duration)
        {
        }

    public:
        StdChronoDuration StdDuration = StdChronoDuration(0);

    protected:
        template <class T> double DurationCastTo()
        {
            return std::chrono::duration_cast<T, double>(StdDuration).count();
        }

        template <class T> void SetStdDuration(double duration)
        {
            StdDuration = std::chrono::duration_cast<std::chrono::seconds, double>(std::chrono::duration<double, T>(duration));
        }

    public:
        double GetNano() { return DurationCastTo<std::chrono::nanoseconds>(); }
        void SetNano(double d) { SetStdDuration<RatioNano>(d); }
        INDEX_Property(get = GetNano, put = SetNano) double Nano;

        double GetMicro() { return DurationCastTo<std::chrono::microseconds>(); }
        void SetMicro(double d) { SetStdDuration<RatioMicro>(d); }
        INDEX_Property(get = GetMicro, put = SetMicro) double Micro;

        double GetMilli() { return DurationCastTo<std::chrono::milliseconds>(); }
        void SetMilli(double d) { SetStdDuration<RatioMilli>(d); }
        INDEX_Property(get = GetMilli, put = SetMilli) double Milli;

        double GetSec() { return DurationCastTo<std::chrono::seconds>(); }
        void SetSec(double d) { SetStdDuration<RatioSec>(d); }
        INDEX_Property(get = GetSec, put = SetSec) double Sec;

        double GetMin() { return DurationCastTo<std::chrono::minutes>(); }
        void SetMin(double d) { SetStdDuration<RatioMin>(d); }
        INDEX_Property(get = GetMin, put = SetMin) double Min;

        double GetHours() { return DurationCastTo<std::chrono::hours>(); }
        void SetHours(double d) { SetStdDuration<RatioHours>(d); }
        INDEX_Property(get = GetHours, put = SetHours) double Hours;

        double GetDays() { return DurationCastTo<std::chrono::days>(); }
        void SetDays(double d) { SetStdDuration<RatioDays>(d); }
        INDEX_Property(get = GetDays, put = SetDays) double Days;

        double GetWeeks() { return DurationCastTo<std::chrono::weeks>(); }
        void SetWeeks(double d) { SetStdDuration<RatioWeeks>(d); }
        INDEX_Property(get = GetWeeks, put = SetWeeks) double Weeks;

        double GetMonths() { return DurationCastTo<std::chrono::months>(); }
        void SetMonths(double d) { SetStdDuration<RatioMonths>(d); }
        INDEX_Property(get = GetMonths, put = SetMonths) double Months;

        double GetYears() { return DurationCastTo<std::chrono::years>(); }
        void SetYears(double d) { SetStdDuration<RatioYears>(d); }
        INDEX_Property(get = GetYears, put = SetYears) double Years;

    public:
        TimeSpan operator+() const { return TimeSpan(+StdDuration); }
        TimeSpan operator-() const { return TimeSpan(-StdDuration); }
        TimeSpan operator+(const TimeSpan& other) const { return TimeSpan(StdDuration + other.StdDuration); }
        TimeSpan operator-(const TimeSpan& other) const { return TimeSpan(StdDuration - other.StdDuration); }

    public:
        template <class T> inline static TimeSpan From(std::chrono::duration<double, T> duration)
        {
            TimeSpan timeSpan;
            timeSpan.StdDuration = std::chrono::duration_cast<std::chrono::seconds, double>(duration);
            return timeSpan;
        }

        template <class T> inline static TimeSpan From(double duration)
        {
            return From(std::chrono::duration<double, T>(duration));
        }

        inline static TimeSpan FromNano(double duration) { return From<RatioNano>((double)duration); }
        inline static TimeSpan FromMicro(double duration) { return From<RatioMicro>((double)duration); }
        inline static TimeSpan FromMilli(double duration) { return From<RatioMilli>((double)duration); }
        inline static TimeSpan FromSec(double duration) { return From<RatioSec>((double)duration); }
        inline static TimeSpan FromMin(double duration) { return From<RatioMin>((double)duration); }
        inline static TimeSpan FromHours(double duration) { return From<RatioHours>((double)duration); }
        inline static TimeSpan FromDays(double duration) { return From<RatioDays>((double)duration); }
        inline static TimeSpan FromWeeks(double duration) { return From<RatioWeeks>((double)duration); }
        inline static TimeSpan FromMonths(double duration) { return From<RatioMonths>((double)duration); }
        inline static TimeSpan FromYears(double duration) { return From<RatioYears>((double)duration); }
    };
}