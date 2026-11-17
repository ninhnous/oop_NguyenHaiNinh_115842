#include <iostream>
#include <vector>
#include <string>
using namespace std;

class SanPham {
private:
    string tenHang;
    int soLuong;
    double donGia;

public:
    SanPham() : tenHang(""), soLuong(0), donGia(0) {}

    void nhap() {
        cout << "Nhap ten hang hoa / dich vu: ";
        cin.ignore();
        getline(cin, tenHang);
        cout << "Nhap so luong (SL): ";
        cin >> soLuong;
        cout << "Nhap don gia: ";
        cin >> donGia;
    }
    void hienThi(int stt) const {
        double thanhTien = soLuong * donGia;
        cout << stt << "\t" << tenHang << "\t\t" << soLuong << "\t" << donGia << "\t" << thanhTien << "\n";
    }
    void setTenHang(string ten) { tenHang = ten; }
    void setSoLuong(int sl) { soLuong = sl; }
    void setDonGia(double gia) { donGia = gia; }
};
class QuanLyHoaDon {
private:
    vector<SanPham> danhSach;
public:
    void them() {
        cout << "\n--- 1. TAO / THEM MAT HANG ---\n";
        SanPham sp;
        sp.nhap();
        danhSach.push_back(sp);
        cout << "-> Da them thanh cong!\n";
    }
    void sua() {
        cout << "\n--- 2. SUA MAT HANG ---\n";
        if (danhSach.empty()) {
            cout << "Danh sach trong!\n";
            return;
        }
        int index;
        cout << "Nhap chi so cua mat hang can sua: "; cin >> index;
        index = index - 1;
        if (index >= 0 && index < danhSach.size()) {
            cout << "Nhap thong tin moi:\n";
            danhSach[index].nhap();
            cout << "-> Sua thanh cong!\n";
        } 
		else
            cout << "Chi so khong hop le!\n";
    }
    void xoa() {
        cout << "\n--- 3. XOA MAT HANG ---\n";
        if (danhSach.empty()) {
            cout << "Danh sach trong!\n";
            return;
        }
        int index;
        cout << "Nhap chi so cua mat hang can xoa: "; cin >> index;
        index = index -1;
        if (index >= 0 && index < danhSach.size()) {
            danhSach.erase(danhSach.begin() + index);
            cout << "-> Xoa thanh cong!\n";
        } 
		else
            cout << "Chi so khong hop le!\n";
    }
	void hienThi() {
	    cout << "\n--- 4. DANH SACH HANG HOA / DICH VU ---\n";
	
	    if (danhSach.empty())
	        cout << "Chua co mat hang nao trong hoa don.\n";
	    else {
	        cout << "STT\tTen hang hoa\t\tSL\tDon gia\tThanh tien\n";
	
	        for (size_t i = 0; i < danhSach.size(); ++i)
	            danhSach[i].hienThi(i + 1);
	    }
	}
    void chayMenu() {
        int chon;
        do {
            cout << "\n=====CHUONG TRINH QUAN LY HOA DON=====\n";
            cout << "1. Tao / Them mat hang moi\n";
            cout << "2. Sua thong tin mat hang\n";
            cout << "3. Xoa mat hang\n";
            cout << "4. Hien thi danh sach mat hang\n";
            cout << "0. Thoat chuong trinh\n";
            cout << "---------------------------------------\n";
            cout << "Nhap lua chon cua ban (0-4): ";
            cin >> chon;

            switch (chon) {
                case 1:
                    them();
                    break;
                case 2:
                    sua();
                    break;
                case 3:
                    xoa();
                    break;
                case 4:
                    hienThi();
                    break;
                case 0:
                    cout << "\nBye bye\n";
                    break;
                default:
                    cout << "\nVui long nhap 0 1 2 3 4.\n";
            }
        } while (chon != 0);
    }
};

int main() {
    QuanLyHoaDon ql;
    ql.chayMenu();
    return 0;
}
