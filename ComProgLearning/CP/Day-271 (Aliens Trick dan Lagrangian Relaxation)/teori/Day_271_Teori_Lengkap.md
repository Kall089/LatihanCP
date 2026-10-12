# Day 271 — Aliens Trick dan Lagrangian Relaxation

> **Ide satu kalimat:** Mengeliminasi dimensi batas kapasitas atau jumlah operasi $K$ pada DP dengan memperkenalkan biaya penalti Lagrangian $\lambda$ per operasi, lalu menggunakan Binary Search (WQS Binary Search) untuk menemukan $\lambda$ yang memaksa DP memilih tepat $K$ operasi dalam waktu $\mathcal{O}(N \log(\text{Range}))$.

---

## 1. Motivasi dan Masalah "Tepat $K$ Operasi"

Banyak masalah optimasi memiliki formulasi:
> *"Pilihlah tepat $K$ elemen / segmen / operasi sehingga biaya total terminimalkan (atau keuntungan termaksimalkan)."*

Contoh klasik:
- Membagi barisan panjang $N$ menjadi tepat $K$ kelompok.
- Memilih tepat $K$ interval yang tidak saling tumpang tindih.
- Melakukan tepat $K$ transaksi jual-beli saham (Stock IV).
- Menutupi titik-titik dengan tepat $K$ kamera/foto (IOI 2016 Aliens).

### Batasan DP Standar:
State DP biasanya berdimensi $(i, k)$:
- $i$: prefiks indeks elemen yang telah diproses ($1 \le i \le N$).
- $k$: jumlah operasi yang telah digunakan ($0 \le k \le K$).

Kompleksitas waktu: $\mathcal{O}(N \cdot K)$ atau $\mathcal{O}(N^2 \cdot K)$.
Jika $N, K \le 10^5$, pendekatan ini pasti **TLE** (*Time Limit Exceeded*).

---

## 2. Intuisi Geometris: Konveksitas Fungsi $f(k)$

Definisikan fungsi:
$$f(k) = \text{biaya minimum yang dibutuhkan dengan menggunakan TEPAT } k \text{ operasi}$$

Untuk banyak masalah, fungsi $f(k)$ memiliki sifat **konveks** (*convex*):
$$f(k+1) - f(k) \ge f(k) - f(k-1)$$

Artinya:
- Setiap penambahan satu operasi tambahan memberikan penurunan biaya yang semakin kecil (hukum *diminishing returns*).
- Jika digambarkan pada bidang koordinat Cartesius $(k, f(k))$, kurva titik-titik tersebut berbentuk mangkuk cembung (konveks ke bawah).

```text
Biaya f(k)
 ^
 |  * (k=1)
 |   \
 |    \   * (k=2)
 |     \_/
 |       \__* (k=3)
 |          \___* (k=4)
 |               \____* (k=5)
 +-----------------------------> k (jumlah operasi)
```

---

## 3. Lagrangian Relaxation (Penalti $\lambda$)

Bagaimana jika kita **MENGHAPUS** syarat "tepat $K$ operasi"?
Alih-alih membatasi jumlah operasi, kita tetapkan:
> **"Setiap kali Anda menggunakan 1 operasi, Anda harus membayar penalti sebesar $\lambda$."**

Dengan demikian, masalah baru tanpa batas $K$ adalah:
$$g(\lambda) = \min_{k} \{ f(k) + k \cdot \lambda \}$$

Perhatikan bahwa:
- Nilai $g(\lambda)$ dapat dihitung dengan DP 1-dimensi sederhana dalam waktu $\mathcal{O}(N)$ (atau $\mathcal{O}(N \log N)$ dengan CHT/Segment Tree) tanpa perlu melacak jumlah operasi pada state DP!
- State DP hanya menyimpan pasangan: `(biaya_terbaik, jumlah_operasi_yang_dipakai)`.

### Interpretasi Garis Singgung (*Tangent Line*):
Persamaan $g(\lambda) = \min_k \{ f(k) + k \cdot \lambda \}$ dapat ditulis ulang sebagai:
$$f(k) = -\lambda \cdot k + g(\lambda)$$

Ini adalah persamaan garis lurus dengan kemiringan (*slope*) $m = -\lambda$ dan perpotongan sumbu-y (*y-intercept*) $g(\lambda)$!
Mencari nilai minimum berarti kita menggeser garis dengan gradien $-\lambda$ dari bawah hingga **menyentuh kurva konveks $f(k)$ pertama kali**.
Titik singgungnya adalah $k^*$ yang menjadi solusi optimal untuk penalti $\lambda$ tersebut!

