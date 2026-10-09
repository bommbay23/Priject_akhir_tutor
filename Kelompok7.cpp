/*
 * PROJEK AKHIR TUTOR - SISTEM PENGELOLAAN NILAI PRAKTIKUM
 *
 * Materi yang diterapkan:
 *  1. Input/Output data      (cin, cout, getline)
 *  2. Array                  (array paralel: nim, nama, nilai)
 *  3. Sorting                (Bubble Sort ascending & descending)
 *  4. Searching              (Linear Search NIM, Binary Search nilai)
 *  5. Boolean / assignment   (status lulus, flag sudah diurutkan, dll.)
 *  6. Percabangan & perulangan, serta fungsi
 *
 * Computational Thinking:
 *  - Dekomposisi        : program dipecah menjadi fungsi-fungsi kecil
 *  - Pengenalan pola    : proses berulang (input N data, tukar elemen, cek lulus)
 *  - Abstraksi          : hanya data penting (NIM, nama, nilai) yang disimpan
 *  - Algoritma          : langkah-langkah jelas di tiap fungsi
 */

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX = 100;           // kapasitas maksimum data
const float NILAI_LULUS = 70;  // batas kelulusan

// Array paralel: indeks yang sama = mahasiswa yang sama
string nim[MAX];
string nama[MAX];
float nilai[MAX];
int jumlah = 0;                // banyak data saat ini
bool sudahUrutAsc = false;     // flag untuk syarat binary search

// ---------- Fungsi bantu ----------
bool isLulus(float n) {        // boolean: true jika nilai >= batas
    return n >= NILAI_LULUS;
}

void tukar(int a, int b) {     // menukar semua array sekaligus
    string tmpS = nim[a];  nim[a] = nim[b];   nim[b] = tmpS;
    tmpS = nama[a];        nama[a] = nama[b]; nama[b] = tmpS;
    float tmpF = nilai[a]; nilai[a] = nilai[b]; nilai[b] = tmpF;
}

void garis() {
    cout << "+------+------------+----------------------+--------+-------------+\n";
}

// ---------- 1. Input ----------
void inputData() {
    int n;
    cout << "Berapa data yang ingin dimasukkan? ";
    cin >> n;

    if (n < 1 || jumlah + n > MAX) {
        cout << "Jumlah tidak valid (sisa kapasitas: " << MAX - jumlah << ")\n";
        return;
    }

    for (int i = 0; i < n; i++) {
        cout << "\nData ke-" << jumlah + 1 << endl;
        cout << "NIM   : ";
        cin >> nim[jumlah];
        cin.ignore();
        cout << "Nama  : ";
        getline(cin, nama[jumlah]);

        do {   // validasi nilai 0-100
            cout << "Nilai : ";
            cin >> nilai[jumlah];
            if (nilai[jumlah] < 0 || nilai[jumlah] > 100)
                cout << "Nilai harus 0 - 100!\n";
        } while (nilai[jumlah] < 0 || nilai[jumlah] > 100);

        jumlah++;
    }
    sudahUrutAsc = false;  // data baru -> urutan tidak terjamin
    cout << "\nData berhasil ditambahkan.\n";
}

// ---------- 2. Output ----------
void tampilData() {
    if (jumlah == 0) {
        cout << "Data masih kosong.\n";
        return;
    }
    garis();
    cout << "| No   | NIM        | Nama                 | Nilai  | Status      |\n";
    garis();
    for (int i = 0; i < jumlah; i++) {
        cout << "| " << left << setw(4) << i + 1
             << " | " << setw(10) << nim[i]
             << " | " << setw(20) << nama[i]
             << " | " << setw(6) << fixed << setprecision(1) << nilai[i]
             << " | " << setw(11) << (isLulus(nilai[i]) ? "LULUS" : "TIDAK LULUS")
             << " |\n";
    }
    garis();
}

// ---------- 3. Statistik ----------
void statistik() {
    if (jumlah == 0) {
        cout << "Data masih kosong.\n";
        return;
    }
    float total = 0, maks = nilai[0], min = nilai[0];
    int idxMaks = 0, idxMin = 0, lulus = 0;

    for (int i = 0; i < jumlah; i++) {
        total += nilai[i];
        if (nilai[i] > maks) { maks = nilai[i]; idxMaks = i; }
        if (nilai[i] < min)  { min = nilai[i];  idxMin = i; }
        if (isLulus(nilai[i])) lulus++;
    }

    cout << fixed << setprecision(2);
    cout << "Jumlah mahasiswa : " << jumlah << endl;
    cout << "Rata-rata nilai  : " << total / jumlah << endl;
    cout << "Nilai tertinggi  : " << maks << " (" << nama[idxMaks] << ")\n";
    cout << "Nilai terendah   : " << min  << " (" << nama[idxMin]  << ")\n";
    cout << "Lulus            : " << lulus << " mahasiswa\n";
    cout << "Tidak lulus      : " << jumlah - lulus << " mahasiswa\n";
}

