# 04 — Class, object, inheritance, interface

[← 03 kontrol](03-kontrol-method.md) · [Lanjut 05 collections →](05-collections-list-set-map.md)

Class adalah cetakan. Object adalah data hidup di heap. Inheritance (`extends`) memakai ulang dan menyesuaikan. Interface adalah kontrak. Abstract class adalah cetakan yang tidak lengkap.

## Daftar isi

- [class](#class)
- [new dan object](#new-dan-object)
- [field](#field)
- [constructor](#constructor)
- [constructor overloading](#constructor-overloading)
- [this](#this)
- [this() chaining](#this-chaining)
- [getter dan setter](#getter-dan-setter)
- [enkapsulasi](#enkapsulasi)
- [public](#public)
- [private](#private)
- [protected](#protected)
- [package-private](#package-private)
- [static field](#static-field)
- [extends](#extends)
- [super](#super)
- [super()](#super-constructor)
- [override](#override)
- [@Override](#override-anotasi)
- [overload versus override](#overload-versus-override)
- [polimorfisme](#polimorfisme)
- [instanceof](#instanceof)
- [upcast dan downcast](#upcast-dan-downcast)
- [abstract class](#abstract-class)
- [abstract method](#abstract-method)
- [interface](#interface)
- [implements](#implements)
- [default method](#default-method)
- [static method di interface](#static-method-di-interface)
- [multiple interface](#multiple-interface)
- [final class](#final-class)
- [final method](#final-method)
- [final field](#final-field)
- [record](#record)
- [Object.toString](#objecttostring)
- [Object.equals](#objectequals)
- [Object.hashCode](#objecthashcode)
- [komposisi](#komposisi)
- [inner class](#inner-class)
- [anonymous class](#anonymous-class)

---

### class

**Tipe:** class (deklarasi tipe)

**Untuk apa:** menggabungkan data (field) dan perilaku (method) di bawah satu nama.

**Contoh implementasi:**

```java
public class Barang {
    String nama;
    int harga;

    public static void main(String[] args) {
        Barang b = new Barang();
        b.nama = "Buku Java";
        b.harga = 45000;
        System.out.println(b.nama + " Rp" + b.harga);
    }
}
```

**Yang terjadi:** `class Barang` mendaftarkan tipe baru. `new Barang()` mengalokasikan objek. Field diisi lewat titik. Tanpa assignment, field memakai default (0, `null`).

**Biasanya digabungkan dengan:** constructor, `private` + getter, dan file `Barang.java`.

**Jangan:** menaruh semua data toko di `main` sebagai puluhan variabel lepas jika mereka milik satu konsep. Jangan class tanpa tanggung jawab jelas (`class Manager2FinalNew`).

---

### new dan object

**Tipe:** operator / instance

**Untuk apa:** `new` memanggil constructor dan mengembalikan referensi ke objek di heap.

**Contoh implementasi:**

```java
public class ObjekBaru {
    String merek;

    public static void main(String[] args) {
        ObjekBaru a = new ObjekBaru();
        ObjekBaru b = new ObjekBaru();
        a.merek = "Pensil A";
        b.merek = "Pensil B";
        ObjekBaru c = a;
        c.merek = "Tertukar";
        System.out.println("a=" + a.merek);
        System.out.println("b=" + b.merek);
        System.out.println("a == b ? " + (a == b));
        System.out.println("a == c ? " + (a == c));
    }
}
```

**Yang terjadi:** `a` dan `b` dua objek. `c` **bukan** salinan: ia menunjuk objek yang sama dengan `a`. Mengubah `c.merek` mengubah `a`. `a == b` false, `a == c` true.

**Biasanya digabungkan dengan:** constructor berparameter, dan `null` berarti “belum menunjuk”.

**Jangan:** `new` di dalam loop ketat jika objek bisa dipakai ulang. Jangan mengira assignment objek menyalin field otomatis.

---

### field

**Tipe:** variabel instance (atau static)

**Untuk apa:** menyimpan keadaan objek yang hidup lebih lama dari satu method.

**Contoh implementasi:**

```java
public class FieldKeranjang {
    int jumlahItem;
    int totalHarga;

    void tambah(int harga) {
        jumlahItem++;
        totalHarga += harga;
    }

    public static void main(String[] args) {
        FieldKeranjang k = new FieldKeranjang();
        k.tambah(15000);
        k.tambah(3000);
        System.out.println(k.jumlahItem + " item, Rp" + k.totalHarga);
    }
}
```

**Yang terjadi:** dua kali `tambah` menaikkan field. Setelah `main` selesai, objek bisa dibuang GC. Local di `tambah` (parameter `harga`) hilang tiap panggilan; field tetap.

**Biasanya digabungkan dengan:** `private`, constructor, method yang menjaga invarian (`total` selalu jumlah item).

**Jangan:** field `public` seenaknya di API. Jangan field `static` untuk data yang seharusnya per objek (lihat static field).

---

### constructor

**Tipe:** method khusus (nama = class, tanpa return type)

**Untuk apa:** mengisi objek saat `new`, agar tidak ada barang tanpa nama/harga.

**Contoh implementasi:**

```java
public class ConstructorBarang {
    String nama;
    int harga;

    ConstructorBarang(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }

    public static void main(String[] args) {
        ConstructorBarang b = new ConstructorBarang("Buku", 45000);
        System.out.println(b.nama + " Rp" + b.harga);
        // new ConstructorBarang(); // error: constructor default hilang
    }
}
```

**Yang terjadi:** compiler **tidak** lagi menyediakan constructor kosong begitu kamu menulis constructor sendiri. `this.nama` menunjuk field, `nama` di kanan adalah parameter.

**Biasanya digabungkan dengan:** validasi (`if (harga < 0) throw ...`), dan overloading constructor.

**Jangan:** menamai constructor beda dari class. Jangan menulis `void ConstructorBarang()` — itu method biasa, bukan constructor.

---

### constructor overloading

**Tipe:** beberapa constructor

**Untuk apa:** menyediakan cara buat objek yang lebih pendek (nilai default) dan yang lengkap.

**Contoh implementasi:**

```java
public class CtorOverload {
    String nama;
    int harga;
    int stok;

    CtorOverload(String nama, int harga, int stok) {
        this.nama = nama;
        this.harga = harga;
        this.stok = stok;
    }

    CtorOverload(String nama, int harga) {
        this(nama, harga, 0);
    }

    public static void main(String[] args) {
        CtorOverload a = new CtorOverload("Buku", 45000, 10);
        CtorOverload b = new CtorOverload("Pensil", 3000);
        System.out.println(a.nama + " stok=" + a.stok);
        System.out.println(b.nama + " stok=" + b.stok);
    }
}
```

**Yang terjadi:** constructor dua argumen memanggil yang tiga argumen lewat `this(...)` dengan stok 0. Satu tempat pengisian field.

**Biasanya digabungkan dengan:** `this()` chaining, validasi sekali.

**Jangan:** menduplikasi assignment di setiap constructor. Jangan `this()` di tengah badan — harus baris pertama.

---

### this

**Tipe:** referensi instance

**Untuk apa:** menunjuk objek yang sedang menjalankan method. Memisahkan field dari parameter se-nama.

**Contoh implementasi:**

```java
public class ContohThis {
    String nama;

    ContohThis(String nama) {
        this.nama = nama;
    }

    ContohThis namaiUlang(String nama) {
        this.nama = nama;
        return this;
    }

    void cetak() {
        System.out.println("nama=" + this.nama);
    }

    public static void main(String[] args) {
        new ContohThis("A").namaiUlang("B").cetak();
    }
}
```

**Yang terjadi:** `namaiUlang` mengubah field lalu mengembalikan objek yang sama, sehingga panggilan bisa dirantai. `cetak` menulis `nama=B`.

**Biasanya digabungkan dengan:** setter, fluent API, membedakan bayangan nama.

**Jangan:** memakai `this` di method `static`. Jangan `this = new ...`.

---

### this() chaining

**Tipe:** panggilan constructor

**Untuk apa:** constructor memanggil constructor lain di class yang **sama**.

**Contoh implementasi:**

```java
public class ThisChaining {
    final String sku;
    final String nama;
    final int harga;

    ThisChaining(String sku, String nama, int harga) {
        this.sku = sku;
        this.nama = nama;
        this.harga = harga;
    }

    ThisChaining(String nama, int harga) {
        this("AUTO", nama, harga);
    }

    public static void main(String[] args) {
        ThisChaining x = new ThisChaining("Buku", 1000);
        System.out.println(x.sku + " " + x.nama);
    }
}
```

**Yang terjadi:** constructor pendek menyerahkan `"AUTO"` sebagai SKU. Field `final` bisa diisi karena assignment terjadi di constructor lengkap.

**Biasanya digabungkan dengan:** `final` field, default.

**Jangan:** `this()` dan `super()` bersamaan. Jangan rantai sirkular constructor A memanggil B memanggil A.

---

### getter dan setter

**Tipe:** method

**Untuk apa:** membaca/menulis field `private` dengan peluang validasi dan nanti mengubah implementasi tanpa merusak pemanggil.

**Contoh implementasi:**

```java
public class GetterSetter {
    private String nama;
    private int harga;

    public String getNama() {
        return nama;
    }

    public void setNama(String nama) {
        if (nama == null || nama.isBlank()) {
            throw new IllegalArgumentException("nama wajib");
        }
        this.nama = nama.strip();
    }

    public int getHarga() {
        return harga;
    }

    public void setHarga(int harga) {
        if (harga < 0) {
            throw new IllegalArgumentException("harga negatif");
        }
        this.harga = harga;
    }

    public static void main(String[] args) {
        GetterSetter g = new GetterSetter();
        g.setNama("  Buku  ");
        g.setHarga(45000);
        System.out.println(g.getNama() + " Rp" + g.getHarga());
        try {
            g.setHarga(-1);
        } catch (IllegalArgumentException ex) {
            System.out.println("ditolak: " + ex.getMessage());
        }
    }
}
```

**Yang terjadi:** nama tersimpan `"Buku"` (strip). Harga -1 ditolak, field tetap 45000.

**Biasanya digabungkan dengan:** JavaBean, serialisasi, framework.

**Jangan:** setter kosong yang hanya `this.x = x` pada objek yang seharusnya immutable — lebih baik constructor + getter. Jangan getter yang mengembalikan array/list internal tanpa salinan jika kamu takut diubah pemanggil.

---

### enkapsulasi

**Tipe:** prinsip OOP

**Untuk apa:** menyembunyikan cara data disimpan, hanya membuka operasi yang sah.

**Contoh implementasi:**

```java
public class EnkapsulasiRekening {
    private int saldo;

    public EnkapsulasiRekening(int saldoAwal) {
        if (saldoAwal < 0) {
            throw new IllegalArgumentException("saldo awal");
        }
        this.saldo = saldoAwal;
    }

    public int getSaldo() {
        return saldo;
    }

    public void setor(int n) {
        if (n <= 0) {
            throw new IllegalArgumentException("setor");
        }
        saldo += n;
    }

    public void tarik(int n) {
        if (n <= 0 || n > saldo) {
            throw new IllegalArgumentException("tarik");
        }
        saldo -= n;
    }

    public static void main(String[] args) {
        EnkapsulasiRekening r = new EnkapsulasiRekening(10000);
        r.setor(5000);
        r.tarik(3000);
        System.out.println(r.getSaldo());
        // r.saldo = -99; // error jika di class lain: private
    }
}
```

**Yang terjadi:** saldo 12000. Tidak ada jalan sah ke saldo negatif. Invarian dijaga di satu class.

**Biasanya digabungkan dengan:** `private` field, method bernama bisnis (`setor`), exception.

**Jangan:** field `public int saldo` lalu validasi di 10 tempat pemanggil.

---

### public

**Tipe:** access modifier

**Untuk apa:** terlihat dari package mana pun.

**Contoh implementasi:**

```java
public class PublicDemo {
    public String merek = "Umum";

    public void sapa() {
        System.out.println("Halo dari " + merek);
    }

    public static void main(String[] args) {
        new PublicDemo().sapa();
    }
}
```

**Yang terjadi:** class, field, dan method bisa dipanggil dari mana saja yang mengimpor class ini.

**Biasanya digabungkan dengan:** API class yang memang untuk dipakai luar.

**Jangan:** semua member `public` “supaya mudah”. Itu merusak enkapsulasi.

---

### private

**Tipe:** access modifier

**Untuk apa:** hanya class itu sendiri yang boleh menyentuh.

**Contoh implementasi:**

```java
public class PrivateDemo {
    private int pin = 1234;

    private boolean cocok(int tebakan) {
        return tebakan == pin;
    }

    public boolean masuk(int tebakan) {
        return cocok(tebakan);
    }

    public static void main(String[] args) {
        PrivateDemo p = new PrivateDemo();
        System.out.println(p.masuk(1234));
        System.out.println(p.masuk(0));
        // System.out.println(p.pin); // hanya error jika dari class lain
    }
}
```

**Yang terjadi:** pemanggil luar memakai `masuk`, tidak membaca `pin` langsung (dari class lain). `cocok` tersembunyi.

**Biasanya digabungkan dengan:** helper internal, field.

**Jangan:** `private` pada class top-level — tidak legal. Class top-level: `public` atau package-private.

---

### protected

**Tipe:** access modifier

**Untuk apa:** terlihat di package yang sama **dan** di subclass (meski beda package).

**Contoh implementasi:**

```java
public class ProtectedInduk {
    protected int diskonPersen = 10;

    protected int setelahDiskon(int harga) {
        return harga - harga * diskonPersen / 100;
    }

    public static void main(String[] args) {
        System.out.println(new AnakToko().setelahDiskon(10000));
    }
}

class AnakToko extends ProtectedInduk {
    void naikkan() {
        diskonPersen = 15;
    }
}
```

**Yang terjadi:** `AnakToko` mengubah `diskonPersen` lalu `setelahDiskon(10000)` = 8500 jika `naikkan` dipanggil; di `main` tanpa `naikkan` hasil 9000. Class lain di package yang sama juga bisa menyentuh `protected`.

**Biasanya digabungkan dengan:** kerangka inheritance, method hook.

**Jangan:** `protected` pada field yang sebenarnya detail implementasi — subclass bisa merusak invarian. Lebih aman method `protected`.

---

### package-private

**Tipe:** access default (tanpa kata)

**Untuk apa:** terlihat hanya di package yang sama.

**Contoh implementasi:**

```java
public class PackagePrivateDemo {
    String catatanInternal = "hanya package";

    public static void main(String[] args) {
        System.out.println(new PackagePrivateDemo().catatanInternal);
    }
}
```

**Yang terjadi:** class lain di package `toko` bisa membaca `catatanInternal`. Class di `toko.web` tidak, meski mengimpor.

**Biasanya digabungkan dengan:** class pembantu satu paket, tes di package yang sama (pola lama).

**Jangan:** mengira “tanpa modifier = protected”. Default lebih ketat dari `protected` terhadap subclass lintas package.

---

### static field

**Tipe:** variabel class

**Untuk apa:** satu nilai dibagi semua instance: konstanta, penghitung objek, cache sederhana.

**Contoh implementasi:**

```java
public class StaticField {
    static int buatan = 0;
    String nama;

    StaticField(String nama) {
        this.nama = nama;
        buatan++;
    }

    public static void main(String[] args) {
        new StaticField("A");
        new StaticField("B");
        System.out.println("jumlah objek=" + StaticField.buatan);
        System.out.println("PI util=" + Math.PI);
    }
}
```

**Yang terjadi:** dua `new` menaikkan `buatan` ke 2. Field itu hidup di class, bukan di objek A atau B.

**Biasanya digabungkan dengan:** `public static final` konstanta (`MAX_STOK`).

**Jangan:** `static` untuk keranjang belanja pengguna — semua user berbagi. Itu bug klasik web/desktop.

---

### extends

**Tipe:** pewarisan class

**Untuk apa:** subclass mendapatkan field/method induk, lalu menambah atau menyesuaikan.

**Contoh implementasi:**

```java
public class ExtendsDemo {
    public static void main(String[] args) {
        Buku b = new Buku("Java", 45000, 400);
        b.cetak();
        System.out.println("halaman=" + b.halaman);
    }
}

class Produk {
    String nama;
    int harga;

    Produk(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }

    void cetak() {
        System.out.println(nama + " Rp" + harga);
    }
}

class Buku extends Produk {
    int halaman;

    Buku(String nama, int harga, int halaman) {
        super(nama, harga);
        this.halaman = halaman;
    }
}
```

**Yang terjadi:** `Buku` punya `nama`, `harga`, `cetak`, plus `halaman`. `super(...)` mengisi bagian `Produk`. Satu class hanya boleh `extends` satu class.

**Biasanya digabungkan dengan:** `super`, override, polimorfisme.

**Jangan:** inheritance dalam hanya untuk memakai ulang dua method — pertimbangkan komposisi. Jangan rantai warisan 6 tingkat.

---

### super

**Tipe:** referensi induk

**Untuk apa:** memanggil method atau field induk, terutama saat override ingin menambah bukan mengganti total.

**Contoh implementasi:**

```java
public class SuperMethod {
    public static void main(String[] args) {
        new KasirMember("Haikal").sapa();
    }
}

class Kasir {
    void sapa() {
        System.out.println("Selamat datang");
    }
}

class KasirMember extends Kasir {
    String nama;

    KasirMember(String nama) {
        this.nama = nama;
    }

    @Override
    void sapa() {
        super.sapa();
        System.out.println("Member: " + nama);
    }
}
```

**Yang terjadi:** `sapa` anak memanggil `sapa` induk dulu, lalu menambah baris member. Tanpa `super.sapa()`, sapaan umum hilang.

**Biasanya digabungkan dengan:** `@Override`, constructor `super()`.

**Jangan:** `super.super.method()` — tidak ada. Jangan `super` di context static.

---

### super() constructor

**Tipe:** panggilan constructor induk

**Untuk apa:** wajib (eksplisit atau implisit) agar bagian induk siap sebelum anak berjalan.

**Contoh implementasi:**

```java
public class SuperCtor {
    public static void main(String[] args) {
        new Anak("pensil", 3);
    }
}

class Induk {
    String jenis;

    Induk(String jenis) {
        this.jenis = jenis;
        System.out.println("induk jenis=" + jenis);
    }
}

class Anak extends Induk {
    int ukuran;

    Anak(String jenis, int ukuran) {
        super(jenis);
        this.ukuran = ukuran;
        System.out.println("anak ukuran=" + ukuran);
    }
}
```

**Yang terjadi:** output induk dulu, lalu anak. Jika `Induk` tidak punya constructor kosong, `super(...)` **wajib** baris pertama constructor anak. Compiler tidak bisa menyisipkan `super()` tanpa argumen.

**Biasanya digabungkan dengan:** field `final` di induk.

**Jangan:** memakai `this` atau field anak sebelum `super(...)` selesai (aturan inisialisasi). Jangan lupa: `super()` implisit hanya jika induk punya no-arg.

---

### override

**Tipe:** method instance (tanda tangan sama)

**Untuk apa:** mengganti perilaku induk pada subclass. Dipilih saat **runtime** berdasarkan objek sungguhan.

**Contoh implementasi:**

```java
public class OverrideDemo {
    public static void main(String[] args) {
        Pegawai[] daftar = { new Pegawai(), new Manajer() };
        for (Pegawai p : daftar) {
            p.kerja();
        }
    }
}

class Pegawai {
    void kerja() {
        System.out.println("Pegawai: selesaikan tugas");
    }
}

class Manajer extends Pegawai {
    @Override
    void kerja() {
        System.out.println("Manajer: rapat + tugas");
    }
}
```

**Yang terjadi:** elemen bertipe `Pegawai` tetapi objek kedua adalah `Manajer`, jadi `kerja` manajer yang jalan. Ini dinamai dynamic dispatch.

**Biasanya digabungkan dengan:** `@Override`, polimorfisme, interface.

**Jangan:** mengubah parameter sehingga jadi overload, bukan override. Jangan memperketat akses (`public` di induk jadi `private` di anak) — ditolak.

---

### @Override anotasi

**Tipe:** anotasi

**Untuk apa:** meminta compiler memastikan method benar-benar menimpa milik induk/interface.

**Contoh implementasi:**

```java
public class AnotasiOverride {
    public static void main(String[] args) {
        System.out.println(new AnakSalah().nama());
    }
}

class IndukNama {
    String nama() {
        return "induk";
    }
}

class AnakSalah extends IndukNama {
    @Override
    String nama() {
        return "anak";
    }
    // @Override String Nama() { ... } // error: tidak menimpa
}
```

**Yang terjadi:** `nama()` menimpa dengan benar, cetak `anak`. Jika kamu salah ketik `Nama()`, `@Override` membuat `javac` gagal — lebih baik daripada method baru yang tidak pernah dipanggil.

**Biasanya digabungkan dengan:** setiap override, termasuk `toString`/`equals`.

**Jangan:** melewatkan anotasi. Tanpa itu, typo jadi method baru sunyi.

---

### overload versus override

**Tipe:** dua konsep berbeda

**Untuk apa:** overload = nama sama, parameter beda, dipilih **compile-time**. Override = tanda tangan sama di subclass, dipilih **runtime**.

**Contoh implementasi:**

```java
public class OverloadOverride {
    static void cetak(Pegawai2 p) {
        System.out.println("overload pegawai");
    }

    static void cetak(Manajer2 m) {
        System.out.println("overload manajer");
    }

    public static void main(String[] args) {
        Pegawai2 p = new Manajer2();
        cetak(p);
        p.kerja();
    }
}

class Pegawai2 {
    void kerja() {
        System.out.println("kerja pegawai");
    }
}

class Manajer2 extends Pegawai2 {
    @Override
    void kerja() {
        System.out.println("kerja manajer");
    }
}
```

**Yang terjadi:** `cetak(p)` memilih `cetak(Pegawai2)` karena tipe **variabel** `p`. `p.kerja()` memilih `kerja` manajer karena tipe **objek**.

**Biasanya digabungkan dengan:** desain API: jangan andalkan overload untuk perilaku bisnis yang seharusnya override.

**Jangan:** mengira overload bersifat polimorfik.

---

### polimorfisme

**Tipe:** prinsip OOP

**Untuk apa:** merawat banyak tipe lewat satu tipe induk/interface.

**Contoh implementasi:**

```java
public class Polimorfisme {
    public static void main(String[] args) {
        Bentuk[] bentuk = { new Kotak(3), new Lingkaran(2) };
        double luas = 0;
        for (Bentuk b : bentuk) {
            luas += b.luas();
        }
        System.out.println("total luas=" + luas);
    }
}

abstract class Bentuk {
    abstract double luas();
}

class Kotak extends Bentuk {
    double sisi;
    Kotak(double sisi) { this.sisi = sisi; }
    @Override double luas() { return sisi * sisi; }
}

class Lingkaran extends Bentuk {
    double r;
    Lingkaran(double r) { this.r = r; }
    @Override double luas() { return Math.PI * r * r; }
}
```

**Yang terjadi:** loop tidak peduli kotak atau lingkaran. Menambah `Segitiga` tidak mengubah loop, hanya array.

**Biasanya digabungkan dengan:** abstract/interface, collections `List<Bentuk>`.

**Jangan:** `if (b instanceof Kotak)` beruntun di setiap operasi — itu menolak manfaat polimorfisme. Taruh perilaku di method override.

---

### instanceof

**Tipe:** operator

**Untuk apa:** menanyakan apakah objek adalah tipe tertentu (atau subclass-nya). `null instanceof T` selalu false.

**Contoh implementasi:**

```java
public class InstanceofDemo {
    public static void main(String[] args) {
        Object x = "Buku";
        Object y = Integer.valueOf(5);
        Object z = null;
        System.out.println(x instanceof String);
        System.out.println(y instanceof String);
        System.out.println(z instanceof String);
        if (x instanceof String s) {
            System.out.println("panjang=" + s.length());
        }
    }
}
```

**Yang terjadi:** `"Buku"` true. `Integer` false. `null` false (tidak NPE). Pattern matching `instanceof String s` (Java 16+) mengisi `s` tanpa cast terpisah.

**Biasanya digabungkan dengan:** downcast aman, `equals`.

**Jangan:** `instanceof` di loop bisnis yang seharusnya virtual method. Jangan `obj instanceof T` lalu cast ke tipe lain.

---

### upcast dan downcast

**Tipe:** konversi referensi

**Untuk apa:** upcast (anak → induk) selalu aman, implisit. Downcast (induk → anak) butuh cast dan bisa `ClassCastException`.

**Contoh implementasi:**

```java
public class CastObjek {
    public static void main(String[] args) {
        Produk2 p = new Buku2("Java", 400);
        p.info();
        if (p instanceof Buku2 b) {
            System.out.println("halaman=" + b.halaman);
        }
        Produk2 lain = new Produk2("Umum");
        try {
            Buku2 salah = (Buku2) lain;
            System.out.println(salah.halaman);
        } catch (ClassCastException ex) {
            System.out.println("cast gagal: " + ex.getClass().getSimpleName());
        }
    }
}

class Produk2 {
    String nama;
    Produk2(String nama) { this.nama = nama; }
    void info() { System.out.println(nama); }
}

class Buku2 extends Produk2 {
    int halaman;
    Buku2(String nama, int halaman) {
        super(nama);
        this.halaman = halaman;
    }
}
```

**Yang terjadi:** `Buku2` ditampung sebagai `Produk2` (upcast). Pattern matching mengambil `halaman`. Cast `Produk2` biasa ke `Buku2` meledak.

**Biasanya digabungkan dengan:** `instanceof`, polimorfisme.

**Jangan:** downcast tanpa cek. Jangan merancang API yang memaksa pemanggil cast terus-menerus.

---

### abstract class

**Tipe:** class

**Untuk apa:** cetakan yang tidak bisa di-`new`, bisa punya field, constructor, method konkret, dan method abstract.

**Contoh implementasi:**

```java
public class AbstractClassDemo {
    public static void main(String[] args) {
        Karyawan k = new Tetap("Siti", 8_000_000);
        System.out.println(k.nama + " gaji=" + k.gajiBulanan());
        // new Karyawan("X"); // error: abstract
    }
}

abstract class Karyawan {
    String nama;
    Karyawan(String nama) { this.nama = nama; }
    abstract int gajiBulanan();
    void absen() { System.out.println(nama + " absen"); }
}

class Tetap extends Karyawan {
    int gaji;
    Tetap(String nama, int gaji) {
        super(nama);
        this.gaji = gaji;
    }
    @Override int gajiBulanan() { return gaji; }
}
```

**Yang terjadi:** `Tetap` wajib mengisi `gajiBulanan`. `absen` diwarisi jadi. Constructor induk tetap dipanggil.

**Biasanya digabungkan dengan:** template method: method konkret memanggil langkah abstract.

**Jangan:** abstract class jika tidak ada kode bersama — pakai interface. Jangan `new` abstract.

---

### abstract method

**Tipe:** method tanpa badan (di class abstract / interface)

**Untuk apa:** memaksa subclass menyediakan implementasi.

**Contoh implementasi:**

```java
public class AbstractMethodDemo {
    public static void main(String[] args) {
        Diskon[] d = { new DiskonPersen(10), new DiskonNominal(2000) };
        int harga = 20000;
        for (Diskon x : d) {
            System.out.println(x.terapkan(harga));
        }
    }
}

abstract class Diskon {
    abstract int terapkan(int harga);
}

class DiskonPersen extends Diskon {
    int persen;
    DiskonPersen(int persen) { this.persen = persen; }
    @Override int terapkan(int harga) { return harga - harga * persen / 100; }
}

class DiskonNominal extends Diskon {
    int potong;
    DiskonNominal(int potong) { this.potong = potong; }
    @Override int terapkan(int harga) { return Math.max(0, harga - potong); }
}
```

**Yang terjadi:** 10% dari 20000 = 18000. Nominal 2000 → 18000. Kontrak sama, rumus beda.

**Biasanya digabungkan dengan:** abstract class / interface.

**Jangan:** method abstract di class konkret. Jangan `private abstract`.

---

### interface

**Tipe:** interface

**Untuk apa:** kontrak kemampuan: “bisa dibayar”, “bisa disimpan”. Class boleh mengimplementasi banyak interface. Field di interface implisit `public static final`. Method abstrak implisit `public abstract`.

**Contoh implementasi:**

```java
public class InterfaceDemo {
    public static void main(String[] args) {
        Pembayaran p = new TransferBank("Haikal");
        p.bayar(75000);
        System.out.println("mata uang default: " + Pembayaran.MATA_UANG);
    }
}

interface Pembayaran {
    String MATA_UANG = "IDR";
    void bayar(int jumlah);
}

class TransferBank implements Pembayaran {
    String atasNama;
    TransferBank(String atasNama) { this.atasNama = atasNama; }

    @Override
    public void bayar(int jumlah) {
        System.out.println("Transfer " + MATA_UANG + jumlah + " ke " + atasNama);
    }
}
```

**Yang terjadi:** `TransferBank` wajib `bayar`. Variabel bertipe `Pembayaran` menampung implementasinya. Konstanta `MATA_UANG` dibagi.

**Biasanya digabungkan dengan:** `implements`, default method, polimorfisme, collections `List<Pembayaran>`.

**Jangan:** menaruh state berubah-ubah di interface (hanya konstanta). Jangan interface 40 method tanpa pecah (Interface Segregation).

---

### implements

**Tipe:** klausa class

**Untuk apa:** menjanjikan class memenuhi semua method abstract interface.

**Contoh implementasi:**

```java
public class ImplementsDemo {
    public static void main(String[] args) {
        Cetak c = new StrukBelanja("Buku", 1);
        c.cetak();
    }
}

interface Cetak {
    void cetak();
}

class StrukBelanja implements Cetak {
    String item;
    int qty;
    StrukBelanja(String item, int qty) {
        this.item = item;
        this.qty = qty;
    }

    @Override
    public void cetak() {
        System.out.println(qty + "x " + item);
    }
}
```

**Yang terjadi:** tanpa `cetak`, class gagal kompilasi (kecuali abstract). `public` wajib karena method interface public.

**Biasanya digabungkan dengan:** beberapa interface dipisah koma.

**Jangan:** menurunkan visibilitas method jadi package-private.

---

### default method

**Tipe:** method di interface (Java 8+)

**Untuk apa:** menambah method ke interface tanpa merusak semua implementasi lama; boleh dioverride.

**Contoh implementasi:**

```java
public class DefaultMethodDemo {
    public static void main(String[] args) {
        Logger log = new LoggerLayar();
        log.info("toko buka");
        log.error("stok negatif");
    }
}

interface Logger {
    void info(String pesan);

    default void error(String pesan) {
        info("[ERROR] " + pesan);
    }
}

class LoggerLayar implements Logger {
    @Override
    public void info(String pesan) {
        System.out.println(pesan);
    }
}
```

**Yang terjadi:** `LoggerLayar` hanya menulis `info`. `error` memakai default: mencetak `[ERROR] stok negatif`.

**Biasanya digabungkan dengan:** evolusi API, dan override jika default tidak cocok.

**Jangan:** default method yang merusak state rumit. Jika dua interface punya default sama, class **wajib** override (konflik).

---

### static method di interface

**Tipe:** method static

**Untuk apa:** utilitas terkait kontrak, dipanggil lewat nama interface.

**Contoh implementasi:**

```java
public class StaticInterfaceDemo {
    public static void main(String[] args) {
        int bersih = Harga.bersih(10000, 11);
        System.out.println(bersih);
    }
}

interface Harga {
    static int bersih(int kotor, int pajakPersen) {
        return kotor + kotor * pajakPersen / 100;
    }
}
```

**Yang terjadi:** `Harga.bersih` = 11100. Tidak diwariskan ke instance sebagai method yang dipanggil `obj.bersih(...)`.

**Biasanya digabungkan dengan:** factory `static Of(...) ` di interface modern.

**Jangan:** mengira implementasi class otomatis punya `bersih` sebagai instance method.

---

### multiple interface

**Tipe:** class mengimplementasi banyak kontrak

**Untuk apa:** memadukan kemampuan tanpa multiple inheritance class (yang Java larang).

**Contoh implementasi:**

```java
public class MultiInterface {
    public static void main(String[] args) {
        ProdukDigital p = new ProdukDigital("E-book", 50000);
        p.bayar(p.harga);
        p.kirimEmail("a@b.c");
    }
}

interface BisaDibayar { void bayar(int jumlah); }
interface BisaDikirim { void kirimEmail(String ke); }

class ProdukDigital implements BisaDibayar, BisaDikirim {
    String nama;
    int harga;
    ProdukDigital(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }
    @Override public void bayar(int jumlah) {
        System.out.println("bayar " + jumlah + " untuk " + nama);
    }
    @Override public void kirimEmail(String ke) {
        System.out.println("kirim " + nama + " ke " + ke);
    }
}
```

**Yang terjadi:** satu objek memenuhi dua peran. Bisa ditampung sebagai `BisaDibayar` atau `BisaDikirim` sesuai kebutuhan method.

**Biasanya digabungkan dengan:** interface sempit.

**Jangan:** class yang implements 15 interface — bau desain.

---

### final class

**Tipe:** modifier class

**Untuk apa:** melarang `extends`. Dipakai pada class yang algoritmanya tidak boleh diubah (contoh: `String` final).

**Contoh implementasi:**

```java
public final class FinalClassDemo {
    final String kode;

    FinalClassDemo(String kode) {
        this.kode = kode;
    }

    public static void main(String[] args) {
        System.out.println(new FinalClassDemo("OK").kode);
    }
}
// class Turunan extends FinalClassDemo {} // error
```

**Yang terjadi:** class bisa dipakai, tidak bisa diwarisi. Berguna untuk keamanan (`String`) dan kejelasan.

**Biasanya digabungkan dengan:** class utilitas, value object.

**Jangan:** menandai final semua class “karena rapi” jika tugas meminta inheritance.

---

### final method

**Tipe:** modifier method

**Untuk apa:** melarang override, menjaga langkah kritis di kerangka inheritance.

**Contoh implementasi:**

```java
public class FinalMethodDemo {
    public static void main(String[] args) {
        new AnakBayar().proses(1000);
    }
}

class KerangkaBayar {
    public final void proses(int n) {
        validasi(n);
        eksekusi(n);
    }
    void validasi(int n) {
        if (n <= 0) throw new IllegalArgumentException();
    }
    void eksekusi(int n) {
        System.out.println("bayar default " + n);
    }
}

class AnakBayar extends KerangkaBayar {
    @Override
    void eksekusi(int n) {
        System.out.println("bayar e-wallet " + n);
    }
}
```

**Yang terjadi:** anak boleh ganti `eksekusi`, tidak boleh ganti `proses`. Alur validasi+eksekusi tetap.

**Biasanya digabungkan dengan:** template method.

**Jangan:** `final` semua method lalu masih menyediakan class untuk di-extend — tidak ada yang bisa disesuaikan.

---

### final field

**Tipe:** modifier field

**Untuk apa:** referensi/nilai field hanya diisi sekali (constructor atau initializer).

**Contoh implementasi:**

```java
public class FinalField {
    final String id;
    final java.util.List<String> isi = new java.util.ArrayList<>();

    FinalField(String id) {
        this.id = id;
    }

    public static void main(String[] args) {
        FinalField f = new FinalField("TRX-1");
        f.isi.add("Buku");
        // f.id = "x"; // error
        // f.isi = new ArrayList<>(); // error
        System.out.println(f.id + " " + f.isi);
    }
}
```

**Yang terjadi:** `id` terkunci. `isi` referensinya terkunci, tetapi **list masih bisa `add`**.

**Biasanya digabungkan dengan:** immutable class (list diganti `List.copyOf` / unmodifiable).

**Jangan:** mengira `final List` = list beku.

---

### record

**Tipe:** class ringkas (Java 16+)

**Untuk apa:** wadah data immutable: constructor, getter, `equals`, `hashCode`, `toString` digenerate.

**Contoh implementasi:**

```java
public class RecordDemo {
    record Barang(String nama, int harga) {
        Barang {
            if (harga < 0) {
                throw new IllegalArgumentException("harga");
            }
            nama = nama.strip();
        }
    }

    public static void main(String[] args) {
        Barang a = new Barang("  Buku  ", 45000);
        Barang b = new Barang("Buku", 45000);
        System.out.println(a);
        System.out.println(a.nama() + " " + a.harga());
        System.out.println(a.equals(b));
    }
}
```

**Yang terjadi:** compact constructor men-strip nama dan menolak harga negatif. `a.equals(b)` true. `toString` berisi nama komponen. Tidak ada `getNama` — accessor `nama()`.

**Biasanya digabungkan dengan:** DTO, kunci `Map`, pola data transfer.

**Jangan:** record jika objek harus berubah-ubah. Jangan field mutable di dalam record tanpa salinan.

---

### Object.toString

**Tipe:** method (`Object`, sering dioverride)

**Untuk apa:** representasi teks untuk debug dan `println`.

**Contoh implementasi:**

```java
public class ToStringDemo {
    String nama;
    int harga;

    ToStringDemo(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }

    @Override
    public String toString() {
        return "Barang(" + nama + ", Rp" + harga + ")";
    }

    public static void main(String[] args) {
        System.out.println(new ToStringDemo("Teh", 5000));
        System.out.println(new Object());
    }
}
```

**Yang terjadi:** override mencetak `Barang(Teh, Rp5000)`. `Object` mentah mencetak `java.lang.Object@...`.

**Biasanya digabungkan dengan:** log, `StringBuilder`, record (otomatis).

**Jangan:** `toString` yang melempar atau memanggil jaringan. Jangan memakai `toString` sebagai format file resmi yang kaku.

---

### Object.equals

**Tipe:** method

**Untuk apa:** kesamaan nilai. Default: identitas (`==`). Override bersama `hashCode`.

**Contoh implementasi:**

```java
import java.util.Objects;

public class EqualsDemo {
    private final String sku;

    EqualsDemo(String sku) {
        this.sku = sku;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof EqualsDemo other)) return false;
        return Objects.equals(sku, other.sku);
    }

    @Override
    public int hashCode() {
        return Objects.hashCode(sku);
    }

    public static void main(String[] args) {
        EqualsDemo a = new EqualsDemo("BK-1");
        EqualsDemo b = new EqualsDemo("BK-1");
        System.out.println(a == b);
        System.out.println(a.equals(b));
        System.out.println(a.equals(null));
    }
}
```

**Yang terjadi:** `==` false, `equals` true, `equals(null)` false tanpa NPE.

**Biasanya digabungkan dengan:** `HashSet`, `HashMap` key, `Objects.equals`.

**Jangan:** override `equals` tanpa `hashCode`. Jangan memakai `==` pada field `String` di dalam `equals`.

---

### Object.hashCode

**Tipe:** method

**Untuk apa:** angka sebaran untuk hash table. Kontrak: jika `equals` true, `hashCode` **wajib** sama.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class HashCodeDemo {
    final String sku;

    HashCodeDemo(String sku) { this.sku = sku; }

    @Override public boolean equals(Object o) {
        return o instanceof HashCodeDemo h && Objects.equals(sku, h.sku);
    }

    @Override public int hashCode() {
        return Objects.hashCode(sku);
    }

    public static void main(String[] args) {
        Set<HashCodeDemo> set = new HashSet<>();
        set.add(new HashCodeDemo("BK-1"));
        System.out.println(set.contains(new HashCodeDemo("BK-1")));
        System.out.println(new HashCodeDemo("BK-1").hashCode());
    }
}
```

**Yang terjadi:** `contains` true karena `equals`+`hashCode` konsisten. Tanpa `hashCode` override, `contains` sering false meski `equals` true.

**Biasanya digabungkan dengan:** `HashMap`, `HashSet` (bab 05).

**Jangan:** `hashCode` acak tiap panggilan. Jangan memasukkan objek mutable ke `HashSet` lalu mengubah field yang dipakai `equals`.

---

### komposisi

**Tipe:** desain (“has-a”)

**Untuk apa:** objek punya objek lain, daripada memaksa “is-a” lewat inheritance.

**Contoh implementasi:**

```java
public class KomposisiDemo {
    public static void main(String[] args) {
        Keranjang k = new Keranjang();
        k.masuk(new Item("Buku", 45000));
        k.masuk(new Item("Pensil", 3000));
        System.out.println(k.total());
    }
}

class Item {
    final String nama;
    final int harga;
    Item(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }
}

class Keranjang {
    private final java.util.List<Item> isi = new java.util.ArrayList<>();
    void masuk(Item i) { isi.add(i); }
    int total() {
        int s = 0;
        for (Item i : isi) s += i.harga;
        return s;
    }
}
```

**Yang terjadi:** `Keranjang` **punya** daftar `Item`, bukan subclass `ArrayList`. Total 48000. Kamu mengontrol method yang dibuka.

**Biasanya digabungkan dengan:** collections, enkapsulasi.

**Jangan:** `class Keranjang extends ArrayList<Item>` hanya agar bisa `add`. Itu membocorkan semua method list.

---

### inner class

**Tipe:** class di dalam class

**Untuk apa:** tipe yang erat dengan luar; inner non-static menyimpan referensi ke instance luar.

**Contoh implementasi:**

```java
public class InnerClassDemo {
    String toko = "Belajar";

    class Etiket {
        String barang;
        Etiket(String barang) { this.barang = barang; }
        void cetak() {
            System.out.println(barang + " @ " + toko);
        }
    }

    public static void main(String[] args) {
        InnerClassDemo luar = new InnerClassDemo();
        Etiket e = luar.new Etiket("Buku");
        e.cetak();
    }
}
```

**Yang terjadi:** `Etiket` membaca `toko` milik luar. Sintaks `luar.new Etiket` wajib untuk inner non-static dari `static main`.

**Biasanya digabungkan dengan:** builder, iterator kecil.

**Jangan:** inner class jika static nested cukup (tidak butuh `this` luar) — static nested tidak menahan objek luar hidup.

---

### anonymous class

**Tipe:** class tanpa nama

**Untuk apa:** implementasi interface/class sekali pakai, sebelum lambda (bab 07) lebih pendek.

**Contoh implementasi:**

```java
public class AnonymousDemo {
    public static void main(String[] args) {
        Runnable r = new Runnable() {
            @Override
            public void run() {
                System.out.println("jalan sekali");
            }
        };
        r.run();

        Pembanding p = new Pembanding() {
            @Override public int banding(int a, int b) {
                return a - b;
            }
        };
        System.out.println(p.banding(3, 5));
    }
}

interface Pembanding {
    int banding(int a, int b);
}
```

**Yang terjadi:** compiler membuat class sintetis. `run` mencetak pesan. `banding` mengembalikan -2. Di Java 8+, `Runnable` dan `Pembanding` (jika SAM) bisa diganti lambda.

**Biasanya digabungkan dengan:** listener lama, `Comparator` sebelum lambda.

**Jangan:** anonymous 80 baris — buat class bernama. Jangan menangkap local non-`final`/non-effectively-final.

---

Lanjut ke [05 — collections](05-collections-list-set-map.md).
