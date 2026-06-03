#ifndef GLOBALS_H
#define GLOBALS_H

#include <iostream>
using namespace std;

const int MAX_RUANGAN = 10;
const int kapasitas   = 20;

// --- Graph ---
int jumlahRuangan;
int adj[MAX_RUANGAN][MAX_RUANGAN];
int visited[MAX_RUANGAN];
string namaRuangan[MAX_RUANGAN];
int itemRuangan[MAX_RUANGAN]; // 0=kosong, 1=kunci, 2=petunjuk, 3=EXIT

// --- Stack ---
struct Stack
{
    int top;
    int temp[kapasitas];
} riwayat;

#endif
