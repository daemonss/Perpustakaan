/* 
 * File: buku.h
 * Deskripsi: Header file untuk ADT Buku dalam sistem perpustakaan
 * Menggunakan implementasi Singly Linked List untuk menyimpan daftar buku
 */

 #ifndef BUKU_H
 #define BUKU_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 
 // Struktur data untuk Buku
 typedef struct {
     char judul[100];  // Judul buku
     int stok;         // Jumlah stok buku
 } Buku;
 
 // Node untuk Singly Linked List Buku
 typedef struct ElmtBuku* addressBuku;
 typedef struct ElmtBuku {
     Buku info;
     addressBuku next;
 } ElmtBuku;
 
 // Linked List untuk menyimpan daftar buku
 typedef struct {
     addressBuku first;
 } ListBuku;
 
 // KONSTRUKTOR
 // Inisialisasi list buku kosong
 void createListBuku(ListBuku *L);
 
 // DESTRUKTOR
 // Menghapus seluruh elemen dalam list buku
 void deleteListBuku(ListBuku *L);
 
 // SELEKTOR & VALIDATOR
 // Mengecek apakah list buku kosong
 bool isEmptyBuku(ListBuku L);
 
 // Mencari buku berdasarkan judul
 addressBuku findBuku(ListBuku L, char *judul);
 
 // OPERATOR DASAR
 // Menambahkan buku baru ke dalam list
 void insertBuku(ListBuku *L, char *judul, int stok);
 
 // Menghapus buku dari list
 void deleteBuku(ListBuku *L, char *judul);
 
 // OPERATOR TAMBAHAN
 // Mengubah stok buku
 void updateStokBuku(ListBuku *L, char *judul, int stok);
 
 // Mengurangi stok buku saat dipinjam
 bool decreaseStokBuku(ListBuku *L, char *judul);
 
 // Menambah stok buku saat dikembalikan
 void increaseStokBuku(ListBuku *L, char *judul);
 
 // Menampilkan seluruh buku dalam list
 void displayListBuku(ListBuku L);
 
 #endif /* BUKU_H */