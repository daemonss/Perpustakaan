/**
 * menu.c
 * Implementasi untuk manajemen menu sistem perpustakaan
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "menu.h"
 #include "buku.h"
 #include "peminjam.h"  
 
 // ========================= IMPLEMENTASI MENU =========================
 
 void tampilkanMenu() {
     printf("\n========================================\n");
     printf("   SISTEM PERPUSTAKAAN PERGURUAN TINGGI\n");
     printf("========================================\n");
     printf("1. Tambah Buku\n");
     printf("2. Tambah Peminjam ke Buku\n");
     printf("3. Proses Peminjaman Buku\n");
     printf("4. Pengembalian Buku\n");
     printf("5. Batalkan Permintaan Peminjaman\n");
     printf("6. Tampilkan Daftar Buku dan Antrian\n");
     printf("7. Jalankan Skenario Pengujian\n");
     printf("0. Keluar\n");
     printf("----------------------------------------\n");
     printf("Pilihan Anda: ");
 }
 
 bool prosesMenu(int pilihan, DaftarBuku *daftar) {
     switch(pilihan) {
         case 1: menuTambahBuku(daftar); break;
         case 2: menuTambahPeminjam(daftar); break;
         case 3: menuProsesPeminjaman(daftar); break;
         case 4: menuPengembalianBuku(daftar); break;
         case 5: menuBatalkanPeminjaman(daftar); break;
         case 6: menuTampilkanDataPerpustakaan(daftar); break;
         case 7: jalankanSkenarioPengujian(daftar); break;
         case 0: 
             printf("\nTerima kasih telah menggunakan sistem!\n");
             return false;
         default:
             printf("\nPilihan tidak valid!\n");
     }
     return true;
 }
 
 // ==================== IMPLEMENTASI SUBMENU ======================
 
 void menuTambahBuku(DaftarBuku *daftar) {
     char judul[MAX_JUDUL];
     int stok;
     
     printf("\n=== TAMBAH BUKU BARU ===\n");
     printf("Masukkan judul buku: ");
     scanf(" %[^\n]", judul);
     
     printf("Masukkan stok awal: ");
     scanf("%d", &stok);
     
     if(stok < 1) {
         printf("Error: Stok minimal 1\n");
         return;
     }
     
     if(tambahBuku(daftar, judul, stok)) {
         printf("Buku berhasil ditambahkan!\n");
         tampilkanDaftarBuku(*daftar);
     }
 }
 
 void menuTambahPeminjam(DaftarBuku *daftar) {
     char judul[MAX_JUDUL], nama[MAX_NAMA];
     int level;
     
     printf("\n=== TAMBAH PEMINJAM ===\n");
     tampilkanDaftarBuku(*daftar);
     
     if(daftar->jumlah == 0) return;
     
     printf("Masukkan judul buku: ");
     scanf(" %[^\n]", judul);
     
     int idx = cariBuku(*daftar, judul);
     if(idx == -1) {
         printf("Buku tidak ditemukan!\n");
         return;
     }
     
     printf("Nama peminjam: ");
     scanf(" %[^\n]", nama);
     
     printf("Level (0=Umum, 1=Mahasiswa, 2=Dosen): ");
     scanf("%d", &level);
     
     LevelPrioritas prioritas;
     switch(level) {
         case 0: prioritas = UMUM; break;
         case 1: prioritas = MAHASISWA; break;
         case 2: prioritas = DOSEN; break;
         default: 
             printf("Input invalid! Default ke Umum\n");
             prioritas = UMUM;
     }
     
     if(tambahPeminjam(daftar->data[idx].queuePeminjam, nama, prioritas)) {
         printf("Peminjam berhasil ditambahkan!\n");
         tampilkanQueuePeminjam(*(daftar->data[idx].queuePeminjam));
     }
 }
 
 void menuProsesPeminjaman(DaftarBuku *daftar) {
     char judul[MAX_JUDUL];
     Peminjam p;
     
     printf("\n=== PROSES PEMINJAMAN ===\n");
     tampilkanDaftarBuku(*daftar);
     
     if(daftar->jumlah == 0) return;
     
     printf("Masukkan judul buku: ");
     scanf(" %[^\n]", judul);
     
     int idx = cariBuku(*daftar, judul);
     if(idx == -1) {
         printf("Buku tidak ditemukan!\n");
         return;
     }
     
     if(daftar->data[idx].stok < 1) {
         printf("Stok buku habis!\n");
         return;
     }
     
     if(ambilPeminjamTertinggi(daftar->data[idx].queuePeminjam, &p)) {
         daftar->data[idx].stok--;
         printf("[BERHASIL] %s (%s) meminjam buku\n", 
               p.nama, getLevelString(p.level));
         printf("Stok tersisa: %d\n", daftar->data[idx].stok);
     } else {
         printf("Tidak ada antrian peminjam!\n");
     }
 }
 
 void menuPengembalianBuku(DaftarBuku *daftar) {
     char judul[MAX_JUDUL];
     
     printf("\n=== PENGEMBALIAN BUKU ===\n");
     tampilkanDaftarBuku(*daftar);
     
     if(daftar->jumlah == 0) return;
     
     printf("Masukkan judul buku: ");
     scanf(" %[^\n]", judul);
     
     int idx = cariBuku(*daftar, judul);
     if(idx == -1) {
         printf("Buku tidak ditemukan!\n");
         return;
     }
     
     daftar->data[idx].stok++;
     printf("Stok diperbarui: %d\n", daftar->data[idx].stok);
     
     // Proses antrian berikutnya
     Peminjam p;
     if(getPeminjamTertinggi(*(daftar->data[idx].queuePeminjam), &p)) {
         printf("Peminjam berikutnya: %s (%s)\n", 
               p.nama, getLevelString(p.level));
     }
 }
 
 void menuBatalkanPeminjaman(DaftarBuku *daftar) {
     char judul[MAX_JUDUL], nama[MAX_NAMA];
     
     printf("\n=== PEMBATALAN PEMINJAMAN ===\n");
     tampilkanDaftarBuku(*daftar);
     
     if(daftar->jumlah == 0) return;
     
     printf("Masukkan judul buku: ");
     scanf(" %[^\n]", judul);
     
     int idx = cariBuku(*daftar, judul);
     if(idx == -1) {
         printf("Buku tidak ditemukan!\n");
         return;
     }
     
     printf("Masukkan nama peminjam: ");
     scanf(" %[^\n]", nama);
     
     if(hapusPeminjam(daftar->data[idx].queuePeminjam, nama)) {
         printf("Pembatalan berhasil!\n");
         tampilkanQueuePeminjam(*(daftar->data[idx].queuePeminjam));
     } else {
         printf("Peminjam tidak ditemukan!\n");
     }
 }
 
 void menuTampilkanDataPerpustakaan(DaftarBuku *daftar) {
     printf("\n=== DATA PERPUSTAKAAN ===\n");
     tampilkanDaftarBuku(*daftar);
     
     for(int i = 0; i < daftar->jumlah; i++) {
         printf("\nAntrian untuk %s:\n", daftar->data[i].judul);
         tampilkanQueuePeminjam(*(daftar->data[i].queuePeminjam));
     }
 }
 
 // ================== IMPLEMENTASI SKENARIO ======================
 
 void jalankanSkenarioPengujian(DaftarBuku *daftar) {
    printf("\n=== MENJALANKAN SKENARIO PENGUJIAN ===\n");
    
    // Reset data
    for(int i = 0; i < daftar->jumlah; i++) {
        free(daftar->data[i].queuePeminjam);
    }
    inisialisasiDaftarBuku(daftar);

    // Skenario a
    printf("\na) Tambah Buku1 dan Buku2\n");
    tambahBuku(daftar, "Buku1", 1);
    tambahBuku(daftar, "Buku2", 1);
    tampilkanDaftarBuku(*daftar);

    // Skenario b
    printf("\nb) Tambah Anggota1 (Mahasiswa) ke Buku1\n");
    int idx1 = cariBuku(*daftar, "Buku1");
    tambahPeminjam(daftar->data[idx1].queuePeminjam, "Anggota1", MAHASISWA);
    printf("Antrian Buku1:\n");
    tampilkanQueuePeminjam(*(daftar->data[idx1].queuePeminjam));

    // Skenario c
    printf("\nc) Tambah Dosen1 ke Buku1\n");
    tambahPeminjam(daftar->data[idx1].queuePeminjam, "Dosen1", DOSEN);
    printf("Antrian Buku1 (Dosen1 harus di depan):\n");
    tampilkanQueuePeminjam(*(daftar->data[idx1].queuePeminjam));

    // Skenario d
    printf("\nd) Tambah Umum1 ke Buku1\n");
    tambahPeminjam(daftar->data[idx1].queuePeminjam, "Umum1", UMUM);
    printf("Antrian Buku1 (Urutan: Dosen1 > Anggota1 > Umum1):\n");
    tampilkanQueuePeminjam(*(daftar->data[idx1].queuePeminjam));

    // Skenario e
    printf("\ne) Tambah Umum1 ke Buku2\n");
    int idx2 = cariBuku(*daftar, "Buku2");
    tambahPeminjam(daftar->data[idx2].queuePeminjam, "Umum1", UMUM);
    printf("Antrian Buku2:\n");
    tampilkanQueuePeminjam(*(daftar->data[idx2].queuePeminjam));

    // Skenario f
    printf("\nf) Proses peminjaman Buku1\n");
    Peminjam p;
    if(ambilPeminjamTertinggi(daftar->data[idx1].queuePeminjam, &p)) {
        daftar->data[idx1].stok--;
        printf("[BERHASIL] %s (%s) meminjam buku\n", p.nama, getLevelString(p.level));
        printf("Stok Buku1: %d\n", daftar->data[idx1].stok);
    }
    printf("Antrian Buku1 setelah peminjaman:\n");
    tampilkanQueuePeminjam(*(daftar->data[idx1].queuePeminjam));

    // Skenario g
    printf("\ng) Pengembalian Buku1\n");
    daftar->data[idx1].stok++;
    printf("Stok Buku1: %d\n", daftar->data[idx1].stok);
    if(getPeminjamTertinggi(*(daftar->data[idx1].queuePeminjam), &p)) {
        printf("Peminjam berikutnya: %s (%s)\n", p.nama, getLevelString(p.level));
    }

    // Skenario h
    printf("\nh) Batalkan peminjaman Umum1 di Buku2\n");
    hapusPeminjam(daftar->data[idx2].queuePeminjam, "Umum1");
    printf("Antrian Buku2 setelah pembatalan:\n");
    tampilkanQueuePeminjam(*(daftar->data[idx2].queuePeminjam));

    printf("\n=== SKENARIO SELESAI ===\n");
}