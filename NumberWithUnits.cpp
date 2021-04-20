#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <map>
#include <cmath>
#include "NumberWithUnits.hpp"

using namespace std;
namespace ariel
{
    map<string, map<string, double>> units_table;
    const double EPSILON = 0.0000000000001;

    void NumberWithUnits::read_units(ifstream &units_file)
    {
        string line;
        string unit1;
        string equal;
        string unit2;
        double n1 = 0;
        double n2 = 0;
        while (units_file.good())
        {
            getline(units_file, line);
            istringstream ss(line);
            ss >> n1 >> unit1 >> equal >> n2 >> unit2;
            units_table[unit1][unit2] = n2;
            units_table[unit2][unit1] = 1 / n2;
            for (pair<string, map<string, double>> element : units_table)
            {
                //Search unit1 in the value maps and add unit2
                //And add the founded key to unit2's map
                if (element.second.contains(unit1))
                {
                    double value = n2 * units_table[element.first][unit1];
                    units_table[element.first][unit2] = value;
                    units_table[unit2][element.first] = 1 / value;
                }
                //Search unit2 in the value maps and add unit1
                //And add the founded key to unit1's map
                else if (element.second.contains(unit2))
                {
                    double value = units_table[element.first][unit2] / n2;
                    units_table[element.first][unit1] = value;
                    units_table[unit1][element.first] = 1 / value;
                }
            }
        }
        // print the map
        // for (auto elem : units_table)
        // {
        //     cout <<endl<< "key:" << elem.first <<endl;
        //     for (auto e2 : elem.second)
        //     cout << e2.first << " = " << e2.second<<endl;
        // }
    }

    double convert_unit(double n, const string before, const string after)
    {
        if (before == after)
        {
            return n;
        }
        if (units_table[after].contains(before))
        {
            return n * units_table[before][after];
        }
        throw invalid_argument("Not the same unit!");
    }

    //-------------------------//Six accounting operators-----------------------------
    NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        return NumberWithUnits(n1.num + convert, n1.unit);
    }

    NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        return NumberWithUnits(n1.num - convert, n1.unit);
    }

    NumberWithUnits operator+=(NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        n1.num += convert;
        return n1;
    }

    NumberWithUnits operator-=(NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        n1.num -= convert;
        return n1;
    }

    NumberWithUnits operator+(const NumberWithUnits &n3)
    {
        return n3;
    }

    NumberWithUnits operator-(const NumberWithUnits &n3)
    {
        return NumberWithUnits(-n3.num, n3.unit);
    }

    //--------------------------//Six comparison operators---------------------
    bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;
        if (n1.num > convert)
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;

        if (n1.num >= convert || abs(n1.num - convert) < EPSILON)
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;
        if (n1.num < convert)
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;
        if (n1.num <= convert || abs(n1.num - convert) < EPSILON)
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;
        if (n1.num == convert || abs(n1.num - convert) < EPSILON)
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2)
    {
        double convert = convert_unit(n2.num, n2.unit, n1.unit);
        bool flag = false;
        if (n1.num != convert && !(abs(n1.num - convert) < EPSILON))
        {
            flag = true;
            return flag;
        }
        return flag;
    }

    //---------Increase by 1 (++) and decrease by 1 (--) before and after the number--------
    NumberWithUnits operator++(NumberWithUnits &n)
    {
        return NumberWithUnits(++n.num, n.unit);
    }

    NumberWithUnits operator++(NumberWithUnits &n, int)
    {
        return NumberWithUnits(n.num++, n.unit);
    }

    NumberWithUnits operator--(NumberWithUnits &n)
    {
        return NumberWithUnits(--n.num, n.unit);
    }

    NumberWithUnits operator--(NumberWithUnits &n, int)
    {
        return NumberWithUnits(n.num--, n.unit);
    }

    //---------------------Multiplication by real number-------------------
    NumberWithUnits operator*(const NumberWithUnits &n, double x)
    {
        return NumberWithUnits(n.num * x, n.unit);
    }

    NumberWithUnits operator*(double x, const NumberWithUnits &n)
    {
        return NumberWithUnits(n.num * x, n.unit);
    }

    NumberWithUnits operator*=(NumberWithUnits &n, double x)
    {
        return NumberWithUnits(n.num *= x, n.unit);
    }

    NumberWithUnits operator*=(double x, NumberWithUnits &n)
    {
        return NumberWithUnits(n.num *= x, n.unit);
    }

    //-------------------------Input and output operator--------------------
    ostream &operator<<(ostream &output, const NumberWithUnits &n)
    {
        output << n.num << "[" << n.unit << "]";
        return output;
    }

    istream &operator>>(istream &input, NumberWithUnits &n)
    {
        string bracket;
        input >> n.num >> bracket >> n.unit;
        return input;
    }
}
