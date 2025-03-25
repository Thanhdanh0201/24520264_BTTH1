#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

class TinhSin {
private:
    double x;
    double dochinhxac;

    long double GiaiThua(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        long double result = 1;
        for (int i = 1; i <= n; ++i) {
            result *= i;
        }
        return result;
    }

public:
    TinhSin(double x, double dochinhxac = 0.00001) : x(x), dochinhxac(dochinhxac) {}

    // Hàm tính sin(x)
    double tinhSin() {
        double sinValue = 0;
        double term = x;
        int n = 0;
        int sign = 1;

        while (abs(term) >= dochinhxac) {
            sinValue += term;
            n++;
            sign *= -1;
            term = sign * pow(x, 2 * n + 1) / GiaiThua(2 * n + 1);
        }
        return sinValue;
    }

    // Hàm in kết quả
    void printResult()
    {
        double result = tinhSin();
        cout << fixed << setprecision(6);
        cout << "Sin(" << x << ") = " << result << endl;
    }
};

int main()
{
    double x;
    cout << "Nhap gia tri x (radian): ";
    cin>>x;

    TinhSin sin(x);
    sin.printResult();
 
    return 0;
}
