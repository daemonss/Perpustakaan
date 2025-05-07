#include "menu.h"

int main() {
    // Inisialisasi data
    createEmptyBuku(&daftarBuku);
    createEmptyPeminjam(&daftarPeminjam);
    createEmptyStack(&riwayatAktivitas);
    
    // Jalankan menu utama
    prosesMenuUtama();
    
    return 0;
}