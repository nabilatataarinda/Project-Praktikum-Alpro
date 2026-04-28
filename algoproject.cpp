#include <iostream>
using namespace std;

struct Pasien {
    int nomor;
    string nama;
    Pasien* next;
};

Pasien* head = NULL;
Pasien* tail = NULL;
Pasien* riwayat = NULL;

int nomorAntrian = 1;

// menu 1
void ambilAntrian() {
    string nama;
    cout << "Masukkan nama: ";
    cin >> nama;

    Pasien* baru = new Pasien();
    baru->nomor = nomorAntrian++;
    baru->nama = nama;
    baru->next = NULL;

    if(head == NULL) {
        head = tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    cout << "Nomor antrian kamu: " << baru->nomor << endl;
}

// menu 2
void panggilPasien() {
    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    Pasien* temp = head;

    cout << "Memanggil: " << temp->nama 
         << " (No: " << temp->nomor << ")\n";
    
    //riwayat
    Pasien* selesai = new Pasien();
    selesai->nomor = temp->nomor;
    selesai->nama = temp->nama;
    selesai->next = riwayat;
    riwayat = selesai;

    head = head->next;
    delete temp;

    if(head == NULL) {
        tail = NULL;
    }
}

// menu 3
void tambahDarurat() {
    string nama;
    cout << "Masukkan nama pasien darurat: ";
    cin >> nama;

    Pasien* baru = new Pasien();
    baru->nomor = nomorAntrian++;
    baru->nama = nama;

    // Masuk ke depan
    baru->next = head;
    head = baru;

    if(tail == NULL) {
        tail = baru;
    }

    cout << "Pasien darurat ditambahkan dengan nomor antrian: "
         << baru->nomor << endl;
}


