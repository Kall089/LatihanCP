# 07 — Lambda, Optional, dan Stream

[← 06 exception](06-exception-file-io.md) · [Lanjut 08 generics →](08-generics-enum.md)

Lambda adalah fungsi pendek. Optional membungkus “ada atau kosong” tanpa `null` liar. Stream merangkai `filter`/`map`/`collect` pada data.

## Daftar isi

- [lambda](#lambda)
- [functional interface](#functional-interface)
- [Predicate](#predicate)
- [Function](#function)
- [Consumer](#consumer)
- [Supplier](#supplier)
- [BiFunction](#bifunction)
- [method reference](#method-reference)
- [Optional](#optional)
- [Optional.of](#optionalof)
- [Optional.ofNullable](#optionalofnullable)
- [Optional.empty](#optionalempty)
- [isPresent dan ifPresent](#ispresent-dan-ifpresent)
- [orElse](#orelse)
- [orElseGet](#orelseget)
- [orElseThrow](#orelsethrow)
- [Optional.map](#optionalmap)
- [Optional.filter](#optionalfilter)
- [Stream](#stream)
- [filter](#filter)
- [map](#map)
- [flatMap](#flatmap)
- [distinct](#distinct)
- [sorted](#sorted)
- [limit dan skip](#limit-dan-skip)
- [peek](#peek)
- [forEach Stream](#foreach-stream)
- [collect dan Collectors](#collect-dan-collectors)
- [Collectors.groupingBy](#collectorsgroupingby)
- [Collectors.joining](#collectorsjoining)
- [reduce](#reduce)
- [anyMatch allMatch noneMatch](#anymatch-allmatch-nonematch)
- [findFirst](#findfirst)
- [count min max](#count-min-max)
- [IntStream](#intstream)
- [toList](#tolist)
- [lazy Stream](#lazy-stream)

---

### lambda

**Tipe:** ekspresi fungsi

**Untuk apa:** menuliskan implementasi interface ber-satu method abstract (SAM) tanpa class anonim.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class LambdaDasar {
    public static void main(String[] args) {
        List<Integer> harga = new ArrayList<>(List.of(15000, 3000, 20000, 500));
        harga.removeIf(h -> h < 5000);
        harga.sort((a, b) -> Integer.compare(a, b));
        harga.forEach(h -> System.out.println("Rp" + h));
        Runnable r = () -> System.out.println("selesai");
        r.run();
    }
}
```

**Yang terjadi:** harga < 5000 hilang. Sisa terurut. Tiap elemen dicetak. `Runnable` tanpa parameter.

**Biasanya digabungkan dengan:** `removeIf`, `sort`, Stream, Optional.

**Jangan:** lambda 30 baris — buat method. Jangan menangkap variabel local yang berubah-ubah (harus effectively final).

---

### functional interface

**Tipe:** interface SAM (`@FunctionalInterface`)

**Untuk apa:** target tipe lambda. Boleh punya `default`/`static`, tetapi **satu** method abstract.

**Contoh implementasi:**

```java
public class FunctionalInterfaceDemo {
    @FunctionalInterface
    interface Diskon {
        int terapkan(int harga);
    }

    public static void main(String[] args) {
        Diskon sepuluh = h -> h * 90 / 100;
        Diskon potong2rb = h -> h - 2000;
        System.out.println(sepuluh.terapkan(10000));
        System.out.println(potong2rb.terapkan(10000));
    }
}
```

**Yang terjadi:** 9000 dan 8000. Compiler memastikan `Diskon` tetap SAM.

**Biasanya digabungkan dengan:** `Predicate`, `Function`, method yang menerima interface.

**Jangan:** menambah method abstract kedua — lambda rusak. Jangan lupa `@FunctionalInterface` agar kesalahan ketahuan.

---

### Predicate

**Tipe:** interface (`java.util.function.Predicate<T>`)

**Untuk apa:** `boolean test(T t)` — saring data.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.function.Predicate;

public class PredicateDemo {
    public static void main(String[] args) {
        Predicate<String> panjang = s -> s.length() >= 4;
        Predicate<String> hurufB = s -> s.startsWith("B");
        List<String> nama = List.of("Buku", "Teh", "Pensil", "Bola");
        nama.stream().filter(panjang.and(hurufB)).forEach(System.out::println);
        System.out.println(panjang.negate().test("Teh"));
    }
}
```

**Yang terjadi:** `Buku` dan `Bola` (panjang ≥ 4 dan awalan B). `negate` pada `"Teh"` true karena panjang 3.

**Biasanya digabungkan dengan:** `filter`, `removeIf`, `and`/`or`/`negate`.

**Jangan:** `Predicate` yang mengubah list yang sedang di-stream.

---

### Function

**Tipe:** interface (`Function<T,R>`)

**Untuk apa:** ubah `T` menjadi `R`: `apply`.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.function.Function;

public class FunctionDemo {
    public static void main(String[] args) {
        Function<String, Integer> panjang = String::length;
        Function<Integer, String> label = n -> n + " huruf";
        Function<String, String> rantai = panjang.andThen(label);
        List.of("Buku", "Teh").stream().map(rantai).forEach(System.out::println);
    }
}
```

**Yang terjadi:** `Buku` → 4 → `4 huruf`. `andThen` merangkai.

**Biasanya digabungkan dengan:** `map`, `computeIfAbsent`, `compose`.

**Jangan:** `Function` dengan side-effect berat — pakai `Consumer`.

---

### Consumer

**Tipe:** interface (`Consumer<T>`)

**Untuk apa:** menerima nilai, tidak mengembalikan: cetak, simpan, kirim.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;
import java.util.function.Consumer;

public class ConsumerDemo {
    public static void main(String[] args) {
        List<String> log = new ArrayList<>();
        Consumer<String> catat = log::add;
        Consumer<String> layar = s -> System.out.println(">> " + s);
        catat.andThen(layar).accept("stok masuk");
        System.out.println("log=" + log);
    }
}
```

**Yang terjadi:** `"stok masuk"` masuk list dan tercetak. `andThen` urutan catat lalu layar.

**Biasanya digabungkan dengan:** `forEach`, `Optional.ifPresent`.

**Jangan:** `Consumer` yang diharapkan mengembalikan nilai — itu `Function`.

---

### Supplier

**Tipe:** interface (`Supplier<T>`)

**Untuk apa:** menyediakan nilai saat diminta, tanpa argumen: lazy, factory.

**Contoh implementasi:**

```java
import java.util.Optional;
import java.util.function.Supplier;

public class SupplierDemo {
    static String mahal() {
        System.out.println("hitung mahal");
        return "cadangan";
    }

    public static void main(String[] args) {
        Supplier<String> s = () -> mahal();
        Optional<String> ada = Optional.of("Buku");
        System.out.println(ada.orElseGet(s));
        Optional<String> kosong = Optional.empty();
        System.out.println(kosong.orElseGet(s));
    }
}
```

**Yang terjadi:** `orElseGet` pada `ada` **tidak** memanggil `mahal`. Pada kosong, `hitung mahal` tercetak lalu `cadangan`.

**Biasanya digabungkan dengan:** `orElseGet`, `computeIfAbsent`, uji waktu.

**Jangan:** `orElse(mahal())` jika `mahal` mahal — ia **selalu** dievaluasi.

---

### BiFunction

**Tipe:** interface (`BiFunction<T,U,R>`)

**Untuk apa:** dua argumen, satu hasil. `Map.merge` memakainya.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class BiFunctionDemo {
    public static void main(String[] args) {
        Map<String, Integer> stok = new HashMap<>();
        stok.merge("Buku", 1, Integer::sum);
        stok.merge("Buku", 2, Integer::sum);
        stok.merge("Teh", 5, (lama, baru) -> lama + baru);
        System.out.println(stok);
    }
}
```

**Yang terjadi:** Buku 1+2=3, Teh 5. `merge` membuat kunci jika belum ada, atau menggabungkan nilai.

**Biasanya digabungkan dengan:** histogram, `reduce` dua sumber.

**Jangan:** `merge` dengan fungsi yang return `null` — kunci dihapus.

---

### method reference

**Tipe:** sintaks `Kelas::method`

**Untuk apa:** lambda yang hanya memanggil method yang sudah ada.

**Contoh implementasi:**

```java
import java.util.List;

public class MethodRefDemo {
    static String besar(String s) {
        return s.toUpperCase();
    }

    public static void main(String[] args) {
        List.of("buku", "teh").stream()
                .map(MethodRefDemo::besar)
                .map(String::strip)
                .forEach(System.out::println);
        List<String> nama = List.of("A", "B");
        String[] arr = nama.stream().toArray(String[]::new);
        System.out.println(arr.length);
    }
}
```

**Yang terjadi:** `BUKU` dan `TEH`. `String[]::new` constructor reference untuk `toArray`.

**Biasanya digabungkan dengan:** `map`, `filter` (`Objects::nonNull`), `comparing`.

**Jangan:** method ref jika argumen perlu diubah dulu — tetap lambda.

---

### Optional

**Tipe:** class (`java.util.Optional<T>`)

**Untuk apa:** menyatakan hasil yang mungkin absen, memaksa pemanggil memilih `orElse`/`ifPresent`/`orElseThrow`.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalDasar {
    static Optional<Integer> stok(String sku) {
        if ("BK-1".equals(sku)) {
            return Optional.of(8);
        }
        return Optional.empty();
    }

    public static void main(String[] args) {
        stok("BK-1").ifPresent(n -> System.out.println("stok=" + n));
        int cadangan = stok("XX").orElse(0);
        System.out.println("cadangan=" + cadangan);
    }
}
```

**Yang terjadi:** `BK-1` mencetak 8. `XX` memakai 0.

**Biasanya digabungkan dengan:** `map`/`flatMap`, Stream `findFirst`.

**Jangan:** `Optional` sebagai field mutable yang sering di-set. Jangan `Optional` untuk collections — kembalikan list kosong. Jangan `get()` tanpa cek.

---

### Optional.of

**Tipe:** method static

**Untuk apa:** membungkus nilai **non-null**. `null` → NPE segera.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalOf {
    public static void main(String[] args) {
        Optional<String> a = Optional.of("Buku");
        System.out.println(a.get());
        try {
            Optional.of(null);
        } catch (NullPointerException ex) {
            System.out.println("of(null) meledak");
        }
    }
}
```

**Yang terjadi:** `get` `"Buku"`. `of(null)` gagal di tempat, bukan nanti.

**Biasanya digabungkan dengan:** nilai yang sudah jelas ada.

**Jangan:** `of` pada hasil yang bisa null — pakai `ofNullable`.

---

### Optional.ofNullable

**Tipe:** method static

**Untuk apa:** `null` menjadi `empty`, selain itu `of`.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalOfNullable {
    public static void main(String[] args) {
        String input = null;
        String nama = Optional.ofNullable(input).orElse("Tamu");
        System.out.println(nama);
        System.out.println(Optional.ofNullable("Haikal").orElse("Tamu"));
    }
}
```

**Yang terjadi:** `Tamu` lalu `Haikal`.

**Biasanya digabungkan dengan:** API lama yang return `null`.

**Jangan:** `ofNullable` lalu `get()` langsung.

---

### Optional.empty

**Tipe:** method static

**Untuk apa:** instance kosong bersama.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalEmpty {
    public static void main(String[] args) {
        Optional<String> o = Optional.empty();
        System.out.println(o.isPresent());
        System.out.println(o.isEmpty());
        System.out.println(o.orElse("kosong"));
    }
}
```

**Yang terjadi:** false, true (Java 11+ `isEmpty`), teks `kosong`.

**Biasanya digabungkan dengan:** return awal method pencari.

**Jangan:** `return null` dari method yang bertipe `Optional`.

---

### isPresent dan ifPresent

**Tipe:** method

**Untuk apa:** `isPresent` boolean. `ifPresent` menjalankan `Consumer` jika ada.

**Contoh implementasi:**

```java
import java.util.Optional;

public class IfPresentDemo {
    public static void main(String[] args) {
        Optional<String> a = Optional.of("Teh");
        Optional<String> b = Optional.empty();
        if (a.isPresent()) {
            System.out.println(a.get());
        }
        a.ifPresent(v -> System.out.println("ada " + v));
        b.ifPresent(v -> System.out.println("tidak jalan"));
        a.ifPresentOrElse(
                v -> System.out.println("ok " + v),
                () -> System.out.println("tidak ada"));
    }
}
```

**Yang terjadi:** `Teh`, `ada Teh`, `ok Teh`. Cabang empty tidak mencetak di `ifPresent`.

**Biasanya digabungkan dengan:** side-effect tampilan.

**Jangan:** `if (isPresent()) get()` berulang — pakai `ifPresent`/`orElse`/`map`.

---

### orElse

**Tipe:** method

**Untuk apa:** nilai cadangan, **selalu dievaluasi** sebelum/saat panggilan.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OrElseDemo {
    static String cadangan() {
        System.out.println("buat cadangan");
        return "N/A";
    }

    public static void main(String[] args) {
        System.out.println(Optional.of("Buku").orElse(cadangan()));
        System.out.println(Optional.empty().orElse("N/A"));
    }
}
```

**Yang terjadi:** `buat cadangan` tercetak **meski** Optional berisi `"Buku"`, lalu `Buku`. Empty mencetak `N/A`.

**Biasanya digabungkan dengan:** konstanta murah (`orElse(0)`, `orElse("")`).

**Jangan:** `orElse(hitungMahal())` — pakai `orElseGet`.

---

### orElseGet

**Tipe:** method

**Untuk apa:** cadangan lazy lewat `Supplier`.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OrElseGetDemo {
    public static void main(String[] args) {
        String a = Optional.of("Ada").orElseGet(() -> {
            System.out.println("tidak dipanggil");
            return "X";
        });
        String b = Optional.<String>empty().orElseGet(() -> "X");
        System.out.println(a + " / " + b);
    }
}
```

**Yang terjadi:** `"tidak dipanggil"` tidak muncul. Hasil `Ada / X`.

**Biasanya digabungkan dengan:** factory, baca default file.

**Jangan:** `orElseGet(null)` — NPE saat empty.

---

### orElseThrow

**Tipe:** method

**Untuk apa:** kosong → lempar exception. Tanpa argumen: `NoSuchElementException`.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OrElseThrowDemo {
    public static void main(String[] args) {
        String ada = Optional.of("BK-1").orElseThrow();
        System.out.println(ada);
        try {
            Optional.empty().orElseThrow(() -> new IllegalStateException("SKU wajib"));
        } catch (IllegalStateException ex) {
            System.out.println(ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `BK-1`. Empty melempar pesan `SKU wajib`.

**Biasanya digabungkan dengan:** alur yang memang error jika data absen.

**Jangan:** `orElseThrow` lalu menangkap di baris berikutnya sebagai pengganti `orElse`.

---

### Optional.map

**Tipe:** method

**Untuk apa:** jika ada, terapkan fungsi; jika fungsi return null, jadi empty.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalMap {
    public static void main(String[] args) {
        Optional<String> nama = Optional.of("  Buku  ");
        Optional<Integer> n = nama.map(String::strip).map(String::length);
        System.out.println(n.orElse(0));
        Optional<String> kosong = Optional.<String>empty().map(String::toUpperCase);
        System.out.println(kosong.isEmpty());
    }
}
```

**Yang terjadi:** panjang 4. Empty tetap empty, `toUpperCase` tidak dipanggil.

**Biasanya digabungkan dengan:** `filter`, `flatMap` jika fungsi sudah return `Optional`.

**Jangan:** `map` yang return `Optional` — jadi `Optional<Optional<T>>`. Pakai `flatMap`.

---

### Optional.filter

**Tipe:** method

**Untuk apa:** jika nilai gagal predikat, jadi empty.

**Contoh implementasi:**

```java
import java.util.Optional;

public class OptionalFilter {
    public static void main(String[] args) {
        Optional<Integer> stok = Optional.of(3);
        System.out.println(stok.filter(n -> n > 0).orElse(-1));
        System.out.println(stok.filter(n -> n > 10).orElse(-1));
    }
}
```

**Yang terjadi:** 3 lolos predikat > 0. Predikat > 10 gagal → -1.

**Biasanya digabungkan dengan:** validasi setelah `ofNullable`.

**Jangan:** `filter` dengan predikat yang NPE pada nilai.

---

### Stream

**Tipe:** interface (`java.util.stream.Stream`)

**Untuk apa:** pipa operasi pada elemen: saring, ubah, kumpulkan. Tidak mengubah sumber kecuali kamu sengaja di terminal side-effect.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamDasar {
    public static void main(String[] args) {
        List<String> menu = List.of("Nasi goreng", "Teh", "Pisang goreng", "Kopi");
        List<String> goreng = menu.stream()
                .filter(s -> s.contains("goreng"))
                .map(String::toUpperCase)
                .toList();
        System.out.println(goreng);
        System.out.println("sumber utuh: " + menu);
    }
}
```

**Yang terjadi:** `[NASI GORENG, PISANG GORENG]`. `menu` tidak berubah (`List.of` juga immutable).

**Biasanya digabungkan dengan:** `List.stream()`, `Files.lines`, `Optional.stream`.

**Jangan:** memakai ulang `Stream` setelah terminal (`toList`, `forEach`) — `IllegalStateException`. Jangan Stream untuk 3 elemen jika for-biasa lebih jelas, kecuali latihan.

---

### filter

**Tipe:** method Stream (intermediate)

**Untuk apa:** loloskan elemen yang predikatnya true.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamFilter {
    public static void main(String[] args) {
        List<Integer> nilai = List.of(80, 40, 90, 55, 70);
        long lulus = nilai.stream().filter(n -> n >= 70).count();
        System.out.println("lulus=" + lulus);
        nilai.stream().filter(n -> n < 0).findAny().ifPresent(n -> System.out.println(n));
    }
}
```

**Yang terjadi:** 3 nilai ≥ 70. Tidak ada negatif, `ifPresent` diam.

**Biasanya digabungkan dengan:** `map`, `count`, `toList`.

**Jangan:** `filter` + `get(0)` pada list hasil — pakai `findFirst`.

---

### map

**Tipe:** method Stream

**Untuk apa:** 1 elemen → 1 elemen baru.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamMap {
    public static void main(String[] args) {
        List<String> nama = List.of("buku", "pensil");
        List<Integer> panjang = nama.stream().map(String::length).toList();
        List<String> label = nama.stream().map(s -> s + " (" + s.length() + ")").toList();
        System.out.println(panjang);
        System.out.println(label);
    }
}
```

**Yang terjadi:** `[4, 6]` dan label beranotasi panjang.

**Biasanya digabungkan dengan:** `mapToInt` jika hasil primitif.

**Jangan:** `map` yang `add` ke list luar — pakai `collect`.

---

### flatMap

**Tipe:** method Stream

**Untuk apa:** 1 elemen → 0..n elemen, lalu diratakan.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamFlatMap {
    public static void main(String[] args) {
        List<List<String>> rak = List.of(
                List.of("Buku", "Pensil"),
                List.of("Teh"),
                List.of()
        );
        List<String> datar = rak.stream().flatMap(List::stream).toList();
        System.out.println(datar);
        List<String> kata = List.of("nasi goreng", "es teh");
        List<String> pecah = kata.stream()
                .flatMap(s -> List.of(s.split(" ")).stream())
                .toList();
        System.out.println(pecah);
    }
}
```

**Yang terjadi:** `[Buku, Pensil, Teh]`. Kata pecah `[nasi, goreng, es, teh]`.

**Biasanya digabungkan dengan:** list bersarang, `Optional::stream`.

**Jangan:** `map` jika hasilnya Stream/List yang ingin diratakan.

---

### distinct

**Tipe:** method Stream

**Untuk apa:** unik menurut `equals`/`hashCode`, menjaga urutan pertama.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamDistinct {
    public static void main(String[] args) {
        List<String> sku = List.of("A", "B", "A", "C", "B");
        System.out.println(sku.stream().distinct().toList());
    }
}
```

**Yang terjadi:** `[A, B, C]`.

**Biasanya digabungkan dengan:** `map` lowercase dulu agar `A`/`a` menyatu.

**Jangan:** `distinct` pada objek tanpa `equals`.

---

### sorted

**Tipe:** method Stream

**Untuk apa:** urut; butuh `Comparable` atau `Comparator`. Tidak men-sort list sumber.

**Contoh implementasi:**

```java
import java.util.Comparator;
import java.util.List;

public class StreamSorted {
    public static void main(String[] args) {
        List<String> nama = List.of("jeruk", "Apel", "mangga");
        System.out.println(nama.stream().sorted().toList());
        System.out.println(nama.stream().sorted(String.CASE_INSENSITIVE_ORDER).toList());
        System.out.println(nama.stream().sorted(Comparator.comparing(String::length)).toList());
    }
}
```

**Yang terjadi:** urutan ASCII, lalu abaikan kapital, lalu panjang.

**Biasanya digabungkan dengan:** `reversed()`, `thenComparing`.

**Jangan:** `sorted()` pada Stream yang elemennya tidak comparable.

---

### limit dan skip

**Tipe:** method Stream

**Untuk apa:** paginasi: lewati `skip`, ambil `limit`.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.stream.IntStream;

public class SkipLimit {
    public static void main(String[] args) {
        List<Integer> halaman = IntStream.rangeClosed(1, 20).boxed().toList();
        int page = 2, size = 5;
        List<Integer> isi = halaman.stream().skip((page - 1) * size).limit(size).toList();
        System.out.println(isi);
    }
}
```

**Yang terjadi:** halaman 2: 6..10.

**Biasanya digabungkan dengan:** `sorted` sebelum paginasi.

**Jangan:** `skip` jutaan pada sumber mahal tanpa index DB — itu latihan, bukan produksi besar.

---

### peek

**Tipe:** method Stream

**Untuk apa:** melihat elemen di tengah pipa (debug). Tidak mengganti elemen.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamPeek {
    public static void main(String[] args) {
        List<String> hasil = List.of("a", "bb", "c").stream()
                .peek(s -> System.out.println("sebelum " + s))
                .filter(s -> s.length() == 1)
                .peek(s -> System.out.println("lolos " + s))
                .toList();
        System.out.println(hasil);
    }
}
```

**Yang terjadi:** debug tercetak, hasil `[a, c]`. Tanpa terminal `toList`, `peek` **tidak** jalan (lazy).

**Biasanya digabungkan dengan:** belajar pipa, bukan produksi.

**Jangan:** `peek` untuk mutasi bisnis — pakai `map`/`forEach`.

---

### forEach Stream

**Tipe:** method terminal

**Untuk apa:** side-effect per elemen. Tidak mengembalikan stream.

**Contoh implementasi:**

```java
import java.util.List;

public class StreamForEach {
    public static void main(String[] args) {
        List.of(3, 1, 2).stream().sorted().forEach(n -> System.out.print(n + " "));
        System.out.println();
    }
}
```

**Yang terjadi:** `1 2 3 `. Urutan `forEach` pada stream sekuensial mengikuti pipa; parallel tidak dijamin.

**Biasanya digabungkan dengan:** cetak, `System.out::println`.

**Jangan:** `forEach` + `add` ke `ArrayList` bersama `parallelStream` tanpa list aman thread.

---

### collect dan Collectors

**Tipe:** method terminal / class

**Untuk apa:** kumpulkan ke `List`, `Set`, `Map`, string, ringkasan.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.stream.Collectors;

public class CollectorsDemo {
    public static void main(String[] args) {
        List<String> nama = List.of("Buku", "Teh", "Buku", "Kopi");
        Set<String> unik = nama.stream().collect(Collectors.toSet());
        List<String> list = nama.stream().collect(Collectors.toList());
        Map<String, Integer> panjang = nama.stream().distinct()
                .collect(Collectors.toMap(s -> s, String::length));
        System.out.println(unik);
        System.out.println(list);
        System.out.println(panjang);
    }
}
```

**Yang terjadi:** set tanpa duplikat (urutan bebas). `toList()` collector **mutable**. `toMap` 3 kunci.

**Biasanya digabungkan dengan:** `groupingBy`, `joining`, `toList()` Java 16 (immutable).

**Jangan:** `toMap` jika kunci duplikat tanpa merge function — exception.

---

### Collectors.groupingBy

**Tipe:** collector

**Untuk apa:** kelompokkan ke `Map<K, List<T>>` (atau downstream lain).

**Contoh implementasi:**

```java
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class GroupingByDemo {
    record Barang(String jenis, String nama) {}

    public static void main(String[] args) {
        List<Barang> daftar = List.of(
                new Barang("alat", "Pensil"),
                new Barang("alat", "Penghapus"),
                new Barang("minum", "Teh")
        );
        Map<String, List<Barang>> g = daftar.stream()
                .collect(Collectors.groupingBy(Barang::jenis));
        System.out.println(g.keySet());
        System.out.println(g.get("alat").size());
        Map<String, Long> hitung = daftar.stream()
                .collect(Collectors.groupingBy(Barang::jenis, Collectors.counting()));
        System.out.println(hitung);
    }
}
```

**Yang terjadi:** dua jenis. `alat` size 2. counting `{alat=2, minum=1}`.

**Biasanya digabungkan dengan:** `mapping`, `joining` downstream.

**Jangan:** mengubah list sumber saat collect.

---

### Collectors.joining

**Tipe:** collector

**Untuk apa:** gabung string dengan pemisah, awalan, akhiran.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.stream.Collectors;

public class JoiningDemo {
    public static void main(String[] args) {
        String csv = List.of("Buku", "Pensil", "Teh").stream()
                .collect(Collectors.joining(","));
        String html = List.of("A", "B").stream()
                .collect(Collectors.joining("</li><li>", "<ul><li>", "</li></ul>"));
        System.out.println(csv);
        System.out.println(html);
    }
}
```

**Yang terjadi:** `Buku,Pensil,Teh` dan potongan HTML list.

**Biasanya digabungkan dengan:** `map(Object::toString)`, `String.join` jika tanpa pipa.

**Jangan:** `joining` pada Stream bukan CharSequence tanpa `map` dulu.

---

### reduce

**Tipe:** method terminal

**Untuk apa:** menggabungkan elemen jadi satu nilai: jumlah, max, gabung custom.

**Contoh implementasi:**

```java
import java.util.List;

public class ReduceDemo {
    public static void main(String[] args) {
        List<Integer> harga = List.of(15000, 3000, 2000);
        int total = harga.stream().reduce(0, Integer::sum);
        int max = harga.stream().reduce(Integer::max).orElse(0);
        System.out.println(total);
        System.out.println(max);
        String gabung = List.of("A", "B", "C").stream().reduce("", (a, b) -> a + b);
        System.out.println(gabung);
    }
}
```

**Yang terjadi:** 20000, 15000, `ABC`. Identity `0` untuk sum; tanpa identity, hasil `Optional`.

**Biasanya digabungkan dengan:** `mapToInt(x -> x).sum()` lebih jelas untuk angka.

**Jangan:** `reduce` string di loop besar — `StringBuilder`/`joining` lebih baik.

---

### anyMatch allMatch noneMatch

**Tipe:** method terminal short-circuit

**Untuk apa:** pertanyaan ya/tidak pada pipa, berhenti lebih awal jika sudah ketahuan.

**Contoh implementasi:**

```java
import java.util.List;

public class MatchDemo {
    public static void main(String[] args) {
        List<Integer> stok = List.of(3, 0, 5);
        System.out.println(stok.stream().anyMatch(n -> n == 0));
        System.out.println(stok.stream().allMatch(n -> n >= 0));
        System.out.println(stok.stream().noneMatch(n -> n < 0));
        System.out.println(List.<Integer>of().stream().allMatch(n -> false));
    }
}
```

**Yang terjadi:** ada 0 → true. Semua ≥ 0 → true. Tidak ada negatif → true. `allMatch` pada stream **kosong** adalah **true** (vakuum logika).

**Biasanya digabungkan dengan:** validasi, `filter` tidak perlu jika hanya boolean.

**Jangan:** mengira `allMatch` pada kosong false.

---

### findFirst

**Tipe:** method terminal

**Untuk apa:** `Optional` elemen pertama (urut stream). `findAny` boleh mana saja (berguna parallel).

**Contoh implementasi:**

```java
import java.util.List;

public class FindFirstDemo {
    public static void main(String[] args) {
        String ketemu = List.of("Teh", "Buku", "Kopi").stream()
                .filter(s -> s.startsWith("B"))
                .findFirst()
                .orElse("tidak ada");
        System.out.println(ketemu);
        System.out.println(List.of("Teh").stream().filter(s -> s.startsWith("B")).findFirst().isEmpty());
    }
}
```

**Yang terjadi:** `Buku`. Filter kosong → empty → `isEmpty` true.

**Biasanya digabungkan dengan:** `filter`, `orElseThrow`.

**Jangan:** `findFirst().get()` tanpa cadangan.

---

### count min max

**Tipe:** method terminal

**Untuk apa:** `count` long. `min`/`max` butuh `Comparator`, hasil `Optional`.

**Contoh implementasi:**

```java
import java.util.Comparator;
import java.util.List;

public class CountMinMax {
    public static void main(String[] args) {
        List<String> nama = List.of("Teh", "Buku", "Penghapus");
        System.out.println(nama.stream().count());
        System.out.println(nama.stream().min(Comparator.comparing(String::length)).orElse(""));
        System.out.println(nama.stream().max(Comparator.naturalOrder()).orElse(""));
    }
}
```

**Yang terjadi:** 3, `Teh` (terpendek), `Teh` atau `Penghapus` tergantung `naturalOrder` string (`Penghapus` vs `Teh`: `Penghapus` sebelum `Teh`? P < T jadi min natural `Buku`/`Penghapus`/`Teh` — max natural `Teh`). Cetak apa adanya dari program.

**Biasanya digabungkan dengan:** `mapToInt` + `max` IntStream.

**Jangan:** `max` tanpa comparator pada non-Comparable.

---

### IntStream

**Tipe:** stream primitif

**Untuk apa:** menghindari boxing `Integer` pada hitungan: `range`, `sum`, `average`.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.stream.IntStream;

public class IntStreamDemo {
    public static void main(String[] args) {
        System.out.println(IntStream.range(0, 5).sum());
        System.out.println(IntStream.rangeClosed(1, 5).sum());
        List<Integer> harga = List.of(10, 20, 30);
        int total = harga.stream().mapToInt(Integer::intValue).sum();
        System.out.println(total);
        IntStream.rangeClosed(1, 3).mapToObj(i -> "item-" + i).forEach(System.out::println);
    }
}
```

**Yang terjadi:** `range` 0..4 sum 10. `rangeClosed` 1..5 sum 15. Total 60. Tiga label `item-`.

**Biasanya digabungkan dengan:** `average().orElse(0)`, `summaryStatistics`.

**Jangan:** `range` mengira akhir inklusif.

---

### toList

**Tipe:** method terminal (Java 16+)

**Untuk apa:** kumpulkan ke list **unmodifiable**. Lebih pendek dari `collect(Collectors.toList())`.

**Contoh implementasi:**

```java
import java.util.List;

public class ToListDemo {
    public static void main(String[] args) {
        List<String> a = List.of("x", "y").stream().map(String::toUpperCase).toList();
        System.out.println(a);
        try {
            a.add("Z");
        } catch (UnsupportedOperationException ex) {
            System.out.println("toList() beku");
        }
    }
}
```

**Yang terjadi:** `[X, Y]`, `add` ditolak. `Collectors.toList()` biasanya `ArrayList` yang bisa diubah.

**Biasanya digabungkan dengan:** pipa pendek Java 16+.

**Jangan:** `toList()` lalu `set` jika kamu butuh list hidup — kumpulkan ke `ArrayList`.

---

### lazy Stream

**Tipe:** sifat pipa

**Untuk apa:** operasi intermediate tidak jalan sampai ada **terminal**. Berguna + mudah membingungkan saat debug.

**Contoh implementasi:**

```java
import java.util.List;
import java.util.stream.Stream;

public class LazyStream {
    public static void main(String[] args) {
        Stream<String> s = List.of("A", "B", "C").stream()
                .filter(x -> {
                    System.out.println("filter " + x);
                    return true;
                });
        System.out.println("belum terminal");
        System.out.println(s.toList());
    }
}
```

**Yang terjadi:** `belum terminal` tercetak **sebelum** `filter A/B/C`. Baru `toList` memicu pipa.

**Biasanya digabungkan dengan:** `limit` yang memotong kerja (short-circuit).

**Jangan:** mengira `filter` di baris deklarasi sudah memproses. Jangan side-effect di intermediate yang kamu andalkan sebelum terminal.

---

Lanjut ke [08 — generics dan enum](08-generics-enum.md).
