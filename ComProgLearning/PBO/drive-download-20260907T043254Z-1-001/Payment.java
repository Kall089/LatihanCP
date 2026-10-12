import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;

// TODO: Buat class Payment agar memiliki dua atribut jumlahDibayar (double) dan waktuPembayaran (LocalDateTime)
//  Gunakan access modifier yang sesuai
public class Payment {

    protected double jumlahDibayar;
    protected LocalDateTime waktuPembayaran;
    // TODO: Buat constructor kosong

    public Payment() {

    }

    // TODO: Buat method prosesPembayaran
    //  1. Menerima satu parameter, amount dengan tipe double
    //  2. Set properti jumlahDibayar dengan penambahan PPN 11%
    //  3. Panggil method informasiPembayaran
    //  4. Set propert waktuPembayaran dengan LocalDateTime.now()

    public void prosesPembayaran(double amount) {
        this.jumlahDibayar = amount * 111 / 100;
        this.waktuPembayaran = LocalDateTime.now();
        informasiPembayaran();
    }

    // ! DON'T MODIFY
    public void informasiPembayaran() {
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd MMM yyyy, HH:mm");
        System.out.printf("Telah dibayar sejumlah Rp%,.0f pada %s\n", jumlahDibayar, waktuPembayaran.format(formatter));
    }
    // ! DON'T MODIFY

    // TODO: Implementasi getter dan setter
    public double getJumlahDibayar() {
        return jumlahDibayar;
    }

    public void setJumlahDibayar(double jumlahDibayar) {
        this.jumlahDibayar = jumlahDibayar;
    }

    public LocalDateTime getWaktuPembayaran() {
        return waktuPembayaran;
    }

    public void setWaktuPembayaran(LocalDateTime waktuPembayaran) {
        this.waktuPembayaran = waktuPembayaran;
    }
}
