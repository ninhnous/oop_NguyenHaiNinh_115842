#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class phuong_tien {
private:
    int ma_xe;
    string loai_xe;
    int gio_vao;
    int tg_do;
public:
    phuong_tien();
    phuong_tien(int ma, string loai, int gio, int tg);

    int lay_ma_xe() const;
    string lay_loai_xe() const;
    double tinh_phi() const;
    void hien_thi() const;
};
phuong_tien::phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

phuong_tien::phuong_tien(int ma, string loai, int gio, int tg) : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

int phuong_tien::lay_ma_xe() const { return ma_xe; }

string phuong_tien::lay_loai_xe() const { return loai_xe; }

double phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0 : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) || (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
    for (int h = 0; h < tg_do; h++) {
        if (h < 2) tong += gia * (cao_diem ? 1.30 : 0.95);
        else tong += gia * 0.90;
    }
    return tong;
}

void phuong_tien::hien_thi() const {
    cout << "  ID: " << ma_xe
         << " | " << loai_xe
         << " | " << gio_vao << "h"
         << " | " << tg_do << "h"
         << " | Phi: $" << fixed << setprecision(2)
         << tinh_phi() << "\n";
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;

    static const int suc_chua = 3;
    phuong_tien ds_xe[suc_chua];

    int so_luong_xe;
public:
    bai_xe();
    bai_xe(int ma, char kt);

    int lay_ma() const;
    int lay_suc_chua() const;

    bool day() const;
    bool them(const phuong_tien& v);
    bool xoa(int ma_xe);

    int tim_xe(int ma_xe) const;

    void hien_thi() const;
    bool co_loai(string loai, int& dem, double& tong) const;
};

bai_xe::bai_xe() : ma_bai(0), kich_thuoc('S'), so_luong_xe(0) {}

bai_xe::bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), so_luong_xe(0) {}

int bai_xe::lay_ma() const { return ma_bai; }

int bai_xe::lay_suc_chua() const {
    if (kich_thuoc == 'S') return 1;
    else if (kich_thuoc == 'M') return 2;
    else return 3;
}

bool bai_xe::day() const { return so_luong_xe >= lay_suc_chua();}

int bai_xe::tim_xe(int ma_xe) const {
    for (int i = 0; i < so_luong_xe; i++)
        if (ds_xe[i].lay_ma_xe() == ma_xe)
            return i;
    return -1;
}

bool bai_xe::them(const phuong_tien& v) {
    if (day()) return false;
    if (tim_xe(v.lay_ma_xe()) != -1) return false;
    ds_xe[so_luong_xe] = v;
    so_luong_xe++;
    return true;
}

bool bai_xe::xoa(int ma_xe) {
    int vi_tri = tim_xe(ma_xe);
    if (vi_tri == -1) return false;
    for (int i = vi_tri; i < so_luong_xe - 1; i++)
        ds_xe[i] = ds_xe[i + 1];
    so_luong_xe--;
    ds_xe[so_luong_xe] = phuong_tien();
    return true;
}

void bai_xe::hien_thi() const {
    cout << "\nBai " << ma_bai
         << " [" << kich_thuoc << "] "
         << so_luong_xe << "/" << lay_suc_chua()
         << " xe\n";
    for (int i = 0; i < so_luong_xe; i++)
        ds_xe[i].hien_thi();
}

bool bai_xe::co_loai(string loai, int& dem, double& tong) const {
    dem = 0; tong = 0;
    for (int i = 0; i < so_luong_xe; i++)
        if (ds_xe[i].lay_loai_xe() == loai) {
            dem++;
            tong += ds_xe[i].tinh_phi();
        }
    return dem > 0;
}

class SystemInterface {
private:
    static const int max_bai = 10;

    bai_xe ds_bai[max_bai];

    int so_luong_bai;

    bool nhap_so(int& x);

    bool ton_tai_bai(int ma) const;
    bool ton_tai_xe(int ma) const;

    int tim_bai(int ma) const;

    int tao_ma_ngau_nhien() const;
    int tao_ma_xe_ngau_nhien() const;

    void tao_bai(); void xoa_bai();
    void them_xe(); void lay_xe_ra();

    void hien_thi_ALL(); void hien_thi_theo_bai();

