# 📘 Blok 1 — Dari Prosedural ke Objek

**Prasyarat:** C++ dasar — fungsi, `struct`, pointer, referensi, `vector`
**Estimasi:** 4–6 jam teori + 3–4 jam latihan + 2–3 jam proyek

**Setelah blok ini kamu bisa:**
- Menjelaskan **masalah apa** yang dipecahkan OOP, bukan sekadar definisinya
- Menulis class yang siklus hidupnya benar (lahir bersih, mati bersih)
- Menjelaskan urutan inisialisasi yang sebenarnya, bukan yang kamu kira
- Memakai `const` dengan benar dan tahu kenapa itu bukan sekadar formalitas

---

# 1. Masalah yang Dipecahkan OOP

## 1.1 Jangan mulai dari definisi

Hampir semua materi OOP dimulai dengan: *"OOP adalah paradigma pemrograman
berbasis objek yang memiliki empat pilar: enkapsulasi, abstraksi, pewarisan,
dan polimorfisme."*

Kalimat itu benar dan hampir tidak berguna. Ia menjelaskan **apa**, bukan
**kenapa** — dan tanpa "kenapa", empat pilar itu cuma jadi hafalan ujian.

Jadi mari mulai dari kode prosedural yang rusak, dan lihat kerusakannya
sendiri.

## 1.2 Kode yang rusak

Kita menulis program pecahan. Cara prosedural:

```cpp
#include <iostream>
using namespace std;

int pembilang = 1;
int penyebut   = 2;

void cetak() {
    cout << pembilang << "/" << penyebut << "\n";
}

int main() {
    pembilang = 3;
    penyebut  = 4;
    cetak();                  // 3/4
}
```

Sekarang kita butuh **dua** pecahan. Solusi naif:

```cpp
int pembilang1 = 1, penyebut1 = 2;
int pembilang2 = 3, penyebut2 = 4;
```

Sudah mulai janggal, tapi masih jalan. Butuh seratus pecahan? Jelas tidak bisa.
Jadi kita naik ke `struct`:

```cpp
struct Pecahan {
    int pembilang;
    int penyebut;
};

void cetak(Pecahan p) {
    cout << p.pembilang << "/" << p.penyebut << "\n";
}
```

Jauh lebih baik. **Data yang berkaitan sekarang berkumpul.** Ini sudah setengah
jalan menuju objek. Tapi masih ada tiga masalah, dan ketiganya serius.

## 1.3 Masalah 1 — objek bisa lahir dalam keadaan rusak

```cpp
Pecahan p;              // pembilang dan penyebut BERISI SAMPAH
cetak(p);               // mencetak angka acak
```

Lebih buruk lagi:

```cpp
Pecahan q;
q.pembilang = 1;
q.penyebut  = 0;        // pecahan dengan penyebut nol
```

Tidak ada yang mencegahnya. Kompilator tidak protes. Program jalan sampai
nanti meledak di tempat lain — dan saat meledak, kamu akan mencari bugnya di
tempat yang salah.

> **Yang kita mau:** mustahil membuat `Pecahan` yang tidak valid.

## 1.4 Masalah 2 — aturan tersebar ke mana-mana

Pecahan harus selalu disederhanakan: `2/4` seharusnya `1/2`. Siapa yang
bertanggung jawab?

Dengan `struct`, jawabannya: **semua orang yang menyentuhnya.**

```cpp
Pecahan a = {2, 4};
sederhanakan(a);        // <- harus ingat memanggil ini

Pecahan b = {6, 8};
                        // <- di sini lupa. bug.

Pecahan c = jumlah(a, b);
sederhanakan(c);        // <- ingat lagi
```

Setiap pemanggil harus tahu dan mengingat aturannya. Satu orang lupa satu kali,
programnya salah. Dan yang lupa itu biasanya kamu sendiri, tiga minggu kemudian.

> **Yang kita mau:** aturan dijaga di **satu tempat**, dan tidak mungkin dilupakan.

## 1.5 Masalah 3 — mengubah representasi merusak semua pemanggil

Suatu hari kamu ingin menyimpan pecahan sebagai `long long` supaya tidak
overflow. Kamu ubah `struct`-nya:

```cpp
struct Pecahan {
    long long pembilang;
    long long penyebut;
};
```

