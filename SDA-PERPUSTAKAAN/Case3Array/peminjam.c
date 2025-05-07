/**
 * peminjam.c
 * Implementasi ADT Queue Peminjam (Priority Queue)
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include "peminjam.h"
 
 /**
  * Inisialisasi Queue Peminjam
  */
 void inisialisasiQueue(QueuePeminjam *queue) {
     queue->head = -1;
     queue->tail = -1;
 }
 
 /**
  * Cek apakah queue kosong
  */
 bool isQueueEmpty(QueuePeminjam queue) {
     return (queue.head == -1 && queue.tail == -1);
 }
 
 /**
  * Cek apakah queue penuh
  */
 bool isQueueFull(QueuePeminjam queue) {
     return (queue.tail + 1) % MAX_PEMINJAM == queue.head || 
            (queue.head == 0 && queue.tail == MAX_PEMINJAM - 1);
 }
 
 /**
  * Menambahkan peminjam ke dalam queue
  */
 bool tambahPeminjam(QueuePeminjam *queue, char *nama, LevelPrioritas level) {
    if (isQueueFull(*queue)) {
        printf("Antrian peminjam penuh, tidak dapat menambahkan peminjam baru.\n");
        return false;
    }

    // Buat peminjam baru
    Peminjam peminjamBaru;
    strncpy(peminjamBaru.nama, nama, MAX_NAMA - 1);
    peminjamBaru.nama[MAX_NAMA - 1] = '\0';
    peminjamBaru.level = level;

    // Jika queue kosong
    if (isQueueEmpty(*queue)) {
        queue->head = 0;
        queue->tail = 0;
        queue->data[0] = peminjamBaru;
        return true;
    }

    // Cari posisi berdasarkan prioritas (Dosen > Mahasiswa > Umum)
    int pos = queue->tail;
    while (pos >= queue->head && queue->data[pos].level < level) {
        queue->data[(pos + 1) % MAX_PEMINJAM] = queue->data[pos];
        pos--;
    }

    // Sisipkan di posisi yang benar
    pos = (pos + 1) % MAX_PEMINJAM;
    queue->data[pos] = peminjamBaru;
    queue->tail = (queue->tail + 1) % MAX_PEMINJAM;

    return true;
}
 
 /**
  * Mengambil peminjam dengan prioritas tertinggi dari queue
  */
 bool ambilPeminjamTertinggi(QueuePeminjam *queue, Peminjam *peminjam) {
     if (isQueueEmpty(*queue)) {
         return false;
     }
     
     // Salin data peminjam dengan prioritas tertinggi (head)
     *peminjam = queue->data[queue->head];
     
     // Jika hanya ada satu elemen dalam queue
     if (queue->head == queue->tail) {
         queue->head = -1;
         queue->tail = -1;
     } else {
         queue->head = (queue->head + 1) % MAX_PEMINJAM;
     }
     
     return true;
 }
 
 /**
  * Mendapatkan peminjam dengan prioritas tertinggi tanpa menghapusnya
  */
 bool getPeminjamTertinggi(QueuePeminjam queue, Peminjam *peminjam) {
     if (isQueueEmpty(queue)) {
         return false;
     }
     
     // Salin data peminjam dengan prioritas tertinggi (head)
     *peminjam = queue.data[queue.head];
     return true;
 }
 
 /**
  * Menghapus peminjam dari queue berdasarkan nama
  */
 bool hapusPeminjam(QueuePeminjam *queue, char *nama) {
     if (isQueueEmpty(*queue)) {
         return false;
     }
     
     int current = queue->head;
     int found = -1;
     
     // Cari peminjam dengan nama yang sesuai
     while (current != (queue->tail + 1) % MAX_PEMINJAM) {
         if (strcmp(queue->data[current].nama, nama) == 0) {
             found = current;
             break;
         }
         current = (current + 1) % MAX_PEMINJAM;
     }
     
     // Jika tidak ditemukan
     if (found == -1) {
         return false;
     }
     
     // Geser elemen-elemen setelah peminjam yang dihapus
     current = found;
     int next = (current + 1) % MAX_PEMINJAM;
     
     while (next != (queue->tail + 1) % MAX_PEMINJAM) {
         queue->data[current] = queue->data[next];
         current = next;
         next = (next + 1) % MAX_PEMINJAM;
     }
     
     // Update tail
     if (queue->head == queue->tail) {
         // Jika hanya ada satu elemen
         queue->head = -1;
         queue->tail = -1;
     } else {
         queue->tail = (queue->tail - 1 + MAX_PEMINJAM) % MAX_PEMINJAM;
     }
     
     return true;
 }
 
 /**
  * Menghitung jumlah peminjam dalam antrian
  */
 int hitungJumlahAntrian(QueuePeminjam queue) {
     if (isQueueEmpty(queue)) {
         return 0;
     }
     
     if (queue.tail >= queue.head) {
         return queue.tail - queue.head + 1;
     } else {
         return MAX_PEMINJAM - queue.head + queue.tail + 1;
     }
 }
 
 /**
  * Menampilkan seluruh isi queue peminjam
  */
 void tampilkanQueuePeminjam(QueuePeminjam queue) {
     if (isQueueEmpty(queue)) {
         printf("Antrian peminjam kosong.\n");
         return;
     }
     
     printf("\n===== ANTRIAN PEMINJAM =====\n");
     printf("| %-5s | %-20s | %-15s |\n", "No", "Nama", "Level");
     printf("|-------|----------------------|---------------|\n");
     
     int i = 1;
     int current = queue.head;
     
     while (current != (queue.tail + 1) % MAX_PEMINJAM) {
         printf("| %-5d | %-20s | %-15s |\n", i, queue.data[current].nama, 
                getLevelString(queue.data[current].level));
         current = (current + 1) % MAX_PEMINJAM;
         i++;
     }
     
     printf("===========================\n");
 }
 
 /**
  * Mendapatkan string representasi dari level prioritas
  */
 const char* getLevelString(LevelPrioritas level) {
     switch (level) {
         case DOSEN:
             return "Dosen";
         case MAHASISWA:
             return "Mahasiswa";
         case UMUM:
             return "Masyarakat Umum";
         default:
             return "Tidak dikenal";
     }
 }