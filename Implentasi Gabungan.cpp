#include <iostream>
#include <string>
#include <stack>
#include <queue>
using namespace std;

struct Buku {
    string ISBN;
    string judul;
    string pengarang;
    int tahunTerbit;
};

class Library {
private:
    static const int MAX_BUKU = 100; // Maksimal jumlah buku
    Buku* daftarBuku[MAX_BUKU]; // Array of pointers to Buku
    int jumlahBuku;
    stack<Buku*> riwayatPeminjaman; // Stack untuk riwayat peminjaman
    queue<Buku*> antrianPeminjaman; // Queue untuk antrian peminjaman

public:
    Library() : jumlahBuku(0) {}

    void tambahBuku() {
        if (jumlahBuku >= MAX_BUKU) {
            cout << "Daftar buku sudah penuh!" << endl;
            return;
        }
        Buku* b = new Buku;
        cout << "Masukkan ISBN: ";
        cin >> b->ISBN;
        cout << "Masukkan Judul: ";
        cin.ignore(); // Mengabaikan newline
        getline(cin, b->judul);
        cout << "Masukkan Pengarang: ";
        getline(cin, b->pengarang);
        cout << "Masukkan Tahun Terbit: ";
        cin >> b->tahunTerbit;
        daftarBuku[jumlahBuku++] = b; // Menyimpan buku dalam array
        cout << "Buku berhasil ditambahkan!" << endl;
    }

    void tampilkanBuku() {
        if (jumlahBuku == 0) {
            cout << "Tidak ada buku dalam perpustakaan." << endl;
            return;
        }
        for (int i = 0; i < jumlahBuku; ++i) {
            cout << i + 1 << ". ISBN: " << daftarBuku[i]->ISBN 
                 << ", Judul: " << daftarBuku[i]->judul 
                 << ", Pengarang: " << daftarBuku[i]->pengarang 
                 << ", Tahun: " << daftarBuku[i]->tahunTerbit << endl;
        }
    }

    Buku* cariBuku(const string& isbn) {
        for (int i = 0; i < jumlahBuku; ++i) {
            if (daftarBuku[i]->ISBN == isbn) {
                return daftarBuku[i];
            }
        }
        return nullptr; // Buku tidak ditemukan
    }

    void pinjamBuku() {
        if (!antrianPeminjaman.empty()) {
            Buku* b = antrianPeminjaman.front();
            antrianPeminjaman.pop();
            riwayatPeminjaman.push(b);
            cout << "Buku " << b->judul << " dipinjam." << endl;
        } else {
            cout << "Tidak ada buku dalam antrian!" << endl;
        }
    }

    void antriBuku(const string& isbn) {
        Buku* b = cariBuku(isbn);
        if (b) {
            antrianPeminjaman.push(b);
            cout << "Buku " << b->judul << " telah ditambahkan ke dalam antrian." << endl;
        } else {
            cout << "Buku tidak ditemukan!" << endl;
        }
    }

    void kembalikanBuku() {
        if (!riwayatPeminjaman.empty()) {
            Buku* b = riwayatPeminjaman.top();
            riwayatPeminjaman.pop();
            cout << "Buku " << b->judul << " telah dikembalikan." << endl;
        } else {
            cout << "Tidak ada buku yang sedang dipinjam!" << endl;
        }
    }

    ~Library() {
        for (int i = 0; i < jumlahBuku; ++i) {
            delete daftarBuku[i]; // Menghapus buku yang dialokasikan
        }
    }
};

int main() {
    Library library;
    int pilihan;

    do {
        cout << "\n1. Tambah Buku\n2. Tampilkan Buku\n3. Antri Buku\n4. Pinjam Buku\n5. Kembalikan Buku\n6. Keluar\nPilih: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: library.tambahBuku(); break;
            case 2: library.tampilkanBuku(); break;
            case 3: {
                string isbn;
                cout << "Masukkan ISBN buku yang ingin diantri: ";
                cin >> isbn;
                library.antriBuku(isbn);
                break;
            }
            case 4: library.pinjamBuku(); break;
            case 5 : library.kembalikanBuku(); break;
            case 6: cout << "Keluar dari program." << endl; break;
            default: cout << "Pilihan tidak valid!" << endl;
        }
    } while (pilihan != 6);

    return 0;
}