/**
 * File: menu.c
 * Deskripsi: Implementasi pengelolaan menu interaktif
 * Berisi implementasi fungsi-fungsi untuk navigasi menu sistem perpustakaan
 */

#include "menu.h"

// Implementasi variabel global untuk data buku dan peminjam
ListBuku daftarBuku;
ListPeminjam daftarPeminjam;
StackRiwayat riwayatAktivitas;

/**
 * Membersihkan layar konsol
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/**
 * Menampilkan menu utama
 */
void tampilkanMenuUtama() {
    clearScreen();
    printf("===========================================\n");
    printf("|        PERPUSTAKAAN POLBAN JTK          |\n");
    printf("===========================================\n");
    printf("| 1. Manajemen Buku                       |\n");
    printf("| 2. Manajemen Anggota                    |\n");
    printf("| 3. Manajemen Peminjaman                 |\n");
    printf("| 4. Jalankan Skenario Pengujian          |\n");
    printf("| 0. Keluar                               |\n");
    printf("===========================================\n");
    printf("Pilihan: ");
}

/**
 * Memproses input untuk menu utama
 */
void prosesMenuUtama() {
    int pilihan;
    
    do {
        tampilkanMenuUtama();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer
        
        switch (pilihan) {
            case 1:
                prosesMenuBuku();
                break;
            case 2:
                prosesMenuAnggota();
                break;
            case 3:
                prosesMenuPeminjaman();
                break;
            case 4:
                jalankanSkenarioPengujian();
                pause();
                break;
            case 0:
                printf("Terima kasih telah menggunakan sistem perpustakaan!\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                pause();
                break;
        }
    } while (pilihan != 0);
}

/**
 * Menampilkan menu manajemen buku
 */
void tampilkanMenuBuku() {
    clearScreen();
    printf("==== Manajemen Buku ====\n");
    printf("1. Tambah Buku\n");
    printf("2. Tampilkan Daftar Buku\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");
}

/**
 * Memproses input untuk menu manajemen buku
 */
void prosesMenuBuku() {
    int pilihan;
    
    do {
        tampilkanMenuBuku();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer
        
        switch (pilihan) {
            case 1:
                tambahBuku();
                pause();
                break;
            case 2:
                tampilkanDaftarBuku();
                pause();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                pause();
                break;
        }
    } while (pilihan != 0);
}

/**
 * Menambahkan buku baru ke daftar
 */
void tambahBuku() {
    char judul[50];
    int stok;
    
    printf("Masukkan judul buku: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0; // Menghapus karakter newline
    
    printf("Masukkan jumlah stok: ");
    scanf("%d", &stok);
    getchar(); // Membersihkan buffer
    
    // Memeriksa apakah buku sudah ada
    if (findBuku(daftarBuku, judul) != NULL) {
        printf("Buku dengan judul \"%s\" sudah ada dalam daftar.\n", judul);
        return;
    }
    
    insertLastBuku(&daftarBuku, judul, stok);
    visualisasiStrukturData();
}

/**
 * Menampilkan daftar buku
 */
void tampilkanDaftarBuku() {
    printBuku(daftarBuku);
    visualisasiStrukturData();
}

/**
 * Menampilkan menu manajemen anggota
 */
void tampilkanMenuAnggota() {
    clearScreen();
    printf("==== Manajemen Anggota ====\n");
    printf("1. Tambah Anggota ke Buku\n");
    printf("2. Tampilkan Antrian Peminjam Buku\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");
}

/**
 * Memproses input untuk menu manajemen anggota
 */
void prosesMenuAnggota() {
    int pilihan;
    
    do {
        tampilkanMenuAnggota();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer
        
        switch (pilihan) {
            case 1:
                tambahAnggotaKeBuku();
                pause();
                break;
            case 2:
                tampilkanAntrianPeminjamBuku();
                pause();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                pause();
                break;
        }
    } while (pilihan != 0);
}

/**
 * Menambahkan anggota ke antrian peminjaman buku
 */
void tambahAnggotaKeBuku() {
    char nama[50], judul[50];
    int tipe;
    
    printf("Masukkan nama anggota: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Menghapus karakter newline
    
    printf("Masukkan judul buku yang ingin dipinjam: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0; // Menghapus karakter newline
    
    // Memeriksa apakah buku ada
    NodeBuku *buku = findBuku(daftarBuku, judul);
    if (buku == NULL) {
        printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
        return;
    }
    
    printf("Pilih tipe anggota:\n");
    printf("1. Mahasiswa\n");
    printf("2. Dosen\n");
    printf("3. Masyarakat Umum\n");
    printf("Pilihan: ");
    scanf("%d", &tipe);
    getchar(); // Membersihkan buffer
    
    TipePeminjam tipePeminjam;
    switch (tipe) {
        case 1:
            tipePeminjam = MAHASISWA;
            break;
        case 2:
            tipePeminjam = DOSEN;
            break;
        case 3:
            tipePeminjam = MASYARAKAT_UMUM;
            break;
        default:
            printf("Tipe anggota tidak valid.\n");
            return;
    }
    
    insertPeminjamDenganPrioritas(&daftarPeminjam, nama, tipePeminjam, judul);
    
    // Mencatat aktivitas dalam stack riwayat
    pushRiwayat(&riwayatAktivitas, nama, judul);
    
    visualisasiStrukturData();
}

/**
 * Menampilkan antrian peminjam untuk buku tertentu
 */
void tampilkanAntrianPeminjamBuku() {
    char judul[50];
    
    printf("Masukkan judul buku: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0; // Menghapus karakter newline
    
    // Memeriksa apakah buku ada
    NodeBuku *buku = findBuku(daftarBuku, judul);
    if (buku == NULL) {
        printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
        return;
    }
    
    printPeminjamByBuku(daftarPeminjam, judul);
    visualisasiStrukturData();
}

/**
 * Menampilkan menu manajemen peminjaman
 */
void tampilkanMenuPeminjaman() {
    clearScreen();
    printf("==== Manajemen Peminjaman ====\n");
    printf("1. Proses Peminjaman Buku\n");
    printf("2. Pengembalian Buku\n");
    printf("3. Pembatalan Peminjaman\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");
}

/**
 * Memproses input untuk menu manajemen peminjaman
 */
void prosesMenuPeminjaman() {
    int pilihan;
    
    do {
        tampilkanMenuPeminjaman();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer
        
        switch (pilihan) {
            case 1:
                prosesPeminjamanBuku();
                pause();
                break;
            case 2:
                pengembalianBuku();
                pause();
                break;
            case 3:
                pembatalanPeminjaman();
                pause();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                pause();
                break;
        }
    } while (pilihan != 0);
}

/**
 * Memproses peminjaman buku
 */
void prosesPeminjamanBuku() {
    char judul[50];
    
    printf("Masukkan judul buku yang akan diproses peminjaman: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0; // Menghapus karakter newline
    
    // Memeriksa apakah buku ada
    NodeBuku *buku = findBuku(daftarBuku, judul);
    if (buku == NULL) {
        printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
        return;
    }
    
    // Memeriksa ketersediaan stok
    if (buku->stok_tersedia <= 0) {
        printf("Buku \"%s\" tidak tersedia stoknya saat ini.\n", judul);
        return;
    }
    
    // Mencari peminjam dengan prioritas tertinggi untuk buku tersebut
    NodePeminjam *peminjam = findNextPeminjamForBuku(daftarPeminjam, judul);
    if (peminjam == NULL) {
        printf("Tidak ada peminjam yang menunggu untuk buku \"%s\".\n", judul);
        return;
    }
    
    // Memproses peminjaman
    peminjam->sedang_meminjam = true;
    updateStokBuku(&daftarBuku, judul, -1); // Mengurangi stok tersedia
    
    printf("\nPeminjaman buku \"%s\" oleh %s (%s) berhasil diproses.\n", judul, peminjam->nama, getTipePeminjamStr(peminjam->tipe));
    visualisasiStrukturData();
}

/**
 * Memproses pengembalian buku
 */
void pengembalianBuku() {
    char judul[50], nama[50];
    
    printf("Masukkan judul buku yang dikembalikan: ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0; // Menghapus karakter newline
    
    printf("Masukkan nama peminjam yang mengembalikan: ");
    fgets(nama, sizeof(nama), stdin);
    nama[strcspn(nama, "\n")] = 0; // Menghapus karakter newline
    
    // Memeriksa apakah buku ada
    NodeBuku *buku = findBuku(daftarBuku, judul);
    if (buku == NULL) {
        printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
        return;
    }
    
    // Mencari peminjam
    NodePeminjam *peminjam = findPeminjamByNama(daftarPeminjam, nama, judul);
    if (peminjam == NULL || !peminjam->sedang_meminjam) {
        printf("%s tidak sedang meminjam buku \"%s\".\n", nama, judul);
        return;
    }
    
    // Memproses pengembalian
    peminjam->sedang_meminjam = false;
    updateStokBuku(&daftarBuku, judul, 1); // Menambah stok tersedia
    
    printf("\nPengembalian buku \"%s\" oleh %s berhasil diproses.\n", judul, nama);
    
    
    // Mencari peminjam berikutnya
    NodePeminjam *nextPeminjam = findNextPeminjamForBuku(daftarPeminjam, judul);
    if (nextPeminjam != NULL) {
        printf("Peminjam berikutnya untuk buku \"%s\" adalah %s (%s).\n", judul, nextPeminjam->nama, getTipePeminjamStr(nextPeminjam->tipe));
    }
    
    visualisasiStrukturData();
}

/**
 * Memproses pembatalan peminjaman
 */
void pembatalanPeminjaman() {
    char nama[50], judul_buku[50];
    
    // Mengambil aktivitas terakhir dari stack riwayat
    if (isEmptyStack(riwayatAktivitas)) {
        printf("Tidak ada aktivitas yang dapat dibatalkan.\n");
        return;
    }
    
    // Mengambil data dari stack riwayat
    popRiwayat(&riwayatAktivitas, nama, judul_buku);
    
    // Menghapus peminjam dari antrian
    deletePeminjamByNama(&daftarPeminjam, nama, judul_buku);
    
    printf("\nPembatalan peminjaman buku \"%s\" oleh %s berhasil diproses.\n", judul_buku, nama);
    visualisasiStrukturData();
}

/**
 * Menjalankan skenario pengujian sesuai dengan instruksi
 */
void jalankanSkenarioPengujian() {
    clearScreen();
    printf("===== SKENARIO PENGUJIAN =====\n\n");
    
    // a) 2 X insert elemen "Buku1" dan "Buku2" di list Buku dimana stok buku masing masing 1
    printf("a) Insert elemen \"Buku1\" dan \"Buku2\" (stok 1):\n");
    insertLastBuku(&daftarBuku, "Buku1", 1);
    insertLastBuku(&daftarBuku, "Buku2", 1);
    printBuku(daftarBuku);
    visualisasiStrukturData();
    printf("\n");
    
    // b) 1 X insert elemen "Anggota1" sebagai mahasiswa di list peminjaman "Buku1"
    printf("b) Insert elemen \"Anggota1\" (Mahasiswa) ke peminjaman \"Buku1\":\n");
    insertPeminjamDenganPrioritas(&daftarPeminjam, "Anggota1", MAHASISWA, "Buku1");
    pushRiwayat(&riwayatAktivitas, "Anggota1", "Buku1");
    printPeminjamByBuku(daftarPeminjam, "Buku1");
    visualisasiStrukturData();
    printf("\n");
    
    // c) 1 X insert elemen "Dosen1" sebagai dosen di list peminjaman "Buku1"
    printf("c) Insert elemen \"Dosen1\" (Dosen) ke peminjaman \"Buku1\":\n");
    insertPeminjamDenganPrioritas(&daftarPeminjam, "Dosen1", DOSEN, "Buku1");
    pushRiwayat(&riwayatAktivitas, "Dosen1", "Buku1");
    printPeminjamByBuku(daftarPeminjam, "Buku1");
    visualisasiStrukturData();
    printf("\n");
    
    // d) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku1"
    printf("d) Insert elemen \"Umum1\" (Umum) ke peminjaman \"Buku1\":\n");
    insertPeminjamDenganPrioritas(&daftarPeminjam, "Umum1", MASYARAKAT_UMUM, "Buku1");
    pushRiwayat(&riwayatAktivitas, "Umum1", "Buku1");
    printPeminjamByBuku(daftarPeminjam, "Buku1");
    visualisasiStrukturData();
    printf("\n");
    
    // e) 1 X insert elemen "Umum1" sebagai masyarakat umum di list peminjaman "Buku2"
    printf("e) Insert elemen \"Umum1\" (Umum) ke peminjaman \"Buku2\":\n");
    insertPeminjamDenganPrioritas(&daftarPeminjam, "Umum1", MASYARAKAT_UMUM, "Buku2");
    pushRiwayat(&riwayatAktivitas, "Umum1", "Buku2");
    printPeminjamByBuku(daftarPeminjam, "Buku2");
    visualisasiStrukturData();
    printf("\n");
    
    // f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman.
    // Lanjutan dari implementasi yang terpotong di menu.c

// f) Proses peminjaman "Buku1". Pastikan "Dosen1" yang mendapatkan proses peminjaman.
    printf("f) Proses peminjaman \"Buku1\" (pastikan Dosen1 dipilih):\n");
    NodeBuku *buku1 = findBuku(daftarBuku, "Buku1");
    if (buku1 != NULL && buku1->stok_tersedia > 0) {
        NodePeminjam *nextPeminjam = findNextPeminjamForBuku(daftarPeminjam, "Buku1");
        if (nextPeminjam != NULL) {
            nextPeminjam->sedang_meminjam = true;
            updateStokBuku(&daftarBuku, "Buku1", -1);
            printf("Peminjaman berhasil oleh: %s (%s)\n", 
                nextPeminjam->nama, 
                getTipePeminjamStr(nextPeminjam->tipe));
        }
    } else {
        printf("Buku1 tidak tersedia atau tidak ada peminjam.\n");
    }
    visualisasiStrukturData();
    printf("\n");

    // g) Pengembalian Buku1 oleh Dosen1
    printf("g) Pengembalian Buku1 oleh Dosen1:\n");
    NodePeminjam *dosen1 = findPeminjamByNama(daftarPeminjam, "Dosen1", "Buku1");
    if (dosen1 != NULL && dosen1->sedang_meminjam) {
        dosen1->sedang_meminjam = false;
        updateStokBuku(&daftarBuku, "Buku1", 1);
        printf("Pengembalian berhasil oleh: %s\n", dosen1->nama);
        
        // Cari peminjam berikutnya (Anggota1)
        NodePeminjam *nextPeminjam = findNextPeminjamForBuku(daftarPeminjam, "Buku1");
        if (nextPeminjam != NULL) {
            printf("Peminjam berikutnya: %s (%s)\n", 
                nextPeminjam->nama, 
                getTipePeminjamStr(nextPeminjam->tipe));
        }
    }
    visualisasiStrukturData();
    printf("\n");

    // h) Umum1 membatalkan peminjaman Buku2
    printf("h) Umum1 membatalkan peminjaman Buku2:\n");
    deletePeminjamByNama(&daftarPeminjam, "Umum1", "Buku2");
    visualisasiStrukturData();
    printf("\n");
}

    // Fungsi untuk pause eksekusi
void pause() {
    printf("\nTekan Enter untuk melanjutkan...");
    getchar();
}

    // Fungsi visualisasi struktur data (contoh sederhana)
void visualisasiStrukturData() {
    printf("\n=== VISUALISASI STRUCT ===\n");
    printBuku(daftarBuku);
    printPeminjam(daftarPeminjam);
    printStack(riwayatAktivitas);
}