Dan **setiap baris kode** di seluruh program yang menulis `p.pembilang` ikut
terdampak. Kalau ada 200 tempat, kamu punya 200 tempat untuk salah.

> **Yang kita mau:** representasi internal bisa berubah tanpa menyentuh pemakainya.

## 1.6 Tiga masalah, satu nama

| Masalah | Nama resminya | Solusinya di C++ |
|---|---|---|
| Objek bisa lahir rusak | **invariant tidak dijaga** | constructor |
| Aturan tersebar ke pemanggil | **coupling tinggi** | member function |
| Ubah representasi = ubah semua | **abstraksi bocor** | `private` + antarmuka publik |

**Enkapsulasi** adalah nama gabungan untuk solusi ketiganya. Perhatikan bahwa
definisinya sekarang punya isi:

> Enkapsulasi bukan "menyembunyikan data". Enkapsulasi adalah **menyatukan data
> dengan aturan yang menjaganya, sehingga objek tidak pernah bisa berada dalam
> keadaan tidak valid, dan pemakainya tidak perlu tahu bagaimana isinya disimpan.**

Itu kalimat yang layak kamu hafal — karena kamu sudah melihat masalah yang
dipecahkannya.

## 1.7 Kapan OOP BUKAN jawabannya

Ini bagian yang jarang diajarkan, dan penting sejak hari pertama.

OOP berguna saat ada **state yang punya aturan**. Kalau tidak ada state, atau
tidak ada aturan yang perlu dijaga, class hanya menambah kerumitan:

```cpp
// TIDAK PERLU class. Ini cuma fungsi.
class Kalkulator {
public:
    int tambah(int a, int b) { return a + b; }
};

// LEBIH BAIK
int tambah(int a, int b) { return a + b; }
```

Class tanpa data anggota, atau class yang semua datanya `public`, biasanya
adalah tanda bahwa yang kamu butuhkan sebenarnya fungsi bebas. Kamu akan
bertemu lagi dengan ini di Blok 9.

---

# 2. `struct` vs `class` dan Access Specifier

## 2.1 Perbedaannya cuma satu

Di C++, `struct` dan `class` **identik** kecuali satu hal:

```cpp
struct A { int x; };     // x otomatis PUBLIC
class  B { int x; };     // x otomatis PRIVATE
```

Itu saja. Segalanya yang bisa dilakukan `class` bisa juga dilakukan `struct`.

Tapi **konvensinya** bermakna, dan sebaiknya kamu ikuti:

| Pakai | Kapan |
|---|---|
| `struct` | sekadar kumpulan data tanpa invariant — semua boleh diakses bebas |
| `class` | ada invariant yang harus dijaga |

Menulis `struct Pecahan` mengirim pesan "silakan utak-atik langsung". Menulis
`class Pecahan` mengirim pesan "ada aturan di sini". Pesan itu dibaca manusia,
bukan kompilator — dan manusia yang membacanya sering kali kamu sendiri.

## 2.2 Tiga tingkat akses

```cpp
class Contoh {
public:
    // siapa pun boleh akses
    int a;

private:
    // hanya member function kelas ini (dan friend) yang boleh
    int b;

protected:
    // seperti private, TAPI kelas turunan juga boleh
    int c;
};
```

`protected` baru benar-benar berarti di Blok 4 saat ada inheritance. Untuk
sekarang, cukup tahu ia ada.

## 2.3 Aturan praktis

**Mulai dari `private`, buka seperlunya.** Bukan sebaliknya.

Alasannya asimetris: menambah akses nanti itu mudah dan aman. Mengurangi akses
nanti berarti membongkar semua kode yang sudah terlanjur memakainya.

```cpp
class Pecahan {
private:                     // <- pertahanan pertama
    int pembilang_;
    int penyebut_;

public:                      // <- apa yang boleh dilakukan dunia luar
    int ambilPembilang() const;
    void cetak() const;
};
```

Perhatikan `_` di belakang nama data anggota. Itu konvensi umum untuk
membedakan data anggota dari parameter dan variabel lokal. Konvensi lain yang
juga umum: `m_pembilang`. Pilih satu, lalu konsisten.

## 2.4 Urutan penulisan

Tulis `public` **duluan**, `private` belakangan:

```cpp
class Pecahan {
public:
    Pecahan(int p, int q);
    void cetak() const;

private:
    int pembilang_;
    int penyebut_;
};
```

