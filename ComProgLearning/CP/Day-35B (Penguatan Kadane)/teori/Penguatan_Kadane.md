# 🔁 Day 35B: Penguatan Kadane

> Day 35 mengajarkan **cara kerjanya**. File ini mengejar tiga hal yang biasanya
> masih menggantung sesudahnya:
> **(A) kenapa itu benar, (B) kapan soal ini sebenarnya soal Kadane, (C) cara
> menurunkan variasi tanpa menghafal.**

---

## 🎯 Target Sesi Ini

- [ ] Menyebutkan **invariant** Kadane dari ingatan, tanpa melihat kode
- [ ] Membuktikan kenapa `cur = max(a[i], cur + a[i])` tidak pernah melewatkan jawaban
- [ ] Menjelaskan kenapa keputusan "buang atau lanjut" **hanya bergantung pada tanda `cur`**
- [ ] Melihat soal baru dan memutuskan Kadane / sliding window / deque / prefix-map dalam < 60 detik
- [ ] Menurunkan varian melingkar, produk, dan 2D **dari prinsip**, bukan hafalan

---

# BAGIAN A — Logika Inti

## A.1 Satu kalimat yang menjadi kunci semuanya

> **`dp[i]` = jumlah maksimum subarray yang berakhir TEPAT di indeks `i`.**

Kalau hanya satu hal yang kamu ingat dari Kadane, ingat kalimat ini. Kode
tiga barisnya cuma akibat.

Kenapa endpoint? Karena masalah aslinya punya **dua** derajat kebebasan
(`l` dan `r`) — itu ruang berukuran O(n²). Dengan **mengunci `r = i`**, ruang
pencariannya tinggal satu dimensi. Dan itu boleh, karena:

```
setiap subarray punya TEPAT SATU indeks akhir
→ himpunan semua subarray terpartisi rapi berdasarkan endpoint-nya
→ jawaban = max(dp[0], dp[1], ..., dp[n-1])
```

Tidak ada subarray yang terhitung dua kali, dan tidak ada yang terlewat.
Ini bukan trik Kadane — ini **pola umum** yang akan kamu pakai lagi di LIS,
di monotonic stack, dan di hampir semua DP array. Kunci satu ujung, iterasi
ujung itu.

## A.2 Rekurens, dan kenapa cuma ada dua pilihan

Subarray yang berakhir di `i` bentuknya `[l..i]`. Hanya ada dua kemungkinan:

1. `l == i` → subarray-nya cuma `{a[i]}` → jumlahnya `a[i]`
2. `l < i` → subarray-nya = (subarray yang berakhir di `i-1`) + `a[i]`

Untuk kasus 2, kita ingin subarray berakhir di `i-1` dengan jumlah **terbesar** —
dan itu persis `dp[i-1]`. Jadi:

```
dp[i] = max( a[i] , dp[i-1] + a[i] )
```

**Kenapa boleh langsung ambil `dp[i-1]` yang terbaik?** Ini yang namanya
*optimal substructure*, dan buktinya pendek:

> Misalkan subarray terbaik yang berakhir di `i` adalah `[l..i]` dengan `l < i`.
> Maka `sum(l..i) = sum(l..i-1) + a[i]`.
> Andaikan `sum(l..i-1) < dp[i-1]`, artinya ada `[l'..i-1]` yang lebih besar.
> Tempel `a[i]` padanya: `sum(l'..i) = sum(l'..i-1) + a[i] > sum(l..i)`.
> Kontradiksi — `[l..i]` tadi bukan yang terbaik.
> ∎ Jadi bagian `[l..i-1]` **harus** optimal.

Kuncinya: `a[i]` adalah **konstanta tambahan yang sama** untuk semua pilihan `l`.
Menambahkan konstanta yang sama tidak mengubah urutan siapa yang terbesar.
Itulah alasan greedy-nya aman.

## A.3 Kenapa keputusannya cuma soal tanda `cur`

Tulis ulang rekurensnya dengan mengeluarkan `a[i]`:

```
dp[i] = max(a[i], dp[i-1] + a[i])
      = a[i] + max(0, dp[i-1])          ← bentuk yang paling menjelaskan
```

