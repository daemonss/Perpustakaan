/*
 * File: peminjaman.h
 * Deskripsi: Header file untuk ADT Peminjaman buku
 * Menggunakan implementasi Singly Linked List untuk menyimpan antrian peminjaman
 */

 #ifndef PEMINJAMAN_H
 #define PEMINJAMAN_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "buku.h"
 #include "anggota.h"
 
 // Struktur data untuk Peminjaman
 typedef struct {
     char judulBuku[100];   // Judul buku yang dipinjam
     char namaAnggota[100]; // Nama anggota peminjam
     TipePrioritas prioritas; // Prioritas anggota
     bool sedangDipinjam;   // Status peminjaman (sedang dipinjam atau dalam antrian)
 } Peminjaman;
 
 // Node untuk Singly Linked List Peminjaman
 typedef struct ElmtPeminjaman* addressPeminjaman;
 typedef struct ElmtPeminjaman {
     Peminjaman info;
     addressPeminjaman next;
 } ElmtPeminjaman;
 
 // Linked List untuk menyimpan daftar peminjaman
 typedef struct {
     addressPeminjaman first;
 } ListPeminjaman;
 
 // Struktur untuk menyimpan riwayat peminjaman (untuk fitur undo)
 typedef struct {
     Peminjaman data[100];  // Array untuk menyimpan history peminjaman
     int top;               // Indeks top stack
 } StackPeminjaman;
 
 // KONSTRUKTOR
 // Inisialisasi list peminjaman kosong
 void createListPeminjaman(ListPeminjaman *L);
 
 // Inisialisasi stack peminjaman kosong
 void createStackPeminjaman(StackPeminjaman *S);
 
 // DESTRUKTOR
 // Menghapus seluruh elemen dalam list peminjaman
 void deleteListPeminjaman(ListPeminjaman *L);
 
 // SELEKTOR & VALIDATOR
 // Mengecek apakah list peminjaman kosong
 bool isEmptyPeminjaman(ListPeminjaman L);
 
 // Mengecek apakah stack peminjaman kosong
 bool isEmptyStack(StackPeminjaman S);
 
 // Mengecek apakah stack peminjaman penuh
 bool isFullStack(StackPeminjaman S);
 
 // Mencari peminjaman berdasarkan judul buku dan nama anggota
 addressPeminjaman findPeminjaman(ListPeminjaman L, char *judulBuku, char *namaAnggota);
 
 // Mencari peminjaman aktif berdasarkan judul buku
 addressPeminjaman findPeminjamanAktif(ListPeminjaman L, char *judulBuku);
 
 // OPERATOR DASAR
 // Menambahkan peminjaman baru ke dalam list berdasarkan prioritas
 void insertPeminjaman(ListPeminjaman *L, char *judulBuku, char *namaAnggota, 
                       TipePrioritas prioritas, ListBuku *daftarBuku, StackPeminjaman *S);
 
 // Menghapus peminjaman dari list
 void deletePeminjaman(ListPeminjaman *L, char *judulBuku, char *namaAnggota);
 
 // Push peminjaman ke stack (untuk fitur undo)
 void pushPeminjaman(StackPeminjaman *S, Peminjaman data);
 
 // Pop peminjaman dari stack (untuk fitur undo)
 Peminjaman popPeminjaman(StackPeminjaman *S);
 
 // Membatalkan peminjaman terakhir untuk anggota tertentu
 void batalkanPeminjaman(ListPeminjaman *L, char *namaAnggota, 
                         ListBuku *daftarBuku, StackPeminjaman *S);
 
 // OPERATOR PEMINJAMAN
 // Memproses peminjaman buku
 void prosesPeminjaman(ListPeminjaman *L, char *judulBuku, ListBuku *daftarBuku);
 
 // Memproses pengembalian buku
 void prosesKembali(ListPeminjaman *L, char *judulBuku, char *namaAnggota, ListBuku *daftarBuku);
 
 // Menampilkan daftar peminjaman
 void displayListPeminjaman(ListPeminjaman L);
 
 // Menampilkan daftar antrian peminjaman untuk buku tertentu
 void displayAntrianPeminjaman(ListPeminjaman L, char *judulBuku);

 // Menampilkan visualisasi linked list antrian
 //void displayVisualisasiAntrian(ListPeminjaman L, char *judulBuku);
 
 #endif /* PEMINJAMAN_H */