/**
 * File: buku.c
 * Deskripsi: Implementasi ADT Buku menggunakan Doubly Linked List
 * Berisi definisi fungsi-fungsi untuk manajemen buku
 */

 #include "buku.h"

 
 void createEmptyBuku(ListBuku *list) {
     list->first = NULL;
     list->last = NULL;
 }
 
 
 bool isEmptyBuku(ListBuku list) {
     return (list.first == NULL && list.last == NULL);
 }
 

 NodeBuku* alokasiNodeBuku(char judul[], int stok) {
     NodeBuku *node = (NodeBuku*) malloc(sizeof(NodeBuku));
     if (node != NULL) {
         strcpy(node->judul, judul);
         node->stok = stok;
         node->stok_tersedia = stok; // Awalnya stok tersedia sama dengan total stok
         node->next = NULL;
         node->prev = NULL;
     }
     return node;
 }
 

 void dealokasiNodeBuku(NodeBuku *node) {
     free(node);
 }
 
 
  
 void insertFirstBuku(ListBuku *list, char judul[], int stok) {
     NodeBuku *new_node = alokasiNodeBuku(judul, stok);
     if (new_node != NULL) {
         if (isEmptyBuku(*list)) {
             list->first = new_node;
             list->last = new_node;
         } else {
             new_node->next = list->first;
             list->first->prev = new_node;
             list->first = new_node;
         }
         printf("Buku \"%s\" berhasil ditambahkan dengan stok %d.\n", judul, stok);
     } else {
         printf("Gagal mengalokasi memori untuk buku baru.\n");
     }
 }
 
 
 void insertLastBuku(ListBuku *list, char judul[], int stok) {
     NodeBuku *new_node = alokasiNodeBuku(judul, stok);
     if (new_node != NULL) {
         if (isEmptyBuku(*list)) {
             list->first = new_node;
             list->last = new_node;
         } else {
             new_node->prev = list->last;
             list->last->next = new_node;
             list->last = new_node;
         }
         printf("Buku \"%s\" berhasil ditambahkan dengan stok %d.\n", judul, stok);
     } else {
         printf("Gagal mengalokasi memori untuk buku baru.\n");
     }
 }
 
 
 void insertAfterBuku(ListBuku *list, NodeBuku *prev_node, char judul[], int stok) {
     if (prev_node == NULL) {
         printf("Node sebelumnya tidak boleh NULL.\n");
         return;
     }
     
     NodeBuku *new_node = alokasiNodeBuku(judul, stok);
     if (new_node != NULL) {
         new_node->next = prev_node->next;
         new_node->prev = prev_node;
         
         if (prev_node->next != NULL) {
             prev_node->next->prev = new_node;
         } else {
             list->last = new_node; // Jika prev_node adalah node terakhir
         }
         
         prev_node->next = new_node;
         printf("Buku \"%s\" berhasil ditambahkan dengan stok %d.\n", judul, stok);
     } else {
         printf("Gagal mengalokasi memori untuk buku baru.\n");
     }
 }
 
 
 void deleteFirstBuku(ListBuku *list) {
     if (isEmptyBuku(*list)) {
         printf("List buku kosong, tidak ada yang dapat dihapus.\n");
         return;
     }
     
     NodeBuku *temp = list->first;
     if (list->first == list->last) {
         list->first = NULL;
         list->last = NULL;
     } else {
         list->first = list->first->next;
         list->first->prev = NULL;
     }
     
     printf("Buku \"%s\" berhasil dihapus.\n", temp->judul);
     dealokasiNodeBuku(temp);
 }
 
 
 void deleteLastBuku(ListBuku *list) {
     if (isEmptyBuku(*list)) {
         printf("List buku kosong, tidak ada yang dapat dihapus.\n");
         return;
     }
     
     NodeBuku *temp = list->last;
     if (list->first == list->last) {
         list->first = NULL;
         list->last = NULL;
     } else {
         list->last = list->last->prev;
         list->last->next = NULL;
     }
     
     printf("Buku \"%s\" berhasil dihapus.\n", temp->judul);
     dealokasiNodeBuku(temp);
 }
 
 
 void deleteAfterBuku(ListBuku *list, NodeBuku *prev_node) {
     if (prev_node == NULL || prev_node->next == NULL) {
         printf("Tidak ada node yang dapat dihapus.\n");
         return;
     }
     
     NodeBuku *temp = prev_node->next;
     prev_node->next = temp->next;
     
     if (temp->next != NULL) {
         temp->next->prev = prev_node;
     } else {
         list->last = prev_node; // Jika temp adalah node terakhir
     }
     
     printf("Buku \"%s\" berhasil dihapus.\n", temp->judul);
     dealokasiNodeBuku(temp);
 }
 
 
 void printBuku(ListBuku list) {
     if (isEmptyBuku(list)) {
         printf("List buku kosong.\n");
         return;
     }
     
     printf("\n===== DAFTAR BUKU =====\n");
     printf("%-5s %-30s %-15s %-15s\n", "No.", "Judul Buku", "Stok Total", "Stok Tersedia");
     printf("-------------------------------------------------------\n");
     
     int i = 1;
     NodeBuku *current = list.first;
     while (current != NULL) {
         printf("%-5d %-30s %-15d %-15d\n", i, current->judul, current->stok, current->stok_tersedia);
         current = current->next;
         i++;
     }
     printf("-------------------------------------------------------\n");
 }
 
 
 NodeBuku* findBuku(ListBuku list, char judul[]) {
     if (isEmptyBuku(list)) {
         return NULL;
     }
     
     NodeBuku *current = list.first;
     while (current != NULL) {
         if (strcmp(current->judul, judul) == 0) {
             return current;
         }
         current = current->next;
     }
     
     return NULL; // Buku tidak ditemukan
 }
 
 
 void updateStokBuku(ListBuku *list, char judul[], int perubahan) {
     NodeBuku *buku = findBuku(*list, judul);
     if (buku != NULL) {
         buku->stok_tersedia += perubahan;
         printf("Stok buku \"%s\" berhasil diupdate. Stok tersedia sekarang: %d\n", judul, buku->stok_tersedia);
     } else {
         printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
     }
 }