Alasannya bukan teknis, melainkan tentang pembaca. Orang yang membaca kelasmu
ingin tahu **apa yang bisa dilakukan** dengannya, bukan bagaimana isinya
disimpan. Yang penting untuk mereka ditaruh di atas.

---

# 3. Member Function, `this`, dan Definisi di Luar Kelas

## 3.1 Fungsi yang tahu objeknya

```cpp
class Pecahan {
public:
    void cetak() const {
        cout << pembilang_ << "/" << penyebut_ << "\n";
    }
private:
    int pembilang_, penyebut_;
};

Pecahan a, b;
a.cetak();      // mencetak isi a
b.cetak();      // mencetak isi b
```

Satu definisi fungsi, tapi hasilnya berbeda tergantung objek yang memanggilnya.
Bagaimana `cetak()` tahu ia sedang mengurus `a` atau `b`?

## 3.2 `this` — parameter tersembunyi

Setiap member function non-static punya parameter tambahan yang tidak kamu
tulis: pointer ke objek pemanggilnya, bernama `this`.

Yang kamu tulis:

```cpp
void cetak() const {
    cout << pembilang_ << "/" << penyebut_;
}
```

Yang sebenarnya terjadi (kira-kira):

```cpp
void cetak(const Pecahan* this) {
    cout << this->pembilang_ << "/" << this->penyebut_;
}
```

```
        a.cetak()                       b.cetak()
            │                               │
            ▼                               ▼
     ┌─────────────┐                 ┌─────────────┐
     │  this ──────┼──► objek a      │  this ──────┼──► objek b
     └─────────────┘                 └─────────────┘
       kode fungsinya SAMA, yang berbeda cuma this
```

Jadi: **satu salinan kode, banyak objek.** Member function tidak disimpan di
dalam tiap objek — kalau begitu, seribu objek berarti seribu salinan kode, dan
itu boros tanpa alasan.

## 3.3 Kapan `this` perlu ditulis eksplisit

Sebagian besar waktu tidak perlu. Tiga kasus di mana perlu:

**Kasus 1 — nama parameter bertabrakan dengan nama anggota:**

```cpp
class Titik {
    int x, y;
public:
    void set(int x, int y) {
        this->x = x;        // tanpa this->, kamu menugaskan x ke dirinya sendiri
        this->y = y;
    }
};
```

Ini alasan bagus untuk memakai akhiran `_` pada data anggota. Dengan `x_`,
tabrakan tidak pernah terjadi dan `this->` tidak perlu.

**Kasus 2 — mengembalikan objek itu sendiri (untuk chaining):**

```cpp
class Builder {
    string hasil_;
public:
    Builder& tambah(const string& s) {
        hasil_ += s;
        return *this;                    // kembalikan objeknya, bukan pointernya
    }
};

Builder b;
b.tambah("a").tambah("b").tambah("c");   // bisa dirangkai
```

**Kasus 3 — memberikan objek ini ke fungsi lain:**

```cpp
void daftarkanKe(Registry& r) {
    r.tambah(this);
}
```

## 3.4 Deklarasi di dalam, definisi di luar

Kelas yang panjang jadi sulit dibaca kalau semua badan fungsi ditulis di
dalamnya. Pisahkan:

```cpp
class Pecahan {
public:
    void cetak() const;              // deklarasi saja
    int ambilPembilang() const;

private:
    int pembilang_, penyebut_;
};

// definisi di luar — perhatikan Pecahan:: di depan nama fungsi
void Pecahan::cetak() const {
    cout << pembilang_ << "/" << penyebut_ << "\n";
}

int Pecahan::ambilPembilang() const {
    return pembilang_;
}
```

`Pecahan::` itu bukan hiasan. Tanpanya, kompilator menganggap kamu sedang
mendefinisikan fungsi bebas bernama `cetak`, dan `pembilang_` jadi tidak dikenal.

**Perbedaan penting:** fungsi yang didefinisikan **di dalam** kelas otomatis
bersifat `inline`. Yang di luar tidak. Untuk sekarang, cukup tahu aturan
praktisnya: fungsi satu-dua baris boleh di dalam, sisanya di luar.

---

# 4. Constructor & Destructor: Siklus Hidup Objek

## 4.1 Constructor menutup lubang pertama

Ingat masalah 1.3 — objek bisa lahir dalam keadaan rusak. Constructor
menutupnya:

