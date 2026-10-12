//  Tambahkan empat properti baru, dengan tipe data yang sesuai
//  Properti tambahan: nomorKartu, cvv, limitKredit, persentaseBiayaLayanan
public class KartuKreditPayment extends Payment {

    private int nomorKartu;
    private int cvv;
    private double limitKredit;
    private double persentaseBiayaLayanan;
    // TODO: Buat dua constructor, default constructor dan parameterized
    //  constructor yang menerima tiga parameter. Properti persentaseBiayaLayanan
    //  di-set di dalam construct or langsung.
    
    public KartuKreditPayment() {

    }

    public KartuKreditPayment(int nomorKartu, int cvv, double limitKredit, double persentaseBiayaLayanan) {
        this.nomorKartu = nomorKartu;
        this.cvv = cvv;
        this.limitKredit = limitKredit;
        this.persentaseBiayaLayanan = persentaseBiayaLayanan;
    }


    // TODO: Override method prosesPembayaran
    //  1. Jika nilai amount lebih dari limit kredit, tidak bisa melakukan pembayaran
    //  2. Set properti jumlahDibayar dengan penambahan PPN 11% dan persentaseBiayaLayanan
    //  3. Panggil method informasiPembayaran

    @Override
    public void prosesPembayaran(double amount) {
        // TODO Auto-generated method stub
        jumlahDibayar = amount * 111 / 100 + persentaseBiayaLayanan;
        super.prosesPembayaran(amount);
    }


    // TODO: Implementasi getter dan setter
}
