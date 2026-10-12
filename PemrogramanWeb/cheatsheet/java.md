# Cheatsheet Java

[← Daftar panduan](README.md) · [Ensiklopedia Java](ensiklopedia/java/README.md)

Java mengolah **logika berobjek** yang dikompilasi ke bytecode, lalu dijalankan JVM. File `.java` tidak dibuka di browser. Kamu menulis class, compile dengan `javac`, lalu menjalankan `java`.

Versi cepat ini pintu masuk. Detail tiap tipe, koleksi, dan API ada di [ensiklopedia/java](ensiklopedia/java/README.md).

## Daftar isi

- [Persiapan](#persiapan)
- [Tipe primitif dan wrapper](#tipe-primitif-dan-wrapper)
- [String dan array](#string-dan-array)
- [Kondisi, loop, dan method](#kondisi-loop-dan-method)
- [Class dan object](#class-dan-object)
- [Inheritance dan interface](#inheritance-dan-interface)
- [Collections](#collections)
- [Exception dan file](#exception-dan-file)
- [Stream, Optional, lambda](#stream-optional-lambda)
- [Generics dan enum](#generics-dan-enum)
- [Kesalahan umum](#kesalahan-umum)

## Persiapan

**Untuk apa:** memastikan JDK terpasang, lalu compile dan jalankan satu class.

```bash
java -version
javac -version

# satu file
javac Toko.java
java Toko
```

`javac` menghasilkan `.class`. `java NamaClass` menjalankan `main`. Nama file publik harus sama dengan nama class: `Toko.java` berisi `public class Toko`.

Struktur kecil yang biasa:

```text
src/Toko.java
src/model/Produk.java
```

Paket `model` berarti file di folder `model` dan baris pertama `package model;`.

**Contoh implementasi:** class `Toko` dengan `public static void main(String[] args)` yang mencetak `"Halo toko"`. Compile, jalankan, pastikan teks tampil.

**Biasanya digabungkan dengan:** editor + JDK 17 atau lebih baru. Install dan struktur: [README ensiklopedia](ensiklopedia/java/README.md).

## Tipe primitif dan wrapper

**Untuk apa:** menyimpan angka, huruf, dan benar/salah. Wrapper dipakai saat koleksi butuh object.

```java
int jumlah = 2;
long penduduk = 280_000_000L;
float diskon = 0.1f;
double harga = 45000.0;
char kode = 'B';
boolean tersedia = true;

Integer stokObj = Integer.valueOf(3);
int kembali = stokObj.intValue();
Double rata = Double.valueOf(4.5);
Boolean aktif = Boolean.TRUE;

System.out.println(jumlah + " " + tersedia);
```

`int` paling sering untuk hitungan. `double` untuk pecahan. `boolean` hanya `true`/`false`. Wrapper (`Integer`, `Double`, `Boolean`) bisa `null`; primitif tidak. Autoboxing mengubah `int` ↔ `Integer` otomatis, tetapi `null` yang di-unbox melempar error.

**Contoh implementasi:** `int harga` dan `int jumlah`, hitung `int total = harga * jumlah`, bungkus ke `Integer` hanya jika akan dimasukkan `List<Integer>`.

**Biasanya digabungkan dengan:** array, `ArrayList`, dan field class. Tiap tipe: [01 — primitif dan wrapper](ensiklopedia/java/01-tipe-primitif-wrapper.md).

## String dan array

**Untuk apa:** teks dan daftar berukuran tetap.

```java
String nama = "Buku tulis";
System.out.println(nama.length());
System.out.println(nama.toUpperCase());
System.out.println(nama.contains("Buku"));
System.out.println(nama.substring(0, 4));

String[] daftar = {"Buku", "Pensil", "Tas"};
System.out.println(daftar[0]);
System.out.println(daftar.length);

int[] harga = {45000, 5000, 90000};
harga[1] = 6000;
```

`String` tidak diubah di tempat; `toUpperCase()` mengembalikan string baru. Indeks mulai 0. `daftar.length` tanpa tanda kurung (berbeda dari `nama.length()`). Array tidak memanjang; untuk daftar yang bertambah, pakai `ArrayList`.

**Contoh implementasi:** array `String[] keranjang`, loop `for (String item : keranjang)`, cetak tiap item huruf kecil dengan `toLowerCase()`.

**Biasanya digabungkan dengan:** `split`, `equals` (bukan `==` untuk isi teks), dan Collections. String/array: [02 — string dan array](ensiklopedia/java/02-string-array.md).

## Kondisi, loop, dan method

**Untuk apa:** memilih jalan, mengulang, dan membungkus langkah di dalam class.

```java
public class Kasir {
    public static String labelStok(int stok) {
        if (stok > 0) {
            return "tersedia";
        } else if (stok == 0) {
            return "habis";
        }
        return "data aneh";
    }

    public static int total(int harga, int jumlah) {
        return harga * jumlah;
    }

    public static void main(String[] args) {
        int[] stok = {3, 0, 2};
        for (int s : stok) {
            System.out.println(labelStok(s));
        }
        System.out.println(total(45000, 2));
    }
}
```

`if` memakai `==` untuk angka, `equals` untuk `String`. `for-each` nyaman untuk array/list. Method punya tipe kembalian (`int`, `String`, `void`). `static` dipanggil lewat class, tanpa membuat object.

**Contoh implementasi:** method `formatRupiah(int nilai)` mengembalikan `"Rp" + nilai`, dipanggil dari `main` untuk tiga harga.

**Biasanya digabungkan dengan:** class non-static dan validasi. Kontrol: [03 — kontrol dan method](ensiklopedia/java/03-kontrol-method.md).

## Class dan object

**Untuk apa:** menggabungkan data produk dengan perilakunya.

```java
public class Produk {
    private final String nama;
    private final int harga;

    public Produk(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }

    public String getNama() {
        return nama;
    }

    public int getHarga() {
        return harga;
    }

    public int subtotal(int jumlah) {
        return harga * jumlah;
    }
}
```

`new Produk("Buku", 45000)` membuat object. `this` menunjuk object saat ini. `private` menjaga field; luar class memakai getter. Constructor mengisi data wajib saat dibuat.

**Contoh implementasi:** di `main`, `Produk buku = new Produk("Buku CSS", 40000);` lalu `System.out.println(buku.subtotal(2));`.

**Biasanya digabungkan dengan:** `List<Produk>` dan inheritance. OOP dasar: [04 — class dan inheritance](ensiklopedia/java/04-oop-class-inheritance.md).

## Inheritance dan interface

**Untuk apa:** berbagi perilaku, atau menjanjikan method tanpa merinci cara.

```java
public abstract class Barang {
    protected String nama;

    public Barang(String nama) {
        this.nama = nama;
    }

    public abstract int hargaAkhir();
}

public class Buku extends Barang {
    private final int harga;

    public Buku(String nama, int harga) {
        super(nama);
        this.harga = harga;
    }

    @Override
    public int hargaAkhir() {
        return harga;
    }
}

public interface Diskon {
    int setelahDiskon(int harga);
}
```

`extends` mewarisi class. `super` memanggil constructor induk. `@Override` menandai method yang menimpa milik induk. `abstract` belum lengkap; anak wajib mengisi. `interface` adalah kontrak; class menulis `implements`. Tiap `public class` di file sendiri (`Barang.java`, `Buku.java`).

**Contoh implementasi:** `Buku` dan `Tas` extends `Barang`, masing-masing `hargaAkhir()`, lalu array `Barang[]` dicetak tanpa peduli tipe konkret.

**Biasanya digabungkan dengan:** polimorfisme dan Collections. Warisan: [04 — class dan inheritance](ensiklopedia/java/04-oop-class-inheritance.md).

## Collections

**Untuk apa:** daftar, himpunan unik, dan peta kunci-nilai yang memanjang sendiri.

```java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

List<String> nama = new ArrayList<>();
nama.add("Buku");
nama.add("Pensil");
System.out.println(nama.get(0));

Set<Integer> id = new HashSet<>();
id.add(1);
id.add(1); // tetap satu

Map<String, Integer> stok = new HashMap<>();
stok.put("Buku", 3);
System.out.println(stok.getOrDefault("Tas", 0));
```

`List` berurut, boleh duplikat (`ArrayList` umum, `LinkedList` jika banyak sisip di tengah). `Set` unik (`HashSet` cepat, `TreeSet` terurut). `Map` kunci → nilai (`HashMap` umum). Tulis tipe di kiri sebagai interface (`List`), kanan sebagai implementasi.

**Contoh implementasi:** `List<Produk>` keranjang, `add` tiga produk, loop hitung total `getHarga()`.

**Biasanya digabungkan dengan:** generics dan stream. Koleksi: [05 — List Set Map](ensiklopedia/java/05-collections-list-set-map.md).

## Exception dan file

**Untuk apa:** menangkap kegagalan, dan membaca/menulis teks.

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class CatatanToko {
    public static void main(String[] args) {
        Path path = Path.of("data", "catatan.txt");
        try {
            Files.createDirectories(path.getParent());
            Files.writeString(path, "Halo toko\n");
            String teks = Files.readString(path);
            System.out.println(teks);
        } catch (IOException e) {
            System.err.println("Gagal berkas: " + e.getMessage());
        }
    }
}
```

`try/catch` menangkap error yang bisa terjadi. `IOException` wajib ditangani atau dideklarasikan `throws`. Jangan menelan exception kosong. `Files` + `Path` lebih modern daripada `FileReader` mentah untuk tugas singkat.

**Contoh implementasi:** baca `produk.csv` baris per baris dengan `Files.readAllLines`, pecah `split(",")`, cetak kolom nama.

**Biasanya digabungkan dengan:** validasi input dan logging. IO: [06 — exception dan file](ensiklopedia/java/06-exception-file-io.md).

## Stream, Optional, lambda

**Untuk apa:** mengolah isi koleksi tanpa loop panjang, dan menandai nilai yang mungkin kosong.

```java
import java.util.List;
import java.util.Optional;

List<Integer> harga = List.of(45000, 5000, 90000);

int total = harga.stream()
        .filter(n -> n > 10000)
        .mapToInt(n -> n)
        .sum();

Optional<Integer> termurah = harga.stream().min(Integer::compareTo);
termurah.ifPresent(n -> System.out.println("Termurah: " + n));

System.out.println(total);
```

Lambda `n -> n > 10000` adalah fungsi singkat. `filter` menyaring, `map` mengubah, `sum` merangkum. `Optional` menghindari `null` mentah: cek `isPresent` atau `ifPresent`, jangan `get()` membabi buta.

**Contoh implementasi:** `List<Produk>` → `stream()` → `filter(p -> p.getHarga() < 50000)` → `map(Produk::getNama)` → `toList()`.

**Biasanya digabungkan dengan:** `List` dan method reference. Stream: [07 — stream dan lambda](ensiklopedia/java/07-stream-optional-lambda.md).

## Generics dan enum

**Untuk apa:** mengunci tipe koleksi saat compile, dan menamai pilihan tetap.

```java
public enum StatusStok {
    TERSEDIA,
    HABIS,
    PREORDER
}

public class Kotak<T> {
    private T isi;

    public void simpan(T nilai) {
        this.isi = nilai;
    }

    public T ambil() {
        return isi;
    }
}

Kotak<String> label = new Kotak<>();
label.simpan("Buku");

StatusStok status = StatusStok.TERSEDIA;
if (status == StatusStok.HABIS) {
    System.out.println("Jangan dijual");
}
```

`List<Produk>` lebih aman daripada `List` mentah. `T` adalah placeholder tipe. Enum memakai `==` karena tiap nilai unik. Jangan menyimpan status sebagai angka ajaib `0/1/2` jika bisa enum.

**Contoh implementasi:** `enum Kategori { BUKU, ALAT, TAS }` di field `Produk`, lalu `switch (produk.getKategori())`.

**Biasanya digabungkan dengan:** Collections dan `switch`. Generics: [08 — generics dan enum](ensiklopedia/java/08-generics-enum.md).

## Kesalahan umum

- **`==` pada String:** membandingkan referensi, bukan isi. Pakai `equals` atau `Objects.equals`.
- **`NullPointerException`:** object belum di-`new`, atau wrapper `null` di-unbox. Cek null atau pakai `Optional`.
- **Array vs List:** `arr.length` tanpa `()`, `list.size()` dengan `()`.
- **Lupa compile ulang:** mengubah `.java` tetapi menjalankan `.class` lama.
- **`package` tidak cocok folder:** `package model;` wajib di `model/Produk.java`.
- **Raw type:** `List` tanpa `<Produk>` menghilangkan perlindungan compiler.

Resep class toko dan error yang sering muncul: [09 — resep dan kesalahan](ensiklopedia/java/09-resep-dan-kesalahan.md).

Latihan: class `Produk` + `ArrayList<Produk>` + hitung total + tulis nama ke `data/keranjang.txt`.

## Peta ensiklopedia

| Ingin… | Buka |
| --- | --- |
| `int`, `Integer` | [01](ensiklopedia/java/01-tipe-primitif-wrapper.md) |
| `String`, array | [02](ensiklopedia/java/02-string-array.md) |
| `if`, method | [03](ensiklopedia/java/03-kontrol-method.md) |
| class, `interface` | [04](ensiklopedia/java/04-oop-class-inheritance.md) |
| `ArrayList`, `HashMap` | [05](ensiklopedia/java/05-collections-list-set-map.md) |
| `try`, file | [06](ensiklopedia/java/06-exception-file-io.md) |
| stream / lambda | [07](ensiklopedia/java/07-stream-optional-lambda.md) |
| generics / enum | [08](ensiklopedia/java/08-generics-enum.md) |
| resep | [09](ensiklopedia/java/09-resep-dan-kesalahan.md) |

Referensi: [Java SE docs](https://docs.oracle.com/en/java/javase/).
