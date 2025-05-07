/*
 * File: peminjaman.c
 * Deskripsi: Implementasi fungsi-fungsi untuk ADT Peminjaman
 */

 #include "peminjaman.h"

 // Inisialisasi list peminjaman kosong
 void createListPeminjaman(ListPeminjaman *L) {
     L->first = NULL;
 }
 
 // Inisialisasi stack peminjaman kosong
 void createStackPeminjaman(StackPeminjaman *S) {
     S->top = -1;
 }
 
 // Menghapus seluruh elemen dalam list peminjaman
 void deleteListPeminjaman(ListPeminjaman *L) {
     addressPeminjaman P, temp;
     
     P = L->first;
     while (P != NULL) {
         temp = P;
         P = P->next;
         free(temp);
     }
     
     L->first = NULL;
 }
 
 // Mengecek apakah list peminjaman kosong
 bool isEmptyPeminjaman(ListPeminjaman L) {
     return (L.first == NULL);
 }
 
 // Mengecek apakah stack peminjaman kosong
 bool isEmptyStack(StackPeminjaman S) {
     return (S.top == -1);
 }
 
 // Mengecek apakah stack peminjaman penuh
 bool isFullStack(StackPeminjaman S) {
     return (S.top == 99); // Karena ukuran array 100 (indeks 0-99)
 }
 
 // Mencari peminjaman berdasarkan judul buku dan nama anggota
 addressPeminjaman findPeminjaman(ListPeminjaman L, char *judulBuku, char *namaAnggota) {
     addressPeminjaman P = L.first;
     
     while (P != NULL) {
         if (strcmp(P->info.judulBuku, judulBuku) == 0 && 
             strcmp(P->info.namaAnggota, namaAnggota) == 0) {
             return P;
         }
         P = P->next;
     }
     
     return NULL;
 }
 
 // Mencari peminjaman aktif berdasarkan judul buku
 addressPeminjaman findPeminjamanAktif(ListPeminjaman L, char *judulBuku) {
     addressPeminjaman P = L.first;
     
     while (P != NULL) {
         if (strcmp(P->info.judulBuku, judulBuku) == 0 && P->info.sedangDipinjam) {
             return P;
         }
         P = P->next;
     }
     
     return NULL;
 }
 
 // Menambahkan peminjaman baru ke dalam list berdasarkan prioritas
 void insertPeminjaman(ListPeminjaman *L, char *judulBuku, char *namaAnggota, 
                       TipePrioritas prioritas, ListBuku *daftarBuku, StackPeminjaman *S) {
     // Cek apakah buku ada di daftar
     addressBuku bukuDipinjam = findBuku(*daftarBuku, judulBuku);
     if (bukuDipinjam == NULL) {
         printf("Buku '%s' tidak tersedia di perpustakaan\n", judulBuku);
         return;
     }
     
     // Cek apakah peminjaman sudah ada
     if (findPeminjaman(*L, judulBuku, namaAnggota) != NULL) {
         printf("Anggota '%s' sudah dalam antrian peminjaman buku '%s'\n", namaAnggota, judulBuku);
         return;
     }
     
     // Buat node peminjaman baru
     addressPeminjaman P = (addressPeminjaman) malloc(sizeof(ElmtPeminjaman));
     
     if (P != NULL) {
         strcpy(P->info.judulBuku, judulBuku);
         strcpy(P->info.namaAnggota, namaAnggota);
         P->info.prioritas = prioritas;
         P->info.sedangDipinjam = false; // Default belum dipinjam (masih dalam antrian)
         P->next = NULL;
         
         // Simpan ke stack untuk fitur undo
         pushPeminjaman(S, P->info);
         
         // Jika list kosong
         if (isEmptyPeminjaman(*L)) {
             L->first = P;
             printf("Peminjaman buku '%s' oleh '%s' (%s) berhasil ditambahkan ke antrian\n", 
                    judulBuku, namaAnggota, getPrioritasString(prioritas));
             return;
         }
         
         // Jika prioritas lebih tinggi dari elemen pertama
         if (P->info.prioritas > L->first->info.prioritas) {
             P->next = L->first;
             L->first = P;
             printf("Peminjaman buku '%s' oleh '%s' (%s) berhasil ditambahkan ke antrian\n", 
                    judulBuku, namaAnggota, getPrioritasString(prioritas));
             return;
         }
         
         // Cari posisi yang tepat berdasarkan prioritas
         addressPeminjaman current = L->first;
         addressPeminjaman prev = NULL;
         
         while (current != NULL && P->info.prioritas <= current->info.prioritas) {
             // Untuk prioritas yang sama, tambahkan di belakang (FIFO)
             if (P->info.prioritas == current->info.prioritas && 
                 strcmp(current->info.judulBuku, judulBuku) == 0) {
                 prev = current;
                 current = current->next;
             } else if (strcmp(current->info.judulBuku, judulBuku) != 0) {
                 // Jika buku berbeda, lanjut ke node berikutnya
                 prev = current;
                 current = current->next;
             } else {
                 break;
             }
         }
         
         // Insert di posisi yang tepat
         if (prev == NULL) {
             P->next = L->first;
             L->first = P;
         } else {
             P->next = prev->next;
             prev->next = P;
         }
         
         printf("Peminjaman buku '%s' oleh '%s' (%s) berhasil ditambahkan ke antrian\n", 
                judulBuku, namaAnggota, getPrioritasString(prioritas));
     } else {
         printf("Gagal mengalokasikan memori untuk peminjaman baru\n");
     }
 }
 
 // Menghapus peminjaman dari list
 void deletePeminjaman(ListPeminjaman *L, char *judulBuku, char *namaAnggota) {
     if (isEmptyPeminjaman(*L)) {
         printf("List peminjaman kosong\n");
         return;
     }
     
     addressPeminjaman P = L->first;
     addressPeminjaman prev = NULL;
     
     // Jika peminjaman yang akan dihapus adalah elemen pertama
     if (strcmp(P->info.judulBuku, judulBuku) == 0 && 
         strcmp(P->info.namaAnggota, namaAnggota) == 0) {
         L->first = P->next;
         free(P);
         printf("Peminjaman buku '%s' oleh '%s' berhasil dihapus\n", judulBuku, namaAnggota);
         return;
     }
     
     // Cari peminjaman yang akan dihapus
     while (P != NULL && (strcmp(P->info.judulBuku, judulBuku) != 0 || 
                         strcmp(P->info.namaAnggota, namaAnggota) != 0)) {
         prev = P;
         P = P->next;
     }
     
     // Jika peminjaman ditemukan
     if (P != NULL) {
         prev->next = P->next;
         free(P);
         printf("Peminjaman buku '%s' oleh '%s' berhasil dihapus\n", judulBuku, namaAnggota);
     } else {
         printf("Peminjaman buku '%s' oleh '%s' tidak ditemukan\n", judulBuku, namaAnggota);
     }
 }
 
 // Push peminjaman ke stack (untuk fitur undo)
 void pushPeminjaman(StackPeminjaman *S, Peminjaman data) {
     if (isFullStack(*S)) {
         printf("Stack peminjaman penuh, tidak bisa menyimpan history\n");
         return;
     }
     
     S->top++;
     S->data[S->top] = data;
 }
 
 // Pop peminjaman dari stack (untuk fitur undo)
 Peminjaman popPeminjaman(StackPeminjaman *S) {
     Peminjaman temp;
     
     if (isEmptyStack(*S)) {
         printf("Stack peminjaman kosong, tidak ada history\n");
         strcpy(temp.judulBuku, "");
         strcpy(temp.namaAnggota, "");
         temp.prioritas = 0;
         temp.sedangDipinjam = false;
         return temp;
     }
     
     temp = S->data[S->top];
     S->top--;
     return temp;
 }
 
 // Membatalkan peminjaman terakhir untuk anggota tertentu
 void batalkanPeminjaman(ListPeminjaman *L, char *namaAnggota, 
                         ListBuku *daftarBuku, StackPeminjaman *S) {
     if (isEmptyStack(*S)) {
         printf("Tidak ada peminjaman yang dapat dibatalkan\n");
         return;
     }
     
     // Cari peminjaman terakhir dari anggota tersebut dalam stack
     int i = S->top;
     bool found = false;
     
     while (i >= 0 && !found) {
         if (strcmp(S->data[i].namaAnggota, namaAnggota) == 0) {
             found = true;
         } else {
             i--;
         }
     }
     
     if (!found) {
         printf("Tidak ada peminjaman terakhir dari anggota '%s'\n", namaAnggota);
         return;
     }
     
     // Ambil data peminjaman terakhir
     Peminjaman terakhir = S->data[i];
     
     // Hapus dari stack
     for (int j = i; j < S->top; j++) {
         S->data[j] = S->data[j+1];
     }
     S->top--;
     
     // Hapus dari list peminjaman
     deletePeminjaman(L, terakhir.judulBuku, terakhir.namaAnggota);
     
     printf("Pembatalan peminjaman buku '%s' oleh '%s' berhasil\n", 
            terakhir.judulBuku, terakhir.namaAnggota);
 }
 
 // Memproses peminjaman buku
 void prosesPeminjaman(ListPeminjaman *L, char *judulBuku, ListBuku *daftarBuku) {
     // Cek ketersediaan stok buku
     addressBuku bukuDipinjam = findBuku(*daftarBuku, judulBuku);
     if (bukuDipinjam == NULL) {
         printf("Buku '%s' tidak tersedia di perpustakaan\n", judulBuku);
         return;
     }
     
     if (bukuDipinjam->info.stok <= 0) {
         printf("Stok buku '%s' habis\n", judulBuku);
         return;
     }
     
     // Cek apakah ada peminjaman yang aktif untuk buku ini
     addressPeminjaman aktif = findPeminjamanAktif(*L, judulBuku);
     if (aktif != NULL) {
         printf("Buku '%s' sedang dipinjam oleh '%s'\n", judulBuku, aktif->info.namaAnggota);
         return;
     }
     
     // Cari peminjam pertama dari antrian sesuai prioritas
     if (isEmptyPeminjaman(*L)) {
         printf("Tidak ada antrian peminjaman untuk buku '%s'\n", judulBuku);
         return;
     }
     
     addressPeminjaman P = L->first;
     addressPeminjaman peminjamTerpilih = NULL;
     TipePrioritas prioritasTertinggi = 0;
     
     // Cari peminjam dengan prioritas tertinggi untuk buku tersebut
     while (P != NULL) {
         if (strcmp(P->info.judulBuku, judulBuku) == 0 && 
             P->info.prioritas > prioritasTertinggi && 
             !P->info.sedangDipinjam) {
             peminjamTerpilih = P;
             prioritasTertinggi = P->info.prioritas;
         }
         P = P->next;
     }
     
     if (peminjamTerpilih != NULL) {
         // Proses peminjaman
         peminjamTerpilih->info.sedangDipinjam = true;
         decreaseStokBuku(daftarBuku, judulBuku);
         
         printf("Buku '%s' berhasil dipinjam oleh '%s' (%s)\n", 
                judulBuku, peminjamTerpilih->info.namaAnggota, 
                getPrioritasString(peminjamTerpilih->info.prioritas));
     } else {
         printf("Tidak ada antrian peminjaman untuk buku '%s'\n", judulBuku);
     }
 }
 
 // Memproses pengembalian buku
 void prosesKembali(ListPeminjaman *L, char *judulBuku, char *namaAnggota, ListBuku *daftarBuku) {
     // Cek apakah buku sedang dipinjam oleh anggota tersebut
     addressPeminjaman P = findPeminjaman(*L, judulBuku, namaAnggota);
     
     if (P == NULL || !P->info.sedangDipinjam) {
         printf("Buku '%s' tidak sedang dipinjam oleh '%s'\n", judulBuku, namaAnggota);
         return;
     }
     
     // Kembalikan buku
     P->info.sedangDipinjam = false;
     increaseStokBuku(daftarBuku, judulBuku);
     
     // Hapus peminjaman dari list
     deletePeminjaman(L, judulBuku, namaAnggota);
     
     printf("Buku '%s' berhasil dikembalikan oleh '%s'\n", judulBuku, namaAnggota);
     printf("Memeriksa antrian peminjaman untuk buku '%s'...\n", judulBuku);
     
     // Cek antrian berikutnya
     prosesPeminjaman(L, judulBuku, daftarBuku);
 }
 
 // Menampilkan daftar peminjaman
 void displayListPeminjaman(ListPeminjaman L) {
     if (isEmptyPeminjaman(L)) {
         printf("List peminjaman kosong\n");
         return;
     }
     
     addressPeminjaman P = L.first;
     int i = 1;
     
     printf("\n================================================================\n");
     printf("|                     DAFTAR PEMINJAMAN                         |\n");
     printf("================================================================\n");
     printf("| No |    Judul Buku   |   Nama Anggota  | Prioritas |  Status  |\n");
     printf("----------------------------------------------------------------\n");
     
     while (P != NULL) {
         printf("| %-2d | %-15s | %-15s | %-9s | %-8s |\n", 
                i, P->info.judulBuku, P->info.namaAnggota, 
                getPrioritasString(P->info.prioritas), 
                P->info.sedangDipinjam ? "Dipinjam" : "Antri");
         i++;
         P = P->next;
     }
     
     printf("================================================================\n\n");
 }
 
 // Menampilkan daftar antrian peminjaman untuk buku tertentu
 void displayAntrianPeminjaman(ListPeminjaman L, char *judulBuku) {
     if (isEmptyPeminjaman(L)) {
         printf("List peminjaman kosong\n");
         return;
     }
     
     addressPeminjaman P = L.first;
     int i = 1;
     bool found = false;
     
     printf("\n================================================================\n");
     printf("|             DAFTAR ANTRIAN PEMINJAMAN BUKU '%s'               |\n", judulBuku);
     printf("================================================================\n");
     printf("| No |   Nama Anggota  | Prioritas |  Status  |\n");
     printf("----------------------------------------------------------------\n");
     
     while (P != NULL) {
         if (strcmp(P->info.judulBuku, judulBuku) == 0) {
             printf("| %-2d | %-15s | %-9s | %-8s |\n", 
                    i, P->info.namaAnggota, 
                    getPrioritasString(P->info.prioritas), 
                    P->info.sedangDipinjam ? "Dipinjam" : "Antri");
             i++;
             found = true;
         }
         P = P->next;
     }
     
     if (!found) {
         printf("|            Tidak ada antrian untuk buku ini                  |\n");
     }
     
     printf("================================================================\n\n");
 }

 // peminjaman.c - Tambahkan fungsi ini
//void displayVisualisasiAntrian(ListPeminjaman L) {
//    addressPeminjaman P = L.first;
//    
//    printf("\nVisualisasi Antrian:\n");
//    printf("HEAD -> ");
//    
//    while(P != NULL) {
//        printf("[%s (%s)] -> ", P->info.namaAnggota, getPrioritasString(P->info.prioritas));
//        P = P->next;
//    }
//    printf("NULL\n\n");
//}