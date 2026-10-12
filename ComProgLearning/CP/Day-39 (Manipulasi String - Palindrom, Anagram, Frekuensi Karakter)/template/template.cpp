/*
============================================================
  Day 32 — String Dasar | CP Template
============================================================
  Tiga senjata utama:
    1. DUA POINTER      -> cek palindrom, O(N) waktu O(1) memori
    2. TABEL FREKUENSI  -> anagram, huruf terbanyak, bisa-jadi-palindrom
    3. EXPAND CENTER    -> palindrom terpanjang, O(N^2)

  Jebakan yang paling sering:
    - substr(mulai, PANJANG), bukan (mulai, akhir)
    - cin.ignore() sebelum getline setelah cin >>
    - c - 'a' jadi negatif kalau ada huruf besar/spasi
============================================================
*/
#include <bits/stdc++.h>
using namespace std;

#define FASTIO ios_base::sync_with_stdio(false); cin.tie(NULL)
typedef long long ll;

// ─── 1. PALINDROM (DUA POINTER) ──────────────────────────

bool palindrom(const string& s) {
    int kiri = 0, kanan = (int)s.size() - 1;
    while (kiri < kanan) {
        if (s[kiri] != s[kanan]) return false;
        kiri++;
        kanan--;
    }
    return true;
}

// Versi longgar: abaikan spasi, tanda baca, dan besar-kecil huruf
bool palindromLonggar(const string& s) {
    string bersih;
    for (char c : s)
        if (isalnum((unsigned char)c)) bersih += tolower((unsigned char)c);
    return palindrom(bersih);
}

// ─── 2. TABEL FREKUENSI ──────────────────────────────────

array<int, 26> frekuensi(const string& s) {
    array<int, 26> f{};
    for (char c : s)
        if (c >= 'a' && c <= 'z') f[c - 'a']++;
    return f;
}

bool anagram(const string& a, const string& b) {
    if (a.size() != b.size()) return false;   // cek murah lebih dulu
    array<int, 26> f{};
    for (char c : a) f[c - 'a']++;
    for (char c : b) f[c - 'a']--;
    for (int i = 0; i < 26; i++) if (f[i] != 0) return false;
    return true;
}

// Berapa huruf yang frekuensinya ganjil? (<= 1 berarti bisa jadi palindrom)
int hurufGanjil(const string& s) {
    auto f = frekuensi(s);
    int ganjil = 0;
    for (int i = 0; i < 26; i++) if (f[i] % 2 == 1) ganjil++;
    return ganjil;
}

bool bisaJadiPalindrom(const string& s) { return hurufGanjil(s) <= 1; }

// Susun jadi palindrom (alfabetis). Kembalikan "" kalau tidak mungkin.
string susunPalindrom(const string& s) {
    auto f = frekuensi(s);
    int ganjil = 0;
    for (int i = 0; i < 26; i++) if (f[i] % 2 == 1) ganjil++;
    if (ganjil > 1) return "";

    string kiri, tengah;
    for (int i = 0; i < 26; i++) {
        if (f[i] % 2 == 1) tengah = string(1, 'a' + i);
        kiri += string(f[i] / 2, 'a' + i);
    }
    string kanan = kiri;
    reverse(kanan.begin(), kanan.end());
    return kiri + tengah + kanan;
}

// ─── 3. EXPAND AROUND CENTER ─────────────────────────────

string palindromTerpanjang(const string& s) {
    int n = s.size();
    if (n == 0) return "";
    int mulaiTerbaik = 0, panjangTerbaik = 1;

    auto lebarkan = [&](int kiri, int kanan) {
        while (kiri >= 0 && kanan < n && s[kiri] == s[kanan]) { kiri--; kanan++; }
        int panjang = kanan - kiri - 1;
        if (panjang > panjangTerbaik) { panjangTerbaik = panjang; mulaiTerbaik = kiri + 1; }
    };

    for (int i = 0; i < n; i++) {
        lebarkan(i, i);        // pusat 1 huruf -> panjang ganjil
        lebarkan(i, i + 1);    // pusat 2 huruf -> panjang genap
    }
    return s.substr(mulaiTerbaik, panjangTerbaik);
}

// ─── 4. PENCARIAN POLA NAIF (untuk N kecil) ──────────────

int hitungMuncul(const string& teks, const string& pola) {
    if (pola.empty() || pola.size() > teks.size()) return 0;
    int total = 0;
    for (size_t i = teks.find(pola); i != string::npos; i = teks.find(pola, i + 1))
        total++;                              // menghitung yang tumpang tindih juga
    return total;
}

// ─── MAIN ────────────────────────────────────────────────

int main() {
    FASTIO;

    string s;
    if (!(cin >> s)) return 0;

    cout << (palindrom(s) ? "PALINDROM" : "BUKAN PALINDROM") << "\n";
    cout << "Palindrom terpanjang: " << palindromTerpanjang(s) << "\n";

    return 0;
}
