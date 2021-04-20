#include "doctest.h"
#include "NumberWithUnits.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
using namespace ariel;

ifstream units_file{"units.txt"};

TEST_CASE("Operator +")
{
    NumberWithUnits::read_units(units_file);

    CHECK_EQ(NumberWithUnits(1, "km") + NumberWithUnits(2, "km"), NumberWithUnits(3, "km"));
    CHECK_EQ(NumberWithUnits(2, "km") + NumberWithUnits(3, "m"), NumberWithUnits(2.003, "km"));
    CHECK_EQ(NumberWithUnits(3, "km") + NumberWithUnits(300, "m"), NumberWithUnits(3.300, "km"));

    CHECK_EQ(NumberWithUnits(2, "m") + NumberWithUnits(2, "m"), NumberWithUnits(4, "m"));
    CHECK_EQ(NumberWithUnits(5, "m") + NumberWithUnits(54, "cm"), NumberWithUnits(5.54, "m"));
    CHECK_EQ(NumberWithUnits(1, "m") + NumberWithUnits(123, "cm"), NumberWithUnits(2.23, "m"));

    CHECK_EQ(NumberWithUnits(1, "kg") + NumberWithUnits(1, "kg"), NumberWithUnits(2, "kg"));
    CHECK_EQ(NumberWithUnits(5, "kg") + NumberWithUnits(111, "g"), NumberWithUnits(5.111, "kg"));
    CHECK_EQ(NumberWithUnits(2, "kg") + NumberWithUnits(50, "g"), NumberWithUnits(2.050, "kg"));

    CHECK_EQ(NumberWithUnits(4, "ton") + NumberWithUnits(4, "ton"), NumberWithUnits(8, "ton"));
    CHECK_EQ(NumberWithUnits(3, "ton") + NumberWithUnits(500, "kg"), NumberWithUnits(3.500, "ton"));
    CHECK_EQ(NumberWithUnits(7, "ton") + NumberWithUnits(1, "kg"), NumberWithUnits(7.001, "ton"));

    CHECK_EQ(NumberWithUnits(5, "hour") + NumberWithUnits(3, "hour"), NumberWithUnits(8, "hour"));
    CHECK_EQ(NumberWithUnits(1, "hour") + NumberWithUnits(60, "min"), NumberWithUnits(2, "hour"));
    CHECK_EQ(NumberWithUnits(6, "min") + NumberWithUnits(1, "min"), NumberWithUnits(7, "min"));
}

TEST_CASE("Operator -")
{
    NumberWithUnits::read_units(units_file);

    CHECK_EQ(NumberWithUnits(3, "km") - NumberWithUnits(2, "km"), NumberWithUnits(1, "km"));
    CHECK_EQ(NumberWithUnits(2, "km") - NumberWithUnits(3, "m"), NumberWithUnits(1.997, "km"));
    CHECK_EQ(NumberWithUnits(3, "km") - NumberWithUnits(300, "m"), NumberWithUnits(2.700, "km"));

    CHECK_EQ(NumberWithUnits(2, "m") - NumberWithUnits(1, "m"), NumberWithUnits(1, "m"));
    CHECK_EQ(NumberWithUnits(5, "m") - NumberWithUnits(54, "cm"), NumberWithUnits(4.46, "m"));
    CHECK_EQ(NumberWithUnits(1, "m") - NumberWithUnits(23, "cm"), NumberWithUnits(0.77, "m"));

    CHECK_EQ(NumberWithUnits(7, "kg") - NumberWithUnits(1, "kg"), NumberWithUnits(6, "kg"));
    CHECK_EQ(NumberWithUnits(5, "kg") - NumberWithUnits(111, "g"), NumberWithUnits(4.889, "kg"));
    CHECK_EQ(NumberWithUnits(2, "kg") - NumberWithUnits(50, "g"), NumberWithUnits(1.950, "kg"));

    CHECK_EQ(NumberWithUnits(4, "ton") - NumberWithUnits(2, "ton"), NumberWithUnits(2, "ton"));
    CHECK_EQ(NumberWithUnits(3, "ton") - NumberWithUnits(500, "kg"), NumberWithUnits(2.500, "ton"));
    CHECK_EQ(NumberWithUnits(7, "ton") - NumberWithUnits(1, "kg"), NumberWithUnits(6.999, "ton"));

    CHECK_EQ(NumberWithUnits(5, "hour") - NumberWithUnits(4, "hour"), NumberWithUnits(1, "hour"));
    CHECK_EQ(NumberWithUnits(6, "min") - NumberWithUnits(1, "min"), NumberWithUnits(5, "min"));
    CHECK_EQ(NumberWithUnits(5, "min") - NumberWithUnits(2, "min"), NumberWithUnits(3, "min"));
}

TEST_CASE("Operator +=, -=, ==")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1{5, "kg"};
    NumberWithUnits n2{200, "g"};
    CHECK((n1 += n2) == NumberWithUnits{5.2, "kg"});
    CHECK(n1 == NumberWithUnits{5.2, "kg"});
    CHECK((n2 += n1) == NumberWithUnits{5400, "g"});
    CHECK(n2 == NumberWithUnits{5400, "g"});
    CHECK((n1 -= n2) == NumberWithUnits{-0.2, "kg"});
    CHECK(n1 == NumberWithUnits{-0.2, "kg"});
    CHECK((n2 -= n1) == NumberWithUnits{5600, "g"});
    CHECK(n2 == NumberWithUnits{5600, "g"});
}

TEST_CASE("Operator unary +, -")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n1{1, "km"};
    CHECK((+n1) == NumberWithUnits(1, "km"));
    CHECK((-n1) == NumberWithUnits(-1, "km"));

    NumberWithUnits n2{-1, "km"};
    CHECK((+n2) == NumberWithUnits(-1, "km"));
    CHECK((-n2) == NumberWithUnits(1, "km"));
}

