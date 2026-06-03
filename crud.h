#ifndef CRUD_H
#define CRUD_H

#include "globals.h"
#include "graph.h"

// CRUD RUANGAN (Create, Read, Update, Delete)

void tampilkanSemuaRuangan()
{
    cout << "\n===== DAFTAR RUANGAN DUNGEON =====" << endl;
    for (int i = 0; i < jumlahRuangan; i++)
    {
        cout << "[" << i << "] " << namaRuangan[i];
        if      (itemRuangan[i] == 1) cout << " - KUNCI";
        else if (itemRuangan[i] == 2) cout << " - PETUNJUK";
        else if (itemRuangan[i] == 3) cout << " - EXIT";
        else                          cout << " - Kosong";
        cout << endl;
    }
    cout << "\nKoneksi antar ruangan (Adjacency Matrix):" << endl;
    cout << "     ";
    for (int i = 0; i < jumlahRuangan; i++)
        cout << "[" << i << "] ";
    cout << endl;
    for (int i = 0; i < jumlahRuangan; i++)
    {
        cout << "[" << i << "]  ";
        for (int j = 0; j < jumlahRuangan; j++)
            cout << " " << adj[i][j] << "  ";
        cout << endl;
    }
}

// CREATE - Tambah ruangan baru
void tambahRuangan()
{
    if (jumlahRuangan >= MAX_RUANGAN)
    {
        cout << "Ruangan sudah penuh! Maksimal " << MAX_RUANGAN << " ruangan." << endl;
        return;
    }
    int id = jumlahRuangan;
    cout << "Nama ruangan baru (ketik '-' untuk batal): ";
    cin.ignore();
    getline(cin, namaRuangan[id]);
    if (namaRuangan[id] == "-") {
        cout << "Operasi dibatalkan." << endl;
        return;
    }
    cout << "Item ruangan (0=Kosong, 1=Kunci, 2=Petunjuk, 3=EXIT): ";
    while (!(cin >> itemRuangan[id])) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid! Masukkan angka: ";
    }

    cout << "Hubungkan ke ruangan mana? (masukkan ID, -1 untuk berhenti)" << endl;
    int hubung;
    while (true)
    {
        cout << "ID ruangan: ";
        if (!(cin >> hubung)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Masukkan angka." << endl;
            continue;
        }
        if (hubung == -1) break;
        if (hubung == id) {
            cout << "Tidak dapat menghubungkan ruangan ke dirinya sendiri!" << endl;
            continue;
        }
        if (hubung >= 0 && hubung < jumlahRuangan)
        {
            tambahEdge(id, hubung);
            cout << "Terhubung!" << endl;
        }
        else
        {
            cout << "ID tidak valid." << endl;
        }
    }
    jumlahRuangan++;
    cout << "Ruangan berhasil ditambahkan dengan ID " << id << endl;
}

// UPDATE - Edit nama dan item ruangan
void editRuangan()
{
    tampilkanSemuaRuangan();
    int id;
    cout << "\nMasukkan ID ruangan yang akan diedit (-1 untuk batal): ";
    while (!(cin >> id)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid! Masukkan angka ID: ";
    }
    if (id == -1) {
        cout << "Operasi dibatalkan." << endl;
        return;
    }
    if (id < 0 || id >= jumlahRuangan)
    {
        cout << "ID tidak valid!" << endl;
        return;
    }
    cout << "Nama baru (sekarang: " << namaRuangan[id] << "): ";
    cin.ignore();
    getline(cin, namaRuangan[id]);
    cout << "Item baru (0=Kosong, 1=Kunci, 2=Petunjuk, 3=EXIT): ";
    while (!(cin >> itemRuangan[id])) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Input tidak valid! Masukkan angka: ";
    }
    cout << "Ruangan berhasil diupdate!" << endl;
}

// CREATE - Tambah koneksi baru antar ruangan
void tambahKoneksiMenu()
{
    tampilkanSemuaRuangan();
    int a, b;
    cout << "\nTambah koneksi antara ruangan ID (-1 untuk batal): ";
    while (!(cin >> a)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Input angka: "; }
    if (a == -1) {
        cout << "Operasi dibatalkan." << endl;
        return;
    }
    cout << "dan ruangan ID: ";
    while (!(cin >> b)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Input angka: "; }
    if (a == b)
    {
        cout << "Tidak dapat menghubungkan ruangan ke dirinya sendiri!" << endl;
    }
    else if (a >= 0 && a < jumlahRuangan && b >= 0 && b < jumlahRuangan)
    {
        tambahEdge(a, b);
        cout << "Koneksi berhasil ditambahkan!" << endl;
    }
    else
    {
        cout << "ID tidak valid!" << endl;
    }
}

// DELETE - Hapus koneksi antar ruangan
void hapusEdgeMenu()
{
    tampilkanSemuaRuangan();
    int a, b;
    cout << "\nHapus koneksi antara ruangan ID (-1 untuk batal): ";
    while (!(cin >> a)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Input angka: "; }
    if (a == -1) {
        cout << "Operasi dibatalkan." << endl;
        return;
    }
    cout << "dan ruangan ID: ";
    while (!(cin >> b)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Input angka: "; }
    if (a >= 0 && a < jumlahRuangan && b >= 0 && b < jumlahRuangan)
    {
        hapusEdge(a, b);
        cout << "Koneksi antara " << namaRuangan[a]
             << " dan " << namaRuangan[b] << " dihapus!" << endl;
    }
    else
    {
        cout << "ID tidak valid!" << endl;
    }
}

#endif
