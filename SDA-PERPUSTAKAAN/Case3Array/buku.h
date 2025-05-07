/**
 * buku.h
 * Header file untuk ADT Buku yang diimplementasikan dengan array
 * 
 * Berisi definisi struct dan fungsi-fungsi untuk mengelola daftar buku
 * pada sistem perpustakaan perguruan tinggi
 */

 #ifndef BUKU_H
 #define BUKU_H
 
 #include <stdbool.h>
 
 // Forward declaration untuk menghindari circular include
 typedef struct QueuePeminjam QueuePeminjam;
 
 // Definisi konstanta
 #define MAX_BUKU 100
 #define MAX_JUDUL 50
 
 // Definisi tipe data Buku
 typedef struct {
     char judul[MAX_JUDUL];  // Judul buku
     int stok;               // Jumlah stok buku yang tersedia
     QueuePeminjam *queuePeminjam;  // Pointer ke antrian peminjam buku
 } Buku;
 
 // Definisi tipe data DaftarBuku (array of buku)
 typedef struct {
     Buku data[MAX_BUKU];    // Array untuk menyimpan buku
     int jumlah;             // Jumlah buku yang tersimpan dalam array
 } DaftarBuku;
 

 void inisialisasiDaftarBuku(DaftarBuku *daftar);
 

 bool tambahBuku(DaftarBuku *daftar, char *judul, int stok);
 

 int cariBuku(DaftarBuku daftar, char *judul);
 

 bool kurangiStokBuku(Buku *buku);
 

 void tambahStokBuku(Buku *buku);
 

 void tampilkanInfoBuku(Buku buku);
 

 void tampilkanDaftarBuku(DaftarBuku daftar);
 
 #endif /* BUKU_H */