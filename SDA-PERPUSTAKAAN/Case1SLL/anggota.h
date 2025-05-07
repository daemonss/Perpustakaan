/*
 * File: anggota.h
 * Deskripsi: Header file untuk ADT Anggota perpustakaan
 * Menggunakan implementasi Singly Linked List untuk menyimpan daftar anggota
 */

 #ifndef ANGGOTA_H
 #define ANGGOTA_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 
 // Enumerasi untuk level prioritas anggota
 typedef enum {
     MASYARAKAT_UMUM = 1,  // Prioritas terendah
     MAHASISWA = 2,
     DOSEN = 3             // Prioritas tertinggi
 } TipePrioritas;
 
 // Struktur data untuk Anggota
 typedef struct {
     char nama[100];         // Nama anggota
     TipePrioritas prioritas; // Level prioritas anggota
 } Anggota;
 
 // Node untuk Singly Linked List Anggota
 typedef struct ElmtAnggota* addressAnggota;
 typedef struct ElmtAnggota {
     Anggota info;
     addressAnggota next;
 } ElmtAnggota;
 
 // Linked List untuk menyimpan daftar anggota
 typedef struct {
     addressAnggota first;
 } ListAnggota;
 
 // KONSTRUKTOR
 // Inisialisasi list anggota kosong
 void createListAnggota(ListAnggota *L);
 
 // DESTRUKTOR
 // Menghapus seluruh elemen dalam list anggota
 void deleteListAnggota(ListAnggota *L);
 
 // SELEKTOR & VALIDATOR
 // Mengecek apakah list anggota kosong
 bool isEmptyAnggota(ListAnggota L);
 
 // Mencari anggota berdasarkan nama
 addressAnggota findAnggota(ListAnggota L, char *nama);
 
 // OPERATOR DASAR
 // Menambahkan anggota baru ke dalam list
 void insertAnggota(ListAnggota *L, char *nama, TipePrioritas prioritas);
 
 // Menghapus anggota dari list
 void deleteAnggota(ListAnggota *L, char *nama);
 
 // Mengkonversi tipe prioritas ke string untuk ditampilkan
 char* getPrioritasString(TipePrioritas prioritas);
 
 // Menampilkan seluruh anggota dalam list
 void displayListAnggota(ListAnggota L);
 
 #endif /* ANGGOTA_H */