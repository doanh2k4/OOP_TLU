#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

class GhiLog {
public:
    GhiLog(const string& tenTepTin) {
        tepTinLog.open(tenTepTin, ios::out | ios::app);
        if (!tepTinLog.is_open()) {
            cerr << "Loi mo tep tin log: " << tenTepTin << endl;
        }
    }

    ~GhiLog() {
        if (tepTinLog.is_open()) {
            tepTinLog.close();
        }
    }

    void ghiLog(const string& thongDiep) {
        ghiLog("LOG", thongDiep);
    }

    void ghiDebug(const string& thongDiep) {
        ghiLog("DEBUG", thongDiep);
    }

    void ghiThongTin(const string& thongDiep) {
        ghiLog("THONG_TIN", thongDiep);
    }

    void ghiLoi(const string& thongDiep) {
        ghiLog("LOI", thongDiep);
    }

private:
    ofstream tepTinLog;

    void ghiLog(const string& capDo, const string& thongDiep) {
        time_t thoiGianHienTai = time(0);
        tm* thongTinThoiGian = localtime(&thoiGianHienTai);
        char timestamp[80];
        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S] ", thongTinThoiGian);

        cout << timestamp << "[" << capDo << "] " << thongDiep << endl;

        if (tepTinLog.is_open()) {
            tepTinLog << timestamp << "[" << capDo << "] " << thongDiep << endl;
            tepTinLog.flush(); // Dam bao ghi vao tep tin ngay lap tuc
        }
    }
};

class MaTran {
private:
    int m; // so hang
    int n; // so cot
    double elements[100][100];

public:
    MaTran() {
        m = 0;
        n = 0;
    }

    MaTran operator+(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep cong ma tran.");
        return performOperation(a, "+");
    }

    MaTran operator-(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep tru ma tran.");
        return performOperation(a, "-");
    }

    MaTran operator*(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep nhan ma tran.");
        return performOperation(a, "*");
    }

    MaTran operator/(const MaTran& a) const {
        GhiLog logger("logfile.txt");
        logger.ghiLog("Thuc hien phep chia ma tran.");
        return performOperation(a, "/");
    }

    void nhap() {
        cout << "Nhap so hang: ";
        cin >> m;
        cout << "Nhap so cot: ";
        cin >> n;

        cout << "Nhap cac phan tu cua ma tran:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << "Nhap phan tu thu [" << i << "][" << j << "]: ";
                cin >> elements[i][j];
            }
        }
    }

    void xuat() const {
        cout << "Ma tran:" << endl;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                cout << elements[i][j] << " ";
            }
            cout << endl;
        }
    }

private:
    MaTran performOperation(const MaTran& a, const string& operation) const {
        MaTran result;
        result.m = m;
        result.n = n;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (operation == "+") {
                    result.elements[i][j] = elements[i][j] + a.elements[i][j];
                } else if (operation == "-") {
                    result.elements[i][j] = elements[i][j] - a.elements[i][j];
                } else if (operation == "*") {
                    result.elements[i][j] = elements[i][j] * a.elements[i][j];
                } else if (operation == "/") {
                    if (a.elements[i][j] != 0) {
                        result.elements[i][j] = elements[i][j] / a.elements[i][j];
                    } else {
                        // Xu ly chia cho 0
                        GhiLog logger("logfile.txt");
                        logger.ghiLoi("Loi: Chia cho 0!");
                        result.elements[i][j] = 0; // hoac gan mot gia tri mac dinh khac
                    }
                }
            }
        }

        return result;
    }
};

int main() {
    MaTran mt1, mt2;
    GhiLog logger("logfile.txt");

    cout << "Nhap ma tran 1:" << endl;
    mt1.nhap();

    cout << "Nhap ma tran 2:" << endl;
    mt2.nhap();

    cout << "Ma tran 1:" << endl;
    mt1.xuat();

    cout << "Ma tran 2:" << endl;
    mt2.xuat();

    cout << "Ket qua Cong:" << endl;
    (mt1 + mt2).xuat();

    cout << "Ket qua Tru:" << endl;
    (mt1 - mt2).xuat();

    cout << "Ket qua Nhan:" << endl;
    (mt1 * mt2).xuat();

    cout << "Ket qua Chia:" << endl;
    (mt1 / mt2).xuat();

    return 0;
}
