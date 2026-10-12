# 22 — DP probabilitas & ekspektasi (Day 163)

[← Reroot](21-reroot.md) · [README](README.md) · [Bitset →](23-bitset.md)

> **Satu kalimat:** ekspektasi linear — pecah jadi jumlah indikator atau tulis `E[s] = 1 + rata-rata E[lanjutan]` pada DAG.

Day ComprogLearning: **163**. Bukan teori peluang kuliah lengkap. Hanya pola yang muncul di soal CP.

Tiga pertanyaan:

```
1. STATE     : E[s] atau P[s] = ekspektasi / peluang dari keadaan s sampai selesai
2. TRANSISI  : rata-rata berbobot atas langkah acak, atau jumlah indikator
3. BASIS     : terminal E=0 atau P=1/0; hati-hati siklus
```

## Daftar isi

- [Teori](#teori)
- [Kapan](#kapan)
- [Linearitas](#linearitas)
- [Ekspektasi pada DAG](#ekspektasi-pada-dag)
- [Koin dan dadu](#koin-dan-dadu)
- [Geometric](#geometric)
- [Random walk di pohon / garis](#random-walk-di-pohon--garis)
- [Sistem linear jika ada siklus](#sistem-linear-jika-ada-siklus)
- [Kode modular](#kode-modular)
- [Jebakan](#jebakan)
- [Kompleksitas](#kompleksitas)
- [Tabel uji](#tabel-uji)
- [Checklist](#checklist)

---

## Teori

**Teori:** Peluang dan ekspektasi mematuhi rumus total:

```
P(A) = Σ P(A | cabang) P(cabang)
E[X] = Σ E[X | cabang] P(cabang)
```

Kalau cabang adalah langkah DP, itu transisi biasa — operatornya rata-rata, bukan `max`.

**Linearitas ekspektasi:** untuk apa pun `X = X_1 + ... + X_n` (boleh dependen!),

```
E[X] = E[X_1] + ... + E[X_n]
```

Ini senjata paling kuat. Banyak soal "ekspektasi jumlah" pecah jadi `n` soal "peluang peristiwa i terjadi".

Analoginya: gaji rata-rata tim = jumlah rata-rata per orang, meski orang saling meniru.

DP dipakai jika state kecil dan langkah acak **ke state yang "lebih selesai"** (DAG). Jika bisa balik, dapat sistem persamaan, bukan DP biasa.

---

## Kapan

**Kapan dipakai.**

| Gejala | Alat |
|---|---|
| "ekspektasi jumlah / langkah" | linearitas atau `E[s]` |
| dadu / koin sampai kondisi | geometric + DP |
| peluang mencapai terminal | `P[s]` |
| langkah acak tanpa siklus | DP topo |
| langkah acak ada siklus | Gaussian / substitusi |

**Kapan tidak.**

1. Perlu distribusi lengkap `P(X = k)` untuk `k` besar — state meledak.
2. Variansi diminta dan kamu hanya punya `E` — linearitas **tidak** berlaku untuk `Var` tanpa kovarians.
3. "Peluang max" — max tidak linear. Itu bukan `E[max] = max E`.

---

## Linearitas

**STATE:** tidak wajib tabel. `X_i = 1` jika peristiwa i terjadi.

**TRANSISI:** `E[X] = Σ P(X_i = 1)`.

**BASIS:** `P` dihitung dengan kombinatorial atau DP terpisah.

**Proses: lempar koin adil n kali, ekspektasi jumlah muka.**

```
X_i = 1 jika lemparan i muka
E[X_i] = 1/2
E[jumlah] = n/2
```

Tidak peduli dependen. Urutan tidak penting.

**Proses: ekspektasi jumlah inversi array acak permutasi.**

```
X_ij = 1 jika i < j tetapi a[i] > a[j]
P = 1/2 untuk i ≠ j
E = C(n,2) / 2
```

**Proses: n lampu, tiap subset sama mungkin, ekspektasi banyak lampu nyala.**

Sama `n/2`. Jangan enumerasi `2^n`.

**Kapan linearitas kalah:** soal minta `E[X^2]` atau `E[max]`. Pecah `(Σ X_i)^2 = Σ X_i^2 + 2 Σ_{i<j} X_i X_j`, lalu `E[X_i X_j] = P(keduanya)`. Itu masih linearitas, tapi pada pasangan.

---

## Ekspektasi pada DAG

**Teori:** state permainan / proses, dari `s` kamu pilih (atau diundi) langkah ke `t`. Biaya 1 per langkah.

```
E[s] = 0                         jika s terminal
E[s] = 1 + Σ P(s→t) E[t]        jika tidak
```

**STATE:** `E[s]` = ekspektasi biaya dari `s` sampai terminal.

**TRANSISI:** rata-rata anak di DAG.

**BASIS:** terminal 0.

**Proses: dadu 6 muka, ingin jumlah ≥ 1 sudah selesai? Terlalu sepele.**

Lebih baik: katak di tangga, dari `i` lempar 1..k, ingin ke `n`.

```
E[n] = 0
E[i] = 1 + (E[i+1] + ... + E[min(n, i+k)]) / k
       hati-hati: jika i+j > n, beberapa soal "diam", beberapa "tepat".
```

Isi dari `i = n-1` turun ke 0.

**Kapan:** setiap transisi menambah "progress" (posisi naik, mask bit nambah, sisa item berkurang).

---

## Koin dan dadu

**Teori:** peluang `p` sukses, proses Bernoulli.

Ingin **tepat** `k` sukses dari `n` lemparan: `C(n,k) p^k (1-p)^{n-k}`. Bukan DP kecuali `p` berubah per state.

Ingin **ekspektasi lemparan sampai sukses pertama:** `1/p`. Geometric.

Ingin **ekspektasi sampai k sukses:** `k/p` (jumlah k geometric).

DP muncul jika sukses mengubah state (misalnya terkumpul mask, atau posisi).

**STATE contoh:** `E[mask]` = ekspektasi lemparan sampai semua bit nyala, tiap lemparan menambah item seragam dari `n` jenis (coupon collector).

```
E[(1<<n)-1] = 0
E[mask] = 1 + (Σ_i E[mask | (1<<i)]) / n
```

Ada suku `E[mask]` di kanan jika item duplikat. Pindahkan:

```
E[mask] = 1 + ((n-baru)/n) E[mask] + (baru/n) * rata-rata E[mask+item]
(baru/n) E[mask] = 1 + (baru/n) * ...
E[mask] = n/baru + rata-rata E[baru]
```

Itu rumus collector: dari `k` terkumpul, `E = n/(n-k) + ...`. Total `n H_n`.

**Proses angka:** `n = 2` kupon.

```
E[11]=0
E[01] = 2/1 + E[11] = 2
E[10] = 2
E[00] = 2/2 + (E[01]+E[10])/2 = 1+2 = 3
```

`2 (1 + 1/2) = 3`. Cocok.

---

## Geometric

Kalau tiap percobaan peluang `p` selesai, bebas state:

```
E = (1-p)(1+E) + p(1+0)  →  E = 1/p
```

Di CP, `p` sering `cnt_baik / total`, tergantung state. Sama seperti collector.

**Jebakan:** `p = 0` terperangkap. Soal harus menjamin selesai atau kamu deteksi.

---

## Random walk di pohon / garis

**Garis 0..n**, start `i`, ujung 0 dan n absorbing. Langkah kiri/kanan 1/2. Ekspektasi langkah sampai ujung.

```
E[0]=E[n]=0
E[i] = 1 + (E[i-1]+E[i+1])/2
→ E[i-1] - 2E[i] + E[i+1] = -2
```

Solusi klasik `E[i] = i (n-i)`.

**Proses:** `n=2`, tengah `i=1`: `E=1`. Ya, satu langkah pasti selesai.

`n=3`, `i=1`: `1*2=2`. Dari 1: 50% selesai ke 0 (1 langkah), 50% ke 2 lalu simetris...

Ini **bukan** DP DAG (ada siklus 1↔2). Kita memakai rumus tertutup atau Gaussian kecil.

Di pohon, ekspektasi kembali ke akar lebih rumit (2*(n-1) untuk cover? itu cover time, bukan file ini). Untuk soal CP, biasanya DAG atau rumus `i(n-i)`.

---

## Sistem linear jika ada siklus

**STATE:** satu variabel per state.

**TRANSISI:** persamaan `E_s - Σ P_st E_t = 1`.

**BASIS:** terminal 0.

Selesaikan Gaussian `O(k^3)` untuk `k` state. `k ≤ 300` aman, `k = 2000` tidak.

Kadang substitusi: state pada garis berantai, eliminasi O(n).

Jangan memo DFS naif pada graf berarah bersiklus: infinite recursion.

---

## Kode modular

```cpp
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

double expectedDiceToN(int n, int k) {
    vector<double> E(n + 1, 0.0);
    for (int i = n - 1; i >= 0; i--) {
        double s = 0;
        for (int d = 1; d <= k; d++) {
            int nxt = i + d;
            if (nxt > n) nxt = n; // versi "kelebihan menempel di n"
            s += E[nxt];
        }
        E[i] = 1.0 + s / k;
    }
    return E[0];
}

double couponCollector(int n) {
    if (n == 0) return 0;
    int N = 1 << n;
    vector<double> E(N, 0.0);
    for (int mask = N - 2; mask >= 0; mask--) {
        double sumNew = 0;
        int baru = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            baru++;
            sumNew += E[mask | (1 << i)];
        }
        E[mask] = (n + sumNew) / baru;
    }
    return E[0];
}

double expectedHeads(int n) { return n * 0.5; }

double expectedInversions(int n) {
    return n * (n - 1) / 4.0;
}

// peluang mencapai n tepat dengan langkah 1..k, start 0, overshoot gagal di versi ini
double probReachExact(int n, int k) {
    vector<double> P(n + 1, 0.0);
    P[0] = 1.0;
    for (int i = 0; i < n; i++) {
        if (P[i] == 0) continue;
        for (int d = 1; d <= k; d++) {
            if (i + d <= n) P[i + d] += P[i] / k;
        }
    }
    return P[n];
}

// E[i] = i*(n-i) pada garis absorbing
ll expectedLineClosed(int i, int n) {
    return 1LL * i * (n - i);
}

int main() {
    FASTIO;
    cout << fixed << setprecision(6);
    cout << couponCollector(2) << "\n";          // 3
    cout << expectedHeads(10) << "\n";           // 5
    cout << expectedInversions(3) << "\n";       // 1.5
    cout << expectedLineClosed(1, 2) << "\n";    // 1
    cout << expectedDiceToN(1, 6) << "\n";       // 1
    return 0;
}
```

Modular aritmetika (jawaban `p/q mod 1e9+7`):

```cpp
const ll MOD = 1000000007LL;

ll modpow(ll a, ll e) {
    ll r = 1;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

ll inv(ll a) { return modpow(a, MOD - 2); }

// E[mask] coupon dalam modular
ll couponMod(int n) {
    int N = 1 << n;
    vector<ll> E(N, 0);
    for (int mask = N - 2; mask >= 0; mask--) {
        ll sumNew = 0;
        int baru = 0;
        for (int i = 0; i < n; i++) {
            if (mask >> i & 1) continue;
            baru++;
            sumNew += E[mask | (1 << i)];
            if (sumNew >= MOD) sumNew -= MOD;
        }
        E[mask] = (n + sumNew) % MOD * inv(baru) % MOD;
    }
    return E[0];
}
```

Isi mask dari banyak bit ke sedikit, sama seperti "lebih dekat ke penuh".

---

## Jebakan

1. **`E[max] = max E`.** Salah. Max tidak linear.

2. **DFS memo pada siklus.** TLE / RE / stack.

3. **Lupa pindahkan suku `E[s]` ke kiri** saat ada peluang stay. Pembagi `p_maju`, bukan 1.

4. **`double` vs modulo.** Baca soal. Relatif error `1e-6` → `double` cukup; "mod 1e9+7" → invers.

5. **Overshoot dadu.** Empat aturan berbeda: tembok, ulang, gagal, pantul. Simulasi `n=3, k=6` vs brute.

6. **Peluang 0.** Bagi `baru` saat `baru=0` — hanya mask penuh, sudah basis.

7. **`float` 32-bit.** Pakai `double`.

8. **Linearitas pada produk.** Ubah jadi `E[X_i X_j]`.

9. **Urutan isi `E[i]`.** Harus dari terminal mundur, atau Gauss.

10. **Mencampur `P` dan `E` di array yang sama tanpa komentar.**

---

## Kompleksitas

| Pola | Waktu |
|---|---|
| linearitas n indikator | `O(n)` atau `O(1)` rumus |
| DP tangga `n * k` | `O(n k)` |
| coupon `2^n * n` | `n ≤ 20` |
| Gaussian `k` state | `O(k^3)` |
| garis rumus tertutup | `O(1)` |

Memori: satu array state. `double` 8 byte.

---

## Tabel uji

| Soal | Input | Jawaban |
|---|---|---|
| E muka n koin | n=10 | 5 |
| E inversi | n=3 | 1.5 |
| collector n=1 | — | 1 |
| collector n=2 | — | 3 |
| collector n=3 | — | 3*(1+1/2+1/3)=5.5 |
| garis E[1] n=2 | — | 1 |
| garis E[1] n=3 | — | 2 |
| dadu ke 1, k=6 | — | 1 |

Brute collector n=2: simulasi 1e6 run, rata-rata ≈ 3.

---

## Checklist

1. Apakah `X` jumlah indikator? Kalau ya, jangan DP besar.
2. Apakah transisi DAG? Isi mundur.
3. Ada stay? Pindahkan suku.
4. `double` atau `modinv`.
5. Terminal 0 untuk biaya, 1/0 untuk peluang.
6. Uji collector n=2 → 3.
7. Baca aturan overshoot.

---

## Peluang vs ekspektasi: dua template

**Peluang mencapai baik, langkah tanpa biaya:**

```
P[terminal baik] = 1
P[terminal buruk] = 0
P[s] = Σ P(s→t) P[t]
```

**Ekspektasi nilai hadiah di akhir** (bukan langkah):

```
E[s] = Σ P(s→t) E[t]     // tanpa +1
```

**Ekspektasi jumlah hadiah di setiap kunjungan:**

```
E[s] = reward[s] + Σ P(s→t) E[t]
```

Jangan menempel `+1` jika soal bukan "berapa langkah".

---

## Contoh campur: dadu + sisa hidup

State `(hp, posisi)` kecil. Tiap langkah: damage acak, maju 1. `E[hp][pos]`.

Kalau `hp ≤ 20` dan `pos ≤ 100`, state 2000. Transisi 6. Hidup.

Kalau `hp ≤ 1e9`, pecah: linearitas "peluang masih hidup saat langkah i" atau rumus tertutup.

---

## Proses: pindahkan suku stay

Dari `s`, 30% stay, 70% ke `t`. Biaya 1 per langkah. `E[t]=4`.

Salah: `E[s] = 1 + 0.3 E[s] + 0.7*4` lalu **lupa pindah** dan mengisi `E[s]=1+0.3*???`.

Benar:

```
E = 1 + 0.3 E + 2.8
0.7 E = 3.8
E = 3.8 / 0.7 ≈ 5.428
```

Rumus umum: `E[s] = (1 + Σ_{t≠s} P_st E[t]) / (1 - P_ss)`.

Uji collector: dari 0 kupon, `n=2`, `P_stay=0`? Dari kosong, setiap kupon baru, `baru=2`, `P_stay=0`, `E= (2 + E[01]+E[10])/2 = 3`. Dari 1 kupon, `P_stay=1/2`:

```
E = 1 + 0.5 E + 0.5 * 0
0.5 E = 1 → E = 2 = n/baru
```

---

## Ekspektasi panjang LCS? Jangan

`E[LCS(dua string acak)]` bukan DP kecil. Linearitas pada "apakah LCS ≥ k" sulit. Kalau soal tidak memberi state kecil, hentikan.

Sebaliknya: `E[jumlah posisi a[i]==b[i]]` pada dua permutasi independen = `n * 1/n = 1`. Itu linearitas, 2 baris.

---

## Double vs pecahan

`couponCollector(3)` harus `5.5` tepat di `double` (penyebut 2). `n=4`: `4(1+1/2+1/3+1/4)=8.333...`. Kalau soal minta modulo, jangan `ll(round(E*den))` — pakai invers dari awal.

---

## Ringkasan dinding

```
E[X+Y] = E[X]+E[Y]   selalu
E[s] = 1 + rata-rata E[t]    pada DAG
stay: E = (1 + rata maju) / p_maju
collector n=2 → 3
mod: kali invers
```
