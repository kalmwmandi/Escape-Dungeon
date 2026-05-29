#ifndef CRUD_H
#define CRUD_H

// #include "globals.h"
// #include "graph.h"

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

void tambahRuangan()
{
    if (jumlahRuangan >= MAX_RUANGAN)
    {
        cout << "Ruangan sudah penuh! Maksimal " << MAX_RUANGAN << " ruangan." << endl;
        return;
    }
    int id = jumlahRuangan;
    cout << "Nama ruangan baru: ";
    cin.ignore();
    getline(cin, namaRuangan[id]);
    cout << "Item ruangan (0=Kosong, 1=Kunci, 2=Petunjuk, 3=EXIT): ";
    cin >> itemRuangan[id];

    cout << "Hubungkan ke ruangan mana? (masukkan ID, -1 untuk berhenti)" << endl;
    int hubung;
    while (true)
    {
        cout << "ID ruangan: ";
        cin >> hubung;
        if (hubung == -1) break;
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