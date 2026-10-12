# Soal interaktif

[← README](README.md) · [Indeks CP](../README.md)

Juri membaca tebakanmu **sekarang**. Tanpa flush, ia menunggu, kamu juga menunggu. Soal interaktif hampir selalu binary search dengan anggaran pertanyaan terbatas.

Day terkait: **052**. Di mesin nyata kamu berbicara lewat `stdout`/`stdin`. Di file ini juri palsu hidup di proses yang sama supaya jejak angka bisa diulang.

## Daftar isi

- [Flush dan buffer](#flush-dan-buffer)
- [Anggaran pertanyaan](#anggaran-pertanyaan)
- [Tebak bilangan](#tebak-bilangan)
- [Predikat lebih besar atau sama](#predikat-lebih-besar-atau-sama)
- [Juri palsu untuk tes lokal](#juri-palsu-untuk-tes-lokal)
- [Protokol dua fase](#protokol-dua-fase)
- [Debug tanpa merusak saluran](#debug-tanpa-merusak-saluran)
- [Peta keputusan](#peta-keputusan)

---

## Flush dan buffer

**Teori:** Analoginya telepon: kalau kamu bicara tanpa menekan “kirim”, lawan tidak mendengar. `endl` = newline plus flush. `cout << x << '\n' << flush` sama. Fast I/O plus `cin.tie(NULL)` **memutus** flush otomatis sebelum baca. Di soal biasa itu cepat. Di interaktif itu deadlock. Alasan benar: juri adalah proses lain; ia tidak melihat buffer milikmu sampai kamu mengosongkannya.

**Kapan:** setiap soal bertanda *interactive*. Jangan menumpuk 100 query lalu flush sekali jika protokol minta sebaris-sebalik. Jangan memakai `cerr` sebagai saluran juri.

**Proses:** urutan yang benar untuk satu tanya-jawab.

1. Tulis `? 5` ke `cout`.
2. Flush.
3. Baca respon `cin >> s`.
4. Tanpa langkah 2, juri tidak pernah melihat `? 5`, jadi tidak menulis respon, jadi `cin` menunggu selamanya.
5. Setelah jawaban akhir, biasanya `! 6` plus flush, lalu program boleh berhenti.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void tanyaNyata(ll x) {
    cout << "? " << x << endl; // endl = '\n' + flush
}

void jawabNyata(ll x) {
    cout << "! " << x << endl;
}

int main() {
    // INTERAKTIF: jangan FASTIO mentah tanpa flush manual.
    // ios_base::sync_with_stdio(false); boleh.
    // cin.tie(NULL) hanya aman jika setiap cetak diakhiri endl/flush.
    cout << "contoh flush\n" << flush;
    return 0;
}
```

Di kontes, ganti fungsi di atas sebagai satu-satunya pintu bicara ke juri.

**Jebakan:**
1. `'\n'` tanpa flush.
2. `FASTIO` lengkap lalu baca respon yang belum terkirim.
3. `printf` campur `cout` tanpa `tie` yang kamu pahami.
4. Flush ke `cerr` mengira juri membacanya.

**Kompleksitas:** flush `O(1)` per query. Biaya yang mahal adalah jumlah query, bukan flush.

---

## Anggaran pertanyaan

**Teori:** Soal interaktif memberi kuota, misalnya 30 atau 60 tanya. Linear search `1, 2, 3, …` habis kuota. Binary search memakai sekitar `log2(rentang)` tanya. Analoginya 20 pertanyaan: tiap jawaban ya/tidak membagi dua dunia. `2^20 ≈ 1e6`, `2^30 ≈ 1e9`, `2^60` jauh lebih dari rentang `ll` positif.

**Kapan:** selalu hitung kuota sebelum coding. Jangan “coba linear dulu” pada rentang `1e9`. Jangan dua kali lipat query karena off-by-one memaksa kamu mengulang.

**Proses:** tebak angka di `[1, 1e9]`, respon `>` atau `<=`.

1. Ruang 1e9, `log2(1e9) ≈ 30`.
2. Kuota 30 pas-pasan. Off-by-one satu langkah bisa TLE/WA “too many queries”.
3. Kuota 40 longgar. Kuota 20 tidak cukup untuk 1e9.
4. Kalau tiap tanya membuang sepertiga (ternary interaktif), butuh lebih banyak tanya daripada binary.
5. Simpan sisa kuota di variabel jika soal memotong saat habis.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int butuhBit(ll n) {
    int k = 0;
    ll p = 1;
    while (p < n) {
        p *= 2;
        k++;
    }
    return k;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << butuhBit(1000000000LL) << '\n'; // 30
    cout << butuhBit(10) << '\n';           // 4, karena 8<10
    cout << butuhBit(1) << '\n';            // 0
    return 0;
}
```

Kalau kuota persis `ceil(log2(n))`, tulis loop `lo < hi` yang dijamin `<=` kuota, lalu satu cetak `!`.

**Jebakan:**
1. Menghitung `log2(hi)` padahal ruangnya `hi - lo + 1`.
2. Query tambahan untuk “memastikan” setelah `lo == hi`.
3. Ternary interaktif tanpa alasan, kuota lebih boros.

**Kompleksitas:** hitung kuota `O(log n)`.

---

## Tebak bilangan

**Teori:** Juri memegang `rahasia` di `[L, R]`. Kamu menanya `? mid`. Jika angka lebih besar dari `mid`, buang kiri. Jika tidak, buang kanan termasuk strategi `hi = mid`. Analoginya tebak halaman kamus. Alasan benar: invariant “rahasia ada di `[lo, hi]`” dipertahankan.

**Kapan:** pola paling sering. Jangan menanya `lo` lalu `lo+1` berurutan. Jangan mengubah `lo = mid` tanpa plus satu saat respon “lebih besar”.

**Proses:** juri memegang `6` di `[1, 10]`. Respon `>` artinya rahasia `> mid`, `<=` artinya `<= mid`.

1. `lo = 1`, `hi = 10`, `mid = 5`. `6 > 5` → `lo = 6`.
2. `mid = 8`. `6 <= 8` → `hi = 8`.
3. `mid = 7`. `6 <= 7` → `hi = 7`.
4. `mid = 6`. `6 <= 6` → `hi = 6`.
5. `lo == hi == 6`. Cetak `! 6`.

Jejak kuota: 4 tanya, jauh di bawah `ceil(log2(10)) + cadangan`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

string juri(ll tebakan, ll rahasia) {
    if (rahasia <= tebakan) return "<=";
    return ">";
}

ll tebak(ll lo, ll hi, ll rahasia) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        // di soal nyata:
        // cout << "? " << mid << endl;
        // string res; cin >> res;
        string res = juri(mid, rahasia);
        if (res == ">") lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << tebak(1, 10, 6) << '\n' << flush; // 6
    cout << tebak(1, 10, 1) << '\n' << flush; // 1
    cout << tebak(1, 10, 10) << '\n' << flush; // 10
    return 0;
}
```

**Jebakan:**
1. `lo = mid` saat respon `>` → infinite.
2. Habis kuota karena linear.
3. Lupa cetak `!` sesuai format.
4. Membaca token ekstra yang tidak dikirim juri.

**Kompleksitas:** `O(log (hi-lo))` query, memori `O(1)`.

---

## Predikat lebih besar atau sama

**Teori:** Beberapa juri menjawab `YES` jika `x >= rahasia`, `NO` jika tidak. Itu lower bound pada domain integer. Analoginya: “apakah thermostat ini sudah cukup panas?” First `YES` adalah rahasia. Alasan benar: predikat monoton, jadi binary search on answer jalan.

**Kapan:** soal “minimum nilai yang diterima juri”. Jangan menafsirkan `YES` sebagai “tepat sama”.

**Proses:** rahasia `6`, tanya “apakah `mid >= 6`?”. Tunggu: jika juri menguji tebakan terhadap rahasia, rumuskan ulang.

Misal juri: `YES` jika rahasia `<= mid` (tebakan sudah menutup rahasia).

1. `mid = 5` → `6 <= 5`? `NO` → `lo = 6`.
2. `mid = 8` → `YES` → `hi = 8`.
3. Sama seperti seksi sebelumnya.
4. First `YES` = `6`.
5. Kalau kamu membalik `YES`/`NO` di kepala, `lo`/`hi` terbalik dan WA.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

bool juriYes(ll mid, ll rahasia) {
    return rahasia <= mid;
}

ll firstYes(ll lo, ll hi, ll rahasia) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        if (juriYes(mid, rahasia)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << firstYes(1, 100, 6) << '\n';  // 6
    cout << firstYes(1, 100, 100) << '\n'; // 100
    cout << firstYes(1, 100, 1) << '\n';   // 1
    return 0;
}
```

**Jebakan:**
1. Menukar cabang `YES` dan `NO`.
2. `mid` condong kanan padahal mencari first yes.
3. Domain `0` atau negatif tidak dimasukkan ke `lo`.

**Kompleksitas:** `O(log (hi-lo))` query.

---

## Juri palsu untuk tes lokal

**Teori:** Mengetes interaktif di mesin nyata tanpa juri itu menyakitkan. Tulis fungsi `tanya` yang bisa diganti: lokal memanggil oracle, kontes memanggil `cout`/`cin`. Analoginya boneka peraga sebelum telepon sungguhan. Alasan benar: logika `lo`/`hi` terpisah dari saluran I/O, jadi bug off-by-one ketahuan tanpa deadlock.

**Kapan:** selalu sebelum submit. Jangan mengirim oracle ke judge. Jangan memakai angka rahasia yang selalu di tengah.

**Proses:** uji tiga rahasia ujung dan tengah.

1. Rahasia `L`: setiap `mid < L` harus `>`, `mid >= L` harus `<=`.
2. Rahasia `R`: hampir semua tanya `<=` sampai ruang menempel `R`.
3. Rahasia acak 100 kali, oracle dan `tebak` harus sama.
4. Hitung jumlah tanya; gagal jika melebihi kuota.
5. Baru ganti tubuh `tanya` ke I/O nyata.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int kuotaPakai = 0;

string tanyaLokal(ll mid, ll rahasia) {
    kuotaPakai++;
    if (rahasia <= mid) return "<=";
    return ">";
}

ll tebakHitung(ll lo, ll hi, ll rahasia) {
    kuotaPakai = 0;
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        string res = tanyaLokal(mid, rahasia);
        if (res == ">") lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    mt19937 rng(1);
    for (int i = 0; i < 20; i++) {
        ll rahasia = 1 + (rng() % 1000);
        ll ans = tebakHitung(1, 1000, rahasia);
        if (ans != rahasia || kuotaPakai > 20) {
            cout << "gagal\n";
            return 0;
        }
    }
    cout << "lolos\n";
    return 0;
}
```

**Jebakan:**
1. Oracle memakai `<` padahal protokol `<=`.
2. Tidak mereset `kuotaPakai`.
3. Tes hanya satu rahasia, yaitu contoh soal.

**Kompleksitas:** 20 tes kali `O(log R)`.

---

## Protokol dua fase

**Teori:** Banyak soal: fase tanya `?`, lalu tepat satu jawaban `!`. Beberapa soal lebih rumit: kamu boleh `?` pada pasangan, atau juri memotong dengan `0` jika query ilegal. Analoginya ujian lisan: pertanyaan bebas, kesimpulan sekali. Alasan benar: format salah = WA meski angka benar.

**Kapan:** baca statement tiga kali khusus baris protokol. Jangan meniru file kemarin. Jangan mencetak spasi ekstra jika juri token-sensitive.

**Proses:** tebak indeks maksimum di array tersembunyi `a = [2, 5, 4]`, query `? i j` membandingkan `a[i]` dan `a[j]`.

1. `lo = 0`, `hi = 2`.
2. Banding `0` dan `1`: `2 < 5`, kandidat max di `[1, 2]`.
3. Banding `1` dan `2`: `5 > 4`, max indeks `1`.
4. Cetak `! 1`.
5. Jumlah banding `n-1` linear juga benar, tetapi kuota ketat memaksa turnamen / binary.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

int bandingLokal(const vector<ll>& a, int i, int j) {
    if (a[i] < a[j]) return -1;
    if (a[i] > a[j]) return 1;
    return 0;
}

int indeksMax(const vector<ll>& a) {
    int best = 0;
    for (int i = 1; i < (int)a.size(); i++) {
        if (bandingLokal(a, best, i) < 0) best = i;
    }
    return best;
}

int main() {
    ios_base::sync_with_stdio(false);
    vector<ll> a = {2, 5, 4};
    cout << indeksMax(a) << '\n'; // 1
    vector<ll> b = {9, 1, 9};
    cout << indeksMax(b) << '\n'; // 0, yang kiri jika sama
    return 0;
}
```

Di soal nyata, ganti `bandingLokal` dengan cetak `? i j`, flush, baca `<`, `>`, atau `=`.

**Jebakan:**
1. Indeks 1-based di protokol, 0-based di kepala.
2. Mencetak `!` sebelum kuota tanya selesai padahal juri masih menunggu query.
3. Membandingkan nilai yang belum pernah ditanya, seolah array terlihat.

**Kompleksitas:** turnamen `O(n)` query. Binary pada nilai, bukan indeks, `O(log A)`.

---

## Debug tanpa merusak saluran

**Teori:** `cerr` tidak dibaca juri. Analoginya catatan di kertas sendiri, bukan ucapan ke penguji. Alasan benar: saluran `stdout` harus murni protokol. Beberapa judge menampilkan `stderr` di verdict; itu aman untuk debug, bukan untuk jawaban.

**Kapan:** interaktif yang WA “idleness limit” atau “wrong format”. Jangan mengirim `cerr` masif sampai melebihi batas keluaran error.

**Proses:** satu sesi gagal.

1. Idleness: biasanya lupa flush.
2. WA cepat: format `?` salah, atau `lo`/`hi` keluar rentang yang diizinkan.
3. Too many queries: off-by-one atau linear.
4. Cetak ke `cerr` nilai `lo`, `hi`, `mid`, respon.
5. Setelah ketemu bug, hapus atau bungkus `#ifdef`.

**Kode:**

```cpp
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

void logRuang(ll lo, ll hi, ll mid, const string& res) {
    cerr << "lo=" << lo << " hi=" << hi
         << " mid=" << mid << " res=" << res << '\n';
}

ll tebakLog(ll lo, ll hi, ll rahasia) {
    while (lo < hi) {
        ll mid = lo + (hi - lo) / 2;
        string res = (rahasia <= mid) ? "<=" : ">";
        logRuang(lo, hi, mid, res);
        if (res == ">") lo = mid + 1;
        else hi = mid;
    }
    return lo;
}

int main() {
    ios_base::sync_with_stdio(false);
    cout << tebakLog(1, 10, 6) << '\n';
    return 0;
}
```

`cout` hanya jawaban akhir. Jejak langkah ada di `cerr`.

**Jebakan:**
1. `clog`/`cout` tertukar.
2. Log ke `stdout` merusak parser juri.
3. Membaca `stderr` sebagai respon.

**Kompleksitas:** `O(log n)` baris log.

---

## Peta keputusan

```text
Soal interactive?
  → flush setiap query, jaga kuota

Respon monoton YES/NO atau </>?
  → binary search, file ini + binary-search.md

Respon unimodal (lebih dekat / lebih jauh)?
  → hati-hati, sering binary pada selisih, bukan tebak linear

Perlu tes lokal?
  → oracle + hitung kuota

Idleness limit exceeded?
  → flush, bukan algoritma
```

| gejala judge | kemungkinan |
| --- | --- |
| idleness | tidak flush / deadlock |
| too many queries | linear atau off-by-one |
| wrong format | spasi, `?`/`!`, 1-based |
| WA angka | cabang `>` vs `>=` |

Di soal nyata: `cout << "? " << mid << endl;` lalu `cin >> res;`, akhiri `cout << "! " << ans << endl;`.

Kembali ke [binary-search.md](binary-search.md) untuk predikat, atau [ternary.md](ternary.md) jika juri memberi nilai fungsi, bukan ya/tidak.
