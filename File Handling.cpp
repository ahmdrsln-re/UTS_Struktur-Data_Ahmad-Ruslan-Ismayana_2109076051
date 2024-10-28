#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> // For numeric_limits
using namespace std;

struct Peralatan {
    string kode;
    string nama;
    int jumlah;
    string kondisi;
};

void tambahPeralatan(vector<Peralatan>& inventaris) {
    Peralatan p;
    cout << "Masukkan Kode: ";
    cin >> p.kode;
    cout << "Masukkan Nama: ";
    cin >> p.nama;

    // Input validation for jumlah
    while (true) {
        cout << "Masukkan Jumlah: ";
        cin >> p.jumlah;
        if (cin.fail() || p.jumlah < 0) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Input tidak valid. Jumlah harus berupa angka positif." << endl;
        } else {
            break; // Valid input
        }
    }

    cout << "Masukkan Kondisi: ";
    cin >> p.kondisi;
    inventaris.push_back(p);
    cout << "Peralatan berhasil ditambahkan." << endl;
}

void simpanKeFile(const vector<Peralatan>& inventaris) {
    ofstream file("inventaris.txt");
    if (!file) {
        cout << "Error: Tidak dapat membuka file untuk menyimpan data." << endl;
        return;
    }
    for (const auto& p : inventaris) {
        file << p.kode << "," << p.nama << "," << p.jumlah << "," << p.kondisi << endl;
    }
    file.close();
    cout << "Data berhasil disimpan ke inventaris.txt" << endl;
}

void bacaDariFile(vector<Peralatan>& inventaris) {
    ifstream file("inventaris.txt");
    if (!file) {
        cout << "Error: Tidak dapat membuka file untuk membaca data." << endl;
        return;
    }

    inventaris.clear(); // Clear existing inventory to prevent duplicates

    Peralatan p;
    string line;
    while (getline(file, line)) {
        size_t pos = 0;
        pos = line.find(',');
        p.kode = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        p.nama = line.substr(0, pos);
        line.erase(0, pos + 1);
        pos = line.find(',');
        p.jumlah = stoi(line.substr(0, pos));
        line.erase(0, pos + 1);
        p.kondisi = line;
        inventaris.push_back(p);
    }
    file.close();
    cout << "Data berhasil dibaca dari inventaris.txt" << endl;
}

void tampilkanInventaris(const vector<Peralatan>& inventaris) {
    if (inventaris.empty()) {
        cout << "Inventaris kosong." << endl;
        return;
    }
    for (const auto& p : inventaris) {
        cout << "Kode: " << p.kode << ", Nama: " << p.nama << ", Jumlah: " << p.jumlah << ", Kondisi: " << p.kondisi << endl;
    }
}

int main() {
    vector<Peralatan> inventaris;
    int pilihan;

    do {
        cout << "\nMenu Inventaris:\n";
        cout << "1. Tambah Peralatan\n";
        cout << "2. Simpan ke File\n";
        cout << "3. Baca dari File\n";
        cout << "4. Tampilkan Inventaris\n";
        cout << "5. Keluar\n";
        cout << "Pilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: 
                tambahPeralatan(inventaris); 
                break;
            case 2: 
                simpanKeFile(inventaris); 
                break;
            case 3: 
                bacaDariFile(inventaris); 
                break;
            case 4: 
                tampilkanInventaris(inventaris); 
                break;
            case 5: 
                cout << "Keluar dari program." << endl;
                break;
            default: 
                cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0;
}