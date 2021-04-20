#include <iostream>
#include <fstream>
#include <string>

namespace ariel
{
    class NumberWithUnits
    {

    private:
        double num;
        std::string unit;

    public:
        NumberWithUnits(){};
        NumberWithUnits(double num, std::string unit)
        {
            this->num = num;
            this->unit = unit;
        }

        static void read_units(std::ifstream &units_file);

        //Six accounting operators
        friend NumberWithUnits operator+(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator+=(NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator-=(NumberWithUnits &n1, const NumberWithUnits &n2);
        friend NumberWithUnits operator+(const NumberWithUnits &n3);
        friend NumberWithUnits operator-(const NumberWithUnits &n3);

        //Six comparison operators
        friend bool operator>(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator>=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator<=(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator==(const NumberWithUnits &n1, const NumberWithUnits &n2);
        friend bool operator!=(const NumberWithUnits &n1, const NumberWithUnits &n2);

        //Increase by 1 (++) and decrease by 1 (--) before and after the number
        friend NumberWithUnits operator++(NumberWithUnits &n);      //++n
        friend NumberWithUnits operator++(NumberWithUnits &n, int); //n++
        friend NumberWithUnits operator--(NumberWithUnits &n);      //--n
        friend NumberWithUnits operator--(NumberWithUnits &n, int); //n--

        //Multiplication by real number
        friend NumberWithUnits operator*(const NumberWithUnits &n, double x);
        friend NumberWithUnits operator*(double x, const NumberWithUnits &n);
        friend NumberWithUnits operator*=(NumberWithUnits &n, double x);
        friend NumberWithUnits operator*=(double x, NumberWithUnits &n);

        //Input and output operator
        friend std::ostream &operator<<(std::ostream &output, const NumberWithUnits &n);
        friend std::istream &operator>>(std::istream &input, NumberWithUnits &n);
    };
}
