#include <iostream>
#include <vector>

using namespace std;

class TimMang
{
private:
    vector<int> A, B;
    
public:
    TimMang()
    {
        int n, m;
        cout << "Nhap so phan tu cua A: ";
        cin >> n;
        cout << "Nhap so phan tu cua B: ";
        cin >> m;
        vector<int> A(n), B(m);
        cout << "Nhap cac phan tu cua A: ";
        for (int &x : A)
            cin >> x;
        cout << "Nhap cac phan tu cua B: ";
        for (int &x : B)
            cin >> x;
        this->A=A;
        this->B=B;
    }
    
    vector<int> ViTriXuatHien()
    {
        vector<int> ViTri;
        int lenA = A.size();
        int lenB = B.size();

        for (int i = 0; i <= lenB - lenA; i++)
        {
            if (vector<int>(B.begin() + i, B.begin() + i + lenA) == A)
            {
                ViTri.push_back(i);
            }
        }
        return ViTri;
    }
    
    int DemSoLanXuatHien()
    {
        return ViTriXuatHien().size();
    }
    
    void In()
    {
        vector<int> ViTri = this->ViTriXuatHien();
        cout << "So lan xuat hien: " << ViTri.size() << endl;
        cout << "Vi tri bat dau: ";
        bool check=false;
        for (int pos : ViTri)
        {
            cout << pos << " ";
            check=true;
        }
        if(!check)
            cout<<"Khong co";
        cout << endl;
    }
    
};

int main()
{
    TimMang AvaB;
    AvaB.In();
    return 0;
}

