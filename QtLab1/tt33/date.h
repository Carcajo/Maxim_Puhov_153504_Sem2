#ifndef DATE_H
#define DATE_H
#include <QString>
#include <QTableWidgetItem>
#include<QTextBrowser>
#include<QLineEdit>


class Date
{
    friend class MainWindow;
public:
    Date(int day = 2, int month = 12, int year = 2003);
    Date NextDay();
    Date PreviousDay();
    bool IsLeap();
    bool daysInMonth(int month); //returns 1 if 31 days and returns 0 if 30 days
    short DaysNumber();
    short WeekNumber();
    int DaysTillYourBithday(Date bithdaydate);
    int convertToDays();
    int Duration(Date date);
    QTableWidgetItem* convertIntoTableItem();
    void doValid();
    friend std::istream& operator>>(std::istream&, Date&);
    friend std::fstream& operator<<(std::fstream&, Date&);

private:

    int m_day;
    int m_month;
    int m_year;
};

#endif // DATE_H
