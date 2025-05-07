/**
 * File: buku.c
 * Deskripsi: Implementasi ADT Buku menggunakan Doubly Linked List
 * Berisi definisi fungsi-fungsi untuk manajemen buku
 */

 #include "buku.h"

 /**
  * Membuat list buku kosong
  * @param list Pointer ke list buku yang akan diinisialisasi
  */
 void createEmptyBuku(ListBuku *list) {
     list->first = NULL;
     list->last = NULL;
 }
 
 /**
  * Memeriksa apakah list buku kosong
  * @param list List buku yang akan diperiksa
  * @return true jika list kosong, false jika tidak
  */
 bool isEmptyBuku(ListBuku list) {
     return (list.first == NULL && list.last == NULL);
 }
 
 /**
  * Alokasi node buku baru
  * @param judul Judul buku
  * @param stok Jumlah stok buku
  * @return Pointer ke node buku yang telah dialokasi
  */
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
 
 /**
  * Dealokasi node buku
  * @param node Pointer ke node buku yang akan didealokasi
  */
 void dealokasiNodeBuku(NodeBuku *node) {
     free(node);
 }
 
 /**
  * Menambahkan buku di awal list
  * @param list Pointer ke list buku
  * @param judul Judul buku yang akan ditambahkan
  * @param stok Jumlah stok buku
  */
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
 
 /**
  * Menambahkan buku di akhir list
  * @param list Pointer ke list buku
  * @param judul Judul buku yang akan ditambahkan
  * @param stok Jumlah stok buku
  */
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
 
 /**
  * Menambahkan buku setelah node tertentu
  * @param list Pointer ke list buku
  * @param prev_node Node sebelum posisi yang akan ditambahkan
  * @param judul Judul buku yang akan ditambahkan
  * @param stok Jumlah stok buku
  */
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
 
 /**
  * Menghapus buku di awal list
  * @param list Pointer ke list buku
  */
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
 
 /**
  * Menghapus buku di akhir list
  * @param list Pointer ke list buku
  */
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
 
 /**
  * Menghapus buku setelah node tertentu
  * @param list Pointer ke list buku
  * @param prev_node Node sebelum posisi yang akan dihapus
  */
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
 
 /**
  * Mencetak daftar buku
  * @param list List buku yang akan dicetak
  */
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
 
 /**
  * Mencari buku berdasarkan judul
  * @param list List buku yang akan dicari
  * @param judul Judul buku yang dicari
  * @return Pointer ke node buku jika ditemukan, NULL jika tidak ditemukan
  */
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
 
 /**
  * Mengupdate stok buku
  * @param list Pointer ke list buku
  * @param judul Judul buku yang akan diupdate stoknya
  * @param perubahan Nilai perubahan stok (positif untuk penambahan, negatif untuk pengurangan)
  */
 void updateStokBuku(ListBuku *list, char judul[], int perubahan) {
     NodeBuku *buku = findBuku(*list, judul);
     if (buku != NULL) {
         buku->stok_tersedia += perubahan;
         printf("Stok buku \"%s\" berhasil diupdate. Stok tersedia sekarang: %d\n", judul, buku->stok_tersedia);
     } else {
         printf("Buku dengan judul \"%s\" tidak ditemukan.\n", judul);
     }
 }