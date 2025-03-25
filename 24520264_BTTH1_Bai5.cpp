#include <iostream>
using namespace std;
class NgayThangNam
{
private:
    int ngay,sothang,thang[12],nam;
    bool KiemTraNamNhuan(int nam)
    {
        if(nam%400==0||(nam%4==0&&nam%100!=0))
            return true;
        return false;
    }
public:
    NgayThangNam()
    {
        do
        {
        do
        {
        cout<<"Nhập ngày: ";
        cout.flush();
        cin>>ngay;
        }
        while(ngay<=0&&ngay>32);
        do
        {
        cout<<"Nhập tháng: ";
        cout.flush();
        cin>>sothang;
        }
        while(sothang<=0&&sothang>12);
        cout<<"Nhập năm: ";
        cout.flush();
        cin>>nam;
        int temp[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        for (int i = 0; i < 12; i++) {
            thang[i] = temp[i];
        }
        if(KiemTraNamNhuan(nam))
            thang[1]=29;
        else
            thang[1]=28;
        }
        while(ngay>thang[sothang-1]);
    }
    void InNgayKeTiep()
    {
        int ngay2=ngay,sothang2=sothang,nam2=nam;
        ngay2+=1;
        if(ngay2>thang[sothang2-1])
        {
            sothang2++;
            ngay2=1;
            if(sothang2==13)
            {
                nam2++;
                sothang2=1;
            }
        }
        cout<<"Ngày kế tiếp là: "<<ngay2<<'/'<<sothang2<<'/'<<nam2<<endl;
    }
    void InNgayTruoc()
    {
    int ngay1=ngay,sothang1=sothang,nam1=nam;
    ngay1 -= 1;
    if (ngay1 == 0)
    {
        sothang1 -= 1;
        if (sothang1 == 0)
        {
            nam1 -= 1;
            sothang1 = 12;
        }
        thang[1] = (KiemTraNamNhuan(nam1) ? 29 : 28);
        ngay1 = thang[sothang1 - 1];
    }
    cout << "Ngày trước đó là: " << ngay1 << '/' << sothang1 << '/' << nam1 << endl;
    }
    void InSoNgayTrongNam()
    {
        int result=0;
        for(int i=0;i<sothang-1;i++)
        {
            result+=thang[i];
        }
        result+=ngay;
        cout<<"Ngày "<<ngay<<'/'<<sothang<<'/'<<nam;
        cout<<" là ngày thứ "<<result<<" trong năm.";
    }
};

int main()
{
    NgayThangNam a;
    a.InNgayKeTiep();
    a.InNgayTruoc();
    a.InSoNgayTrongNam();
    return 0;
}
