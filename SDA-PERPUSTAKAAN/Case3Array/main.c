/**
 * main.c
 * Program utama (driver) untuk sistem perpustakaan perguruan tinggi
 * 
 * Program ini mengimplementasikan studi kasus perpustakaan dengan prioritas peminjam:
 * Dosen > Mahasiswa > Masyarakat Umum
 * 
 * Implementasi menggunakan struktur data array dan pointer
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "menu.h"
 #include "buku.h"
 
 int main() {
     DaftarBuku daftarBuku;
     int pilihan;
     bool lanjut = true;
     
     // Inisialisasi daftar buku
     inisialisasiDaftarBuku(&daftarBuku);
     
     printf("Selamat datang di Sistem Perpustakaan Perguruan Tinggi\n");
     
     // Loop menu utama
     while (lanjut) {
         tampilkanMenu();
         scanf("%d", &pilihan);
         lanjut = prosesMenu(pilihan, &daftarBuku);
     }
     
     // Bebaskan memori untuk setiap queue peminjam sebelum program berakhir
     for (int i = 0; i < daftarBuku.jumlah; i++) {
         if (daftarBuku.data[i].queuePeminjam != NULL) {
             free(daftarBuku.data[i].queuePeminjam);
         }
     }
     
     return 0;
 }