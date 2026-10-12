/*
============================================================
✅ Solution 3: Menyusun Kartu Bertahap
============================================================
Approach: Insertion sort, cetak keadaan setelah tiap penyisipan
Complexity: Time O(n^2) | Space O(1)
Key Insight: Invariant insertion sort adalah "a[0..i-1] sudah terurut di
             antara mereka sendiri". Perhatikan bahwa ini BERBEDA dari
             invariant bubble/selection, yang menyatakan elemen sudah berada
             di posisi FINAL. Pada insertion sort, elemen di bagian kiri
             masih bisa bergeser lagi ketika elemen yang lebih kecil datang.

📖 PENJELASAN PENDEKATAN:
1. Untuk i dari 1 sampai n-1: simpan kunci = a[i].
2. Geser semua elemen di kiri yang lebih besar dari kunci, satu langkah ke
   kanan, sampai menemukan tempat yang benar.
3. Tulis kunci di tempat itu, lalu cetak seluruh array.

⚠️ ARAH PENULISAN SAAT MENGGESER adalah satu-satunya jebakan teknis di sini.
   Yang benar: a[j+1] = a[j], berjalan MUNDUR dari j = i-1.
   Kalau kamu menuliskannya maju (a[j] = a[j+1]) atau berjalan maju,
   kamu akan menimpa data dan array berubah menjadi rusak.

⚠️ MENGGESER, BUKAN MENUKAR. Satu penulisan memori per langkah, bukan tiga
   (swap = tmp=a, a=b, b=tmp). Perbedaan konstanta inilah yang membuat
   insertion sort dipakai di dalam std::sort untuk potongan kecil (< 16
   elemen), tempat overhead rekursi quicksort lebih mahal daripada O(n^2)
   yang sangat kecil.

⚠️ BAGIAN KANAN YANG BELUM DIPROSES tetap utuh dan ikut dicetak. Perhatikan
   sampel: baris pertama "1 5 4 2" -- elemen 4 dan 2 belum tersentuh.

⚠️ KUNCI HARUS DISIMPAN DULU sebelum menggeser. Kalau tidak, a[i] akan
   tertimpa oleh pergeseran pertama.

🔄 ALTERNATIVE APPROACHES:
- Binary insertion sort: memakai binary search untuk mencari posisi.
  Perbandingan turun jadi O(n log n), tetapi PERGESERANNYA tetap O(n^2)
  karena memindahkan elemen di array tetap butuh menyalin satu per satu.
  Berguna hanya kalau operasi perbandingan mahal (misalnya string panjang).
============================================================
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int& x : a) cin >> x;

    string out;
    for (int i = 1; i < n; i++) {
        int kunci = a[i];                  // SIMPAN dulu sebelum menggeser
        int j = i - 1;
        while (j >= 0 && a[j] > kunci) {   // '>' -> berhenti saat sama (stabil)
            a[j + 1] = a[j];               // geser ke KANAN, berjalan MUNDUR
            j--;
        }
        a[j + 1] = kunci;

        for (int k = 0; k < n; k++) {
            out += to_string(a[k]);
            out += (k + 1 == n) ? '\n' : ' ';
        }
    }

    cout << out;
    return 0;
}
