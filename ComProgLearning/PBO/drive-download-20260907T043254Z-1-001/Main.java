import java.util.Scanner;

public class Main {
    private static final Scanner sc = new Scanner(System.in);

    public static Keranjang prepartion() {
        Produk p1 = new Produk("Laptop", 8500000);
        Produk p2 = new Produk("Mouse", 150000);
        Produk p3 = new Produk("Keyboard", 350000);
        Produk p4 = new Produk("Monitor", 2200000);
        Produk p5 = new Produk("Headset", 450000);
        Produk p6 = new Produk("Webcam", 600000);
        Produk p7 = new Produk("Flashdisk", 100000);
        Produk p8 = new Produk("Hard Disk", 1200000);

        Item[] daftarItem = new Item[4];
        daftarItem[0] = new Item(p1, 1);
        daftarItem[1] = new Item(p2, 2);
        daftarItem[2] = new Item(p3, 1);
        daftarItem[3] = new Item(p5, 3);

        return new Keranjang(daftarItem);
    }

    public static void handlePembayaranTunai(double amount) {
        Payment pembayaranTunai = new Payment();
        pembayaranTunai.prosesPembayaran(amount);
        pembayaranTunai.informasiPembayaran();
    }

    public static void handlePembayaranEWallet(double amount) {
        System.out.println("\n========= Informasi Dompet =========");
        System.out.print("Nomor telepon: ");
        String nomorTelepon = sc.nextLine();
        System.out.print("Sisa saldo: ");
        double sisaSaldo = Double.parseDouble(sc.nextLine());

        // TODO: Buat objek untuk pembayaran EWallet lalu panggil method untuk proses bayar

    }

    public static void handlePembayaranKartuKredit(double amount) {
        System.out.println("\n========= Informasi Kartu Kredit =========");
        System.out.print("Nomor kartu: ");
        String nomorKartu = sc.nextLine();
        System.out.print("CVV: ");
        String cvv = sc.nextLine();
        System.out.print("Limit kredit: ");
        double limitKredit = Double.parseDouble(sc.nextLine());

        // TODO: Buat objek untuk pembayaran Kartu Kredit lalu panggil method untuk proses bayar

    }

    public static void main(String[] args) {
        Keranjang keranjangBelanja = prepartion();
        double amount = keranjangBelanja.getTotal();

        System.out.println("======================================");
        System.out.printf("Tagihan belanja: Rp%,.0f%n", amount);
        System.out.println("======================================");

        System.out.println("\n========= Opsi Bayar =========");
        System.out.println("1. Pembayaran Tunai");
        System.out.println("2. E-Wallet");
        System.out.println("3. Kartu Kredit");
        System.out.println("0. Keluar");
        System.out.print("Metode yang dipilih: ");
        int opsi = Integer.parseInt(sc.nextLine());

        if (opsi != 1 && opsi != 2 && opsi != 3) {
            return;
        }

        if (opsi == 1) handlePembayaranTunai(amount);
        if (opsi == 2) handlePembayaranEWallet(amount);
        if (opsi == 3) handlePembayaranKartuKredit(amount);
    }
}
