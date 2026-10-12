# Day 268 — Convex Hull Trick: Kasus Monoton

> **Ide satu kalimat:** Convex Hull Trick (CHT) memetakan transisi DP berbentuk $dp[i] = \min_{j < i} \{ dp[j] + b[j] \cdot a[i] \}$ menjadi pencarian nilai minimum dari sekumpulan garis linear $y = m_j \cdot x + c_j$, memangkas kompleksitas dari $\mathcal{O}(N^2)$ menjadi $\mathcal{O}(N)$ linier menggunakan *double-ended queue* (deque).

---

## 1. Motivasi & Geometri Transisi DP

Banyak permasalahan optimasi memiliki bentuk transisi dengan suku perkalian silang antara variabel yang hanya bergantung pada $j$ dan variabel yang hanya bergantung pada $i$:
$$dp[i] = \min_{0 \le j < i} \{ dp[j] + b_j \cdot a_i + \text{cost}_i \}$$

Perhatikan bahwa untuk setiap indeks $j$ yang telah dihitung:
- Nilai $b_j$ berperan sebagai **kemiringan garis (slope)** $m = b_j$.
- Nilai $dp[j]$ berperan sebagai **perpotongan sumbu-Y (intercept)** $c = dp[j]$.
- Nilai $a_i$ berperan sebagai **titik evaluasi (query)** $x = a_i$.

Persamaan transisi berubah menjadi:
$$dp[i] = \text{cost}_i + \min_{j} \{ m_j \cdot x + c_j \}$$

Secara geometris, setiap state $j$ adalah sebuah **garis lurus** pada bidang kartesius, dan mencari $dp[i]$ sama dengan mencari **amplop bawah (lower convex hull)** dari seluruh himpunan garis pada koordinat $x = a_i$.

---

## 2. Syarat Kasus Monoton (Deque $\mathcal{O}(1)$ Amortized)

Varian paling efisien dari CHT terjadi ketika:
1. **Kemiringan Garis Monoton**: Nilai kemiringan $m$ yang dimasukkan terurut (misalnya monoton menurun: $m_1 > m_2 > m_3 > \dots$).
2. **Titik Evaluasi Kueri Monoton**: Nilai kueri $x$ yang diminta terurut (misalnya monoton menaik: $x_1 \le x_2 \le x_3 \le \dots$).

### Mengapa Bisa $\mathcal{O}(N)$?
- **Pembersihan Belakang Deque (`pop_back`)**:
  Ketika garis baru $L_3$ akan dimasukkan, garis di ujung belakang $L_2$ dibuang jika titik potongnya dengan $L_1$ berada di sebelah kanan titik potongnya dengan $L_3$ (artinya $L_2$ berada di atas amplop bawah untuk semua nilai $x$).
- **Pembersihan Depan Deque (`pop_front`)**:
  Karena nilai kueri $x$ selalu bergerak ke kanan (monoton menaik), jika garis di posisi indeks 1 lebih rendah dari garis di posisi indeks 0 pada nilai $x$ saat ini, maka garis di indeks 0 **tidak akan pernah lagi menjadi yang terbaik di masa depan**! Oleh karena itu, kita dapat membuangnya secara permanen dengan `pop_front()`.
- Setiap garis ditambahkan tepat sekali dan dihapus paling banyak sekali dari depan/belakang, sehingga total waktu untuk memproses $N$ garis dan $Q$ kueri adalah **$\mathcal{O}(N + Q)$ amortized**!

---

## 3. Kondisi Eliminasi Garis (Uji Perkalian Silang)

Misalkan tiga garis berurutan $L_1, L_2, L_3$ memiliki kemiringan menurun $m_1 > m_2 > m_3$.
Titik potong antara $L_1$ dan $L_2$ adalah:
$$x_{12} = \frac{c_1 - c_2}{m_2 - m_1}$$
Titik potong antara $L_2$ dan $L_3$ adalah:
$$x_{23} = \frac{c_2 - c_3}{m_3 - m_2}$$

Garis $L_2$ menjadi **usang / tidak berguna** jika $x_{12} \ge x_{23}$:
$$\frac{c_1 - c_2}{m_2 - m_1} \ge \frac{c_2 - c_3}{m_3 - m_2}$$

Untuk menghindari masalah ketelitian bilangan pecahan (*floating point precision*), kita kalikan silang:
$$(c_2 - c_1)(m_2 - m_3) \ge (c_3 - c_2)(m_1 - m_2)$$

> [!WARNING]
> Karena nilai $c$ bisa mencapai $10^{12}$ dan $m$ mencapai $10^6$, hasil kali silang bisa melampaui rentang 64-bit integer (`long long`). **Wajib gunakan `__int128` saat melakukan perkalian silang!**

---

## 4. Pola Ekspansi Kuadratik (Frog Jump & Distance)

Banyak soal memuat bentuk biaya kuadrat selisih:
$$dp[i] = \min_{j < i} \{ dp[j] + (h_i - h_j)^2 + C \}$$

Langkah ekspansi aljabar:
1. Jabarkan kuadrat: $(h_i - h_j)^2 = h_i^2 - 2 h_j h_i + h_j^2$.
2. Kumpulkan suku-suku:
   $$dp[i] = h_i^2 + C + \min_{j < i} \{ \underbrace{(-2 h_j)}_{m_j} \cdot \underbrace{h_i}_{x} + \underbrace{(dp[j] + h_j^2)}_{c_j} \}$$
3. Diperoleh bentuk linear sempurna:
   - Garis $j$: $m = -2 h_j$, $c = dp[j] + h_j^2$.
   - Kueri $i$: $x = h_i$, tambahkan konstanta luar $h_i^2 + C$.

---

## 5. Checklist Debug & Jebakan Gotchas

1. **Urutan Operasi**: Pada DP, lakukan **Query untuk menghitung $dp[i]$ TERLEBIH DAHULU**, baru kemudian **Tambahkan garis milik state $i$ ke dalam Hull**. Jangan pernah memasukkan garis $i$ sebelum men-query!
2. **Kemiringan Sama ($m_1 = m_2$)**:
   Jika dua garis memiliki kemiringan persis sama, simpan hanya garis dengan intersep $c$ terkecil (untuk kasus minimasi) atau terbesar (untuk maksimasi).
3. **Monotonisitas Menurun vs Menaik**:
   - Minimasi dengan $m$ menurun dan $x$ menaik: gunakan `pop_front` jika $L_1(x) \le L_0(x)$.
   - Jika $m$ monoton tetapi $x$ acak/tidak monoton: jangan gunakan deque `pop_front`, gunakan **Binary Search** di atas hull dengan waktu $\mathcal{O}(\log N)$ per kueri.
   - Jika $m$ dan $x$ keduanya acak: gunakan **Li Chao Tree** (Day 269).
