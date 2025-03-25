/*2. Viết chương trình cho phép người dùng nhập vào hai phân số, tìm phân số lớn
 nhất và xuất kết quả ra màn hình */
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
    void InPhanSo()
    {
        cout<<this->tu<<"/"<<this->mau<<endl;
    }
    void SoSanh(PhanSo b)
    {
        PhanSo c=*this-b;
        if(c.tu<0)
        {
            cout<<"Phan so lon nhat la: ";
            b.InPhanSo();
        }
        else if(c.tu>0)
        {
            cout<<"Phan so lon nhat la: ";
            this->InPhanSo();
        }
        else
        {
            cout<<"Ca hai phan so deu bang nhau."<<endl;
        }
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
    a.SoSanh(b);
}
