/*
 * File: buku.c
 * Deskripsi: Implementasi fungsi-fungsi untuk ADT Buku
 */

 #include "buku.h"

 // Inisialisasi list buku kosong
 void createListBuku(ListBuku *L) {
     L->first = NULL;
 }
 
 // Menghapus seluruh elemen dalam list buku
 void deleteListBuku(ListBuku *L) {
     addressBuku P, temp;
     
     P = L->first;
     while (P != NULL) {
         temp = P;
         P = P->next;
         free(temp);
     }
     
     L->first = NULL;
 }
 
 // Mengecek apakah list buku kosong
 bool isEmptyBuku(ListBuku L) {
     return (L.first == NULL);
 }
 
 // Mencari buku berdasarkan judul
 addressBuku findBuku(ListBuku L, char *judul) {
     addressBuku P = L.first;
     
     while (P != NULL) {
         if (strcmp(P->info.judul, judul) == 0) {
             return P;
         }
         P = P->next;
     }
     
     return NULL;
 }
 
 // Menambahkan buku baru ke dalam list
 void insertBuku(ListBuku *L, char *judul, int stok) {
     addressBuku P = (addressBuku) malloc(sizeof(ElmtBuku));
     
     if (P != NULL) {
         strcpy(P->info.judul, judul);
         P->info.stok = stok;
         P->next = NULL;
         
         // Jika list kosong
         if (isEmptyBuku(*L)) {
             L->first = P;
         } else {
             // Tambahkan di akhir list
             addressBuku last = L->first;
             while (last->next != NULL) {
                 last = last->next;
             }
             last->next = P;
         }
         
         printf("Buku '%s' dengan stok %d berhasil ditambahkan\n", judul, stok);
     } else {
         printf("Gagal mengalokasikan memori untuk buku baru\n");
     }
 }
 
 // Menghapus buku dari list
 void deleteBuku(ListBuku *L, char *judul) {
     if (isEmptyBuku(*L)) {
         printf("List buku kosong\n");
         return;
     }
     
     addressBuku P = L->first;
     addressBuku prev = NULL;
     
     // Jika buku yang akan dihapus adalah elemen pertama
     if (strcmp(P->info.judul, judul) == 0) {
         L->first = P->next;
         free(P);
         printf("Buku '%s' berhasil dihapus\n", judul);
         return;
     }
     
     // Cari buku yang akan dihapus
     while (P != NULL && strcmp(P->info.judul, judul) != 0) {
         prev = P;
         P = P->next;
     }
     
     // Jika buku ditemukan
     if (P != NULL) {
         prev->next = P->next;
         free(P);
         printf("Buku '%s' berhasil dihapus\n", judul);
     } else {
         printf("Buku '%s' tidak ditemukan\n", judul);
     }
 }
 
 // Mengubah stok buku
 void updateStokBuku(ListBuku *L, char *judul, int stok) {
     addressBuku P = findBuku(*L, judul);
     
     if (P != NULL) {
         P->info.stok = stok;
         printf("Stok buku '%s' berhasil diubah menjadi %d\n", judul, stok);
     } else {
         printf("Buku '%s' tidak ditemukan\n", judul);
     }
 }
 
 // Mengurangi stok buku saat dipinjam
 bool decreaseStokBuku(ListBuku *L, char *judul) {
     addressBuku P = findBuku(*L, judul);
     
     if (P != NULL) {
         if (P->info.stok > 0) {
             P->info.stok--;
             printf("Stok buku '%s' berkurang menjadi %d\n", judul, P->info.stok);
             return true;
         } else {
             printf("Stok buku '%s' sudah habis\n", judul);
             return false;
         }
     } else {
         printf("Buku '%s' tidak ditemukan\n", judul);
         return false;
     }
 }
 
 // Menambah stok buku saat dikembalikan
 void increaseStokBuku(ListBuku *L, char *judul) {
     addressBuku P = findBuku(*L, judul);
     
     if (P != NULL) {
         P->info.stok++;
         printf("Stok buku '%s' bertambah menjadi %d\n", judul, P->info.stok);
     } else {
         printf("Buku '%s' tidak ditemukan\n", judul);
     }
 }
 
 // Menampilkan seluruh buku dalam list
 void displayListBuku(ListBuku L) {
     if (isEmptyBuku(L)) {
         printf("List buku kosong\n");
         return;
     }
     
     addressBuku P = L.first;
     int i = 1;
     
     printf("\n=============================================\n");
     printf("|               DAFTAR BUKU                 |\n");
     printf("=============================================\n");
     printf("| No |          Judul          |    Stok    |\n");
     printf("---------------------------------------------\n");
     
     while (P != NULL) {
         printf("| %-2d | %-23s | %-10d |\n", i, P->info.judul, P->info.stok);
         i++;
         P = P->next;
     }
     
     printf("=============================================\n\n");
 }