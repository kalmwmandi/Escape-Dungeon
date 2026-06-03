#ifndef GRAPH_H
#define GRAPH_H

#include "globals.h"

// ============================================================
// OPERASI GRAPH
// ============================================================
void buatGraph(int v)
{
    jumlahRuangan = v;

    // Buat matrix dengan semua elemen 0 (belum ada edge)
    for (int baris = 0; baris < v; baris++)
    {
        for (int kolom = 0; kolom < v; kolom++)
        {
            adj[baris][kolom] = 0;
        }
    }

    // Reset visited
    for (int i = 0; i < v; i++)
    {
        visited[i] = 0;
    }
}

void tambahEdge(int vAwal, int vTujuan)
{
    // Graph tidak berarah: awal ke tujuan = tujuan ke awal
    adj[vAwal][vTujuan] = 1;
    adj[vTujuan][vAwal] = 1;
}

void hapusEdge(int vAwal, int vTujuan)
{
    adj[vAwal][vTujuan] = 0;
    adj[vTujuan][vAwal] = 0;
}

void tampilkanPintuKeluar(int ruanganSaatIni)
{
    cout << "\nPintu yang tersedia dari " << namaRuangan[ruanganSaatIni] << ":" << endl;
    int ada = 0;
    for (int i = 0; i < jumlahRuangan; i++)
    {
        if (adj[ruanganSaatIni][i] == 1)
        {
            cout << "  [" << i << "] " << namaRuangan[i];
            if (itemRuangan[i] == 1) cout << " (ada KUNCI)";
            if (itemRuangan[i] == 2) cout << " (ada PETUNJUK)";
            if (itemRuangan[i] == 3) cout << " *** EXIT ***";
            cout << endl;
            ada = 1;
        }
    }
    if (ada == 0)
        cout << "  Jalan buntu! Tidak ada pintu keluar." << endl;
}

void inisialisasiDungeon()
{
    buatGraph(7);

    namaRuangan[0] = "Pintu Masuk";
    namaRuangan[1] = "Ruang Gelap";
    namaRuangan[2] = "Lorong Sempit";
    namaRuangan[3] = "Ruang Jebakan";
    namaRuangan[4] = "Ruang Rahasia";
    namaRuangan[5] = "Ruang Penjaga";
    namaRuangan[6] = "Pintu Keluar";

    itemRuangan[0] = 0; // kosong (start)
    itemRuangan[1] = 2; // petunjuk
    itemRuangan[2] = 0; // kosong
    itemRuangan[3] = 0; // jebakan / jalan buntu
    itemRuangan[4] = 1; // kunci
    itemRuangan[5] = 0; // kosong
    itemRuangan[6] = 3; // EXIT

    // Hubungkan ruangan (graph tidak berarah)
    tambahEdge(0, 1); // Pintu Masuk <-> Ruang Gelap
    tambahEdge(0, 2); // Pintu Masuk <-> Lorong Sempit
    tambahEdge(1, 3); // Ruang Gelap <-> Ruang Jebakan
    tambahEdge(1, 4); // Ruang Gelap <-> Ruang Rahasia
    tambahEdge(2, 5); // Lorong Sempit <-> Ruang Penjaga
    tambahEdge(4, 6); // Ruang Rahasia <-> Pintu Keluar
    tambahEdge(5, 6); // Ruang Penjaga <-> Pintu Keluar
}

#endif