```cpp
class Pecahan {
public:
    Pecahan(int p, int q) {              // constructor
        if (q == 0) q = 1;               // jaga invariant
        pembilang_ = p;
        penyebut_  = q;
    }
private:
    int pembilang_, penyebut_;
};

Pecahan a(3, 4);       // OK
Pecahan b;             // ERROR kompilasi - tidak ada constructor tanpa parameter
```

Baris terakhir itu **fitur, bukan gangguan**. Kompilator sekarang mencegahmu
membuat pecahan yang tidak diinisialisasi. Kesalahan yang tadinya baru ketahuan
saat program jalan, sekarang ketahuan saat kompilasi.

Ciri constructor:
- namanya sama persis dengan nama kelas
- tidak punya tipe kembalian, bahkan bukan `void`
- dipanggil otomatis saat objek dibuat

## 4.2 Overloading constructor

Satu kelas boleh punya beberapa constructor, asal parameternya berbeda:

```cpp
class Pecahan {
public:
    Pecahan() : pembilang_(0), penyebut_(1) {}        // default: 0/1
    Pecahan(int bulat) : pembilang_(bulat), penyebut_(1) {}
    Pecahan(int p, int q) : pembilang_(p), penyebut_(q) {}
private:
    int pembilang_, penyebut_;
};

Pecahan a;            // 0/1
Pecahan b(5);         // 5/1
Pecahan c(3, 4);      // 3/4
```

## 4.3 Constructor default dan aturannya yang menjebak

```cpp
class A { int x; };                    // kompilator MEMBUATKAN A()
A a;                                   // OK (tapi x berisi sampah)

class B {
public:
    B(int v) : x_(v) {}                // kamu membuat constructor sendiri
private:
    int x_;
};
B b;                                   // ERROR - B() tidak dibuatkan lagi
```

**Aturannya:** kompilator hanya membuatkan constructor default kalau kamu
**tidak menulis constructor apa pun**. Begitu kamu menulis satu saja, yang
gratisan hilang.

Kalau kamu tetap menginginkannya:

```cpp
class B {
public:
    B() = default;                     // minta yang gratisan kembali
    B(int v) : x_(v) {}
private:
    int x_ = 0;                        // inisialisasi default anggota
};
```

## 4.4 `explicit` — mencegah konversi yang tidak kamu minta

Constructor dengan satu parameter diam-diam berfungsi sebagai **konverter**:

```cpp
class Pecahan {
public:
    Pecahan(int bulat) : pembilang_(bulat), penyebut_(1) {}
    // ...
};

void proses(Pecahan p);

proses(5);            // KOMPILASI? Ya. 5 diam-diam jadi Pecahan(5).
```

Kadang itu memang yang kamu mau. Sering kali tidak — dan konversi diam-diam
menghasilkan bug yang sulit dilihat karena tidak ada yang tampak salah di kode.

Cegah dengan `explicit`:

```cpp
explicit Pecahan(int bulat) : pembilang_(bulat), penyebut_(1) {}

proses(5);              // ERROR sekarang. Bagus.
proses(Pecahan(5));     // harus ditulis jelas
```

> **Aturan praktis:** beri `explicit` pada semua constructor satu-parameter,
> kecuali kamu memang sengaja menginginkan konversi implisitnya.

## 4.5 Destructor

Destructor dipanggil otomatis saat objek mati:

```cpp
class Pecahan {
public:
    Pecahan(int p, int q) { cout << "lahir\n"; }
    ~Pecahan()            { cout << "mati\n"; }
};

int main() {
    Pecahan a(1, 2);        // "lahir"
    {
        Pecahan b(3, 4);    // "lahir"
    }                       // "mati"  <- b mati di sini, akhir blok
    cout << "selesai\n";
}                           // "mati"  <- a mati di sini
```

Keluarannya:
```
lahir
lahir
mati
selesai
mati
```

Ciri destructor:
- namanya `~NamaKelas`
- tidak punya parameter dan tidak punya tipe kembalian
- tidak bisa di-overload — satu kelas hanya punya satu
- dipanggil **otomatis**, dan urutannya kebalikan dari urutan lahir

## 4.6 Kenapa destructor adalah fitur besar

`Pecahan` tidak butuh destructor — ia hanya berisi dua `int` yang mati sendiri.
Destructor menjadi penting saat objek **memiliki sesuatu**: memori, file,
koneksi, kunci.

