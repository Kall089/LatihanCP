import java.util.Scanner;

public class Latihan2 {

    public static class Product {

        private String namaProduk;
        private String kategori;
        private int harga;
        private int stokAwal;

        public Product(String namaProduk, String kategori, int harga, int stokAwal) {
            this.namaProduk = namaProduk;
            this.kategori = kategori;
            this.harga = harga;
            this.stokAwal = stokAwal;
        }

        public int getHarga() {
            return harga;
        }

        public String getKategori() {
            return kategori;
        }

        public String getNamaProduk() {
            return namaProduk;
        }

        public int getStokAwal() {
            return stokAwal;
        }

        public void setHarga(int harga) {
            this.harga = harga;
        }

        public void setKategori(String kategori) {
            this.kategori = kategori;
        }

        public void setNamaProduk(String namaProduk) {
            this.namaProduk = namaProduk;
        }

        public void setStokAwal(int stokAwal) {
            this.stokAwal = stokAwal;
        }

        public void cetak() {
            System.out.println("Nama Produk : " + namaProduk);
            System.out.println("Kategori    : " + kategori);
            System.out.println("Harga       : Rp" + harga);
            System.out.println("Stok Awal   : " + stokAwal);
            System.out.println("-----------------------------");
        }
    }

    public static void main(String[] args) {

        Scanner input = new Scanner(System.in);

        Product[] daftarProduk = new Product[3];
        int jumlahProduk = 0;
        int menu;

        do {
            System.out.println("\n=== SISTEM MANAJEMEN TOKO ===");
            System.out.println("1. Tambah Produk");
            System.out.println("2. Tampilkan Produk");
            System.out.println("3. Keluar");
            System.out.print("Pilih Menu: ");

            menu = input.nextInt();
            input.nextLine();

            System.out.println("-----------------------------");

            switch (menu) {

                case 1:
                    if (jumlahProduk >= daftarProduk.length) {
                        System.out.println("Produk sudah penuh!");
                        break;
                    }

                    System.out.println("Masukkan Data Produk:");

                    System.out.print("Nama Produk: ");
                    String namaProduk = input.nextLine();

                    System.out.print("Kategori: ");
                    String kategori = input.nextLine();

                    System.out.print("Harga: ");
                    int harga = input.nextInt();

                    System.out.print("Stok Awal: ");
                    int stokAwal = input.nextInt();

                    input.nextLine();

                    Product produkBaru = new Product(namaProduk, kategori, harga, stokAwal);
                    daftarProduk[jumlahProduk] = produkBaru;
                    jumlahProduk++;

                    System.out.println("Produk berhasil ditambahkan!");
                    break;
                case 2:

                    System.out.println("=== LIST PRODUK ===");
                    if (jumlahProduk == 0) {
                        System.out.println("Belum ada produk.");
                    } else {
                        for (int i = 0; i < jumlahProduk; i++) {
                            System.out.println("Produk ke-" + (i + 1));
                            daftarProduk[i].cetak();
                        }
                    }
                    break;

                case 3:
                    System.out.println("Program selesai.");
                    break;
                default:
                    System.out.println("Menu tidak tersedia.");
            }

        } while (menu != 3);
    }
}