# 09 — Resep dan kesalahan

[← 08 generics](08-generics-enum.md) · [Indeks](README.md)

Pola siap pakai dan jebakan yang sama berulang. Tiap resep merujuk entri di file lain. Contoh tetap **satu class + `main`**.

## Daftar isi

- [Resep: Hello World](#resep-hello-world)
- [Resep: baca Scanner aman](#resep-baca-scanner-aman)
- [Resep: total keranjang](#resep-total-keranjang)
- [Resep: cari di List](#resep-cari-di-list)
- [Resep: sort objek](#resep-sort-objek)
- [Resep: histogram HashMap](#resep-histogram-hashmap)
- [Resep: unik tetap urut](#resep-unik-tetap-urut)
- [Resep: parse angka aman](#resep-parse-angka-aman)
- [Resep: validasi constructor](#resep-validasi-constructor)
- [Resep: baca file baris](#resep-baca-file-baris)
- [Resep: tulis CSV](#resep-tulis-csv)
- [Resep: Optional anti-null](#resep-optional-anti-null)
- [Resep: equals dan hashCode](#resep-equals-dan-hashcode)
- [Resep: groupingBy](#resep-groupingby)
- [Kesalahan: == pada String](#kesalahan--pada-string)
- [Kesalahan: == pada Integer](#kesalahan--pada-integer)
- [Kesalahan: pembagian int](#kesalahan-pembagian-int)
- [Kesalahan: uang double](#kesalahan-uang-double)
- [Kesalahan: unboxing null](#kesalahan-unboxing-null)
- [Kesalahan: Scanner nextInt](#kesalahan-scanner-nextint)
- [Kesalahan: ConcurrentModification](#kesalahan-concurrentmodification)
- [Kesalahan: List.of lalu add](#kesalahan-listof-lalu-add)
- [Kesalahan: Arrays.asList add](#kesalahan-arraysaslist-add)
- [Kesalahan: HashSet tanpa hashCode](#kesalahan-hashset-tanpa-hashcode)
- [Kesalahan: public class ≠ nama file](#kesalahan-public-class--nama-file)
- [Kesalahan: static vs instance](#kesalahan-static-vs-instance)
- [Kesalahan: String + di loop](#kesalahan-string--di-loop)
- [Kesalahan: resource bocor](#kesalahan-resource-bocor)
- [Kesalahan: package ≠ folder](#kesalahan-package--folder)
- [Kesalahan: catch kosong](#kesalahan-catch-kosong)
- [Tabel jangan / pakai](#tabel-jangan--pakai)

---

### Resep: Hello World

**Tipe:** resep (class + method `main`)

**Untuk apa:** memastikan JDK, `javac`, dan `java` hidup.

**Contoh implementasi:**

```java
public class HaloDunia {
    public static void main(String[] args) {
        System.out.println("Halo, Java");
    }
}
```

```text
javac HaloDunia.java
java HaloDunia
```

**Yang terjadi:** `Halo, Java` di terminal. Jika `javac` tidak ketemu, kembali ke [README — JDK](README.md#jdk).

**Biasanya digabungkan dengan:** [public static void main](README.md#public-static-void-main), [javac](README.md#javac).

**Jangan:** `java HaloDunia.java` sebagai satu-satunya cara yang kamu pahami — tugas package membutuhkan `javac -d`.

---

### Resep: baca Scanner aman

**Tipe:** resep

**Untuk apa:** membaca teks dan angka tanpa menelan baris.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class ScannerAman {
    public static void main(String[] args) {
        Scanner in = new Scanner("Buku Java\n2\n45000\n");
        System.out.println("Nama: (simulasi)");
        String nama = in.nextLine().strip();
        System.out.println("Jumlah:");
        while (!in.hasNextInt()) {
            in.nextLine();
        }
        int jumlah = in.nextInt();
        in.nextLine();
        System.out.println("Harga:");
        int harga = Integer.parseInt(in.nextLine().strip());
        System.out.println(nama + " x" + jumlah + " = " + (harga * jumlah));
        in.close();
    }
}
```

**Yang terjadi:** nama utuh termasuk spasi. `hasNextInt` menolak sampah. `nextLine` setelah `nextInt` membuang newline. Total 90000.

**Biasanya digabungkan dengan:** [Scanner](03-kontrol-method.md#scanner-ringkas), [parseInt](01-tipe-primitif-wrapper.md#integerparseint).

**Jangan:** `next()` untuk nama orang yang ada spasi.

---

### Resep: total keranjang

**Tipe:** resep

**Untuk apa:** jumlah `harga * qty` dengan class kecil, bukan 10 variabel lepas.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class TotalKeranjang {
    static class Item {
        final String nama;
        final int harga;
        final int qty;
        Item(String nama, int harga, int qty) {
            this.nama = nama;
            this.harga = harga;
            this.qty = qty;
        }
        int subtotal() { return harga * qty; }
    }

    public static void main(String[] args) {
        List<Item> k = new ArrayList<>();
        k.add(new Item("Buku", 45000, 1));
        k.add(new Item("Pensil", 3000, 2));
        int total = 0;
        for (Item i : k) {
            total += i.subtotal();
        }
        System.out.println(total);
        int viaStream = k.stream().mapToInt(Item::subtotal).sum();
        System.out.println(viaStream);
    }
}
```

**Yang terjadi:** 51000 dua kali. Field `final` mencegah item berubah diam-diam.

**Biasanya digabungkan dengan:** [ArrayList](05-collections-list-set-map.md#arraylist), [mapToInt](07-stream-optional-lambda.md#intstream).

**Jangan:** `int` overflow pada qty besar — pakai `long` subtotal jika perlu.

---

### Resep: cari di List

**Tipe:** resep

**Untuk apa:** temukan objek pertama yang cocok, atau kosong.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.Optional;

public class CariList {
    record Barang(String sku, String nama) {}

    static Optional<Barang> cari(List<Barang> daftar, String sku) {
        return daftar.stream()
                .filter(b -> b.sku().equals(sku))
                .findFirst();
    }

    public static void main(String[] args) {
        List<Barang> d = List.of(
                new Barang("BK-1", "Java"),
                new Barang("PN-1", "Pensil")
        );
        cari(d, "PN-1").ifPresent(b -> System.out.println(b.nama()));
        System.out.println(cari(d, "XX").orElse(new Barang("?", "tidak ada")).nama());
    }
}
```

**Yang terjadi:** `Pensil`. SKU tiada memakai cadangan.

**Biasanya digabungkan dengan:** [findFirst](07-stream-optional-lambda.md#findfirst), [HashMap](05-collections-list-set-map.md#hashmap) jika sering cari by id.

**Jangan:** loop + `break` tanpa menampung hasil, lalu memakai variabel belum diisi.

---

### Resep: sort objek

**Tipe:** resep

**Untuk apa:** urut list barang menurut harga, lalu nama.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class SortObjek {
    record Barang(String nama, int harga) {}

    public static void main(String[] args) {
        List<Barang> d = new ArrayList<>();
        d.add(new Barang("Buku", 45000));
        d.add(new Barang("Pena", 3000));
        d.add(new Barang("Album", 3000));
        d.sort(Comparator.comparingInt(Barang::harga).thenComparing(Barang::nama));
        d.forEach(System.out::println);
    }
}
```

**Yang terjadi:** Album, Pena, Buku. `List.of` tidak bisa `sort` di tempat — pakai `ArrayList`.

**Biasanya digabungkan dengan:** [Comparator.comparing](08-generics-enum.md#comparatorcomparing), [Collections.sort](05-collections-list-set-map.md#collectionssort).

**Jangan:** `a.harga - b.harga`. Jangan sort `List.of`.

---

### Resep: histogram HashMap

**Tipe:** resep

**Untuk apa:** hitung frekuensi kata/SKU.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Histogram {
    public static void main(String[] args) {
        List<String> log = List.of("BK-1", "PN-1", "BK-1", "BK-1", "TH-1");
        Map<String, Integer> hitung = new HashMap<>();
        for (String sku : log) {
            hitung.put(sku, hitung.getOrDefault(sku, 0) + 1);
        }
        hitung.forEach((k, v) -> System.out.println(k + " = " + v));
    }
}
```

**Yang terjadi:** BK-1 = 3, lainnya 1. `getOrDefault` menghindari NPE.

**Biasanya digabungkan dengan:** [getOrDefault](05-collections-list-set-map.md#hashmapgetordefault), [merge](07-stream-optional-lambda.md#bifunction), [groupingBy](07-stream-optional-lambda.md#collectorsgroupingby).

**Jangan:** `int n = map.get(sku); n++` saat kunci baru — NPE.

---

### Resep: unik tetap urut

**Tipe:** resep

**Untuk apa:** buang duplikat, jaga urutan pertama muncul.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.LinkedHashSet;
import java.util.List;
import java.util.Set;

public class UnikUrut {
    public static void main(String[] args) {
        List<String> mentah = List.of("Buku", "Teh", "Buku", "Kopi", "Teh");
        Set<String> unik = new LinkedHashSet<>(mentah);
        List<String> hasil = new ArrayList<>(unik);
        System.out.println(hasil);
    }
}
```

**Yang terjadi:** `[Buku, Teh, Kopi]`. `HashSet` saja bisa mengacak tampilan.

**Biasanya digabungkan dengan:** [LinkedHashSet](05-collections-list-set-map.md#linkedhashset), [distinct](07-stream-optional-lambda.md#distinct).

**Jangan:** `HashSet` + sort jika urutan insert yang kamu mau, bukan alfabet.

---

### Resep: parse angka aman

**Tipe:** resep

**Untuk apa:** input teks → `int` tanpa meruntuhkan program.

**Contoh implementasi:**

```java
import java.util.OptionalInt;

public class ParseAman {
    static OptionalInt keInt(String s) {
        if (s == null || s.isBlank()) {
            return OptionalInt.empty();
        }
        try {
            return OptionalInt.of(Integer.parseInt(s.strip()));
        } catch (NumberFormatException ex) {
            return OptionalInt.empty();
        }
    }

    public static void main(String[] args) {
        System.out.println(keInt(" 42 ").orElse(-1));
        System.out.println(keInt("x").orElse(-1));
        System.out.println(keInt(null).orElse(-1));
    }
}
```

**Yang terjadi:** 42, -1, -1. `OptionalInt` menghindari `null` wrapper.

**Biasanya digabungkan dengan:** [NumberFormatException](06-exception-file-io.md#numberformatexception), form.

**Jangan:** mengembalikan `0` sebagai error jika 0 nilai sah.

---

### Resep: validasi constructor

**Tipe:** resep

**Untuk apa:** objek tidak pernah lahir dalam keadaan rusak.

**Contoh implementasi:**

```java
public class ValidasiCtor {
    static class Produk {
        private final String nama;
        private final int harga;
        Produk(String nama, int harga) {
            if (nama == null || nama.isBlank()) {
                throw new IllegalArgumentException("nama wajib");
            }
            if (harga < 0) {
                throw new IllegalArgumentException("harga");
            }
            this.nama = nama.strip();
            this.harga = harga;
        }
        @Override public String toString() { return nama + "=" + harga; }
    }

    public static void main(String[] args) {
        System.out.println(new Produk("  Teh  ", 5000));
        try {
            new Produk(" ", 1);
        } catch (IllegalArgumentException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `Teh=5000`. Nama blank ditolak sebelum field terisi.

**Biasanya digabungkan dengan:** [constructor](04-oop-class-inheritance.md#constructor), [IAE](06-exception-file-io.md#illegalargumentexception).

**Jangan:** setter publik yang menembus invarian constructor.

---

### Resep: baca file baris

**Tipe:** resep

**Untuk apa:** olah daftar dari file teks UTF-8.

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.List;

public class BacaBaris {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("barang", ".txt");
        Files.writeString(p, "Buku\nPensil\n\nTeh\n", StandardCharsets.UTF_8);
        List<String> isi = new ArrayList<>();
        for (String baris : Files.readAllLines(p, StandardCharsets.UTF_8)) {
            if (!baris.isBlank()) {
                isi.add(baris.strip());
            }
        }
        System.out.println(isi);
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** `[Buku, Pensil, Teh]`. Baris kosong dibuang.

**Biasanya digabungkan dengan:** [readAllLines](06-exception-file-io.md#filesreadalllines), [UTF-8](06-exception-file-io.md#charset-utf-8).

**Jangan:** charset default. Jangan meninggalkan file temp di tugas (contoh ini menghapus).

---

### Resep: tulis CSV

**Tipe:** resep

**Untuk apa:** ekspor tabel sederhana. (Koma di dalam field tidak ditangani — itu CSV sungguhan.)

**Contoh implementasi:**

```java
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.List;

public class TulisCsv {
    record Barang(String nama, int harga) {}

    public static void main(String[] args) throws IOException {
        List<Barang> d = List.of(new Barang("Buku", 45000), new Barang("Teh", 5000));
        StringBuilder sb = new StringBuilder();
        sb.append("nama,harga\n");
        for (Barang b : d) {
            sb.append(b.nama()).append(',').append(b.harga()).append('\n');
        }
        Path p = Files.createTempFile("stok", ".csv");
        Files.writeString(p, sb.toString(), StandardCharsets.UTF_8);
        System.out.println(Files.readString(p));
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** header + dua baris. `StringBuilder` menghindari `+` di loop.

**Biasanya digabungkan dengan:** [StringBuilder](02-string-array.md#stringbuilder), [writeString](06-exception-file-io.md#fileswritestring).

**Jangan:** CSV dengan nama `Buku, bekas` tanpa tanda kutip — kolom pecah.

---

### Resep: Optional anti-null

**Tipe:** resep

**Untuk apa:** API pencari yang jujur: ada atau tidak.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;
import java.util.Optional;

public class OptionalAntiNull {
    static Optional<Integer> stok(Map<String, Integer> m, String sku) {
        return Optional.ofNullable(m.get(sku));
    }

    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        m.put("BK-1", 4);
        int tampil = stok(m, "BK-1").orElse(0);
        int tiada = stok(m, "XX").orElse(0);
        System.out.println(tampil + " " + tiada);
        stok(m, "BK-1").ifPresent(n -> System.out.println("ada " + n));
    }
}
```

**Yang terjadi:** `4 0` dan `ada 4`. Pemanggil tidak wajib ingat `get` bisa null.

**Biasanya digabungkan dengan:** [Optional.ofNullable](07-stream-optional-lambda.md#optionalofnullable), [containsKey](05-collections-list-set-map.md#hashmapcontainskey) jika 0 dan null beda arti.

**Jangan:** `Optional` di-`get()` di pemanggil. Jangan `Map` yang menyimpan `Optional` sebagai value.

---

### Resep: equals dan hashCode

**Tipe:** resep

**Untuk apa:** identitas bisnis (SKU) untuk `HashSet`/`HashMap`.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class EqualsHashResep {
    static class Sku {
        final String kode;
        Sku(String kode) { this.kode = kode; }
        @Override public boolean equals(Object o) {
            return o instanceof Sku s && Objects.equals(kode, s.kode);
        }
        @Override public int hashCode() { return Objects.hashCode(kode); }
    }

    public static void main(String[] args) {
        Set<Sku> s = new HashSet<>();
        s.add(new Sku("BK-1"));
        System.out.println(s.contains(new Sku("BK-1")));
        System.out.println(s.add(new Sku("BK-1")));
    }
}
```

**Yang terjadi:** `contains` true, `add` kedua false.

**Biasanya digabungkan dengan:** [hashCode](04-oop-class-inheritance.md#objecthashcode), [HashSet](05-collections-list-set-map.md#hashset).

**Jangan:** hanya `equals`. Jangan field yang berubah setelah masuk set.

---

### Resep: groupingBy

**Tipe:** resep

**Untuk apa:** kelompokkan barang per kategori.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class ResepGroup {
    record Barang(String kat, String nama) {}

    public static void main(String[] args) {
        List<Barang> d = List.of(
                new Barang("alat", "Pensil"),
                new Barang("alat", "Spidol"),
                new Barang("minum", "Teh")
        );
        Map<String, List<String>> g = d.stream()
                .collect(Collectors.groupingBy(Barang::kat,
                        Collectors.mapping(Barang::nama, Collectors.toList())));
        System.out.println(g);
    }
}
```

**Yang terjadi:** `{alat=[Pensil, Spidol], minum=[Teh]}` (urutan kunci bebas).

**Biasanya digabungkan dengan:** [groupingBy](07-stream-optional-lambda.md#collectorsgroupingby).

**Jangan:** `groupingBy` lalu mengubah list sumber di tengah.

---

### Kesalahan: == pada String

**Tipe:** jebakan

**Untuk apa:** memahami mengapa input `Scanner` “tidak sama” padahal kelihatan sama.

**Contoh implementasi:**

```java
public class SalahStringEq {
    public static void main(String[] args) {
        String a = "admin";
        String b = new String("admin");
        System.out.println("== " + (a == b));
        System.out.println("equals " + a.equals(b));
    }
}
```

**Yang terjadi:** `==` false, `equals` true. Literal kadang `==` true, input file hampir selalu false.

**Biasanya digabungkan dengan:** [equals String](02-string-array.md#equals-dan-equalsignorecase).

**Jangan:** `if (s == "keluar")`.

---

### Kesalahan: == pada Integer

**Tipe:** jebakan

**Untuk apa:** cache -128..127 membuat tes “kadang lulus”.

**Contoh implementasi:**

```java
public class SalahIntegerEq {
    public static void main(String[] args) {
        Integer x = 100;
        Integer y = 100;
        Integer p = 200;
        Integer q = 200;
        System.out.println("100 == " + (x == y));
        System.out.println("200 == " + (p == q));
        System.out.println("200 equals " + p.equals(q));
    }
}
```

**Yang terjadi:** 100 sering true, 200 sering false, `equals` true.

**Biasanya digabungkan dengan:** [cache Integer](01-tipe-primitif-wrapper.md#cache-integer).

**Jangan:** tes unit `assertSame` pada wrapper hasil hitungan.

---

### Kesalahan: pembagian int

**Tipe:** jebakan

**Untuk apa:** rata-rata yang selalu bulat.

**Contoh implementasi:**

```java
public class SalahBagiInt {
    public static void main(String[] args) {
        int jumlah = 7, n = 2;
        double salah = jumlah / n;
        double benar = jumlah / (double) n;
        System.out.println(salah);
        System.out.println(benar);
    }
}
```

**Yang terjadi:** 3.0 dan 3.5. Pembagian terjadi sebagai `int` dulu.

**Biasanya digabungkan dengan:** [pembagian int](01-tipe-primitif-wrapper.md#pembagian-int).

**Jangan:** `double rata = total / size;` jika keduanya `int`.

---

### Kesalahan: uang double

**Tipe:** jebakan

**Untuk apa:** 0.1 + 0.2 bukan 0.3.

**Contoh implementasi:**

```java
import java.math.BigDecimal;

public class SalahUang {
    public static void main(String[] args) {
        System.out.println(0.1 + 0.2);
        System.out.println((0.1 + 0.2) == 0.3);
        System.out.println(new BigDecimal("0.1").add(new BigDecimal("0.2")));
    }
}
```

**Yang terjadi:** pecahan kotor, `==` false, BigDecimal `0.3`.

**Biasanya digabungkan dengan:** [BigDecimal](01-tipe-primitif-wrapper.md#bigdecimal-uang), atau simpan sen sebagai `int`.

**Jangan:** `double saldo`. Jangan `new BigDecimal(0.1)`.

---

### Kesalahan: unboxing null

**Tipe:** jebakan

**Untuk apa:** `Integer` null + angka → NPE, bukan 0.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class SalahUnbox {
    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        try {
            int x = m.get("Buku") + 1;
            System.out.println(x);
        } catch (NullPointerException ex) {
            System.out.println("get tiada lalu + 1");
        }
        int aman = m.getOrDefault("Buku", 0) + 1;
        System.out.println(aman);
    }
}
```

**Yang terjadi:** NPE, lalu 1.

**Biasanya digabungkan dengan:** [unboxing](01-tipe-primitif-wrapper.md#unboxing), [getOrDefault](05-collections-list-set-map.md#hashmapgetordefault).

**Jangan:** `int` dari `get` map tanpa default.

---

### Kesalahan: Scanner nextInt

**Tipe:** jebakan

**Untuk apa:** `nextLine` setelah `nextInt` membaca string kosong.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class SalahNextInt {
    public static void main(String[] args) {
        Scanner in = new Scanner("2\nBuku Java\n");
        int n = in.nextInt();
        String salah = in.nextLine();
        String nama = in.nextLine();
        System.out.println("n=" + n);
        System.out.println("setelah nextInt kosong? [" + salah + "]");
        System.out.println("nama=" + nama);
        in.close();
    }
}
```

**Yang terjadi:** `salah` kosong, `nama` baru `"Buku Java"`. Tanpa `nextLine` pembuang, nama seolah hilang.

**Biasanya digabungkan dengan:** resep Scanner aman.

**Jangan:** mengira `nextInt` menghabiskan seluruh baris.

---

### Kesalahan: ConcurrentModification

**Tipe:** jebakan

**Untuk apa:** hapus saat for-each.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class SalahCme {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>(List.of("ok", "hapus", "ok"));
        try {
            for (String s : k) {
                if (s.equals("hapus")) {
                    k.remove(s);
                }
            }
        } catch (java.util.ConcurrentModificationException ex) {
            System.out.println("CME");
        }
        k.removeIf("hapus"::equals);
        System.out.println(k);
    }
}
```

**Yang terjadi:** CME, lalu `removeIf` merapikan.

**Biasanya digabungkan dengan:** [removeIf](05-collections-list-set-map.md#removeif), [Iterator](05-collections-list-set-map.md#iterator).

**Jangan:** `list.remove` di dalam for-each.

---

### Kesalahan: List.of lalu add

**Tipe:** jebakan

**Untuk apa:** list immutable.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class SalahListOf {
    public static void main(String[] args) {
        List<String> tetap = List.of("A");
        try {
            tetap.add("B");
        } catch (UnsupportedOperationException ex) {
            System.out.println("List.of beku");
        }
        List<String> hidup = new ArrayList<>(List.of("A"));
        hidup.add("B");
        System.out.println(hidup);
    }
}
```

**Yang terjadi:** exception, lalu `[A, B]`.

**Biasanya digabungkan dengan:** [List.of](05-collections-list-set-map.md#listof).

**Jangan:** `List.of` sebagai keranjang yang diisi pengguna.

---

### Kesalahan: Arrays.asList add

**Tipe:** jebakan

**Untuk apa:** `asList` boleh `set`, tidak boleh `add`.

**Contoh implementasi:**

```java
import java.util.Arrays;
import java.util.List;

public class SalahAsList {
    public static void main(String[] args) {
        String[] arr = { "A", "B" };
        List<String> v = Arrays.asList(arr);
        v.set(0, "Z");
        System.out.println(Arrays.toString(arr));
        try {
            v.add("C");
        } catch (UnsupportedOperationException ex) {
            System.out.println("asList tidak add");
        }
    }
}
```

**Yang terjadi:** array ikut `"Z"`. `add` gagal.

**Biasanya digabungkan dengan:** [Arrays.asList](02-string-array.md#arraysaslist).

**Jangan:** `asList` pada `int[]` mengira dapat `List<Integer>`.

---

### Kesalahan: HashSet tanpa hashCode

**Tipe:** jebakan

**Untuk apa:** `equals` true tetapi `contains` false.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Set;

public class SalahHash {
    static class Sku {
        String kode;
        Sku(String kode) { this.kode = kode; }
        @Override public boolean equals(Object o) {
            return o instanceof Sku s && kode.equals(s.kode);
        }
    }

    public static void main(String[] args) {
        Set<Sku> s = new HashSet<>();
        s.add(new Sku("BK-1"));
        System.out.println("contains? " + s.contains(new Sku("BK-1")));
        System.out.println("equals? " + new Sku("BK-1").equals(new Sku("BK-1")));
    }
}
```

**Yang terjadi:** `equals` true, `contains` biasanya **false** karena `hashCode` default (identitas).

**Biasanya digabungkan dengan:** resep equals/hashCode.

**Jangan:** override satu tanpa yang lain.

---

### Kesalahan: public class ≠ nama file

**Tipe:** jebakan compiler

**Untuk apa:** error *should be declared in a file named*.

**Contoh implementasi:**

File **wajib** `KasirApp.java`:

```java
public class KasirApp {
    public static void main(String[] args) {
        System.out.println("nama file = KasirApp.java");
    }
}
```

**Yang terjadi:** `javac Lain.java` berisi `public class KasirApp` ditolak.

**Biasanya digabungkan dengan:** [nama file](README.md#nama-file--nama-class).

**Jangan:** rename file di Explorer tanpa rename class.

---

### Kesalahan: static vs instance

**Tipe:** jebakan

**Untuk apa:** `non-static method cannot be referenced from a static context`.

**Contoh implementasi:**

```java
public class SalahStatic {
    int harga = 10;

    int pajak() {
        return harga * 11 / 100;
    }

    public static void main(String[] args) {
        // System.out.println(pajak()); // error
        SalahStatic o = new SalahStatic();
        System.out.println(o.pajak());
    }
}
```

**Yang terjadi:** `main` static tidak punya `this`. Objek `o` punya `harga`.

**Biasanya digabungkan dengan:** [static method](03-kontrol-method.md#static-method), [instance](03-kontrol-method.md#instance-method).

**Jangan:** membuat semua field `static` agar “error hilang”.

---

### Kesalahan: String + di loop

**Tipe:** jebakan kinerja / kejelasan

**Untuk apa:** ribuan `+` membuat banyak objek sementara.

**Contoh implementasi:**

```java
public class SalahPlusLoop {
    public static void main(String[] args) {
        String s = "";
        for (int i = 0; i < 5; i++) {
            s = s + i + ",";
        }
        System.out.println(s);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 5; i++) {
            sb.append(i).append(',');
        }
        System.out.println(sb);
    }
}
```

**Yang terjadi:** hasil sama `0,1,2,3,4,`. Builder satu buffer. Untuk 5 elemen tidak terasa; untuk puluhan ribu terasa.

**Biasanya digabungkan dengan:** [StringBuilder](02-string-array.md#stringbuilder), [join](02-string-array.md#join).

**Jangan:** merangkai HTML/CSV panjang dengan `+` di loop.

---

### Kesalahan: resource bocor

**Tipe:** jebakan

**Untuk apa:** file/reader tidak tertutup jika exception di tengah.

**Contoh implementasi:**

```java
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

public class SalahResource {
    public static void main(String[] args) throws IOException {
        Path p = Files.createTempFile("bocor", ".txt");
        try (BufferedWriter w = Files.newBufferedWriter(p)) {
            w.write("aman tertutup");
        }
        System.out.println(Files.readString(p));
        Files.deleteIfExists(p);
    }
}
```

**Yang terjadi:** try-with-resources menutup writer. Pola salah: `Writer w = ...; w.write; w.close();` — `close` terlewat jika `write` melempar.

**Biasanya digabungkan dengan:** [try-with-resources](06-exception-file-io.md#try-with-resources).

**Jangan:** `close` hanya di ujung `try` tanpa `finally`/TWR.

---

### Kesalahan: package ≠ folder

**Tipe:** jebakan

**Untuk apa:** `package toko;` harus di folder `toko/`.

**Contoh implementasi:**

```java
package toko;

public class SalahPackage {
    public static void main(String[] args) {
        System.out.println(SalahPackage.class.getName());
        System.out.println("Jalankan: java -cp out toko.SalahPackage");
    }
}
```

**Yang terjadi:** nama lengkap `toko.SalahPackage`. `java SalahPackage` dari folder salah → `could not find or load main class`.

**Biasanya digabungkan dengan:** [package](README.md#package), [classpath](README.md#classpath-dan--cp).

**Jangan:** `java toko/SalahPackage` sebagai pengganti nama class.

---

### Kesalahan: catch kosong

**Tipe:** jebakan

**Untuk apa:** program “jalan” tetapi data salah, tidak ada jejak.

**Contoh implementasi:**

```java
public class SalahCatchKosong {
    public static void main(String[] args) {
        int harga = 0;
        try {
            harga = Integer.parseInt("mahal");
        } catch (NumberFormatException ex) {
            System.out.println("input bukan angka, harga tetap " + harga);
        }
        System.out.println("dipakai: " + harga);
    }
}
```

**Yang terjadi:** pesan jelas, harga 0 sadar sebagai gagal parse. Versi `catch (Exception e) {}` akan mencetak `dipakai: 0` tanpa alasan.

**Biasanya digabungkan dengan:** [try-catch](06-exception-file-io.md#try-catch).

**Jangan:** `catch (Exception e) { e.printStackTrace(); }` di production tanpa keputusan — tetapi itu masih lebih baik daripada kosong.

---

### Tabel jangan / pakai

**Tipe:** ringkasan

**Untuk apa:** keputusan cepat saat coding.

| Jangan | Pakai |
| --- | --- |
| `==` String/wrapper | `equals` / `Objects.equals` |
| `double` uang | `int` sen atau `BigDecimal("...")` |
| `int / int` untuk rata | bagi `double` |
| `List.of` + `add` | `new ArrayList<>(List.of(...))` |
| for-each + `remove` | `removeIf` / Iterator |
| `HashSet` class tanpa `hashCode` | override berpasangan |
| `catch (Exception e) {}` | tangani atau biarkan naik |
| `String +` di loop besar | `StringBuilder` / `join` |
| `FileReader` tanpa charset | `Files.newBufferedReader(..., UTF_8)` |
| `main` 200 baris | method/class |
| field `static` untuk data objek | field instance |
| `ordinal()` ke database | `name()` |
| raw `List` | `List<String>` |

**Contoh implementasi:**

```java
import java.util.Objects;

public class TabelJanganPakai {
    public static void main(String[] args) {
        String a = "Buku";
        String b = new String("Buku");
        System.out.println(Objects.equals(a, b));
        System.out.println("Baca tabel di atas sebelum submit tugas.");
    }
}
```

**Yang terjadi:** `equals` aman null. Pengingat terakhir sebelum pengumpulan.

**Biasanya digabungkan dengan:** seluruh folder ensiklopedia ini.

**Jangan:** menghafal tabel tanpa menjalankan satu contoh pun. Ubah nilai, `javac`, `java`, lihat sendiri.

---

Kembali ke [indeks Java](README.md).