Baca versi kedua itu keras-keras: **`a[i]` selalu ikut. Yang jadi pertanyaan
hanyalah apakah kita membawa `dp[i-1]` atau membawa nol.**

Dan `max(0, dp[i-1])` jawabannya sepele:

| kondisi | artinya | tindakan |
|---|---|---|
| `dp[i-1] > 0` | masa lalu **menambah** nilai | bawa terus |
| `dp[i-1] ≤ 0` | masa lalu **beban** | buang, mulai dari `a[i]` |

Tidak peduli seberapa panjang, seberapa rumit, atau seberapa negatif isi
masa lalunya. Cuma tandanya. Sebabnya: kontribusi masa lalu ke setiap
subarray masa depan bersifat **aditif dan tetap** — ia menyumbang angka yang
sama persis ke semua kandidat berikutnya. Kalau angka itu negatif, ia merugikan
semuanya secara seragam. Buang.

> ⚠️ Ini juga persis alasan kenapa Kadane **rusak** untuk hasil kali:
> pada perkalian, "beban" negatif bisa berubah jadi untung besar begitu
> ketemu negatif berikutnya. Sifat aditifnya hilang → butuh dua variabel.
> (lihat C.4)

## A.4 Sudut pandang kedua: prefix minimum

Kalau versi DP masih licin, pakai yang ini — sebagian orang langsung "klik" di sini.

```
P[0] = 0, P[k] = a[0] + ... + a[k-1]
sum(l..r) = P[r+1] − P[l]
```

Kunci `r`. Maka memaksimalkan `sum(l..r)` = **meminimalkan `P[l]`** untuk `l ≤ r`.

```
dp[r] = P[r+1] − min{ P[0], P[1], ..., P[r] }
```

Jadi Kadane hanyalah: *jalan ke kanan sambil menyimpan prefix terkecil yang
pernah dilihat.* Variabel `cur` di kode itu identik dengan `P[i+1] − minP`.

**Dua sudut pandang ini setara.** Tapi keduanya berguna:

- **DP** lebih enak saat kamu perlu menambah *state* (varian hapus satu elemen, varian produk)
- **Prefix-min** lebih enak saat ada *batasan panjang* atau saat perlu rekonstruksi indeks

## A.5 Uji paham diri (jawab tanpa lihat kode)

1. Kenapa `best` tidak boleh diinisialisasi `0` kalau subarray tidak boleh kosong?
2. Kalau semua elemen positif, apa yang dilakukan Kadane? Kenapa itu masuk akal?
3. `dp[i-1] == 0` tepat — buang atau lanjut? Apakah hasilnya beda?
4. Kalau `a[i]` diganti `a[i] + 5` untuk **semua** `i`, apakah jawabannya jadi `lama + 5`? Kenapa tidak?
5. Sebutkan invariant `cur` dan invariant `best` di awal setiap iterasi.

<details>
<summary>Kunci</summary>

1. Karena `0` diam-diam mewakili "subarray kosong". Kalau semua elemen negatif,
   `best` akan tetap `0` dan itu jawaban untuk pertanyaan yang berbeda. Pakai `LLONG_MIN`
   (atau `best = a[0]`, `cur = a[0]`, mulai loop dari `i = 1`).
2. `cur` tidak pernah negatif, jadi tidak pernah reset — jawabannya seluruh array.
   Masuk akal: membuang elemen positif hanya mengurangi jumlah.
3. Nilai `best` **sama saja**. Yang berbeda cuma **indeks awal** yang tercatat:
   membuang memberi `l` lebih besar, melanjutkan memberi `l` lebih kecil.
   Karena itu soal "cari juga posisinya" sensitif pada `<` vs `<=`.
4. Tidak. Setiap elemen bertambah 5, jadi subarray panjang `k` bertambah `5k` —
   tambahannya bergantung panjang, sehingga pemenangnya bisa berubah total.
   (Ini alasan kenapa "normalisasi" naif merusak soal Kadane.)
5. Sebelum memproses `a[i]`: `cur` = jumlah maksimum subarray yang berakhir di `i-1`;
   `best` = jawaban untuk prefix `a[0..i-1]`.

</details>

---

# BAGIAN B — Kapan Soal Ini Soal Kadane

Ini bagian yang paling menentukan di kontes, dan paling jarang dilatih.

