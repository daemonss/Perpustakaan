/**
 * File: peminjam.h
 * Deskripsi: Header untuk ADT Peminjam dengan antrian prioritas
 * Berisi definisi struktur data dan deklarasi fungsi-fungsi untuk manajemen peminjam
 */

#ifndef PEMINJAM_H
#define PEMINJAM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "buku.h"

 // Definisi level prioritas anggota
typedef enum {
     MASYARAKAT_UMUM = 0,   // Prioritas terendah
     MAHASISWA = 1,         // Prioritas menengah
     DOSEN = 2              // Prioritas tertinggi
} TipePeminjam;

 // Definisi struktur Node Peminjam
typedef struct NodePeminjam {
     char nama[50];             // Nama peminjam
     TipePeminjam tipe;         // Tipe/kategori peminjam
     char judul_buku[50];       // Judul buku yang dipinjam
     bool sedang_meminjam;      // Status peminjaman (true jika sedang meminjam)
     struct NodePeminjam *next; // Pointer ke node berikutnya
     struct NodePeminjam *prev; // Pointer ke node sebelumnya
} NodePeminjam;
 
 // Definisi struktur List Antrian Peminjam
typedef struct {
     NodePeminjam *first;       // Pointer ke node pertama
     NodePeminjam *last;        // Pointer ke node terakhir
     int size;                  // Jumlah peminjam dalam antrian
} ListPeminjam;

 // Definisi struktur Riwayat Peminjaman untuk Stack
typedef struct RiwayatNode {
     char nama[50];             // Nama peminjam
     char judul_buku[50];       // Judul buku yang dipinjam
     struct RiwayatNode *next;  // Pointer ke node berikutnya
} RiwayatNode;

 // Definisi struktur Stack untuk riwayat aktivitas
typedef struct {
     RiwayatNode *top;          // Pointer ke elemen teratas stack
} StackRiwayat;

 // Deklarasi fungsi-fungsi untuk manajemen peminjam
 void createEmptyPeminjam(ListPeminjam *list);
 bool isEmptyPeminjam(ListPeminjam list);
 NodePeminjam* alokasiNodePeminjam(char nama[], TipePeminjam tipe, char judul_buku[]);
 void dealokasiNodePeminjam(NodePeminjam *node);
 void insertPeminjamDenganPrioritas(ListPeminjam *list, char nama[], TipePeminjam tipe, char judul_buku[]);
 void deleteFirstPeminjam(ListPeminjam *list);
 void deleteLastPeminjam(ListPeminjam *list);
 void deletePeminjamByNama(ListPeminjam *list, char nama[], char judul_buku[]);
 void printPeminjam(ListPeminjam list);
 void printPeminjamByBuku(ListPeminjam list, char judul_buku[]);
 NodePeminjam* findPeminjamByNama(ListPeminjam list, char nama[], char judul_buku[]);
 NodePeminjam* findNextPeminjamForBuku(ListPeminjam list, char judul_buku[]);
 char* getTipePeminjamStr(TipePeminjam tipe);
 
 
 // Deklarasi fungsi-fungsi untuk stack riwayat aktivitas
 void createEmptyStack(StackRiwayat *stack);
 bool isEmptyStack(StackRiwayat stack);
 RiwayatNode* alokasiRiwayatNode(char nama[], char judul_buku[]);
 void dealokasiRiwayatNode(RiwayatNode *node);
 void pushRiwayat(StackRiwayat *stack, char nama[], char judul_buku[]);
 void popRiwayat(StackRiwayat *stack, char nama[], char judul_buku[]);
 void printStack(StackRiwayat stack);
 
 #endif // PEMINJAM_H