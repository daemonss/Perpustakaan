/**
 * buku.c
 * Implementasi ADT Buku yang disimpan dalam array
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "buku.h"
 #include "peminjam.h"
 
 /**
  * Inisialisasi daftar buku
  */
 void inisialisasiDaftarBuku(DaftarBuku *daftar) {
     daftar->jumlah = 0;
 }
 
 /**
  * Menambahkan buku baru ke dalam daftar
  */
 bool tambahBuku(DaftarBuku *daftar, char *judul, int stok) {
     // Cek apakah daftar penuh
     if (daftar->jumlah >= MAX_BUKU) {
         printf("Daftar buku penuh, tidak dapat menambahkan buku baru.\n");
         return false;
     }
     
     // Cek apakah buku sudah ada
     if (cariBuku(*daftar, judul) != -1) {
         printf("Buku dengan judul \"%s\" sudah ada dalam daftar.\n", judul);
         return false;
     }
     
     // Tambahkan buku baru
     int idx = daftar->jumlah;
     strncpy(daftar->data[idx].judul, judul, MAX_JUDUL - 1);
     daftar->data[idx].judul[MAX_JUDUL - 1] = '\0';  // Pastikan null-terminated
     daftar->data[idx].stok = stok;
     
     // Alokasi memori untuk queue peminjam dan inisialisasi
     daftar->data[idx].queuePeminjam = (QueuePeminjam *)malloc(sizeof(QueuePeminjam));
     if (daftar->data[idx].queuePeminjam == NULL) {
         printf("Gagal mengalokasikan memori untuk antrian peminjam.\n");
         return false;
     }
     inisialisasiQueue(daftar->data[idx].queuePeminjam);
     
     daftar->jumlah++;
     printf("Buku \"%s\" berhasil ditambahkan dengan stok %d.\n", judul, stok);
     return true;
 }
 
 /**
  * Mencari buku berdasarkan judul
  */
 int cariBuku(DaftarBuku daftar, char *judul) {
     for (int i = 0; i < daftar.jumlah; i++) {
         if (strcmp(daftar.data[i].judul, judul) == 0) {
             return i;
         }
     }
     return -1;  // Buku tidak ditemukan
 }
 
 /**
  * Mengurangi stok buku karena dipinjam
  */
 bool kurangiStokBuku(Buku *buku) {
     if (buku->stok <= 0) {
         return false;
     }
     
     buku->stok--;
     return true;
 }
 
 /**
  * Menambah stok buku karena dikembalikan
  */
 void tambahStokBuku(Buku *buku) {
     buku->stok++;
 }
 
 /**
  * Menampilkan informasi buku (judul dan stok)
  */
 void tampilkanInfoBuku(Buku buku) {
     printf("Judul: %s\n", buku.judul);
     printf("Stok: %d\n", buku.stok);
     
     // Tampilkan informasi antrian peminjam jika ada
     if (buku.queuePeminjam != NULL) {
         int jumlahAntrian = hitungJumlahAntrian(*(buku.queuePeminjam));
         printf("Jumlah antrian peminjam: %d\n", jumlahAntrian);
     } else {
         printf("Belum ada antrian peminjam\n");
     }
 }
 
 /**
  * Menampilkan seluruh daftar buku beserta informasinya
  */
 void tampilkanDaftarBuku(DaftarBuku daftar) {
     if (daftar.jumlah == 0) {
         printf("Daftar buku kosong.\n");
         return;
     }
     
     printf("\n===== DAFTAR BUKU =====\n");
     for (int i = 0; i < daftar.jumlah; i++) {
         printf("\n[%d] ", i + 1);
         tampilkanInfoBuku(daftar.data[i]);
     }
     printf("======================\n");
 }