TEST_CASE("Comparison operators >, >=, <, <=, ==, !=")
{
    NumberWithUnits::read_units(units_file);
    CHECK_GT(NumberWithUnits{5, "km"}, NumberWithUnits{4.5, "km"});
    CHECK_GT(NumberWithUnits{5, "km"}, NumberWithUnits{4900, "m"});

    CHECK_GE(NumberWithUnits{2, "km"}, NumberWithUnits{2000, "m"});
    CHECK_GE(NumberWithUnits{3, "km"}, NumberWithUnits{300000, "cm"});

    CHECK_LT(NumberWithUnits{4, "m"}, NumberWithUnits{401, "cm"});
    CHECK_LT(NumberWithUnits{5, "m"}, NumberWithUnits{7900, "cm"});

    CHECK_LE(NumberWithUnits{2, "m"}, NumberWithUnits{2, "m"});
    CHECK_LE(NumberWithUnits{1, "m"}, NumberWithUnits{100, "cm"});

    CHECK_EQ(NumberWithUnits{6, "kg"}, NumberWithUnits{6, "kg"});
    CHECK_EQ(NumberWithUnits{4, "kg"}, NumberWithUnits{4000, "g"});

    CHECK_NE(NumberWithUnits{3, "ton"}, NumberWithUnits{400, "kg"});
    CHECK_NE(NumberWithUnits{1, "ton"}, NumberWithUnits{50000, "g"});
}

TEST_CASE("Operators ++, --")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n{5, "ton"};
    CHECK(n == NumberWithUnits{5, "ton"});
    CHECK(++n == NumberWithUnits{6, "ton"});
    CHECK(n == NumberWithUnits{6, "ton"});
    CHECK(n++ == NumberWithUnits{6, "ton"});
    CHECK(n == NumberWithUnits{7, "ton"});
    CHECK(n-- == NumberWithUnits{7, "ton"});
    CHECK(n == NumberWithUnits{6, "ton"});
    CHECK(--n == NumberWithUnits{5, "ton"});
    CHECK(n == NumberWithUnits{5, "ton"});
}

TEST_CASE("Operator *, *=")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n{10, "kg"};
    CHECK((n * 1) == NumberWithUnits{10, "kg"});
    CHECK((n * 1.5) == NumberWithUnits{15, "kg"});
    CHECK((n * 2.3) == NumberWithUnits{23, "kg"});
    CHECK((0.1 * n) == NumberWithUnits{1, "kg"});
    CHECK((2.9 * n) == NumberWithUnits{29, "kg"});
    CHECK((4 * n) == NumberWithUnits{40, "kg"});

    NumberWithUnits n1{5, "ton"};
    CHECK((n1 *= 1) == NumberWithUnits{5, "ton"});
    CHECK((n1 *= 2) == NumberWithUnits{10, "ton"});
    CHECK((n1 *= 3) == NumberWithUnits{30, "ton"});
    CHECK((n1 *= 4) == NumberWithUnits{120, "ton"});
    CHECK((n1 *= 0.5) == NumberWithUnits{60, "ton"});
    CHECK((n1 *= 0.2) == NumberWithUnits{12, "ton"});
}

TEST_CASE("Exception")
{
    NumberWithUnits n1{1, "km"};
    NumberWithUnits n2{2, "kg"};
    NumberWithUnits n3{3, "hour"};
    NumberWithUnits n4{4, "USD"};

    CHECK_THROWS(n1 + n2);
    CHECK_THROWS(n1 + n3);
    CHECK_THROWS(n1 + n4);
    CHECK_THROWS(n2 + n3);
    CHECK_THROWS(n2 + n4);
    CHECK_THROWS(n3 + n4);

    NumberWithUnits n5{1, "m"};
    NumberWithUnits n6{2, "g"};
    NumberWithUnits n7{3, "min"};
    NumberWithUnits n8{4, "ILS"};

    CHECK_THROWS(n5 + n6);
    CHECK_THROWS(n5 + n7);
    CHECK_THROWS(n5 + n8);
    CHECK_THROWS(n6 + n7);
    CHECK_THROWS(n6 + n8);
    CHECK_THROWS(n7 + n8);
}

TEST_CASE("Operator <<")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits u1{5.3, "kg"};
    ostringstream out1;
    out1 << u1;
    CHECK_EQ(out1.str(), "5.3[kg]");

    ostringstream out2;
    NumberWithUnits u2{1, "hour"};
    out2 << u2;
    CHECK_EQ(out2.str(), "1[hour]");

    ostringstream out3;
    NumberWithUnits u3{600, "cm"};
    out3 << u3;
    CHECK_EQ(out3.str(), "600[cm]");
}

TEST_CASE("Operator >>")
{
    NumberWithUnits::read_units(units_file);

    NumberWithUnits n{6, "sec"};
    istringstream in1("4 [ km ]");
    in1 >> n;

    CHECK_EQ(n, NumberWithUnits{4, "km"});

    istringstream in2("15 [ m ]");
    in2 >> n;
    CHECK_EQ(n, NumberWithUnits{15, "m"});

    istringstream in3("6 [ kg ]");
    in3 >> n;
    CHECK_EQ(n, NumberWithUnits{6, "kg"});

    istringstream in4("-1 [ g ]");
    in4 >> n;
    CHECK_EQ(n, NumberWithUnits{-1, "g"});

    istringstream in5("-9 [ ton ]");
    in5 >> n;
    CHECK_EQ(n, NumberWithUnits{-9, "ton"});
}
