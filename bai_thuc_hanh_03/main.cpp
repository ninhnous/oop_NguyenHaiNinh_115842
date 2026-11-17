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
    phuong_tien() : ma_xe(0), loai_xe(""), gio_vao(0), tg_do(0) {}

    phuong_tien(int ma, const string& loai, int gio, int tg)
        : ma_xe(ma), loai_xe(loai), gio_vao(gio), tg_do(tg) {}

    int lay_ma_xe() const { return ma_xe; }
    string lay_loai_xe() const { return loai_xe; }

    double tinh_phi() const;
    void hien_thi() const {
        cout << "  ID: " << ma_xe
             << " | " << loai_xe
             << " | " << gio_vao << "h"
             << " | " << tg_do << "h"
             << " | Phi: $" << fixed << setprecision(2)
             << tinh_phi() << '\n';
    }
};
phuong_tien::tinh_phi() const {
    double gia = (loai_xe == "Car") ? 6.0
               : (loai_xe == "Motorcycle") ? 4.0 : 2.0;
    bool cao_diem = (gio_vao >= 6 && gio_vao <= 9) ||
                    (gio_vao >= 15 && gio_vao <= 18);
    double tong = 0;
		for (int h = 0; h < tg_do; ++h) {
           if (h < 2)
                tong += gia * (cao_diem ? 1.30 : 0.95);
            else
                tong += gia * 0.90;
        }
    return tong;
}

class bai_xe {
private:
    int ma_bai;
    char kich_thuoc;
    int suc_chua;
    int so_luong_xe;
    phuong_tien** ds_xe;

    void xoa_phuongtien() {
        if (ds_xe != nullptr) {
            for (int i = 0; i < so_luong_xe; ++i) {
                delete ds_xe[i];
                ds_xe[i] = nullptr;
            }
            delete[] ds_xe;
            ds_xe = nullptr;
        }
        so_luong_xe = 0;
        suc_chua = 0;
    }
public:
    bai_xe() : ma_bai(0), kich_thuoc('S'), suc_chua(1), so_luong_xe(0), ds_xe(nullptr) {
        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; ++i) ds_xe[i] = nullptr;
    }
    bai_xe(int ma, char kt) : ma_bai(ma), kich_thuoc(kt), suc_chua(kt == 'S' ? 1 : (kt == 'M' ? 2 : 3)), so_luong_xe(0), ds_xe(nullptr) {
        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; ++i) ds_xe[i] = nullptr;
    }
    bai_xe(const bai_xe& other) : ma_bai(other.ma_bai), kich_thuoc(other.kich_thuoc), suc_chua(other.suc_chua), so_luong_xe(other.so_luong_xe), ds_xe(nullptr) {
        ds_xe = new phuong_tien*[suc_chua];
        for (int i = 0; i < suc_chua; ++i) ds_xe[i] = nullptr;
        try {
            for (int i = 0; i < so_luong_xe; ++i)
                ds_xe[i] = new phuong_tien(*other.ds_xe[i]);
        } catch (...) {
            for (int i = 0; i < suc_chua; ++i) {
                delete ds_xe[i];
                ds_xe[i] = nullptr;
            }
            delete[] ds_xe;
            ds_xe = nullptr;
            throw;
        }
    }
    bai_xe& operator=(const bai_xe& other) {
        if (this == &other) return *this;

        phuong_tien** ds_moi = new phuong_tien*[other.suc_chua];
        for (int i = 0; i < other.suc_chua; ++i) ds_moi[i] = nullptr;

        try {
            for (int i = 0; i < other.so_luong_xe; ++i)
                ds_moi[i] = new phuong_tien(*other.ds_xe[i]);
        } catch (...) {
            for (int i = 0; i < other.suc_chua; ++i) {
                delete ds_moi[i];
                ds_moi[i] = nullptr;
            }
            delete[] ds_moi;
            throw;
        }

        for (int i = 0; i < so_luong_xe; ++i) {
            delete ds_xe[i];
            ds_xe[i] = nullptr;
        }
        delete[] ds_xe;
        ds_xe = nullptr;

        ma_bai = other.ma_bai;
        kich_thuoc = other.kich_thuoc;
        suc_chua = other.suc_chua;
        so_luong_xe = other.so_luong_xe;
        ds_xe = ds_moi;
        return *this;
    }
    ~bai_xe() {xoa_phuongtien();}

    int lay_ma() const { return ma_bai; }
    int lay_so_luong_xe() const { return so_luong_xe; }
    int lay_suc_chua() const { return suc_chua; }

    bool day() const { return so_luong_xe >= suc_chua;}

    int tim_xe(int ma_xe) const {
        for (int i = 0; i < so_luong_xe; ++i)
            if (ds_xe[i] != nullptr && ds_xe[i]->lay_ma_xe() == ma_xe)
                return i;
        return -1;
    }
    void mo_rong(int suc_chua_moi) {
        if (suc_chua_moi <= suc_chua) return;

        phuong_tien** ds_moi = new phuong_tien*[suc_chua_moi];
        for (int i = 0; i < suc_chua_moi; ++i) ds_moi[i] = nullptr;

        for (int i = 0; i < so_luong_xe; ++i)
            ds_moi[i] = ds_xe[i];

        delete[] ds_xe;
        ds_xe = nullptr;

        ds_xe = ds_moi;
        suc_chua = suc_chua_moi;
    }
    bool them(const phuong_tien& v) {
        if (tim_xe(v.lay_ma_xe()) != -1) return false;
        if (so_luong_xe == suc_chua)
            mo_rong(suc_chua * 2);
        ds_xe[so_luong_xe] = new phuong_tien(v);
        ++so_luong_xe;
        return true;
    }
    bool xoa(int ma_xe) {
        int vi_tri = tim_xe(ma_xe);
        if (vi_tri == -1) return false;

        delete ds_xe[vi_tri];
        ds_xe[vi_tri] = nullptr;

        for (int i = vi_tri; i < so_luong_xe - 1; ++i)
            ds_xe[i] = ds_xe[i + 1];

        --so_luong_xe;
        ds_xe[so_luong_xe] = nullptr;
        return true;
    }
    bool co_loai(string loai, int& dem, double& tong) const {
        dem = 0;
        tong = 0;

        for (int i = 0; i < so_luong_xe; ++i) {
            if (ds_xe[i] != nullptr && ds_xe[i]->lay_loai_xe() == loai) {
                ++dem;
                tong += ds_xe[i]->tinh_phi();
            }
        }
        return dem > 0;
    }

    void hien_thi() const {
        cout << "\nBai " << ma_bai << " [" << kich_thuoc << "] "
             << so_luong_xe << "/" << suc_chua << " xe\n";
        for (int i = 0; i < so_luong_xe; ++i)
            if (ds_xe[i] != nullptr) ds_xe[i]->hien_thi();
    }
};

