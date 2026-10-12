import java.util.*;

public class Latihan1 {

    public static class Kasir {
        private String barang;
        private int harga;
        private int satuan;

        public Kasir(int harga, String barang, int satuan) {
          this.harga = harga;
          this.barang = barang;
          this.satuan = satuan;
        }

        public void GetHarga(int harga) {
            this.harga = harga;
        }

        public void GetBarang(String barang) {
            this.barang = barang;
        }

        public void GetSatuan(int satuan) {
            this.satuan = satuan;
        }

        public int HitungBarang() {
            return harga * satuan;
        }

        public void Cetak() {
            System.out.println("Simulasi Kasir");
            System.out.println("Nama Barang = " + barang);
            System.out.println("Harga Satuan = " + harga);
            System.out.println("Jumlah = " + satuan);
            System.out.println("Subtotal(" + satuan + "x) : " + HitungBarang());
        }
    }

    public static void main(String[] args) {
        Scanner myObj = new Scanner(System.in);
      
        System.out.print("Masukkan nama barang: ");
        String barang = myObj.nextLine();

        System.out.print("Masukkan harga satuan: ");
        int harga = myObj.nextInt();

        System.out.print("Masukkan jumlah barang: ");
        int satuan = myObj.nextInt();

        Kasir Indomaret = new Kasir(harga, barang, satuan);

        System.out.println();

        Indomaret.Cetak();
    }
}