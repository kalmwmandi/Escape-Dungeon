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