# 02 — String dan array

[← 01 tipe](01-tipe-primitif-wrapper.md) · [Lanjut 03 kontrol & method →](03-kontrol-method.md)

`String` adalah class **immutable**: setiap ubahan menghasilkan objek baru. Array adalah wadah berukuran tetap. Untuk daftar yang tumbuh, pakai `ArrayList` di bab 05.

## Daftar isi

- [String](#string)
- [Literal versus new String](#literal-versus-new-string)
- [Immutability](#immutability)
- [length](#length)
- [isEmpty dan isBlank](#isempty-dan-isblank)
- [charAt](#charat)
- [substring](#substring)
- [indexOf dan lastIndexOf](#indexof-dan-lastindexof)
- [contains](#contains)
- [startsWith dan endsWith](#startswith-dan-endswith)
- [equals dan equalsIgnoreCase](#equals-dan-equalsignorecase)
- [compareTo](#compareto)
- [toLowerCase dan toUpperCase](#tolowercase-dan-touppercase)
- [trim dan strip](#trim-dan-strip)
- [replace dan replaceAll](#replace-dan-replaceall)
- [split](#split)
- [join](#join)
- [concat dan +](#concat-dan-)
- [format dan formatted](#format-dan-formatted)
- [String.valueOf](#stringvalueof)
- [toCharArray](#tochararray)
- [matches](#matches)
- [repeat](#repeat)
- [text block](#text-block)
- [StringBuilder](#stringbuilder)
- [StringBuffer](#stringbuffer)
- [intern](#intern)
- [array 1 dimensi](#array-1-dimensi)
- [array 2 dimensi](#array-2-dimensi)
- [length pada array](#length-pada-array)
- [Arrays.toString](#arraystostring)
- [Arrays.sort](#arrayssort)
- [Arrays.fill](#arraysfill)
- [Arrays.copyOf](#arrayscopyof)
- [Arrays.equals](#arraysequals)
- [Arrays.binarySearch](#arraysbinarysearch)
- [System.arraycopy](#systemarraycopy)
- [for-each pada array](#for-each-pada-array)
- [varargs](#varargs)
- [Arrays.asList](#arraysaslist)
- [null versus array kosong](#null-versus-array-kosong)

---

### String

**Tipe:** class (`java.lang.String`)

**Untuk apa:** menyimpan teks: nama toko, pesan error, isi file, input pengguna.

**Contoh implementasi:**

```java
public class ContohString {
    public static void main(String[] args) {
        String toko = "Toko Belajar";
        String sapaan = "Halo, " + toko;
        System.out.println(sapaan);
        System.out.println("Panjang: " + sapaan.length());
        System.out.println("Class: " + sapaan.getClass().getName());
    }
}
```

**Yang terjadi:** literal `"Toko Belajar"` adalah objek `String`. Operator `+` membuat string baru `"Halo, Toko Belajar"`. `length()` menghitung unit `char` (UTF-16), di sini 18 termasuk spasi dan koma.

**Biasanya digabungkan dengan:** `Scanner.nextLine()`, tulis file, dan `StringBuilder` jika dirangkai di loop.

**Jangan:** memakai `String` untuk sandi yang harus dihapus dari memori (lebih dekat ke `char[]` di konteks keamanan). Jangan mengira `String` bisa diubah di tempat.

---

### Literal versus new String

**Tipe:** cara membuat objek `String`

**Untuk apa:** memahami pool literal. `new String("x")` memaksa objek baru di heap.

**Contoh implementasi:**

```java
public class LiteralVsNew {
    public static void main(String[] args) {
        String a = "Buku";
        String b = "Buku";
        String c = new String("Buku");
        String d = c.intern();
        System.out.println("a == b ? " + (a == b));
        System.out.println("a == c ? " + (a == c));
        System.out.println("a.equals(c) ? " + a.equals(c));
        System.out.println("a == d ? " + (a == d));
    }
}
```

**Yang terjadi:** `a` dan `b` merujuk literal yang sama di pool: `==` true. `c` objek berbeda: `==` false, `equals` true. `intern()` mengembalikan referensi pool, jadi `a == d` true.

**Biasanya digabungkan dengan:** `equals` sebagai perbandingan resmi.

**Jangan:** menulis `new String("teks")` di kode biasa — sia-sia. Jangan menguji kesamaan teks dengan `==`.

---

### Immutability

**Tipe:** sifat class `String`

**Untuk apa:** menjamin isi string tidak berubah setelah dibuat. Method seperti `toUpperCase` mengembalikan **salinan**.

**Contoh implementasi:**

```java
public class StringImmutable {
    public static void main(String[] args) {
        String judul = "pemrograman java";
        String besar = judul.toUpperCase();
        System.out.println("asli: " + judul);
        System.out.println("baru: " + besar);
        judul.concat(" edisi 2");
        System.out.println("setelah concat dibuang: " + judul);
        judul = judul.concat(" edisi 2");
        System.out.println("setelah ditampung: " + judul);
    }
}
```

**Yang terjadi:** `judul` tetap huruf kecil sampai kamu **menugaskan ulang**. `concat` tanpa menampung hasil tidak mengubah apa pun. Inilah sebabnya `replace` yang tidak disimpan tampak “tidak jalan”.

**Biasanya digabungkan dengan:** `final String` untuk referensi yang tidak diganti, dan `StringBuilder` untuk mutasi banyak.

**Jangan:** memanggil `nama.toLowerCase();` lalu memakai `nama` dan heran masih campur huruf.

---

### length

**Tipe:** method (`String.length`)

**Untuk apa:** menghitung jumlah `char` (bukan selalu “jumlah huruf yang mata lihat” untuk emoji).

**Contoh implementasi:**

```java
public class StringLength {
    public static void main(String[] args) {
        String nama = "Haikal";
        String kosong = "";
        String spasi = " ";
        System.out.println(nama.length());
        System.out.println("kosong=" + kosong.length());
        System.out.println("spasi=" + spasi.length());
        String campuran = "A😊";
        System.out.println("A + emoji length=" + campuran.length());
        System.out.println("codePointCount=" + campuran.codePointCount(0, campuran.length()));
    }
}
```

**Yang terjadi:** `"Haikal"` = 6. `""` = 0. `" "` = 1. Emoji sering 2 unit `char`, jadi `length` bisa 3 sementara `codePointCount` 2.

**Biasanya digabungkan dengan:** loop `for (int i = 0; i < s.length(); i++)` dan validasi “minimal 3 karakter”.

**Jangan:** mengira `length` adalah field seperti array. Pada `String` ia **method**: `s.length()`.

---

### isEmpty dan isBlank

**Tipe:** method (`String`)

**Untuk apa:** `isEmpty` = panjang 0. `isBlank` (Java 11+) = kosong atau hanya whitespace.

**Contoh implementasi:**

```java
public class EmptyBlank {
    public static void main(String[] args) {
        String[] uji = { "", "  ", "\t", "Buku", " B " };
        for (String s : uji) {
            System.out.println("[" + s + "] empty=" + s.isEmpty()
                    + " blank=" + s.isBlank());
        }
    }
}
```

**Yang terjadi:** `""` empty dan blank. `"  "` dan tab **bukan** empty, tetapi blank. `"Buku"` keduanya false. `" B "` bukan blank.

**Biasanya digabungkan dengan:** `trim()`/`strip()` sebelum simpan nama.

**Jangan:** `if (s.length() == 0)` jika yang kamu maksud “pengguna hanya menekan spasi”. Pakai `isBlank`.

---

### charAt

**Tipe:** method (`String.charAt`)

**Untuk apa:** mengambil satu `char` di indeks 0-based.

**Contoh implementasi:**

```java
public class ContohCharAt {
    public static void main(String[] args) {
        String kode = "SKU-42A";
        System.out.println("pertama=" + kode.charAt(0));
        System.out.println("terakhir=" + kode.charAt(kode.length() - 1));
        int huruf = 0;
        for (int i = 0; i < kode.length(); i++) {
            if (Character.isLetter(kode.charAt(i))) {
                huruf++;
            }
        }
        System.out.println("huruf=" + huruf);
        try {
            kode.charAt(99);
        } catch (StringIndexOutOfBoundsException ex) {
            System.out.println("Indeks liar: " + ex.getClass().getSimpleName());
        }
    }
}
```

**Yang terjadi:** `'S'` dan `'A'`. Huruf dihitung 4 (`S`,`K`,`U`,`A`). Indeks 99 melempar exception, bukan `null`.

**Biasanya digabungkan dengan:** `Character.isDigit`, parsing kode manual.

**Jangan:** `charAt(s.length())` — indeks terakhir adalah `length-1`.

---

### substring

**Tipe:** method (`String.substring`)

**Untuk apa:** potong teks. `substring(begin)` sampai akhir. `substring(begin, end)` **end eksklusif**.

**Contoh implementasi:**

```java
public class ContohSubstring {
    public static void main(String[] args) {
        String sku = "BK-JAVA-01";
        String awalan = sku.substring(0, 2);
        String sisa = sku.substring(3);
        String tengah = sku.substring(3, 7);
        System.out.println(awalan);
        System.out.println(sisa);
        System.out.println(tengah);
        System.out.println("[" + "Haikal".substring(2, 2) + "]");
    }
}
```

**Yang terjadi:** `"BK"`, `"JAVA-01"`, `"JAVA"`. `substring(2,2)` string kosong. Indeks `end` tidak ikut.

**Biasanya digabungkan dengan:** `indexOf` untuk mencari batas potong.

**Jangan:** mengira `end` inklusif seperti sebagian bahasa. Jangan `substring` dengan `end < begin`.

---

### indexOf dan lastIndexOf

**Tipe:** method (`String`)

**Untuk apa:** mencari posisi substring atau `char`. Tidak ketemu → `-1`.

**Contoh implementasi:**

```java
public class ContohIndexOf {
    public static void main(String[] args) {
        String email = "haikal.muzho@kampus.ac.id";
        int at = email.indexOf('@');
        int titik = email.lastIndexOf('.');
        System.out.println("posisi @ = " + at);
        System.out.println("titik terakhir = " + titik);
        if (at > 0) {
            System.out.println("lokal: " + email.substring(0, at));
            System.out.println("domain: " + email.substring(at + 1));
        }
        System.out.println("cari xyz: " + email.indexOf("xyz"));
        System.out.println("indexOf dari 10: " + email.indexOf('.', 10));
    }
}
```

**Yang terjadi:** `@` ketemu di tengah. `lastIndexOf('.')` menunjuk `.id` atau `.ac` tergantung string — di contoh, titik terakhir sebelum `id`. `"xyz"` → -1. Overload dari indeks 10 mencari titik setelah posisi itu.

**Biasanya digabungkan dengan:** `if (index >= 0)` sebelum `substring`.

**Jangan:** memakai hasil `-1` sebagai indeks `substring` — exception. Jangan mengira `indexOf` regex; itu teks biasa.

---

### contains

**Tipe:** method (`String.contains`)

**Untuk apa:** cek substring tanpa peduli posisi.

**Contoh implementasi:**

```java
public class ContohContains {
    public static void main(String[] args) {
        String judul = "Buku Pemrograman Java Dasar";
        System.out.println(judul.contains("Java"));
        System.out.println(judul.contains("java"));
        System.out.println(judul.toLowerCase().contains("java"));
        System.out.println(judul.contains("Python"));
    }
}
```

**Yang terjadi:** `"Java"` true, `"java"` false (huruf besar dihitung). Setelah `toLowerCase`, true. `"Python"` false.

**Biasanya digabungkan dengan:** filter daftar judul, dan `toLowerCase` untuk pencarian longgar.

**Jangan:** `contains(null)` — `NullPointerException`.

---

### startsWith dan endsWith

**Tipe:** method (`String`)

**Untuk apa:** cek awalan/akhiran: ekstensi file, protokol URL, kode SKU.

**Contoh implementasi:**

```java
public class AwalanAkhiran {
    public static void main(String[] args) {
        String file = "daftar-barang.csv";
        String url = "https://toko.local/buku";
        System.out.println(file.endsWith(".csv"));
        System.out.println(file.endsWith(".CSV"));
        System.out.println(url.startsWith("https://"));
        System.out.println(file.startsWith("daftar", 0));
    }
}
```

**Yang terjadi:** `.csv` true, `.CSV` false. `https://` true. Overload `startsWith` dengan offset 0 sama seperti biasa.

**Biasanya digabungkan dengan:** `toLowerCase` pada ekstensi, dan `Path` di bab 06 untuk file sungguhan.

**Jangan:** memotong string manual hanya untuk cek ekstensi jika `endsWith` cukup.

---

### equals dan equalsIgnoreCase

**Tipe:** method (`String`)

**Untuk apa:** membandingkan isi. `equalsIgnoreCase` mengabaikan kapital.

**Contoh implementasi:**

```java
public class StringEquals {
    public static void main(String[] args) {
        String a = "Admin";
        String b = new String("Admin");
        String c = "admin";
        System.out.println(a.equals(b));
        System.out.println(a.equals(c));
        System.out.println(a.equalsIgnoreCase(c));
        String kosong = null;
        System.out.println("aman: " + "Admin".equals(kosong));
        try {
            System.out.println(kosong.equals("Admin"));
        } catch (NullPointerException ex) {
            System.out.println("null.equals meledak");
        }
    }
}
```

**Yang terjadi:** `a.equals(b)` true. `equals` biasa dengan `"admin"` false. `equalsIgnoreCase` true. `"Admin".equals(null)` false **tanpa** NPE. `null.equals(...)` NPE.

**Biasanya digabungkan dengan:** konstanta di kiri (`"ya".equals(input)`), atau `Objects.equals`.

**Jangan:** `==` untuk teks dari `Scanner` atau file. Jangan `s.equalsIgnoreCase(null)` — tetap NPE pada receiver null.

---

### compareTo

**Tipe:** method (`Comparable`)

**Untuk apa:** urutan leksikografis. Negatif jika `this` di depan, 0 jika sama, positif jika di belakang.

**Contoh implementasi:**

```java
public class StringCompareTo {
    public static void main(String[] args) {
        System.out.println("apel".compareTo("apel"));
        System.out.println("apel".compareTo("jeruk"));
        System.out.println("jeruk".compareTo("apel"));
        System.out.println("Apel".compareTo("apel"));
        System.out.println("apel".compareToIgnoreCase("Apel"));
        String[] buah = { "jeruk", "apel", "mangga" };
        java.util.Arrays.sort(buah);
        System.out.println(java.util.Arrays.toString(buah));
    }
}
```

**Yang terjadi:** 0 untuk sama. `"apel"` sebelum `"jeruk"` (negatif). Huruf besar `A` di ASCII sebelum `a`, jadi `"Apel"` lebih kecil dari `"apel"`. `compareToIgnoreCase` 0. `Arrays.sort` memakai `compareTo`: `apel, jeruk, mangga`.

**Biasanya digabungkan dengan:** `Arrays.sort`, `TreeSet`, `TreeMap`.

**Jangan:** memakai hasil `compareTo` selain tanda (negatif/0/positif). Jangan mengurut nama orang tanpa `Collator` jika butuh urutan bahasa Indonesia yang ketat.

---

### toLowerCase dan toUpperCase

**Tipe:** method (`String`)

**Untuk apa:** menyeragamkan huruf sebelum banding atau simpan.

**Contoh implementasi:**

```java
import java.util.Locale;

public class HurufBesarKecil {
    public static void main(String[] args) {
        String merek = "NaSa GoReNg";
        System.out.println(merek.toLowerCase());
        System.out.println(merek.toUpperCase());
        System.out.println(merek);
        String i = "I";
        System.out.println("TR: " + i.toLowerCase(Locale.forLanguageTag("tr")));
        System.out.println("ROOT: " + i.toLowerCase(Locale.ROOT));
    }
}
```

**Yang terjadi:** cetak `nasa goreng` dan `NASA GORENG`. `merek` asli utuh. Locale Turki mengubah `I` menjadi `ı` tanpa titik — alasan memakai `Locale.ROOT` untuk token sistem.

**Biasanya digabungkan dengan:** `equals` setelah dinormalisasi, email, kode kupon.

**Jangan:** menormalisasi nama tampilan manusia tanpa izin (nama diri punya kapital khusus).

---

### trim dan strip

**Tipe:** method (`String`)

**Untuk apa:** membuang whitespace ujung. `trim` memakai definisi lama (kode ≤ 32 plus beberapa). `strip` (Java 11+) memakai Unicode whitespace.

**Contoh implementasi:**

```java
public class TrimStrip {
    public static void main(String[] args) {
        String nama = "  Haikal  ";
        System.out.println("[" + nama.trim() + "]");
        System.out.println("[" + nama.strip() + "]");
        System.out.println("[" + nama.stripLeading() + "]");
        System.out.println("[" + nama.stripTrailing() + "]");
        String unicode = "\u2003Haikal\u2003";
        System.out.println("trim len=" + unicode.trim().length());
        System.out.println("strip len=" + unicode.strip().length());
    }
}
```

**Yang terjadi:** spasi biasa hilang di keduanya. `stripLeading` hanya kiri, trailing hanya kanan. Spatium Unicode `\u2003` sering **lolos `trim`** tetapi tertangkap `strip`.

**Biasanya digabungkan dengan:** input form, `parseInt(s.trim())`.

**Jangan:** `trim` lalu mengira semua “spasi yang kelihatan” hilang. Di Java 11+ lebih aman `strip`.

---

### replace dan replaceAll

**Tipe:** method (`String`)

**Untuk apa:** `replace` menukar `char` atau substring **literal**. `replaceAll` menukar dengan **regex**.

**Contoh implementasi:**

```java
public class StringReplace {
    public static void main(String[] args) {
        String tel = "(021) 555-1212";
        String digit = tel.replace("(", "").replace(")", "").replace(" ", "").replace("-", "");
        System.out.println(digit);
        String titik = "a.b.c";
        System.out.println("replace literal: " + titik.replace(".", "-"));
        System.out.println("replaceAll regex: " + titik.replaceAll(".", "-"));
        System.out.println("replaceAll escaped: " + titik.replaceAll("\\.", "-"));
        System.out.println("replaceFirst: " + titik.replaceFirst("\\.", "-"));
    }
}
```

**Yang terjadi:** telepon jadi `0215551212`. `replace(".", "-")` menukar tiap titik. `replaceAll(".", "-")` menukar **setiap karakter** karena `.` di regex artinya apa saja. `\\.` memperbaiki. `replaceFirst` hanya titik pertama.

**Biasanya digabungkan dengan:** normalisasi input, dan `Pattern` jika regex rumit.

**Jangan:** `replaceAll` untuk teks biasa yang mengandung `( ) . * +`. Pakai `replace` atau `replaceAll(Pattern.quote(x), ...)`.

---

### split

**Tipe:** method (`String.split`)

**Untuk apa:** memecah teks jadi `String[]` menurut regex pemisah.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ContohSplit {
    public static void main(String[] args) {
        String csv = "Buku,Pensil,Penghapus";
        String[] barang = csv.split(",");
        System.out.println(Arrays.toString(barang));
        System.out.println("jumlah=" + barang.length);
        String raw = "Buku|Pensil|Penghapus";
        System.out.println(Arrays.toString(raw.split("\\|")));
        String kosongTengah = "a,,b";
        System.out.println(Arrays.toString(kosongTengah.split(",", -1)));
        String kalimat = "satu   dua\ttiga";
        System.out.println(Arrays.toString(kalimat.split("\\s+")));
    }
}
```

**Yang terjadi:** tiga barang. `|` harus di-escape. `split(",", -1)` menjaga token kosong di antara koma. `\\s+` memecah spasi/tab beruntun.

**Biasanya digabungkan dengan:** `trim` tiap token, dan `Integer.parseInt` untuk CSV angka.

**Jangan:** `split(".")` tanpa escape — memecah per karakter (atau hasil aneh). Jangan lupa limit: `split(",", 2)` hanya dua potong.

---

### join

**Tipe:** method static (`String.join`)

**Untuk apa:** menggabungkan potongan dengan pemisah, tanpa koma berlebih di ujung.

**Contoh implementasi:**

```java
import java.util.List;

public class ContohJoin {
    public static void main(String[] args) {
        String csv = String.join(",", "Buku", "Pensil", "Penghapus");
        String path = String.join("/", "home", "haikal", "toko");
        String dariList = String.join(" | ", List.of("Nasi", "Teh", "Gorengan"));
        System.out.println(csv);
        System.out.println(path);
        System.out.println(dariList);
    }
}
```

**Yang terjadi:** `Buku,Pensil,Penghapus` tanpa koma di ekor. Path memakai `/`. List jadi `Nasi | Teh | Gorengan`.

**Biasanya digabungkan dengan:** `split` kebalikannya, dan `Collectors.joining` di Stream.

**Jangan:** merangkai di loop dengan `s = s + "," + x` lalu memotong koma terakhir jika `join` tersedia.

---

### concat dan +

**Tipe:** method / operator

**Untuk apa:** menempelkan teks. `+` juga memanggil `String.valueOf` pada non-string.

**Contoh implementasi:**

```java
public class ConcatPlus {
    public static void main(String[] args) {
        String a = "Toko";
        String b = a.concat(" Belajar");
        String c = a + " " + 2026;
        System.out.println(b);
        System.out.println(c);
        System.out.println(1 + 2 + " barang");
        System.out.println("barang " + 1 + 2);
        String nullan = null;
        System.out.println("isi:" + nullan);
    }
}
```

**Yang terjadi:** `concat` butuh `String` di kanan. `1+2+" barang"` = `"3 barang"` karena `+` kiri-ke-kanan (angka dulu). `"barang "+1+2` = `"barang 12"`. `null` digabung menjadi teks `"null"`, bukan NPE.

**Biasanya digabungkan dengan:** pesan log pendek.

**Jangan:** `+` di dalam loop ribuan kali. Pakai `StringBuilder`. Jangan `a.concat(null)` — NPE, beda dengan `+`.

---

### format dan formatted

**Tipe:** method (`String.format` / Java 15 `formatted`)

**Untuk apa:** menyisipkan nilai ke pola: `%s` teks, `%d` int, `%f` pecahan, `%n` newline.

**Contoh implementasi:**

```java
public class StringFormat {
    public static void main(String[] args) {
        String nama = "Buku Java";
        int harga = 45000;
        double diskon = 0.1;
        String a = String.format("%s seharga Rp%,d", nama, harga);
        String b = "Diskon %.0f%% jadi Rp%.0f".formatted(diskon * 100, harga * (1 - diskon));
        System.out.println(a);
        System.out.println(b);
        System.out.printf("Stok %+d%n", -3);
    }
}
```

**Yang terjadi:** `%,d` menambah pemisah ribuan sesuai locale default. `formatted` mengisi dua placeholder. `printf` menulis langsung ke `System.out`; `%n` newline portabel.

**Biasanya digabungkan dengan:** struk, log, `Locale` eksplisit (`String.format(Locale.US, ...)`).

**Jangan:** mencampur jumlah placeholder dan argumen. Jangan memakai `%d` untuk `double`.

---

### String.valueOf

**Tipe:** method static

**Untuk apa:** mengubah apa saja jadi teks dengan aman, termasuk `null` → `"null"`.

**Contoh implementasi:**

```java
public class StringValueOf {
    public static void main(String[] args) {
        System.out.println(String.valueOf(42));
        System.out.println(String.valueOf(true));
        System.out.println(String.valueOf(3.5));
        Object o = null;
        System.out.println(String.valueOf(o));
        try {
            System.out.println(o.toString());
        } catch (NullPointerException ex) {
            System.out.println("toString pada null meledak");
        }
        char[] huruf = { 'J', 'a', 'v', 'a' };
        System.out.println(String.valueOf(huruf));
    }
}
```

**Yang terjadi:** angka dan boolean jadi teks. `valueOf(null)` `"null"`. `o.toString()` NPE. Array `char` jadi `"Java"`, bukan identitas array.

**Biasanya digabungkan dengan:** `StringBuilder.append`, log.

**Jangan:** `String.valueOf` pada array objek jika kamu ingin isi — hasilnya mirip `[Ljava.lang.String;@...`. Pakai `Arrays.toString`.

---

### toCharArray

**Tipe:** method (`String.toCharArray`)

**Untuk apa:** salinan isi sebagai `char[]` yang bisa diubah (salinannya, bukan string asli).

**Contoh implementasi:**

```java
public class ToCharArray {
    public static void main(String[] args) {
        String kata = "buku";
        char[] huruf = kata.toCharArray();
        huruf[0] = 'B';
        System.out.println("array: " + String.valueOf(huruf));
        System.out.println("asli: " + kata);
    }
}
```

**Yang terjadi:** array menjadi `Buku`. `kata` tetap `buku`.

**Biasanya digabungkan dengan:** algoritma in-place pada latihan (palindrom, reverse).

**Jangan:** mengira mengubah array mengubah `String`.

---

### matches

**Tipe:** method (`String.matches`)

**Untuk apa:** menguji **seluruh** string terhadap regex.

**Contoh implementasi:**

```java
public class StringMatches {
    public static void main(String[] args) {
        String sku = "BK-1234";
        System.out.println(sku.matches("BK-\\d{4}"));
        System.out.println("42".matches("\\d+"));
        System.out.println("sku BK-1234 ada di kalimat".matches("BK-\\d{4}"));
        System.out.println("sku BK-1234 ada di kalimat".matches(".*BK-\\d{4}.*"));
    }
}
```

**Yang terjadi:** `BK-1234` cocok. `"42"` cocok digit. Kalimat panjang **tidak** cocok tanpa `.*` di kiri-kanan, karena `matches` menuntut seluruh teks.

**Biasanya digabungkan dengan:** validasi kode, `Pattern.compile` jika dipanggil berulang.

**Jangan:** memakai `matches` sebagai “contains regex” tanpa `.*`. Jangan compile regex berat di loop tanpa `Pattern`.

---

### repeat

**Tipe:** method (`String.repeat`, Java 11+)

**Untuk apa:** mengulang teks n kali.

**Contoh implementasi:**

```java
public class StringRepeat {
    public static void main(String[] args) {
        System.out.println("-".repeat(20));
        System.out.println("ha".repeat(3));
        System.out.println("x".repeat(0).isEmpty());
        try {
            System.out.println("x".repeat(-1));
        } catch (IllegalArgumentException ex) {
            System.out.println("n negatif ditolak");
        }
    }
}
```

**Yang terjadi:** garis 20 karakter, `hahaha`, repeat 0 string kosong. Negatif exception.

**Biasanya digabungkan dengan:** padding sederhana, garis pemisah struk.

**Jangan:** `repeat` jutaan kali pada string panjang tanpa sadar memori.

---

### text block

**Tipe:** literal `String` (Java 15+)

**Untuk apa:** menulis teks banyak baris tanpa `\n` manual: JSON, SQL, HTML latihan.

**Contoh implementasi:**

```java
public class TextBlock {
    public static void main(String[] args) {
        String json = """
                {
                  "nama": "Buku Java",
                  "harga": 45000
                }
                """;
        System.out.println(json);
        String satu = """
                Halo %s, total Rp%d
                """.formatted("Haikal", 90000);
        System.out.println(satu);
    }
}
```

**Yang terjadi:** indentasi bersama di kiri dipotong sesuai posisi penutup `"""`. Isi punya newline asli. `formatted` mengisi placeholder.

**Biasanya digabungkan dengan:** contoh payload, query, email template.

**Jangan:** text block di Java 8/11. Jangan mencampur tab/spasi indent sampai isi miring tak terduga — jaga konsisten.

---

### StringBuilder

**Tipe:** class (`java.lang.StringBuilder`)

**Untuk apa:** merangkai teks yang **berubah-ubah** tanpa membuat `String` baru setiap langkah.

**Contoh implementasi:**

```java
public class ContohStringBuilder {
    public static void main(String[] args) {
        String[] barang = { "Buku", "Pensil", "Penghapus" };
        StringBuilder sb = new StringBuilder();
        sb.append("Daftar: ");
        for (int i = 0; i < barang.length; i++) {
            if (i > 0) {
                sb.append(", ");
            }
            sb.append(barang[i]);
        }
        sb.append(" (").append(barang.length).append(" item)");
        System.out.println(sb.toString());
        sb.reverse();
        System.out.println(sb);
        sb.setLength(0);
        sb.append("bersih");
        System.out.println(sb);
    }
}
```

**Yang terjadi:** `append` mengubah buffer internal. `toString()` mengambil snapshot. `reverse` membalik buffer. `setLength(0)` mengosongkan tanpa objek builder baru.

**Biasanya digabungkan dengan:** loop, HTML sederhana, CSV.

**Jangan:** `StringBuilder` di banyak thread tanpa sinkronisasi. Untuk itu `StringBuffer` atau kunci. Jangan lupa `toString()` saat butuh `String`.

---

### StringBuffer

**Tipe:** class (`java.lang.StringBuffer`)

**Untuk apa:** sama seperti `StringBuilder` tetapi method-nya `synchronized`. Lebih lambat di thread tunggal.

**Contoh implementasi:**

```java
public class ContohStringBuffer {
    public static void main(String[] args) {
        StringBuffer sb = new StringBuffer("Toko");
        sb.append(' ').append("Belajar");
        sb.insert(0, "[");
        sb.append(']');
        System.out.println(sb);
        sb.delete(0, 1);
        sb.deleteCharAt(sb.length() - 1);
        System.out.println(sb);
    }
}
```

**Yang terjadi:** `[Toko Belajar]` lalu kurung dihapus, kembali `Toko Belajar`.

**Biasanya digabungkan dengan:** kode warisan. Kode baru thread-tunggal: `StringBuilder`.

**Jangan:** memilih `StringBuffer` “karena terdengar resmi”. Pilih berdasarkan kebutuhan sinkronisasi.

---

### intern

**Tipe:** method (`String.intern`)

**Untuk apa:** memasukkan/mengambil string dari pool global. Jarang dibutuhkan di tugas kuliah.

**Contoh implementasi:**

```java
public class StringIntern {
    public static void main(String[] args) {
        String a = new String("member").intern();
        String b = "member";
        System.out.println(a == b);
    }
}
```

**Yang terjadi:** `a` dan literal `b` merujuk objek pool yang sama.

**Biasanya digabungkan dengan:** optimisasi memori ekstrem, bukan kode harian.

**Jangan:** `intern` semua input pengguna — pool hidup sepanjang JVM, bisa memboroskan metaspace/heap.

---

### array 1 dimensi

**Tipe:** tipe array

**Untuk apa:** deretan bernomor, ukuran **tetap** sejak dibuat.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArraySatuD {
    public static void main(String[] args) {
        int[] harga = { 15000, 3000, 2000 };
        String[] nama = new String[3];
        nama[0] = "Buku";
        nama[1] = "Pensil";
        nama[2] = "Penghapus";
        harga[1] = 3500;
        System.out.println(nama[0] + " Rp" + harga[0]);
        System.out.println(Arrays.toString(harga));
        System.out.println(Arrays.toString(nama));
    }
}
```

**Yang terjadi:** `harga` langsung terisi. `nama` awalnya `{null,null,null}` lalu diisi. Mengubah `harga[1]` menimpa elemen, bukan mengubah panjang.

**Biasanya digabungkan dengan:** loop indeks, `Arrays.sort`.

**Jangan:** `harga[3]` pada array panjang 3. Jangan `new int[-1]`. Jangan mengira `nama = "Buku"` mengisi seluruh array.

---

### array 2 dimensi

**Tipe:** array of array

**Untuk apa:** tabel: baris × kolom, papan, matriks nilai.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArrayDuaD {
    public static void main(String[] args) {
        int[][] nilai = {
                { 80, 90, 70 },
                { 60, 75, 85 }
        };
        System.out.println("baris=" + nilai.length);
        System.out.println("kolom baris0=" + nilai[0].length);
        System.out.println(nilai[1][2]);
        int[][] tidakRata = new int[2][];
        tidakRata[0] = new int[] { 1, 2, 3 };
        tidakRata[1] = new int[] { 4, 5 };
        System.out.println(Arrays.deepToString(tidakRata));
    }
}
```

**Yang terjadi:** `nilai[1][2]` adalah 85 (mahasiswa ke-2, mapel ke-3). `length` luar = jumlah baris. Baris boleh beda panjang (jagged). `deepToString` mencetak isi bersarang.

**Biasanya digabungkan dengan:** loop bersarang `for i / for j`.

**Jangan:** `Arrays.toString(nilai)` jika ingin melihat angka dalam — itu hanya mencetak identitas baris. Pakai `deepToString`.

---

### length pada array

**Tipe:** field (`array.length`)

**Untuk apa:** membaca kapasitas yang dipesan, **bukan** method.

**Contoh implementasi:**

```java
public class ArrayLength {
    public static void main(String[] args) {
        int[] stok = new int[4];
        stok[0] = 10;
        stok[1] = 3;
        System.out.println("kapasitas=" + stok.length);
        int terisi = 0;
        for (int x : stok) {
            if (x != 0) {
                terisi++;
            }
        }
        System.out.println("terisi non-nol=" + terisi);
    }
}
```

**Yang terjadi:** `length` tetap 4 meskipun hanya dua elemen “berisi”. Nol adalah nilai sah, jadi “terisi” di sini hanya heuristik.

**Biasanya digabungkan dengan:** batas loop `i < arr.length`.

**Jangan:** `arr.length()` — error kompilasi. Jangan memakai `length` sebagai jumlah logis jika ada `null`/0 sebagai lowong.

---

### Arrays.toString

**Tipe:** method static (`java.util.Arrays`)

**Untuk apa:** mencetak isi array 1D agar manusia bisa baca.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArraysToStringDemo {
    public static void main(String[] args) {
        int[] harga = { 3, 1, 2 };
        System.out.println(harga);
        System.out.println(Arrays.toString(harga));
        String[] nama = { "Buku", null, "Teh" };
        System.out.println(Arrays.toString(nama));
    }
}
```

**Yang terjadi:** `println(harga)` mencetak tipe + hash, bukan isi. `toString` mencetak `[3, 1, 2]`. `null` tertulis `null`.

**Biasanya digabungkan dengan:** debug cepat, dan `deepToString` untuk 2D.

**Jangan:** mengandalkan format `toString` sebagai CSV resmi — itu untuk manusia, ada spasi setelah koma.

---

### Arrays.sort

**Tipe:** method static

**Untuk apa:** mengurut array di tempat. Primitif: urutan angka. Objek: `Comparable` atau `Comparator`.

**Contoh implementasi:**

```java
import java.util.Arrays;
import java.util.Comparator;

public class ArraysSortDemo {
    public static void main(String[] args) {
        int[] harga = { 15000, 3000, 20000, 500 };
        Arrays.sort(harga);
        System.out.println(Arrays.toString(harga));
        String[] nama = { "jeruk", "Apel", "mangga" };
        Arrays.sort(nama);
        System.out.println(Arrays.toString(nama));
        Arrays.sort(nama, String.CASE_INSENSITIVE_ORDER);
        System.out.println(Arrays.toString(nama));
        Integer[] objek = { 3, 1, 2 };
        Arrays.sort(objek, Comparator.reverseOrder());
        System.out.println(Arrays.toString(objek));
    }
}
```

**Yang terjadi:** harga naik: 500 … 20000. `String` default: `Apel` dulu (huruf besar). Case-insensitive: `Apel, jeruk, mangga`. `Integer[]` bisa `reverseOrder`; `int[]` tidak menerima `Comparator`.

**Biasanya digabungkan dengan:** `binarySearch` (harus sudah terurut), dan `Comparable` custom di bab 08.

**Jangan:** `binarySearch` sebelum `sort`. Jangan `sort` array objek yang elemennya `null` tanpa comparator tahan null.

---

### Arrays.fill

**Tipe:** method static

**Untuk apa:** mengisi semua (atau rentang) elemen dengan nilai yang sama.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArraysFillDemo {
    public static void main(String[] args) {
        int[] kursi = new int[5];
        Arrays.fill(kursi, -1);
        Arrays.fill(kursi, 1, 3, 99);
        System.out.println(Arrays.toString(kursi));
        String[] label = new String[3];
        Arrays.fill(label, "kosong");
        System.out.println(Arrays.toString(label));
    }
}
```

**Yang terjadi:** awalnya `[-1,-1,-1,-1,-1]`, lalu indeks 1..2 (end eksklusif) jadi 99: `[-1, 99, 99, -1, -1]`. Label tiga `"kosong"`.

**Biasanya digabungkan dengan:** papan permainan, sentinel.

**Jangan:** mengira `fill` menambah panjang.

---

### Arrays.copyOf

**Tipe:** method static

**Untuk apa:** menyalin ke array baru, bisa lebih panjang (isi default) atau lebih pendek (terpotong).

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArraysCopyOfDemo {
    public static void main(String[] args) {
        int[] asal = { 10, 20, 30 };
        int[] lebih = Arrays.copyOf(asal, 5);
        int[] potong = Arrays.copyOf(asal, 2);
        int[] rentang = Arrays.copyOfRange(asal, 1, 3);
        System.out.println(Arrays.toString(lebih));
        System.out.println(Arrays.toString(potong));
        System.out.println(Arrays.toString(rentang));
        asal[0] = 99;
        System.out.println("asal berubah, salinan: " + Arrays.toString(lebih));
    }
}
```

**Yang terjadi:** `lebih` = `[10,20,30,0,0]`. `potong` dua elemen. `copyOfRange(1,3)` = `[20,30]`. Mengubah `asal[0]` **tidak** mengubah salinan primitif.

**Biasanya digabungkan dengan:** “array penuh, saya butuh slot baru” — pola tumbuh manual.

**Jangan:** mengira ini deep copy untuk array objek bersarang. Elemen referensi masih objek yang sama.

---

### Arrays.equals

**Tipe:** method static

**Untuk apa:** membandingkan isi 1D. `==` pada array hanya identitas.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ArraysEqualsDemo {
    public static void main(String[] args) {
        int[] a = { 1, 2, 3 };
        int[] b = { 1, 2, 3 };
        int[] c = { 1, 2, 4 };
        System.out.println("== " + (a == b));
        System.out.println("equals " + Arrays.equals(a, b));
        System.out.println("equals c " + Arrays.equals(a, c));
        int[][] m1 = { { 1, 2 }, { 3 } };
        int[][] m2 = { { 1, 2 }, { 3 } };
        System.out.println("equals 2D dangkal: " + Arrays.equals(m1, m2));
        System.out.println("deepEquals: " + Arrays.deepEquals(m1, m2));
    }
}
```

**Yang terjadi:** `a == b` false (dua objek). `Arrays.equals` true untuk isi sama. 2D: `equals` membandingkan referensi baris, sering false; `deepEquals` true.

**Biasanya digabungkan dengan:** tes unit, `deepEquals` untuk matriks.

**Jangan:** `a.equals(b)` pada `int[]` — itu `equals` milik `Object` (identitas), bukan isi. Untuk primitif array, pakai `Arrays.equals`.

---

### Arrays.binarySearch

**Tipe:** method static

**Untuk apa:** mencari indeks pada array **yang sudah terurut**. Tidak ketemu: nilai negatif `(-(insertion point) - 1)`.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class BinarySearchDemo {
    public static void main(String[] args) {
        int[] harga = { 500, 3000, 15000, 20000 };
        System.out.println(Arrays.binarySearch(harga, 15000));
        System.out.println(Arrays.binarySearch(harga, 10000));
        int[] acak = { 9, 1, 5 };
        System.out.println("tanpa sort, hasil tidak dijamin: " + Arrays.binarySearch(acak, 5));
        Arrays.sort(acak);
        System.out.println("setelah sort: " + Arrays.binarySearch(acak, 5));
    }
}
```

**Yang terjadi:** 15000 ketemu di indeks 2. 10000 tidak ada, hasil negatif. Array acak bisa memberi jawaban salah; setelah sort, 5 ketemu.

**Biasanya digabungkan dengan:** `Arrays.sort` sebelumnya.

**Jangan:** binary search pada daftar tidak urut. Jangan mengira hasil negatif adalah `-1` selalu.

---

### System.arraycopy

**Tipe:** method static (`System`)

**Untuk apa:** menyalin blok array dengan cepat, termasuk geser elemen di array yang sama.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class SystemArraycopy {
    public static void main(String[] args) {
        int[] a = { 1, 2, 3, 4, 5 };
        int[] b = new int[5];
        System.arraycopy(a, 0, b, 0, 5);
        System.out.println(Arrays.toString(b));
        System.arraycopy(a, 1, a, 2, 3);
        System.out.println("geser: " + Arrays.toString(a));
    }
}
```

**Yang terjadi:** `b` salinan penuh. Geser: dari indeks 1 sepanjang 3 elemen ditaruh mulai indeks 2, menghasilkan sesuatu seperti `[1, 2, 2, 3, 4]` (tumpang tindih ditangani dengan benar).

**Biasanya digabungkan dengan:** implementasi list manual, buffer.

**Jangan:** salah mengisi `length` sampai `IndexOutOfBoundsException`. Untuk salinan sederhana, `Arrays.copyOf` lebih mudah dibaca.

---

### for-each pada array

**Tipe:** sintaks loop

**Untuk apa:** menelusuri elemen tanpa indeks, jika indeks tidak dibutuhkan.

**Contoh implementasi:**

```java
public class ForEachArray {
    public static void main(String[] args) {
        String[] menu = { "Nasi goreng", "Es teh", "Pisang goreng" };
        int i = 1;
        for (String item : menu) {
            System.out.println(i + ". " + item);
            i++;
        }
        int[] harga = { 15000, 5000, 8000 };
        int total = 0;
        for (int h : harga) {
            total += h;
        }
        System.out.println("total=" + total);
    }
}
```

**Yang terjadi:** setiap elemen dikunjungi sekali dari kiri. `item` adalah salinan referensi/nilai; `item = "x"` **tidak** mengubah array. Mengubah field objek yang dirujuk tetap memengaruhi objek.

**Biasanya digabungkan dengan:** pencetakan, akumulasi.

**Jangan:** menghapus/geser elemen saat for-each (untuk array kamu memang tidak bisa mengubah panjang). Untuk ganti elemen, pakai loop indeks `arr[i] = ...`.

---

### varargs

**Tipe:** parameter `T...`

**Untuk apa:** menerima nol atau lebih argumen, diterima sebagai array.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class ContohVarargs {
    static int total(int... harga) {
        int s = 0;
        for (int h : harga) {
            s += h;
        }
        return s;
    }

    public static void main(String[] args) {
        System.out.println(total());
        System.out.println(total(15000));
        System.out.println(total(15000, 3000, 2000));
        int[] arr = { 1, 2, 3 };
        System.out.println(total(arr));
        System.out.println(Arrays.toString(arr));
    }
}
```

**Yang terjadi:** tanpa argumen, array kosong, total 0. Tiga harga dijumlah. Mengirim array yang sudah ada juga sah. Method melihat `harga.length`.

**Biasanya digabungkan dengan:** `main(String... args)` (setara `String[]`), dan `List.of`.

**Jangan:** menaruh varargs **bukan** di parameter terakhir. Jangan overload `f(int...)` dan `f(int[])` — tanda tangan sama.

---

### Arrays.asList

**Tipe:** method static

**Untuk apa:** pandangan `List` pada array objek. Panjang tetap.

**Contoh implementasi:**

```java
import java.util.Arrays;
import java.util.List;

public class ArraysAsListDemo {
    public static void main(String[] args) {
        String[] nama = { "Buku", "Pensil" };
        List<String> list = Arrays.asList(nama);
        list.set(1, "Penghapus");
        System.out.println(list);
        System.out.println(Arrays.toString(nama));
        try {
            list.add("Spidol");
        } catch (UnsupportedOperationException ex) {
            System.out.println("add ditolak: " + ex.getClass().getSimpleName());
        }
        // Arrays.asList(1, 2, 3) -> List<Integer>
        // Arrays.asList(new int[]{1,2,3}) -> List<int[]> SATU elemen!
    }
}
```

**Yang terjadi:** `set` mengubah array asli juga. `add` melempar. `asList` pada `int[]` **bukan** mengekspansi angka — list berisi satu elemen yaitu array itu.

**Biasanya digabungkan dengan:** `new ArrayList<>(Arrays.asList(...))` jika butuh `add`.

**Jangan:** `asList` pada array primitif untuk mendapat `List<Integer>`. Pakai loop atau `IntStream`.

---

### null versus array kosong

**Tipe:** nilai referensi vs array length 0

**Untuk apa:** membedakan “tidak ada wadah” dan “wadah tanpa elemen”.

**Contoh implementasi:**

```java
import java.util.Arrays;

public class NullVsKosong {
    public static void main(String[] args) {
        String[] kosong = new String[0];
        String[] nada = null;
        System.out.println("kosong length=" + kosong.length);
        System.out.println(Arrays.toString(kosong));
        try {
            System.out.println(nada.length);
        } catch (NullPointerException ex) {
            System.out.println("null.length meledak");
        }
        System.out.println("kosong == null? " + (kosong == null));
    }
}
```

**Yang terjadi:** array kosong aman di-loop (nol iterasi). `null` meledak saat `.length`. Keduanya berbeda artinya.

**Biasanya digabungkan dengan:** method yang mengembalikan `T[]` — lebih ramah mengembalikan kosong daripada `null`.

**Jangan:** mengembalikan `null` “supaya hemat” jika pemanggil harus for-each. Jangan menukar istilah “kosong” dan “null” di laporan bug.

---

Lanjut ke [03 — kontrol dan method](03-kontrol-method.md).
