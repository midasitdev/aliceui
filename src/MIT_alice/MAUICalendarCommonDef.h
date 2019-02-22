#pragma once


namespace mit::alice
{
    enum class TableCriterion
    {
        DAY = 0,
        MONTH,
        YEAR
    };

    enum class MonthType
    {
        LASTMONTH = 0,
        THISMONTH,
        NEXTMONTH
    };

    enum class DayOfWeek
    {
        SUN = 0,
        MON,
        TUE,
        WEN,
        THU,
        FRI,
        SAT
    };
}