    void thong_ke(); void phi_trung_binh();
public:
    SystemInterface();
    void runMenu();
};

SystemInterface::SystemInterface() : so_luong_bai(0) {
    srand((unsigned int)time(0));
}

bool SystemInterface::nhap_so(int& x) {
    while (!(cin >> x)) {
        cout << "Du lieu khong hop le! Nhap lai: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return true;
}

bool SystemInterface::ton_tai_bai(int ma) const {
    for (int i = 0; i < so_luong_bai; i++)
        if (ds_bai[i].lay_ma() == ma)
            return true;
    return false;
}

bool SystemInterface::ton_tai_xe(int ma) const {
    for (int i = 0; i < so_luong_bai; i++)
        if (ds_bai[i].tim_xe(ma) != -1)
            return true;
    return false;
}

int SystemInterface::tim_bai(int ma) const {
    for (int i = 0; i < so_luong_bai; i++)
        if (ds_bai[i].lay_ma() == ma)
            return i;
    return -1;
}

int SystemInterface::tao_ma_ngau_nhien() const {
    int ma;
    do { ma = rand() % 9000 + 1000;
    } while (ton_tai_bai(ma));
    return ma;
}

int SystemInterface::tao_ma_xe_ngau_nhien() const {
    int ma;
    do { ma = rand() % 9000 + 1000;
    } while (ton_tai_xe(ma));
    return ma;
}

void SystemInterface::tao_bai() {
    if (so_luong_bai >= max_bai) {
        cout << "He thong da du 10 bai!\n"; return;
    }
    int ma; char kt;
    cout << "Ma bai: "; nhap_so(ma);
    if (ma <= 0) {
        cout << "Ma bai khong hop le!\n"; return;
    }
    if (ton_tai_bai(ma)) {
        cout << "Ma bai bi trung! Tu dong tao ma bai moi.\n";
        ma = tao_ma_ngau_nhien();
    }
    cout << "Kich thuoc (S/M/L): ";
    cin >> kt;

    if (kt >= 'a' && kt <= 'z') kt -= 32;
    if (kt != 'S' && kt != 'M' && kt != 'L') {
        cout << "Kich thuoc khong hop le!\n"; return;
    }
    ds_bai[so_luong_bai] = bai_xe(ma, kt);
    so_luong_bai++;
    cout << "Da tao bai " << ma << "\n";
}

void SystemInterface::them_xe() {
    if (so_luong_bai == 0) {
        cout << "Chua co bai xe nao!\n"; return;
    }
    int ma, gio, tg; string loai;
    cout << "Ma xe: ";
    nhap_so(ma);
    if (ma <= 0) {
        cout << "Ma xe khong hop le!\n"; return;
    }
    if (ton_tai_xe(ma)) {
        cout << "Ma xe bi trung! Tu dong tao ma xe moi.\n";
		ma = tao_ma_xe_ngau_nhien();
    }
    cout << "Loai (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle") {
        cout << "Loai xe khong hop le!\n"; return;
    }
    cout << "Gio vao (0-23): ";
    nhap_so(gio);
    if (gio < 0 || gio > 23) {
        cout << "Gio vao khong hop le!\n"; return;
    }
    cout << "Thoi luong (1-23): ";
    nhap_so(tg);
    if (tg < 1 || tg > 23) {
        cout << "Thoi luong khong hop le!\n"; return;
    }
    int vi_tri = -1;
    for (int i = 0; i < so_luong_bai; i++)
        if (!ds_bai[i].day()) {
            vi_tri = i;
            break;
        }
    if (vi_tri == -1) {
        cout << "Tat ca bai xe da day!\n"; return;
    }
    phuong_tien v(ma, loai, gio, tg);
    ds_bai[vi_tri].them(v);
    cout << "Da them xe " << ma
         << " vao bai " << ds_bai[vi_tri].lay_ma()
         << " | Phi: $" << fixed << setprecision(2)
         << v.tinh_phi() << "\n";
}

