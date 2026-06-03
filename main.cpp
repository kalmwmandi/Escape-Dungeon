#include "globals.h"
#include "stack.h"
#include "graph.h"
#include "crud.h"

void mainkan()
{
    int ruanganSaatIni = 0;
    int punya_kunci    = 0;
    int langkah        = 0;

    createStack();
    push(ruanganSaatIni);

    for (int i = 0; i < jumlahRuangan; i++)
        visited[i] = 0;
    visited[ruanganSaatIni] = 1;

    cout << "\n=========================================" << endl;
    cout << "   SELAMAT DATANG DI ESCAPE DUNGEON!     " << endl;
    cout << "   Temukan jalan keluar dari dungeon!     " << endl;
    cout << "=========================================\n" << endl;

    while (true)
    {
        cout << "\n--- Kamu berada di: [" << ruanganSaatIni << "] "
             << namaRuangan[ruanganSaatIni] << " ---" << endl;

        if (itemRuangan[ruanganSaatIni] == 1 && punya_kunci == 0)
        {
            cout << ">>> Kamu menemukan KUNCI di ruangan ini! Kunci diambil." << endl;
            punya_kunci = 1;
            itemRuangan[ruanganSaatIni] = 0;
        }
        else if (itemRuangan[ruanganSaatIni] == 2)
        {
            cout << ">>> PETUNJUK: Cari ruang rahasia, di sana ada kunci!" << endl;
        }
        else if (itemRuangan[ruanganSaatIni] == 3)
        {
            if (punya_kunci == 1)
            {
                cout << "\n=========================================" << endl;
                cout << " SELAMAT! Kamu berhasil KELUAR dari dungeon!" << endl;
                cout << " Total langkah: " << langkah << endl;
                cout << "=========================================\n" << endl;
                displayRiwayat();
                return;
            }
            else
            {
                cout << ">>> Pintu keluar terkunci! Kamu butuh KUNCI terlebih dahulu." << endl;
            }
        }

        tampilkanPintuKeluar(ruanganSaatIni);
        displayRiwayat();
        if (punya_kunci) cout << "[Status: membawa KUNCI]" << endl;

        cout << "\nAksi:" << endl;
        cout << "  [ID] Pindah ke ruangan (masukkan ID ruangan)" << endl;
        cout << "  [B]  Kembali ke ruangan sebelumnya" << endl;
        cout << "  [Q]  Menyerah / Keluar game" << endl;
        cout << "Pilihan: ";

        string input;
        cin >> input;

        if (input == "Q" || input == "q")
        {
            cout << "\nKamu menyerah... Game over." << endl;
            displayRiwayat();
            return;
        }
        else if (input == "B" || input == "b")
        {
            pop(); // keluarkan posisi saat ini (backtracking)
            if (isEmpty() == 1)
            {
                cout << "Kamu sudah di ruangan awal!" << endl;
                push(ruanganSaatIni); // kembalikan
            }
            else
            {
                int sebelumnya = riwayat.temp[riwayat.top];
                cout << "Kembali ke " << namaRuangan[sebelumnya] << endl;
                ruanganSaatIni = sebelumnya;
                langkah++;
            }
        }
        else
        {
            // Parse angka secara manual
            int tujuan = -1;
            int valid  = 1;
            for (int i = 0; i < (int)input.size(); i++)
            {
                if (input[i] < '0' || input[i] > '9')
                {
                    valid = 0;
                    break;
                }
            }
            if (valid && input.size() > 0)
            {
                tujuan = 0;
                for (int i = 0; i < (int)input.size(); i++)
                    tujuan = tujuan * 10 + (input[i] - '0');
            }

            if (tujuan < 0 || tujuan >= jumlahRuangan)
                cout << "Pilihan tidak valid!" << endl;
            else if (adj[ruanganSaatIni][tujuan] == 0)
                cout << "Tidak ada jalan ke ruangan tersebut!" << endl;
            else
            {
                ruanganSaatIni = tujuan;
                visited[ruanganSaatIni] = 1;
                push(ruanganSaatIni);
                langkah++;
            }
        }
    }
}

// MENU UTAMA
int main()
{
    inisialisasiDungeon();

    int pilihan;
    while (true)
    {
        cout << "\n====================================" << endl;
        cout << "        ESCAPE DUNGEON              " << endl;
        cout << "====================================" << endl;
        cout << "1. Mulai Bermain" << endl;
        cout << "2. Lihat Peta Dungeon (Read)" << endl;
        cout << "3. Tambah Ruangan (Create)" << endl;
        cout << "4. Edit Ruangan (Update)" << endl;
        cout << "5. Tambah Koneksi Ruangan" << endl;
        cout << "6. Hapus Koneksi Ruangan (Delete)" << endl;
        cout << "7. Reset Dungeon" << endl;
        cout << "0. Keluar Program" << endl;
        cout << "Pilihan: ";
        while (!(cin >> pilihan)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Input tidak valid! Masukkan angka: ";
        }

        if      (pilihan == 0) { cout << "Sampai jumpa!" << endl; break; }
        else if (pilihan == 1) mainkan();
        else if (pilihan == 2) tampilkanSemuaRuangan();
        else if (pilihan == 3) tambahRuangan();
        else if (pilihan == 4) editRuangan();
        else if (pilihan == 5) tambahKoneksiMenu();
        else if (pilihan == 6) hapusEdgeMenu();
        else if (pilihan == 7) { inisialisasiDungeon(); clearStack(); cout << "Dungeon direset!" << endl; }
        else cout << "Pilihan tidak valid!" << endl;
    }

    return 0;
}
