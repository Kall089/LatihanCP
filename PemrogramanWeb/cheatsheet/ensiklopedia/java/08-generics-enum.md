# 08 — Generics dan enum

[← 07 stream](07-stream-optional-lambda.md) · [Lanjut 09 resep →](09-resep-dan-kesalahan.md)

Generics menuliskan tipe di dalam `<>` agar `List` bukan campur aduk. Enum adalah kumpulan konstanta bernama. `Comparable`/`Comparator` mengatur urutan.

## Daftar isi

- [generic class](#generic-class)
- [generic method](#generic-method)
- [diamond](#diamond)
- [raw type](#raw-type)
- [type erasure](#type-erasure)
- [bounded T extends](#bounded-t-extends)
- [wildcard ?](#wildcard-)
- [wildcard extends](#wildcard-extends)
- [wildcard super](#wildcard-super)
- [PECS](#pecs)
- [enum](#enum)
- [enum values](#enum-values)
- [enum valueOf](#enum-valueof)
- [enum ordinal](#enum-ordinal)
- [enum field dan method](#enum-field-dan-method)
- [switch pada enum](#switch-pada-enum)
- [EnumSet](#enumset)
- [EnumMap](#enummap)
- [Comparable](#comparable)
- [Comparator](#comparator)
- [Comparator.comparing](#comparatorcomparing)
- [record dan generics](#record-dan-generics)
- [@Deprecated](#deprecated)
- [@SuppressWarnings](#suppresswarnings)

---

### generic class

**Tipe:** class berparameter tipe

**Untuk apa:** satu implementasi, banyak tipe isi. Contoh: kotak yang bisa menaruh `String` atau `Barang`, bukan `Object` plus cast.

**Contoh implementasi:**

```java
public class GenericClassDemo {
    static class Kotak<T> {
        private T isi;
        void taruh(T nilai) { this.isi = nilai; }
        T ambil() { return isi; }
    }

    public static void main(String[] args) {
        Kotak<String> nama = new Kotak<>();
        nama.taruh("Buku");
        System.out.println(nama.ambil().toUpperCase());
        Kotak<Integer> harga = new Kotak<>();
        harga.taruh(45000);
        System.out.println(harga.ambil() + 1);
        // nama.taruh(12); // error kompilasi
    }
}
```

**Yang terjadi:** `ambil` pada `Kotak<String>` sudah `String` — `toUpperCase` tanpa cast. `Integer` di-unbox saat `+ 1`. Salah tipe ditolak `javac`.

**Biasanya digabungkan dengan:** collections, `Optional<T>`, method generic.

**Jangan:** `Kotak` raw (`Kotak k = new Kotak();`) di kode baru. Jangan `T` pada field `static` instance-level (static tidak punya `T`).

---

### generic method

**Tipe:** method dengan `<T>` sendiri

**Untuk apa:** tipe parameter mengikuti argumen panggilan, tidak harus dari class.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class GenericMethodDemo {
    static <T> T pertama(List<T> list) {
        if (list.isEmpty()) {
            throw new IllegalArgumentException("kosong");
        }
        return list.get(0);
    }

    static <T> List<T> dua(T a, T b) {
        List<T> r = new ArrayList<>();
        r.add(a);
        r.add(b);
        return r;
    }

    public static void main(String[] args) {
        System.out.println(pertama(List.of("Buku", "Teh")));
        System.out.println(dua(1, 2));
    }
}
```

**Yang terjadi:** compiler menyimpulkan `T=String` lalu `T=Integer`. Cetak `Buku` dan `[1, 2]`.

**Biasanya digabungkan dengan:** utilitas `Collections`, helper salin.

**Jangan:** `<T>` yang tidak muncul di parameter/return — tidak berguna. Jangan bingungkan dengan wildcard di pemanggil.

---

### diamond

**Tipe:** operator `<>` (Java 7+)

**Untuk apa:** tidak mengulang tipe di kanan constructor.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class DiamondDemo {
    public static void main(String[] args) {
        List<String> a = new ArrayList<>();
        Map<String, List<Integer>> m = new HashMap<>();
        m.put("Buku", new ArrayList<>());
        m.get("Buku").add(3);
        a.add("ok");
        System.out.println(a + " " + m);
    }
}
```

**Yang terjadi:** `ArrayList<>` menyalin parameter dari kiri (`List<String>`, `List<Integer>`). Map terisi.

**Biasanya digabungkan dengan:** `var` (`var list = new ArrayList<String>();` — tipe di kanan).

**Jangan:** `new ArrayList()` tanpa `<>` dan tanpa tipe kiri yang jelas — raw. Jangan diamond pada anonymous class di Java lama (kini sudah lebih longgar).

---

### raw type

**Tipe:** generic tanpa `<>` (warisan pra-Java 5)

**Untuk apa:** kompatibilitas. Di kode baru: **jangan**.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class RawTypeDemo {
    public static void main(String[] args) {
        List raw = new ArrayList();
        raw.add("Buku");
        raw.add(42);
        List<String> pura = raw;
        try {
            for (String s : pura) {
                System.out.println(s.toUpperCase());
            }
        } catch (ClassCastException ex) {
            System.out.println("heap pollution: " + ex);
        }
    }
}
```

**Yang terjadi:** compiler mungkin hanya warning. Saat loop, `42` tidak bisa jadi `String` → `ClassCastException`. Ini “heap pollution”.

**Biasanya digabungkan dengan:** migrasi kode kuno, lalu perbaiki.

**Jangan:** mematikan warning dan lanjut. Jangan `List` tanpa parameter di API baru.

---

### type erasure

**Tipe:** perilaku compiler/JVM

**Untuk apa:** memahami mengapa `List<String>` dan `List<Integer>` adalah `List` yang sama di runtime, dan mengapa tidak bisa `new T()`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class TypeErasureDemo {
    public static void main(String[] args) {
        List<String> a = new ArrayList<>();
        List<Integer> b = new ArrayList<>();
        System.out.println(a.getClass() == b.getClass());
        System.out.println(a instanceof List);
        // if (a instanceof List<String>) {} // tidak valid seperti yang diharapkan siswa
    }
}
```

**Yang terjadi:** kedua class runtime sama (`ArrayList`). Informasi `<String>` dihapus (erasure) setelah `javac` memasang cast.

**Biasanya digabungkan dengan:** penjelasan “mengapa tidak overload `f(List<String>)` dan `f(List<Integer>)`”.

**Jangan:** `new T()` atau `T[] arr = new T[10]` — ilegal. Pakai factory/`ArrayList`.

---

### bounded T extends

**Tipe:** bound generic

**Untuk apa:** `T` harus turunan tipe tertentu agar method induk aman dipanggil.

**Contoh implementasi:**

```java
public class BoundedDemo {
    static class Bentuk {
        double luas() { return 0; }
    }
    static class Kotak extends Bentuk {
        double s;
        Kotak(double s) { this.s = s; }
        @Override double luas() { return s * s; }
    }

    static <T extends Bentuk> double totalLuas(java.util.List<T> list) {
        double s = 0;
        for (T b : list) {
            s += b.luas();
        }
        return s;
    }

    public static void main(String[] args) {
        System.out.println(totalLuas(java.util.List.of(new Kotak(2), new Kotak(3))));
    }
}
```

**Yang terjadi:** 4+9=13. `T extends Bentuk` mengizinkan `luas()`. `List<String>` ditolak.

**Biasanya digabungkan dengan:** `T extends Comparable<T>`, multiple bound `T extends A & B`.

**Jangan:** `T extends` class **dan** ingin masih menerima tipe tak terkait. Jangan bound jika `T` benar-benar bebas.

---

### wildcard ?

**Tipe:** `List<?>` unknown

**Untuk apa:** “list bertipe suatu hal yang tidak kita sebut”. Bisa **baca** sebagai `Object`, hampir tidak bisa `add` (kecuali `null`).

**Contoh implementasi:**

```java
import java.util.List;

public class WildcardDemo {
    static void cetak(List<?> list) {
        for (Object o : list) {
            System.out.println(o);
        }
        // list.add("x"); // error
        list.add(null);
    }

    public static void main(String[] args) {
        cetak(List.of("A", "B"));
        cetak(List.of(1, 2));
    }
}
```

**Yang terjadi:** method menerima kedua list. `add` selain `null` ditolak compiler — menjaga keamanan tipe.

**Biasanya digabungkan dengan:** method yang hanya membaca, atau `? extends`/`? super`.

**Jangan:** `List<?>` sebagai field yang sering diisi berbagai add. Pakai tipe konkret atau generic method `<T>`.

---

### wildcard extends

**Tipe:** `<? extends T>` (producer)

**Untuk apa:** list yang elemennya **T atau anaknya**. Aman dibaca sebagai `T`. Tidak aman menambah (kecuali null).

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ExtendsWildcard {
    static double jumlah(List<? extends Number> list) {
        double s = 0;
        for (Number n : list) {
            s += n.doubleValue();
        }
        return s;
    }

    public static void main(String[] args) {
        System.out.println(jumlah(List.of(1, 2, 3)));
        System.out.println(jumlah(List.of(1.5, 2.5)));
        List<? extends Number> w = new ArrayList<Integer>();
        // w.add(1); // error
        System.out.println(w.size());
    }
}
```

**Yang terjadi:** 6.0 dan 4.0. `add(1)` pada `? extends Number` ditolak: compiler tidak tahu list itu `Integer` atau `Double`.

**Biasanya digabungkan dengan:** PECS “producer extends”.

**Jangan:** `List<? extends T>` lalu `add` elemen `T`.

---

### wildcard super

**Tipe:** `<? super T>` (consumer)

**Untuk apa:** list yang bisa menampung `T` (tipe induk). Aman `add(T)`. Baca hanya sebagai `Object`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class SuperWildcard {
    static void masukkan(List<? super Integer> tujuan, Integer nilai) {
        tujuan.add(nilai);
    }

    public static void main(String[] args) {
        List<Number> angka = new ArrayList<>();
        List<Object> apaSaja = new ArrayList<>();
        masukkan(angka, 7);
        masukkan(apaSaja, 8);
        System.out.println(angka);
        System.out.println(apaSaja);
        Object o = angka.get(0);
        System.out.println(o);
    }
}
```

**Yang terjadi:** 7 masuk `List<Number>`, 8 masuk `List<Object>`. `get` bertipe `Object`.

**Biasanya digabungkan dengan:** `Collections.copy`, Comparator `<? super T>`.

**Jangan:** mengira `get` mengembalikan `Integer`.

---

### PECS

**Tipe:** aturan (Producer Extends, Consumer Super)

**Untuk apa:** mengingat kapan `extends` vs `super`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class PecsDemo {
    static <T> void salin(List<? extends T> sumber, List<? super T> tujuan) {
        for (T x : sumber) {
            tujuan.add(x);
        }
    }

    public static void main(String[] args) {
        List<Integer> src = List.of(1, 2);
        List<Number> dst = new ArrayList<>();
        salin(src, dst);
        System.out.println(dst);
    }
}
```

**Yang terjadi:** `Integer` (producer) dibaca, ditulis ke `Number` (consumer). `[1, 2]`.

**Biasanya digabungkan dengan:** API collections, method helper.

**Jangan:** memakai `List<T>` kaku di kedua sisi lalu gagal memanggil dengan `List<Integer>` dan `List<Number>`.

---

### enum

**Tipe:** tipe khusus (class `final` berinstance tetap)

**Untuk apa:** kumpulan nilai bernama: status pesanan, hari, tingkat member. Lebih aman daripada `int` kode atau string magis.

**Contoh implementasi:**

```java
public class EnumDasar {
    enum Status {
        BARU, DIPROSES, SELESAI, BATAL
    }

    public static void main(String[] args) {
        Status s = Status.DIPROSES;
        System.out.println(s);
        System.out.println(s == Status.DIPROSES);
        System.out.println(s.equals(Status.BARU));
        // s = "DIPROSES"; // error
    }
}
```

**Yang terjadi:** cetak `DIPROSES`. `==` sah untuk enum (instance tunggal). String tidak bisa diisi ke variabel `Status`.

**Biasanya digabungkan dengan:** `switch`, `EnumMap`, field tambahan.

**Jangan:** status sebagai `"selesai"` string di 10 file. Jangan `new Status()` — tidak ada constructor publik.

---

### enum values

**Tipe:** method static generated

**Untuk apa:** array semua konstanta, urutan deklarasi.

**Contoh implementasi:**

```java
public class EnumValues {
    enum Hari { SENIN, SELASA, RABU, KAMIS, JUMAT, SABTU, MINGGU }

    public static void main(String[] args) {
        for (Hari h : Hari.values()) {
            System.out.println(h.name());
        }
        System.out.println("jumlah=" + Hari.values().length);
    }
}
```

**Yang terjadi:** tujuh nama tercetak. `values()` mengembalikan **array baru** tiap panggilan.

**Biasanya digabungkan dengan:** isi combo box, tes lengkap.

**Jangan:** mengubah array hasil `values()` lalu mengira enum berubah — itu salinan, tetapi tetap jangan andalkan mutasi.

---

### enum valueOf

**Tipe:** method static generated

**Untuk apa:** parse nama konstanta **persis** (huruf besar/kecil dihitung).

**Contoh implementasi:**

```java
public class EnumValueOf {
    enum Status { BARU, SELESAI }

    public static void main(String[] args) {
        Status s = Status.valueOf("BARU");
        System.out.println(s);
        try {
            Status.valueOf("baru");
        } catch (IllegalArgumentException ex) {
            System.out.println("nama harus persis: " + ex.getMessage());
        }
    }
}
```

**Yang terjadi:** `"BARU"` sukses. `"baru"` exception.

**Biasanya digabungkan dengan:** `strip`/`toUpperCase` sebelum parse jika input pengguna.

**Jangan:** `valueOf` pada teks bebas tanpa `try`. Jangan bingung dengan `Enum.valueOf(Status.class, nama)`.

---

### enum ordinal

**Tipe:** method instance

**Untuk apa:** posisi 0-based di deklarasi. Berguna internal, **buruk** sebagai ID yang disimpan ke file/DB jangka panjang.

**Contoh implementasi:**

```java
public class EnumOrdinal {
    enum Tingkat { BASIC, PREMIUM, VIP }

    public static void main(String[] args) {
        for (Tingkat t : Tingkat.values()) {
            System.out.println(t + " -> " + t.ordinal());
        }
        System.out.println(Tingkat.PREMIUM.compareTo(Tingkat.BASIC));
    }
}
```

**Yang terjadi:** 0,1,2. `compareTo` positif karena PREMIUM setelah BASIC.

**Biasanya digabungkan dengan:** urutan alami enum, **bukan** skema persistensi.

**Jangan:** menyimpan `ordinal()` ke CSV semester lalu menyisip konstanta baru di tengah — data lama bergeser. Simpan `name()`.

---

### enum field dan method

**Tipe:** enum sebagai class penuh

**Untuk apa:** tiap konstanta punya data dan perilaku.

**Contoh implementasi:**

```java
public class EnumField {
    enum Paket {
        BASIC(0),
        PREMIUM(15),
        VIP(25);

        private final int diskon;

        Paket(int diskon) {
            this.diskon = diskon;
        }

        int hargaAkhir(int kotor) {
            return kotor - kotor * diskon / 100;
        }
    }

    public static void main(String[] args) {
        int kotor = 100_000;
        for (Paket p : Paket.values()) {
            System.out.println(p + " -> " + p.hargaAkhir(kotor));
        }
    }
}
```

**Yang terjadi:** 100000, 85000, 75000. Constructor enum `private` implisit.

**Biasanya digabungkan dengan:** `switch` yang memanggil method, daripada `switch` berisi rumus.

**Jangan:** enum yang mutable (setter field) — membingungkan. Jangan logika 200 baris per konstanta tanpa pecah.

---

### switch pada enum

**Tipe:** kontrol + enum

**Untuk apa:** cabang lengkap; compiler bisa mengingatkan case kurang (tergantung opsi/`switch` expression).

**Contoh implementasi:**

```java
public class SwitchEnum {
    enum Status { BARU, DIPROSES, SELESAI }

    static String label(Status s) {
        return switch (s) {
            case BARU -> "baru masuk";
            case DIPROSES -> "sedang dikemas";
            case SELESAI -> "selesai";
        };
    }

    public static void main(String[] args) {
        System.out.println(label(Status.DIPROSES));
    }
}
```

**Yang terjadi:** `sedang dikemas`. Expression tanpa `default` sah karena semua konstanta tertutup.

**Biasanya digabungkan dengan:** `enum` status, UI.

**Jangan:** `switch (s.name())` string jika sudah punya enum. Jangan lupa: `s` null → NPE.

---

### EnumSet

**Tipe:** class (`java.util.EnumSet`)

**Untuk apa:** set khusus enum, sangat hemat dan cepat (bit vector).

**Contoh implementasi:**

```java
import java.util.EnumSet;
import java.util.Set;

public class EnumSetDemo {
    enum Izin { BACA, TULIS, HAPUS }

    public static void main(String[] args) {
        Set<Izin> admin = EnumSet.allOf(Izin.class);
        Set<Izin> tamu = EnumSet.of(Izin.BACA);
        Set<Izin> editor = EnumSet.of(Izin.BACA, Izin.TULIS);
        System.out.println(admin.contains(Izin.HAPUS));
        System.out.println(tamu.contains(Izin.HAPUS));
        System.out.println(editor);
    }
}
```

**Yang terjadi:** admin true, tamu false, editor `{BACA, TULIS}`.

**Biasanya digabungkan dengan:** flag izin, `EnumSet.noneOf`, `complementOf`.

**Jangan:** `HashSet<Enum>` tanpa alasan. Jangan `EnumSet` untuk non-enum.

---

### EnumMap

**Tipe:** class (`java.util.EnumMap`)

**Untuk apa:** map berkunci enum, array internal, iterasi urutan enum.

**Contoh implementasi:**

```java
import java.util.EnumMap;
import java.util.Map;

public class EnumMapDemo {
    enum Status { BARU, SELESAI }

    public static void main(String[] args) {
        Map<Status, Integer> hitung = new EnumMap<>(Status.class);
        hitung.put(Status.BARU, 3);
        hitung.merge(Status.BARU, 1, Integer::sum);
        hitung.put(Status.SELESAI, 10);
        System.out.println(hitung);
        System.out.println(hitung.get(Status.BARU));
    }
}
```

**Yang terjadi:** BARU=4, SELESAI=10. Constructor wajib `Class<Status>`.

**Biasanya digabungkan dengan:** histogram status, `computeIfAbsent`.

**Jangan:** `EnumMap` tanpa class token. Jangan kunci `null`.

---

### Comparable

**Tipe:** interface (`Comparable<T>`)

**Untuk apa:** urutan alami objek: `compareTo` negatif/0/positif. Dipakai `TreeSet`, `Collections.sort` tanpa comparator.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class ComparableDemo {
    static class Barang implements Comparable<Barang> {
        final String nama;
        final int harga;
        Barang(String nama, int harga) {
            this.nama = nama;
            this.harga = harga;
        }
        @Override
        public int compareTo(Barang o) {
            return Integer.compare(this.harga, o.harga);
        }
        @Override
        public String toString() {
            return nama + "=" + harga;
        }
    }

    public static void main(String[] args) {
        List<Barang> list = new ArrayList<>();
        list.add(new Barang("Buku", 45000));
        list.add(new Barang("Pensil", 3000));
        Collections.sort(list);
        System.out.println(list);
    }
}
```

**Yang terjadi:** Pensil dulu (lebih murah). `Integer.compare` aman dari overflow.

**Biasanya digabungkan dengan:** `equals` konsisten jika masuk `TreeSet` (disarankan).

**Jangan:** `return this.harga - o.harga` untuk sebarang `int`. Jangan urutan alami yang berubah-ubah tiap hari.

---

### Comparator

**Tipe:** interface (`Comparator<T>`)

**Untuk apa:** urutan **eksternal**: bisa banyak cara sort tanpa mengubah class.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class ComparatorDemo {
    static class Barang {
        final String nama;
        final int harga;
        Barang(String n, int h) { nama = n; harga = h; }
        @Override public String toString() { return nama + "=" + harga; }
    }

    public static void main(String[] args) {
        List<Barang> list = new ArrayList<>();
        list.add(new Barang("Buku", 45000));
        list.add(new Barang("Pensil", 3000));
        list.add(new Barang("Album", 3000));
        list.sort(Comparator.comparingInt((Barang b) -> b.harga)
                .thenComparing(b -> b.nama));
        System.out.println(list);
        list.sort(Comparator.comparing((Barang b) -> b.nama).reversed());
        System.out.println(list);
    }
}
```

**Yang terjadi:** harga naik, nama sebagai tie-break (`Album` sebelum `Pensil`). Lalu nama Z–A.

**Biasanya digabungkan dengan:** `list.sort`, Stream `sorted`, `TreeMap`.

**Jangan:** comparator yang `equals` tidak selaras jika dipakai di `TreeSet` sebagai ordering. Jangan `(a,b) -> a.harga - b.harga`.

---

### Comparator.comparing

**Tipe:** method static

**Untuk apa:** membangun comparator dari getter, bisa dirantai.

**Contoh implementasi:**

```java
import java.util.Arrays;
import java.util.Comparator;

public class ComparingDemo {
    public static void main(String[] args) {
        String[] nama = { "Buku", "teh", "Pensil" };
        Arrays.sort(nama, Comparator.comparingInt(String::length)
                .thenComparing(String.CASE_INSENSITIVE_ORDER));
        System.out.println(Arrays.toString(nama));
        Arrays.sort(nama, Comparator.comparing(String::toLowerCase));
        System.out.println(Arrays.toString(nama));
    }
}
```

**Yang terjadi:** terpendek dulu (`teh`), lalu alfabet longgar. Sort kedua murni lowercase.

**Biasanya digabungkan dengan:** `nullsFirst`/`nullsLast`.

**Jangan:** `comparing` pada getter yang NPE tanpa `nullsFirst`.

---

### record dan generics

**Tipe:** kombinasi

**Untuk apa:** pasangan tipe aman: `record Pasangan<A,B>(A kiri, B kanan)`.

**Contoh implementasi:**

```java
public class RecordGeneric {
    record Pasangan<A, B>(A kiri, B kanan) {}

    public static void main(String[] args) {
        Pasangan<String, Integer> p = new Pasangan<>("Buku", 45000);
        System.out.println(p.kiri() + " Rp" + p.kanan());
        Pasangan<Integer, Integer> titik = new Pasangan<>(3, 4);
        System.out.println(titik);
    }
}
```

**Yang terjadi:** accessor `kiri`/`kanan` bertipe tepat. `toString` record otomatis.

**Biasanya digabungkan dengan:** return dua nilai tanpa class panjang, kunci map.

**Jangan:** record generic mutable di dalamnya tanpa salinan.

---

### @Deprecated

**Tipe:** anotasi

**Untuk apa:** menandai API yang tidak disarankan. Compiler memperingatkan pemakaian.

**Contoh implementasi:**

```java
public class DeprecatedDemo {
    @Deprecated(since = "1.1", forRemoval = false)
    static int totalLama(int a, int b) {
        return a + b;
    }

    static int total(int a, int b) {
        return a + b;
    }

    public static void main(String[] args) {
        System.out.println(total(1, 2));
        System.out.println(totalLama(1, 2));
    }
}
```

**Yang terjadi:** program mencetak 3 dua kali. IDE/`javac -Xlint` menandai `totalLama`.

**Biasanya digabungkan dengan:** Javadoc `@deprecated`, method pengganti.

**Jangan:** menghapus method publik semalaman tanpa deprecated dulu di library. Jangan menandai semua kode latihan.

---

### @SuppressWarnings

**Tipe:** anotasi

**Untuk apa:** mematikan peringatan **sempit** yang sudah kamu pahami (unchecked, deprecation).

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class SuppressDemo {
    @SuppressWarnings("unchecked")
    static List<String> dariRaw() {
        List raw = new ArrayList();
        raw.add("Buku");
        return raw;
    }

    public static void main(String[] args) {
        System.out.println(dariRaw());
    }
}
```

**Yang terjadi:** warning unchecked di method itu diredam. List berisi `Buku`.

**Biasanya digabungkan dengan:** jembatan ke API raw, komentar *mengapa* aman.

**Jangan:** `@SuppressWarnings("all")` di class. Jangan menekan warning alih-alih memakai generics benar.

---

Lanjut ke [09 — resep dan kesalahan](09-resep-dan-kesalahan.md).
