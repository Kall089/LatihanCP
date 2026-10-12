# 05 — Collections: List, Set, Map

[← 04 OOP](04-oop-class-inheritance.md) · [Lanjut 06 exception & file →](06-exception-file-io.md)

Collection Framework menyimpan banyak objek. **List** berurut dan boleh duplikat. **Set** unik. **Map** pasangan kunci-nilai (bukan `Collection`, tetapi satu keluarga). Elemen adalah objek: `List<int>` ilegal, pakai `List<Integer>`.

## Daftar isi

- [Collection](#collection)
- [List](#list)
- [ArrayList](#arraylist)
- [ArrayList.add](#arraylistadd)
- [ArrayList.get](#arraylistget)
- [ArrayList.set](#arraylistset)
- [ArrayList.remove](#arraylistremove)
- [ArrayList.size](#arraylistsize)
- [ArrayList.contains](#arraylistcontains)
- [ArrayList.indexOf](#arraylistindexof)
- [ArrayList.clear](#arraylistclear)
- [ArrayList.addAll](#arraylistaddall)
- [ArrayList.toArray](#arraylisttoarray)
- [ArrayList.subList](#arraylistsublist)
- [LinkedList](#linkedlist)
- [LinkedList.addFirst addLast](#linkedlistaddfirst-addlast)
- [LinkedList sebagai Queue](#linkedlist-sebagai-queue)
- [List.of](#listof)
- [HashSet](#hashset)
- [HashSet.add](#hashsetadd)
- [HashSet.contains](#hashsetcontains)
- [HashSet.remove](#hashsetremove)
- [LinkedHashSet](#linkedhashset)
- [TreeSet](#treeset)
- [TreeSet.first last](#treesetfirst-last)
- [TreeSet.subSet](#treesetsubset)
- [HashMap](#hashmap)
- [HashMap.put](#hashmapput)
- [HashMap.get](#hashmapget)
- [HashMap.getOrDefault](#hashmapgetordefault)
- [HashMap.containsKey](#hashmapcontainskey)
- [HashMap.remove](#hashmapremove)
- [HashMap.keySet values entrySet](#hashmapkeyset-values-entryset)
- [HashMap.putIfAbsent](#hashmapputifabsent)
- [HashMap.computeIfAbsent](#hashmapcomputeifabsent)
- [LinkedHashMap](#linkedhashmap)
- [TreeMap](#treemap)
- [Iterator](#iterator)
- [removeIf](#removeif)
- [Collections.sort](#collectionssort)
- [forEach](#foreach)
- [Queue dan ArrayDeque](#queue-dan-arraydeque)
- [PriorityQueue](#priorityqueue)
- [Pilih struktur](#pilih-struktur)

---

### Collection

**Tipe:** interface (`java.util.Collection`)

**Untuk apa:** kontrak bersama List dan Set: `add`, `remove`, `size`, `iterator`. Map **bukan** Collection.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;

public class CollectionDemo {
    static void cetak(Collection<String> c) {
        System.out.println(c.getClass().getSimpleName() + " size=" + c.size() + " " + c);
    }

    public static void main(String[] args) {
        Collection<String> list = new ArrayList<>();
        list.add("Buku");
        list.add("Buku");
        Collection<String> set = new HashSet<>();
        set.add("Buku");
        set.add("Buku");
        cetak(list);
        cetak(set);
    }
}
```

**Yang terjadi:** method `cetak` menerima keduanya. List menyimpan dua `"Buku"`. Set menyimpan satu. `size` dan `toString` berbeda.

**Biasanya digabungkan dengan:** polimorfisme, `addAll`, loop.

**Jangan:** menaruh `Map` ke parameter `Collection`. Jangan mengandalkan urutan pada `Collection` umum — hanya List (dan Set tertentu) yang berjanji urutan.

---

### List

**Tipe:** interface (`java.util.List`)

**Untuk apa:** urutan, indeks, duplikat diizinkan. Implementasi umum: `ArrayList`, `LinkedList`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ListInterface {
    public static void main(String[] args) {
        List<String> keranjang = new ArrayList<>();
        keranjang.add("Buku");
        keranjang.add("Pensil");
        keranjang.add("Buku");
        System.out.println(keranjang.get(1));
        System.out.println(keranjang);
        System.out.println("indeks Buku pertama=" + keranjang.indexOf("Buku"));
    }
}
```

**Yang terjadi:** tiga elemen, `"Buku"` dua kali. `get(1)` `"Pensil"`. `indexOf` 0.

**Biasanya digabungkan dengan:** `ArrayList` sebagai default, `LinkedList` jika sering sisip di ujung sebagai deque.

**Jangan:** `List` raw `List list = new ArrayList();` tanpa generics — peringatan dan cast berbahaya.

---

### ArrayList

**Tipe:** class (`java.util.ArrayList`)

**Untuk apa:** list berbasis array dinamis. `get`/`set` cepat (O(1)). `add` di akhir biasanya cepat. Sisip/hapus di tengah menggeser (O(n)).

**Contoh implementasi:**

```java
import java.util.ArrayList;

public class ContohArrayList {
    public static void main(String[] args) {
        ArrayList<String> menu = new ArrayList<>();
        menu.add("Nasi goreng");
        menu.add("Es teh");
        menu.add("Pisang goreng");
        System.out.println(menu);
        System.out.println("ke-0=" + menu.get(0));
        menu.set(1, "Es jeruk");
        System.out.println(menu);
        menu.remove("Nasi goreng");
        System.out.println(menu);
        System.out.println("size=" + menu.size());
    }
}
```

**Yang terjadi:** tiga item, `set` menukar minuman, `remove` menghapus nasi (elemen pertama yang `equals`). Size 2.

**Biasanya digabungkan dengan:** `List<String> x = new ArrayList<>()` (program ke interface), loop, `sort`.

**Jangan:** `new ArrayList<String>(20)` lalu mengira sudah ada 20 elemen — itu **kapasitas**, `size` tetap 0. Jangan akses `get` tanpa cek size.

---

### ArrayList.add

**Tipe:** method (`List.add`)

**Untuk apa:** `add(e)` di akhir. `add(index, e)` sisip, geser ke kanan.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListAdd {
    public static void main(String[] args) {
        List<String> antrian = new ArrayList<>();
        antrian.add("A");
        antrian.add("C");
        antrian.add(1, "B");
        boolean masuk = antrian.add("D");
        System.out.println(antrian);
        System.out.println("add mengembalikan " + masuk);
        try {
            antrian.add(10, "Z");
        } catch (IndexOutOfBoundsException ex) {
            System.out.println("indeks sisip harus 0..size");
        }
    }
}
```

**Yang terjadi:** `[A, B, C, D]`. `add` di akhir mengembalikan `true`. Sisip indeks 10 gagal. Indeks sah untuk sisip: 0 sampai `size` (size = tempel di ujung).

**Biasanya digabungkan dengan:** `addAll`, pembacaan file per baris.

**Jangan:** `add` ke `List.of` — immutable. Jangan sisip berulang di indeks 0 pada list panjang — lambat.

---

### ArrayList.get

**Tipe:** method (`List.get`)

**Untuk apa:** baca elemen ke-i, 0-based.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListGet {
    public static void main(String[] args) {
        List<Integer> harga = new ArrayList<>();
        harga.add(15000);
        harga.add(3000);
        System.out.println(harga.get(0) + harga.get(1));
        try {
            harga.get(2);
        } catch (IndexOutOfBoundsException ex) {
            System.out.println("tidak ada indeks 2, size=" + harga.size());
        }
    }
}
```

**Yang terjadi:** 18000. `get(2)` exception, bukan `null` (kecuali elemennya memang null).

**Biasanya digabungkan dengan:** loop `for (int i = 0; i < list.size(); i++)`.

**Jangan:** `get(-1)`. Jangan `get` di `LinkedList` besar berulang dari indeks acak — O(n) tiap kali; pakai iterator/for-each.

---

### ArrayList.set

**Tipe:** method (`List.set`)

**Untuk apa:** menimpa elemen yang sudah ada, mengembalikan nilai lama.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListSet {
    public static void main(String[] args) {
        List<String> rak = new ArrayList<>();
        rak.add("Buku A");
        rak.add("Buku B");
        String lama = rak.set(1, "Buku C");
        System.out.println("terganti: " + lama);
        System.out.println(rak);
        try {
            rak.set(2, "Buku D");
        } catch (IndexOutOfBoundsException ex) {
            System.out.println("set tidak menambah panjang");
        }
    }
}
```

**Yang terjadi:** `"Buku B"` dikembalikan. List `[Buku A, Buku C]`. `set(2)` gagal — `set` bukan `add`.

**Biasanya digabungkan dengan:** `indexOf` lalu `set`.

**Jangan:** memakai `set` untuk “tambah jika belum ada”.

---

### ArrayList.remove

**Tipe:** method (dua overload)

**Untuk apa:** `remove(index)` hapus posisi, mengembalikan elemen. `remove(Object)` hapus kemunculan pertama yang `equals`, mengembalikan boolean.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListRemove {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>();
        k.add("Buku");
        k.add("Pensil");
        k.add("Buku");
        boolean hapusObjek = k.remove("Buku");
        System.out.println("hapus objek=" + hapusObjek + " " + k);
        String hapusIndeks = k.remove(0);
        System.out.println("hapus indeks=" + hapusIndeks + " " + k);

        List<Integer> angka = new ArrayList<>();
        angka.add(1);
        angka.add(2);
        angka.remove(1);
        System.out.println("remove(1) pada Integer: " + angka);
        angka.add(2);
        angka.remove(Integer.valueOf(1));
        System.out.println("remove nilai 1: " + angka);
    }
}
```

**Yang terjadi:** `remove("Buku")` menghapus yang pertama, sisa Pensil+Buku. `remove(0)` mengambil Pensil. Pada `List<Integer>`, `remove(1)` artinya **indeks 1**, bukan nilai 1. `remove(Integer.valueOf(1))` menghapus nilai.

**Biasanya digabungkan dengan:** `removeIf`, Iterator.

**Jangan:** `remove(i)` di dalam for-i maju tanpa menyesuaikan indeks — elemen terlewati. Jangan salah overload `Integer`.

---

### ArrayList.size

**Tipe:** method (`Collection.size`)

**Untuk apa:** jumlah elemen sekarang, bukan kapasitas internal.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListSize {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>(100);
        System.out.println("awal size=" + k.size() + " empty=" + k.isEmpty());
        k.add("a");
        k.add("b");
        System.out.println("size=" + k.size());
        k.clear();
        System.out.println("setelah clear=" + k.size());
    }
}
```

**Yang terjadi:** kapasitas 100, size 0, `isEmpty` true. Setelah dua add, size 2. `clear` size 0.

**Biasanya digabungkan dengan:** loop, validasi “keranjang kosong”.

**Jangan:** `list.length` — itu array. Jangan mengira `size` otomatis = kapasitas constructor.

---

### ArrayList.contains

**Tipe:** method

**Untuk apa:** cek keanggotaan lewat `equals` (linier).

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListContains {
    public static void main(String[] args) {
        List<String> member = new ArrayList<>();
        member.add("Haikal");
        member.add("Siti");
        System.out.println(member.contains("Siti"));
        System.out.println(member.contains("siti"));
        System.out.println(member.contains(null));
        member.add(null);
        System.out.println(member.contains(null));
    }
}
```

**Yang terjadi:** `"Siti"` true, `"siti"` false. `null` awalnya false, setelah `add(null)` true. ArrayList **mengizinkan** `null`.

**Biasanya digabungkan dengan:** `if (!list.contains(x)) list.add(x)` — untuk keunikan, `Set` lebih jujur.

**Jangan:** `contains` berulang pada list sangat panjang di dalam loop (O(n²)). Pakai `HashSet`.

---

### ArrayList.indexOf

**Tipe:** method

**Untuk apa:** indeks pertama, atau -1. `lastIndexOf` dari belakang.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListIndexOf {
    public static void main(String[] args) {
        List<String> log = new ArrayList<>();
        log.add("IN");
        log.add("OUT");
        log.add("IN");
        System.out.println(log.indexOf("IN"));
        System.out.println(log.lastIndexOf("IN"));
        System.out.println(log.indexOf("PAY"));
    }
}
```

**Yang terjadi:** 0, 2, -1.

**Biasanya digabungkan dengan:** `if (i >= 0) list.set(i, baru)`.

**Jangan:** memakai -1 sebagai indeks `get`.

---

### ArrayList.clear

**Tipe:** method

**Untuk apa:** mengosongkan list, objek lama bisa di-GC jika tidak ditunjuk lain.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListClear {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>();
        k.add("A");
        k.add("B");
        List<String> tampilan = k;
        k.clear();
        System.out.println("k=" + k + " tampilan=" + tampilan);
        System.out.println(k == tampilan);
    }
}
```

**Yang terjadi:** `tampilan` merujuk list yang sama, jadi ikut kosong. `==` true.

**Biasanya digabungkan dengan:** reset keranjang, reuse list.

**Jangan:** `clear` lalu mengira ada “versi lama” di variabel lain yang menunjuk objek sama.

---

### ArrayList.addAll

**Tipe:** method

**Untuk apa:** menambahkan semua isi collection lain.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListAddAll {
    public static void main(String[] args) {
        List<String> a = new ArrayList<>(List.of("Buku", "Pensil"));
        List<String> b = List.of("Teh", "Kopi");
        a.addAll(b);
        a.addAll(1, List.of("Spidol"));
        System.out.println(a);
    }
}
```

**Yang terjadi:** `[Buku, Spidol, Pensil, Teh, Kopi]`. `addAll` di indeks 1 menyisip.

**Biasanya digabungkan dengan:** gabung hasil query, salin `new ArrayList<>(lain)`.

**Jangan:** `a.addAll(a)` pada sebagian implementasi/kondisi — bisa loop tak terbatas atau perilaku aneh. Salin dulu.

---

### ArrayList.toArray

**Tipe:** method

**Untuk apa:** snapshot array. Lebih aman overload `toArray(T[])` atau `toArray(String[]::new)`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public class ArrayListToArray {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>(List.of("A", "B"));
        String[] arr = k.toArray(new String[0]);
        System.out.println(Arrays.toString(arr));
        arr[0] = "Z";
        System.out.println("list tetap " + k);
        Object[] mentah = k.toArray();
        System.out.println(mentah[1]);
    }
}
```

**Yang terjadi:** array `A,B`. Mengubah array tidak mengubah list (salinan). `toArray()` tanpa argumen adalah `Object[]`.

**Biasanya digabungkan dengan:** API yang menuntut array.

**Jangan:** `String[] s = (String[]) list.toArray();` — `ClassCastException`.

---

### ArrayList.subList

**Tipe:** method

**Untuk apa:** pandangan rentang `[from, to)` yang **hidup** pada list induk.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ArrayListSubList {
    public static void main(String[] args) {
        List<String> semua = new ArrayList<>(List.of("a", "b", "c", "d"));
        List<String> tengah = semua.subList(1, 3);
        System.out.println(tengah);
        tengah.set(0, "B");
        System.out.println("induk: " + semua);
        tengah.clear();
        System.out.println("setelah clear sub: " + semua);
    }
}
```

**Yang terjadi:** `tengah` `[b, c]`. `set` mengubah induk jadi `[a, B, c, d]`. `clear` pada sub menghapus rentang: `[a, d]`.

**Biasanya digabungkan dengan:** potong halaman, `new ArrayList<>(list.subList(...))` untuk salinan mandiri.

**Jangan:** mengubah induk dengan `add` di luar sub lalu memakai sub — `ConcurrentModificationException`. Jangan mengira subList adalah salinan.

---

### LinkedList

**Tipe:** class (`java.util.LinkedList`)

**Untuk apa:** list tautan ganda. Implementasi `List` + `Deque`. Sisip/hapus di **ujung** O(1). `get(i)` O(n).

**Contoh implementasi:**

```java
import java.util.LinkedList;

public class ContohLinkedList {
    public static void main(String[] args) {
        LinkedList<String> antre = new LinkedList<>();
        antre.add("pertama");
        antre.add("kedua");
        antre.addFirst("darurat");
        antre.addLast("terakhir");
        System.out.println(antre);
        System.out.println("peek=" + antre.peekFirst());
        System.out.println("hapus ujung=" + antre.removeFirst());
        System.out.println(antre);
        System.out.println("get(1)=" + antre.get(1));
    }
}
```

**Yang terjadi:** `[darurat, pertama, kedua, terakhir]`. `peekFirst` tidak menghapus. `removeFirst` mengambil darurat. `get(1)` menelusuri dari kepala.

**Biasanya digabungkan dengan:** antrian, undo stack (`push`/`pop`), `Deque`.

**Jangan:** memilih `LinkedList` “karena terdengar canggih” untuk akses acak. `ArrayList` hampir selalu lebih cepat di tugas kuliah.

---

### LinkedList.addFirst addLast

**Tipe:** method (`Deque`)

**Untuk apa:** menaruh di kepala atau ekor tanpa peduli indeks.

**Contoh implementasi:**

```java
import java.util.LinkedList;

public class LinkedListUjung {
    public static void main(String[] args) {
        LinkedList<Integer> d = new LinkedList<>();
        d.addLast(2);
        d.addLast(3);
        d.addFirst(1);
        System.out.println(d);
        System.out.println(d.removeLast());
        System.out.println(d);
    }
}
```

**Yang terjadi:** `[1, 2, 3]`, `removeLast` 3, sisa `[1, 2]`.

**Biasanya digabungkan dengan:** antrian FIFO (`addLast` + `removeFirst`).

**Jangan:** `get(i)` berulang untuk “berjalan” — pakai for-each.

---

### LinkedList sebagai Queue

**Tipe:** pemakaian `Queue`

**Untuk apa:** FIFO: masuk belakang, keluar depan.

**Contoh implementasi:**

```java
import java.util.LinkedList;
import java.util.Queue;

public class LinkedListQueue {
    public static void main(String[] args) {
        Queue<String> q = new LinkedList<>();
        q.offer("tiket-1");
        q.offer("tiket-2");
        q.offer("tiket-3");
        while (!q.isEmpty()) {
            System.out.println("layani " + q.poll());
        }
        System.out.println("poll kosong=" + q.poll());
    }
}
```

**Yang terjadi:** layani 1 lalu 2 lalu 3. `poll` pada kosong mengembalikan `null` (beda `remove` yang exception). `offer` lebih ramah dari `add` pada antrean berkapasitas (di `LinkedList` keduanya hampir sama).

**Biasanya digabungkan dengan:** BFS, antrean printer.

**Jangan:** `element()`/`remove()` tanpa cek jika kosong mungkin terjadi dan kamu tidak ingin exception.

---

### List.of

**Tipe:** method static (Java 9+)

**Untuk apa:** list **immutable** ringkas. Tidak `add`/`set`/`remove`. Tidak berisi `null`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class ListOfDemo {
    public static void main(String[] args) {
        List<String> tetap = List.of("A", "B");
        System.out.println(tetap);
        try {
            tetap.add("C");
        } catch (UnsupportedOperationException ex) {
            System.out.println("List.of tidak bisa add");
        }
        List<String> bisa = new ArrayList<>(List.of("A", "B"));
        bisa.add("C");
        System.out.println(bisa);
        try {
            List.of("A", null);
        } catch (NullPointerException ex) {
            System.out.println("null ditolak");
        }
    }
}
```

**Yang terjadi:** `List.of` beku. Salin ke `ArrayList` untuk list hidup. `null` elemen ditolak.

**Biasanya digabungkan dengan:** data contoh, `addAll`.

**Jangan:** `List.of` lalu `set`. Jangan bingung dengan `Arrays.asList` (boleh `set`, tidak boleh `add`).

---

### HashSet

**Tipe:** class (`java.util.HashSet`)

**Untuk apa:** himpunan unik, tanpa urutan dijamin, `add`/`contains`/`remove` rata-rata O(1). Berbasis hash.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Set;

public class ContohHashSet {
    public static void main(String[] args) {
        Set<String> sku = new HashSet<>();
        System.out.println(sku.add("BK-1"));
        System.out.println(sku.add("BK-2"));
        System.out.println(sku.add("BK-1"));
        System.out.println(sku);
        System.out.println("punya BK-2? " + sku.contains("BK-2"));
        sku.remove("BK-2");
        System.out.println(sku);
    }
}
```

**Yang terjadi:** `add` pertama/kedua true, `add` `"BK-1"` kedua **false** (sudah ada). `toString` urutan tidak dijamin. `contains` true. Setelah remove, satu elemen.

**Biasanya digabungkan dengan:** `equals`/`hashCode` pada classmu, filter duplikat `new HashSet<>(list)`.

**Jangan:** mengandalkan urutan cetak. Jangan mengubah field kunci setelah objek masuk set.

---

### HashSet.add

**Tipe:** method (`Set.add`)

**Untuk apa:** memasukkan jika belum `equals` ke anggota ada. Return true jika set berubah.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Set;

public class HashSetAdd {
    public static void main(String[] args) {
        Set<Integer> s = new HashSet<>();
        s.add(1);
        s.add(1);
        s.add(null);
        s.add(null);
        System.out.println(s);
        System.out.println("size=" + s.size());
    }
}
```

**Yang terjadi:** `{1, null}` (urutan bebas), size 2. HashSet mengizinkan **satu** `null`.

**Biasanya digabungkan dengan:** `if (set.add(x)) { /* pertama kali */ }`.

**Jangan:** `TreeSet.add(null)` (kecuali comparator tahan null) — biasanya NPE.

---

### HashSet.contains

**Tipe:** method

**Untuk apa:** keanggotaan cepat. Memakai `hashCode` lalu `equals`.

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Objects;
import java.util.Set;

public class HashSetContains {
    static class Sku {
        final String kode;
        Sku(String kode) { this.kode = kode; }
        @Override public boolean equals(Object o) {
            return o instanceof Sku s && Objects.equals(kode, s.kode);
        }
        @Override public int hashCode() { return Objects.hashCode(kode); }
        @Override public String toString() { return kode; }
    }

    public static void main(String[] args) {
        Set<Sku> s = new HashSet<>();
        s.add(new Sku("BK-1"));
        System.out.println(s.contains(new Sku("BK-1")));
        System.out.println(s.contains(new Sku("BK-9")));
    }
}
```

**Yang terjadi:** `contains` true untuk objek **baru** berkode sama, karena `equals`/`hashCode`. Tanpa keduanya, false.

**Biasanya digabungkan dengan:** class kunci yang immutable.

**Jangan:** class tanpa `hashCode` di `HashSet`.

---

### HashSet.remove

**Tipe:** method

**Untuk apa:** hapus berdasarkan `equals`, bukan indeks (Set tidak berindeks).

**Contoh implementasi:**

```java
import java.util.HashSet;
import java.util.Set;

public class HashSetRemove {
    public static void main(String[] args) {
        Set<String> s = new HashSet<>();
        s.add("A");
        s.add("B");
        System.out.println(s.remove("A"));
        System.out.println(s.remove("Z"));
        System.out.println(s);
    }
}
```

**Yang terjadi:** true, false, sisa `B`.

**Biasanya digabungkan dengan:** `removeAll`, `retainAll`.

**Jangan:** `remove(0)` mengira indeks — itu `remove(Integer)` / objek `Integer.valueOf(0)` jika set integer.

---

### LinkedHashSet

**Tipe:** class

**Untuk apa:** unik seperti `HashSet`, tetapi **mengingat urutan insert**.

**Contoh implementasi:**

```java
import java.util.LinkedHashSet;
import java.util.Set;

public class ContohLinkedHashSet {
    public static void main(String[] args) {
        Set<String> s = new LinkedHashSet<>();
        s.add("pisang");
        s.add("apel");
        s.add("pisang");
        s.add("mangga");
        System.out.println(s);
    }
}
```

**Yang terjadi:** `[pisang, apel, mangga]` — duplikat dibuang, urutan pertama kali masuk terjaga.

**Biasanya digabungkan dengan:** “unik tapi tetap urutan tampilan”.

**Jangan:** mengira `HashSet` melakukan ini.

---

### TreeSet

**Tipe:** class (`java.util.TreeSet`)

**Untuk apa:** set terurut (merah-hitam). Elemen harus `Comparable` atau diberi `Comparator`. Tidak `null` (urutan alami).

**Contoh implementasi:**

```java
import java.util.Set;
import java.util.TreeSet;

public class ContohTreeSet {
    public static void main(String[] args) {
        Set<String> s = new TreeSet<>();
        s.add("jeruk");
        s.add("apel");
        s.add("mangga");
        s.add("apel");
        System.out.println(s);
        TreeSet<Integer> n = new TreeSet<>();
        n.add(30);
        n.add(10);
        n.add(20);
        System.out.println(n);
        System.out.println("first=" + n.first() + " last=" + n.last());
    }
}
```

**Yang terjadi:** string terurut leksikografis `[apel, jeruk, mangga]`. Angka `[10, 20, 30]`. `first`/`last` 10 dan 30.

**Biasanya digabungkan dengan:** `Comparator.reverseOrder()`, `NavigableSet`.

**Jangan:** menaruh class tanpa `Comparable` — `ClassCastException` saat `add` kedua. Jangan andalkan hash; TreeSet memakai `compareTo` (konsistensi dengan `equals` penting).

---

### TreeSet.first last

**Tipe:** method (`SortedSet`)

**Untuk apa:** elemen terkecil/terbesar, exception jika kosong.

**Contoh implementasi:**

```java
import java.util.TreeSet;

public class TreeSetFirstLast {
    public static void main(String[] args) {
        TreeSet<Integer> antrianPrioritasAngka = new TreeSet<>();
        antrianPrioritasAngka.add(5);
        antrianPrioritasAngka.add(1);
        antrianPrioritasAngka.add(9);
        System.out.println(antrianPrioritasAngka.first());
        System.out.println(antrianPrioritasAngka.last());
        System.out.println(antrianPrioritasAngka.higher(5));
        System.out.println(antrianPrioritasAngka.lower(5));
        antrianPrioritasAngka.clear();
        try {
            antrianPrioritasAngka.first();
        } catch (java.util.NoSuchElementException ex) {
            System.out.println("kosong");
        }
    }
}
```

**Yang terjadi:** 1, 9, `higher(5)`=9, `lower(5)`=1. `first` pada kosong exception.

**Biasanya digabungkan dengan:** `pollFirst` untuk ambil-dan-hapus terkecil.

**Jangan:** `first` tanpa `isEmpty` jika kosong mungkin.

---

### TreeSet.subSet

**Tipe:** method

**Untuk apa:** pandangan rentang terurut.

**Contoh implementasi:**

```java
import java.util.TreeSet;

public class TreeSetSubSet {
    public static void main(String[] args) {
        TreeSet<Integer> n = new TreeSet<>();
        n.add(1);
        n.add(3);
        n.add(5);
        n.add(7);
        n.add(9);
        System.out.println(n.subSet(3, 8));
        System.out.println(n.headSet(5));
        System.out.println(n.tailSet(5));
    }
}
```

**Yang terjadi:** `subSet(3,8)` → 3,5,7 (8 eksklusif). `headSet(5)` → 1,3. `tailSet(5)` → 5,7,9.

**Biasanya digabungkan dengan:** filter rentang harga/tanggal jika disimpan sebagai Comparable.

**Jangan:** mengubah himpunan di luar rentang lewat view dengan cara yang merusak — ikuti kontrak `SortedSet`.

---

### HashMap

**Tipe:** class (`java.util.HashMap`)

**Untuk apa:** kamus kunci → nilai. Kunci unik. Satu `null` key, banyak `null` value. Tanpa urutan.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class ContohHashMap {
    public static void main(String[] args) {
        Map<String, Integer> stok = new HashMap<>();
        stok.put("Buku", 10);
        stok.put("Pensil", 50);
        stok.put("Buku", 8);
        System.out.println(stok);
        System.out.println("stok buku=" + stok.get("Buku"));
        System.out.println("penghapus=" + stok.get("Penghapus"));
        System.out.println("size=" + stok.size());
    }
}
```

**Yang terjadi:** `put` `"Buku"` kedua **menimpa** 10 jadi 8, size tetap 2. `get` kunci tiada → `null` (bukan exception).

**Biasanya digabungkan dengan:** `getOrDefault`, `containsKey`, loop `entrySet`.

**Jangan:** `get` lalu unbox ke `int` jika kunci bisa absen — NPE. Jangan kunci mutable.

---

### HashMap.put

**Tipe:** method

**Untuk apa:** sisip atau timpa. Mengembalikan nilai **lama**, atau `null` jika baru (atau lama memang null).

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapPut {
    public static void main(String[] args) {
        Map<String, Integer> harga = new HashMap<>();
        System.out.println("put baru=" + harga.put("Teh", 5000));
        System.out.println("put timpa=" + harga.put("Teh", 5500));
        System.out.println(harga);
    }
}
```

**Yang terjadi:** put pertama `null`, kedua `5000`, map `{Teh=5500}`.

**Biasanya digabungkan dengan:** `putIfAbsent` jika tidak ingin menimpa.

**Jangan:** memakai return `null` sebagai “kunci baru” jika nilai `null` diizinkan — ambigu. Pakai `containsKey` atau `putIfAbsent`.

---

### HashMap.get

**Tipe:** method

**Untuk apa:** ambil nilai atau `null`.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapGet {
    public static void main(String[] args) {
        Map<String, Integer> stok = new HashMap<>();
        stok.put("Buku", 0);
        System.out.println(stok.get("Buku"));
        System.out.println(stok.get("Radio"));
        Integer s = stok.get("Buku");
        if (s != null) {
            System.out.println("ada kunci, nilai=" + s);
        }
    }
}
```

**Yang terjadi:** 0 tercetak (kunci ada, stok habis). `"Radio"` null. `0` dan “tidak ada” **beda**; `get` saja tidak cukup jika `null` value dipakai.

**Biasanya digabungkan dengan:** `containsKey`, `getOrDefault`.

**Jangan:** `int x = map.get(k)` tanpa jaga null.

---

### HashMap.getOrDefault

**Tipe:** method (Java 8+)

**Untuk apa:** nilai cadangan jika kunci tiada. **Tidak** menulis ke map.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapGetOrDefault {
    public static void main(String[] args) {
        Map<String, Integer> hitung = new HashMap<>();
        hitung.put("Buku", 2);
        int buku = hitung.getOrDefault("Buku", 0);
        int teh = hitung.getOrDefault("Teh", 0);
        System.out.println(buku + " " + teh);
        System.out.println(hitung);
    }
}
```

**Yang terjadi:** 2 dan 0. Map tetap hanya `Buku`. 0 tidak disimpan otomatis.

**Biasanya digabungkan dengan:** histogram (`put(k, getOrDefault(k,0)+1)`), tampilan.

**Jangan:** mengira `getOrDefault` mengisi map. Itu `putIfAbsent` / `computeIfAbsent`.

---

### HashMap.containsKey

**Tipe:** method

**Untuk apa:** membedakan “tidak ada kunci” vs “nilai null/0”.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapContainsKey {
    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        m.put("Buku", null);
        System.out.println("get Buku=" + m.get("Buku"));
        System.out.println("contains Buku=" + m.containsKey("Buku"));
        System.out.println("contains Teh=" + m.containsKey("Teh"));
        System.out.println("containsValue null=" + m.containsValue(null));
    }
}
```

**Yang terjadi:** `get` null, tetapi `containsKey("Buku")` true. `"Teh"` false.

**Biasanya digabungkan dengan:** nilai opsional, `remove`.

**Jangan:** `if (get(k) != null)` sebagai satu-satunya cek keberadaan.

---

### HashMap.remove

**Tipe:** method

**Untuk apa:** hapus kunci, return nilai lama. Overload `remove(k, v)` hapus hanya jika nilai cocok.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapRemove {
    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        m.put("Buku", 3);
        m.put("Teh", 1);
        System.out.println(m.remove("Buku"));
        System.out.println(m.remove("Susu"));
        System.out.println(m.remove("Teh", 99));
        System.out.println(m);
        System.out.println(m.remove("Teh", 1));
        System.out.println(m);
    }
}
```

**Yang terjadi:** remove Buku → 3. Susu → null. `remove("Teh",99)` false, Teh masih ada. `remove("Teh",1)` true, map kosong.

**Biasanya digabungkan dengan:** sesi, cache.

**Jangan:** `remove` di dalam for-each `keySet` tanpa Iterator — CME. Pakai `keySet().removeIf` atau Iterator.

---

### HashMap.keySet values entrySet

**Tipe:** method tampilan

**Untuk apa:** menelusuri kunci, nilai, atau pasangan. Tampilan **hidup**: hapus di set memengaruhi map.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapViews {
    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        m.put("Buku", 10);
        m.put("Pensil", 50);
        System.out.println("kunci=" + m.keySet());
        System.out.println("nilai=" + m.values());
        for (Map.Entry<String, Integer> e : m.entrySet()) {
            System.out.println(e.getKey() + " -> " + e.getValue());
        }
        m.keySet().remove("Pensil");
        System.out.println("setelah hapus kunci: " + m);
    }
}
```

**Yang terjadi:** dua entry tercetak (urutan bebas). `keySet().remove` menghapus pasangan Pensil dari map.

**Biasanya digabungkan dengan:** `forEach((k,v) -> ...)`, Stream.

**Jangan:** `map.values().add(1)` — values tidak mendukung add. Jangan mengubah map secara struktural saat iterasi biasa.

---

### HashMap.putIfAbsent

**Tipe:** method

**Untuk apa:** menulis hanya jika kunci belum ada **atau** nilainya `null` (di HashMap, `putIfAbsent` menimpa null).

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.Map;

public class HashMapPutIfAbsent {
    public static void main(String[] args) {
        Map<String, Integer> m = new HashMap<>();
        System.out.println(m.putIfAbsent("Buku", 1));
        System.out.println(m.putIfAbsent("Buku", 99));
        System.out.println(m);
        m.put("Teh", null);
        System.out.println(m.putIfAbsent("Teh", 5));
        System.out.println(m);
    }
}
```

**Yang terjadi:** pertama `null` (baru), kedua `1` (tidak menimpa, tetap 1). `Teh` null dianggap absent: jadi 5, return `null`.

**Biasanya digabungkan dengan:** inisialisasi sekali.

**Jangan:** mengira 99 tersimpan. Baca return value.

---

### HashMap.computeIfAbsent

**Tipe:** method

**Untuk apa:** jika kunci tiada (atau null), **hitung** nilai lalu simpan. Cocok list-per-kunci.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ComputeIfAbsentDemo {
    public static void main(String[] args) {
        Map<String, List<String>> indeks = new HashMap<>();
        indeks.computeIfAbsent("minuman", k -> new ArrayList<>()).add("Teh");
        indeks.computeIfAbsent("minuman", k -> new ArrayList<>()).add("Kopi");
        indeks.computeIfAbsent("alat", k -> new ArrayList<>()).add("Pensil");
        System.out.println(indeks);
        Map<String, Integer> hitung = new HashMap<>();
        for (String n : List.of("Buku", "Teh", "Buku")) {
            hitung.put(n, hitung.getOrDefault(n, 0) + 1);
        }
        System.out.println(hitung);
    }
}
```

**Yang terjadi:** `"minuman"` memakai **satu** `ArrayList` untuk Teh dan Kopi. Histogram Buku=2, Teh=1.

**Biasanya digabungkan dengan:** grouping manual, cache.

**Jangan:** lambda yang return `null` di `computeIfAbsent` — kunci tidak tersimpan (Java 8+ perilaku: mapping dihapus/tidak ditulis).

---

### LinkedHashMap

**Tipe:** class

**Untuk apa:** map yang ingat urutan insert (atau access-order jika dikonfigurasi). Dasar LRU sederhana.

**Contoh implementasi:**

```java
import java.util.LinkedHashMap;
import java.util.Map;

public class ContohLinkedHashMap {
    public static void main(String[] args) {
        Map<String, Integer> m = new LinkedHashMap<>();
        m.put("pertama", 1);
        m.put("kedua", 2);
        m.put("ketiga", 3);
        System.out.println(m);
        for (String k : m.keySet()) {
            System.out.println(k);
        }
    }
}
```

**Yang terjadi:** iterasi `pertama, kedua, ketiga` — urutan masuk.

**Biasanya digabungkan dengan:** tampilan stabil, cache.

**Jangan:** mengira `HashMap` menjaga ini (sejak Java 8+ kadang kelihatan terurut untuk kunci kecil — **bukan kontrak**).

---

### TreeMap

**Tipe:** class

**Untuk apa:** map terurut menurut kunci.

**Contoh implementasi:**

```java
import java.util.Map;
import java.util.TreeMap;

public class ContohTreeMap {
    public static void main(String[] args) {
        Map<String, Integer> harga = new TreeMap<>();
        harga.put("Pensil", 3000);
        harga.put("Buku", 45000);
        harga.put("Penghapus", 2000);
        System.out.println(harga);
        TreeMap<Integer, String> t = new TreeMap<>();
        t.put(10, "sepuluh");
        t.put(2, "dua");
        t.put(7, "tujuh");
        System.out.println(t);
        System.out.println("ceiling 6=" + t.ceilingKey(6));
    }
}
```

**Yang terjadi:** kunci string alfabet. Kunci angka 2,7,10. `ceilingKey(6)` = 7.

**Biasanya digabungkan dengan:** `NavigableMap`, range query.

**Jangan:** kunci yang `compareTo` tidak selaras `equals`. Jangan `null` key.

---

### Iterator

**Tipe:** interface (`java.util.Iterator`)

**Untuk apa:** menelusuri dan **menghapus aman** saat iterasi.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class IteratorDemo {
    public static void main(String[] args) {
        List<String> k = new ArrayList<>(java.util.List.of("ok", "hapus", "ok", "hapus"));
        Iterator<String> it = k.iterator();
        while (it.hasNext()) {
            if (it.next().equals("hapus")) {
                it.remove();
            }
        }
        System.out.println(k);
        try {
            for (String s : k) {
                k.remove(s);
            }
        } catch (java.util.ConcurrentModificationException ex) {
            System.out.println("for-each + list.remove = CME");
        }
    }
}
```

**Yang terjadi:** sisa `[ok, ok]`. For-each plus `k.remove` melempar `ConcurrentModificationException`.

**Biasanya digabungkan dengan:** filter destruktif, `removeIf` (lebih pendek).

**Jangan:** `it.remove()` sebelum `next`. Jangan `list.remove` di dalam for-each.

---

### removeIf

**Tipe:** method (`Collection.removeIf`, Java 8+)

**Untuk apa:** hapus semua yang lolos predikat, tanpa CME.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.List;

public class RemoveIfDemo {
    public static void main(String[] args) {
        List<Integer> nilai = new ArrayList<>(List.of(80, 40, 90, 55, 30));
        nilai.removeIf(n -> n < 60);
        System.out.println(nilai);
        List<String> nama = new ArrayList<>(List.of("Buku", "", "Teh", "  "));
        nama.removeIf(String::isBlank);
        System.out.println(nama);
    }
}
```

**Yang terjadi:** nilai `[80, 90]`. Nama kosong/blank hilang.

**Biasanya digabungkan dengan:** lambda (bab 07).

**Jangan:** predikat yang mengubah collection lain dengan cara berbahaya. Jangan `removeIf` pada `List.of`.

---

### Collections.sort

**Tipe:** method static (`java.util.Collections`)

**Untuk apa:** mengurut `List`. Alternatif modern: `list.sort(comparator)`.

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class CollectionsSortDemo {
    public static void main(String[] args) {
        List<Integer> harga = new ArrayList<>(List.of(15000, 3000, 20000));
        Collections.sort(harga);
        System.out.println(harga);
        List<String> nama = new ArrayList<>(List.of("jeruk", "Apel", "mangga"));
        nama.sort(String.CASE_INSENSITIVE_ORDER);
        System.out.println(nama);
        nama.sort(Comparator.comparing(String::length));
        System.out.println(nama);
        Collections.reverse(harga);
        System.out.println(harga);
    }
}
```

**Yang terjadi:** harga naik. Nama case-insensitive lalu menurut panjang. `reverse` membalik list harga.

**Biasanya digabungkan dengan:** `Comparator.comparing`, class `Comparable` (bab 08).

**Jangan:** `Collections.sort` pada `List.of`. Jangan sort list yang elemennya tidak comparable tanpa comparator.

---

### forEach

**Tipe:** method (`Iterable.forEach`)

**Untuk apa:** menjalankan lambda per elemen.

**Contoh implementasi:**

```java
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ForEachDemo {
    public static void main(String[] args) {
        List.of("Buku", "Teh").forEach(item -> System.out.println("- " + item));
        Map<String, Integer> m = new HashMap<>();
        m.put("Buku", 2);
        m.put("Teh", 5);
        m.forEach((k, v) -> System.out.println(k + "=" + v));
    }
}
```

**Yang terjadi:** dua baris list, lalu dua baris map (urutan map bebas).

**Biasanya digabungkan dengan:** method reference `System.out::println`.

**Jangan:** `forEach` yang `remove` elemen — CME. Pakai `removeIf`.

---

### Queue dan ArrayDeque

**Tipe:** interface / class

**Untuk apa:** `ArrayDeque` adalah antrian/deque array sirkular, biasanya lebih cepat dari `LinkedList` sebagai queue/stack.

**Contoh implementasi:**

```java
import java.util.ArrayDeque;
import java.util.Deque;

public class ArrayDequeDemo {
    public static void main(String[] args) {
        Deque<String> stack = new ArrayDeque<>();
        stack.push("satu");
        stack.push("dua");
        System.out.println("pop=" + stack.pop());
        Deque<String> q = new ArrayDeque<>();
        q.addLast("A");
        q.addLast("B");
        System.out.println("poll=" + q.pollFirst());
        System.out.println(q);
    }
}
```

**Yang terjadi:** stack LIFO: pop `"dua"`. Queue FIFO: poll `"A"`, sisa `B`.

**Biasanya digabungkan dengan:** DFS (stack), BFS (queue).

**Jangan:** `ArrayDeque` dengan `null` elemen — ditolak. Jangan `Stack` legacy kecuali diminta.

---

### PriorityQueue

**Tipe:** class

**Untuk apa:** heap: setiap `poll` mengambil elemen terkecil (atau sesuai comparator), bukan FIFO.

**Contoh implementasi:**

```java
import java.util.PriorityQueue;

public class PriorityQueueDemo {
    public static void main(String[] args) {
        PriorityQueue<Integer> pq = new PriorityQueue<>();
        pq.offer(30);
        pq.offer(10);
        pq.offer(20);
        System.out.println("peek=" + pq.peek());
        while (!pq.isEmpty()) {
            System.out.print(pq.poll() + " ");
        }
        System.out.println();
        System.out.println("toString tidak wajib terurut: " + new PriorityQueue<>(java.util.List.of(3, 1, 2)));
    }
}
```

**Yang terjadi:** `peek` 10. `poll` 10,20,30. `toString` **bukan** jaminan urutan heap in-order.

**Biasanya digabungkan dengan:** `Comparator.reverseOrder()` untuk maksimum dulu.

**Jangan:** mengiterasi `PriorityQueue` mengira sudah terurut. Jangan `null`.

---

### Pilih struktur

**Tipe:** panduan (bukan API)

**Untuk apa:** memutuskan struktur sebelum coding.

| Kebutuhan | Pilih |
| --- | --- |
| Daftar berindeks, sering `get` | `ArrayList` |
| Antrean/stack | `ArrayDeque` |
| Unik, cepat cek | `HashSet` |
| Unik + urutan insert | `LinkedHashSet` |
| Unik + terurut | `TreeSet` |
| Kamus cepat | `HashMap` |
| Kamus terurut kunci | `TreeMap` |
| Kamus urutan insert | `LinkedHashMap` |
| List tetap contoh | `List.of` + salin jika perlu |

**Contoh implementasi:**

```java
import java.util.ArrayList;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class PilihStruktur {
    public static void main(String[] args) {
        List<String> antrianNama = new ArrayList<>();
        Set<String> emailUnik = new HashSet<>();
        Map<String, Integer> stok = new HashMap<>();
        antrianNama.add("Haikal");
        emailUnik.add("a@b.c");
        stok.put("Buku", 10);
        System.out.println(antrianNama + " " + emailUnik + " " + stok);
    }
}
```

**Yang terjadi:** tiga struktur dipakai sesuai peran, bukan semuanya `ArrayList`.

**Biasanya digabungkan dengan:** generics (bab 08), Stream (bab 07).

**Jangan:** `Vector`/`Hashtable` di kode baru tanpa alasan thread-safety lama. Jangan `HashMap` untuk data yang harus terurut tampilan — `LinkedHashMap`.

---

Lanjut ke [06 — exception dan file I/O](06-exception-file-io.md).
