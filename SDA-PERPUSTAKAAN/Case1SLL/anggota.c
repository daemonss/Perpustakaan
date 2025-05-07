/*
 * File: anggota.c
 * Deskripsi: Implementasi fungsi-fungsi untuk ADT Anggota
 */

 #include "anggota.h"

 // Inisialisasi list anggota kosong
 void createListAnggota(ListAnggota *L) {
     L->first = NULL;
 }
 
 // Menghapus seluruh elemen dalam list anggota
 void deleteListAnggota(ListAnggota *L) {
     addressAnggota P, temp;
     
     P = L->first;
     while (P != NULL) {
         temp = P;
         P = P->next;
         free(temp);
     }
     
     L->first = NULL;
 }
 
 // Mengecek apakah list anggota kosong
 bool isEmptyAnggota(ListAnggota L) {
     return (L.first == NULL);
 }
 
 // Mencari anggota berdasarkan nama
 addressAnggota findAnggota(ListAnggota L, char *nama) {
     addressAnggota P = L.first;
     
     while (P != NULL) {
         if (strcmp(P->info.nama, nama) == 0) {
             return P;
         }
         P = P->next;
     }
     
     return NULL;
 }
 
 // Menambahkan anggota baru ke dalam list
 void insertAnggota(ListAnggota *L, char *nama, TipePrioritas prioritas) {
     addressAnggota P = (addressAnggota) malloc(sizeof(ElmtAnggota));
     
     if (P != NULL) {
         strcpy(P->info.nama, nama);
         P->info.prioritas = prioritas;
         P->next = NULL;
         
         // Jika list kosong
         if (isEmptyAnggota(*L)) {
             L->first = P;
         } else {
             // Tambahkan di akhir list
             addressAnggota last = L->first;
             while (last->next != NULL) {
                 last = last->next;
             }
             last->next = P;
         }
         
         printf("Anggota '%s' dengan prioritas %s berhasil ditambahkan\n", 
                nama, getPrioritasString(prioritas));
     } else {
         printf("Gagal mengalokasikan memori untuk anggota baru\n");
     }
 }
 
 // Menghapus anggota dari list
 void deleteAnggota(ListAnggota *L, char *nama) {
     if (isEmptyAnggota(*L)) {
         printf("List anggota kosong\n");
         return;
     }
     
     addressAnggota P = L->first;
     addressAnggota prev = NULL;
     
     // Jika anggota yang akan dihapus adalah elemen pertama
     if (strcmp(P->info.nama, nama) == 0) {
         L->first = P->next;
         free(P);
         printf("Anggota '%s' berhasil dihapus\n", nama);
         return;
     }
     
     // Cari anggota yang akan dihapus
     while (P != NULL && strcmp(P->info.nama, nama) != 0) {
         prev = P;
         P = P->next;
     }
     
     // Jika anggota ditemukan
     if (P != NULL) {
         prev->next = P->next;
         free(P);
         printf("Anggota '%s' berhasil dihapus\n", nama);
     } else {
         printf("Anggota '%s' tidak ditemukan\n", nama);
     }
 }
 
 // Mengkonversi tipe prioritas ke string untuk ditampilkan
 char* getPrioritasString(TipePrioritas prioritas) {
     switch (prioritas) {
         case DOSEN:
             return "Dosen";
         case MAHASISWA:
             return "Mahasiswa";
         case MASYARAKAT_UMUM:
             return "Masyarakat Umum";
         default:
             return "Tidak diketahui";
     }
 }
 
 // Menampilkan seluruh anggota dalam list
 void displayListAnggota(ListAnggota L) {
     if (isEmptyAnggota(L)) {
         printf("List anggota kosong\n");
         return;
     }
     
     addressAnggota P = L.first;
     int i = 1;
     
     printf("\n==================================================\n");
     printf("|                DAFTAR ANGGOTA                  |\n");
     printf("==================================================\n");
     printf("| No |       Nama        |       Prioritas       |\n");
     printf("--------------------------------------------------\n");
     
     while (P != NULL) {
         printf("| %-2d | %-17s | %-21s |\n", 
                i, P->info.nama, getPrioritasString(P->info.prioritas));
         i++;
         P = P->next;
     }
     
     printf("==================================================\n\n");
 }