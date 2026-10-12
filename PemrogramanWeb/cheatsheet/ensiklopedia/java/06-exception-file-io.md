# 06 — Exception dan file I/O

[← 05 collections](05-collections-list-set-map.md) · [Lanjut 07 stream →](07-stream-optional-lambda.md)

Exception adalah objek error yang **dilempar** (`throw`) dan bisa **ditangkap** (`catch`). File I/O memakai `Path`/`Files` (modern) atau reader/writer (klasik). Selalu pikirkan: siapa yang menutup resource?

## Daftar isi

- [Exception](#exception)
- [Error versus Exception](#error-versus-exception)
- [checked versus unchecked](#checked-versus-unchecked)
- [try-catch](#try-catch)
- [multi-catch](#multi-catch)
- [finally](#finally)
- [try-with-resources](#try-with-resources)
- [throw](#throw)
- [throws](#throws)
- [exception buatan](#exception-buatan)
- [NullPointerException](#nullpointerexception)
- [IllegalArgumentException](#illegalargumentexception)
- [IndexOutOfBoundsException](#indexoutofboundsexception)
- [NumberFormatException](#numberformatexception)
- [ArithmeticException](#arithmeticexception)
- [ClassCastException](#classcastexception)
- [IOException](#ioexception)
- [FileNotFoundException](#filenotfoundexception)
- [stack trace](#stack-trace)
- [File](#file)
- [Path dan Paths](#path-dan-paths)
- [Files.readString](#filesreadstring)
- [Files.writeString](#fileswritestring)
- [Files.readAllLines](#filesreadalllines)
- [Files.exists](#filesexists)
- [Files.createDirectories](#filescreatedirectories)
- [Files.delete](#filesdelete)
- [Files.copy dan move](#filescopy-dan-move)
- [Files.list](#fileslist)
- [BufferedReader](#bufferedreader)
- [BufferedWriter](#bufferedwriter)
- [PrintWriter](#printwriter)
- [Scanner file](#scanner-file)
- [charset UTF-8](#charset-utf-8)

---

### Exception

**Tipe:** class (`java.lang.Exception`)

**Untuk apa:** mewakili kondisi abnormal yang masih masuk akal ditangani program: file hilang, angka jelek, jaringan putus.

**Contoh implementasi:**

```java
public class ExceptionDasar {
    public static void main(String[] args) {
        try {
            int n = Integer.parseInt("bukan-angka");
            System.out.println(n);
        } catch (Exception ex) {
            System.out.println("tipe=" + ex.getClass().getSimpleName());
            System.out.println("pesan=" + ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `parseInt` melempar `NumberFormatException` (turunan `Exception`). `catch` menelan, program **tidak** mati. `main` selesai normal.

**Biasanya digabungkan dengan:** `getMessage`, `printStackTrace`, exception lebih spesifik daripada `Exception` umum.

**Jangan:** `catch (Exception e) {}` kosong. Jangan menangkap `Exception` di setiap method “supaya aman” — error tersembunyi.

---

### Error versus Exception

**Tipe:** dua cabang `Throwable`

**Untuk apa:** `Error` (mis. `OutOfMemoryError`, `StackOverflowError`) biasanya **jangan** ditangkap: JVM sakit. `Exception` boleh ditangani.

**Contoh implementasi:**

```java
public class ErrorVsException {
    static void rekursi() {
        rekursi();
    }

    public static void main(String[] args) {
        try {
            throw new RuntimeException("masih Exception");
        } catch (RuntimeException ex) {
            System.out.println("tertangkap: " + ex.getMessage());
        }
        System.out.println("Error seperti StackOverflowError jangan dijadikan alur bisnis.");
        // rekursi(); // Error, bukan Exception biasa
    }
}
```

**Yang terjadi:** `RuntimeException` tertangkap. Komentar mengingatkan: rekursi tak berujung adalah `Error`.

**Biasanya digabungkan dengan:** membedakan bug program vs kegagalan lingkungan.

**Jangan:** `catch (Throwable t)` di kode kuliah tanpa alasan. Jangan “menangani” `OutOfMemoryError` dengan retry diam-diam.

---

### checked versus unchecked

**Tipe:** kategori exception

**Untuk apa:** **checked** (`IOException` dan turunan `Exception` selain `RuntimeException`) wajib `catch` atau `throws`. **Unchecked** (`RuntimeException` + `Error`) tidak wajib dideklarasikan.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class CheckedUnchecked {
    static int bagi(int a, int b) {
        return a / b; // ArithmeticException unchecked
    }

    static String baca(Path p) throws IOException {
        return Files.readString(p);
    }

    public static void main(String[] args) {
        try {
            System.out.println(bagi(1, 1));
            System.out.println(baca(Path.of("tidak-ada.txt")));
        } catch (IOException ex) {
            System.out.println("checked: " + ex.getClass().getSimpleName());
        }
    }
}
```

**Yang terjadi:** `bagi` tidak perlu `throws`. `baca` tanpa `throws`/`try` gagal kompilasi. File tiada → `IOException` tertangkap.

**Biasanya digabungkan dengan:** `throws IOException` pada method I/O, unchecked untuk argumen salah.

**Jangan:** membungkus semua checked ke `RuntimeException` tanpa pesan hanya untuk “menghindari throws”. Jangan membuat checked exception untuk kesalahan programmer (`null` argumen) — pakai unchecked.

---

### try-catch

**Tipe:** pernyataan

**Untuk apa:** menjalankan blok, dan jika exception tipe tertentu muncul, pindah ke `catch` lalu lanjut setelah blok.

**Contoh implementasi:**

```java
public class TryCatch {
    public static void main(String[] args) {
        String[] sku = { "BK-1" };
        try {
            System.out.println("mulai");
            System.out.println(sku[5]);
            System.out.println("tidak tercetak");
        } catch (ArrayIndexOutOfBoundsException ex) {
            System.out.println("indeks liar: " + ex.getMessage());
        }
        System.out.println("masih hidup");
    }
}
```

**Yang terjadi:** `mulai` tercetak. `sku[5]` melempar. Baris setelahnya di `try` dilewati. `catch` jalan. `masih hidup` tercetak.

**Biasanya digabungkan dengan:** `finally` / try-with-resources, logging.

**Jangan:** `try` raksasa 200 baris satu `catch (Exception)`. Jangan `catch` lalu `throw ex` tanpa menambah konteks jika kamu tidak mengubah apa-apa — biarkan naik.

---

### multi-catch

**Tipe:** `catch (A | B e)`

**Untuk apa:** satu penanganan untuk beberapa tipe yang tidak se-hierarki langsung.

**Contoh implementasi:**

```java
public class MultiCatch {
    public static void main(String[] args) {
        String s = args.length == 0 ? "abc" : args[0];
        try {
            int n = Integer.parseInt(s);
            System.out.println(100 / n);
        } catch (NumberFormatException | ArithmeticException ex) {
            System.out.println("input/hitung gagal: " + ex.getClass().getSimpleName());
        }
    }
}
```

**Yang terjadi:** `"abc"` → `NumberFormatException`. `"0"` → `ArithmeticException`. Keduanya masuk cabang yang sama.

**Biasanya digabungkan dengan:** API yang melempar dua checked serupa.

**Jangan:** `catch (Exception | RuntimeException)` — `RuntimeException` sudah tercakup. Tipe di multi-catch tidak boleh satu turunan yang lain.

---

### finally

**Tipe:** blok

**Untuk apa:** jalan **hampir selalu** setelah `try`/`catch`: sukses, gagal, bahkan `return` di `try`. Tempat klasik menutup resource (sekarang lebih baik try-with-resources).

**Contoh implementasi:**

```java
public class FinallyDemo {
    static int demo(boolean meledak) {
        try {
            if (meledak) {
                throw new IllegalStateException("boom");
            }
            return 1;
        } catch (IllegalStateException ex) {
            System.out.println("catch");
            return 2;
        } finally {
            System.out.println("finally");
        }
    }

    public static void main(String[] args) {
        System.out.println("hasil=" + demo(false));
        System.out.println("hasil=" + demo(true));
    }
}
```

**Yang terjadi:** kedua jalur mencetak `finally` **sebelum** nilai kembali ke `main`. Hasil 1 lalu 2.

**Biasanya digabungkan dengan:** tutup file lama, ukur waktu.

**Jangan:** `return` di `finally` — menelan exception dari `try`. Jangan kerja panjang di `finally`.

---

### try-with-resources

**Tipe:** pernyataan (`try (Resource r = ...)`)

**Untuk apa:** menutup otomatis objek `AutoCloseable` (`Reader`, `Writer`, `Stream` NIO, `Scanner`, koneksi).

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class TryWithResources {
    public static void main(String[] args) throws IOException {
        Path p = Path.of("latihan-twr.txt");
        Files.writeString(p, "baris1\nbaris2\n");
        try (var reader = Files.newBufferedReader(p, StandardCharsets.UTF_8)) {
            String baris;
            while ((baris = reader.readLine()) != null) {
                System.out.println(baris);
            }
        }
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** file ditulis, dibaca dua baris, `reader.close()` dipanggil meski loop error. File latihan dihapus.

**Biasanya digabungkan dengan:** beberapa resource dipisah `;` di header `try`.

**Jangan:** membuka file di `try` biasa lalu lupa `close` di semua jalur. Jangan menutup `System.in` jika program masih baca keyboard.

---

### throw

**Tipe:** pernyataan

**Untuk apa:** melempar exception sekarang. Menghentikan method kecuali ada `catch` di atasnya.

**Contoh implementasi:**

```java
public class ThrowDemo {
    static int diskon(int harga, int persen) {
        if (harga < 0) {
            throw new IllegalArgumentException("harga negatif: " + harga);
        }
        if (persen < 0 || persen > 100) {
            throw new IllegalArgumentException("persen: " + persen);
        }
        return harga - harga * persen / 100;
    }

    public static void main(String[] args) {
        System.out.println(diskon(10000, 10));
        try {
            diskon(-1, 10);
        } catch (IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** 9000 tercetak. `harga -1` melempar, pesan jelas.

**Biasanya digabungkan dengan:** validasi awal method, exception buatan.

**Jangan:** `throw new Exception()` tanpa pesan. Jangan `throw null` — jadi NPE.

---

### throws

**Tipe:** klausa method

**Untuk apa:** menyatakan method bisa melempar checked exception ke pemanggil.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class ThrowsDemo {
    static String wajibAda(Path p) throws IOException {
        if (!Files.exists(p)) {
            throw new IOException("tidak ketemu: " + p);
        }
        return Files.readString(p);
    }

    public static void main(String[] args) {
        try {
            System.out.println(wajibAda(Path.of("tidak-ada.txt")));
        } catch (IOException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `main` wajib menangani atau juga `throws`. Di sini ditangkap, pesan `tidak ketemu: ...`.

**Biasanya digabungkan dengan:** rantai I/O, `main throws Exception` pada skrip kecil.

**Jangan:** `throws Exception` di API publik yang sebenarnya hanya `IOException`. Jangan `throws` untuk unchecked kecuali dokumentasi.

---

### exception buatan

**Tipe:** class turunan `Exception` / `RuntimeException`

**Untuk apa:** nama error domain: `StokHabisException`, bukan `Exception("stok")` generik.

**Contoh implementasi:**

```java
public class ExceptionBuatan {
    static class StokHabisException extends RuntimeException {
        StokHabisException(String barang) {
            super("Stok habis: " + barang);
        }
    }

    static void jual(String barang, int stok) {
        if (stok <= 0) {
            throw new StokHabisException(barang);
        }
        System.out.println("terjual " + barang);
    }

    public static void main(String[] args) {
        try {
            jual("Buku", 0);
        } catch (StokHabisException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `catch` bisa membedakan stok habis dari NPE. Pesan `Stok habis: Buku`.

**Biasanya digabungkan dengan:** checked jika pemanggil **wajib** memikirkan pulih; unchecked jika bug/aturan bisnis yang jarang dipulihkan.

**Jangan:** hierarki 15 class exception untuk tugas kecil. Jangan lupa constructor `super(pesan)` / `super(pesan, cause)`.

---

### NullPointerException

**Tipe:** class (unchecked)

**Untuk apa:** memanggil member pada referensi `null`, unboxing null, `null.length`, dsb.

**Contoh implementasi:**

```java
public class NpeDemo {
    public static void main(String[] args) {
        String nama = null;
        try {
            System.out.println(nama.length());
        } catch (NullPointerException ex) {
            System.out.println("NPE di length");
        }
        Integer harga = null;
        try {
            int x = harga + 1;
            System.out.println(x);
        } catch (NullPointerException ex) {
            System.out.println("NPE unboxing");
        }
    }
}
```

**Yang terjadi:** dua NPE berbeda sebab. Java 14+ sering menulis *which* referensi null di pesan.

**Biasanya digabungkan dengan:** `Objects.requireNonNull`, `Optional`, penjagaan `if (x == null)`.

**Jangan:** `catch (NullPointerException)` sebagai alur normal. Perbaiki sumber null.

---

### IllegalArgumentException

**Tipe:** class (unchecked)

**Untuk apa:** argumen method tidak memenuhi kontrak: negatif, string kosong, rentang salah.

**Contoh implementasi:**

```java
public class IaeDemo {
    static String sku(String kode) {
        if (kode == null || kode.isBlank()) {
            throw new IllegalArgumentException("kode wajib");
        }
        return kode.strip().toUpperCase();
    }

    public static void main(String[] args) {
        System.out.println(sku(" bk-1 "));
        try {
            sku("  ");
        } catch (IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `"BK-1"` tercetak. Blank ditolak.

**Biasanya digabungkan dengan:** constructor, setter, `Objects.requireNonNull`.

**Jangan:** IAE untuk “file tidak ketemu” — itu I/O. Jangan IAE tanpa menyebut parameter mana.

---

### IndexOutOfBoundsException

**Tipe:** class (unchecked)

**Untuk apa:** indeks array/list/string di luar 0..length-1 (atau sisip > size).

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class IoobeDemo {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>();
        k.add("A");
        try {
            System.out.println(k.get(1));
        } catch (IndexOutOfBoundsException ex) {
            System.out.println("list: " + ex.getMessage());
        }
        try {
            System.out.println("Hi".charAt(5));
        } catch (StringIndexOutOfBoundsException ex) {
            System.out.println("string: " + ex.getClass().getSimpleName());
        }
    }
}
```

**Yang terjadi:** `get(1)` pada size 1 gagal. `charAt(5)` turunan lebih spesifik.

**Biasanya digabungkan dengan:** cek `size()`/`length`, loop benar.

**Jangan:** menangkap ini alih-alih memperbaiki rumus indeks.

---

### NumberFormatException

**Tipe:** class (unchecked, turunan `IllegalArgumentException`)

**Untuk apa:** `parseInt`/`parseDouble`/`valueOf` pada teks yang bukan angka sah.

**Contoh implementasi:**

```java
public class NfeDemo {
    static Integer bacaAman(String s) {
        try {
            return Integer.parseInt(s.strip());
        } catch (NumberFormatException ex) {
            return null;
        }
    }

    public static void main(String[] args) {
        System.out.println(bacaAman("42"));
        System.out.println(bacaAman("42.5"));
        System.out.println(bacaAman(""));
    }
}
```

**Yang terjadi:** 42, lalu dua `null`. Pemanggil harus cek `null`.

**Biasanya digabungkan dengan:** `trim`/`strip`, pesan ke pengguna, `Scanner.hasNextInt`.

**Jangan:** `parseInt` pada input UI tanpa `try` atau validasi.

---

### ArithmeticException

**Tipe:** class (unchecked)

**Untuk apa:** `/` atau `%` nol pada integer, atau `Math.*Exact` overflow.

**Contoh implementasi:**

```java
public class ArithmeticDemo {
    public static void main(String[] args) {
        try {
            System.out.println(10 / 0);
        } catch (ArithmeticException ex) {
            System.out.println("int/0: " + ex.getMessage());
        }
        System.out.println("double/0=" + (10.0 / 0.0));
        try {
            System.out.println(Math.multiplyExact(1_000_000, 1_000_000));
        } catch (ArithmeticException ex) {
            System.out.println("exact overflow");
        }
    }
}
```

**Yang terjadi:** `int/0` ditangkap. `double/0` Infinity tanpa exception. `multiplyExact` 10^12 tidak muat `int` → exception.

**Biasanya digabungkan dengan:** jaga `if (b == 0)`, `long`/`Exact`.

**Jangan:** mengira semua bagi-nol melempar.

---

### ClassCastException

**Tipe:** class (unchecked)

**Untuk apa:** cast referensi ke tipe yang objeknya tidak penuhi.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class CceDemo {
    public static void main(String[] args) {
        Object o = "Buku";
        try {
            Integer n = (Integer) o;
            System.out.println(n);
        } catch (ClassCastException ex) {
            System.out.println("cast gagal");
        }
        List raw = new ArrayList();
        raw.add("teks");
        try {
            Integer x = (Integer) raw.get(0);
            System.out.println(x);
        } catch (ClassCastException ex) {
            System.out.println("raw list berbohong");
        }
    }
}
```

**Yang terjadi:** `"Buku"` bukan `Integer`. Raw list menunda error sampai cast/`get` bertipe.

**Biasanya digabungkan dengan:** `instanceof`, generics (bab 08).

**Jangan:** raw type. Jangan cast “coba-coba” tanpa cek.

---

### IOException

**Tipe:** class (checked)

**Untuk apa:** kegagalan I/O: file hilang, disk penuh, stream tutup, encoding.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class IoExceptionDemo {
    public static void main(String[] args) {
        try {
            Files.readString(Path.of("/folder-yang-mustahil/x.txt"));
        } catch (IOException ex) {
            System.out.println(ex.getClass().getName());
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** turunan seperti `NoSuchFileException` tertangkap sebagai `IOException`. Pesan berisi path.

**Biasanya digabungkan dengan:** `throws`, try-with-resources, `getCause`.

**Jangan:** menelan `IOException` dan lanjut seolah file terbaca. Jangan pesan hanya `"error"`.

---

### FileNotFoundException

**Tipe:** class (checked, turunan `IOException`)

**Untuk apa:** API klasik (`FileInputStream`, `FileReader`) saat path tidak bisa dibuka.

**Contoh implementasi:**

```java
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class FnfeDemo {
    public static void main(String[] args) {
        try (FileInputStream in = new FileInputStream("tidak-ada.bin")) {
            System.out.println(in.read());
        } catch (FileNotFoundException ex) {
            System.out.println("tidak ketemu: " + ex.getMessage());
        } catch (IOException ex) {
            System.out.println("I/O lain: " + ex);
        }
    }
}
```

**Yang terjadi:** constructor `FileInputStream` melempar FNFE. `catch` spesifik jalan dulu (harus sebelum `IOException`).

**Biasanya digabungkan dengan:** `Files.exists` sebagai cek awal, tetapi tetap tangani race.

**Jangan:** menaruh `catch (IOException)` di atas `FileNotFoundException` — tidak kompilasi (unreachable / more specific harus dulu).

---

### stack trace

**Tipe:** keluaran `Throwable`

**Untuk apa:** menelusuri rantai panggilan: **baca dari atas**, cari class-mu, bukan hanya baris JDK.

**Contoh implementasi:**

```java
public class StackTraceDemo {
    static void kasir() {
        hitung();
    }

    static void hitung() {
        Integer x = null;
        System.out.println(x + 1);
    }

    public static void main(String[] args) {
        try {
            kasir();
        } catch (NullPointerException ex) {
            ex.printStackTrace(System.out);
        }
    }
}
```

**Yang terjadi:** jejak `hitung` ← `kasir` ← `main`. Perbaiki `hitung`, bukan `main`, kecuali `main` yang mengirim null.

**Biasanya digabungkan dengan:** `getCause()` untuk exception terbungkus (`ex.initCause` / constructor cause).

**Jangan:** screenshot 80 baris tanpa menandai *Caused by* dan file tugasmu.

---

### File

**Tipe:** class (`java.io.File`)

**Untuk apa:** path gaya lama: ada/tidak, `mkdirs`, `delete`. Banyak kode kuliah masih memakainya. API baru: `Path`.

**Contoh implementasi:**

```java
import java.io.File;
import java.io.IOException;

public class FileKlasik {
    public static void main(String[] args) throws IOException {
        File f = new File("latihan-file.txt");
        System.out.println("absolute=" + f.getAbsolutePath());
        System.out.println("exists=" + f.exists());
        boolean dibuat = f.createNewFile();
        System.out.println("createNewFile=" + dibuat);
        System.out.println("exists sekarang=" + f.exists());
        System.out.println("hapus=" + f.delete());
    }
}
```

**Yang terjadi:** path absolut tercetak (folder kerja JVM). File dibuat sekali, `createNewFile` kedua false jika sudah ada. `delete` true.

**Biasanya digabungkan dengan:** `FileWriter`, cek `isDirectory`.

**Jangan:** mengira `File` berisi isi file. Ia hanya path. Jangan `delete` tanpa cek di tugas yang menyentuh file pengguna.

---

### Path dan Paths

**Tipe:** interface / class (`java.nio.file`)

**Untuk apa:** path modern, bekerja dengan `Files`. `Path.of` (Java 11+) lebih disukai daripada `Paths.get`.

**Contoh implementasi:**

```java
import java.nio.file.Path;

public class PathDemo {
    public static void main(String[] args) {
        Path p = Path.of("data", "stok", "barang.txt");
        System.out.println(p);
        System.out.println("fileName=" + p.getFileName());
        System.out.println("parent=" + p.getParent());
        System.out.println("absolut=" + p.toAbsolutePath());
        Path lain = Path.of("data/stok/../stok/barang.txt").normalize();
        System.out.println("normalize=" + lain);
    }
}
```

**Yang terjadi:** `data/stok/barang.txt` (pemisah OS). `normalize` merapikan `..`. Belum tentu file fisik ada.

**Biasanya digabungkan dengan:** `Files.*`, `resolve`, `relativize`.

**Jangan:** merangkai path dengan `+ "\\"` — pecah di macOS/Linux. Pakai `Path.of` / `resolve`.

---

### Files.readString

**Tipe:** method static (Java 11+)

**Untuk apa:** membaca seluruh file teks ke satu `String`.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class ReadStringDemo {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("ensiklopedia", ".txt");
        Files.writeString(p, "Halo toko\nBaris dua", StandardCharsets.UTF_8);
        String isi = Files.readString(p, StandardCharsets.UTF_8);
        System.out.println(isi);
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** file temp ditulis, dibaca utuh termasuk newline, lalu dihapus.

**Biasanya digabungkan dengan:** file konfigurasi kecil, `strip`, `split`.

**Jangan:** `readString` pada file gigabyte. Jangan lupa charset — default bisa tidak UTF-8 di beberapa API lama (di `Files.readString` tanpa argumen: UTF-8).

---

### Files.writeString

**Tipe:** method static (Java 11+)

**Untuk apa:** menulis teks, default menimpa. Opsi `CREATE`, `APPEND`.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;

public class WriteStringDemo {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("tulis", ".txt");
        Files.writeString(p, "pertama\n");
        Files.writeString(p, "tambahan\n", StandardOpenOption.APPEND);
        System.out.println(Files.readString(p));
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** isi `pertama` plus `tambahan`. Tanpa `APPEND`, tulis kedua menimpa.

**Biasanya digabungkan dengan:** `createDirectories` pada parent, charset.

**Jangan:** append tanpa newline sadar — baris menempel. Jangan tulis ke path yang sama dari dua proses tanpa kunci.

---

### Files.readAllLines

**Tipe:** method static

**Untuk apa:** `List<String>` satu elemen per baris, tanpa karakter newline.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class ReadAllLinesDemo {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("baris", ".txt");
        Files.writeString(p, "Buku,45000\nPensil,3000\n");
        List<String> baris = Files.readAllLines(p);
        for (String b : baris) {
            String[] kol = b.split(",");
            System.out.println(kol[0] + " Rp" + kol[1]);
        }
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** dua baris CSV sederhana tercetak sebagai nama dan harga.

**Biasanya digabungkan dengan:** `split`, `parseInt`, Stream `Files.lines` untuk file besar (lazy).

**Jangan:** `readAllLines` file raksasa. Jangan anggap koma di dalam teks CSV aman tanpa parser.

---

### Files.exists

**Tipe:** method static

**Untuk apa:** cek path ada (ikuti link, opsi bisa diatur).

**Contoh implementasi:**

```java
import java.nio.file.Files;
import java.nio.file.Path;

public class FilesExistsDemo {
    public static void main(String[] args) {
        Path p = Path.of("tidak-ada-" + System.nanoTime() + ".txt");
        System.out.println(Files.exists(p));
        System.out.println(Files.notExists(p));
        Path cwd = Path.of(".").toAbsolutePath();
        System.out.println("cwd ada? " + Files.exists(cwd));
        System.out.println("direktori? " + Files.isDirectory(cwd));
    }
}
```

**Yang terjadi:** file acak false/true untuk exists/notExists. Folder kerja ada dan `isDirectory` true.

**Biasanya digabungkan dengan:** `isRegularFile`, `isReadable`.

**Jangan:** `exists` lalu baca tanpa `try` — file bisa hilang di antaranya. `notExists` false tidak selalu berarti “ada” (tidak bisa ditentukan).

---

### Files.createDirectories

**Tipe:** method static

**Untuk apa:** membuat folder beserta induknya, aman jika sudah ada.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class CreateDirsDemo {
    public static void main(String[] args) throws IOException {
        Path dir = Path.of("latihan-ensiklopedia-java", "data");
        Files.createDirectories(dir);
        Path f = dir.resolve("catatan.txt");
        Files.writeString(f, "ok");
        System.out.println(f.toAbsolutePath());
        Files.deleteIfExists(f);
        Files.deleteIfExists(dir);
        Files.deleteIfExists(dir.getParent());
    }
}
```

**Yang terjadi:** `latihan-ensiklopedia-java/data` terbentuk, file ditulis, lalu dibersihkan dari dalam ke luar.

**Biasanya digabungkan dengan:** `resolve("nama.txt")` sebelum write.

**Jangan:** `createDirectory` (tunggal) jika induk belum ada — gagal. `createDirectories` yang ramah.

---

### Files.delete

**Tipe:** method static

**Untuk apa:** `delete` gagal jika tidak ada (`NoSuchFileException`). `deleteIfExists` mengembalikan boolean.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FilesDeleteDemo {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("hapus", ".txt");
        Files.delete(p);
        System.out.println("deleteIfExists kedua=" + Files.deleteIfExists(p));
        try {
            Files.delete(p);
        } catch (java.nio.file.NoSuchFileException ex) {
            System.out.println("delete ketat gagal jika sudah tiada");
        }
    }
}
```

**Yang terjadi:** file temp dihapus. `deleteIfExists` false. `delete` melempar.

**Biasanya digabungkan dengan:** bersihkan file latihan, `walk` hapus pohon (hati-hati).

**Jangan:** `delete` folder yang masih berisi isi — exception. Jangan hapus path dari input pengguna tanpa validasi.

---

### Files.copy dan move

**Tipe:** method static

**Untuk apa:** salin atau pindah/ganti nama. Opsi `REPLACE_EXISTING`.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardCopyOption;

public class CopyMoveDemo {
    public static void main(String[] args) throws IOException {
        Path a = Files.createTempFile("asal", ".txt");
        Files.writeString(a, "isi");
        Path b = a.resolveSibling("salinan-" + a.getFileName());
        Files.copy(a, b, StandardCopyOption.REPLACE_EXISTING);
        System.out.println("salin=" + Files.readString(b));
        Path c = a.resolveSibling("pindah-" + a.getFileName());
        Files.move(b, c, StandardCopyOption.REPLACE_EXISTING);
        System.out.println("move exists b=" + Files.exists(b) + " c=" + Files.exists(c));
        Files.deleteIfExists(a);
        Files.deleteIfExists(c);
    }
}
```

**Yang terjadi:** isi tersalin. Setelah `move`, `b` tiada, `c` ada.

**Biasanya digabungkan dengan:** backup, ganti nama.

**Jangan:** `copy` tanpa `REPLACE_EXISTING` ke path yang sudah ada — `FileAlreadyExistsException`.

---

### Files.list

**Tipe:** method static (mengembalikan `Stream<Path>`)

**Untuk apa:** isi **langsung** sebuah direktori (bukan rekursif). Wajib ditutup (try-with-resources).

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class FilesListDemo {
    public static void main(String[] args) throws IOException {
        Path dir = Path.of(".").toAbsolutePath().normalize();
        try (var stream = Files.list(dir)) {
            stream.limit(5).forEach(p -> System.out.println(p.getFileName()));
        }
    }
}
```

**Yang terjadi:** sampai lima nama di folder kerja. Stream directory tertutup di akhir `try`.

**Biasanya digabungkan dengan:** `filter(Files::isRegularFile)`, `Files.walk` untuk rekursif.

**Jangan:** `Files.list` tanpa close. Jangan `walk` seluruh disk.

---

### BufferedReader

**Tipe:** class (`java.io.BufferedReader`)

**Untuk apa:** baca teks per baris, buffer agar tidak satu byte per syscall.

**Contoh implementasi:**

```java
import java.io.BufferedReader;
import java.io.IOException;
import java.io.StringReader;

public class BufferedReaderDemo {
    public static void main(String[] args) throws IOException {
        String data = "Buku\nPensil\n";
        try (BufferedReader br = new BufferedReader(new StringReader(data))) {
            String baris;
            while ((baris = br.readLine()) != null) {
                System.out.println("item=" + baris);
            }
        }
    }
}
```

**Yang terjadi:** dua iterasi, `readLine` null menandai habis. Pola sama untuk `Files.newBufferedReader(path)`.

**Biasanya digabungkan dengan:** try-with-resources, `split`.

**Jangan:** `FileReader` tanpa charset di mesin Windows jika file UTF-8. Pakai `InputStreamReader(..., UTF_8)` atau `Files.newBufferedReader`.

---

### BufferedWriter

**Tipe:** class

**Untuk apa:** tulis teks ter-buffer. `newLine()` portabel.

**Contoh implementasi:**

```java
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.StringWriter;

public class BufferedWriterDemo {
    public static void main(String[] args) throws IOException {
        StringWriter tujuan = new StringWriter();
        try (BufferedWriter bw = new BufferedWriter(tujuan)) {
            bw.write("Buku");
            bw.newLine();
            bw.write("Pensil");
            bw.newLine();
        }
        System.out.println(tujuan);
    }
}
```

**Yang terjadi:** setelah `close` (otomatis), buffer dikosongkan ke `StringWriter`. Dua baris tercetak.

**Biasanya digabungkan dengan:** `Files.newBufferedWriter`, loop data.

**Jangan:** lupa flush/close — file tampak kosong. Try-with-resources menangani.

---

### PrintWriter

**Tipe:** class

**Untuk apa:** `print`/`println`/`printf` ke file atau writer. Tidak melempar `IOException` pada `println` (cek `checkError`).

**Contoh implementasi:**

```java
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;

public class PrintWriterDemo {
    public static void main(String[] args) throws IOException {
        StringWriter sw = new StringWriter();
        try (PrintWriter pw = new PrintWriter(sw)) {
            pw.println("Struk");
            pw.printf("Total: %d%n", 48000);
        }
        System.out.print(sw);
    }
}
```

**Yang terjadi:** teks struk terformat terkumpul di `StringWriter`.

**Biasanya digabungkan dengan:** laporan, `PrintWriter(Path, charset)` (Java 10+).

**Jangan:** mengira `println` gagal akan melempar seperti `BufferedWriter.write`. Cek error atau pakai writer yang checked.

---

### Scanner file

**Tipe:** class

**Untuk apa:** tokenisasi file: `hasNext`, `next`, `nextInt`.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class ScannerFileDemo {
    public static void main(String[] args) {
        String csv = "Buku 45000\nPensil 3000\n";
        try (Scanner sc = new Scanner(csv)) {
            while (sc.hasNext()) {
                String nama = sc.next();
                int harga = sc.nextInt();
                System.out.println(nama + " -> " + harga);
            }
        }
    }
}
```

**Yang terjadi:** dua pasangan nama-harga. `hasNext` false mengakhiri. Untuk file nyata: `new Scanner(path, UTF_8)`.

**Biasanya digabungkan dengan:** `hasNextInt` sebelum `nextInt`.

**Jangan:** `Scanner` pada file biner. Jangan campur `nextInt`+`nextLine` tanpa pola bab 03.

---

### charset UTF-8

**Tipe:** `Charset` (`StandardCharsets.UTF_8`)

**Untuk apa:** menyepakati bagaimana byte jadi huruf. Tanpa ini, “Buku” bisa jadi rusak di Windows.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;

public class Utf8Demo {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("utf8", ".txt");
        String teks = "Harga: Rp15.000 — buku pemrograman";
        Files.writeString(p, teks, StandardCharsets.UTF_8);
        String baca = Files.readString(p, StandardCharsets.UTF_8);
        System.out.println(baca.equals(teks));
        System.out.println(baca);
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** `equals` true. Em dash dan titik tetap.

**Biasanya digabungkan dengan:** semua baca/tulis teks, JSON.

**Jangan:** mengandalkan charset default OS. Jangan membuka UTF-8 sebagai `ISO_8859_1` lalu “memperbaiki” dengan replace aneh.

---

Lanjut ke [07 — stream, Optional, lambda](07-stream-optional-lambda.md).
