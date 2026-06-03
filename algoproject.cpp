#include <iostream>
#include <string>
#include <cstdio>

using namespace std;

// Node untuk menyimpan data pasien
struct Pasien {
    int nomor;
    string nama;
    Pasien* next;
    Pasien* prev;
};

// Implementasi Linked List Tunggal Head-Tail
// Pointer awal dan akhir antrian aktif
Pasien* head = NULL;
Pasien* tail = NULL;

// Implementasi Linked List Ganda
// Pointer awal dan akhir riwayat kunjungan
Pasien* riwayatHead = NULL;
Pasien* riwayatTail = NULL;

// Counter untuk nomor antrian pasien reguler berikutnya
int nomorAntrian = 1;

// Fungsi Tambah Pasien Reguler (Masuk dari Belakang/Tail)
void tambahReguler() {
    string nama;
    cout << "Masukkan nama pasien reguler: ";
    cin >> nama;

    Pasien* baru = new Pasien();
    baru->nomor = nomorAntrian++;
    baru->nama = nama;
    baru->next = NULL;
    baru->prev = NULL;

    if (head == NULL) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        baru->prev = tail;
        tail = baru;
    }
    cout << "Pasien reguler " << nama << " berhasil ditambahkan dengan nomor antrian: " << baru->nomor << "\n";
}

// Fungsi Tambah Pasien Darurat (Masuk dari Depan, otomatis jadi Nomor 1)
void tambahDarurat() {
    string nama;
    cout << "Masukkan nama pasien DARURAT: ";
    cin >> nama;

    Pasien* baru = new Pasien();
    baru->nomor = 1; // Pasien darurat langsung memotong jadi nomor 1
    baru->nama = nama;
    baru->next = NULL;
    baru->prev = NULL;

    // Geser semua nomor antrian pasien yang sudah ada di dalam list (ditambah 1)
    Pasien* temp = head;
    while (temp != NULL) {
        temp->nomor = temp->nomor + 1;
        temp = temp->next;
    }
    
    // Counter nomorAntrian global juga ditambah agar pasien reguler berikutnya tidak bentrok
    nomorAntrian++;

    // Masukkan pasien darurat ke posisi paling depan (head)
    if (head == NULL) {
        head = baru;
        tail = baru;
    } else {
        baru->next = head;
        head->prev = baru;
        head = baru;
    }
    cout << "Pasien darurat " << nama << " berhasil ditambahkan di urutan pertama (Nomor 1)!\n";
}

void cariPasien() {
    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    string nama;
    cout << "Masukkan nama pasien: ";
    cin >> nama;
	
	// Mulai pencarian dari head
    Pasien* temp = head;
    int posisi = 1;
	
	// Sequential Search berdasarkan nama
    while(temp != NULL) {

        if(temp->nama == nama) {

            cout << "\n=== DATA DITEMUKAN ===\n";
            cout << "Nama   : " << temp->nama << endl;
            cout << "Nomor  : " << temp->nomor << endl;
            cout << "Posisi : " << posisi << endl;

            return;
        }

        temp = temp->next;
        posisi++;
    }

    cout << "Pasien tidak ditemukan!\n";
}

// Fungsi Mengurutkan dan Menampilkan Antrian (Bubble Sort)
void tampilkanAntrian() {
    if (head == NULL) {
        cout << "Antrian pasien kosong!\n";
        return;
    }

    bool tukar;
    do {
        tukar = false;
        Pasien* temp = head;

        while (temp->next != NULL) {
            if (temp->nomor > temp->next->nomor) { // bandingkan nomor antrian
                int no = temp->nomor;
                string nama = temp->nama;

                temp->nomor = temp->next->nomor;
                temp->nama = temp->next->nama;

                temp->next->nomor = no;
                temp->next->nama = nama;

                tukar = true;
            }
            temp = temp->next;
        }
    } while (tukar);

    Pasien* temp = head;
    cout << "\n=== DAFTAR ANTRIAN SAAT INI ===\n";
    while (temp != NULL) {
        cout << "No. " << temp->nomor << " - " << temp->nama << endl;
        temp = temp->next;
    }
}