class SystemInterface {
private:
    int suc_chua_he_thong;
    int so_luong_bai;
    bai_xe** ds_bai;

    bool nhap_so(int& x) {
        while (!(cin >> x)) {
            cout << "Du lieu khong hop le! Nhap lai: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        return true;
    }
    void xoa_tat_ca_bai() {
        if (ds_bai != nullptr) {
            for (int i = 0; i < so_luong_bai; ++i) {
                delete ds_bai[i];
                ds_bai[i] = nullptr;
            }
            delete[] ds_bai;
            ds_bai = nullptr;
        }
        so_luong_bai = 0;
        suc_chua_he_thong = 0;
    }

    int tim_bai(int ma) const {
        for (int i = 0; i < so_luong_bai; ++i)
            if (ds_bai[i] != nullptr && ds_bai[i]->lay_ma() == ma)
                return i;
        return -1;
    }

    bool ton_tai_bai(int ma) const {
        return tim_bai(ma) != -1;
    }

    bool ton_tai_xe(int ma) const {
        for (int i = 0; i < so_luong_bai; ++i)
            if (ds_bai[i]->tim_xe(ma) != -1)
                return true;
        return false;
    }

    int tao_ma_ngau_nhien() const {
        int ma;
        do { ma = rand() % 9000 + 1000; }
        while (ton_tai_bai(ma));
        return ma;
    }

    int tao_ma_xe_ngau_nhien() const {
        int ma;
        do { ma = rand() % 9000 + 1000; }
        while (ton_tai_xe(ma));
        return ma;
    }

    void tao_bai();
    void xoa_bai();
    void them_xe();
    void lay_xe_ra();
    void hien_thi_ALL() const;
    void hien_thi_theo_bai() const;
    void thong_ke() const;
    void phi_trung_binh() const;

public:
    SystemInterface() : suc_chua_he_thong(5), so_luong_bai(0), ds_bai(nullptr) {
        ds_bai = new bai_xe*[suc_chua_he_thong];
        for (int i = 0; i < suc_chua_he_thong; ++i) ds_bai[i] = nullptr;
        srand(static_cast<unsigned int>(time(0)));
    }
    SystemInterface(const SystemInterface& other) : suc_chua_he_thong(other.suc_chua_he_thong), so_luong_bai(other.so_luong_bai), ds_bai(nullptr) {
        ds_bai = new bai_xe*[suc_chua_he_thong];
        for (int i = 0; i < suc_chua_he_thong; ++i) ds_bai[i] = nullptr;

        try {
            for (int i = 0; i < so_luong_bai; ++i)
                ds_bai[i] = new bai_xe(*other.ds_bai[i]);
        } catch (...) {
            for (int i = 0; i < suc_chua_he_thong; ++i) {
                delete ds_bai[i];
                ds_bai[i] = nullptr;
            }
            delete[] ds_bai;
            ds_bai = nullptr;
            throw;
        }
    }
    SystemInterface& operator=(const SystemInterface& other) {
        if (this == &other) return *this;

        bai_xe** ds_moi = new bai_xe*[other.suc_chua_he_thong];
        for (int i = 0; i < other.suc_chua_he_thong; ++i) ds_moi[i] = nullptr;

        try {
            for (int i = 0; i < other.so_luong_bai; ++i)
                ds_moi[i] = new bai_xe(*other.ds_bai[i]);
        } catch (...) {
            for (int i = 0; i < other.suc_chua_he_thong; ++i) {
                delete ds_moi[i];
                ds_moi[i] = nullptr;
            }
            delete[] ds_moi;
            throw;
        }

        for (int i = 0; i < so_luong_bai; ++i) {
            delete ds_bai[i];
            ds_bai[i] = nullptr;
        }
        delete[] ds_bai;
        ds_bai = nullptr;

        suc_chua_he_thong = other.suc_chua_he_thong;
        so_luong_bai = other.so_luong_bai;
        ds_bai = ds_moi;
        return *this;
    }
    ~SystemInterface() {
        xoa_tat_ca_bai();
    }
    void mo_rong_he_thong(int suc_chua_moi) {
        if (suc_chua_moi <= suc_chua_he_thong) return;

        bai_xe** ds_moi = new bai_xe*[suc_chua_moi];
        for (int i = 0; i < suc_chua_moi; ++i) ds_moi[i] = nullptr;

        for (int i = 0; i < so_luong_bai; ++i)
            ds_moi[i] = ds_bai[i];

        delete[] ds_bai;
        ds_bai = nullptr;

        ds_bai = ds_moi;
        suc_chua_he_thong = suc_chua_moi;
    }

    void runMenu();
};
void SystemInterface::tao_bai() {
    int ma; char kt;

    cout << "Ma bai: "; nhap_so(ma);
    if (ma <= 0) {
        cout << "Ma bai khong hop le!\n";
        return;
    }
    if (ton_tai_bai(ma)) {
        cout << "Ma bai bi trung! Tu dong tao ma bai moi.\n";
        ma = tao_ma_ngau_nhien();
        cout << "Ma bai moi: " << ma << '\n';
    }
    cout << "Kich thuoc (S/M/L): "; cin >> kt;
    if (kt >= 'a' && kt <= 'z') 
		kt -= 32;
    if (kt != 'S' && kt != 'M' && kt != 'L') {
        cout << "Kich thuoc khong hop le!\n";
        return;
    }
    if (so_luong_bai == suc_chua_he_thong)
        mo_rong_he_thong(suc_chua_he_thong * 2);
    ds_bai[so_luong_bai] = new bai_xe(ma, kt);
    ++so_luong_bai;
    cout << "Da tao bai " << ma << '\n';
}

void SystemInterface::xoa_bai() {
    int ma;
    cout << "Ma bai can xoa: ";
	nhap_so(ma);

    int vi_tri = tim_bai(ma);
    if (vi_tri == -1) {
        cout << "Khong tim thay bai!\n";
        return;
    }
    delete ds_bai[vi_tri];
    ds_bai[vi_tri] = nullptr;

    for (int i = vi_tri; i < so_luong_bai - 1; ++i)
        ds_bai[i] = ds_bai[i + 1];
    --so_luong_bai;
    ds_bai[so_luong_bai] = nullptr;

    cout << "Da xoa bai " << ma << '\n';
}
void SystemInterface::them_xe() {
    if (so_luong_bai == 0) {
        cout << "Chua co bai xe nao!\n";
        return;
    }
    int ma, gio, tg;
    string loai;

    cout << "Ma xe: ";
    nhap_so(ma);
    if (ma <= 0) {
        cout << "Ma xe khong hop le!\n";
        return;
    }

    if (ton_tai_xe(ma)) {
        cout << "Ma xe bi trung! Tu dong tao ma xe moi.\n";
        ma = tao_ma_xe_ngau_nhien();
        cout << "Ma xe moi: " << ma << '\n';
    }

    cout << "Loai (Car/Motorcycle/Bicycle): ";
    cin >> loai;
    if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle") {
        cout << "Loai xe khong hop le!\n";
        return;
    }

