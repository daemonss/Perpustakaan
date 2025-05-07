/**
 * File: menu.h
 * Deskripsi: Header untuk pengelolaan menu interaktif
 * Berisi deklarasi fungsi-fungsi untuk navigasi menu sistem perpustakaan
 */

#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "buku.h"
#include "peminjam.h"

// Deklarasi variabel global untuk data buku dan peminjam
extern ListBuku daftarBuku;
extern ListPeminjam daftarPeminjam;
extern StackRiwayat riwayatAktivitas;

// Deklarasi fungsi-fungsi untuk menu utama
void clearScreen();
void tampilkanMenuUtama();
void prosesMenuUtama();

// Deklarasi fungsi-fungsi untuk menu manajemen buku
void tampilkanMenuBuku();
void prosesMenuBuku();
void tambahBuku();
void tampilkanDaftarBuku();

// Deklarasi fungsi-fungsi untuk menu manajemen anggota
void tampilkanMenuAnggota();
void prosesMenuAnggota();
void tambahAnggotaKeBuku();
void tampilkanAntrianPeminjamBuku();

// Deklarasi fungsi-fungsi untuk menu manajemen peminjaman
void tampilkanMenuPeminjaman();
void prosesMenuPeminjaman();
void prosesPeminjamanBuku();
void pengembalianBuku();
void pembatalanPeminjaman();

// Deklarasi fungsi untuk skenario pengujian
void jalankanSkenarioPengujian();

// Fungsi utilitas
void pause();
void visualisasiStrukturData();

#endif // MENU_H