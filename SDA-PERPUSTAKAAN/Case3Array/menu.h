/**
 * menu.h
 * Header file untuk manajemen menu sistem perpustakaan
 */

 #ifndef MENU_H
 #define MENU_H
 
 #include "buku.h"
 
 /**
  * Menampilkan menu utama sistem perpustakaan
  */
 void tampilkanMenu();
 

  //Menjalankan menu berdasarkan pilihan pengguna

 bool prosesMenu(int pilihan, DaftarBuku *daftar);
 
 
  //Submenu untuk menambahkan buku baru
 void menuTambahBuku(DaftarBuku *daftar);
 

  //Submenu untuk menambahkan peminjam ke buku tertentu

 void menuTambahPeminjam(DaftarBuku *daftar);
 
 
  //Submenu untuk melakukan proses peminjaman buku
 
 void menuProsesPeminjaman(DaftarBuku *daftar);
 

  //Submenu untuk melakukan proses pengembalian buku

 void menuPengembalianBuku(DaftarBuku *daftar);
 

  //Submenu untuk membatalkan permintaan peminjaman

 void menuBatalkanPeminjaman(DaftarBuku *daftar);
 

  //Submenu untuk menampilkan seluruh daftar buku dan antrian peminjamnya

 void menuTampilkanDataPerpustakaan(DaftarBuku *daftar);
 

  //Menjalankan skenario pengujian sesuai studi kasus

 void jalankanSkenarioPengujian(DaftarBuku *daftar);
 
 #endif /* MENU_H */