void SystemInterface::xoa_bai() {
    int ma;
    cout << "Ma bai can xoa: ";
    nhap_so(ma);
    int vi_tri = tim_bai(ma);
    if (vi_tri == -1) {
        cout << "Khong tim thay bai!\n"; return;
    }
    for (int i = vi_tri; i < so_luong_bai - 1; i++)
        ds_bai[i] = ds_bai[i + 1];

    so_luong_bai--;
    ds_bai[so_luong_bai] = bai_xe();
    cout << "Da xoa bai " << ma << "\n";
}

void SystemInterface::lay_xe_ra() {
    int ma;
    cout << "Ma xe can lay ra: ";
    nhap_so(ma);
    for (int i = 0; i < so_luong_bai; i++)
        if (ds_bai[i].xoa(ma)) {
            cout << "Da lay xe ra thanh cong!\n"; return;
        }
    cout << "Khong tim thay xe!\n";
}

void SystemInterface::hien_thi_ALL() {
    if (so_luong_bai == 0) {
        cout << "Chua co bai xe nao!\n"; return;
    }
    for (int i = 0; i < so_luong_bai; i++)
        ds_bai[i].hien_thi();
}

void SystemInterface::hien_thi_theo_bai() {
    int ma;
    cout << "Ma bai: ";
    nhap_so(ma);

    int vi_tri = tim_bai(ma);
    if (vi_tri == -1) {
        cout << "Khong tim thay bai!\n";
        return;
    }
    ds_bai[vi_tri].hien_thi();
}

void SystemInterface::thong_ke() {
    string loai;
    cout << "Loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai;

    if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle") {
        cout << "Loai xe khong hop le!\n"; return;
    }
    int tong_dem = 0; double tong_phi = 0;
    for (int i = 0; i < so_luong_bai; i++) {
        int dem = 0; double tong = 0;
        if (ds_bai[i].co_loai(loai, dem, tong)) {
            cout << "Bai " << ds_bai[i].lay_ma()
                 << ": " << dem << " xe\n";
            tong_dem += dem;
            tong_phi += tong;
        }
    }
    cout << "\nTong so xe: " << tong_dem << "\n";
    cout << "Tong phi: $" << fixed << setprecision(2)
         << tong_phi << "\n";
}

void SystemInterface::phi_trung_binh() {
    string loai_arr[3] = { "Car", "Motorcycle", "Bicycle" };
    for (int t = 0; t < 3; t++) {
        int dem = 0;
        double tong = 0;
        cout << "\n" << loai_arr[t] << ":\n";
        for (int i = 0; i < so_luong_bai; i++) {
            int d = 0; double s = 0;
            ds_bai[i].co_loai(loai_arr[t], d, s);
            if (d > 0) {
                cout << "Bai " << ds_bai[i].lay_ma()
                     << ": " << d << " xe | Tong phi: $"
                     << fixed << setprecision(2) << s << "\n";
            }
            dem += d; tong += s;
        }
        if (dem == 0) cout << "Khong co xe!\n";
        else
            cout << "Tong so xe: " << dem
                 << " | Phi trung binh: $"
                 << fixed << setprecision(2)
                 << tong / dem << "\n";
    }
}

void SystemInterface::runMenu() {
    int chon;
    do {
        cout << "\n===== QUAN LY BAI DO XE =====\n";
        cout << "1. Tao bai do\n";
        cout << "2. Them xe\n";
        cout << "3. Xoa bai do\n";
        cout << "4. Lay xe ra\n";
        cout << "5. Hien thi tat ca bai do\n";
        cout << "6. Hien thi xe theo bai\n";
        cout << "7. Liet ke xe theo loai\n";
        cout << "8. Bao cao phi trung binh\n";
        cout << "9. Thoat\n";
        cout << "Chon: ";

        nhap_so(chon);
        switch (chon) {
            case 1:
                tao_bai(); break;
            case 2:
                them_xe(); break;
            case 3:
                xoa_bai(); break;
            case 4:
                lay_xe_ra(); break;
            case 5:
                hien_thi_ALL(); break;
            case 6:
                hien_thi_theo_bai(); break;
            case 7:
                thong_ke(); break;
            case 8:
                phi_trung_binh(); break;
            case 9:
                cout << "Ket thuc chuong trinh!\n"; break;
            default:
                cout << "Vui long chon lai!\n";
        }
    } while (chon != 9);
}

int main() {
    SystemInterface sys;
    sys.runMenu();
    return 0;
}
