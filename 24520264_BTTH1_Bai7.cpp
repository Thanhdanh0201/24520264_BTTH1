#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void ChuyenChuThuong(string &str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

class HocSinh {
private:
    string hoten;
    double toan, van, anh;
    double diemtb;
    string Rank;

    bool KiemTraHoTen(const string& hoten) {
        if (hoten.length() < 2 || hoten.length() > 50) {
            return false;
        }
        for (char c : hoten) {
            if (!( (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == ' ') || (c >= -64 && c <= 255) )) {
                return false;
            }
        }
        return true;
    }

    void XepLoai() {
        if (diemtb >= 9)
            Rank = "Xuất Xắc";
        else if (diemtb >= 8)
            Rank = "Giỏi";
        else if (diemtb >= 6.5)
            Rank = "Khá";
        else if (diemtb >= 5)
            Rank = "Trung Bình";
        else
            Rank = "Yếu";
    }

public:
    void NhapThongTin() {
        cin.ignore();
        do
        {
            cout << "Nhập họ tên học sinh: ";
            getline(cin, hoten);
            if (!KiemTraHoTen(hoten))
                cout << "Họ tên không hợp lệ! Nhập lại.\n";
        } while (!KiemTraHoTen(hoten));

        do {
            cout << "Nhập điểm Toán (0 - 10): ";
            cin >> toan;
        } while (toan < 0 || toan > 10);

        do {
            cout << "Nhập điểm Văn (0 - 10): ";
            cin >> van;
        } while (van < 0 || van > 10);

        do {
            cout << "Nhập điểm Anh (0 - 10): ";
            cin >> anh;
        } while (anh < 0 || anh > 10);

        diemtb = ((2 * toan) + van + anh) / 4.0;
        XepLoai();
    }

    void XuatThongTin() const {
        cout << "\n Họ tên: " << hoten << "\n";
        cout << " Điểm Toán: " << toan << " | Văn: " << van << " | Anh: " << anh << "\n";
        cout << " Điểm Trung Bình: " << diemtb << " | Xếp loại: " << Rank << "\n";
        cout << "---------------------------\n";
    }

    double getDiemTB() const
    { return diemtb;}
    double getDiemToan() const
    { return toan; }
    string getHoTen() const
    { return hoten; }
};

class LopHoc {
private:
    vector<HocSinh> DanhSach;
    int SoLuong;
    double TBmax = -1;
    double toanthapnhat = 11;

public:
    LopHoc(int n) {
        SoLuong = n;
        DanhSach.resize(n);
    }

    void NhapDanhSachHocSinh() {
        for (int i = 0; i < SoLuong; i++) {
            cout << "\nNhập thông tin cho học sinh thứ " << i + 1 << ":\n";
            DanhSach[i].NhapThongTin();
            if (DanhSach[i].getDiemTB() > TBmax)
                TBmax = DanhSach[i].getDiemTB();
            if (DanhSach[i].getDiemToan() < toanthapnhat)
                toanthapnhat = DanhSach[i].getDiemToan();
        }
    }

    void HocSinhTBCaoNhat() {
        cout << "\n️ Học sinh có điểm trung bình cao nhất:\n";
        for (int i = 0; i < SoLuong; i++) {
            if (DanhSach[i].getDiemTB() == TBmax) {
                DanhSach[i].XuatThongTin();
            }
        }
    }
    void TimKiemHocSinhTheoTen(const string &keyword)
    {
    string keywordLower = keyword;
    ChuyenChuThuong(keywordLower);
    bool found = false;
    
    cout << "\n Kết quả tìm kiếm:\n";
    for (const auto &hs : DanhSach) {
        string hotenLower = hs.getHoTen();
        ChuyenChuThuong(hotenLower);
        if (hotenLower.find(keywordLower) != string::npos)
        {
            hs.XuatThongTin();
            found = true;
        }
    }

    if (!found) {
        cout << "Không tìm thấy học sinh nào với từ khóa \"" << keyword << "\".\n";
    }
}
    void HienThiDanhSachHocSinhToanThapNhat()
    {
        cout << "\n DANH SÁCH HỌC SINH CÓ ĐIỂM TOÁN THẤP NHẤT:\n";
        for (int i = 0; i < SoLuong; i++)
        {
            if(DanhSach[i].getDiemToan()==toanthapnhat)
            DanhSach[i].XuatThongTin();
        }
    }
};

int main() {
    int n;
    cout << "Nhập số lượng học sinh: ";
    cin >> n;

    LopHoc lop(n);
    lop.NhapDanhSachHocSinh();
    lop.HocSinhTBCaoNhat();
    string keyword;
    cout << "\n Nhập từ khóa để tìm kiếm học sinh: ";
    cin.ignore();
    getline(cin, keyword);
    lop.TimKiemHocSinhTheoTen(keyword);
    lop.HienThiDanhSachHocSinhToanThapNhat();

    return 0;
}
