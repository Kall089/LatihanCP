# 03 — Kontrol alur dan method

[← 02 String & array](02-string-array.md) · [Lanjut 04 OOP →](04-oop-class-inheritance.md)

Program memilih cabang (`if`, `switch`), mengulang (`for`, `while`), dan membungkus langkah ke **method**. Method membuat `main` tetap pendek.

## Daftar isi

- [if](#if)
- [if-else](#if-else)
- [else if](#else-if)
- [operator ternary](#operator-ternary)
- [&& || !](#--dan--)
- [switch klasik](#switch-klasik)
- [switch expression](#switch-expression)
- [for](#for)
- [while](#while)
- [do-while](#do-while)
- [for-each](#for-each)
- [break](#break)
- [continue](#continue)
- [label break/continue](#label-breakcontinue)
- [return](#return)
- [method void](#method-void)
- [method dengan return](#method-dengan-return)
- [parameter](#parameter)
- [pass by value](#pass-by-value)
- [overloading](#overloading)
- [varargs pada method](#varargs-pada-method)
- [static method](#static-method)
- [instance method](#instance-method)
- [rekursi](#rekursi)
- [scope dan blok](#scope-dan-blok)
- [Math](#math)
- [printf](#printf)
- [Scanner ringkas](#scanner-ringkas)

---

### if

**Tipe:** pernyataan kontrol

**Untuk apa:** menjalankan blok hanya jika kondisi `boolean` true.

**Contoh implementasi:**

```java
public class ContohIf {
    public static void main(String[] args) {
        int stok = 0;
        if (stok == 0) {
            System.out.println("Stok habis, jangan dijual.");
        }
        if (stok < 0) {
            System.out.println("Data rusak");
        }
        System.out.println("Selesai cek.");
    }
}
```

**Yang terjadi:** `stok == 0` true, pesan habis tercetak. `stok < 0` false, bloknya dilewati. “Selesai cek.” selalu tercetak.

**Biasanya digabungkan dengan:** `else`, method yang mengembalikan `boolean`, dan penjagaan di awal method (`if (x == null) return;`).

**Jangan:** `if (stok = 0)` — itu penugasan, dan untuk `int` tidak menjadi kondisi. Jangan lupa kurung kurawal jika isi lebih dari satu baris; lebih aman selalu memakai `{ }`.

---

### if-else

**Tipe:** pernyataan kontrol

**Untuk apa:** memilih **salah satu** dari dua jalan.

**Contoh implementasi:**

```java
public class IfElse {
    public static void main(String[] args) {
        int umur = 16;
        if (umur >= 17) {
            System.out.println("Boleh buat KTP (contoh aturan).");
        } else {
            System.out.println("Belum cukup umur.");
        }
    }
}
```

**Yang terjadi:** 16 < 17, cabang `else` jalan. Hanya satu blok yang dijalankan.

**Biasanya digabungkan dengan:** return awal di method agar tidak perlu `else` dalam.

**Jangan:** menulis kondisi yang tumpang tindih di `if` dan `else` seolah keduanya bisa true.

---

### else if

**Tipe:** pernyataan kontrol

**Untuk apa:** menata beberapa rentang yang saling menyingkir.

**Contoh implementasi:**

```java
public class ElseIfNilai {
    public static void main(String[] args) {
        int nilai = 82;
        String huruf;
        if (nilai >= 85) {
            huruf = "A";
        } else if (nilai >= 70) {
            huruf = "B";
        } else if (nilai >= 55) {
            huruf = "C";
        } else {
            huruf = "D/E";
        }
        System.out.println("Nilai " + nilai + " = " + huruf);
    }
}
```

**Yang terjadi:** 82 tidak ≥ 85, tetapi ≥ 70, jadi `"B"`. Urutan penting: cek yang lebih ketat dulu.

**Biasanya digabungkan dengan:** `switch` jika yang dibanding **nilai diskrit**, bukan rentang.

**Jangan:** menulis `if (nilai >= 70)` sebelum `>= 85` — nilai 90 akan tertangkap sebagai B.

---

### operator ternary

**Tipe:** operator `? :`

**Untuk apa:** memilih **satu ekspresi** dari dua, biasanya untuk nilai pendek.

**Contoh implementasi:**

```java
public class Ternary {
    public static void main(String[] args) {
        int stok = 4;
        String status = stok > 0 ? "tersedia" : "habis";
        int harga = 15000;
        boolean member = true;
        int bayar = member ? harga - 2000 : harga;
        System.out.println(status);
        System.out.println("Bayar: " + bayar);
        int a = 5, b = 9;
        int max = a > b ? a : b;
        System.out.println("max=" + max);
    }
}
```

**Yang terjadi:** `status` `"tersedia"`. Member mendapat 13000. `max` 9. Ternary **menghasilkan nilai**, bukan menggantikan semua `if`.

**Biasanya digabungkan dengan:** `return` pendek, dan argumen `println`.

**Jangan:** menyarangkan tiga-empat ternary. Jangan memakai ternary untuk menjalankan dua prosedur samping; pakai `if`.

---

### && || !

**Tipe:** operator logika

**Untuk apa:** menggabungkan kondisi. `&&` dan `||` **short-circuit**: kanan tidak dievaluasi jika kiri sudah menentukan hasil.

**Contoh implementasi:**

```java
public class LogikaPendek {
    static boolean mahal(int harga) {
        System.out.println("cek mahal dipanggil");
        return harga > 10000;
    }

    public static void main(String[] args) {
        String nama = null;
        if (nama != null && nama.length() > 3) {
            System.out.println(nama);
        } else {
            System.out.println("Nama tidak dipakai");
        }
        boolean member = false;
        if (member || mahal(15000)) {
            System.out.println("salah satu true");
        }
        if (false && mahal(1)) {
            System.out.println("tidak tercetak");
        } else {
            System.out.println("mahal tidak dipanggil karena && kiri false");
        }
        System.out.println("kebalikan member: " + !member);
    }
}
```

**Yang terjadi:** `nama != null` false, `nama.length()` **tidak** dipanggil — selamat dari NPE. `member` false, jadi `mahal` dipanggil (true). `false && mahal(1)` tidak memanggil `mahal`. `!false` true.

**Biasanya digabungkan dengan:** penjagaan null, validasi berlapis.

**Jangan:** memakai `&` / `|` boolean jika kamu butuh short-circuit (bentuk itu mengevaluasi kedua sisi). Jangan menulis `if (!member == false)` — sulit dibaca.

---

### switch klasik

**Tipe:** pernyataan kontrol

**Untuk apa:** memilih cabang berdasarkan nilai diskrit (`int`, `String`, `enum`, beberapa tipe lain).

**Contoh implementasi:**

```java
public class SwitchKlasik {
    public static void main(String[] args) {
        String hari = "sabtu";
        String jenis;
        switch (hari) {
            case "sabtu":
            case "minggu":
                jenis = "libur kuliah (contoh)";
                break;
            case "jumat":
                jenis = "weekday + Jumat";
                break;
            default:
                jenis = "weekday";
        }
        System.out.println(hari + " -> " + jenis);
        int kode = 2;
        switch (kode) {
            case 1:
                System.out.println("baru");
                break;
            case 2:
                System.out.println("diproses");
                break;
            default:
                System.out.println("kode tidak dikenal");
        }
    }
}
```

**Yang terjadi:** `"sabtu"` jatuh ke case libur karena **fall-through** tanpa `break` di `"sabtu"`. `kode` 2 mencetak `diproses` lalu `break` mencegah default.

**Biasanya digabungkan dengan:** `enum` (bab 08) agar typo ketahuan compiler.

**Jangan:** lupa `break` kecuali fall-through memang disengaja dan dikomentari. Jangan `switch` pada `String` null — NPE.

---

### switch expression

**Tipe:** ekspresi (Java 14+)

**Untuk apa:** `switch` yang **menghasilkan nilai**, memakai `->` atau `yield`, wajib lengkap (atau `default`).

**Contoh implementasi:**

```java
public class SwitchEkspresi {
    public static void main(String[] args) {
        int nilai = 82;
        String huruf = switch (nilai / 10) {
            case 10, 9, 8 -> "A/B atas";
            case 7 -> "B";
            case 6 -> "C";
            default -> "perlu perbaikan";
        };
        System.out.println(huruf);

        String paket = "premium";
        int diskon = switch (paket) {
            case "basic" -> 0;
            case "premium" -> {
                System.out.println("hitung diskon premium");
                yield 15;
            }
            default -> 5;
        };
        System.out.println("diskon%=" + diskon);
    }
}
```

**Yang terjadi:** `82/10` = 8, label `10,9,8` memilih teks A/B. `->` tidak fall-through. Blok `premium` menjalankan `println` lalu `yield 15`.

**Biasanya digabungkan dengan:** `enum`, dan `return switch (...)`.

**Jangan:** mencampur `:` klasik dan `->` seenaknya. Jangan lupa `yield` di dalam `{ }` expression.

---

### for

**Tipe:** loop

**Untuk apa:** mengulang dengan penghitung: inisialisasi, kondisi, kenaikan.

**Contoh implementasi:**

```java
public class ContohFor {
    public static void main(String[] args) {
        int[] harga = { 15000, 3000, 2000 };
        int total = 0;
        for (int i = 0; i < harga.length; i++) {
            System.out.println("indeks " + i + " = " + harga[i]);
            total += harga[i];
        }
        System.out.println("total=" + total);
        for (int i = harga.length - 1; i >= 0; i--) {
            System.out.print(harga[i] + " ");
        }
        System.out.println();
    }
}
```

**Yang terjadi:** `i` 0,1,2. Total 20000. Loop kedua mencetak terbalik. Setelah loop, `i` tidak hidup di luar (scope header).

**Biasanya digabungkan dengan:** array, `charAt`, indeks saling terkait.

**Jangan:** `for (int i = 0; i <= arr.length; i++)` — `<=` menyentuh indeks ilegal. Jangan mengubah `i` di dua tempat tanpa komentar.

---

### while

**Tipe:** loop

**Untuk apa:** mengulang selama kondisi true, saat jumlah putaran tidak diketahui di awal.

**Contoh implementasi:**

```java
public class ContohWhile {
    public static void main(String[] args) {
        int stok = 5;
        while (stok > 0) {
            System.out.println("jual 1, sisa sebelum=" + stok);
            stok--;
        }
        System.out.println("habis, stok=" + stok);

        String teks = "banana";
        int hitung = 0;
        int pos = teks.indexOf('a');
        while (pos >= 0) {
            hitung++;
            pos = teks.indexOf('a', pos + 1);
        }
        System.out.println("huruf a: " + hitung);
    }
}
```

**Yang terjadi:** stok 5→4→…→0, lima penjualan. Huruf `a` di `"banana"` dihitung 3 dengan `indexOf` bergeser.

**Biasanya digabungkan dengan:** baca file per baris, input sampai “stop”, pencarian berulang.

**Jangan:** lupa mengubah variabel kondisi — loop abadi. Jangan `while (true)` tanpa `break` yang pasti tercapai.

---

### do-while

**Tipe:** loop

**Untuk apa:** menjalankan badan **minimal sekali**, lalu cek kondisi.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class ContohDoWhile {
    public static void main(String[] args) {
        int percobaan = 0;
        int tebakan;
        int rahasia = 7;
        do {
            tebakan = 4 + percobaan; // simulasi input: 4,5,6,7
            percobaan++;
            System.out.println("coba " + tebakan);
        } while (tebakan != rahasia && percobaan < 10);
        System.out.println("selesai dalam " + percobaan + " percobaan");

        Scanner demo = new Scanner("ya\n");
        String jawab;
        do {
            jawab = demo.nextLine().strip();
        } while (!jawab.equals("ya") && !jawab.equals("tidak"));
        System.out.println("jawab=" + jawab);
        demo.close();
    }
}
```

**Yang terjadi:** badan jalan dulu, baru syarat. Simulasi tebakan naik sampai 7. Scanner membaca `"ya"` sekali.

**Biasanya digabungkan dengan:** menu yang harus tampil dulu, validasi ulang input.

**Jangan:** memakai `do-while` jika ada kemungkinan **nol** iterasi yang sah — pakai `while`.

---

### for-each

**Tipe:** enhanced for

**Untuk apa:** menelusuri array atau `Iterable` (List, Set) tanpa indeks.

**Contoh implementasi:**

```java
import java.util.List;

public class ForEachDemo {
    public static void main(String[] args) {
        List<String> keranjang = List.of("Buku", "Pensil", "Teh");
        for (String item : keranjang) {
            System.out.println("- " + item);
        }
        int jumlahHuruf = 0;
        for (String item : keranjang) {
            jumlahHuruf += item.length();
        }
        System.out.println("total huruf=" + jumlahHuruf);
    }
}
```

**Yang terjadi:** tiga baris daftar. Panjang nama dijumlah (4+6+3=13). Variabel `item` hanya hidup di dalam loop.

**Biasanya digabungkan dengan:** `List`, array, akumulasi.

**Jangan:** menghapus elemen list di dalam for-each — `ConcurrentModificationException`. Pakai `Iterator` atau `removeIf` (bab 05).

---

### break

**Tipe:** pernyataan

**Untuk apa:** keluar dari loop atau `switch` terdekat segera.

**Contoh implementasi:**

```java
public class ContohBreak {
    public static void main(String[] args) {
        int[] id = { 4, 8, 15, 16, 23, 42 };
        int cari = 16;
        int ketemu = -1;
        for (int i = 0; i < id.length; i++) {
            if (id[i] == cari) {
                ketemu = i;
                break;
            }
        }
        System.out.println("indeks=" + ketemu);
    }
}
```

**Yang terjadi:** saat `16` ketemu di indeks 3, loop berhenti. `23` dan `42` tidak diperiksa.

**Biasanya digabungkan dengan:** pencarian linier, `switch` klasik.

**Jangan:** `break` untuk “keluar method” — itu tugas `return`. `break` hanya loop/switch.

---

### continue

**Tipe:** pernyataan

**Untuk apa:** lompat ke iterasi berikutnya, melewati sisa badan loop.

**Contoh implementasi:**

```java
public class ContohContinue {
    public static void main(String[] args) {
        int[] nilai = { 80, -1, 90, 70, -5 };
        int jumlah = 0;
        int n = 0;
        for (int v : nilai) {
            if (v < 0) {
                continue;
            }
            jumlah += v;
            n++;
        }
        System.out.println("rata valid=" + (jumlah / (double) n));
    }
}
```

**Yang terjadi:** `-1` dan `-5` dilewati. Rata-rata (80+90+70)/3 = 80.0.

**Biasanya digabungkan dengan:** filter “data rusak diabaikan”.

**Jangan:** `continue` yang membuat kenaikan `for` terlewat — pada `for` biasa, bagian kenaikan tetap jalan. Pada `while`, kamu harus menaikkan sendiri **sebelum** `continue` jika tidak ingin macet.

---

### label break/continue

**Tipe:** pernyataan berlabel

**Untuk apa:** keluar dari loop **luar**, bukan hanya dalam.

**Contoh implementasi:**

```java
public class LabelBreak {
    public static void main(String[] args) {
        int[][] meja = {
                { 1, 2, 3 },
                { 4, 5, 6 },
                { 7, 8, 9 }
        };
        int cari = 6;
        int baris = -1, kolom = -1;
        cari:
        for (int i = 0; i < meja.length; i++) {
            for (int j = 0; j < meja[i].length; j++) {
                if (meja[i][j] == cari) {
                    baris = i;
                    kolom = j;
                    break cari;
                }
            }
        }
        System.out.println("ketemu di " + baris + "," + kolom);
    }
}
```

**Yang terjadi:** `6` di `[1][2]`. `break cari` meninggalkan **kedua** loop. Tanpa label, `break` hanya keluar loop `j`, lalu `i` lanjut.

**Biasanya digabungkan dengan:** pencarian di matriks.

**Jangan:** memakai label sebagai pengganti method. Jika bersarang dalam, pecah ke method `cari()` lalu `return`.

---

### return

**Tipe:** pernyataan

**Untuk apa:** keluar dari method, dan (jika bukan `void`) menyerahkan nilai.

**Contoh implementasi:**

```java
public class ContohReturn {
    static int kali(int a, int b) {
        return a * b;
    }

    static void cekStok(int stok) {
        if (stok < 0) {
            System.out.println("stok tidak sah");
            return;
        }
        System.out.println("stok=" + stok);
    }

    public static void main(String[] args) {
        System.out.println(kali(3, 4));
        cekStok(-2);
        cekStok(8);
    }
}
```

**Yang terjadi:** `kali` mengembalikan 12 ke `println`. `cekStok(-2)` mencetak tidak sah lalu `return` (method selesai). `cekStok(8)` mencetak stok.

**Biasanya digabungkan dengan:** penjagaan awal, method murni tanpa side-effect.

**Jangan:** menulis kode setelah `return` di jalur yang sama — unreachable. Jangan `return` tanpa nilai di method `int`.

---

### method void

**Tipe:** method

**Untuk apa:** melakukan kerja (cetak, ubah objek) tanpa mengembalikan nilai.

**Contoh implementasi:**

```java
public class MethodVoid {
    static void cetakStruk(String barang, int harga) {
        System.out.println("==== STRUK ====");
        System.out.println(barang + " Rp" + harga);
        System.out.println("===============");
    }

    public static void main(String[] args) {
        cetakStruk("Buku", 45000);
        cetakStruk("Pensil", 3000);
    }
}
```

**Yang terjadi:** `main` memanggil `cetakStruk` dua kali. Tiap panggilan menjalankan tiga `println` lalu kembali. Tidak ada nilai yang bisa ditampung: `int x = cetakStruk(...)` error.

**Biasanya digabungkan dengan:** side-effect: IO, mengubah field objek.

**Jangan:** memakai `void` jika pemanggil butuh hasil untuk dihitung lagi. Jangan menamai method `hitungTotal` lalu hanya `println` — nama berbohong.

---

### method dengan return

**Tipe:** method

**Untuk apa:** menghitung dan menyerahkan hasil agar bisa dipakai ulang.

**Contoh implementasi:**

```java
public class MethodReturn {
    static int total(int harga, int jumlah) {
        return harga * jumlah;
    }

    static double rata(int a, int b, int c) {
        return (a + b + c) / 3.0;
    }

    public static void main(String[] args) {
        int bayar = total(15000, 3);
        System.out.println("Bayar: " + bayar);
        System.out.println("Plus ongkir: " + (bayar + 10000));
        System.out.println("Rata: " + rata(80, 90, 70));
    }
}
```

**Yang terjadi:** `total` 45000 ditampung, lalu ditambah ongkir. `rata` 80.0. Method bisa diuji tanpa mencetak.

**Biasanya digabungkan dengan:** `if` pada hasil, dan unit test di mata kuliah lanjut.

**Jangan:** `return` kadang `int` kadang tidak di method yang sama. Semua jalur harus return, atau melempar exception.

---

### parameter

**Tipe:** variabel lokal method

**Untuk apa:** menerima input dari pemanggil. Urutan dan tipe harus cocok.

**Contoh implementasi:**

```java
public class ParameterMethod {
    static String label(String nama, int harga, boolean diskon) {
        String teks = nama + " Rp" + harga;
        if (diskon) {
            teks = teks + " (diskon)";
        }
        return teks;
    }

    public static void main(String[] args) {
        System.out.println(label("Buku", 45000, true));
        System.out.println(label("Teh", 5000, false));
        // label(45000, "Buku", true); // error: urutan tipe
    }
}
```

**Yang terjadi:** parameter terisi sesuai urutan panggilan. Nama parameter di pemanggil tidak wajib sama dengan di definisi.

**Biasanya digabungkan dengan:** overloading jika jumlah/tipe beda, dan class parameter-object jika argumen > 4.

**Jangan:** terlalu banyak parameter primitif (10+) — pecah jadi objek. Jangan mengubah parameter objek lalu heran pemanggil ikut berubah (lihat pass by value + mutasi).

---

### pass by value

**Tipe:** aturan pemanggilan

**Untuk apa:** memahami bahwa Java mengirim **salinan nilai**. Untuk objek, yang disalin adalah **referensi**, bukan objek utuh.

**Contoh implementasi:**

```java
public class PassByValue {
    static void tambah(int x) {
        x = x + 10;
        System.out.println("di method x=" + x);
    }

    static void gantiNama(String[] rak) {
        rak[0] = "Tertukar";
    }

    static void gantiReferensi(String[] rak) {
        rak = new String[] { "Baru" };
    }

    public static void main(String[] args) {
        int harga = 5;
        tambah(harga);
        System.out.println("di main harga=" + harga);
        String[] rak = { "Asli" };
        gantiNama(rak);
        System.out.println("setelah gantiNama: " + rak[0]);
        gantiReferensi(rak);
        System.out.println("setelah gantiReferensi: " + rak[0]);
    }
}
```

**Yang terjadi:** `harga` di `main` tetap 5. `gantiNama` mengubah **isi** array yang dirujuk bersama: `"Tertukar"`. `gantiReferensi` hanya menimpa salinan referensi lokal; `main` masih melihat array lama (tetap `"Tertukar"`).

**Biasanya digabungkan dengan:** method yang mengembalikan nilai baru, atau mengubah objek secara sadar.

**Jangan:** mengira Java “pass by reference” seperti C++ `&`. Jangan mengharapkan `void ubah(int x)` mengubah variabel pemanggil.

---

### overloading

**Tipe:** beberapa method nama sama

**Untuk apa:** nama yang sama, **parameter berbeda** (jumlah atau tipe). Bukan hanya beda `return`.

**Contoh implementasi:**

```java
public class OverloadKasir {
    static int total(int harga, int jumlah) {
        return harga * jumlah;
    }

    static int total(int harga, int jumlah, int ongkir) {
        return harga * jumlah + ongkir;
    }

    static double total(double harga, int jumlah) {
        return harga * jumlah;
    }

    public static void main(String[] args) {
        System.out.println(total(15000, 2));
        System.out.println(total(15000, 2, 5000));
        System.out.println(total(15000.5, 2));
    }
}
```

**Yang terjadi:** compiler memilih method dari argumen: dua `int` → 30000; tiga `int` → 35000; `double`+`int` → 30001.0.

**Biasanya digabungkan dengan:** constructor overloading (bab 04), dan API yang ramah.

**Jangan:** overload yang hanya beda return type. Jangan overload `f(int)` dan `f(Integer)` lalu memanggil `f(10)` — membingungkan (autoboxing). Hindari jika mungkin.

---

### varargs pada method

**Tipe:** parameter `T...`

**Untuk apa:** daftar argumen fleksibel di ujung daftar parameter.

**Contoh implementasi:**

```java
public class MethodVarargs {
    static int max(int pertama, int... sisanya) {
        int m = pertama;
        for (int x : sisanya) {
            if (x > m) {
                m = x;
            }
        }
        return m;
    }

    public static void main(String[] args) {
        System.out.println(max(3));
        System.out.println(max(3, 9, 4, 7));
    }
}
```

**Yang terjadi:** `max(3)` — `sisanya` kosong, hasil 3. `max(3,9,4,7)` membandingkan semua, hasil 9. Minimal satu argumen dijamin oleh parameter `pertama`.

**Biasanya digabungkan dengan:** `String.format`, `List.of`.

**Jangan:** `null` sebagai satu-satunya argumen varargs objek — bisa NPE saat iterate. Jangan dua varargs.

---

### static method

**Tipe:** method class

**Untuk apa:** perilaku yang **tidak** butuh data instance: utilitas, `main`, factory sederhana.

**Contoh implementasi:**

```java
public class StaticMethod {
    static int pajak(int harga) {
        return harga * 11 / 100;
    }

    public static void main(String[] args) {
        System.out.println(StaticMethod.pajak(100000));
        System.out.println(pajak(50000));
    }
}
```

**Yang terjadi:** `pajak` dipanggil lewat nama class atau langsung dari `main` (class yang sama). Tidak ada `this`. Tidak bisa menyentuh field instance tanpa objek.

**Biasanya digabungkan dengan:** `Math.max`, `Integer.parseInt`, class `Util`.

**Jangan:** membuat hampir semua method `static` lalu meniru program prosedural 1000 baris. Jangan memanggil instance method dari `static` tanpa `new`.

---

### instance method

**Tipe:** method objek

**Untuk apa:** perilaku yang memakai (atau mengubah) data objek: `this`.

**Contoh implementasi:**

```java
public class InstanceMethod {
    String nama;
    int harga;

    int denganPajak() {
        return harga + harga * 11 / 100;
    }

    void etiket() {
        System.out.println(nama + " Rp" + denganPajak());
    }

    public static void main(String[] args) {
        InstanceMethod a = new InstanceMethod();
        a.nama = "Buku";
        a.harga = 100000;
        a.etiket();
        InstanceMethod b = new InstanceMethod();
        b.nama = "Pensil";
        b.harga = 3000;
        b.etiket();
    }
}
```

**Yang terjadi:** dua objek, dua harga. `denganPajak` membaca `harga` milik objek yang dipanggil. `a.etiket()` tidak memakai data `b`.

**Biasanya digabungkan dengan:** field, constructor, encapsulation (bab 04).

**Jangan:** `InstanceMethod.etiket();` tanpa objek. Jangan menyimpan state di `static` jika tiap objek harus punya data sendiri.

---

### rekursi

**Tipe:** method yang memanggil dirinya

**Untuk apa:** masalah yang terpecah ke versi lebih kecil: faktorial, telusur pohon, DFS.

**Contoh implementasi:**

```java
public class Rekursi {
    static int faktorial(int n) {
        if (n < 0) {
            throw new IllegalArgumentException("n negatif");
        }
        if (n == 0 || n == 1) {
            return 1;
        }
        return n * faktorial(n - 1);
    }

    static int jumlahArray(int[] a, int i) {
        if (i == a.length) {
            return 0;
        }
        return a[i] + jumlahArray(a, i + 1);
    }

    public static void main(String[] args) {
        System.out.println(faktorial(5));
        System.out.println(jumlahArray(new int[] { 1, 2, 3, 4 }, 0));
    }
}
```

**Yang terjadi:** `faktorial(5)` = 5*4*3*2*1 = 120. Basis `n==0/1` menghentikan rantai. `jumlahArray` maju indeks sampai `length`, lalu menjumlah saat kembali. Tanpa basis, `StackOverflowError`.

**Biasanya digabungkan dengan:** struktur pohon (bab OOP), dan versi iteratif jika dalam sekali.

**Jangan:** rekursi tanpa basis. Jangan rekursi pada `n` besar untuk faktorial — overflow `int` dan stack. Lebih aman loop + `long`.

---

### scope dan blok

**Tipe:** aturan nama

**Untuk apa:** variabel hidup di dalam `{ }` terdekat (dan header `for`).

**Contoh implementasi:**

```java
public class ScopeBlok {
    public static void main(String[] args) {
        int luar = 1;
        if (luar > 0) {
            int dalam = 2;
            System.out.println(luar + dalam);
        }
        // System.out.println(dalam); // error: out of scope
        for (int i = 0; i < 2; i++) {
            System.out.print(i);
        }
        System.out.println();
        // System.out.println(i); // error
        int i = 99;
        System.out.println("i baru=" + i);
    }
}
```

**Yang terjadi:** `dalam` dan `i` loop tidak terlihat di luar. Kamu boleh membuat `int i` baru setelah loop selesai.

**Biasanya digabungkan dengan:** variabel loop yang tidak bocor, dan field class yang hidup lebih lama.

**Jangan:** mendeklarasikan dua variabel sama di scope yang bertumpuk secara ilegal (`int x; { int x; }` di method — error di Java). Jangan field dan local sama nama tanpa sadar (local menyembunyikan field; pakai `this`).

---

### Math

**Tipe:** class (`java.lang.Math`)

**Untuk apa:** fungsi numerik static: `max`, `min`, `abs`, `round`, `sqrt`, `pow`, `random`.

**Contoh implementasi:**

```java
public class ContohMath {
    public static void main(String[] args) {
        System.out.println(Math.max(3, 9));
        System.out.println(Math.min(3, 9));
        System.out.println(Math.abs(-12));
        System.out.println(Math.round(4.5));
        System.out.println(Math.floor(4.9));
        System.out.println(Math.ceil(4.1));
        System.out.println(Math.sqrt(9));
        System.out.println(Math.pow(2, 10));
        int dadu = (int) (Math.random() * 6) + 1;
        System.out.println("dadu=" + dadu);
        System.out.println(Math.PI);
    }
}
```

**Yang terjadi:** max 9, min 3, abs 12. `round(4.5)` ke `long` 5 (half up jauh dari nol untuk .5 positif). `floor` 4.0, `ceil` 5.0. `sqrt` 3.0. `pow` 1024.0. `random()` ∈ [0.0, 1.0), dikali 6 lalu +1 → 1..6.

**Biasanya digabungkan dengan:** hitungan geometri, pembulatan tampilan, `Random`/`ThreadLocalRandom` jika butuh seed.

**Jangan:** `Math.random()` untuk keamanan (token). Jangan `pow` untuk kuadrat sederhana jika `x*x` cukup. Jangan `abs(Integer.MIN_VALUE)` — tetap negatif (overflow).

---

### printf

**Tipe:** method (`PrintStream.printf`)

**Untuk apa:** mencetak terformat tanpa merangkai `String.format` dulu.

**Contoh implementasi:**

```java
public class ContohPrintf {
    public static void main(String[] args) {
        String nama = "Buku";
        int harga = 45000;
        double berat = 0.35;
        System.out.printf("%-10s | Rp%,8d | %.2f kg%n", nama, harga, berat);
        System.out.printf("hex %d = %x%n", 255, 255);
        System.out.printf("persen 11%% %n");
    }
}
```

**Yang terjadi:** kolom nama rata kiri 10, harga dengan pemisah ribuan, berat 2 desimal, newline `%n`. `255` heks `ff`. `%%` mencetak `%`.

**Biasanya digabungkan dengan:** tabel di terminal, struk.

**Jangan:** lupa `%n` lalu baris menempel. Jangan `%d` untuk `double`. `printf` mengembalikan `PrintStream`, bukan string — tampung dengan `String.format` jika butuh nilai.

---

### Scanner ringkas

**Tipe:** class (`java.util.Scanner`)

**Untuk apa:** membaca token dari teks atau `System.in`: `next`, `nextLine`, `nextInt`, `nextDouble`.

**Contoh implementasi:**

```java
import java.util.Scanner;

public class ScannerRingkas {
    public static void main(String[] args) {
        String data = "Buku 2\n45000\n";
        Scanner in = new Scanner(data);
        String nama = in.next();
        int jumlah = in.nextInt();
        in.nextLine(); // habiskan sisa baris
        int harga = Integer.parseInt(in.nextLine().strip());
        System.out.println(nama + " x" + jumlah + " Rp" + harga);
        in.close();
    }
}
```

**Yang terjadi:** `next()` membaca `"Buku"`. `nextInt()` 2. `nextLine()` setelah `nextInt` sering string kosong (sisa newline) — kita buang. Baris berikutnya `"45000"` di-parse. Pola ini mencegah bug “input terlewat”.

**Biasanya digabungkan dengan:** loop `hasNext`, dan resep bab 09.

**Jangan:** `nextInt` lalu `nextLine` tanpa menyadari newline. Jangan `close()` `Scanner(System.in)` di library yang masih butuh stdin (di `main` tugas kecil biasanya boleh).

---

## Pola: pecah main

**Tipe:** resep struktur

**Untuk apa:** menaruh logika di method bernama, `main` hanya merakit.

**Contoh implementasi:**

```java
public class MainPendek {
    static int subtotal(int[] harga) {
        int s = 0;
        for (int h : harga) {
            s += h;
        }
        return s;
    }

    static int pajak(int dasar) {
        return dasar * 11 / 100;
    }

    static void cetak(int dasar, int pajak) {
        System.out.println("Dasar: " + dasar);
        System.out.println("Pajak: " + pajak);
        System.out.println("Bayar: " + (dasar + pajak));
    }

    public static void main(String[] args) {
        int[] harga = { 15000, 3000, 2000 };
        int dasar = subtotal(harga);
        cetak(dasar, pajak(dasar));
    }
}
```

**Yang terjadi:** tiga tanggung jawab terpisah. Mengubah rumus pajak tidak merusak loop. Output tiga baris struk.

**Biasanya digabungkan dengan:** class di bab 04 saat data mulai punya identitas.

**Jangan:** `main` 200 baris `if` bersarang. Jangan method 200 baris juga — pecah lagi.

---

Lanjut ke [04 — class, inheritance, interface](04-oop-class-inheritance.md).
