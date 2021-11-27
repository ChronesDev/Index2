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
            : Duration(duration.count())
        {
        }

    protected:
        double Duration = 0.0;

    public:
        [[nodiscard]] StdChronoDuration GetStdDuration() const { return StdChronoDuration(Duration); }
        INDEX_Property(get = GetStdDuration) StdChronoDuration StdDuration;

    protected:
        template <class T> [[nodiscard]] double DurationCastTo() const
        {
            return std::chrono::duration<double, T>(StdDuration).count();
        }

        template <class T> void SetStdDuration(double duration)
        {
            Duration = std::chrono::duration<double, T>(duration).count();
        }

    public:
        [[nodiscard]] double GetNano() const { return DurationCastTo<RatioNano>(); }
        void SetNano(double d) { SetStdDuration<RatioNano>(d); }
        INDEX_Property(get = GetNano, put = SetNano) double Nano;
        INDEX_Property(get = GetNano, put = SetNano) double NanoSeconds;

        [[nodiscard]] double GetMicro() const { return DurationCastTo<RatioMicro>(); }
        void SetMicro(double d) { SetStdDuration<RatioMicro>(d); }
        INDEX_Property(get = GetMicro, put = SetMicro) double Micro;
        INDEX_Property(get = GetMicro, put = SetMicro) double MicroSeconds;

        [[nodiscard]] double GetMilli() const { return DurationCastTo<RatioMilli>(); }
        void SetMilli(double d) { SetStdDuration<RatioMilli>(d); }
        INDEX_Property(get = GetMilli, put = SetMilli) double Milli;
        INDEX_Property(get = GetMilli, put = SetMilli) double MilliSeconds;

        [[nodiscard]] double GetSec() const { return DurationCastTo<RatioSec>(); }
        void SetSec(double d) { SetStdDuration<RatioSec>(d); }
        INDEX_Property(get = GetSec, put = SetSec) double Sec;
        INDEX_Property(get = GetSec, put = SetSec) double Seconds;

        [[nodiscard]] double GetMin() const { return DurationCastTo<RatioMin>(); }
        void SetMin(double d) { SetStdDuration<RatioMin>(d); }
        INDEX_Property(get = GetMin, put = SetMin) double Min;
        INDEX_Property(get = GetMin, put = SetMin) double Minutes;

        [[nodiscard]] double GetHours() const { return DurationCastTo<RatioHours>(); }
        void SetHours(double d) { SetStdDuration<RatioHours>(d); }
        INDEX_Property(get = GetHours, put = SetHours) double Hours;

        [[nodiscard]] double GetDays() const { return DurationCastTo<RatioDays>(); }
        void SetDays(double d) { SetStdDuration<RatioDays>(d); }
        INDEX_Property(get = GetDays, put = SetDays) double Days;

        [[nodiscard]] double GetWeeks() const { return DurationCastTo<RatioWeeks>(); }
        void SetWeeks(double d) { SetStdDuration<RatioWeeks>(d); }
        INDEX_Property(get = GetWeeks, put = SetWeeks) double Weeks;

        [[nodiscard]] double GetMonths() const { return DurationCastTo<RatioMonths>(); }
        void SetMonths(double d) { SetStdDuration<RatioMonths>(d); }
        INDEX_Property(get = GetMonths, put = SetMonths) double Months;

        [[nodiscard]] double GetYears() const { return DurationCastTo<RatioYears>(); }
        void SetYears(double d) { SetStdDuration<RatioYears>(d); }
        INDEX_Property(get = GetYears, put = SetYears) double Years;

    public:
        TimeSpan Lerp(double v)
        {
            auto ret = TimeSpan();
            ret.Duration = Duration * v;
            return ret;
        }

    public:
        TimeSpan operator+() const { return { +StdDuration }; }
        TimeSpan operator-() const { return { -StdDuration }; }
        TimeSpan operator+(const TimeSpan& other) const { return MakeFromDouble(Duration + other.Duration); }
        TimeSpan operator-(const TimeSpan& other) const { return MakeFromDouble(Duration - other.Duration); }
        TimeSpan& operator+=(const TimeSpan& other)
        {
            Duration += other.Duration;
            return *this;
        }
        TimeSpan& operator-=(const TimeSpan& other)
        {
            Duration -= other.Duration;
            return *this;
        }
        bool operator==(const TimeSpan& other) const { return Duration == other.Duration; }
        bool operator!=(const TimeSpan& other) const { return Duration != other.Duration; }
        bool operator<(const TimeSpan& other) const { return Duration < other.Duration; }
        bool operator>(const TimeSpan& other) const { return Duration > other.Duration; }
        bool operator<=(const TimeSpan& other) const { return Duration <= other.Duration; }
        bool operator>=(const TimeSpan& other) const { return Duration >= other.Duration; }

    protected:
        inline static TimeSpan MakeFromDouble(double durationValue)
        {
            TimeSpan timeSpan;
            timeSpan.Duration = durationValue;
            return timeSpan;
        }

    public:
        template <class T> inline static TimeSpan From(std::chrono::duration<double, T> duration)
        {
            TimeSpan timeSpan;
            timeSpan.Duration = StdChronoDuration(duration).count();
            return timeSpan;
        }
        template <class T> inline static TimeSpan From(double duration)
        {
            return From(std::chrono::duration<double, T>(duration));
        }

        inline static TimeSpan FromNano(double duration) { return From<RatioNano>((double)duration); }
        inline static TimeSpan FromNanoSeconds(double duration) { return From<RatioNano>((double)duration); }
        inline static TimeSpan FromMicro(double duration) { return From<RatioMicro>((double)duration); }
        inline static TimeSpan FromMicroSeconds(double duration) { return From<RatioMicro>((double)duration); }
        inline static TimeSpan FromMilli(double duration) { return From<RatioMilli>((double)duration); }
        inline static TimeSpan FromMilliSeconds(double duration) { return From<RatioMilli>((double)duration); }
        inline static TimeSpan FromSec(double duration) { return From<RatioSec>((double)duration); }
        inline static TimeSpan FromSeconds(double duration) { return From<RatioSec>((double)duration); }
        inline static TimeSpan FromMin(double duration) { return From<RatioMin>((double)duration); }
        inline static TimeSpan FromMinutes(double duration) { return From<RatioMin>((double)duration); }
        inline static TimeSpan FromHours(double duration) { return From<RatioHours>((double)duration); }
        inline static TimeSpan FromDays(double duration) { return From<RatioDays>((double)duration); }
        inline static TimeSpan FromWeeks(double duration) { return From<RatioWeeks>((double)duration); }
        inline static TimeSpan FromMonths(double duration) { return From<RatioMonths>((double)duration); }
        inline static TimeSpan FromYears(double duration) { return From<RatioYears>((double)duration); }

        inline static TimeSpan Zero() { return { }; };
    };
}