```cpp
class BukaFile {
public:
    BukaFile(const string& nama) { f_ = fopen(nama.c_str(), "r"); }
    ~BukaFile()                  { if (f_) fclose(f_); }   // DIJAMIN dipanggil
private:
    FILE* f_;
};

void kerjakan() {
    BukaFile bf("data.txt");
    // ... kode yang mungkin melempar exception ...
    // ... kode yang mungkin return lebih awal ...
}   // file DIJAMIN tertutup, lewat jalur keluar mana pun
```

Bandingkan dengan Java, di mana kamu harus menulis `try/finally` dan
mengingatnya setiap kali. Di C++, kamu menulisnya **sekali** di dalam kelas,
dan semua pemakai mendapatkannya gratis.

Ini yang namanya **RAII**, dan ia dibahas tuntas di Blok 2. Untuk sekarang
cukup tahu: destructor otomatis inilah alasan C++ tidak butuh garbage collector.

## 4.7 Peta siklus hidup

```
    Pecahan a(3, 4);
         │
         ├─► 1. memori dialokasikan (di stack)
         ├─► 2. anggota diinisialisasi (initializer list — bagian 5)
         ├─► 3. badan constructor dijalankan
         │
         ▼
      [ objek hidup dan valid ]
         │
         ├─► 4. badan destructor dijalankan
         ├─► 5. anggota dihancurkan (urutan TERBALIK)
         └─► 6. memori dilepas
```

Perhatikan langkah 2 datang **sebelum** langkah 3. Itu bukan detail sepele, dan
jadi pokok bahasan berikutnya.

---

# 5. Member Initializer List & Urutan Inisialisasi

## 5.1 Dua cara yang kelihatan sama

```cpp
// Cara A — penugasan di dalam badan
Pecahan(int p, int q) {
    pembilang_ = p;
    penyebut_  = q;
}

// Cara B — initializer list
Pecahan(int p, int q) : pembilang_(p), penyebut_(q) {
}
```

Untuk `int`, hasilnya sama dan bedanya sepele. Untuk tipe lain, bedanya nyata.

## 5.2 Apa yang sebenarnya terjadi

Anggota kelas **selalu** diinisialisasi sebelum badan constructor dijalankan.
Selalu — kamu tidak bisa mematikannya.

```
Cara A:   pembilang_ diinisialisasi (default)  →  lalu DITIMPA dengan p
          dua langkah

Cara B:   pembilang_ diinisialisasi LANGSUNG dengan p
          satu langkah
```

Untuk `int`, langkah pertama gratis. Untuk objek berat, tidak:

```cpp
class Mahasiswa {
public:
    // Cara A: string nama_ dibuat KOSONG, lalu dibuang isinya, lalu diisi n
    Mahasiswa(const string& n) { nama_ = n; }

    // Cara B: string nama_ langsung dibangun dari n
    Mahasiswa(const string& n) : nama_(n) {}
private:
    string nama_;
};
```

## 5.3 Tiga hal yang HANYA bisa lewat initializer list

Ini bukan soal efisiensi, tapi soal mungkin atau tidak.

**1. Anggota `const`:**

```cpp
class Lingkaran {
    const double PI_;
public:
    Lingkaran() { PI_ = 3.14159; }        // ERROR - const tidak bisa ditugaskan
    Lingkaran() : PI_(3.14159) {}         // OK
};
```

**2. Anggota referensi:**

```cpp
class Pencatat {
    ostream& keluaran_;
public:
    Pencatat(ostream& os) { keluaran_ = os; }    // ERROR - referensi tidak bisa dipindah
    Pencatat(ostream& os) : keluaran_(os) {}     // OK
};
```

**3. Anggota yang tidak punya constructor default:**

```cpp
class Mesin {
public:
    Mesin(int daya) : daya_(daya) {}       // tidak ada Mesin()
private:
    int daya_;
};

class Mobil {
    Mesin mesin_;
public:
    Mobil() { }                            // ERROR - Mesin() tidak ada
    Mobil() : mesin_(150) {}               // OK
};
```

## 5.4 Jebakan urutan — ini yang menggigit

> **Anggota diinisialisasi menurut urutan DEKLARASINYA di dalam kelas,
> bukan menurut urutan penulisan di initializer list.**