    cout << "Gio vao (0-23): ";
    nhap_so(gio);
    if (gio < 0 || gio > 23) {
        cout << "Gio vao khong hop le!\n";
        return;
    }

    cout << "Thoi luong (1-23): ";
    nhap_so(tg);
    if (tg < 1 || tg > 23) {
        cout << "Thoi luong khong hop le!\n";
        return;
    }

    int vi_tri = -1;
    for (int i = 0; i < so_luong_bai; ++i) {
        if (!ds_bai[i]->day()) {
            vi_tri = i;
            break;
        }
    }

    if (vi_tri == -1) {
        cout << "Tat ca bai xe da day! Khong co bai de them xe.\n";
        return;
    }

    phuong_tien v(ma, loai, gio, tg);
    if (ds_bai[vi_tri]->them(v)) {
        cout << "Da them xe " << ma << " vao bai "
             << ds_bai[vi_tri]->lay_ma()
             << " | Phi: $" << fixed << setprecision(2)
             << v.tinh_phi() << '\n';
    } else {
        cout << "Khong the them xe (ma xe bi trung trong bai)!\n";
    }
}

void SystemInterface::lay_xe_ra() {
    int ma;
    cout << "Ma xe can lay ra: ";
    nhap_so(ma);

    for (int i = 0; i < so_luong_bai; ++i) {
        if (ds_bai[i]->xoa(ma)) {
            cout << "Da lay xe ra thanh cong!\n";
            return;
        }
    }
    cout << "Khong tim thay xe!\n";
}