## B.1 Tiga sinyal yang harus muncul bersamaan

Kadane hampir pasti benar kalau **ketiganya** ada:

1. **Berurutan** — soal bilang "subarray", "potongan berurutan", "segmen", "rentang `[l..r]`"
   (kalau bilang "subsequence"/"boleh loncat" → **bukan** Kadane)
2. **Optimasi jumlah** — cari maksimum/minimum *sum*, bukan menghitung banyaknya
   (kalau "ada berapa subarray dengan sum = k" → prefix sum + `map`, **bukan** Kadane)
3. **Ada elemen negatif** (atau bisa dibuat negatif lewat transformasi)
   (kalau semua elemen ≥ 0 dan tanpa batasan, jawabannya seluruh array — soalnya
   pasti bukan itu, berarti ada batasan lain → sliding window)

## B.2 Pohon keputusan

```
Butuh subarray BERURUTAN?
├─ tidak → bukan Kadane (sorting / DP subsequence / greedy)
└─ ya
   └─ Yang dicari MAX/MIN jumlah?
      ├─ tidak (menghitung banyaknya) → prefix sum + hash map
      └─ ya
         └─ Ada batasan PANJANG?
            ├─ panjang tepat k        → sliding window ukuran tetap   (Day 33)
            ├─ panjang ≤ k            → prefix + monotonic deque      (Day 37)
            ├─ panjang ≥ k            → prefix + prefix-min tertunda
            └─ bebas
               └─ Ada elemen negatif?
                  ├─ tidak → jawabannya seluruh array (cek ulang soalnya!)
                  └─ ya    → ✅ KADANE
```

## B.3 Kalimat penyamaran yang sering dipakai

Soal jarang menulis "gunakan Kadane". Yang muncul biasanya:

| Kalimat di soal | Yang sebenarnya diminta |
|---|---|
| "periode terbaik untuk membeli dan menjual" | Kadane pada array selisih |
| "keuntungan bersih maksimum dari sederet transaksi berurutan" | Kadane langsung |
| "hari-hari berurutan dengan total suhu tertinggi" | Kadane langsung |
| "boleh melewatkan **satu** hari buruk" | Kadane + 1 state (`dp0`/`dp1`) |
| "arraynya melingkar / stadion berbentuk lingkaran" | Kadane max & min + penjaga |
| "persegi panjang di dalam grid dengan total maksimum" | kunci pasangan baris + Kadane |
| "sinyal terkuat pada rentang waktu" | Kadane |
| "ubah paling banyak satu elemen jadi 0" | Kadane + state |

## B.4 Yang **terlihat** seperti Kadane tapi bukan

Latih pengenalan jebakan ini — nilainya sama besar dengan mengenali yang benar:

| Soal | Kenapa bukan Kadane | Yang benar |
|---|---|---|
| Subarray terpanjang dengan sum = k | mencari panjang, bukan max sum | prefix + `map` |
| Banyaknya subarray dengan sum habis dibagi m | menghitung | prefix mod + counting |
| Subarray max dengan panjang ≤ k | Kadane tak bisa membatasi panjang | prefix + deque |
| Semua elemen positif, cari window terpendek dengan sum ≥ s | tidak ada negatif | two pointers |
| Max sum **subsequence** (boleh loncat) | tidak berurutan | jumlahkan semua yang positif |
| Max sum dari **dua** subarray terpisah | butuh dua segmen | Kadane prefix + suffix |
| Max **rata-rata** subarray panjang ≥ k | rata-rata bukan jumlah | binary search on answer + Kadane |

> Baris terakhir itu manis: setelah kamu tebak rata-ratanya `x`, kurangi semua
> elemen dengan `x`, lalu pertanyaannya berubah jadi "adakah subarray panjang ≥ k
> dengan sum ≥ 0" — Kadane lagi. Ini contoh Kadane sebagai **komponen**, bukan
> sebagai jawaban akhir. Nanti ketemu lagi di Day 50.

---

# BAGIAN C — Variasi, Diturunkan Bukan Dihafal

Resepnya selalu sama: **tanya "apa yang berubah dari dp[i]?"**

## C.1 Peta variasi

