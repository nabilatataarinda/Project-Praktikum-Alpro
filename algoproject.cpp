#include <iostream>
#include <stdio.h>
using namespace std;

struct Pasien {
    int nomor;
    string nama;
    Pasien* next;
    Pasien* prev;
};

// Implementasi Linked List Tunggal Head-Tail
Pasien* head = NULL;
Pasien* tail = NULL;

// Implementasi Linked List Ganda
Pasien* riwayatHead = NULL;
Pasien* riwayatTail = NULL;

int nomorAntrian = 1;

void ambilAntrian() {
    string nama;

    cout << "Masukkan nama pasien: ";
    cin >> nama;

    Pasien* baru = new Pasien();

    baru->nomor = nomorAntrian++;
    baru->nama = nama;
    baru->next = NULL;
    baru->prev = NULL;

    if(head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Nomor antrian: " << baru->nomor << endl;
}

void panggilPasien() {
    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    Pasien* temp = head;

    cout << "\nMemanggil pasien :\n";
    cout << "Nama  : " << temp->nama << endl;
    cout << "Nomor : " << temp->nomor << endl;

    Pasien* selesai = new Pasien();

    selesai->nomor = temp->nomor;
    selesai->nama = temp->nama;

    selesai->next = NULL;
    selesai->prev = riwayatTail;

    if(riwayatHead == NULL) {
        riwayatHead = riwayatTail = selesai;
    } else {
        riwayatTail->next = selesai;
        riwayatTail = selesai;
    }
    
    head = head->next;

   if(head != NULL) {
    head->prev = NULL;
    } else {
    tail = NULL;
   }


    delete temp;

    cout << "Pasien selesai dipanggil.\n";
}

void tambahDarurat() {
    string nama;

    cout << "Masukkan nama pasien darurat: ";
    cin >> nama;

    Pasien* baru = new Pasien();

    baru->nomor = nomorAntrian++;
    baru->nama = nama;

    // pasien darurat masuk paling depan
    baru->next = head;
    baru->prev = NULL;

    // sambungkan head lama ke node baru
    if(head != NULL) {
        head->prev = baru;
    }

    // pindahkan head ke node baru
    head = baru;

    if(tail == NULL) {
        tail = baru;
    }

    cout << "Pasien darurat berhasil ditambahkan!\n";
}

void cariPasien() {
    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    string nama;
    cout << "Masukkan nama pasien: ";
    cin >> nama;

    Pasien* temp = head;
    int posisi = 1;

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

void tampilkanAntrian() {

    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    // Bubble Sort
    bool tukar;

    do {
        tukar = false;

        Pasien* temp = head;

        while(temp->next != NULL) {

            if(temp->nomor > temp->next->nomor) {

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

    } while(tukar);

    Pasien* temp = head;

    cout << "\n=== DAFTAR ANTRIAN ===\n";

    while(temp != NULL) {

        cout << temp->nomor
             << " - "
             << temp->nama
             << endl;

        temp = temp->next;
    }
}

void tampilRiwayatMaju() {

    if(riwayatHead == NULL) {
        cout << "Riwayat kosong!\n";
        return;
    }

    Pasien* temp = riwayatHead;


    while(temp != NULL) {

        cout << temp->nomor
             << " - "
             << temp->nama
             << endl;

        temp = temp->next;
    }
}


void tampilRiwayatMundur() {

    if(riwayatTail == NULL) {
        cout << "Riwayat kosong!\n";
        return;
    }

    Pasien* temp = riwayatTail;


    while(temp != NULL) {

        cout << temp->nomor
             << " - "
             << temp->nama
             << endl;

        temp = temp->prev;
    }
}

void menuRiwayat() {

    int pilih;

    do {

        cout << "\n=== MENU RIWAYAT ===\n";
        cout << "1. Tampilkan Dari Awal\n";
        cout << "2. Tampilkan Dari Akhir\n";
        cout << "3. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                tampilRiwayatMaju();
                break;

            case 2:
                tampilRiwayatMundur();
                break;

            case 3:
                cout << "Kembali ke menu utama...\n";
                break;

            default:
                cout << "Pilihan salah!\n";
        }

    } while(pilih != 3);
}

void simpanFile() {

    FILE* file = fopen("data_antrian.txt", "w");

    if(file == NULL) {
        cout << "File gagal dibuat!\n";
        return;
    }

    fprintf(file, "=== DAFTAR ANTRIAN ===\n");

    if(head == NULL) {

        fprintf(file, "Antrian kosong.\n");

    } else {

        Pasien* temp = head;

        while(temp != NULL) {

            fprintf(file,
                    "%d - %s\n",
                    temp->nomor,
                    temp->nama.c_str());

            temp = temp->next;
        }
    }

    fprintf(file, "\n=== RIWAYAT KUNJUNGAN ===\n");

    if(riwayatHead == NULL) {

        fprintf(file, "Belum ada riwayat.\n");

    } else {

        Pasien* temp = riwayatHead;

        while(temp != NULL) {

            fprintf(file,
                    "%d - %s\n",
                    temp->nomor,
                    temp->nama.c_str());

            temp = temp->next;
        }
    }

    fclose(file);

    cout << "Data berhasil disimpan ke file!\n";
}

int main() {

    int pilih;

    do {

        cout << "\n===== MENU =====\n";
        cout << "1. Ambil Antrian\n";
        cout << "2. Panggil Pasien\n";
        cout << "3. Pasien Darurat\n";
        cout << "4. Cari Pasien\n";
        cout << "5. Tampilkan Antrian\n";
        cout << "6. Riwayat Kunjungan\n";
        cout << "7. Simpan File\n";
        cout << "8. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {

            case 1:
                ambilAntrian();
                break;

            case 2:
                panggilPasien();
                break;

            case 3:
                tambahDarurat();
                break;

            case 4:
                cariPasien();
                break;

            case 5:
                tampilkanAntrian();
                break;

            case 6:
                menuRiwayat();
                break;

            case 7:
                simpanFile();
                break;

            case 8:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan salah!\n";
        }

    } while(pilih != 8);

    return 0;
}
