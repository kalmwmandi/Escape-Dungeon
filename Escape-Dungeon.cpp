#include <iostream>
using namespace std;

// ============================================================
// DEKLARASI GRAPH (dari materi Graph - Adjacency Matrix)
// ============================================================
const int MAX_RUANGAN = 10;

int jumlahRuangan;
int adj[MAX_RUANGAN][MAX_RUANGAN]; // adjacency matrix
int visited[MAX_RUANGAN];          // untuk lacak node yang dikunjungi

// Nama setiap ruangan
string namaRuangan[MAX_RUANGAN];

// Item di setiap ruangan (0=kosong, 1=kunci, 2=petunjuk, 3=EXIT)
int itemRuangan[MAX_RUANGAN];

// ============================================================
// DEKLARASI STACK (dari materi Stack)
// ============================================================
const int kapasitas = 20;
struct Stack
{
    int top;
    int temp[kapasitas];
} riwayat; // stack untuk menyimpan riwayat perjalanan

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

// Tampilkan ruangan yang terhubung dari ruangan saat ini
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

// ============================================================
// CRUD RUANGAN (Create, Read, Update, Delete)
// ============================================================
void tampilkanSemuaRuangan()
{
    cout << "\n===== DAFTAR RUANGAN DUNGEON =====" << endl;
    for (int i = 0; i < jumlahRuangan; i++)
    {
        cout << "[" << i << "] " << namaRuangan[i];
        if (itemRuangan[i] == 1) cout << " - KUNCI";
        else if (itemRuangan[i] == 2) cout << " - PETUNJUK";
        else if (itemRuangan[i] == 3) cout << " - EXIT";
        else cout << " - Kosong";
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

    // Tambah edge
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

void editRuangan()
{
    tampilkanSemuaRuangan();
    int id;
    cout << "\nMasukkan ID ruangan yang akan diedit: ";
    cin >> id;
    if (id < 0 || id >= jumlahRuangan)
    {
        cout << "ID tidak valid!" << endl;
        return;
    }
    cout << "Nama baru (sekarang: " << namaRuangan[id] << "): ";
    cin.ignore();
    getline(cin, namaRuangan[id]);
    cout << "Item baru (0=Kosong, 1=Kunci, 2=Petunjuk, 3=EXIT): ";
    cin >> itemRuangan[id];
    cout << "Ruangan berhasil diupdate!" << endl;
}

void hapusEdgeMenu()
{
    tampilkanSemuaRuangan();
    int a, b;
    cout << "\nHapus koneksi antara ruangan ID: ";
    cin >> a;
    cout << "dan ruangan ID: ";
    cin >> b;
    if (a >= 0 && a < jumlahRuangan && b >= 0 && b < jumlahRuangan)
    {
        hapusEdge(a, b);
        cout << "Koneksi antara " << namaRuangan[a] << " dan " << namaRuangan[b] << " dihapus!" << endl;
    }
    else
    {
        cout << "ID tidak valid!" << endl;
    }
}

void tambahKoneksiMenu()
{
    tampilkanSemuaRuangan();
    int a, b;
    cout << "\nTambah koneksi antara ruangan ID: ";
    cin >> a;
    cout << "dan ruangan ID: ";
    cin >> b;
    if (a >= 0 && a < jumlahRuangan && b >= 0 && b < jumlahRuangan)
    {
        tambahEdge(a, b);
        cout << "Koneksi berhasil ditambahkan!" << endl;
    }
    else
    {
        cout << "ID tidak valid!" << endl;
    }
}

// ============================================================
// INISIALISASI DUNGEON DEFAULT
// ============================================================
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

// ============================================================
// MAIN GAME LOOP
// ============================================================
void mainkan()
{
    int ruanganSaatIni = 0;
    int punya_kunci = 0;
    int langkah = 0;

    createStack();
    push(ruanganSaatIni);

    // Reset visited
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

        // Cek item
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
            // Backtracking dengan pop
            pop(); // keluarkan posisi saat ini
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
            // Cek apakah input angka valid (manual, tanpa stoi)
            int tujuan = -1;
            int valid = 1;
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
            {
                cout << "Pilihan tidak valid!" << endl;
            }
            else if (adj[ruanganSaatIni][tujuan] == 0)
            {
                cout << "Tidak ada jalan ke ruangan tersebut!" << endl;
            }
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

// ============================================================
// MENU UTAMA
// ============================================================
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
        cin >> pilihan;

        if (pilihan == 0)
        {
            cout << "Sampai jumpa!" << endl;
            break;
        }
        else if (pilihan == 1)
        {
            mainkan();
        }
        else if (pilihan == 2)
        {
            tampilkanSemuaRuangan();
        }
        else if (pilihan == 3)
        {
            tambahRuangan();
        }
        else if (pilihan == 4)
        {
            editRuangan();
        }
        else if (pilihan == 5)
        {
            tambahKoneksiMenu();
        }
        else if (pilihan == 6)
        {
            hapusEdgeMenu();
        }
        else if (pilihan == 7)
        {
            inisialisasiDungeon();
            clearStack();
            cout << "Dungeon direset ke kondisi awal!" << endl;
        }
        else
        {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    return 0;
}