// ---------- 4. Sorting (Bubble Sort) ----------
void urutkan(bool naik) {
    if (jumlah == 0) {
        cout << "Data masih kosong.\n";
        return;
    }
    for (int i = 0; i < jumlah - 1; i++) {
        for (int j = 0; j < jumlah - i - 1; j++) {
            bool harusTukar = naik ? (nilai[j] > nilai[j + 1])
                                   : (nilai[j] < nilai[j + 1]);
            if (harusTukar) tukar(j, j + 1);
        }
    }
    sudahUrutAsc = naik;   // assignment boolean
    cout << "Data berhasil diurutkan " << (naik ? "ascending" : "descending") << ".\n";
}

// ---------- 5. Linear Search (NIM) ----------
void cariNIM() {
    string target;
    cout << "Masukkan NIM yang dicari: ";
    cin >> target;

    bool ketemu = false;
    for (int i = 0; i < jumlah; i++) {
        if (nim[i] == target) {
            cout << "\nData ditemukan pada urutan ke-" << i + 1 << endl;
            cout << "NIM    : " << nim[i] << endl;
            cout << "Nama   : " << nama[i] << endl;
            cout << "Nilai  : " << nilai[i] << endl;
            cout << "Status : " << (isLulus(nilai[i]) ? "LULUS" : "TIDAK LULUS") << endl;
            ketemu = true;
            break;
        }
    }
    if (!ketemu) cout << "NIM " << target << " tidak ditemukan.\n";
}

// ---------- 6. Binary Search (Nilai) ----------
void cariNilai() {
    if (jumlah == 0) {
        cout << "Data masih kosong.\n";
        return;
    }
    if (!sudahUrutAsc) {
        cout << "Binary search butuh data terurut ascending.\n";
        cout << "Urutkan dulu lewat menu 4 (pilih ascending).\n";
        return;
    }
    float target;
    cout << "Masukkan nilai yang dicari: ";
    cin >> target;

    int kiri = 0, kanan = jumlah - 1;
    bool ketemu = false;
    while (kiri <= kanan && !ketemu) {
        int tengah = (kiri + kanan) / 2;
        if (nilai[tengah] == target) {
            cout << "Ditemukan: " << nama[tengah] << " (" << nim[tengah]
                 << ") dengan nilai " << nilai[tengah] << endl;
            ketemu = true;
        } else if (nilai[tengah] < target) {
            kiri = tengah + 1;
        } else {
            kanan = tengah - 1;
        }
    }
    if (!ketemu) cout << "Tidak ada mahasiswa dengan nilai " << target << ".\n";
}

// ---------- Menu utama ----------
int main() {
    int pilihan;
    do {
        cout << "\n===== SISTEM PENGELOLAAN NILAI PRAKTIKUM =====\n";
        cout << "1. Input data mahasiswa\n";
        cout << "2. Tampilkan semua data\n";
        cout << "3. Statistik nilai\n";
        cout << "4. Urutkan data berdasarkan nilai\n";
        cout << "5. Cari mahasiswa berdasarkan NIM (Linear Search)\n";
        cout << "6. Cari mahasiswa berdasarkan nilai (Binary Search)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cout << endl;

        switch (pilihan) {
            case 1: inputData(); break;
            case 2: tampilData(); break;
            case 3: statistik(); break;
            case 4: {
                int jenis;
                cout << "1. Ascending (kecil -> besar)\n";
                cout << "2. Descending (besar -> kecil)\n";
                cout << "Pilih: ";
                cin >> jenis;
                if (jenis == 1)      urutkan(true);
                else if (jenis == 2) urutkan(false);
                else cout << "Pilihan tidak valid.\n";
                break;
            }
            case 5: cariNIM(); break;
            case 6: cariNilai(); break;
            case 0: cout << "Terima kasih!\n"; break;
            default: cout << "Menu tidak tersedia.\n";
        }
    } while (pilihan != 0);

    return 0;
}