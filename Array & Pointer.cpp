#include <iostream>
#include <string>
#include <vector>
#include <limits> // Untuk numeric_limits
#include <algorithm>
using namespace std;

struct Mahasiswa {
    string NIM;
    string nama;
    float IPK;
};

void tambahMahasiswa(vector<Mahasiswa>& mhs) {
    Mahasiswa newMhs;
    cout << "Masukkan NIM:  ";
    cin >> newMhs.NIM;
    cout << "Masukkan Nama:  ";
    cin >> newMhs.nama;

    // Validasi input untuk IPK
    while (true) {
        cout << "Masukkan IPK (0.0 - 4.0):  ";
        cin >> newMhs.IPK;

        if (cin.fail() || newMhs.IPK < 0.0 || newMhs.IPK > 4.0) {
            cin.clear(); // Menghapus flag kesalahan
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Mengabaikan input yang tidak valid
            cout << "Input tidak valid. Silakan coba lagi." << endl;
        } else {
            break; // Input valid
        }
    }

    mhs.push_back(newMhs); // Tambahkan mahasiswa baru ke vector
}

void tampilkanMahasiswa(const vector<Mahasiswa>& mhs) {
    for (const auto& mahasiswa : mhs) {
        cout << "NIM:  " << mahasiswa.NIM << ",  Nama:  " << mahasiswa.nama << ",  IPK:  " << mahasiswa.IPK << endl;
    }
}

void hapusMahasiswa(vector<Mahasiswa>& mhs) {
    string nim;
    cout << "Masukkan NIM mahasiswa yang ingin dihapus: ";
    cin >> nim;

    auto it = remove_if(mhs.begin(), mhs.end(), [&nim](const Mahasiswa& mhs) {
        return mhs.NIM == nim; // Mencari mahasiswa berdasarkan NIM
    });

    if (it != mhs.end()) {
        mhs.erase(it, mhs.end()); // Menghapus mahasiswa yang ditemukan
        cout << "Mahasiswa dengan NIM " << nim << " telah dihapus." << endl;
    } else {
        cout << "Mahasiswa dengan NIM " << nim << " tidak ditemukan!" << endl;
    }
}

void urutkanMahasiswa(vector<Mahasiswa>& mhs) {
    sort(mhs.begin(), mhs.end(), [](const Mahasiswa& a, const Mahasiswa& b) {
        return a.IPK < b.IPK; // Urutkan berdasarkan IPK
    });
    cout << "Data mahasiswa telah diurutkan berdasarkan IPK." << endl;
}

int main() {
    vector<Mahasiswa> mhs; // Gunakan vector untuk ukuran dinamis
    int pilihan;

    do {
        cout << "1. Tambah Mahasiswa\n2. Tampilkan Mahasiswa\n3. Hapus Mahasiswa\n4. Urutkan Mahasiswa\n5. Keluar\nPilih:  ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:  tambahMahasiswa(mhs); break;
            case 2:  tampilkanMahasiswa(mhs); break;
            case 3:  hapusMahasiswa(mhs); break;
            case 4:  urutkanMahasiswa(mhs); break;
            case 5:  break;
            default:  cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 5);

    return 0; // Tidak perlu menghapus, vector menangani memori secara otomatis
}