| Varian | Yang berubah | Inti |
|---|---|---|
| Boleh kosong | nilai awal `best` | `best = 0`, `cur = max(0, cur+x)` |
| Minimum subarray | arah | negasikan array, jalankan Kadane, negasikan hasil |
| Melingkar | ruang jawaban terbelah dua | `max(kadaneMax, total − kadaneMin)` + penjaga |
| Hasil kali | sifat aditif hilang | lacak `mx` **dan** `mn` |
| Boleh hapus ≤ 1 elemen | tambah 1 state | `dp1[i] = max(dp1[i-1]+a[i], dp0[i-1])` |
| Submatriks 2D | reduksi ke 1D | kunci pasangan baris, kompres jadi array kolom |
| Beserta indeks | butuh jejak | catat `curL` **hanya saat reset** |

## C.2 Melingkar — turunkan sendiri

Setiap subarray melingkar cuma punya dua bentuk. Tidak ada bentuk ketiga:

- **tidak membungkus** → subarray biasa → `kadaneMax`
- **membungkus** → bagian yang **tidak** terpakai adalah satu subarray biasa
  di tengah → jumlahnya `total − (subarray tengah)`. Untuk memaksimalkan ini,
  **minimalkan** yang di tengah → `total − kadaneMin`

Jawaban = `max` dari keduanya.

**Penjaga:** kalau semua elemen negatif, `kadaneMin` mengambil seluruh array,
sehingga `total − kadaneMin = 0` — itu subarray kosong, yang tidak diizinkan.
Deteksinya: `if (kadaneMax < 0) return kadaneMax;` (atau cek `kadaneMin == total`).

## C.3 Hapus paling banyak satu elemen — turunkan sendiri

Tambahkan satu bit ke state: *sudah pakai jatah hapus atau belum?*

```
dp0[i] = max(dp0[i-1] + a[i], a[i])      // belum pakai jatah = Kadane biasa
dp1[i] = max(dp1[i-1] + a[i],            // sudah pernah hapus, sekarang ambil a[i]
             dp0[i-1])                    // hapus a[i] sekarang
jawaban = max over i of max(dp0[i], dp1[i])
```

Pola "Kadane + state" ini terus berulang. Begitu kamu lihat kata **"boleh /
paling banyak satu kali"**, refleksmu harusnya: tambah dimensi kecil ke dp.

## C.4 Hasil kali — kenapa butuh dua variabel

Pada penjumlahan, nilai kecil selamanya kecil. Pada perkalian, **negatif besar
adalah aset** — kalikan dengan satu negatif lagi dan ia jadi positif terbesar.
Jadi minimum harus ikut dijaga:

```
kandidat = { x , mx * x , mn * x }
mxBaru = max(kandidat)
mnBaru = min(kandidat)
```

Hitung keduanya dari nilai **lama** (pakai variabel sementara — ini bug paling
sering: menimpa `mx` lalu memakainya untuk menghitung `mn`).

## C.5 Submatriks 2D — kenapa O(R²C) dan bukan sihir

Setiap submatriks ditentukan oleh (baris atas, baris bawah, kolom kiri, kolom kanan).
Kunci **pasangan barisnya** — ada O(R²) pasangan. Untuk setiap pasangan, jumlahkan
tiap kolom di antara kedua baris itu menjadi satu array 1D sepanjang C. Sekarang
"pilih kolom kiri & kanan terbaik" **persis** masalah Kadane 1D.

Pakai prefix sum kolom supaya kompresi tiap pasangan baris jadi O(C), bukan O(RC).
Total: O(R²C).

---

## 📌 Kartu Ingatan

```
INVARIANT   cur  = max sum subarray yang BERAKHIR di i
            best = jawaban untuk prefix a[0..i]

BENTUK      dp[i] = a[i] + max(0, dp[i-1])
            → a[i] selalu ikut; yang dipilih cuma "bawa masa lalu, atau nol"

PRAKTIS     tanya "boleh kosong?" SEBELUM menulis baris pertama
            pakai long long kalau n·|a| > 2·10^9
            reset cur → di situlah curL diperbarui, dan hanya di situ

SINYAL      berurutan + max/min sum + ada negatif + panjang bebas = Kadane
BUKAN       menghitung banyaknya · subsequence · ada batasan panjang
```
