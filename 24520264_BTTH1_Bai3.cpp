/*3. Viết chương trình cho phép người dùng nhập vào hai phân số. Tính tổng, hiệu,
tích, thương giữa chúng và xuất kết quả ra màn hình.*/
#include <iostream>
#include <cmath>

using namespace std;

class PhanSo
{
    
private:
    int tu,mau;
    int gcd(int a,int b)
    {
        if(b==0)
            return a;
        return gcd(b,a%b);
    }
public:
    PhanSo(int tu,int mau)
    {
        this->tu=tu;
        this->mau=mau;
    }
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
    PhanSo operator -(PhanSo b)
    {
        PhanSo c(1,1);
        c.mau=this->mau*b.mau;
        c.tu=this->tu*b.mau-b.tu*this->mau;
        c.RutGon();
        return c;
    }
    PhanSo operator +(PhanSo b)
    {
        PhanSo c(1,1);
        c.mau=this->mau*b.mau;
        c.tu=this->tu*b.mau+b.tu*this->mau;
        c.RutGon();
        return c;
    }
    PhanSo operator *(PhanSo b)
    {
        PhanSo c(1,1);
        c.mau=this->mau*b.mau;
        c.tu=this->tu*b.tu;
        c.RutGon();
        return c;
    }
    PhanSo operator/(PhanSo b)
    {
        PhanSo c(1,1);
        c.tu=this->tu*b.mau;
        c.mau=this->mau*b.tu;
        c.RutGon();
        return c;
    }
    void InPhanSo()
    {
        cout<<this->tu<<"/"<<this->mau<<endl;
    }
};

int main()
{
    cout<<"Nhap phan so thu nhat: "<<endl;
    cout.flush();
    PhanSo a;
    cout<<"Nhap phan so thu hai: "<<endl;
    cout.flush();
    PhanSo b;
    PhanSo Tong=a+b;
    cout<<"Tong cua hai phan so la: ";Tong.InPhanSo();
    PhanSo Hieu=a-b;
    cout<<"Hieu cua hai phan so la: ";Hieu.InPhanSo();
    PhanSo Tich=a*b;
    cout<<"Tich cua hai phan so la: ";Tich.InPhanSo();
    PhanSo Thuong=a/b;
    cout<<"Thuong cua hai phan so la: ";Thuong.InPhanSo();
}
