

//  Tambahkan dua properti baru, dengan tipe data yang sesuai
//  Properti tambahan: nomorTelepon, saldo
public class EWalletPayment extends Payment {

    private int nomorTelepon;
    private double saldo;
    // TODO: Buat dua constructor, default constructor dan parameterized
    //  constructor yang menerima dua parameter. Setiap properti dapat nilai dari
    //  constructornya langsung

    public EWalletPayment() {

    }

    public EWalletPayment(int nomorTelepon, double saldo) {
        this.nomorTelepon = nomorTelepon;
        this.saldo = saldo;
    }

    // TODO: Override method prosesPembayaran
    //  1. Jika nilai amount lebih dari saldo, tidak bisa melakukan pembayaran
    //  2. Set properti jumlahDibayar de    ngan penambahan PPN 11% dan tambahan biaya, besaran dibebaskan
    //  3. Panggil method informasiPembayaran

    @Override
    public void prosesPembayaran(double amount) {
        // TODO Auto-generated method stub
        jumlahDibayar = amount * 111 / 100 + 500;
        if (jumlahDibayar > saldo) {
            System.out.println("SALDO TIDAK CUKUP");
            return;
        }
        super.informasiPembayaran();
    }

    // TODO: Implementasi getter dan setter
    public double getJumlahDibayar() {
        return jumlahDibayar;
    }

    public void setJumlahDibayar(double jumlahDibayar) {
        this.jumlahDibayar = jumlahDibayar;
    }

    public int getNomorTelepon() {
        return nomorTelepon;
    }

    public void setNomorTelepon(int nomorTelepon) {
        this.nomorTelepon = nomorTelepon;
    }
    
    
}
