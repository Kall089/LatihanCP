# 🎯 Drill 1 — Pengenalan Pola (target: 15 menit, tanpa menulis kode)

Untuk setiap skenario, jawab **dua hal saja**:

1. **Teknik apa?** (Kadane / Kadane+state / sliding window tetap / two pointers /
   prefix+deque / prefix+map / bukan salah satunya)
2. **Sinyal apa di kalimat soalnya yang membuatmu yakin?**

Tulis jawabanmu di sini dulu, baru buka `solusi/drill_1_kunci.md`.
Target: **10 dari 12 benar**. Kalau di bawah itu, baca ulang Bagian B.

---

**1.** Diberikan `n` bilangan bulat (boleh negatif). Cari segmen berurutan dengan
jumlah terbesar.

**2.** Diberikan `n` bilangan bulat positif dan bilangan `s`. Cari segmen berurutan
**terpendek** yang jumlahnya minimal `s`.

**3.** Diberikan `n` bilangan bulat. Ada berapa banyak pasangan `(l, r)` sehingga
`a[l] + ... + a[r] = 0`?

**4.** Suhu harian selama `n` hari (boleh minus). Cari periode berurutan dengan
total suhu tertinggi, tapi periodenya **tidak boleh lebih dari 30 hari**.

**5.** Nilai saham `n` hari. Beli sekali, jual sekali (jual setelah beli). Untung maksimum?

**6.** Diberikan `n` bilangan bulat. Pilih himpunan bagian (boleh loncat-loncat)
dengan jumlah terbesar.

**7.** Diberikan `n` bilangan bulat. Cari segmen berurutan dengan jumlah terbesar,
tapi kamu **boleh membuang paling banyak satu elemen** dari dalam segmen itu.

**8.** `n` pos ronda melingkar, tiap pos punya nilai (boleh negatif). Cari rangkaian
pos berurutan (boleh melewati ujung) dengan total tertinggi.

**9.** Diberikan `n` bilangan bulat positif dan `k`. Cari rata-rata tertinggi dari
segmen berurutan yang panjangnya **tepat** `k`.

**10.** Diberikan `n` bilangan bulat (boleh negatif) dan `k`. Cari rata-rata tertinggi
dari segmen berurutan yang panjangnya **minimal** `k`.

**11.** Grid `r × c` berisi bilangan bulat boleh negatif. Cari persegi panjang dengan
total isi terbesar.

**12.** Diberikan `n` bilangan bulat. Cari **dua** segmen berurutan yang **tidak
bertumpang tindih**, sehingga total jumlah keduanya terbesar.

---

## Bonus — jelaskan dalam satu kalimat

**13.** Kenapa untuk soal nomor 1, `best = 0` bisa memberi jawaban salah, sedangkan
untuk soal "jumlah terbesar, segmen boleh kosong" justru `best = 0` yang benar?

**14.** Pada soal nomor 4, kenapa Kadane biasa gagal? Jawab dengan menyebut bagian
mana dari **bukti optimal substructure** yang runtuh saat ada batasan panjang.
