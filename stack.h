#ifndef STACK_H
#define STACK_H

#include "globals.h"

// ============================================================
// OPERASI STACK
// ============================================================
void createStack()
{
    riwayat.top = -1;
}

int isEmpty()
{
    if (riwayat.top == -1)
        return 1;
    else
        return 0;
}

int isFull()
{
    if (riwayat.top >= kapasitas - 1)
        return 1;
    else
        return 0;
}

void push(int data)
{
    if (isFull() == 1)
    {
        cout << "Maaf, riwayat sudah penuh!" << endl;
    }
    else
    {
        riwayat.top++;
        riwayat.temp[riwayat.top] = data;
    }
}

int pop()
{
    if (isEmpty() == 1)
    {
        cout << "Tidak ada ruangan sebelumnya!" << endl;
        return -1;
    }
    else
    {
        int data = riwayat.temp[riwayat.top];
        riwayat.top--;
        return data;
    }
}

void displayRiwayat()
{
    if (isEmpty() == 1)
    {
        cout << "Riwayat perjalanan kosong." << endl;
    }
    else
    {
        cout << "Riwayat perjalanan: ";
        for (int i = 0; i <= riwayat.top; i++)
        {
            cout << namaRuangan[riwayat.temp[i]];
            if (i < riwayat.top)
                cout << " -> ";
        }
        cout << endl;
    }
}

void clearStack()
{
    riwayat.top = -1;
}

#endif