// Fungsi Panggil Pasien (Selesai Dilayani -> Masuk ke Riwayat Kunjungan)
void panggilPasien() {
    if (head == NULL) {
        cout << "Tidak ada pasien dalam antrian untuk dipanggil.\n";
        return;
    }

    // Ambil pasien paling depan
    Pasien* dipanggil = head;
    cout << "\n MEMANGGIL PASIEN: No. " << dipanggil->nomor << " - " << dipanggil->nama << " \n";

    // Lepaskan pasien dari antrian utama
    head = head->next;
    if (head != NULL) {
        head->prev = NULL;
    } else {
        tail = NULL; // Jika antrian menjadi kosong
    }

    // Masukkan pasien yang selesai dilayani ke Linked List Riwayat (Masuk ke Belakang/Tail riwayat)
    dipanggil->next = NULL;
    dipanggil->prev = NULL;

    if (riwayatHead == NULL) {
        riwayatHead = dipanggil;
        riwayatTail = dipanggil;
    } else {
        riwayatTail->next = dipanggil;
        dipanggil->prev = riwayatTail;
        riwayatTail = dipanggil;
    }
}

// Fungsi Tampil Riwayat Maju (Dari Pertama Sampai Terakhir)
void tampilRiwayatMaju() {
    if (riwayatHead == NULL) {
        cout << "Riwayat kunjungan kosong!\n";
        return;
    }

    Pasien* temp = riwayatHead;
    cout << "\n=== RIWAYAT KUNJUNGAN (ASC) ===\n";
    while (temp != NULL) {
        cout << "No. " << temp->nomor << " - " << temp->nama << endl;
        temp = temp->next;
    }
}

// Fungsi Tampil Riwayat Mundur (Dari Terbaru Sampai Terlama)
void tampilRiwayatMundur() {
    if (riwayatTail == NULL) {
        cout << "Riwayat kunjungan kosong!\n";
        return;
    }

    Pasien* temp = riwayatTail;
    cout << "\n=== RIWAYAT KUNJUNGAN (DESC) ===\n";
    while (temp != NULL) {
        cout << "No. " << temp->nomor << " - " << temp->nama << endl;
        temp = temp->prev;
    }
}

// Fungsi Simpan ke File data_antrian.txt
void simpanFile() {
    FILE* file = fopen("data_antrian.txt", "w");

    if (file == NULL) {
        cout << "File gagal dibuat!\n";
        return;
    }

    fprintf(file, "=== DAFTAR ANTRIAN PASIEN ===\n");
    if (head == NULL) {
        fprintf(file, "Antrian kosong.\n");
    } else {
        Pasien* temp = head;
        while (temp != NULL) {
            fprintf(file, "%d - %s\n", temp->nomor, temp->nama.c_str());
            temp = temp->next;
        }
    }

    fprintf(file, "\n=== RIWAYAT KUNJUNGAN ===\n");
    if (riwayatHead == NULL) {
        fprintf(file, "Belum ada riwayat.\n");
    } else {
        Pasien* temp = riwayatHead;
        while (temp != NULL) {
            fprintf(file, "%d - %s\n", temp->nomor, temp->nama.c_str());
            temp = temp->next;
        }
    }

    fclose(file);
    cout << "Data berhasil disimpan!\n";
}

// Menu Utama Program
int main() {
    int pilihan;

    do {
        cout << "   ========= SISTEM ANTRIAN RUMAH SAKIT=========  \n";
        cout << "1. Tambah Pasien Reguler\n";
        cout << "2. Tambah Pasien Darurat (IGD)\n";
        cout << "3. Tampilkan Antrian Saat Ini\n";
        cout << "4. Panggil Pasien Berikutnya\n";
		cout << "5. Cari Pasien\n";
        cout << "6. Lihat Riwayat Kunjungan (Maju)\n";
        cout << "7. Lihat Riwayat Kunjungan (Mundur)\n";
        cout << "8. Simpan Data ke File Teks\n";
        cout << "9. Keluar Program\n";
        cout << "Pilihan menu [1-9]: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tambahReguler(); 
            break;
            case 2: tambahDarurat(); 
            break;
            case 3: tampilkanAntrian(); 
            break;
            case 4: panggilPasien(); 
            break;
			case 5: cariPasien(); 
            break;
            case 6: tampilRiwayatMaju(); 
            break;
            case 7: tampilRiwayatMundur(); 
            break;
            case 8: simpanFile(); 
            break;
            case 9: cout << "Terima kasih. Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid, coba lagi.\n";
        }
    } while (pilihan != 9);

    return 0;
}
