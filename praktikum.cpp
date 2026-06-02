#include <iostream>
#include <fstream>
#include <vector>
#include <array>
#include <string>

using namespace std;

// =======================
// KELAS TOKO ELEKTRONIK
// =======================
class TokoElektronik
{
private:
    array<string, 3> etalase; // enkapsulasi

public:
    // Constructor
    TokoElektronik()
    {
        etalase[0] = "Laptop";
        etalase[1] = "Smartphone";
        etalase[2] = "Printer";
    }

    // Method mengambil produk
    string ambilProduk(size_t nomorRak)
    {
        try
        {
            return etalase.at(nomorRak);
        }
        catch (const out_of_range&)
        {
            throw string(
                "Gagal Mengambil Barang : Rak nomor "
                + to_string(nomorRak)
                + " kosong atau tidak tersedia!");
        }
    }
};

// =======================
// FUNGSI FILE I/O CRUD
// =======================
const string FILE_GUDANG = "gudang.txt";

// READ
void tampilkanBarang()
{
    ifstream file(FILE_GUDANG);

    cout << "\n===== DAFTAR BARANG GUDANG =====\n";

    if (!file)
    {
        cout << "Belum ada data barang.\n";
        return;
    }

    string barang;
    int nomor = 1;

    while (getline(file, barang))
    {
        cout << nomor++ << ". " << barang << endl;
    }

    if (nomor == 1)
    {
        cout << "Data kosong.\n";
    }

    file.close();
}

// CREATE
void tambahBarang()
{
    ofstream file(FILE_GUDANG, ios::app);

    string barang;

    cin.ignore();
    cout << "Masukkan nama barang: ";
    getline(cin, barang);

    file << barang << endl;

    file.close();

    cout << "Barang berhasil ditambahkan.\n";
}

// UPDATE
void updateBarang()
{
    ifstream file(FILE_GUDANG);

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.empty())
    {
        cout << "Tidak ada data untuk diperbarui.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid!\n";
        return;
    }

    cin.ignore();

    cout << "Masukkan nama barang baru: ";
    getline(cin, data[nomor - 1]);

    ofstream tulis(FILE_GUDANG);

    for (string item : data)
    {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Data berhasil diperbarui.\n";
}

// DELETE
void hapusBarang()
{
    ifstream file(FILE_GUDANG);

    vector<string> data;
    string barang;

    while (getline(file, barang))
    {
        data.push_back(barang);
    }

    file.close();

    if (data.empty())
    {
        cout << "Tidak ada data untuk dihapus.\n";
        return;
    }

    tampilkanBarang();

    int nomor;
    cout << "\nPilih nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor < 1 || nomor > data.size())
    {
        cout << "Nomor tidak valid!\n";
        return;
    }

    data.erase(data.begin() + (nomor - 1));

    ofstream tulis(FILE_GUDANG);

    for (string item : data)
    {
        tulis << item << endl;
    }

    tulis.close();

    cout << "Barang berhasil dihapus.\n";
}

// =======================
// SIMULASI ETALASE
// =======================
void simulasiEtalase()
{
    TokoElektronik toko;

    cout << "\n===== SIMULASI ETALASE =====\n";

    // Skenario 1
    try
    {
        cout << "\nSkenario 1 (Rak 1)\n";
        cout << "Barang ditemukan: "
             << toko.ambilProduk(1) << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }

    // Skenario 2
    try
    {
        cout << "\nSkenario 2 (Rak 5)\n";
        cout << "Barang ditemukan: "
             << toko.ambilProduk(5) << endl;
    }
    catch (string pesan)
    {
        cout << pesan << endl;
    }
}

// =======================
// MAIN PROGRAM
// =======================
int main()
{
    int pilihan;

    do
    {
        cout << "\n=================================";
        cout << "\n MANAJEMEN TOKO ELEKTRONIK";
        cout << "\n=================================\n";

        tampilkanBarang();

        cout << "\nMenu:";
        cout << "\n1. Tambah Barang";
        cout << "\n2. Update Barang";
        cout << "\n3. Hapus Barang";
        cout << "\n4. Simulasi Etalase";
        cout << "\n0. Keluar";

        cout << "\n\nPilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            tambahBarang();
            break;

        case 2:
            updateBarang();
            break;

        case 3:
            hapusBarang();
            break;

        case 4:
            simulasiEtalase();
            break;

        case 0:
            cout << "Program selesai.\n";
            break;

        default:
            cout << "Pilihan tidak valid!\n";
        }

    } while (pilihan != 0);

    return 0;
}