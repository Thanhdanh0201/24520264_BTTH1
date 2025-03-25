//1. Viết chương trình cho phép người dùng nhập vào một phân số, rút gọn phân số và xuất kết quả ra màn hình.
#include <iostream>
#include <cmath>

using namespace std;

class PhanSo
{
    
private:
    int tu, mau;
    int gcd(int a, int b)
    {
        if (b == 0)
            return a;
        return gcd(b, a % b);
    }

public:
    PhanSo()
    {
        cout << "Nhap vao tu so: ";
        cin >> tu;
        do
        {
            cout << "Nhap vao mau so khac 0: ";
            cin >> mau;
        }
        while (mau == 0);
    }

    void RutGon()
    {
        bool check = false;
        if (tu * mau < 0)
            check = true;
        tu = abs(tu);
        mau = abs(mau);
        int tmp = gcd(tu, mau);
        tu /= tmp;
        mau /= tmp;
        if (check)
            tu *= -1;
    }

    void Xuat()
    {
        if (mau != 1)
            cout << "Phan so sau khi da rut gon la: " << tu << "/" << mau << endl;
        else
            cout << "Phan so sau khi da rut gon la: " << tu << endl;
    }
};

int main()
{
    PhanSo a;
    a.RutGon();
    a.Xuat();
    return 0;
}
