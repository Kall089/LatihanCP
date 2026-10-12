# 01 — Tipe primitif dan wrapper

[← README](README.md) · [Lanjut 02 String & array →](02-string-array.md)

Java membedakan **tipe primitif** (nilai mentah di stack/register) dan **wrapper** (objek di heap). Primitif tidak bisa `null`. Wrapper bisa `null`, masuk ke collections, dan punya method.

Delapan primitif: `byte`, `short`, `int`, `long`, `float`, `double`, `char`, `boolean`. Delapan wrapper: `Byte`, `Short`, `Integer`, `Long`, `Float`, `Double`, `Character`, `Boolean`.

## Daftar isi

- [Variabel dan tipe](#variabel-dan-tipe)
- [final](#final)
- [var](#var)
- [Literal angka](#literal-angka)
- [byte](#byte)
- [short](#short)
- [int](#int)
- [long](#long)
- [float](#float)
- [double](#double)
- [char](#char)
- [boolean](#boolean)
- [Nilai default field](#nilai-default-field)
- [Overflow](#overflow)
- [Widening](#widening)
- [Narrowing](#narrowing)
- [Pembagian int](#pembagian-int)
- [NaN dan Infinity](#nan-dan-infinity)
- [Byte](#byte-wrapper)
- [Short](#short-wrapper)
- [Integer](#integer)
- [Integer.parseInt](#integerparseint)
- [Integer.valueOf](#integervalueof)
- [Integer.toString](#integertostring)
- [Integer.compare](#integercompare)
- [Integer.MAX_VALUE](#integermax_value)
- [Long (wrapper)](#long-wrapper)
- [Float (wrapper)](#float-wrapper)
- [Double](#double-wrapper)
- [Double.parseDouble](#doubleparsedouble)
- [Character](#character)
- [Boolean](#boolean-wrapper)
- [Boolean.parseBoolean](#booleanparseboolean)
- [Autoboxing](#autoboxing)
- [Unboxing](#unboxing)
- [== versus equals pada wrapper](#-versus-equals-pada-wrapper)
- [Cache Integer](#cache-integer)
- [null pada wrapper](#null-pada-wrapper)
- [BigDecimal (uang)](#bigdecimal-uang)
- [Operator aritmetika](#operator-aritmetika)
- [Operator perbandingan](#operator-perbandingan)
- [Tabel cepat primitif](#tabel-cepat-primitif)

---

### Variabel dan tipe

**Tipe:** sintaks deklarasi

**Untuk apa:** menamai tempat penyimpanan dan mengunci jenis datanya. Java **statically typed**: tipe dicek saat `javac`, bukan ditebak saat jalan.

**Contoh implementasi:**

```java
public class VariabelDanTipe {
    public static void main(String[] args) {
        int hargaBuku = 45000;
        String namaBuku = "Pemrograman Java";
        boolean readyStock = true;
        hargaBuku = 50000;
        System.out.println(namaBuku + " Rp" + hargaBuku + " ready=" + readyStock);
        // hargaBuku = "mahal"; // error kompilasi: incompatible types
    }
}
```

**Yang terjadi:** `hargaBuku` hanya boleh menampung `int`. Mengganti nilainya ke `50000` sah. Mengisi string ditolak `javac`. Output: `Pemrograman Java Rp50000 ready=true`.

**Biasanya digabungkan dengan:** `final` jika tidak akan diganti, dan nama yang menjelaskan peran (`hargaBuku`, bukan `x`).

**Jangan:** memakai satu variabel `Object` untuk semua data “agar fleksibel”. Itu membuang manfaat tipe. Jangan mendeklarasikan variabel tanpa inisialisasi lalu membacanya di method — compiler menolak local yang belum pasti terisi.

---

### final

**Tipe:** modifier variabel / field / parameter

**Untuk apa:** melarang penugasan ulang pada variabel itu. Untuk primitif, nilainya terkunci. Untuk referensi, **referensinya** terkunci, isi objek masih bisa berubah.

**Contoh implementasi:**

```java
public class ContohFinal {
    public static void main(String[] args) {
        final int pajakPersen = 11;
        final String[] rak = { "Buku A", "Buku B" };
        rak[0] = "Buku C";
        // pajakPersen = 12; // error: cannot assign a value to final variable
        // rak = new String[1]; // error: referensi dikunci
        System.out.println("Pajak: " + pajakPersen + "%");
        System.out.println("Rak[0]: " + rak[0]);
    }
}
```

**Yang terjadi:** `pajakPersen` tetap 11. Array `rak` masih objek yang sama, tetapi elemen ke-0 berubah jadi `"Buku C"`. Output pajak 11% dan `Rak[0]: Buku C`.

**Biasanya digabungkan dengan:** konstanta `static final` (`public static final int MAX_STOK = 100;`) dan parameter method yang tidak boleh ditimpa.

**Jangan:** mengira `final` membuat array atau objek immutable. Untuk objek yang benar-benar terkunci, rancang class tanpa setter (bab 04).

---

### var

**Tipe:** type inference lokal (Java 10+)

**Untuk apa:** membiarkan compiler menyimpulkan tipe dari inisialisasi, agar deklarasi tidak berulang panjang.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ContohVar {
    public static void main(String[] args) {
        var nama = "Toko Belajar";
        var harga = 15000;
        var daftar = new ArrayList<String>();
        daftar.add(nama);
        System.out.println(nama + " bertipe String? " + (nama instanceof String));
        System.out.println("harga + 1 = " + (harga + 1));
        List<String> samaSaja = daftar;
        System.out.println(samaSaja);
        // var kosong; // error: tidak bisa tanpa inisialisasi
        // var acak = null; // error: tipe tidak bisa disimpulkan
    }
}
```

**Yang terjadi:** `nama` adalah `String`, `harga` adalah `int`, `daftar` adalah `ArrayList<String>`. `var` **bukan** tipe dinamis; setelah disimpulkan, `harga` tidak bisa diisi string.

**Biasanya digabungkan dengan:** constructor yang sudah menulis tipe di kanan (`var list = new ArrayList<String>();`).

**Jangan:** memakai `var` untuk field class — hanya local. Jangan memakai `var` jika tipe di kanan tidak jelas (`var hasil = proses();` tanpa nama yang membantu).

---

### Literal angka

**Tipe:** sintaks nilai

**Untuk apa:** menulis nilai langsung di sumber: desimal, biner, heksadesimal, underscore pemisah, sufiks `L`/`F`.

**Contoh implementasi:**

```java
public class LiteralAngka {
    public static void main(String[] args) {
        int desimal = 42;
        int biner = 0b101010;
        int heks = 0x2A;
        int underscore = 1_000_000;
        long penduduk = 280_000_000L;
        float diskon = 0.1f;
        double pi = 3.14;
        double saintifik = 1.5e3;
        System.out.println(desimal + " " + biner + " " + heks);
        System.out.println(underscore);
        System.out.println(penduduk);
        System.out.println(diskon + " " + pi + " " + saintifik);
    }
}
```

**Yang terjadi:** `0b101010`, `0x2A`, dan `42` adalah angka yang sama. Underscore diabaikan compiler: `1_000_000` sama dengan `1000000`. Tanpa `L`, literal bulat adalah `int` (overflow jika terlalu besar). Tanpa `f`, `0.1` adalah `double`. `1.5e3` adalah 1500.0.

**Biasanya digabungkan dengan:** `long` untuk angka besar dan `float` hanya jika diminta API.

**Jangan:** menulis `long x = 3000000000;` tanpa `L` — literal `int` overflow di sumber. Jangan memakai underscore di ujung (`1000_`) — ilegal.

---

### byte

**Tipe:** tipe primitif

**Untuk apa:** bilangan bulat 8-bit dari **-128 sampai 127**. Dipakai untuk data mentah, file biner, atau rentang kecil yang disengaja.

**Contoh implementasi:**

```java
public class ContohByte {
    public static void main(String[] args) {
        byte stokMinimum = 5;
        byte stokSekarang = 3;
        int selisihInt = stokMinimum - stokSekarang;
        byte selisihByte = (byte) (stokMinimum - stokSekarang);
        System.out.println("Selisih int: " + selisihInt);
        System.out.println("Selisih byte: " + selisihByte);
        System.out.println("MIN=" + Byte.MIN_VALUE + " MAX=" + Byte.MAX_VALUE);
        byte hampirPenuh = 127;
        byte overflow = (byte) (hampirPenuh + 1);
        System.out.println("127+1 sebagai byte: " + overflow);
    }
}
```

**Yang terjadi:** pengurangan dua `byte` diangkat ke `int`, jadi `selisihInt` adalah 2 tanpa cast. Cast ke `byte` juga 2. `127 + 1` tidak muat: hasil cast menjadi **-128** (wrap around).

**Biasanya digabungkan dengan:** `byte[]` untuk isi file, wrapper `Byte`, dan cast sadar overflow.

**Jangan:** memakai `byte` untuk harga, umur manusia, atau penghitung loop biasa. Pakai `int`. Jangan menambah `byte` berulang tanpa cast lalu heran tipenya jadi `int`.

---

### short

**Tipe:** tipe primitif

**Untuk apa:** bilangan bulat 16-bit dari **-32.768 sampai 32.767**. Jarang dibutuhkan di kode aplikasi; kadang muncul di API lama atau data numerik hemat memori.

**Contoh implementasi:**

```java
public class ContohShort {
    public static void main(String[] args) {
        short kodePos = 16424;
        short tahun = 2026;
        int gabung = kodePos + tahun;
        short gabungShort = (short) (kodePos + tahun);
        System.out.println("kodePos=" + kodePos);
        System.out.println("jumlah int=" + gabung);
        System.out.println("jumlah short=" + gabungShort);
        System.out.println("MIN=" + Short.MIN_VALUE + " MAX=" + Short.MAX_VALUE);
    }
}
```

**Yang terjadi:** `kodePos + tahun` dihitung sebagai `int` (18450). Cast ke `short` masih muat. `MAX` resmi 32767.

**Biasanya digabungkan dengan:** array `short[]` pada data numerik padat, dan `Short.parseShort`.

**Jangan:** memilih `short` “agar hemat” tanpa mengukur. JVM sering memproses `int` lebih alami. Jangan mengisi `short s = 40000;` — di luar rentang.

---

### int

**Tipe:** tipe primitif

**Untuk apa:** bilangan bulat 32-bit andalan Java, dari **-2.147.483.648 sampai 2.147.483.647**. Default untuk hitungan, indeks, jumlah barang, dan hampir semua loop.

**Contoh implementasi:**

```java
public class ContohInt {
    public static void main(String[] args) {
        int harga = 15000;
        int jumlah = 3;
        int total = harga * jumlah;
        int sisaBagi = 10 % 3;
        System.out.println("Total: " + total);
        System.out.println("10 % 3 = " + sisaBagi);
        System.out.println("MIN=" + Integer.MIN_VALUE);
        System.out.println("MAX=" + Integer.MAX_VALUE);
        int meledak = Integer.MAX_VALUE + 1;
        System.out.println("MAX+1 = " + meledak);
    }
}
```

**Yang terjadi:** `total` menjadi 45000. `10 % 3` adalah 1. `MAX + 1` **tidak** error: ia membungkus ke `Integer.MIN_VALUE` (angka negatif besar). Java tidak melempar overflow pada `int`.

**Biasanya digabungkan dengan:** `long` jika hasil kali bisa tembus 2 miliar, dan `Integer.parseInt` saat baca teks.

**Jangan:** memakai `int` untuk uang pecahan (tidak ada sen). Jangan mengandalkan overflow sebagai fitur. Untuk jumlah penduduk dunia atau ID sangat besar, pakai `long`.

---

### long

**Tipe:** tipe primitif

**Untuk apa:** bilangan bulat 64-bit. Pakai jika `int` bisa kehabisan rentang: milidetik sejak epoch, ukuran file, jumlah transaksi besar.

**Contoh implementasi:**

```java
public class ContohLong {
    public static void main(String[] args) {
        long milidetik = System.currentTimeMillis();
        long hargaSatuan = 50_000L;
        long jumlah = 100_000L;
        long total = hargaSatuan * jumlah;
        System.out.println("Sekarang (ms): " + milidetik);
        System.out.println("Total long: " + total);
        long salahKetik = 50_000 * 100_000;
        System.out.println("Tanpa L, perkalian int: " + salahKetik);
        System.out.println("MAX long=" + Long.MAX_VALUE);
    }
}
```

**Yang terjadi:** `50_000L * 100_000L` = 5_000_000_000, aman di `long`. `50_000 * 100_000` dihitung sebagai **`int` dulu** (overflow) baru disimpan ke `long`, hasilnya **salah**. Sufiks `L` penting sebelum operasi, bukan hanya pada variabel hasil.

**Biasanya digabungkan dengan:** `System.currentTimeMillis()`, ukuran file (`Files.size`), dan `Long.parseLong`.

**Jangan:** menulis literal di atas `Integer.MAX_VALUE` tanpa `L`. Jangan memakai `int` untuk hasil `harga * jumlah` jika keduanya bisa besar.

---

### float

**Tipe:** tipe primitif

**Untuk apa:** pecahan 32-bit IEEE-754. Hemat memori pada array besar, tetapi **kurang presisi** dibanding `double`.

**Contoh implementasi:**

```java
public class ContohFloat {
    public static void main(String[] args) {
        float diskon = 0.1f;
        float harga = 10.0f;
        float setelah = harga * (1.0f - diskon);
        System.out.println("Setelah diskon: " + setelah);
        System.out.println("0.1f + 0.2f = " + (0.1f + 0.2f));
        float besar = 16777216f;
        System.out.println("16777216f + 1 = " + (besar + 1f));
        System.out.println("SIZE bit=" + Float.SIZE);
    }
}
```

**Yang terjadi:** `0.1f + 0.2f` sering **bukan** 0.3 persis. `16777216f + 1f` bisa tetap 16777216 karena mantissa `float` kehabisan bit. Sufiks `f` wajib jika kanan berupa literal pecahan yang ingin jadi `float`.

**Biasanya digabungkan dengan:** API grafis/game yang memakai `float`, dan `Float.parseFloat`.

**Jangan:** menyimpan uang di `float`. Jangan membandingkan `float` dengan `==` untuk hasil hitungan. Jangan menulis `float x = 0.1;` tanpa `f` — itu `double` yang harus di-narrow.

---

### double

**Tipe:** tipe primitif

**Untuk apa:** pecahan 64-bit, default pecahan di Java. Ilmu hitung, rata-rata nilai, koordinat, hampir semua desimal non-uang.

**Contoh implementasi:**

```java
public class ContohDouble {
    public static void main(String[] args) {
        double harga = 15_000.50;
        double jumlah = 3;
        double total = harga * jumlah;
        double rata = (80 + 90 + 70) / 3.0;
        System.out.println("Total: " + total);
        System.out.println("Rata-rata: " + rata);
        System.out.println("0.1 + 0.2 = " + (0.1 + 0.2));
        System.out.println("0.1 + 0.2 == 0.3 ? " + ((0.1 + 0.2) == 0.3));
        System.out.println("MAX=" + Double.MAX_VALUE);
    }
}
```

**Yang terjadi:** `(80+90+70)/3.0` adalah 80.0 karena pembagi `double`. `0.1 + 0.2` mencetak sesuatu seperti `0.30000000000000004`, dan perbandingan `== 0.3` adalah **false**. Itu sifat biner pecahan, bukan bug tokomu.

**Biasanya digabungkan dengan:** `Math` (`sqrt`, `pow`, `round`) dan `Double.parseDouble`.

**Jangan:** memakai `double` untuk saldo uang yang harus pas sen. Pakai `int` sen atau `BigDecimal`. Jangan membagi dua `int` lalu menyimpan ke `double` tanpa mengubah salah satu jadi pecahan: `int 7/2` adalah `3`, baru di-widen.

---

### char

**Tipe:** tipe primitif

**Untuk apa:** satu kode unit UTF-16 (0 sampai 65535). Huruf, digit, tanda. Bukan string.

**Contoh implementasi:**

```java
public class ContohChar {
    public static void main(String[] args) {
        char inisial = 'H';
        char digit = '7';
        char barisBaru = '\n';
        int kode = inisial;
        char berikutnya = (char) (inisial + 1);
        System.out.println("Inisial: " + inisial);
        System.out.println("Kode 'H': " + kode);
        System.out.println("Berikutnya: " + berikutnya);
        System.out.println("digit angka? " + Character.isDigit(digit));
        System.out.print("sebelum");
        System.out.print(barisBaru);
        System.out.println("sesudah");
        // char salah = "H"; // error: String bukan char
    }
}
```

**Yang terjadi:** `'H'` berbeda dari `"H"`. `'H'` bisa dihitung sebagai angka (kode 72), sehingga `+ 1` menjadi `'I'`. `Character.isDigit('7')` true. `\n` memaksa ganti baris.

**Biasanya digabungkan dengan:** `String.charAt`, `Character` wrapper, dan loop menelusuri teks.

**Jangan:** memakai `char` untuk emoji atau huruf di luar BMP (beberapa karakter butuh dua `char` / surrogate pair). Untuk teks pakai `String`. Jangan menulis `char c = "A";`.

---

### boolean

**Tipe:** tipe primitif

**Untuk apa:** nilai `true` atau `false`. Hasil perbandingan, flag stok, hak akses.

**Contoh implementasi:**

```java
public class ContohBoolean {
    public static void main(String[] args) {
        int stok = 0;
        boolean habis = stok == 0;
        boolean member = true;
        boolean bolehDiskon = member && !habis;
        System.out.println("Habis? " + habis);
        System.out.println("Boleh diskon? " + bolehDiskon);
        if (habis) {
            System.out.println("Pesan: restock");
        }
        // boolean salah = 1; // error: Java tidak menganggap 1 sebagai true
    }
}
```

**Yang terjadi:** `habis` true. `member && !habis` false karena stok habis. `if (habis)` masuk cabang restock. Tidak ada konversi diam-diam dari `int` ke `boolean`.

**Biasanya digabungkan dengan:** `if`, `while`, operator `&&` `||` `!`, dan wrapper `Boolean` di collections.

**Jangan:** menulis `if (habis == true)` — cukup `if (habis)`. Jangan memakai `Boolean` (objek) jika `boolean` cukup: unboxing `null` meledak.

---

### Nilai default field

**Tipe:** aturan inisialisasi

**Untuk apa:** memahami nilai field class yang tidak kamu isi: angka 0, `char` `\u0000`, `boolean` false, referensi `null`.

**Contoh implementasi:**

```java
public class NilaiDefault {
    int jumlah;
    double harga;
    boolean aktif;
    char tanda;
    String nama;
    Integer poin;

    public static void main(String[] args) {
        NilaiDefault d = new NilaiDefault();
        System.out.println("jumlah=" + d.jumlah);
        System.out.println("harga=" + d.harga);
        System.out.println("aktif=" + d.aktif);
        System.out.println("tanda kode=" + (int) d.tanda);
        System.out.println("nama=" + d.nama);
        System.out.println("poin=" + d.poin);
    }
}
```

**Yang terjadi:** output `0`, `0.0`, `false`, kode `0`, `nama=null`, `poin=null`. Local variable **tidak** mendapat default: kamu wajib mengisi sebelum baca.

**Biasanya digabungkan dengan:** constructor yang mengisi nilai bermakna, agar `null` tidak lolos.

**Jangan:** mengandalkan default `0` sebagai “belum diisi” jika `0` juga nilai sah (harga gratis). Pakai `Optional` atau wrapper dan cek `null` secara sadar.

---

### Overflow

**Tipe:** perilaku aritmetika primitif

**Untuk apa:** menyadari bahwa `int`/`long` membungkus diam-diam, tidak melempar.

**Contoh implementasi:**

```java
public class ContohOverflow {
    public static void main(String[] args) {
        int a = 1_500_000_000;
        int b = 1_500_000_000;
        int salah = a + b;
        long benar = (long) a + b;
        System.out.println("int + int = " + salah);
        System.out.println("long = " + benar);
        System.out.println("Math.addExact: ");
        try {
            System.out.println(Math.addExact(a, b));
        } catch (ArithmeticException ex) {
            System.out.println("Ketahuilah: " + ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `a + b` sebagai `int` menjadi negatif (sekitar -1294967296) karena melewati `MAX_VALUE`. Cast salah satu ke `long` **sebelum** tambah memberi 3000000000. `Math.addExact` melempar `ArithmeticException`.

**Biasanya digabungkan dengan:** `long`, dan `Math.*Exact` jika overflow harus gagal keras.

**Jangan:** menambahkan harga besar di `int` lalu menampilkan ke pelanggan. Jangan menangkap exception overflow jika kamu belum memakai `*Exact` — overflow biasa **bisu**.

---

### Widening

**Tipe:** konversi implisit

**Untuk apa:** memasukkan tipe “kecil” ke tipe “lebih lebar” tanpa cast: `byte` → `short` → `int` → `long` → `float` → `double`. `char` bisa ke `int` ke atas.

**Contoh implementasi:**

```java
public class ContohWidening {
    public static void main(String[] args) {
        byte stok = 7;
        int stokInt = stok;
        long stokLong = stokInt;
        double stokPecahan = stokLong;
        char huruf = 'A';
        int kode = huruf;
        System.out.println(stokInt + " " + stokLong + " " + stokPecahan);
        System.out.println("Kode A=" + kode);
    }
}
```

**Yang terjadi:** tidak ada data yang terpotong di contoh ini. `7` tetap 7.0 di `double`. `'A'` menjadi 65.

**Biasanya digabungkan dengan:** method yang parameter-nya `double` tetapi kamu punya `int`.

**Jangan:** mengira widening `long` → `float` selalu presisi. `float` punya mantissa lebih pendek; integer besar bisa membulat.

---

### Narrowing

**Tipe:** konversi eksplisit (cast)

**Untuk apa:** memaksa tipe lebar ke tipe sempit. Compiler menuntut `(tipe)` karena data bisa terpotong.

**Contoh implementasi:**

```java
public class ContohNarrowing {
    public static void main(String[] args) {
        double total = 45_000.99;
        int tanpaPecahan = (int) total;
        long penduduk = 300_000_000L;
        int potong = (int) penduduk;
        double besar = 1e20;
        float menyusut = (float) besar;
        System.out.println("double ke int: " + tanpaPecahan);
        System.out.println("long ke int: " + potong);
        System.out.println("1e20 ke float: " + menyusut);
    }
}
```

**Yang terjadi:** `(int) 45000.99` menjadi **45000** (potong pecahan, bukan rounding). `300_000_000L` masih muat di `int`. `1e20` sebagai `float` menjadi `Infinity` karena terlalu besar.

**Biasanya digabungkan dengan:** `Math.round` jika ingin bulat terdekat: `(int) Math.round(total)`.

**Jangan:** men-cast `double` uang ke `int` lalu menganggap sen hilang itu “pembulatan bank”. Jangan men-cast tanpa mencetak hasil saat belajar.

---

### Pembagian int

**Tipe:** perilaku operator `/`

**Untuk apa:** mengingat `int / int` membuang pecahan.

**Contoh implementasi:**

```java
public class BagiInt {
    public static void main(String[] args) {
        int benar = 7;
        int soal = 2;
        int salahRata = benar / soal;
        double rata = benar / (double) soal;
        System.out.println("7/2 int = " + salahRata);
        System.out.println("7/2.0 = " + rata);
        System.out.println("7 % 2 = " + (benar % soal));
    }
}
```

**Yang terjadi:** `7/2` adalah **3**, bukan 3.5. Cast salah satu operand ke `double` memberi 3.5. `%` menghasilkan 1.

**Biasanya digabungkan dengan:** rata-rata nilai, persentase (`bagian * 100.0 / total`).

**Jangan:** menulis `double rata = jumlah / n;` jika `jumlah` dan `n` sama-sama `int`. Pembagian terjadi dulu sebagai `int`.

---

### NaN dan Infinity

**Tipe:** nilai khusus `double`/`float`

**Untuk apa:** hasil operasi pecahan yang tidak terdefinisi atau melewati rentang.

**Contoh implementasi:**

```java
public class NanInfinity {
    public static void main(String[] args) {
        double bagiNol = 1.0 / 0.0;
        double nolPerNol = 0.0 / 0.0;
        double akar = Math.sqrt(-1);
        System.out.println("1.0/0.0 = " + bagiNol);
        System.out.println("0.0/0.0 = " + nolPerNol);
        System.out.println("sqrt(-1) = " + akar);
        System.out.println("NaN == NaN? " + (akar == akar));
        System.out.println("isNaN? " + Double.isNaN(akar));
        System.out.println("isInfinite? " + Double.isInfinite(bagiNol));
        try {
            int meledak = 1 / 0;
            System.out.println(meledak);
        } catch (ArithmeticException ex) {
            System.out.println("int/0 melempar: " + ex);
        }
    }
}
```

**Yang terjadi:** `double` bagi nol menjadi `Infinity`. `0.0/0.0` dan `sqrt(-1)` menjadi `NaN`. `NaN == NaN` adalah **false**; pakai `Double.isNaN`. `int` bagi nol melempar `ArithmeticException`, beda dengan `double`.

**Biasanya digabungkan dengan:** `Double.isFinite` sebelum menampilkan angka ke pengguna.

**Jangan:** menguji `hasil == Double.NaN`. Jangan membagi `int` nol tanpa `try` atau penjagaan.

---

### Byte (wrapper)

**Tipe:** class (`java.lang.Byte`)

**Untuk apa:** membungkus `byte` sebagai objek: collections, `null`, parsing teks.

**Contoh implementasi:**

```java
public class ContohByteWrapper {
    public static void main(String[] args) {
        Byte stok = Byte.valueOf("12");
        byte primitif = stok.byteValue();
        System.out.println("Objek: " + stok);
        System.out.println("Primitif: " + primitif);
        System.out.println("decode 0x10 = " + Byte.decode("0x10"));
        try {
            Byte.valueOf("200");
        } catch (NumberFormatException ex) {
            System.out.println("200 tidak muat di byte: " + ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `"12"` menjadi objek `Byte` bernilai 12. `byteValue()` mengeluarkan primitif. `Byte.decode("0x10")` adalah 16. `"200"` di luar 127: `NumberFormatException`.

**Biasanya digabungkan dengan:** `byte[]` yang perlu diolah per elemen sebagai objek (jarang), dan autoboxing.

**Jangan:** memakai `new Byte(12)` — constructor deprecated. Pakai `valueOf`.

---

### Short (wrapper)

**Tipe:** class (`java.lang.Short`)

**Untuk apa:** objek dari `short`; parsing; konstanta `SIZE`/`BYTES`.

**Contoh implementasi:**

```java
public class ContohShortWrapper {
    public static void main(String[] args) {
        Short kode = Short.valueOf((short) 404);
        short mentah = kode;
        System.out.println("kode=" + kode + " mentah=" + mentah);
        System.out.println(Short.parseShort("32000"));
        System.out.println("BYTES=" + Short.BYTES);
    }
}
```

**Yang terjadi:** autounboxing `kode` ke `mentah`. `parseShort("32000")` sukses. `Short.BYTES` adalah 2.

**Biasanya digabungkan dengan:** data protokol 16-bit.

**Jangan:** `Short.parseShort("40000")` — di luar rentang, exception.

---

### Integer

**Tipe:** class (`java.lang.Integer`)

**Untuk apa:** objek `int`. Paling sering dipakai di `List<Integer>`, parsing input, dan konstanta `MAX_VALUE`.

**Contoh implementasi:**

```java
public class ContohInteger {
    public static void main(String[] args) {
        Integer harga = 15000;
        Integer dariTeks = Integer.valueOf("15000");
        int primitif = harga;
        System.out.println(harga + 500);
        System.out.println(dariTeks.equals(harga));
        System.out.println("bitCount 15=" + Integer.bitCount(15));
        System.out.println("toBinaryString 10=" + Integer.toBinaryString(10));
        System.out.println("toHexString 255=" + Integer.toHexString(255));
    }
}
```

**Yang terjadi:** `15000` di-autobox ke `Integer`. `"15000"` di-parse. `harga + 500` unbox dulu, hasil `int` 15500 lalu dicetak. `equals` membandingkan nilai. `15` dalam biner `1111` punya 4 bit nyala. `10` biner `1010`. `255` heks `ff`.

**Biasanya digabungkan dengan:** `ArrayList<Integer>`, `Map<Integer, String>`, dan `parseInt`.

**Jangan:** memakai `Integer` di loop ketat hanya untuk hitungan — `int` lebih jujur. Jangan membandingkan dua `Integer` dengan `==` untuk nilai di luar cache (lihat entri cache).

---

### Integer.parseInt

**Tipe:** method static (`Integer`)

**Untuk apa:** mengubah `String` angka desimal (atau radix lain) menjadi `int`. Gagal → `NumberFormatException`.

**Contoh implementasi:**

```java
public class ContohParseInt {
    public static void main(String[] args) {
        String input = "  42";
        int bersih = Integer.parseInt(input.trim());
        int heks = Integer.parseInt("2A", 16);
        System.out.println("Desimal: " + bersih);
        System.out.println("Heks 2A: " + heks);
        String[] uji = { "42", "42.5", "", "tiga", "999999999999" };
        for (String s : uji) {
            try {
                System.out.println(s + " -> " + Integer.parseInt(s));
            } catch (NumberFormatException ex) {
                System.out.println(s + " gagal: " + ex.getMessage());
            }
        }
    }
}
```

**Yang terjadi:** `"  42"` gagal tanpa `trim`, berhasil setelah `trim`. `"2A"` basis 16 = 42. `"42.5"`, `""`, `"tiga"`, dan angka di luar `int` semuanya gagal.

**Biasanya digabungkan dengan:** `trim()`, `try/catch` (bab 06), dan `Scanner`/`args`.

**Jangan:** `parseInt` pada string uang `"Rp15000"` tanpa membersihkan huruf. Jangan memakai `parseInt` untuk `"true"`.

---

### Integer.valueOf

**Tipe:** method static (`Integer`)

**Untuk apa:** menghasilkan `Integer` dari `int` atau `String`. Bisa memakai **cache** untuk -128..127.

**Contoh implementasi:**

```java
public class ContohValueOf {
    public static void main(String[] args) {
        Integer a = Integer.valueOf(10);
        Integer b = Integer.valueOf("10");
        Integer c = Integer.valueOf(10);
        System.out.println("equals: " + a.equals(b));
        System.out.println("a == c (cache)? " + (a == c));
        Integer besar1 = Integer.valueOf(1000);
        Integer besar2 = Integer.valueOf(1000);
        System.out.println("1000 == 1000? " + (besar1 == besar2));
        System.out.println("1000 equals? " + besar1.equals(besar2));
    }
}
```

**Yang terjadi:** `a.equals(b)` true. `a == c` biasanya true karena cache. `1000` sering **dua objek berbeda**, jadi `==` false, `equals` true.

**Biasanya digabungkan dengan:** autoboxing (compiler memanggil `valueOf`).

**Jangan:** mengandalkan `==` pada `Integer`. Selalu `equals` atau bandingkan `.intValue()`.

---

### Integer.toString

**Tipe:** method (`static` dan instance)

**Untuk apa:** mengubah `int`/`Integer` menjadi teks.

**Contoh implementasi:**

```java
public class ContohIntToString {
    public static void main(String[] args) {
        int harga = 15000;
        String a = Integer.toString(harga);
        String b = String.valueOf(harga);
        String c = "" + harga;
        String heks = Integer.toString(255, 16);
        Integer objek = 42;
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
        System.out.println(heks);
        System.out.println(objek.toString());
    }
}
```

**Yang terjadi:** `a`, `b`, dan `c` semua `"15000"`. Basis 16 dari 255 adalah `"ff"`. `objek.toString()` `"42"`. `"" + harga` mudah dibaca tetapi mengalokasi string tambahan.

**Biasanya digabungkan dengan:** gabungan pesan ke pengguna, dan tulis file (bab 06).

**Jangan:** mengira `toString` menambah titik ribuan. Untuk format uang lihat resep bab 09 atau `NumberFormat`.

---

### Integer.compare

**Tipe:** method static

**Untuk apa:** membandingkan dua `int` tanpa overflow jebakan `x - y`, mengembalikan negatif/0/positif.

**Contoh implementasi:**

```java
public class ContohIntegerCompare {
    public static void main(String[] args) {
        System.out.println(Integer.compare(5, 10));
        System.out.println(Integer.compare(10, 10));
        System.out.println(Integer.compare(10, 5));
        int min = Integer.MIN_VALUE;
        int max = Integer.MAX_VALUE;
        System.out.println("min - max (overflow): " + (min - max));
        System.out.println("compare min max: " + Integer.compare(min, max));
    }
}
```

**Yang terjadi:** cetakan `-1`, `0`, `1` (atau negatif/positif sejenis). `min - max` overflow dan bisa tampak positif. `Integer.compare` tetap negatif: `min` lebih kecil.

**Biasanya digabungkan dengan:** `Comparator`, `Arrays.sort`, `List.sort`.

**Jangan:** menulis comparator `(a, b) -> a - b` untuk `int` sebarang. Pakai `Integer.compare(a, b)`.

---

### Integer.MAX_VALUE

**Tipe:** field static final (`int`)

**Untuk apa:** batas atas `int`. Sering dipakai sebagai “tak hingga” sementara pada algoritma, atau penjaga overflow.

**Contoh implementasi:**

```java
public class ContohMaxValue {
    public static void main(String[] args) {
        int[] harga = { 12_000, 45_000, 7_500 };
        int terkecil = Integer.MAX_VALUE;
        for (int h : harga) {
            if (h < terkecil) {
                terkecil = h;
            }
        }
        System.out.println("Termurah: " + terkecil);
        System.out.println("MAX=" + Integer.MAX_VALUE);
        System.out.println("MIN=" + Integer.MIN_VALUE);
    }
}
```

**Yang terjadi:** `terkecil` mulai dari nilai terbesar yang mungkin, lalu turun ke 7500. Pola yang sama memakai `Integer.MIN_VALUE` untuk mencari maksimum.

**Biasanya digabungkan dengan:** loop linier, dan `Long.MAX_VALUE` untuk `long`.

**Jangan:** menambah `MAX_VALUE` “sedikit saja”. Jangan memakai `MAX_VALUE` sebagai harga nyata.

---

### Long (wrapper)

**Tipe:** class (`java.lang.Long`)

**Untuk apa:** objek `long`; parsing ID besar; waktu.

**Contoh implementasi:**

```java
public class ContohLongWrapper {
    public static void main(String[] args) {
        Long id = Long.valueOf("10000000000");
        long mentah = id;
        System.out.println(id);
        System.out.println(mentah);
        System.out.println(Long.parseLong("FF", 16));
        System.out.println("MAX=" + Long.MAX_VALUE);
    }
}
```

**Yang terjadi:** `"10000000000"` tidak muat di `int`, tetapi muat di `Long`. `parseLong("FF", 16)` = 255.

**Biasanya digabungkan dengan:** `System.currentTimeMillis()` yang sudah `long`, dan `Map<Long, String>`.

**Jangan:** `Integer.parseInt` pada ID 10+ digit. Jangan membandingkan `Long` dengan `==`.

---

### Float (wrapper)

**Tipe:** class (`java.lang.Float`)

**Untuk apa:** objek `float`; `NaN`/`Infinity` sebagai objek; parsing.

**Contoh implementasi:**

```java
public class ContohFloatWrapper {
    public static void main(String[] args) {
        Float f = Float.valueOf("3.14");
        System.out.println(f);
        System.out.println(f.floatValue() + 0.01f);
        System.out.println("NaN object: " + Float.valueOf(Float.NaN));
        System.out.println(Float.isNaN(0.0f / 0.0f));
    }
}
```

**Yang terjadi:** teks `"3.14"` menjadi objek. `isNaN` true untuk 0/0 float.

**Biasanya digabungkan dengan:** API yang menuntut `Float`, bukan `float`.

**Jangan:** `List<float>` — tidak legal. Collections butuh `Float`. Tetap hindari uang.

---

### Double (wrapper)

**Tipe:** class (`java.lang.Double`)

**Untuk apa:** objek `double`. Sering di `List<Double>` hasil hitungan.

**Contoh implementasi:**

```java
public class ContohDoubleWrapper {
    public static void main(String[] args) {
        Double berat = 1.25;
        Double dariTeks = Double.valueOf("1.25");
        System.out.println(berat.equals(dariTeks));
        System.out.println(Double.compare(0.1 + 0.2, 0.3));
        System.out.println("isFinite(1e308*10)? " + Double.isFinite(1e308 * 10));
        System.out.println(Double.toHexString(1.0));
    }
}
```

**Yang terjadi:** `equals` true untuk 1.25 yang sama. `Double.compare(0.1+0.2, 0.3)` bukan 0 karena pecahan biner. `1e308*10` overflow ke Infinity: `isFinite` false.

**Biasanya digabungkan dengan:** `parseDouble`, `Math`, Stream `mapToDouble`.

**Jangan:** `doubleObj.equals(0.3)` setelah deret tambah 0.1. Bandingkan dengan epsilon, atau pakai `BigDecimal` untuk uang.

---

### Double.parseDouble

**Tipe:** method static

**Untuk apa:** membaca pecahan dari teks. Menerima `1.5`, `1.5e2`, `Infinity` (tergantung teks).

**Contoh implementasi:**

```java
public class ContohParseDouble {
    public static void main(String[] args) {
        System.out.println(Double.parseDouble("3.14"));
        System.out.println(Double.parseDouble("1.5e2"));
        String komaLokal = "3,14";
        try {
            System.out.println(Double.parseDouble(komaLokal));
        } catch (NumberFormatException ex) {
            System.out.println("Koma tidak diterima parseDouble. Ganti: "
                    + Double.parseDouble(komaLokal.replace(',', '.')));
        }
    }
}
```

**Yang terjadi:** `"3.14"` → 3.14. `"1.5e2"` → 150.0. `"3,14"` gagal di locale default parser ini (titik adalah desimal). `replace` menolong input Indonesia.

**Biasanya digabungkan dengan:** `trim()`, dan `NumberFormat` jika format lokal rumit.

**Jangan:** `parseDouble("Rp 3.000,50")` mentah-mentah.

---

### Character

**Tipe:** class (`java.lang.Character`)

**Untuk apa:** method huruf: digit, whitespace, upper/lower, tipe Unicode.

**Contoh implementasi:**

```java
public class ContohCharacter {
    public static void main(String[] args) {
        char c = 'h';
        System.out.println(Character.toUpperCase(c));
        System.out.println("digit? " + Character.isDigit(c));
        System.out.println("huruf? " + Character.isLetter(c));
        System.out.println("spasi? " + Character.isWhitespace(' '));
        Character objek = 'Z';
        char mentah = objek;
        System.out.println(mentah);
        String kata = "Buku12";
        int digit = 0;
        for (int i = 0; i < kata.length(); i++) {
            if (Character.isDigit(kata.charAt(i))) {
                digit++;
            }
        }
        System.out.println("Jumlah digit: " + digit);
    }
}
```

**Yang terjadi:** `'h'` jadi `'H'`. `'h'` bukan digit. Loop menghitung 2 digit di `"Buku12"`.

**Biasanya digabungkan dengan:** `charAt`, validasi input per karakter.

**Jangan:** `Character.toUpperCase` pada seluruh kalimat lalu mengira locale Turki tidak berpengaruh. Untuk teks utuh, `String.toUpperCase()` dengan locale lebih jelas.

---

### Boolean (wrapper)

**Tipe:** class (`java.lang.Boolean`)

**Untuk apa:** objek `true`/`false` yang bisa `null` (tiga keadaan: ya / tidak / belum diisi).

**Contoh implementasi:**

```java
public class ContohBooleanWrapper {
    public static void main(String[] args) {
        Boolean member = Boolean.TRUE;
        Boolean belumTahu = null;
        System.out.println(member);
        System.out.println("belumTahu == null? " + (belumTahu == null));
        System.out.println(Boolean.valueOf("true"));
        System.out.println(Boolean.valueOf("TRUE"));
        System.out.println(Boolean.valueOf("ya"));
    }
}
```

**Yang terjadi:** `Boolean.TRUE` adalah instance terbagi. `belumTahu` null berarti “tidak ada jawaban”. `valueOf("TRUE")` true (abaikan huruf). `valueOf("ya")` **false** — hanya `"true"` (ignore case) yang true.

**Biasanya digabungkan dengan:** field opsional, dan `Boolean.parseBoolean`.

**Jangan:** `if (belumTahu)` saat bisa null — unboxing NPE. Jangan mengira `"false"` dan `"ya"` diperlakukan simetris.

---

### Boolean.parseBoolean

**Tipe:** method static

**Untuk apa:** membaca flag dari teks konfigurasi. Tidak melempar: selain `"true"` (ignore case) dianggap false.

**Contoh implementasi:**

```java
public class ContohParseBoolean {
    public static void main(String[] args) {
        String[] uji = { "true", "TRUE", "True", "false", "salah", "", "1" };
        for (String s : uji) {
            System.out.println(s + " -> " + Boolean.parseBoolean(s));
        }
    }
}
```

**Yang terjadi:** tiga variasi `"true"` menjadi true. Sisanya false, termasuk `"1"` dan `""`. Tidak ada exception.

**Biasanya digabungkan dengan:** file `.properties`, argumen CLI `--ready=true`.

**Jangan:** memakai `parseBoolean` jika kamu butuh error pada input aneh. Validasi sendiri, atau terima hanya `"true"`/`"false"`.

---

### Autoboxing

**Tipe:** konversi compiler

**Untuk apa:** menulis `Integer x = 5;` tanpa `valueOf` manual. Compiler menyelipkan `Integer.valueOf(5)`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ContohAutoboxing {
    public static void main(String[] args) {
        List<Integer> harga = new ArrayList<>();
        harga.add(15000);
        harga.add(20000);
        int total = 0;
        for (Integer h : harga) {
            total += h;
        }
        System.out.println(harga);
        System.out.println("Total: " + total);
    }
}
```

**Yang terjadi:** `add(15000)` mengemas `int` jadi `Integer`. Loop `for` meng-unbox ke `int` saat `total += h`. `List` **tidak bisa** `List<int>`.

**Biasanya digabungkan dengan:** collections (bab 05) dan generics (bab 08).

**Jangan:** mengautobox di dalam loop ketat jutaan kali tanpa sadar alokasi. Jangan memasukkan `null` ke `List<Integer>` lalu menjumlah — NPE saat unbox.

---

### Unboxing

**Tipe:** konversi compiler

**Untuk apa:** memakai objek wrapper di konteks primitif: aritmetika, `if`, array index.

**Contoh implementasi:**

```java
public class ContohUnboxing {
    public static void main(String[] args) {
        Integer poin = 10;
        int ganda = poin * 2;
        Integer kosong = null;
        System.out.println("ganda=" + ganda);
        try {
            int meledak = kosong;
            System.out.println(meledak);
        } catch (NullPointerException ex) {
            System.out.println("Unboxing null: " + ex);
        }
    }
}
```

**Yang terjadi:** `poin * 2` memanggil `intValue()` lalu kali 2 = 20. `int meledak = kosong;` melempar `NullPointerException` — bukan “0”.

**Biasanya digabungkan dengan:** field `Integer` yang opsional, harus dicek null dulu.

**Jangan:** mencampur `Boolean` null dengan `if (flag)`. Jangan mengira unboxing memberi default field.

---

### == versus equals pada wrapper

**Tipe:** operator vs method

**Untuk apa:** `==` pada referensi menguji objek yang sama. `equals` menguji nilai.

**Contoh implementasi:**

```java
public class WrapperSama {
    public static void main(String[] args) {
        Integer a = 100;
        Integer b = 100;
        Integer c = 200;
        Integer d = 200;
        System.out.println("100 == 100 ? " + (a == b));
        System.out.println("200 == 200 ? " + (c == d));
        System.out.println("200 equals 200 ? " + c.equals(d));
        System.out.println("int == int 200? " + (c.intValue() == d.intValue()));
    }
}
```

**Yang terjadi:** `100` biasanya `==` true (cache). `200` biasanya `==` false. `equals` dan perbandingan `intValue` true. Hasil `==` **boleh berbeda antar JVM** di luar jaminan cache, jadi bukan kontrak yang boleh kamu andalkan.

**Biasanya digabungkan dengan:** `equals` pada semua objek, `Objects.equals` jika bisa null.

**Jangan:** menulis `if (harga == 200)` saat `harga` bertipe `Integer` hasil hitungan — kadang true karena unbox, kadang membingungkan jika kedua sisi objek. Lebih aman `harga != null && harga == 200` (unbox sadar) atau `Integer.valueOf(200).equals(harga)`.

---

### Cache Integer

**Tipe:** perilaku `Integer.valueOf`

**Untuk apa:** memahami mengapa `==` “kadang jalan”. JLS menjamin cache paling tidak **-128 sampai 127**.

**Contoh implementasi:**

```java
public class CacheInteger {
    public static void main(String[] args) {
        for (int n : new int[] { -128, 127, 128, 0, 42 }) {
            Integer x = Integer.valueOf(n);
            Integer y = Integer.valueOf(n);
            System.out.println(n + " identitas sama? " + (x == y));
        }
    }
}
```

**Yang terjadi:** -128, 127, 0, 42 biasanya identitas sama. 128 biasanya tidak. Autoboxing memakai `valueOf`, jadi `Integer x = 127; Integer y = 127; x == y` sering true.

**Biasanya digabungkan dengan:** penjelasan bug “di laptop dosen jalan”.

**Jangan:** menulis tes unit yang mengandalkan `==` pada wrapper.

---

### null pada wrapper

**Tipe:** nilai referensi

**Untuk apa:** menandai “tidak ada angka”. Primitif tidak bisa ini.

**Contoh implementasi:**

```java
public class NullWrapper {
    static Integer diskon; // default null

    public static void main(String[] args) {
        System.out.println("diskon field: " + diskon);
        if (diskon == null) {
            System.out.println("Belum ada diskon");
        } else {
            System.out.println("Diskon % " + diskon);
        }
        Integer poin = null;
        try {
            System.out.println(poin + 1);
        } catch (NullPointerException ex) {
            System.out.println("poin+1 gagal karena unboxing");
        }
    }
}
```

**Yang terjadi:** field `diskon` null. Cabang “Belum ada diskon” tercetak. `poin + 1` unbox null → NPE.

**Biasanya digabungkan dengan:** `Optional<Integer>` (bab 07) jika alurnya panjang.

**Jangan:** memberi default `0` pada wrapper jika `0` berarti “diskon nol persen” yang sah — kamu kehilangan arti “belum diisi”.

---

### BigDecimal (uang)

**Tipe:** class (`java.math.BigDecimal`)

**Untuk apa:** desimal basis 10 yang presisi, untuk uang dan pajak.

**Contoh implementasi:**

```java
import java.math.BigDecimal;
import java.math.RoundingMode;

public class ContohBigDecimal {
    public static void main(String[] args) {
        BigDecimal harga = new BigDecimal("10000.00");
        BigDecimal pajak = new BigDecimal("0.11");
        BigDecimal total = harga.add(harga.multiply(pajak)).setScale(2, RoundingMode.HALF_UP);
        System.out.println("Total +11%: " + total);
        System.out.println("0.1 + 0.2 double: " + (0.1 + 0.2));
        System.out.println("0.1 + 0.2 decimal: "
                + new BigDecimal("0.1").add(new BigDecimal("0.2")));
        // new BigDecimal(0.1) berbahaya: 0.1 double sudah kotor
        System.out.println("Jebakan new BigDecimal(0.1): " + new BigDecimal(0.1));
    }
}
```

**Yang terjadi:** total menjadi `11100.00` persis. `0.1 + 0.2` sebagai `BigDecimal` dari **string** adalah `0.3`. Constructor `new BigDecimal(0.1)` menyalin kotoran `double`.

**Biasanya digabungkan dengan:** `setScale`, `RoundingMode`, dan simpan uang sebagai string/angka tetap.

**Jangan:** `new BigDecimal(0.1)`. Jangan memakai `==` pada `BigDecimal` — pakai `compareTo == 0` karena `1.0` dan `1.00` `equals`-nya bisa false.

---

### Operator aritmetika

**Tipe:** operator

**Untuk apa:** `+ - * / %` dan bentuk penugasan `+= -= *= /= %=`, plus `++` `--`.

**Contoh implementasi:**

```java
public class OperatorAritmetika {
    public static void main(String[] args) {
        int stok = 10;
        stok += 5;
        stok--;
        int pre = ++stok;
        int post = stok++;
        System.out.println("stok akhir=" + stok);
        System.out.println("pre=" + pre + " post=" + post);
        System.out.println("sisa 17%5=" + (17 % 5));
        int a = 5;
        a *= 2 + 3;
        System.out.println("a *= 2+3 -> " + a);
    }
}
```

**Yang terjadi:** stok 10+5=15, `--` jadi 14, `++stok` jadi 15 dan `pre=15`, `stok++` memakai 15 lalu stok 16, `post=15`. `17%5=2`. `a *= 2+3` artinya `a = a * (2+3)` = 25, **bukan** `(a*2)+3`.

**Biasanya digabungkan dengan:** loop penghitung, total keranjang.

**Jangan:** menulis `i++` di dalam ekspresi rumit. Jangan lupa prioritas `*=`.

---

### Operator perbandingan

**Tipe:** operator

**Untuk apa:** `>`, `<`, `>=`, `<=`, `==`, `!=` pada primitif; hasilnya `boolean`.

**Contoh implementasi:**

```java
public class OperatorBanding {
    public static void main(String[] args) {
        int stok = 3;
        int minimum = 5;
        System.out.println(stok < minimum);
        System.out.println(stok != 0);
        double x = 0.0;
        double y = -0.0;
        System.out.println("0.0 == -0.0 ? " + (x == y));
        System.out.println("NaN == NaN ? " + (Double.NaN == Double.NaN));
        String a = "Buku";
        String b = new String("Buku");
        System.out.println("String == ? " + (a == b));
        System.out.println("String equals? " + a.equals(b));
    }
}
```

**Yang terjadi:** `3 < 5` true. `0.0 == -0.0` true di Java. `NaN == NaN` false. Dua `String` isi sama boleh `==` false.

**Biasanya digabungkan dengan:** `if`, dan `equals` untuk objek.

**Jangan:** `==` pada `String` atau wrapper. Jangan membandingkan `double` hasil hitung dengan `==`.

---

### Tabel cepat primitif

**Tipe:** ringkasan (bukan API)

**Untuk apa:** memilih tipe tanpa menghafal bit di luar kepala.

| Tipe | Bit | Rentang ringkas | Wrapper | Default field |
| --- | ---: | --- | --- | --- |
| `byte` | 8 | -128 .. 127 | `Byte` | 0 |
| `short` | 16 | ±32 ribu | `Short` | 0 |
| `int` | 32 | ±2,1 miliar | `Integer` | 0 |
| `long` | 64 | sangat besar | `Long` | 0L |
| `float` | 32 | pecahan kasar | `Float` | 0.0f |
| `double` | 64 | pecahan biasa | `Double` | 0.0 |
| `char` | 16 | 0 .. 65535 | `Character` | `\u0000` |
| `boolean` | JVM | true/false | `Boolean` | false |

**Contoh implementasi:**

```java
public class TabelPrimitif {
    public static void main(String[] args) {
        System.out.println("int bytes=" + Integer.BYTES);
        System.out.println("long bytes=" + Long.BYTES);
        System.out.println("double bytes=" + Double.BYTES);
        System.out.println("Pilih int untuk hitungan, long untuk ID/waktu, double untuk sains, BigDecimal untuk uang.");
    }
}
```

**Yang terjadi:** `Integer.BYTES` 4, `Long` 8, `Double` 8. Program mengingatkan pilihan tipe.

**Biasanya digabungkan dengan:** semua file berikutnya — collections membutuhkan wrapper.

**Jangan:** menghafal tabel tanpa menulis program. Ubah `int` jadi `byte` di latihan overflow dan lihat sendiri.

---

Lanjut ke [02 — String dan array](02-string-array.md).
