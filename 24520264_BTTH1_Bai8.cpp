#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ChuyenBay {
private:
    string machuyen, ngaybay, giobay, noidi, noiden;
    int day, month, year, hour, minute;

    bool KiemTraMachuyenbay(const string& machuyen) {
        if (machuyen.size() > 5) return false;
        for (char c : machuyen) {
            if (!isalpha(c)) return false;
        }
        return true;
    }

    bool NamNhuan(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    bool NgaybayHopLe(int day, int month, int year) {
        if (year < 1) return false;
        int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (NamNhuan(year)) daysInMonth[2] = 29;
        return (month >= 1 && month <= 12 && day >= 1 && day <= daysInMonth[month]);
    }

    bool GioBayHopLe(string& giobay) {
        if (giobay.length() != 5 || giobay[2] != ':') return false;
        hour = (giobay[0] - '0') * 10 + (giobay[1] - '0');
        minute = (giobay[3] - '0') * 10 + (giobay[4] - '0');
        return (hour >= 0 && hour <= 23) && (minute >= 0 && minute <= 59);
    }

    bool DiaDanhHopLe(const string& diadiem) {
        if (diadiem.length() > 20 || diadiem.empty()) return false;
        for (char c : diadiem) {
            if (!(isalpha(c) || c == ' ')) return false;
        }
        return true;
    }

public:
    void NhapThongTin() {
        do {
            cout << "Nhập mã chuyến bay: ";
            getline(cin, machuyen);
        } while (!KiemTraMachuyenbay(machuyen));

        do {
            cout << "Nhập ngày bay (dd mm yyyy): ";
            cin >> day >> month >> year;
        } while (!NgaybayHopLe(day, month, year));

        ngaybay = to_string(day) + "/" + to_string(month) + "/" + to_string(year);

        do {
            cout << "Nhập giờ bay (hh:mm): ";
            cin >> giobay;
        } while (!GioBayHopLe(giobay));

        cin.ignore();
        do {
            cout << "Nhập nơi đi: ";
            getline(cin, noidi);
        } while (!DiaDanhHopLe(noidi));

        do {
            cout << "Nhập nơi đến: ";
            getline(cin, noiden);
        } while (!DiaDanhHopLe(noiden));
    }

    void XuatThongTin() const {
    cout << " Mã chuyến bay : " << machuyen << endl;
    cout << " Ngày bay      : " << ngaybay;
    cout << "         Giờ bay       : " << giobay << endl;
    cout << " Nơi đi        : " << noidi;
    cout << "            Nơi đến       : " << noiden << endl;
    cout << "=======================================\n";
    }

    string getMachuyen() const { return machuyen; }
    string getNoidi() const { return noidi; }
    string getNoiden() const { return noiden; }
    string getNgayBay() const { return ngaybay; }
    string getGioBay() const { return giobay; }
    
    bool SoSanhThoiGian(const ChuyenBay& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        return minute < other.minute;
    }
};

class SanBay
{
private:
    vector<ChuyenBay> DanhSach;
    
public:
    void NhapDanhSachChuyenBay() {
        int n;
        cout << "Nhập số lượng chuyến bay: ";
        cin >> n;
        cin.ignore();
        for (int i = 0; i < n; i++) {
            cout << "\nNhập thông tin chuyến bay thứ " << i + 1 << ":\n";
            ChuyenBay cb;
            cb.NhapThongTin();
            DanhSach.push_back(cb);
        }
    }

    void XuatDanhSachChuyenBay() {
        for (const auto& cb : DanhSach) {
            cb.XuatThongTin();
        }
    }

    void TimKiemChuyenBay()
    {
    int choice;
    cout << "Chọn cách tìm kiếm:\n";
    cout << "1. Tìm theo mã chuyến bay\n";
    cout << "2. Tìm theo nơi đi\n";
    cout << "3. Tìm theo nơi đến\n";
    cout << "Nhập lựa chọn (1-3): ";
    cin >> choice;
    cin.ignore();
    string key;
    switch (choice) {
        case 1:
            cout << "Nhập mã chuyến bay: ";
            break;
        case 2:
            cout << "Nhập nơi đi: ";
            break;
        case 3:
            cout << "Nhập nơi đến: ";
            break;
        default:
            cout << "Lựa chọn không hợp lệ!\n";
            return;
    }

    getline(cin, key);
    bool found = false;

    for (const auto& cb : DanhSach) {
        if ((choice == 1 && cb.getMachuyen() == key) ||
            (choice == 2 && cb.getNoidi() == key) ||
            (choice == 3 && cb.getNoiden() == key)) {
            cb.XuatThongTin();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy chuyến bay phù hợp!\n";
    }
}

    void SapXepTheoThoiGian() {
        sort(DanhSach.begin(), DanhSach.end(),
            [](const ChuyenBay& a, const ChuyenBay& b) { return a.SoSanhThoiGian(b); });
        cout << "Danh sách đã sắp xếp.\n";
    }

    void LietKeChuyenBayTheoNgay(const string& noidi, const string& ngay) {
        for (const auto& cb : DanhSach) {
            if (cb.getNoidi() == noidi && cb.getNgayBay() == ngay) {
                cb.XuatThongTin();
            }
        }
    }

    int DemChuyenBay(const string& noidi, const string& noiden) {
        int count = 0;
        for (const auto& cb : DanhSach) {
            if (cb.getNoidi() == noidi && cb.getNoiden() == noiden) {
                count++;
            }
        }
        return count;
    }
    
    void XemSoLuongChuyenBay()
    {
        string di, den;
        cout << "Nhập nơi bạn đi: ";
        cin.ignore();
        getline(cin, di);
    
        cout << "Nhập nơi bạn đến: ";
        getline(cin, den);
        cout << "Số lượng chuyến bay từ " << di << " đến " << den << " là: "
             << DemChuyenBay(di, den) << endl;
    }

};

int main()
{
    SanBay sb;
    sb.NhapDanhSachChuyenBay();
    sb.SapXepTheoThoiGian();
    sb.XuatDanhSachChuyenBay();
    sb.XemSoLuongChuyenBay();
    sb.TimKiemChuyenBay();
    
    return 0;
}