---

## 4. WQS Binary Search pada $\lambda$

Perhatikan hubungan monotonik antara $\lambda$ dan jumlah operasi optimal $k^*(\lambda)$:
- Jika penalti $\lambda$ sangat besar ($\lambda \to +\infty$), menggunakan operasi menjadi sangat mahal $\implies k^*$ bernilai kecil ($k^* \to 0$).
- Jika penalti $\lambda$ sangat kecil atau negatif ($\lambda \to -\infty$), menggunakan operasi menjadi sangat murah/menguntungkan $\implies k^*$ bernilai besar.

Karena $k^*(\lambda)$ bersifat **monoton menurun** terhadap $\lambda$, kita dapat menggunakan **Binary Search** untuk mencari nilai penalti $\lambda$ yang tepat sedemikian sehingga DP memilih tepat $K$ operasi!

### Prosedur Algoritma:
1. Tentukan rentang pencarian biner $[\lambda_{\min}, \lambda_{\max}]$.
2. Hitung $\lambda_{\text{mid}} = \lfloor (\lambda_{\min} + \lambda_{\max}) / 2 \rfloor$.
3. Jalankan DP tanpa batas $K$, di mana setiap transisi yang menambah operasi dikenakan penalti $+\lambda_{\text{mid}}$.
4. DP mengembalikan pasangan `(min_cost, cnt_ops)`:
   - Jika `cnt_ops < K`: penalti terlalu mahal! Geser ke kiri: $\lambda_{\max} = \lambda_{\text{mid}} - 1$.
   - Jika `cnt_ops >= K`: catat kandidat $\lambda$, coba perbesar penalti: $\lambda_{\min} = \lambda_{\text{mid}} + 1$.
5. Setelah konvergen ke penalti $\lambda^*$:
   $$\text{Jawaban Asli } f(K) = \text{min\_cost}(\lambda^*) - K \cdot \lambda^*$$

---

## 5. Penanganan Kasus Kolinier (*Collinear Points*) & Tie-Breaking

Salah satu jebakan terbesar dalam Aliens Trick adalah ketika kurva $f(k)$ memiliki titik-titik yang **segaris lurus** (*collinear*).
Misalkan untuk suatu gradien $-\lambda^*$, garis singgung menyentuh beberapa titik sekaligus, misalnya $k = 3, 4, 5$.

```text
f(k)
 ^
 |    *
 |     \
 |      *---*---* (k=3, 4, 5 segaris lurus!)
 |               \
 +-------------------------> k
```

Jika target kita adalah $K = 4$, binary search mungkin tidak pernah menemukan $\lambda$ yang secara unik menghasilkan `cnt_ops == 4`. Nilai `cnt_ops` bisa melonjak dari 3 ke 5!

### Solusi Tie-Breaking yang Benar:
1. Pada rekurensi DP, ketika dua transisi menghasilkan biaya yang **SAMA PERSIS**:
   - Terapkan aturan tie-breaking yang konsisten (misalnya: selalu pilih yang menggunakan jumlah operasi **MAKSIMUM**, atau selalu **MINIMUM**).
2. Jika aturan memilih operasi maksimum:
   - Pastikan kondisi berhenti binary search mencakup `cnt_ops >= K`.
   - Rumus akhir tetap: $f(K) = \text{DP\_cost}(\lambda^*) - K \cdot \lambda^*$.
   - Mengapa rumus ini tetap valid?
     Karena pada segmen kolinier, titik $(K, f(K))$ berada tepat di garis singgung yang sama! Pengurangan $K \cdot \lambda^*$ secara eksak mengembalikan nilai $f(K)$ yang benar.

---

## 6. Ringkasan Kompleksitas

| Pendekatan | Kompleksitas Waktu | Kompleksitas Memori |
|---|---|---|
| **DP Standar** | $\mathcal{O}(N \cdot K)$ | $\mathcal{O}(N \cdot K)$ |
| **Aliens Trick + DP Linier** | $\mathcal{O}(N \log(\text{Range})) \approx \mathcal{O}(60 \cdot N)$ | $\mathcal{O}(N)$ |
| **Aliens Trick + CHT / Li Chao** | $\mathcal{O}(N \log N \log(\text{Range}))$ | $\mathcal{O}(N)$ |

Peningkatan kecepatan dari $\mathcal{O}(N \cdot K)$ menjadi $\mathcal{O}(N \log(\text{Range}))$ memungkinkan solusi lolos dengan waktu eksekusi di bawah 0.2 detik untuk $N, K = 100.000$!
