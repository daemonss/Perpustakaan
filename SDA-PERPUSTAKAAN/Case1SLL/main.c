/*
 * File: main.c
 * Deskripsi: Program driver untuk sistem perpustakaan
 * Menggunakan implementasi ADT dengan Singly Linked List
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include "menu.h"
 
 int main() {
     int pilihan;
     
     // Inisialisasi daftar buku
     ListBuku daftarBuku;
     createListBuku(&daftarBuku);
     
     // Inisialisasi daftar anggota
     ListAnggota daftarAnggota;
     createListAnggota(&daftarAnggota);
     
     // Inisialisasi daftar peminjaman
     ListPeminjaman daftarPeminjaman;
     createListPeminjaman(&daftarPeminjaman);
     
     // Inisialisasi stack peminjaman untuk fitur undo
     StackPeminjaman stackPeminjaman;
     createStackPeminjaman(&stackPeminjaman);
     
     printf("===================================================\n");
     printf("|   SISTEM MANAJEMEN PERPUSTAKAAN POLBAN JTK      |\n");
     printf("===================================================\n");
     
     do {
         tampilMenuUtama();
         scanf("%d", &pilihan);
         getchar(); // Membersihkan newline
         
         switch (pilihan) {
             case 1:
                 menuBuku(&daftarBuku);
                 break;
             case 2:
                 menuAnggota(&daftarAnggota);
                 break;
             case 3:
                 menuPeminjaman(&daftarPeminjaman, &daftarBuku, &daftarAnggota, &stackPeminjaman);
                 break;
             case 4:
                 runSkenarioPengujian(&daftarBuku, &daftarAnggota, &daftarPeminjaman, &stackPeminjaman);
                 break;
             case 0:
                 printf("Terima kasih. Program selesai.\n");
                 break;
             default:
                 printf("Pilihan tidak valid!\n");
         }
     } while (pilihan != 0);
     
     // Membersihkan memori
     deleteListBuku(&daftarBuku);
     deleteListAnggota(&daftarAnggota);
     deleteListPeminjaman(&daftarPeminjaman);
     
     return 0;
 }