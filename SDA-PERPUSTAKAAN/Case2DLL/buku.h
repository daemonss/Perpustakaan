/**
 * File: buku.h
 * Deskripsi: Header untuk ADT Buku menggunakan Doubly Linked List
 * Berisi definisi struktur data dan deklarasi fungsi-fungsi untuk manajemen buku
 */

 #ifndef BUKU_H
 #define BUKU_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 
 // Definisi struktur Node Buku (Doubly Linked List)
 typedef struct NodeBuku {
     char judul[50];        // Judul buku
     int stok;              // Jumlah stok buku
     int stok_tersedia;     // Jumlah stok yang tersedia untuk dipinjam
     struct NodeBuku *next; // Pointer ke node berikutnya
     struct NodeBuku *prev; // Pointer ke node sebelumnya
 } NodeBuku;
 
 // Definisi struktur List Buku
 typedef struct {
     NodeBuku *first;       // Pointer ke node pertama
     NodeBuku *last;        // Pointer ke node terakhir
 } ListBuku;
 
 // Deklarasi fungsi-fungsi untuk manajemen buku
 void createEmptyBuku(ListBuku *list);
 bool isEmptyBuku(ListBuku list);
 NodeBuku* alokasiNodeBuku(char judul[], int stok);
 void dealokasiNodeBuku(NodeBuku *node);
 void insertFirstBuku(ListBuku *list, char judul[], int stok);
 void insertLastBuku(ListBuku *list, char judul[], int stok);
 void insertAfterBuku(ListBuku *list, NodeBuku *prev_node, char judul[], int stok);
 void deleteFirstBuku(ListBuku *list);
 void deleteLastBuku(ListBuku *list);
 void deleteAfterBuku(ListBuku *list, NodeBuku *prev_node);
 void printBuku(ListBuku list);
 NodeBuku* findBuku(ListBuku list, char judul[]);
 void updateStokBuku(ListBuku *list, char judul[], int perubahan);
 
 #endif // BUKU_H