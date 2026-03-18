

#ifndef DATE_H_INCLUDED
#define DATE_H_INCLUDED


using namespace std;

class Date
{
private:
    int month;
    int day;
    int year;
    static const int monthDays[12];

public:
    class InvalidMonth
    {
    private:
        int value;
    public:
        explicit InvalidMonth(int val) : value(val) {}
        int getValue() const
        {
            return value;
        }
    };

    class InvalidDay
    {
    private:
        int value;
    public:
        explicit InvalidDay(int val) : value(val) {}
        int getValue() const
        {
            return value;
        }
    };

    class InvalidLeap
    {
    private:
        int value;
    public:
        explicit InvalidLeap(int val) : value(val) {}
        int getValue() const
        {
            return value;
        }
    };

    class InvalidYear
    {
    private:
        int value;
    public:
        explicit InvalidYear(int val) : value(val) {}
        int getValue() const
        {
            return value;
        }
    };

    Date() = default;
    Date(int d, int m, int y)
    {
        setYear(y);
        setMonth(m);
        setDay(d);
    }


    void setMonth(int m)
    {
        if (m > 0 && m < 13)
        {
            month = m;
        }
        else
        {
            throw InvalidMonth(m);
        }
    }

    void setDay(int d)
    {
        if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
        {
            if (d > 0 && d < 32)
            {
                day = d;
            }
            else
            {
                throw InvalidDay(d);
            }
        }
        else if (month == 4 || month == 6 || month == 9 || month == 11)
        {
            if (d > 0 && d < 31)
            {
                day = d;
            }
            else
            {
                throw InvalidDay(d);
            }
        }
        else if (month == 2)
        {
            if (isLeapYear(year))
            {
                if (d > 0 && d < 30)
                {
                    day = d;
                }
                else
                {
                    throw InvalidDay(d);
                }
            }
            else
            {
                if (d > 0 && d < 29)
                {
                    day = d;
                }
                else
                {
                    throw InvalidLeap(d);
                }
            }
        }
    }

    void setYear(int y)
    {
        if (y > 2024 && y < 2027)
        {
            year = y;
        }
        else
        {
            throw InvalidYear(y);
        }
    }

    int getDay() const
    {
        return day;
    }
    int getMonth() const
    {
        return month;
    }
    int getYear() const
    {
        return year;
    }

    static bool isLeapYear(int y)
    {
        return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
    }

    static int countLeapYears(const Date& d)
    {
        int years = d.year;
        if (d.month <= 2) years--;
        return years / 4 - years / 100 + years / 400;
    }

    static int getDifference(const Date& dt1, const Date& dt2)    //https://www.geeksforgeeks.org/find-number-of-days-between-two-given-dates/
    {
        long int n1 = dt1.year * 365 + dt1.day;
        long int n2 = dt2.year * 365 + dt2.day;

        for (int i = 0; i < dt1.month - 1; i++) n1 += monthDays[i];
        for (int i = 0; i < dt2.month - 1; i++) n2 += monthDays[i];

        n1 += countLeapYears(dt1);
        n2 += countLeapYears(dt2);

        return n2 - n1;
    }
    void nextDay()
    {
        day++;

        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day > 31)
        {
            day = 1;
            month++;
        }
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
        {
            day = 1;
            month++;
        }
        else if (month == 2)
        {
            if (isLeapYear(year) && day > 29)
            {
                day = 1;
                month++;
            }
            else if (!isLeapYear(year) && day > 28)
            {
                day = 1;
                month++;
            }
        }

        if (month > 12)
        {
            month = 1;
            year++;
        }
    }
    static bool isValidDate(int day, int month, int year)
    {
        if (month < 1 || month > 12) return false;
        if (day < 1) return false;
        int daysInMonth = monthDays[month - 1];
        if (month == 2)
        {
            if (isLeapYear(year))
            {
                daysInMonth = 29;
            }
            else
            {
                daysInMonth = 28;
            }
        }

        return day <= daysInMonth;
    }



    string getMonthName() const
    {
        static const vector<string> monthNames =
        {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        return monthNames[month - 1];
    }

    void printDate() const
    {
        cout << getMonthName() << " " << day << ", " << year;
    }

    bool operator<(const Date& other) const
    {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    bool operator>(const Date& other) const
    {
        return other < *this;
    }
    bool operator<=(const Date& other) const
    {
        return !(*this > other);
    }
    bool operator>=(const Date& other) const
    {
        return !(*this < other);
    }
};

const int Date::monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

#endif // DATE_H_INCLUDED
