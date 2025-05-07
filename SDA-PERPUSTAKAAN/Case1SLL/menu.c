/*
 * File: menu.c
 * Deskripsi: Implementasi fungsi-fungsi menu interaktif
 */

 #include "menu.h"

 // Menampilkan menu utama
 void tampilMenuUtama() {
     printf("\n===========================================\n");
     printf("|        PERPUSTAKAAN POLBAN JTK          |\n");
     printf("===========================================\n");
     printf("| 1. Manajemen Buku                       |\n");
     printf("| 2. Manajemen Anggota                    |\n");
     printf("| 3. Manajemen Peminjaman                 |\n");
     printf("| 4. Jalankan Skenario Pengujian          |\n");
     printf("| 0. Keluar                               |\n");
     printf("===========================================\n");
     printf("Pilihan: ");
 }
 
 // Menu untuk manajemen buku
 void menuBuku(ListBuku *daftarBuku) {
     int pilihan;
     char judul[100];
     int stok;
     
     do {
         printf("\n===========================================\n");
         printf("|            MANAJEMEN BUKU              |\n");
         printf("===========================================\n");
         printf("| 1. Tambah Buku                         |\n");
         printf("| 2. Hapus Buku                          |\n");
         printf("| 3. Ubah Stok Buku                      |\n");
         printf("| 4. Tampilkan Daftar Buku               |\n");
         printf("| 0. Kembali                             |\n");
         printf("===========================================\n");
         printf("Pilihan: ");
         scanf("%d", &pilihan);
         getchar(); // Konsumsi karakter newline
         
         switch (pilihan) {
             case 1:
                 printf("\nTambah Buku\n");
                 printf("Judul: ");
                 fgets(judul, sizeof(judul), stdin);
                 judul[strcspn(judul, "\n")] = 0; // Hapus newline
                 
                 printf("Stok: ");
                 scanf("%d", &stok);
                 getchar(); // Konsumsi karakter newline
                 
                 insertBuku(daftarBuku, judul, stok);
                 break;
                 
             case 2:
                 printf("\nHapus Buku\n");
                 printf("Judul: ");
                 fgets(judul, sizeof(judul), stdin);
                 judul[strcspn(judul, "\n")] = 0; // Hapus newline
                 
                 deleteBuku(daftarBuku, judul);
                 break;
                 
             case 3:
                 printf("\nUbah Stok Buku\n");
                 printf("Judul: ");
                 fgets(judul, sizeof(judul), stdin);
                 judul[strcspn(judul, "\n")] = 0; // Hapus newline
                 
                 printf("Stok Baru: ");
                 scanf("%d", &stok);
                 getchar(); // Konsumsi karakter newline
                 
                 updateStokBuku(daftarBuku, judul, stok);
                 break;
                 
             case 4:
                 displayListBuku(*daftarBuku);
                 break;
                 
             case 0:
                 break;
                 
             default:
                 printf("Pilihan tidak valid\n");
         }
     } while (pilihan != 0);
 }
 
 // Menu untuk manajemen anggota
 void menuAnggota(ListAnggota *daftarAnggota) {
     int pilihan;
     char nama[100];
     int prioritas;
     
     do {
         printf("\n===========================================\n");
         printf("|           MANAJEMEN ANGGOTA            |\n");
         printf("===========================================\n");
         printf("| 1. Tambah Anggota                      |\n");
         printf("| 2. Hapus Anggota                       |\n");
         printf("| 3. Tampilkan Daftar Anggota            |\n");
         printf("| 0. Kembali                             |\n");
         printf("===========================================\n");
         printf("Pilihan: ");
         scanf("%d", &pilihan);
         getchar(); // Konsumsi karakter newline
         
         switch (pilihan) {
             case 1:
                 printf("\nTambah Anggota\n");
                 printf("Nama: ");
                 fgets(nama, sizeof(nama), stdin);
                 nama[strcspn(nama, "\n")] = 0; // Hapus newline
                 
                 printf("Prioritas (1=Masyarakat Umum, 2=Mahasiswa, 3=Dosen): ");
                 scanf("%d", &prioritas);
                 getchar(); // Konsumsi karakter newline
                 
                 if (prioritas >= 1 && prioritas <= 3) {
                     insertAnggota(daftarAnggota, nama, (TipePrioritas)prioritas);
                 } else {
                     printf("Prioritas tidak valid\n");
                 }
                 break;
                 
             case 2:
                 printf("\nHapus Anggota\n");
                 printf("Nama: ");
                 fgets(nama, sizeof(nama), stdin);
                 nama[strcspn(nama, "\n")] = 0; // Hapus newline
                 
                 deleteAnggota(daftarAnggota, nama);
                 break;
                 
             case 3:
                 displayListAnggota(*daftarAnggota);
                 break;
                 
             case 0:
                 break;
                 
             default:
                 printf("Pilihan tidak valid\n");
         }
     } while (pilihan != 0);
 }
 
 // Menu untuk manajemen peminjaman
 void menuPeminjaman(ListPeminjaman *daftarPeminjaman, ListBuku *daftarBuku, 
                     ListAnggota *daftarAnggota, StackPeminjaman *stackPeminjaman) {
     int pilihan;
     char judulBuku[100];
     char namaAnggota[100];
     addressAnggota anggota;
     
     do {
         printf("\n===========================================\n");
         printf("|         MANAJEMEN PEMINJAMAN           |\n");
         printf("===========================================\n");
         printf("| 1. Tambah Antrian Peminjaman           |\n");
         printf("| 2. Proses Peminjaman                   |\n");
         printf("| 3. Proses Pengembalian                 |\n");
         printf("| 4. Batalkan Peminjaman                 |\n");
         printf("| 5. Tampilkan Daftar Peminjaman         |\n");
         printf("| 6. Tampilkan Antrian Peminjaman        |\n");
         printf("| 0. Kembali                             |\n");
         printf("===========================================\n");
         printf("Pilihan: ");
         scanf("%d", &pilihan);
         getchar(); // Konsumsi karakter newline
         
         switch (pilihan) {
             case 1:
                 printf("\nTambah Antrian Peminjaman\n");
                 printf("Judul Buku: ");
                 fgets(judulBuku, sizeof(judulBuku), stdin);
                 judulBuku[strcspn(judulBuku, "\n")] = 0; // Hapus newline
                 
                 printf("Nama Anggota: ");
                 fgets(namaAnggota, sizeof(namaAnggota), stdin);
                 namaAnggota[strcspn(namaAnggota, "\n")] = 0; // Hapus newline
                 
                 // Cek apakah anggota terdaftar
                 anggota = findAnggota(*daftarAnggota, namaAnggota);
                 if (anggota != NULL) {
                     insertPeminjaman(daftarPeminjaman, judulBuku, namaAnggota, 
                                     anggota->info.prioritas, daftarBuku, stackPeminjaman);
                 } else {
                     printf("Anggota '%s' tidak terdaftar\n", namaAnggota);
                 }
                 break;
                 
             case 2:
                 printf("\nProses Peminjaman\n");
                 printf("Judul Buku: ");
                 fgets(judulBuku, sizeof(judulBuku), stdin);
                 judulBuku[strcspn(judulBuku, "\n")] = 0; // Hapus newline
                 
                 prosesPeminjaman(daftarPeminjaman, judulBuku, daftarBuku);
                 break;
                 
             case 3:
                 printf("\nProses Pengembalian\n");
                 printf("Judul Buku: ");
                 fgets(judulBuku, sizeof(judulBuku), stdin);
                 judulBuku[strcspn(judulBuku, "\n")] = 0; // Hapus newline
                 
                 printf("Nama Anggota: ");
                 fgets(namaAnggota, sizeof(namaAnggota), stdin);
                 namaAnggota[strcspn(namaAnggota, "\n")] = 0; // Hapus newline
                 
                 prosesKembali(daftarPeminjaman, judulBuku, namaAnggota, daftarBuku);
                 break;
                 
             case 4:
                 printf("\nBatalkan Peminjaman\n");
                 printf("Nama Anggota: ");
                 fgets(namaAnggota, sizeof(namaAnggota), stdin);
                 namaAnggota[strcspn(namaAnggota, "\n")] = 0; // Hapus newline
                 
                 batalkanPeminjaman(daftarPeminjaman, namaAnggota, daftarBuku, stackPeminjaman);
                 break;
                 
             case 5:
                 displayListPeminjaman(*daftarPeminjaman);
                 break;
                 
             case 6:
                 printf("\nTampilkan Antrian Peminjaman\n");
                 printf("Judul Buku: ");
                 fgets(judulBuku, sizeof(judulBuku), stdin);
                 judulBuku[strcspn(judulBuku, "\n")] = 0; // Hapus newline
                 
                 displayAntrianPeminjaman(*daftarPeminjaman, judulBuku);
                 break;
                 
             case 0:
                 break;
                 
             default:
                 printf("Pilihan tidak valid\n");
         }
     } while (pilihan != 0);
 }
 
 // Menjalankan skenario pengujian sesuai studi kasus
 void runSkenarioPengujian(ListBuku *daftarBuku, ListAnggota *daftarAnggota, 
                          ListPeminjaman *daftarPeminjaman, StackPeminjaman *stackPeminjaman) {
     printf("\n=================================================================\n");
     printf("|                    SKENARIO PENGUJIAN                          |\n");
     printf("=================================================================\n");
     
     // 1. Insert 2 buku
     printf("\nSkenario a) 2 X insert elemen \"Buku1\" dan \"Buku2\" di list Buku dimana stok buku masing masing 1\n");
     insertBuku(daftarBuku, "Buku1", 1);
     insertBuku(daftarBuku, "Buku2", 1);
     displayListBuku(*daftarBuku);
     
     // 2. Insert anggota
     printf("\nSkenario b) 1 X insert elemen \"Anggota1\" sebagai mahasiswa di list peminjaman \"Buku1\"\n");
     insertAnggota(daftarAnggota, "Anggota1", MAHASISWA);
     insertPeminjaman(daftarPeminjaman, "Buku1", "Anggota1", MAHASISWA, daftarBuku, stackPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     printf("\nSkenario c) 1 X insert elemen \"Dosen1\" sebagai dosen di list peminjaman \"Buku1\"\n");
     insertAnggota(daftarAnggota, "Dosen1", DOSEN);
     insertPeminjaman(daftarPeminjaman, "Buku1", "Dosen1", DOSEN, daftarBuku, stackPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     printf("\nSkenario d) 1 X insert elemen \"Umum1\" sebagai masyarakat umum di list peminjaman \"Buku1\"\n");
     insertAnggota(daftarAnggota, "Umum1", MASYARAKAT_UMUM);
     insertPeminjaman(daftarPeminjaman, "Buku1", "Umum1", MASYARAKAT_UMUM, daftarBuku, stackPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     printf("\nSkenario e) 1 X insert elemen \"Umum1\" sebagai masyarakat umum di list peminjaman \"Buku2\"\n");
     insertPeminjaman(daftarPeminjaman, "Buku2", "Umum1", MASYARAKAT_UMUM, daftarBuku, stackPeminjaman);
     
     displayListPeminjaman(*daftarPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     // 3. Proses peminjaman
     printf("\nSkenario f) Proses peminjaman \"Buku1\". Pastikan \"Dosen1\" yang mendapatkan proses peminjaman.\n");
     prosesPeminjaman(daftarPeminjaman, "Buku1", daftarBuku);
     displayListPeminjaman(*daftarPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     // 4. Proses pengembalian
     printf("\nSkenario g) Proses pengembalian \"Buku1\" oleh \"Dosen1\". Pastikan potensi selanjutnya yang akan mendapatkan fasilitas peminjaman adalah \"Anggota1\" di list peminjaman \"Buku1\".\n");
     prosesKembali(daftarPeminjaman, "Buku1", "Dosen1", daftarBuku);
     displayListPeminjaman(*daftarPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     // 5. Pembatalan peminjaman
     printf("\nSkenario h) Elemen \"Umum1\" melakukan pembatalan aktivitas peminjaman buku (berdasarkan aktivitas terakhir, pembatalan terjadi untuk list peminjaman \"Buku2\").\n");
     batalkanPeminjaman(daftarPeminjaman, "Umum1", daftarBuku, stackPeminjaman);
     displayListPeminjaman(*daftarPeminjaman);
     //displayVisualisasiAntrian(*daftarPeminjaman);
     
     printf("\n=================================================================\n");
     printf("                     SKENARIO PENGUJIAN SELESAI                    \n");
     printf("==================================================================\n\n");
 }