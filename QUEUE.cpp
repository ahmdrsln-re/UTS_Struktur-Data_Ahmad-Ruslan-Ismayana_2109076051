#include <iostream>  // Untuk cin dan cout
#include <queue>     // Untuk std::queue
#include <iomanip>   // Untuk std::setprecision
#include <cstdlib>   // Untuk rand() dan srand()
#include <ctime>     // Untuk time()
#include <stdexcept> // Untuk runtime_error
using namespace std;

struct Pelanggan {
    int nomorAntrian;
    int waktuLayanan; // dalam menit
};

class Queue {
public:
    void enqueue(const Pelanggan& pelanggan) {
        q.push(pelanggan);
    }
    
    Pelanggan dequeue() {
        if (isEmpty()) {
            throw runtime_error("Queue is empty. Cannot dequeue.");
        }
        Pelanggan pelanggan = q.front();
        q.pop();
        return pelanggan;
    }
    
    bool isEmpty() {
        return q.empty();
    }

    int size() {
        return q.size();
    }

private:
    queue<Pelanggan> q;
};

void simulasiAntrian(int jumlahPelanggan) {
    Queue antrian;
    const int jumlahLoket = 3;
    int totalWaktuTunggu = 0;
    int totalPelangganTerlayani = 0;

    // Simulasi antrian dengan pelanggan
    for (int i = 1; i <= jumlahPelanggan; ++i) {
        Pelanggan pelanggan;
        pelanggan.nomorAntrian = i;
        pelanggan.waktuLayanan = rand() % 10 + 1; // Waktu layanan antara 1 hingga 10 menit
        antrian.enqueue(pelanggan);
        cout << "Pelanggan " << pelanggan.nomorAntrian << " masuk dengan waktu layanan " << pelanggan.waktuLayanan << " menit." << endl;
    }

    // Proses layanan
    while (!antrian.isEmpty()) {
        for (int loket = 1; loket <= jumlahLoket; ++loket) {
            if (!antrian.isEmpty()) {
                Pelanggan pelanggan = antrian.dequeue();
                totalWaktuTunggu += pelanggan.waktuLayanan;
                totalPelangganTerlayani++;
                cout << "Loket " << loket << " melayani Pelanggan " << pelanggan.nomorAntrian
                     << " selama " << pelanggan.waktuLayanan << " menit." << endl;
            }
        }
    }

    // Statistik
    double rataRataWaktuTunggu = static_cast<double>(totalWaktuTunggu) / totalPelangganTerlayani;
    cout << fixed << setprecision(2);
    cout << "\nStatistik:\n";
    cout << "Rata-rata waktu tunggu: " << rataRataWaktuTunggu << " menit\n";
    cout << "Total pelanggan terlayani: " << totalPelangganTerlayani << endl;
    cout << "Sisa antrian: " << antrian.size() << " pelanggan (seharusnya 0)" << endl;
}

int main() {
    srand(static_cast<unsigned int>(time(0))); // Inisialisasi seed untuk random
    int jumlahPelanggan;

    cout << "Masukkan jumlah pelanggan: ";
    cin >> jumlahPelanggan;

    simulasiAntrian(jumlahPelanggan);

    return 0;
}