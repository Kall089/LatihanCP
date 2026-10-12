# Ensiklopedia Cheatsheet Java

Katalog Java untuk kuliah: **tipe, class, interface, dan method dijelaskan satu per satu**. Bukan esai teori. Setiap entri menjawab: **tipe apa, untuk apa, contoh class + `main` yang bisa dibayangkan dijalankan, apa yang terjadi, biasanya digabung dengan apa, dan apa yang jangan dilakukan.**

Bahasa Indonesia mudah. Contoh memakai toko, keranjang, stok, nilai mahasiswa, dan file daftar barang.

[← Cheatsheet utama](../../README.md)

## Cara memakai folder ini

1. Buka file sesuai topik, lalu cari nama di daftar isi.
2. Baca **Untuk apa** dulu, baru salin class contoh.
3. Setiap contoh adalah **satu class terpisah** dengan `public static void main`. Jangan menempelkan semua contoh ke satu file.
4. Simpan file dengan nama yang **sama** dengan class publik: `ContohInt.java` untuk `public class ContohInt`.
5. Kompilasi lalu jalankan (lihat [javac](#javac) dan [java](#java) di bawah).
6. Ubah satu nilai, kompilasi ulang, lihat akibatnya di terminal.

Urutan belajar: **README (JDK & struktur) → 01 tipe → 02 String/array → 03 kontrol/method → 04 OOP → 05 collections → 06 exception/file → 07 stream/lambda → 08 generics/enum → 09 resep**.

## Daftar file

| File | Isi |
| --- | --- |
| [README.md](README.md) | JDK, JRE, JVM, `javac`, `java`, package, struktur project |
| [01-tipe-primitif-wrapper.md](01-tipe-primitif-wrapper.md) | `byte` sampai `boolean`, wrapper `Integer`/`Double`/`Boolean`, casting |
| [02-string-array.md](02-string-array.md) | `String`, `StringBuilder`, array 1D/2D, `Arrays` |
| [03-kontrol-method.md](03-kontrol-method.md) | `if`, `switch`, loop, method, overloading, `static` |
| [04-oop-class-inheritance.md](04-oop-class-inheritance.md) | class, object, `this`, `super`, override, abstract, interface |
| [05-collections-list-set-map.md](05-collections-list-set-map.md) | `ArrayList`, `LinkedList`, `HashSet`, `TreeSet`, `HashMap` |
| [06-exception-file-io.md](06-exception-file-io.md) | `try/catch`, checked/unchecked, `Files`, `Path`, reader/writer |
| [07-stream-optional-lambda.md](07-stream-optional-lambda.md) | lambda, `Optional`, `Stream`, `Collectors` |
| [08-generics-enum.md](08-generics-enum.md) | `<T>`, wildcard, `enum`, `Comparable`, `Comparator` |
| [09-resep-dan-kesalahan.md](09-resep-dan-kesalahan.md) | resep kerja dan jebakan yang sama berulang |

## Peta cepat: “Saya ingin…”

### Menyiapkan mesin

- Memasang toolkit: [JDK](#jdk)
- Membedakan runtime: [JRE](#jre) dan [JVM](#jvm)
- Mengubah `.java` jadi `.class`: [javac](#javac)
- Menjalankan bytecode: [java](#java)
- Menyusun folder: [struktur project](#struktur-project-tanpa-build-tool)

### Menyimpan data

- Bilangan bulat biasa: [01 — `int`](01-tipe-primitif-wrapper.md#int)
- Teks: [02 — `String`](02-string-array.md#string)
- Daftar yang bisa tumbuh: [05 — `ArrayList`](05-collections-list-set-map.md#arraylist)
- Pasangan kunci-nilai: [05 — `HashMap`](05-collections-list-set-map.md#hashmap)

### Mengatur alur

- Cabang: [03 — `if`](03-kontrol-method.md#if)
- Banyak kasus: [03 — `switch`](03-kontrol-method.md#switch)
- Ulangi daftar: [03 — `for-each`](03-kontrol-method.md#for-each)
- Bungkus langkah: [03 — method](03-kontrol-method.md#method-dengan-return)

### Membuat objek

- Cetakan: [04 — `class`](04-oop-class-inheritance.md#class)
- Objek di memori: [04 — `new`](04-oop-class-inheritance.md#new-dan-object)
- Pewarisan: [04 — `extends`](04-oop-class-inheritance.md#extends)
- Kontrak: [04 — `interface`](04-oop-class-inheritance.md#interface)

### Menangani error dan file

- Tangkap error: [06 — `try/catch`](06-exception-file-io.md#try-catch)
- Baca teks file: [06 — `Files.readString`](06-exception-file-io.md#filesreadstring)
- Nilai yang mungkin kosong: [07 — `Optional`](07-stream-optional-lambda.md#optional)

## Versi yang dipakai di sini

Contoh ditujukan untuk **Java 17+** (LTS yang umum di kuliah). Fitur yang butuh versi lebih baru disebut eksplisit (`toList()` di Stream = Java 16+, text block = Java 15+). Jika kampusmu memakai Java 11, hindari text block dan `List.of` tetap aman (Java 9+).

Dokumentasi resmi: [Java Language](https://docs.oracle.com/javase/tutorial/), [API Java 17](https://docs.oracle.com/en/java/javase/17/docs/api/).

---

## Daftar isi README

- [Java (bahasa)](#java-bahasa)
- [JVM](#jvm)
- [JRE](#jre)
- [JDK](#jdk)
- [Memasang JDK](#memasang-jdk)
- [JAVA_HOME](#java_home)
- [PATH](#path)
- [java -version](#java--version)
- [javac](#javac)
- [java](#java)
- [Berkas .java](#berkas-java)
- [Berkas .class](#berkas-class)
- [public class](#public-class)
- [public static void main](#public-static-void-main)
- [System.out.println](#systemoutprintln)
- [Komentar](#komentar)
- [package](#package)
- [import](#import)
- [import static](#import-static)
- [Nama file = nama class](#nama-file--nama-class)
- [Struktur project tanpa build tool](#struktur-project-tanpa-build-tool)
- [Struktur project dengan package](#struktur-project-dengan-package)
- [classpath dan -cp](#classpath-dan--cp)
- [Menjalankan satu file sumber](#menjalankan-satu-file-sumber)
- [args pada main](#args-pada-main)
- [Scanner di terminal](#scanner-di-terminal)
- [Beberapa class dalam satu file](#beberapa-class-dalam-satu-file)
- [JAR singkat](#jar-singkat)
- [Modul (sekilas)](#modul-sekilas)
- [IDE versus terminal](#ide-versus-terminal)
- [Kesalahan kompilasi yang sering](#kesalahan-kompilasi-yang-sering)
- [Kesalahan runtime yang sering](#kesalahan-runtime-yang-sering)

---

### Java (bahasa)

**Tipe:** bahasa pemrograman (bukan class)

**Untuk apa:** menulis program yang dikompilasi ke bytecode, lalu dijalankan di JVM. Satu kode sumber bisa jalan di Windows, macOS, dan Linux selama ada JVM.

**Contoh implementasi:**

```java
public class HaloToko {
    public static void main(String[] args) {
        String namaToko = "Toko Belajar";
        int jumlahBuku = 3;
        System.out.println(namaToko + " punya " + jumlahBuku + " buku.");
    }
}
```

Simpan sebagai `HaloToko.java`, lalu di terminal:

```text
javac HaloToko.java
java HaloToko
```

**Yang terjadi:** `javac` membaca teks sumber, memeriksa tipe, dan menulis `HaloToko.class`. Perintah `java HaloToko` memuat class itu ke JVM, mencari `main`, lalu mencetak `Toko Belajar punya 3 buku.`

**Biasanya digabungkan dengan:** JDK (agar `javac` ada), package jika proyek membesar, dan class lain di file terpisah.

**Jangan:** mengira file `.java` langsung dibuka browser. Java bukan JavaScript. Jangan juga menamai file beda dengan class publik: kompilator menolak.

---

### JVM

**Tipe:** mesin virtual (bukan class yang kamu tulis)

**Untuk apa:** menjalankan bytecode `.class`. JVM mengelola memori, garbage collection, dan memanggil method `main`.

**Contoh implementasi:**

```java
public class LihatJvm {
    public static void main(String[] args) {
        String namaVm = System.getProperty("java.vm.name");
        String versi = System.getProperty("java.version");
        System.out.println("VM: " + namaVm);
        System.out.println("Versi: " + versi);
    }
}
```

**Yang terjadi:** program tidak bicara ke CPU secara langsung. JVM membaca bytecode, menerjemahkannya (sering dengan JIT), lalu mencetak nama VM (misalnya OpenJDK 64-Bit Server VM) dan versi seperti `17.0.12`.

**Biasanya digabungkan dengan:** JRE atau JDK yang menyediakan JVM, dan perintah `java`.

**Jangan:** menghapus JVM lalu berharap `java NamaClass` masih jalan. Jangan mencampur anggapan “JVM = compiler”: compiler adalah `javac`.

---

### JRE

**Tipe:** paket runtime (bukan class)

**Untuk apa:** menjalankan program Java yang sudah dikompilasi. JRE berisi JVM + pustaka standar, **tanpa** `javac`.

**Contoh implementasi:**

```java
public class CekRuntime {
    public static void main(String[] args) {
        System.out.println("Home: " + System.getProperty("java.home"));
        System.out.println("Vendor: " + System.getProperty("java.vendor"));
    }
}
```

**Yang terjadi:** `java.home` menunjuk folder instalasi runtime. Vendor bisa Oracle, Eclipse Adoptium, Amazon Corretto, atau distribusi OpenJDK lain. Program ini hanya **berjalan**; ia tidak mengompilasi apa pun.

**Biasanya digabungkan dengan:** mesin yang hanya perlu menjalankan aplikasi jadi, bukan menulis kode.

**Jangan:** memasang JRE saja jika kamu masih menulis dan mengompilasi tugas kuliah. Untuk itu kamu butuh [JDK](#jdk).

---

### JDK

**Tipe:** toolkit pengembangan (bukan class)

**Untuk apa:** menulis, mengompilasi, dan menjalankan Java. JDK = JRE + `javac` + tool lain (`jar`, `javadoc`, debugger).

**Contoh implementasi:**

```java
public class CekJdk {
    public static void main(String[] args) {
        System.out.println("Versi spesifikasi: " + System.getProperty("java.specification.version"));
        System.out.println("Java home: " + System.getProperty("java.home"));
        System.out.println("Class path: " + System.getProperty("java.class.path"));
    }
}
```

Setelah JDK terpasang, dua perintah ini harus ada:

```text
javac -version
java -version
```

**Yang terjadi:** `javac -version` mencetak versi compiler (misalnya `javac 17.0.12`). `java -version` mencetak versi JVM. Jika `javac` “command not found”, yang terpasang mungkin hanya JRE, atau PATH belum diisi.

**Biasanya digabungkan dengan:** [JAVA_HOME](#java_home), [PATH](#path), dan editor/IDE.

**Jangan:** mengunduh “Java” acak dari iklan browser. Pakai distribusi jelas: Temurin (Adoptium), Corretto, atau paket resmi kampus. Jangan mencampur JDK 8 dan JDK 17 di PATH tanpa sadar.

---

### Memasang JDK

**Tipe:** langkah instalasi (bukan class)

**Untuk apa:** menyediakan `javac` dan `java` di komputermu.

**Contoh implementasi:**

Setelah JDK 17 terpasang, buat `PasangBerhasil.java`:

```java
public class PasangBerhasil {
    public static void main(String[] args) {
        int fitur = Runtime.version().feature();
        System.out.println("Fitur Java: " + fitur);
        if (fitur < 17) {
            System.out.println("Peringatan: contoh ensiklopedia ini mengasumsikan 17+.");
        } else {
            System.out.println("Siap mengompilasi tugas.");
        }
    }
}
```

Langkah ringkas (macOS dengan Homebrew, jika kamu memakai itu):

```text
brew install openjdk@17
```

Di Linux sering: `sudo apt install openjdk-17-jdk`. Di Windows: pemasang Temurin, lalu centang “Set JAVA_HOME”.

**Yang terjadi:** pemasang menaruh binari di folder seperti `/Library/Java/JavaVirtualMachines/...` atau `C:\Program Files\Eclipse Adoptium\...`. Tool `javac` dan `java` baru terlihat di terminal setelah PATH menunjuk folder `bin`.

**Biasanya digabungkan dengan:** pengecekan `javac -version` segera setelah instal.

**Jangan:** memasang beberapa JDK lalu lupa yang mana yang aktif. Cek `which javac` (macOS/Linux) atau `where javac` (Windows).

---

### JAVA_HOME

**Tipe:** variabel lingkungan (bukan class)

**Untuk apa:** menandai folder akar JDK agar tool (Maven, Gradle, IDE) tahu compiler mana yang dipakai.

**Contoh implementasi:**

```java
public class CetakJavaHome {
    public static void main(String[] args) {
        String home = System.getenv("JAVA_HOME");
        if (home == null) {
            System.out.println("JAVA_HOME belum di-set. java.home JVM: " + System.getProperty("java.home"));
        } else {
            System.out.println("JAVA_HOME=" + home);
        }
    }
}
```

Contoh isi (macOS, sesuaikan path mesinmu):

```text
export JAVA_HOME=$(/usr/libexec/java_home -v 17)
export PATH="$JAVA_HOME/bin:$PATH"
```

**Yang terjadi:** `System.getenv("JAVA_HOME")` membaca lingkungan proses. Jika kosong, program tetap bisa jalan karena JVM sudah ketemu lewat PATH, tetapi build tool bisa bingung.

**Biasanya digabungkan dengan:** [PATH](#path) dan konfigurasi IDE “Project SDK”.

**Jangan:** mengarahkan `JAVA_HOME` ke folder `bin`. `JAVA_HOME` adalah folder **induk** yang berisi `bin`, `lib`, dan `include`.

---

### PATH

**Tipe:** variabel lingkungan (bukan class)

**Untuk apa:** memberitahu shell di folder mana mencari perintah `javac` dan `java`.

**Contoh implementasi:**

```java
public class CekPerintah {
    public static void main(String[] args) {
        System.out.println("Jika kamu bisa menjalankan class ini, perintah java sudah ada di PATH.");
        System.out.println("java.home=" + System.getProperty("java.home"));
    }
}
```

Di terminal:

```text
echo $PATH
which java
which javac
```

**Yang terjadi:** shell menelusuri daftar folder di PATH dari kiri ke kanan. Folder `bin` JDK yang muncul lebih dulu itulah yang dipakai. Itu sebabnya dua instalasi Java bisa “bertengkar”.

**Biasanya digabungkan dengan:** `JAVA_HOME/bin` di depan PATH.

**Jangan:** menambahkan path JDK yang salah versi lalu heran kenapa `record` atau text block error. Compiler yang di PATH-lah yang menentukan.

---

### java -version

**Tipe:** perintah terminal

**Untuk apa:** memastikan JVM yang aktif, sebelum menyalahkan kode.

**Contoh implementasi:**

Tidak perlu class. Di terminal:

```text
java -version
javac -version
```

Kalau ingin dari dalam program:

```java
public class VersiJava {
    public static void main(String[] args) {
        Runtime.Version v = Runtime.version();
        System.out.println("Feature: " + v.feature());
        System.out.println("String versi: " + System.getProperty("java.version"));
    }
}
```

**Yang terjadi:** `java -version` menulis ke **stderr**, biasanya tiga baris: jenis runtime, versi, dan VM. `Runtime.version().feature()` mengembalikan angka utama: `17`, `21`, `25`.

**Biasanya digabungkan dengan:** pengecekan pertama saat “program teman jalan, punya saya tidak”.

**Jangan:** mengira `java -version` dan `javac -version` otomatis sama. Bisa saja `java` dari JDK 21 sementara `javac` dari JDK 8.

---

### javac

**Tipe:** perintah compiler

**Untuk apa:** mengubah `.java` menjadi `.class`. `javac` memeriksa sintaks, tipe, akses, dan kehadiran symbol.

**Contoh implementasi:**

`HitungStok.java`:

```java
public class HitungStok {
    public static void main(String[] args) {
        int masuk = 10;
        int keluar = 4;
        System.out.println("Sisa: " + (masuk - keluar));
    }
}
```

```text
javac HitungStok.java
```

Jika sukses, muncul `HitungStok.class` dan tidak ada pesan error.

**Yang terjadi:** compiler membaca token, membangun pohon sintaks, mengecek bahwa `masuk` dan `keluar` bertipe `int`, lalu menulis bytecode method `main`. Jika kamu menulis `int sisa = "enam";`, `javac` **berhenti** dan tidak membuat/menimpa `.class` yang sah untuk error itu.

**Biasanya digabungkan dengan:** `java HitungStok` setelahnya, dan flag `-d out` untuk menaruh `.class` di folder lain.

**Jangan:** menjalankan `java HitungStok.java` lalu mengira itu menggantikan belajar `javac` — mode satu file itu ada (lihat [menjalankan satu file sumber](#menjalankan-satu-file-sumber)), tetapi tugas kuliah biasanya menuntut `.class` dan package. Jangan juga mengompilasi hanya satu file jika ia memanggil class lain yang belum dikompilasi.

Kompilasi beberapa file sekaligus:

```text
javac Toko.java Barang.java
```

Atau semua sumber di folder:

```text
javac *.java
```

Dengan package dan folder keluaran:

```text
javac -d out src/toko/HitungStok.java
```

---

### java

**Tipe:** perintah launcher

**Untuk apa:** memuat class, mencari `public static void main(String[])`, dan menjalankannya di JVM.

**Contoh implementasi:**

```java
public class CetakArgumen {
    public static void main(String[] args) {
        System.out.println("Jumlah argumen: " + args.length);
        if (args.length > 0) {
            System.out.println("Argumen pertama: " + args[0]);
        }
    }
}
```

```text
javac CetakArgumen.java
java CetakArgumen kopi teh
```

**Yang terjadi:** launcher **bukan** mengompilasi. Ia mencari `CetakArgumen.class` di classpath (folder kerja jika tidak diubah). `args[0]` menjadi `"kopi"`, `args[1]` menjadi `"teh"`. Output:

```text
Jumlah argumen: 2
Argumen pertama: kopi
```

**Biasanya digabungkan dengan:** `javac` sebelumnya, dan `-cp` jika `.class` tidak di folder kerja.

**Jangan:** menulis `java CetakArgumen.class`. Nama yang diberikan ke `java` adalah **nama class**, bukan nama file. Jangan juga `java cetakargumen` — huruf besar/kecil dihitung.

---

### Berkas .java

**Tipe:** file sumber (bukan class API)

**Untuk apa:** tempat menulis class, interface, dan enum dalam teks biasa.

**Contoh implementasi:**

Isi `PesanToko.java`:

```java
public class PesanToko {
    public static void main(String[] args) {
        System.out.println("File ini masih teks sampai di-javac.");
    }
}
```

**Yang terjadi:** editor menyimpan karakter Unicode. JVM tidak membaca file ini saat `java PesanToko` kecuali kamu memakai mode single-file. Yang dijalankan adalah hasil kompilasi.

**Biasanya digabungkan dengan:** satu `public class` per file, nama file cocok.

**Jangan:** menyimpan sebagai `.txt` atau `.js`. Jangan menaruh dua `public class` di satu file.

---

### Berkas .class

**Tipe:** file bytecode

**Untuk apa:** hasil `javac` yang dimuat JVM.

**Contoh implementasi:**

```java
public class LihatClass {
    public static void main(String[] args) {
        System.out.println("Setelah javac, muncul LihatClass.class di folder yang sama (kecuali -d).");
        System.out.println("Nama class: " + LihatClass.class.getName());
    }
}
```

**Yang terjadi:** `.class` berisi constant pool, deskripsi method, dan instruksi bytecode (`iconst`, `invokevirtual`, dan sebagainya). Kamu tidak mengedit file ini dengan tangan.

**Biasanya digabungkan dengan:** perintah `java`, dan tool `javap -c NamaClass` jika ingin melihat bytecode.

**Jangan:** mengirim `.class` hasil JDK 21 ke teman yang JVM-nya 8 tanpa kompilasi ulang. Bytecode punya versi target. Jangan menghapus `.java` lalu hanya menyimpan `.class` sebagai “sumber”.

---

### public class

**Tipe:** deklarasi class

**Untuk apa:** membuat tipe yang bisa dilihat dari package lain, dan (jika namanya cocok) menjadi class utama sebuah file.

**Contoh implementasi:**

```java
public class KartuMember {
    String nama;
    int poin;

    public static void main(String[] args) {
        KartuMember k = new KartuMember();
        k.nama = "Haikal";
        k.poin = 12;
        System.out.println(k.nama + " punya " + k.poin + " poin");
    }
}
```

**Yang terjadi:** `public` pada class berarti class ini bisa di-`import` dari package lain. JVM bisa menjalankan `main` di dalamnya. Field `nama` dan `poin` di contoh ini package-private (tanpa modifier) — class lain di package yang sama bisa menyentuhnya.

**Biasanya digabungkan dengan:** [nama file = nama class](#nama-file--nama-class) dan constructor di bab 04.

**Jangan:** menulis `public class kartuMember` (huruf depan kecil). Konvensi class: `PascalCase`. Compiler memperbolehkan, pembaca manusia tersesat.

---

### public static void main

**Tipe:** method khusus (titik masuk)

**Untuk apa:** menjadi pintu yang dicari perintah `java`. Tanpa method ini (dengan tanda tangan tepat), class dikompilasi tetapi tidak bisa dijadikan program mandiri.

**Contoh implementasi:**

```java
public class TitikMasuk {
    public static void main(String[] args) {
        System.out.println("JVM memanggil main dulu.");
        sapa("Toko Belajar");
    }

    static void sapa(String toko) {
        System.out.println("Selamat datang di " + toko);
    }
}
```

**Yang terjadi:** JVM tidak memanggil `sapa` sendiri. Ia memanggil `main`. `main` lalu memanggil `sapa`. `static` perlu karena objek belum tentu ada saat program mulai. `void` berarti `main` tidak mengembalikan nilai ke JVM lewat `return` bertipe (kode keluar memakai `System.exit` jika perlu).

**Biasanya digabungkan dengan:** `String[] args` untuk argumen CLI, dan method lain agar `main` tetap pendek.

**Jangan:** mengubah jadi `public void main()` lalu heran `Error: Main method not found`. Jangan membuat `main` mengerjakan 200 baris logika — pecah ke method/class.

Bentuk yang diterima compiler modern (beberapa versi) lebih longgar, tetapi **tugas kuliah** hampir selalu menuntut:

```java
public static void main(String[] args)
```

---

### System.out.println

**Tipe:** method (`PrintStream.println`)

**Untuk apa:** mencetak satu baris ke keluaran standar (terminal).

**Contoh implementasi:**

```java
public class CetakBaris {
    public static void main(String[] args) {
        System.out.println("Baris pertama");
        System.out.print("Tanpa ganti baris ");
        System.out.print("masih satu baris. ");
        System.out.println("Sekarang ganti.");
        System.out.println(42);
        System.out.println(true);
    }
}
```

**Yang terjadi:** `System.out` adalah `PrintStream`. `println` mengubah argumen jadi teks, menulisnya, lalu menulis newline. `print` tidak menambah newline. Angka dan `boolean` diubah otomatis ke string.

**Biasanya digabungkan dengan:** operator `+` untuk gabung teks, dan `System.out.printf` untuk format.

**Jangan:** memakai `println` sebagai “debugger resmi” di program besar tanpa kontrol. Jangan mengira `System.out` sama dengan menulis file; itu beda (bab 06).

---

### Komentar

**Tipe:** sintaks sumber (bukan class)

**Untuk apa:** menulis catatan untuk manusia. Compiler membuang komentar.

**Contoh implementasi:**

```java
public class ContohKomentar {
    public static void main(String[] args) {
        // komentar satu baris
        int harga = 15000; // harga satu buku
        /*
         * komentar beberapa baris
         * tidak dijalankan
         */
        System.out.println(harga);
        /**
         * Javadoc biasanya di atas class/method, bukan di dalam main.
         */
    }
}
```

**Yang terjadi:** `javac` mengabaikan teks komentar. `//` sampai akhir baris. `/* */` bisa menyeberangi baris. `/** */` adalah Javadoc; tool `javadoc` bisa memanennya.

**Biasanya digabungkan dengan:** penjelasan *mengapa*, bukan mengulang *apa* yang sudah jelas dari nama variabel.

**Jangan:** mengomentari kode mati sepanjang file sebagai “cadangan”. Jangan menyimpan sandi di komentar. Jangan menaruh `/*` di dalam `/* */` — komentar blok tidak bersarang.

---

### package

**Tipe:** deklarasi namespace

**Untuk apa:** mengelompokkan class agar nama tidak tabrakan, dan mencerminkan folder.

**Contoh implementasi:**

File `src/toko/Kasir.java`:

```java
package toko;

public class Kasir {
    public static void main(String[] args) {
        System.out.println("Class ini hidup di package toko");
        System.out.println("Nama lengkap: " + Kasir.class.getName());
    }
}
```

Kompilasi dari akar project:

```text
javac -d out src/toko/Kasir.java
java -cp out toko.Kasir
```

**Yang terjadi:** baris `package toko;` **harus** baris pertama (selain komentar). Nama lengkap class menjadi `toko.Kasir`. Folder harus `toko/Kasir.java`. Perintah `java` memakai nama lengkap, bukan `java Kasir`.

**Biasanya digabungkan dengan:** [import](#import) di class lain, dan struktur folder yang sama dengan titik pada nama package.

**Jangan:** menulis `package toko;` tetapi menyimpan file di folder `src/` tanpa `toko/`. Jangan memakai huruf besar pada segmen package (`package Toko;` menyalahi konvensi). Jangan menaruh `package` di bawah `import`.

---

### import

**Tipe:** deklarasi (bukan class)

**Untuk apa:** menyebut class package lain dengan nama pendek.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ImportList {
    public static void main(String[] args) {
        List<String> menu = new ArrayList<>();
        menu.add("Nasi goreng");
        menu.add("Es teh");
        System.out.println(menu);
    }
}
```

Tanpa `import`, kamu harus menulis `java.util.ArrayList` di setiap pemakaian.

**Yang terjadi:** `import` **bukan** menyalin kode seperti `#include` C. Ia hanya izin nama pendek. Bytecode tetap merujuk class pustaka standar yang sudah ada di JDK.

**Biasanya digabungkan dengan:** packagemu sendiri (`import toko.Barang;`) dan import banyak class dari package yang sama.

**Jangan:** mengira `import java.util.*` menaruh semua isi package ke memori. Itu hanya kenyamanan nama. Tetap lebih jelas mengimpor class yang dipakai. Jangan mengimpor dua class bernama sama tanpa nama lengkap: `java.util.Date` versus `java.sql.Date`.

---

### import static

**Tipe:** deklarasi

**Untuk apa:** memakai member `static` tanpa nama class.

**Contoh implementasi:**

```java
import static java.lang.Math.max;
import static java.lang.Math.PI;

public class ImportStatis {
    public static void main(String[] args) {
        double jari = 7;
        double luas = PI * jari * jari;
        int termahal = max(15000, 22000);
        System.out.println("Luas kira-kira: " + luas);
        System.out.println("Harga terpilih: " + termahal);
    }
}
```

**Yang terjadi:** `max` merujuk `Math.max`, `PI` merujuk `Math.PI`. Class `java.lang.Math` tidak perlu diimpor biasa karena `java.lang` sudah otomatis, tetapi nama method-nya tidak otomatis “numpang” di classmu.

**Biasanya digabungkan dengan:** konstanta `static final` dan method utilitas yang dipanggil berkali-kali.

**Jangan:** meng-`import static` semuanya sampai pembaca tidak tahu method itu milik siapa.

---

### Nama file = nama class

**Tipe:** aturan compiler

**Untuk apa:** menautkan file sumber ke class publik.

**Contoh implementasi:**

File **harus** `Pengirim.java`:

```java
public class Pengirim {
    public static void main(String[] args) {
        System.out.println("Nama file cocok dengan Pengirim");
    }
}
```

Jika file ini disimpan sebagai `pengirim.java` di macOS yang case-insensitive, kamu bisa kebingungan saat dipindah ke Linux.

**Yang terjadi:** `javac` menolak `public class Pengirim` di dalam `Kirim.java` dengan error semacam *class Pengirim is public, should be declared in a file named Pengirim.java*.

**Biasanya digabungkan dengan:** satu class publik per file.

**Jangan:** mengandalkan “nanti saya rename di Explorer” tanpa menyesuaikan isi `public class`.

---

### Struktur project tanpa build tool

**Tipe:** konvensi folder

**Untuk apa:** tugas kecil satu atau beberapa file, dikompilasi manual.

**Contoh implementasi:**

```text
latihan-kasir/
  HitungTotal.java
  Struk.java
```

`HitungTotal.java`:

```java
public class HitungTotal {
    public static void main(String[] args) {
        int harga = 15000;
        int jumlah = 2;
        System.out.println(Struk.format(harga, jumlah));
    }
}
```

`Struk.java` (boleh tanpa `public` jika tidak dijadikan class publik di file sendiri — di sini kita buat publik):

```java
public class Struk {
    public static String format(int harga, int jumlah) {
        return "Total: " + (harga * jumlah);
    }
}
```

```text
cd latihan-kasir
javac HitungTotal.java Struk.java
java HitungTotal
```

**Yang terjadi:** `javac` menyelesaikan rujukan `Struk.format`. Kedua `.class` muncul di folder yang sama. `java HitungTotal` memuat `Struk` dari classpath default (folder kerja).

**Biasanya digabungkan dengan:** tugas 1–5 class, tanpa Maven.

**Jangan:** menaruh `.class` ke Git sebagai pengganti sumber. Masukkan `*.class` ke `.gitignore`.

---

### Struktur project dengan package

**Tipe:** konvensi folder

**Untuk apa:** meniru proyek nyata: sumber terpisah dari hasil kompilasi.

**Contoh implementasi:**

```text
toko-kuliah/
  src/
    toko/
      App.java
      model/
        Barang.java
  out/
```

`src/toko/model/Barang.java`:

```java
package toko.model;

public class Barang {
    public String nama;
    public int harga;

    public Barang(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }
}
```

`src/toko/App.java`:

```java
package toko;

import toko.model.Barang;

public class App {
    public static void main(String[] args) {
        Barang b = new Barang("Pensil", 3000);
        System.out.println(b.nama + " Rp" + b.harga);
    }
}
```

```text
cd toko-kuliah
javac -d out src/toko/model/Barang.java src/toko/App.java
java -cp out toko.App
```

**Yang terjadi:** `-d out` menulis `out/toko/model/Barang.class` dan `out/toko/App.class`, meniru pohon package. Launcher butuh `-cp out` dan nama **fully qualified** `toko.App`.

**Biasanya digabungkan dengan:** `import`, dan nanti Maven (`src/main/java`) jika mata kuliah memakai build tool.

**Jangan:** mencampur `package toko;` dengan file yang duduk di `src/` langsung. Jangan menjalankan `java out/toko/App` — itu path file, bukan nama class.

Pola Maven/Gradle yang akan kamu temui:

```text
src/main/java/toko/App.java
src/test/java/toko/AppTest.java
```

Ensiklopedia ini tidak mensyaratkan Maven. Yang penting: **folder = package**.

---

### classpath dan -cp

**Tipe:** opsi launcher/compiler

**Untuk apa:** memberitahu JVM (dan `javac`) di mana mencari `.class` dan JAR.

**Contoh implementasi:**

```java
package toko;

public class LihatClasspath {
    public static void main(String[] args) {
        System.out.println(System.getProperty("java.class.path"));
    }
}
```

```text
javac -d out src/toko/LihatClasspath.java
java -cp out toko.LihatClasspath
```

Beberapa folder (pemisah `:` di macOS/Linux, `;` di Windows):

```text
java -cp out:lib/gson.jar toko.App
```

**Yang terjadi:** JVM menelusuri classpath saat butuh class. Jika `toko.model.Barang` tidak ketemu, muncul `NoClassDefFoundError` atau `ClassNotFoundException`. Property `java.class.path` mencetak nilai yang dipakai proses ini.

**Biasanya digabungkan dengan:** `-d` pada `javac` agar pohon package rapi.

**Jangan:** mengira classpath sama dengan PATH sistem. PATH mencari **program** (`java` itu sendiri). Classpath mencari **class**.

---

### Menjalankan satu file sumber

**Tipe:** mode perintah `java` (Java 11+)

**Untuk apa:** uji cepat satu file tanpa langkah `javac` terpisah.

**Contoh implementasi:**

`CobaCepat.java`:

```java
public class CobaCepat {
    public static void main(String[] args) {
        System.out.println("Dijalankan dari sumber: " + CobaCepat.class.getSimpleName());
    }
}
```

```text
java CobaCepat.java
```

**Yang terjadi:** launcher mengompilasi di memori (atau cache implementasi) lalu menjalankan `main`. Berguna untuk eksperimen. Tugas berspakage dan banyak class tetap memakai `javac -d`.

**Biasanya digabungkan dengan:** file tunggal tanpa dependensi project.

**Jangan:** mengumpulkan 15 file lalu mengandalkan mode ini. Jangan lupa: teman yang memakai Java 8 tidak punya mode ini.

---

### args pada main

**Tipe:** parameter method (`String[]`)

**Untuk apa:** menerima teks dari baris perintah.

**Contoh implementasi:**

```java
public class KasirCli {
    public static void main(String[] args) {
        if (args.length < 2) {
            System.out.println("Pakai: java KasirCli <nama> <harga>");
            return;
        }
        String nama = args[0];
        int harga = Integer.parseInt(args[1]);
        System.out.println("Barang: " + nama);
        System.out.println("Harga: Rp" + harga);
    }
}
```

```text
javac KasirCli.java
java KasirCli Penghapus 2000
```

**Yang terjadi:** JVM mengisi array `args` dari token setelah nama class. `args[1]` masih `String` `"2000"` sampai `parseInt` mengubahnya. Jika kamu lupa argumen, program mencetak cara pakai dan `return` dari `main` (program selesai dengan status 0).

**Biasanya digabungkan dengan:** `Integer.parseInt` (bab 01) dan pengecekan `args.length`.

**Jangan:** mengakses `args[0]` tanpa cek panjang — `ArrayIndexOutOfBoundsException`. Jangan mengira `args` berisi nama class.

---

### Scanner di terminal

**Tipe:** class (`java.util.Scanner`)

**Untuk apa:** membaca ketikan pengguna dari `System.in`.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class TanyaNama {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Nama toko: ");
        String nama = input.nextLine();
        System.out.print("Jumlah stok: ");
        int stok = input.nextInt();
        System.out.println(nama + " stok=" + stok);
        input.close();
    }
}
```

**Yang terjadi:** program berhenti di `nextLine()` sampai pengguna menekan Enter. `nextInt()` membaca token angka berikutnya. `close()` menutup scanner (dan di kasus `System.in`, menutup aliran input — di program kecil itu biasa).

**Biasanya digabungkan dengan:** `nextLine` setelah `nextInt` dengan hati-hati (lihat resep di bab 09).

**Jangan:** membuat banyak `Scanner` pada `System.in` sekaligus. Jangan lupa: `nextInt` tidak menghabiskan newline.

---

### Beberapa class dalam satu file

**Tipe:** aturan file sumber

**Untuk apa:** menaruh class pembantu kecil di file yang sama, asalkan hanya **satu** class yang `public` (dan namanya sama dengan file).

**Contoh implementasi:**

File `TokoMini.java`:

```java
public class TokoMini {
    public static void main(String[] args) {
        BarangMini b = new BarangMini("Buku", 45000);
        System.out.println(b.nama + " Rp" + b.harga);
    }
}

class BarangMini {
    String nama;
    int harga;

    BarangMini(String nama, int harga) {
        this.nama = nama;
        this.harga = harga;
    }
}
```

**Yang terjadi:** `javac` menghasilkan **dua** file class: `TokoMini.class` dan `BarangMini.class`. `BarangMini` tidak `public`, jadi class di package lain tidak bisa memakainya.

**Biasanya digabungkan dengan:** latihan singkat. Di proyek rapi, tiap class dapat file sendiri.

**Jangan:** menulis dua `public class` di `TokoMini.java`.

---

### JAR singkat

**Tipe:** arsip (perintah `jar`)

**Untuk apa:** membungkus banyak `.class` (dan resource) jadi satu file yang bisa dibagikan.

**Contoh implementasi:**

```java
package toko;

public class AppJar {
    public static void main(String[] args) {
        System.out.println("Halo dari JAR");
    }
}
```

```text
javac -d out src/toko/AppJar.java
jar --create --file toko.jar --main-class toko.AppJar -C out .
java -jar toko.jar
```

**Yang terjadi:** `jar` menaruh pohon `toko/AppJar.class` plus manifest yang menunjuk `Main-Class: toko.AppJar`. `java -jar` membaca manifest dan menjalankan `main`.

**Biasanya digabungkan dengan:** distribusi tugas jadi, atau library pihak ketiga di classpath.

**Jangan:** mengira JAR adalah installer Windows. Jangan lupa `--main-class` jika ingin `java -jar`.

---

### Modul (sekilas)

**Tipe:** sistem modul (`module-info.java`)

**Untuk apa:** membatasi package mana yang diekspor pada aplikasi besar (Java 9+).

**Contoh implementasi:**

`src/module-info.java`:

```java
module toko.app {
    exports toko;
}
```

`src/toko/AppModul.java`:

```java
package toko;

public class AppModul {
    public static void main(String[] args) {
        System.out.println("Modul: " + AppModul.class.getModule().getName());
    }
}
```

**Yang terjadi:** jika kamu mengompilasi sebagai modul, nama modul menempel pada class. Untuk **tugas kuliah dasar**, modul biasanya **tidak wajib**. Classpath klasik cukup.

**Biasanya digabungkan dengan:** proyek multi-modul besar.

**Jangan:** menambah `module-info.java` ke tugas kecil lalu heran `package is not visible`. Jika belum diajar, lewati.

---

### IDE versus terminal

**Tipe:** cara kerja (bukan class)

**Untuk apa:** memilih alat. IDE (IntelliJ, VS Code, Eclipse) menekan tombol Run yang di balik layar memanggil JDK yang sama.

**Contoh implementasi:**

```java
public class IdeAtauTerminal {
    public static void main(String[] args) {
        System.out.println("Hasilnya sama: JVM menjalankan main.");
        System.out.println("Yang beda: siapa yang mengetik javac untukmu.");
    }
}
```

**Yang terjadi:** IntelliJ memakai Project SDK. VS Code memakai ekstensi Extension Pack for Java / Language Support. Kalau SDK IDE salah, editor merah sementara terminalmu yang PATH-nya benar justru sukses — atau sebaliknya.

**Biasanya digabungkan dengan:** set SDK 17 di IDE, sama dengan `javac -version`.

**Jangan:** menyalin error IDE tanpa melihat *baris yang mana*. Jangan mengira tombol hijau menggantikan paham `package` dan classpath.

---

### Kesalahan kompilasi yang sering

**Tipe:** kategori error `javac`

**Untuk apa:** membedakan “belum jadi `.class`” dengan “program meledak saat jalan”.

**Contoh implementasi:**

```java
public class ErrorKompilasiDemo {
    public static void main(String[] args) {
        int harga = 10000;
        // int salah = "mahal"; // buka komentar ini: incompatible types
        System.out.println(harga);

        String nama = "Buku";
        // System.out.println(Nama); // buka komentar: cannot find symbol
        System.out.println(nama);
    }
}
```

**Yang terjadi:** error kompilasi **mencegah** program jalan. Pesan umum:

| Pesan | Artinya |
| --- | --- |
| `cannot find symbol` | nama variabel/class/method salah ketik atau belum diimpor |
| `incompatible types` | menaruh `String` ke `int`, atau sebaliknya tanpa konversi |
| `';' expected` | kurang titik koma, atau kurung rusak di baris atas |
| `class X is public, should be declared in a file named X.java` | nama file salah |
| `'(' expected` / `')' expected` | kurung method rusak |
| `non-static method cannot be referenced from a static context` | `main` memanggil method instance tanpa objek |
| `reached end of file while parsing` | kurang `}` |

**Biasanya digabungkan dengan:** membaca **baris pertama** error, bukan yang terakhir.

**Jangan:** mengompilasi ulang tanpa menyimpan file. Jangan memperbaiki error dari bawah ke atas jika error atas merusak parsing.

---

### Kesalahan runtime yang sering

**Tipe:** kategori exception

**Untuk apa:** memahami program **sudah** dikompilasi, lalu meledak di JVM.

**Contoh implementasi:**

```java
public class ErrorRuntimeDemo {
    public static void main(String[] args) {
        String[] menu = { "Nasi", "Teh" };
        System.out.println("Panjang: " + menu.length);
        // System.out.println(menu[2]); // ArrayIndexOutOfBoundsException

        String kosong = null;
        // System.out.println(kosong.length()); // NullPointerException

        // int n = Integer.parseInt("tiga"); // NumberFormatException
        int n = Integer.parseInt("3");
        System.out.println(n);
    }
}
```

**Yang terjadi:** `javac` lulus karena tipe masuk akal. Saat baris berbahaya dijalankan, JVM melempar exception, mencetak stack trace, dan (jika tidak ditangkap) mematikan thread `main`.

| Exception | Penyebab tipikal |
| --- | --- |
| `NullPointerException` | memanggil method pada `null` |
| `ArrayIndexOutOfBoundsException` | indeks di luar 0 .. length-1 |
| `NumberFormatException` | `parseInt("abc")` |
| `ArithmeticException` | bagi nol pada `int` |
| `ClassCastException` | cast objek ke tipe yang salah |
| `NoClassDefFoundError` | `.class` hilang di classpath saat jalan |

**Biasanya digabungkan dengan:** bab 06 exception, dan stack trace: baca **Caused by** serta baris *your class*.

**Jangan:** menelan semua exception dengan `catch (Exception e) {}` kosong. Jangan mengira runtime error adalah “Java rusak”.

---

## Checklist sebelum `javac`

1. Nama file = nama `public class`.
2. `main` tertulis `public static void main(String[] args)`.
3. Package cocok dengan folder.
4. `import` untuk class di luar `java.lang` dan package sendiri.
5. Titik koma dan kurung berpasangan.

## Checklist sebelum `java`

1. Sudah `javac` tanpa error.
2. Kamu memanggil **nama class** (plus package), bukan `Nama.class`.
3. `-cp` menunjuk folder yang berisi akar package (`out`, bukan `out/toko`).
4. Argumen CLI ada jika program membacanya.

Lanjut ke [01 — tipe primitif dan wrapper](01-tipe-primitif-wrapper.md).
