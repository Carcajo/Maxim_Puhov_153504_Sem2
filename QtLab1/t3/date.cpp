#include "date.h"

Date::Date(int day, int month, int year)
    :m_day(day), m_month(month), m_year(year)
{

}

Date Date::NextDay()
{
    if (m_day == 31 && m_month == 12)
    {
        Date next_day(1, 1, m_year + 1);
        return next_day;
    }
    else if ((m_month == 2 && m_day == 28 && !IsLeap()) || (m_month == 2 && m_day == 29 && IsLeap()))
    {
        Date next_day(1, m_month + 1, m_year);
        return next_day;
    }
    else if ((m_day == 30 && !daysInMonth(m_month)) || (m_day == 31 && daysInMonth(m_month)))
    {
        Date next_day(1, m_month + 1, m_year);
        return next_day;
    }
    else
    {
        Date next_day(m_day + 1, m_month, m_year);
        return next_day;
    }
}

Date Date::PreviousDay()
{
    if (m_day == 1 && m_month == 1)
    {
        Date previous_day(31, 12, m_year - 1);
        return previous_day;
    }
    else if (m_day == 1 && m_month == 3 && !IsLeap())
    {
        Date previous_day(28, 2, m_year);
        return previous_day;
    }
    else if (m_day == 1 && m_month == 3 && IsLeap())
    {
        Date previous_day(29, 2, m_year);
        return previous_day;
    }
    else if (m_day == 1 && !daysInMonth(m_month - 1))
    {
        Date previous_day(30, m_month - 1, m_year);
        return previous_day;
    }
    else if (m_day == 1 && daysInMonth(m_month - 1))
    {
        Date previous_day(31, m_month - 1, m_year);
        return previous_day;
    }
    else
    {
        Date previous_day(m_day - 1, m_month, m_year);
        return previous_day;
    }
}

bool Date::IsLeap()
{
    if ((m_year % 4 == 0 && m_year % 100 != 0) || (m_year % 4 == 0 && m_year % 400 == 0))
    {
        return 1;
    }
    return 0;
}

bool Date::daysInMonth(int month)
{
    if ((month % 2 != 0 && month <= 7) || (month % 2 == 0 && month > 7)) {
        return 1;
    }
    return 0;
}

short Date::DaysNumber()
{
    short arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    short days = 0;
    for (int i = 0; i < m_month; i++) {
        if (m_month == (i+1)) {
            days += m_day;
            break;
        }
        if (m_month > 2 && (i+1) == 2 && IsLeap()) {
            days += 29;
        } else if (m_month > 2 && (i+1) == 2 && !IsLeap()) {
            days += 28;
        }

        if (m_month != (i+1) && (i+1) != 2) {
            days += arr[i];
        }
    }
    return days;
}

short Date::WeekNumber()
{
    short days = this->DaysNumber();
    short weeks = days / 7 +1;
    return weeks;
}

int Date::DaysTillYourBithday(Date bithdaydate)
{
    int days = 0;

    if (this->m_year < bithdaydate.m_year) {
        return -1;
    }

    if (this->m_month == bithdaydate.m_month) {
        if (this->m_day <= bithdaydate.m_day) {
            days = bithdaydate.m_day - this->m_day;
        }
        else if (this->m_day > bithdaydate.m_day && !this->IsLeap()) {
            days = bithdaydate.m_day - this->m_day + 365;
        }
        else {
            days = bithdaydate.m_day - this->m_day + 366;
        }
    }
    else {
        while (bithdaydate.m_year != this->m_year) {
            ++bithdaydate.m_year;
        }
        days = this->Duration(bithdaydate);
    }
    return days;
}

int Date::Duration(Date date)
{
    int d1 = date.convertToDays();
    int d2 = this->convertToDays();
    if(d1 > d2)
    {
        return d1-d2;
    }
    else
    {
        return d2-d1;
    }
}

int Date::convertToDays()
{
    short arr[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int days = 0;
    for(int m = 0; m < m_month - 1; ++m) {
        days+=arr[m];
    }

    return (365*(m_year - 1)+(m_year - 1)/4 + days + m_day);
}

QTableWidgetItem* Date::convertIntoTableItem()
{
    QString day = QString::number(m_day);
    QString month = QString::number(m_month);
    QString year = QString::number(m_year);

    if (m_day < 10)
    {
        day = '0' + QString::number(m_day);
    }
    if (m_month < 10)
    {
        month = '0' + QString::number(m_month);
    }
    if (m_year < 10)
    {
        year = "000" + QString::number(m_year);
    } else if (m_year < 100)
    {
        year = "00" + QString::number(m_year);
    }

    else if (m_year < 1000)
    {
        year = '0' + QString::number(m_year);
    }



    QTableWidgetItem* date = new QTableWidgetItem(QString("%1.%2.%3").arg(day).arg(month).arg(year));
    return date;
}

void Date::doValid()
{
    if (((m_day >= 31 || m_day >= 30) && !daysInMonth(m_month)) || (m_day >= 29 && !IsLeap()) || (m_day >= 30 && IsLeap()))
    {
        if (m_month >= 12)
        {
            m_month = 0;
            m_year++;
        }
        m_day = 1;
        m_month++;
    }
    if (m_month > 12)
    {
        m_month = 0;
        m_year++;
    }
}