```cpp
class Salah {
    int b_;                                // dideklarasikan DULUAN
    int a_;
public:
    Salah(int x) : a_(x), b_(a_ * 2) {}    // ditulis a_ dulu, tapi...
};
```

Yang terjadi:

```
1. b_ diinisialisasi dulu (karena dideklarasikan duluan)
   b_ = a_ * 2   →  a_ MASIH SAMPAH  →  b_ jadi sampah
2. a_ diinisialisasi dengan x
```

Kompilator biasanya diam saja. Dengan `-Wall`, g++ memberi peringatan
`-Wreorder` — dan itu peringatan yang **tidak boleh** kamu abaikan.

**Perbaikannya:** tulis initializer list dengan urutan yang sama persis dengan
urutan deklarasi. Selalu. Tanpa pengecualian.

```cpp
class Benar {
    int a_;
    int b_;
public:
    Benar(int x) : a_(x), b_(a_ * 2) {}    // urutannya cocok
};
```

## 5.5 Inisialisasi default anggota (C++11)

Cara terbersih untuk nilai bawaan:

```cpp
class Pengaturan {
    int lebar_  = 800;                     // nilai default di tempat deklarasi
    int tinggi_ = 600;
    bool layarPenuh_ = false;
public:
    Pengaturan() = default;                            // pakai semua default
    Pengaturan(int w, int h) : lebar_(w), tinggi_(h) {} // timpa sebagian
};
```

Keunggulannya: nilai defaultnya ditulis **sekali**, di tempat yang jelas, dan
tidak perlu diulang di setiap constructor. Kalau kamu punya empat constructor,
ini menghemat empat tempat untuk lupa.

---

# 6. `const` Correctness

## 6.1 Masalahnya

```cpp
void cetakLaporan(const Pecahan& p) {
    p.cetak();          // ERROR - cetak() tidak dijanjikan const
}
```

`p` adalah `const`, jadi kompilator menolak memanggil fungsi apa pun yang
belum berjanji tidak akan mengubahnya. Bahkan kalau `cetak()` sebenarnya
memang tidak mengubah apa-apa — kompilator tidak menebak, ia menuntut janji
tertulis.

## 6.2 `const` member function

Janji itu ditulis dengan menaruh `const` **setelah** daftar parameter:

```cpp
class Pecahan {
public:
    void cetak() const;                 // janji: tidak mengubah objek
    int ambilPembilang() const;         // janji: tidak mengubah objek
    void sederhanakan();                // TIDAK berjanji - memang mengubah

private:
    int pembilang_, penyebut_;
};

void Pecahan::cetak() const {           // const diulang di definisi
    cout << pembilang_ << "/" << penyebut_;
    // pembilang_ = 5;                  <- ERROR, melanggar janji
}
```

Di dalam `const` member function, semua data anggota menjadi `const`.
Kompilator yang menegakkannya, bukan disiplin dirimu.

## 6.3 Kenapa ini bukan formalitas

Tanpa `const`, kamu tidak bisa memakai objekmu di tempat-tempat ini:

```cpp
void f(const Pecahan& p);          // parameter const& - cara paling umum
                                   // melewatkan objek besar

const Pecahan buatPecahan();       // nilai kembalian const

const vector<Pecahan> daftar;      // elemen container const
for (const auto& p : daftar) p.cetak();
```

`const&` sebagai parameter itu **default yang benar** untuk objek besar:
menghindari penyalinan tanpa memberi izin mengubah. Kalau kelasmu tidak
`const`-correct, kamu memaksa semua pemakai melewatkan objek dengan
penyalinan penuh — atau lebih buruk, membuka objekmu untuk diubah diam-diam.

## 6.4 Aturannya sederhana

> **Beri `const` pada setiap member function yang tidak mengubah objek.**

Bukan "kalau sempat". Setiap. Karena menambahkannya belakangan berarti
menyentuh ulang setiap fungsi, dan sering kali gagal karena satu fungsi
non-`const` memanggil yang lain sehingga efeknya menular.

## 6.5 Overloading berdasarkan `const`

Satu nama, dua versi — kompilator memilih berdasarkan `const`-nya objek:

```cpp
class Wadah {
    vector<int> data_;
public:
    int&       at(int i)       { return data_[i]; }   // objek non-const
    const int& at(int i) const { return data_[i]; }   // objek const
};

Wadah w;
w.at(0) = 5;                    // versi pertama - boleh menulis

const Wadah cw;
int x = cw.at(0);               // versi kedua - hanya boleh membaca
// cw.at(0) = 5;                // ERROR
```

