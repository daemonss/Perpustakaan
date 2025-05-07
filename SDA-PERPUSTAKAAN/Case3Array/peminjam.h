/**
 * peminjam.h
 * Header file untuk ADT Queue Peminjam yang diimplementasikan dengan array
 * 
 * Queue ini merupakan priority queue dengan prioritas:
 * Dosen > Mahasiswa > Masyarakat Umum
 */

 #ifndef PEMINJAM_H
 #define PEMINJAM_H
 
 #include <stdbool.h>
 
 // Definisi konstanta
 #define MAX_NAMA 50
 #define MAX_PEMINJAM 100
 
 // Definisi tipe data untuk level prioritas
 typedef enum {
     UMUM = 0,       // Prioritas terendah
     MAHASISWA = 1,
     DOSEN = 2       // Prioritas tertinggi
 } LevelPrioritas;
 
 // Definisi tipe data untuk peminjam
 typedef struct {
     char nama[MAX_NAMA];     // Nama peminjam
     LevelPrioritas level;    // Level prioritas peminjam
 } Peminjam;
 
 // Definisi tipe data untuk queue peminjam
 typedef struct QueuePeminjam {
     Peminjam data[MAX_PEMINJAM];  // Array untuk menyimpan data peminjam
     int head;                     // Indeks head dari queue
     int tail;                     // Indeks tail dari queue
 } QueuePeminjam;
 
  //Inisialisasi Queue Peminjam
  //I.S. : QueuePeminjam sembarang
  //F.S. : Queue kosong dengan head = tail = -1

 void inisialisasiQueue(QueuePeminjam *queue);
 
  //Cek apakah queue kosong
   

 bool isQueueEmpty(QueuePeminjam queue);
 

  //Cek apakah queue penuh

 bool isQueueFull(QueuePeminjam queue);
 

  //Menambahkan peminjam ke dalam queue
  //I.S. : Queue terdefinisi, mungkin kosong
  //F.S. : Peminjam ditambahkan ke dalam queue

 bool tambahPeminjam(QueuePeminjam *queue, char *nama, LevelPrioritas level);
 
 
  //Mengambil peminjam dengan prioritas tertinggi dari queue
  //I.S. : Queue terdefinisi, tidak kosong
  //F.S. : Peminjam dengan prioritas tertinggi dikeluarkan dari queue

 bool ambilPeminjamTertinggi(QueuePeminjam *queue, Peminjam *peminjam);
 
 
  //Mendapatkan peminjam dengan prioritas tertinggi tanpa menghapusnya


 bool getPeminjamTertinggi(QueuePeminjam queue, Peminjam *peminjam);
 

  //Menghapus peminjam dari queue berdasarkan nama
  //I.S. : Queue terdefinisi, mungkin kosong
  //F.S. : Peminjam dengan nama tertentu dihapus dari queue jika ada
 
 bool hapusPeminjam(QueuePeminjam *queue, char *nama);
 

  //Menghitung jumlah peminjam dalam antrian
 
 int hitungJumlahAntrian(QueuePeminjam queue);
 

  //Menampilkan seluruh isi queue peminjam

 void tampilkanQueuePeminjam(QueuePeminjam queue);
 

  //Mendapatkan string representasi dari level prioritas

 const char* getLevelString(LevelPrioritas level);
 
 #endif /* PEMINJAM_H */