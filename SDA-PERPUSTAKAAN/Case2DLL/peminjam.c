/**
 * File: peminjam.c
 * Deskripsi: Implementasi ADT Peminjam dengan antrian prioritas
 * Berisi definisi fungsi-fungsi untuk manajemen peminjam
 */

 #include "peminjam.h"

 /**
  * Membuat list peminjam kosong
  * @param list Pointer ke list peminjam yang akan diinisialisasi
  */
 void createEmptyPeminjam(ListPeminjam *list) {
     list->first = NULL;
     list->last = NULL;
     list->size = 0;
 }
 
 /**
  * Memeriksa apakah list peminjam kosong
  * @param list List peminjam yang akan diperiksa
  * @return true jika list kosong, false jika tidak
  */
 bool isEmptyPeminjam(ListPeminjam list) {
     return (list.first == NULL && list.last == NULL);
 }
 
 /**
  * Alokasi node peminjam baru
  * @param nama Nama peminjam
  * @param tipe Tipe peminjam (MAHASISWA, DOSEN, atau MASYARAKAT_UMUM)
  * @param judul_buku Judul buku yang dipinjam
  * @return Pointer ke node peminjam yang telah dialokasi
  */
 NodePeminjam* alokasiNodePeminjam(char nama[], TipePeminjam tipe, char judul_buku[]) {
     NodePeminjam *node = (NodePeminjam*) malloc(sizeof(NodePeminjam));
     if (node != NULL) {
         strcpy(node->nama, nama);
         node->tipe = tipe;
         strcpy(node->judul_buku, judul_buku);
         node->sedang_meminjam = false;
         node->next = NULL;
         node->prev = NULL;
     }
     return node;
 }
 
 /**
  * Dealokasi node peminjam
  * @param node Pointer ke node peminjam yang akan didealokasi
  */
 void dealokasiNodePeminjam(NodePeminjam *node) {
     free(node);
 }
 
 /**
  * Menambahkan peminjam dengan memperhatikan prioritas
  * @param list Pointer ke list peminjam
  * @param nama Nama peminjam
  * @param tipe Tipe peminjam (MAHASISWA, DOSEN, atau MASYARAKAT_UMUM)
  * @param judul_buku Judul buku yang dipinjam
  */
 void insertPeminjamDenganPrioritas(ListPeminjam *list, char nama[], TipePeminjam tipe, char judul_buku[]) {
     NodePeminjam *new_node = alokasiNodePeminjam(nama, tipe, judul_buku);
     if (new_node == NULL) {
         printf("Gagal mengalokasi memori untuk peminjam baru.\n");
         return;
     }
     
     // Jika list kosong
     if (isEmptyPeminjam(*list)) {
         list->first = new_node;
         list->last = new_node;
         list->size++;
         printf("%s (%s) berhasil ditambahkan ke antrian peminjaman buku \"%s\".\n", 
                nama, getTipePeminjamStr(tipe), judul_buku);
         return;
     }
     
     // Cek jika peminjam dengan nama yang sama sudah ada dalam antrian untuk buku yang sama
     NodePeminjam *existing = findPeminjamByNama(*list, nama, judul_buku);
     if (existing != NULL) {
         printf("%s sudah ada dalam antrian peminjaman buku \"%s\".\n", nama, judul_buku);
         dealokasiNodePeminjam(new_node);
         return;
     }
     
     // Insert berdasarkan prioritas
     NodePeminjam *current = list->first;
     
     // Mencari posisi yang tepat berdasarkan prioritas
     while (current != NULL && (current->tipe > tipe || 
           (current->tipe == tipe && strcmp(current->judul_buku, judul_buku) == 0))) {
         current = current->next;
     }
     
     // Insert di awal list
     if (current == list->first) {
         new_node->next = list->first;
         list->first->prev = new_node;
         list->first = new_node;
     } 
     // Insert di akhir list
     else if (current == NULL) {
         new_node->prev = list->last;
         list->last->next = new_node;
         list->last = new_node;
     } 
     // Insert di tengah list
     else {
         new_node->next = current;
         new_node->prev = current->prev;
         current->prev->next = new_node;
         current->prev = new_node;
     }
     
     list->size++;
     printf("%s (%s) berhasil ditambahkan ke antrian peminjaman buku \"%s\".\n", 
            nama, getTipePeminjamStr(tipe), judul_buku);
 }
 
 /**
  * Menghapus peminjam di awal list
  * @param list Pointer ke list peminjam
  */
 void deleteFirstPeminjam(ListPeminjam *list) {
     if (isEmptyPeminjam(*list)) {
         printf("List peminjam kosong, tidak ada yang dapat dihapus.\n");
         return;
     }
     
     NodePeminjam *temp = list->first;
     
     if (list->first == list->last) {
         list->first = NULL;
         list->last = NULL;
     } else {
         list->first = list->first->next;
         list->first->prev = NULL;
     }
     
     printf("%s dihapus dari antrian peminjaman buku \"%s\".\n", temp->nama, temp->judul_buku);
     dealokasiNodePeminjam(temp);
     list->size--;
 }
 
 /**
  * Menghapus peminjam di akhir list
  * @param list Pointer ke list peminjam
  */
 void deleteLastPeminjam(ListPeminjam *list) {
     if (isEmptyPeminjam(*list)) {
         printf("List peminjam kosong, tidak ada yang dapat dihapus.\n");
         return;
     }
     
     NodePeminjam *temp = list->last;
     
     if (list->first == list->last) {
         list->first = NULL;
         list->last = NULL;
     } else {
         list->last = list->last->prev;
         list->last->next = NULL;
     }
     
     printf("%s dihapus dari antrian peminjaman buku \"%s\".\n", temp->nama, temp->judul_buku);
     dealokasiNodePeminjam(temp);
     list->size--;
 }
 
 /**
  * Menghapus peminjam berdasarkan nama
  * @param list Pointer ke list peminjam
  * @param nama Nama peminjam yang akan dihapus
  * @param judul_buku Judul buku yang dipinjam
  */
 void deletePeminjamByNama(ListPeminjam *list, char nama[], char judul_buku[]) {
     if (isEmptyPeminjam(*list)) {
         printf("List peminjam kosong, tidak ada yang dapat dihapus.\n");
         return;
     }
     
     NodePeminjam *current = list->first;
     while (current != NULL) {
         if (strcmp(current->nama, nama) == 0 && strcmp(current->judul_buku, judul_buku) == 0) {
             // Jika node yang dihapus adalah node pertama
             if (current == list->first) {
                 deleteFirstPeminjam(list);
                 return;
             }
             // Jika node yang dihapus adalah node terakhir
             else if (current == list->last) {
                 deleteLastPeminjam(list);
                 return;
             }
             // Jika node yang dihapus berada di tengah
             else {
                 current->prev->next = current->next;
                 current->next->prev = current->prev;
                 printf("%s dihapus dari antrian peminjaman buku \"%s\".\n", nama, judul_buku);
                 dealokasiNodePeminjam(current);
                 list->size--;
                 return;
             }
         }
         current = current->next;
     }
     
     printf("%s tidak ditemukan dalam antrian peminjaman buku \"%s\".\n", nama, judul_buku);
 }
 
 /**
  * Mencetak daftar semua peminjam
  * @param list List peminjam yang akan dicetak
  */
 void printPeminjam(ListPeminjam list) {
     if (isEmptyPeminjam(list)) {
         printf("List peminjam kosong.\n");
         return;
     }
     
     printf("\n===== DAFTAR PEMINJAM =====\n");
     printf("%-5s %-20s %-15s %-30s %-15s\n", "No.", "Nama", "Tipe", "Judul Buku", "Status");
     printf("-------------------------------------------------------------------------------\n");
     
     int i = 1;
     NodePeminjam *current = list.first;
     while (current != NULL) {
         printf("%-5d %-20s %-15s %-30s %-15s\n", 
                i, 
                current->nama, 
                getTipePeminjamStr(current->tipe),
                current->judul_buku,
                current->sedang_meminjam ? "Meminjam" : "Menunggu");
         current = current->next;
         i++;
     }
     printf("-------------------------------------------------------------------------------\n");
 }
 
 /**
  * Mencetak daftar peminjam untuk buku tertentu
  * @param list List peminjam yang akan dicetak
  * @param judul_buku Judul buku yang ingin dilihat peminjamnya
  */
 void printPeminjamByBuku(ListPeminjam list, char judul_buku[]) {
     if (isEmptyPeminjam(list)) {
         printf("List peminjam kosong.\n");
         return;
     }
     
     printf("\n===== DAFTAR PEMINJAM BUKU \"%s\" =====\n", judul_buku);
     printf("%-5s %-20s %-15s %-15s\n", "No.", "Nama", "Tipe", "Status");
     printf("-----------------------------------------------------\n");
     
     int i = 1;
     bool found = false;
     NodePeminjam *current = list.first;
     
     while (current != NULL) {
         if (strcmp(current->judul_buku, judul_buku) == 0) {
             printf("%-5d %-20s %-15s %-15s\n", 
                    i, 
                    current->nama, 
                    getTipePeminjamStr(current->tipe),
                    current->sedang_meminjam ? "Meminjam" : "Menunggu");
             found = true;
             i++;
         }
         current = current->next;
     }
     
     if (!found) {
         printf("Tidak ada peminjam untuk buku \"%s\".\n", judul_buku);
     }
     
     printf("-----------------------------------------------------\n");
     
     // Visualisasi antrian prioritas
     if (found) {
         printf("\n===== VISUALISASI ANTRIAN PRIORITAS =====\n");
         printf("[HEAD] ");
         
         current = list.first;
         while (current != NULL) {
             if (strcmp(current->judul_buku, judul_buku) == 0) {
                 printf("<- [%s (%s)] ", current->nama, getTipePeminjamStr(current->tipe));
             }
             current = current->next;
         }
         
         printf("<- [TAIL]\n");
         printf("------------------------------------------\n");
     }
 }
 
 /**
  * Mencari peminjam berdasarkan nama
  * @param list List peminjam yang akan dicari
  * @param nama Nama peminjam yang dicari
  * @param judul_buku Judul buku yang dipinjam
  * @return Pointer ke node peminjam jika ditemukan, NULL jika tidak ditemukan
  */
 NodePeminjam* findPeminjamByNama(ListPeminjam list, char nama[], char judul_buku[]) {
     if (isEmptyPeminjam(list)) {
         return NULL;
     }
     
     NodePeminjam *current = list.first;
     while (current != NULL) {
         if (strcmp(current->nama, nama) == 0 && strcmp(current->judul_buku, judul_buku) == 0) {
             return current;
         }
         current = current->next;
     }
     
     return NULL; // Peminjam tidak ditemukan
 }
 
 /**
  * Mencari peminjam dengan prioritas tertinggi untuk buku tertentu
  * @param list List peminjam yang akan dicari
  * @param judul_buku Judul buku yang dicari
  * @return Pointer ke node peminjam dengan prioritas tertinggi, NULL jika tidak ada peminjam
  */
 NodePeminjam* findNextPeminjamForBuku(ListPeminjam list, char judul_buku[]) {
     if (isEmptyPeminjam(list)) {
         return NULL;
     }
     
     NodePeminjam *current = list.first;
     while (current != NULL) {
         if (strcmp(current->judul_buku, judul_buku) == 0 && !current->sedang_meminjam) {
             return current; // Karena sudah diurutkan berdasarkan prioritas, peminjam pertama adalah yang memiliki prioritas tertinggi
         }
         current = current->next;
     }
     
     return NULL; // Tidak ada peminjam yang menunggu untuk buku tersebut
 }
 
 /**
  * Mendapatkan string representasi dari tipe peminjam
  * @param tipe Tipe peminjam
  * @return String representasi dari tipe peminjam
  */
 char* getTipePeminjamStr(TipePeminjam tipe) {
     switch (tipe) {
         case DOSEN:
             return "Dosen";
         case MAHASISWA:
             return "Mahasiswa";
         case MASYARAKAT_UMUM:
             return "Umum";
         default:
             return "Unknown";
     }
 }
 
 // Implementasi fungsi-fungsi untuk stack riwayat aktivitas
 
 /**
  * Membuat stack kosong
  * @param stack Pointer ke stack yang akan diinisialisasi
  */
 void createEmptyStack(StackRiwayat *stack) {
     stack->top = NULL;
 }
 
 /**
  * Memeriksa apakah stack kosong
  * @param stack Stack yang akan diperiksa
  * @return true jika stack kosong, false jika tidak
  */
 bool isEmptyStack(StackRiwayat stack) {
     return (stack.top == NULL);
 }
 
 /**
  * Alokasi node riwayat baru
  * @param nama Nama peminjam
  * @param judul_buku Judul buku yang dipinjam
  * @return Pointer ke node riwayat yang telah dialokasi
  */
 RiwayatNode* alokasiRiwayatNode(char nama[], char judul_buku[]) {
     RiwayatNode *node = (RiwayatNode*) malloc(sizeof(RiwayatNode));
     if (node != NULL) {
         strcpy(node->nama, nama);
         strcpy(node->judul_buku, judul_buku);
         node->next = NULL;
     }
     return node;
 }
 
 /**
  * Dealokasi node riwayat
  * @param node Pointer ke node riwayat yang akan didealokasi
  */
 void dealokasiRiwayatNode(RiwayatNode *node) {
     free(node);
 }
 
 /**
  * Menambahkan riwayat ke stack
  * @param stack Pointer ke stack
  * @param nama Nama peminjam
  * @param judul_buku Judul buku yang dipinjam
  */
 void pushRiwayat(StackRiwayat *stack, char nama[], char judul_buku[]) {
     RiwayatNode *new_node = alokasiRiwayatNode(nama, judul_buku);
     if (new_node != NULL) {
         new_node->next = stack->top;
         stack->top = new_node;
         printf("Aktivitas %s untuk buku \"%s\" berhasil dicatat dalam riwayat.\n", nama, judul_buku);
     } else {
         printf("Gagal mengalokasi memori untuk riwayat baru.\n");
     }
 }
 
 /**
  * Menghapus riwayat teratas dari stack
  * @param stack Pointer ke stack
  * @param nama Buffer untuk menyimpan nama peminjam yang dihapus
  * @param judul_buku Buffer untuk menyimpan judul buku yang dihapus
  */
 void popRiwayat(StackRiwayat *stack, char nama[], char judul_buku[]) {
     if (isEmptyStack(*stack)) {
         printf("Stack riwayat kosong, tidak ada yang dapat dihapus.\n");
         strcpy(nama, "");
         strcpy(judul_buku, "");
         return;
     }
     
     RiwayatNode *temp = stack->top;
     strcpy(nama, temp->nama);
     strcpy(judul_buku, temp->judul_buku);
     
     stack->top = stack->top->next;
     printf("Riwayat aktivitas %s untuk buku \"%s\" dihapus.\n", nama, judul_buku);
     dealokasiRiwayatNode(temp);
 }
 
 /**
  * Mencetak isi stack riwayat
  * @param stack Stack yang akan dicetak
  */
 void printStack(StackRiwayat stack) {
     if (isEmptyStack(stack)) {
         printf("Stack riwayat kosong.\n");
         return;
     }
     
     printf("\n===== RIWAYAT AKTIVITAS =====\n");
     printf("%-5s %-20s %-30s\n", "No.", "Nama", "Judul Buku");
     printf("--------------------------------------------------\n");
     
     int i = 1;
     RiwayatNode *current = stack.top;
     while (current != NULL) {
         printf("%-5d %-20s %-30s\n", i, current->nama, current->judul_buku);
         current = current->next;
         i++;
     }
     printf("--------------------------------------------------\n");
 }