Pola ini muncul di hampir semua container standar. Kamu akan menulisnya sendiri
di Blok 6.

## 6.6 `mutable` — pengecualian yang jarang

Kadang sebuah anggota memang perlu berubah di dalam `const` member function,
tanpa mengubah *makna* objeknya — misalnya cache atau penghitung akses:

```cpp
class Dokumen {
    mutable int jumlahDibaca_ = 0;         // boleh berubah meski objeknya const
    string isi_;
public:
    const string& baca() const {
        ++jumlahDibaca_;                   // OK karena mutable
        return isi_;
    }
};
```

Pakai dengan hemat. `mutable` yang dipakai untuk menyiasati `const` karena
malas adalah tanda desainnya perlu diperbaiki, bukan tanda `const`-nya salah.

---

# ⚠️ Kesalahan Umum Blok 1

| # | Kesalahan | Gejalanya | Perbaikan |
|---|---|---|---|
| 1 | Lupa `const` pada member function | error saat objek dilewatkan `const&` | beri `const` pada semua yang tidak mengubah |
| 2 | Initializer list urutannya tidak cocok | nilai sampah, peringatan `-Wreorder` | samakan dengan urutan deklarasi |
| 3 | Menugaskan di badan constructor | boros untuk objek berat; error untuk `const`/referensi | pakai initializer list |
| 4 | Menulis constructor lalu heran `A a;` error | "no matching constructor" | tambahkan `A() = default;` |
| 5 | Constructor satu parameter tanpa `explicit` | konversi diam-diam yang tidak diinginkan | beri `explicit` |
| 6 | Semua anggota `public` | tidak ada invariant yang terjaga | mulai dari `private` |
| 7 | Getter dan setter untuk **semua** anggota | sama saja dengan `public`, cuma lebih panjang | dibahas di Blok 2 |
| 8 | Lupa `Pecahan::` saat definisi di luar | "pembilang_ was not declared" | tambahkan `NamaKelas::` |

---

# 📌 Ringkasan Blok 1

### Kartu ingatan

```cpp
class Nama {
public:                              // apa yang bisa dilakukan - di ATAS
    Nama() = default;                // minta constructor default kembali
    explicit Nama(int v);            // explicit untuk satu parameter
    Nama(int a, int b);
    ~Nama();                         // dipanggil otomatis, urutan terbalik

    int ambil() const;               // const = janji tidak mengubah
    void ubah(int v);                // tanpa const = memang mengubah

private:                             // bagaimana isinya disimpan - di BAWAH
    int a_ = 0;                      // inisialisasi default di tempat
    int b_ = 1;
};

// definisi di luar - jangan lupa Nama:: dan const-nya
int Nama::ambil() const { return a_; }

// initializer list - urutannya HARUS sama dengan urutan deklarasi
Nama::Nama(int a, int b) : a_(a), b_(b) {}
```

### Yang harus melekat

1. **Enkapsulasi = menjaga invariant**, bukan menyembunyikan data.
2. **Constructor menutup lubang "objek lahir rusak".** Kalau objekmu bisa
   dibuat dalam keadaan tidak valid, constructor-mu belum selesai.
3. **Anggota diinisialisasi menurut urutan deklarasi**, bukan urutan di
   initializer list.
4. **Destructor dipanggil otomatis, urutannya terbalik.** Ini fondasi RAII.
5. **`const` bukan formalitas.** Tanpanya kelasmu tidak bisa dipakai di
   `const&`, dan `const&` adalah cara normal melewatkan objek.
6. **Class tanpa invariant sebaiknya `struct`** — atau jangan class sama sekali.

### Checklist sebelum lanjut ke Blok 2

- [ ] Bisa menyebutkan tiga masalah kode prosedural dan nama resminya
- [ ] Bisa menjelaskan kenapa `Pecahan b;` gagal setelah `Pecahan(int,int)` ditulis
- [ ] Bisa menjelaskan kenapa `: b_(a_ * 2)` berbahaya kalau `b_` dideklarasikan duluan
- [ ] Bisa menjelaskan kenapa `explicit` ada
- [ ] Semua member function di proyek `Pecahan`-mu sudah `const`-correct
- [ ] Proyek `Pecahan` selesai, termasuk bagian **Perubahan Requirement**
