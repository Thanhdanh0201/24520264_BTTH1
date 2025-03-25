#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

class SoTietKiem {
private:
    string Maso, Loaitietkiem, Hoten, CMND;
    int day, month, year;
    double Sotiengui, LaiSuat;
    bool DaRut = false;
bool KiemTraMaSo(string Maso)
{
    if(Maso.size()>5)
        return false;
    for(char c: Maso)
    {
        if(!((c>='a'&&c<='z')||(c>='A'&&c<='Z')||(c>='0'&&c<='9')))
            return false;
    }
    return true;
}
bool KiemTraCMND(string CMND)
{
    if(CMND.size()!=9 && CMND.size()!=12)
        return false;
    for(char c: CMND)
    {
        if(!(c>='0'&&c<='9'))
            return false;
    }
    return true;
}
bool KiemTraLoai(string Loaitietkiem)
{
    if(Loaitietkiem!="Ngan han"&&Loaitietkiem!="Dai han"&&Loaitietkiem!="Khong ky han")
        return false;
    return true;
}
bool KiemTraHoTen(string name)
{
    if (name.length() > 30 || name.empty()) return false;
    
    for (char c : name)
    {
        if (!( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ') ) ) {
            return false;
        }
    }
    return true;
}
bool NamNhuan(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool KiemTraNgay(int day, int month, int year) {
    if (year < 1900 || year > 2100) return false;
    if (month < 1 || month > 12) return false;

    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && NamNhuan(year)) {
        daysInMonth[2] = 29;
    }

    return (day >= 1 && day <= daysInMonth[month]);
}

bool KiemTraTien(double tien) {
    return tien > 0;
}
public:
    void NhapThongTin() {
cout<<"Nhập mã số của sổ tiết kiệm: \n";
        getline(cin,Maso);
        while(!KiemTraMaSo(Maso))
        {
            cout<<"Mã số không hợp lệ!\n";
            cout<<"Nhập lại mã số: \n";
            getline(cin,Maso);
        }
        cout<<"Có 3 loại: Ngan han, Dai han, Khong ky han.\n";
        cout<<"Nhập loại tiết kiệm quý khách muốn: \n";
        getline(cin,Loaitietkiem);
        while(!KiemTraLoai(Loaitietkiem))
        {
            cout<<"Nhập lại loại tiết kiệm: \n";
            getline(cin,Loaitietkiem);
        }
        cout<<"Nhập họ tên khách hàng: \n";
        getline(cin,Hoten);
        while(!KiemTraHoTen(Hoten))
        {
            cout<<"Không hợp lệ! \n";
            cout<<"Nhập lại họ tên: \n";
            getline(cin,Hoten);
        }
        cout<<"Nhập mã căn cước công dân của khách hàng: \n";
        getline(cin,CMND);
        while(!KiemTraCMND(CMND))
        {
            cout<<"Căn cước công dân không hợp lệ: \n";
            getline(cin,CMND);
        }
        do
        {
            cout << "Nhập ngày mở sổ (dd mm yyyy): ";
            cin >> day >> month >> year;
            if (!KiemTraNgay(day, month, year))
            {
                cout << "Ngày không hợp lệ, vui lòng nhập lại!\n";
            }
        }
        while (!KiemTraNgay(day, month, year));
        do
        {
            cout << "Nhập số tiền gửi: ";
            cin >> Sotiengui;
            if (!KiemTraTien(Sotiengui))
            {
                cout << "Số tiền gửi phải lớn hơn 0, vui lòng nhập lại!\n";
            }
        }
        while (!KiemTraTien(Sotiengui));
        cout << "Nhập lãi suất (%/năm): ";
        cin >> LaiSuat;
    }

    double TinhTienLai(int curDay, int curMonth, int curYear) {
        int totalMonths = (curYear - year) * 12 + (curMonth - month);
        if (totalMonths < 0) return 0;

        double interestRate = LaiSuat / 100.0;
        if (Loaitietkiem == "Ngan han" && totalMonths > 6) totalMonths = 6;
        if (Loaitietkiem == "Dai han" && totalMonths < 6) totalMonths = 6;

        return Sotiengui * interestRate * (totalMonths / 12.0);
    }

    void XuatThongTin(int curDay, int curMonth, int curYear) {
        double tienLai = TinhTienLai(curDay, curMonth, curYear);
        cout << "------------------------------------------------------------\n";
        cout << "| Mã số: " << Maso << " | Loại: " << Loaitietkiem << " |\n";
        cout << "| Họ tên: " << Hoten << " | CMND: " << CMND << " |\n";
        cout << "| Ngày mở sổ: " << day << "/" << month << "/" << year << " |\n";
        cout << "| Số tiền gửi: " << fixed << setprecision(2) << Sotiengui << " VND |\n";
        cout << "| Tiền lãi: " << fixed << setprecision(2) << tienLai << " VND |\n";
        cout << "------------------------------------------------------------\n";
    }

    void CapNhatLaiSuat(double lsMoi) {
        LaiSuat = lsMoi;
        cout << "Lãi suất mới đã cập nhật!\n";
    }

    void RutTien(double SoTienRut, int curDay, int curMonth, int curYear) {
        if (DaRut) {
            cout << "Sổ tiết kiệm đã rút trước đó!\n";
            return;
        }
        if (SoTienRut > Sotiengui) {
            cout << "Số tiền rút vượt quá số dư!\n";
            return;
        }

        int totalMonths = (curYear - year) * 12 + (curMonth - month);
        if ((Loaitietkiem == "Ngan han" && totalMonths < 6) ||
            (Loaitietkiem == "Dai han" && totalMonths < 12)) {
            cout << "Rút trước hạn! Lãi suất giảm còn 0.5%/năm.\n";
            double tienLai = Sotiengui * 0.005 * (totalMonths / 12.0);
            cout << "Tiền lãi nhận được: " << tienLai << " VND\n";
        } else {
            cout << "Rút đúng hạn. Tiền lãi nhận được: " << TinhTienLai(curDay, curMonth, curYear) << " VND\n";
        }

        Sotiengui -= SoTienRut;
        DaRut = true;
        cout << "Số dư còn lại: " << Sotiengui << " VND\n";
    }

    string getCMND() const { return CMND; }
    string getMaso() const { return Maso; }
    int getYear() const { return year; }
    int getMonth() const { return month; }
    double getSotiengui() const { return Sotiengui; }
};

void QuanLy(vector<SoTietKiem>& DanhSach, int curDay, int curMonth, int curYear) {
    int choice;
    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Hiển thị danh sách sổ tiết kiệm\n";
        cout << "2. Cập nhật lãi suất\n";
        cout << "3. Rút tiền\n";
        cout << "4. Tìm kiếm theo CMND hoặc mã sổ\n";
        cout << "5. Liệt kê sổ mở trong khoảng thời gian\n";
        cout << "6. Sắp xếp theo số tiền gửi giảm dần\n";
        cout << "7. Sắp xếp theo ngày mở sổ tăng dần\n";
        cout << "0. Thoát\n";
        cout << "Chọn chức năng: ";
        cin >> choice;

        switch (choice) {
            case 1:
                for (auto& stk : DanhSach) stk.XuatThongTin(curDay, curMonth, curYear);
                break;
            case 2: {
                string maso;
                double lsMoi;
                cout << "Nhập mã số: "; cin >> maso;
                cout << "Nhập lãi suất mới: "; cin >> lsMoi;
                for (auto& stk : DanhSach) if (stk.getMaso() == maso) stk.CapNhatLaiSuat(lsMoi);
                break;
            }
            case 3: {
                string maso;
                double tienRut;
                cout << "Nhập mã số sổ cần rút tiền: "; cin >> maso;
                cout << "Nhập số tiền muốn rút: "; cin >> tienRut;
                for (auto& stk : DanhSach) if (stk.getMaso() == maso) stk.RutTien(tienRut, curDay, curMonth, curYear);
                break;
            }
            case 4: {
                string keyword;
                cout << "Nhập CMND hoặc mã số sổ cần tìm: "; cin >> keyword;
                for (auto& stk : DanhSach) if (stk.getMaso() == keyword || stk.getCMND() == keyword) stk.XuatThongTin(curDay, curMonth, curYear);
                break;
            }
            case 5:
            {
                int startMonth, startYear, endMonth, endYear;
                cout << "Nhập khoảng thời gian (tháng/năm bắt đầu): ";
                cin >> startMonth >> startYear;
                cout << "Nhập khoảng thời gian (tháng/năm kết thúc): ";
                cin >> endMonth >> endYear;
                for (auto& stk : DanhSach) if ((stk.getYear() > startYear || (stk.getYear() == startYear && stk.getMonth() >= startMonth)) &&
                                               (stk.getYear() < endYear || (stk.getYear() == endYear && stk.getMonth() <= endMonth)))
                        stk.XuatThongTin(curDay, curMonth, curYear);
                break;
            }
            case 6:
                sort(DanhSach.begin(), DanhSach.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
                    return a.getSotiengui() > b.getSotiengui();
                });
                cout << "Đã sắp xếp theo số tiền giảm dần!\n";
                                for (auto& stk : DanhSach) stk.XuatThongTin(curDay, curMonth, curYear);
                break;
            case 7:
                sort(DanhSach.begin(), DanhSach.end(), [](const SoTietKiem& a, const SoTietKiem& b) {
                    return a.getYear() < b.getYear() || (a.getYear() == b.getYear() && a.getMonth() < b.getMonth());
                });
                cout << "Đã sắp xếp theo ngày mở sổ tăng dần!\n";
                for (auto& stk : DanhSach) stk.XuatThongTin(curDay, curMonth, curYear);
                break;
        }
    } while (choice != 0);
}

int main() {
    int n;cout<<"Nhập số lượng sổ: ";
    cin>>n;
    cin.ignore();
    vector<SoTietKiem> DanhSach(n);
    for (auto& stk : DanhSach) stk.NhapThongTin();
    int curDay, curMonth, curYear;
    cout << "Nhập ngày hiện tại (dd mm yyyy): "; cin >> curDay >> curMonth >> curYear;
    QuanLy(DanhSach, curDay, curMonth, curYear);
}
