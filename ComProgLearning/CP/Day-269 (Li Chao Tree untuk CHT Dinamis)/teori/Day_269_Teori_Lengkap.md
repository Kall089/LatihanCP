# Day 269 — Li Chao Tree untuk CHT Dinamis

> **Ide satu kalimat:** Li Chao Tree adalah variasi Segment Tree yang menyimpan garis-garis linear pada setiap simpulnya, memungkinkan penambahan garis berurutan acak dan kueri nilai minimum/maksimum pada koordinat acak dalam waktu $\mathcal{O}(\log N)$ tanpa memerlukan pengurutan kemiringan.

---

## 1. Motivasi: Batasan CHT Deque

Pada Day 268, kita mempelajari bahwa Convex Hull Trick dengan Deque membutuhkan:
1. Kemiringan garis $m$ harus terurut monoton.
2. Titik kueri $x$ harus terurut monoton.

Bagaimana jika data masukan tidak terurut?
- Ketinggian batu katak $h[i]$ berfluktuasi naik-turun.
- Garis baru ditambahkan secara dinamis dan kueri datang bergantian dengan koordinat acak.
- Suatu promo/garis hanya berlaku pada rentang interval tertentu $[L, R]$.

Untuk mengatasi skenario dinamis ini, **Li Chao Tree** hadir sebagai struktur data yang sangat elegan, mudah ditulis (*clean*), dan beroperasi dalam waktu $\mathcal{O}(\log N)$ per operasi!

---

## 2. Struktur & Invariant Li Chao Tree

Li Chao Tree dibangun di atas domain koordinat kueri $x \in [X_{\min}, X_{\max}]$ (atau indeks terkompresi $0 \dots K-1$).

### Invariant Utama Simpul:
Setiap simpul yang mewakili interval $[l, r]$ dengan titik tengah $mid = \lfloor \frac{l + r}{2} \rfloor$ **menyimpan garis terbaik pada koordinat $mid$**.

```
                Simpul [l, r]
            Menyimpan garis terbaik di x[mid]
                   /               \
          Anak Kiri [l, mid]    Anak Kanan [mid+1, r]
```

### Mekanisme Penambahan Garis (`add_line`):
Misalkan sebuah simpul saat ini menyimpan garis $L_{\text{old}}$, dan kita ingin memasukkan garis baru $L_{\text{new}}$:
1. Bandingkan nilai $L_{\text{new}}(mid)$ dengan $L_{\text{old}}(mid)$.
2. Jika $L_{\text{new}}$ lebih baik di $mid$, tukar keduanya (`swap(L_new, L_old)`). Sekarang $L_{\text{old}}$ memegang garis terbaik di $mid$.
3. Garis yang kalah sekarang hanya memiliki peluang mengalahkan garis pemenang di **salah satu belahan** (kiri ATAU kanan), karena dua garis lurus hanya dapat berpotongan di maksimal satu titik!
   - Jika garis yang kalah lebih baik di ujung kiri ($x_l$), maka titik potongnya berada di sebelah kiri $mid$. Turunkan garis yang kalah ke **anak kiri**.
   - Jika tidak, garis yang kalah hanya mungkin lebih baik di sebelah kanan $mid$. Turunkan garis yang kalah ke **anak kanan**.
4. Karena pada setiap langkah kita hanya menuruni **satu cabang anak**, kedalaman rekursi maksimal adalah tinggi pohon $\mathcal{O}(\log N)$!

---

## 3. Mekanisme Kueri Nilai Ekstrem (`query`)

Untuk mencari nilai minimum pada koordinat kueri $x$:
1. Mulai dari simpul akar.
2. Pada simpul saat ini, evaluasi nilai garis yang tersimpan di simpul tersebut: `ans = min(ans, line.eval(x))`.
3. Telusuri simpul anak yang memuat koordinat $x$ (ke kiri jika $x \le mid$, ke kanan jika $x > mid$).
4. Ulangi hingga mencapai simpul daun.
5. Jawaban akhir adalah nilai minimum di antara seluruh garis yang dijumpai di sepanjang jalur akar-ke-daun (*root-to-leaf path*).
6. Kompleksitas kueri: tepat $\mathcal{O}(\log N)$ operasi.

---

## 4. Penambahan Segmen Garis $[L, R]$

Jika suatu garis hanya berlaku pada rentang interval tertentu $[L, R]$ (bukan pada seluruh sumbu-$X$):
1. Pecah interval $[L, R]$ menjadi $\mathcal{O}(\log N)$ simpul kanonik pohon rentang (persis seperti pembaruan interval pada Segment Tree biasa).
2. Pada setiap simpul kanonik yang sepenuhnya tercakup oleh $[L, R]$, jalankan prosedur `add_line` Li Chao.
3. Kompleksitas: $\mathcal{O}(\log^2 N)$ waktu per penambahan segmen garis.

---

## 5. Ringkasan Perbandingan Metode CHT

| Metode | Syarat Kemiringan ($m$) | Syarat Kueri ($x$) | Waktu Tambah Garis | Waktu Kueri | Keunggulan Utama |
|---|---|---|---|---|---|
| **CHT Deque** | Monoton | Monoton | $\mathcal{O}(1)$ amortized | $\mathcal{O}(1)$ amortized | Paling cepat, kode ringkas |
| **CHT Binary Search** | Monoton | Bebas | $\mathcal{O}(1)$ amortized | $\mathcal{O}(\log N)$ | Mendukung kueri acak |
| **LineContainer (`std::set`)** | Bebas | Bebas | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | Dinamis penuh, tanpa koordinat awal |
| **Li Chao Tree** | Bebas | Bebas | $\mathcal{O}(\log N)$ | $\mathcal{O}(\log N)$ | **Paling stabil, mudah diimplementasikan, mendukung segmen garis $[L, R]$** |
