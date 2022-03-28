#pragma once

#include <ctime>
#include <map>

namespace custom_ctime
{
    std::map<uint8_t, uint8_t> months =
    {
        {0, 31}, {1, 28},  {2, 31},
        {3, 30}, {4, 31},  {5, 30},
        {6, 31}, {7, 31},  {8, 30},
        {9, 31}, {10, 30}, {11, 31},
    };

    tm* gmtime(const time_t *_Time/*timestamp format*/)
    {
        if (_Time == nullptr)
            return nullptr;

        tm* date = new tm();
        time_t temp_time = *_Time;

        int32_t timestamp_year = temp_time / 31536000;
        int32_t count_leap_year = timestamp_year / 4;

        temp_time = temp_time - (count_leap_year * 86400);

        date->tm_year = (temp_time / 31536000) + 70;
        temp_time = temp_time % 31536000;

        date->tm_yday = (temp_time / 86400);
        temp_time %= 86400;

        date->tm_hour = temp_time / 3600;
        temp_time %= 3600;

        date->tm_min = temp_time / 60;
        temp_time %= 60;

        date->tm_sec = temp_time;

        int32_t days_in_year = date->tm_yday + 1;
        for (auto i = 0; i != 11; ++i)
        {
            const int32_t count_days = months.at(i);
            if (days_in_year < count_days)
            {
                date->tm_mon = i;
                date->tm_mday = days_in_year;
                break;
            }

            days_in_year -= count_days;
        }

        return date;
    }

    time_t mktime(struct tm *_Tm)
    {
        if (_Tm == nullptr)
            return 0;

        int32_t count_years_after_timestamp = _Tm->tm_year - 70;
        int32_t count_leap_year = count_years_after_timestamp / 4;

        time_t timestamp = static_cast<time_t>(count_years_after_timestamp) * 31536000;
        timestamp += static_cast<time_t>(count_leap_year) * 86400;
        timestamp += static_cast<time_t>(_Tm->tm_yday) * 86400;
        timestamp += static_cast<time_t>(_Tm->tm_hour) * 3600;
        timestamp += static_cast<time_t>(_Tm->tm_min) * 60;
        timestamp += static_cast<time_t>(_Tm->tm_sec);
        return timestamp;
    }
}
