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

// menu 4 (linear search)
void cariPasien() {
    if (head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }

    string nama;
    cout << "Masukkan nama yang dicari: ";
    cin >> nama;

    Pasien* temp = head;
    int posisi = 1;

    while (temp != NULL) {
        if (temp->nama == nama) {
            cout << "\n=== DATA DITEMUKAN ===\n";
            cout << "Nama   : " << temp->nama << endl;
            cout << "Nomor  : " << temp->nomor << endl;
            cout << "Posisi : " << posisi << " dalam antrian\n";
            return;
        }
        temp = temp->next;
        posisi++;
    }

    cout << "Pasien tidak ditemukan!\n";
}

// menu 5 (bubble sort)
void tampilkan() {
    if(head == NULL) {
        cout << "Antrian kosong!\n";
        return;
    }
    
    //bubble sort
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
        cout << temp->nomor << " - " << temp->nama << endl;
        temp = temp->next;
    }
}


// menu 6
void tampilRiwayat() {
	if(riwayat == NULL) {
		cout << "Belum ada riwayat!\n";
		return;
	}
	
	Pasien* temp = riwayat;
	
	cout << "\n=== RIWAYAT KUNJUNGAN ===\n";
	
	while(temp != NULL) {
		cout << temp->nomor << " - " << temp->nama << endl;
		temp = temp->next;
	}
}

// menu 7
void simpanFile() {
    FILE* file = fopen("data_antrian.txt", "w");

    if (file == NULL) {
        cout << "Gagal membuka file!\n";
        return;
    }

    fprintf(file, "=== DAFTAR ANTRIAN ===\n");

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

    if (riwayat == NULL) {
        fprintf(file, "Belum ada riwayat.\n");
    } else {
        Pasien* temp = riwayat;
        while (temp != NULL) {
            fprintf(file, "%d - %s\n", temp->nomor, temp->nama.c_str());
            temp = temp->next;
        }
    }

    fclose(file);
    cout << "Data berhasil disimpan ke 'data_antrian.txt'!\n";
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
        cout << "Pilih: ";
        cin >> pilih;

        switch(pilih) {
            case 1: ambilAntrian(); break;
            case 2: panggilPasien(); break;
            case 3: tambahDarurat(); break;
            case 4: cariPasien(); break;
            case 5: tampilkan(); break;
            case 6: tampilRiwayat(); break;
            case 7: simpanFile(); break;
            case 8: cout << "Keluar...\n"; break;   // <-- ganti dari 7
            default: cout << "Pilihan salah!\n";
}
} while(pilih != 8);

    return 0;
}
