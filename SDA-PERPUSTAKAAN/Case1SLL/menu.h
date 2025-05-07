/*
 * File: menu.h
 * Deskripsi: Header file untuk fungsi-fungsi menu interaktif
 */

 #ifndef MENU_H
 #define MENU_H
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <stdbool.h>
 #include "buku.h"
 #include "anggota.h"
 #include "peminjaman.h"
 
 // Menampilkan menu utama
 void tampilMenuUtama();
 
 // Menu untuk manajemen buku
 void menuBuku(ListBuku *daftarBuku);
 
 // Menu untuk manajemen anggota
 void menuAnggota(ListAnggota *daftarAnggota);
 
 // Menu untuk manajemen peminjaman
 void menuPeminjaman(ListPeminjaman *daftarPeminjaman, ListBuku *daftarBuku, 
                     ListAnggota *daftarAnggota, StackPeminjaman *stackPeminjaman);
 
 // Menjalankan skenario pengujian sesuai studi kasus
 void runSkenarioPengujian(ListBuku *daftarBuku, ListAnggota *daftarAnggota, 
                          ListPeminjaman *daftarPeminjaman, StackPeminjaman *stackPeminjaman);
 
 #endif /* MENU_H */