void SystemInterface::hien_thi_ALL() const {
    if (so_luong_bai == 0) {
        cout << "Chua co bai xe nao!\n";
        return;
    }

    for (int i = 0; i < so_luong_bai; ++i)
        if (ds_bai[i] != nullptr) ds_bai[i]->hien_thi();
}

void SystemInterface::hien_thi_theo_bai() const {
    int ma;
    cout << "Ma bai: ";
    nhap_so(ma);

    int vi_tri = tim_bai(ma);
    if (vi_tri == -1) {
        cout << "Khong tim thay bai!\n";
        return;
    }
    ds_bai[vi_tri]->hien_thi();
}

void SystemInterface::thong_ke() const {
    string loai;
    cout << "Loai xe (Car/Motorcycle/Bicycle): ";
    cin >> loai;

    if (loai != "Car" && loai != "Motorcycle" && loai != "Bicycle") {
        cout << "Loai xe khong hop le!\n";
        return;
    }

    int tong_dem = 0;
    double tong_phi = 0;

    for (int i = 0; i < so_luong_bai; ++i) {
        int dem = 0;
        double tong = 0;

        if (ds_bai[i]->co_loai(loai, dem, tong)) {
            cout << "Bai " << ds_bai[i]->lay_ma()
                 << ": " << dem << " xe\n";
            tong_dem += dem;
            tong_phi += tong;
        }
    }

    cout << "\nTong so xe: " << tong_dem << '\n';
    cout << "Tong phi: $" << fixed << setprecision(2)
         << tong_phi << '\n';
}

void SystemInterface::phi_trung_binh() const {
    const string loai_arr[3] = { "Car", "Motorcycle", "Bicycle" };

    for (int t = 0; t < 3; ++t) {
        int tong_dem = 0;
        double tong_phi = 0;

        cout << "\n" << loai_arr[t] << ":\n";

        for (int i = 0; i < so_luong_bai; ++i) {
            int dem = 0;
            double tong = 0;

            ds_bai[i]->co_loai(loai_arr[t], dem, tong);

            if (dem > 0) {
                cout << "Bai " << ds_bai[i]->lay_ma()
                     << ": " << dem << " xe | Tong phi: $"
                     << fixed << setprecision(2) << tong << '\n';
            }

            tong_dem += dem;
            tong_phi += tong;
        }

        if (tong_dem == 0) {
            cout << "Khong co xe!\n";
        } else {
            cout << "Tong so xe: " << tong_dem
                 << " | Phi trung binh: $"
                 << fixed << setprecision(2)
                 << tong_phi / tong_dem << '\n';
        }
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
            case 1: tao_bai(); break;
            case 2: them_xe(); break;
            case 3: xoa_bai(); break;
            case 4: lay_xe_ra(); break;
            case 5: hien_thi_ALL(); break;
            case 6: hien_thi_theo_bai(); break;
            case 7: thong_ke(); break;
            case 8: phi_trung_binh(); break;
            case 9: cout << "Ket thuc chuong trinh!\n"; break;
            default: cout << "Vui long chon lai!\n";
        }
    } while (chon != 9);
}

int main() {
    SystemInterface he_thong;
    he_thong.runMenu();
    return 0;
}
