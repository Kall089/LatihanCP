# 08 — UPROPERTY, UFUNCTION, dan specifier

[← UObject dan Actor](07-unreal-uobject-actor.md) · [README](README.md) · [Lanjut: komponen dan input →](09-unreal-komponen-input.md)

Reflection Unreal tidak membaca C++ mentah. Field yang ingin terlihat di Details / Blueprint / GC harus `UPROPERTY`. Fungsi yang ingin dipanggil dari Blueprint atau direplikasi harus `UFUNCTION`. Ini **API publik** editor dan networking Unreal, bukan cara meretas game.

## Daftar isi

- [UPROPERTY](#uproperty)
- [VisibleAnywhere](#visibleanywhere)
- [EditAnywhere](#editanywhere)
- [EditDefaultsOnly](#editdefaultsonly)
- [EditInstanceOnly](#editinstanceonly)
- [BlueprintReadOnly](#blueprintreadonly)
- [BlueprintReadWrite](#blueprintreadwrite)
- [Category](#category)
- [meta AllowPrivateAccess](#meta-allowprivateaccess)
- [Transient](#transient)
- [Replicated](#replicated)
- [TArray TMap sebagai UPROPERTY](#tarray-tmap-sebagai-uproperty)
- [UFUNCTION BlueprintCallable](#ufunction-blueprintcallable)
- [BlueprintPure](#blueprintpure)
- [BlueprintImplementableEvent](#blueprintimplementableevent)
- [BlueprintNativeEvent](#blueprintnativeevent)
- [UFUNCTION Server](#ufunction-server)
- [Client dan NetMulticast](#client-dan-netmulticast)
- [Reliable](#reliable)
- [USTRUCT](#ustruct)
- [UENUM](#uenum)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## UPROPERTY

**Tipe:** macro refleksi field

**Untuk apa:** mendaftarkan member ke UHT: tampil di editor, terlihat Blueprint (jika specifier), dan **dihitung sebagai referensi GC** jika tipenya `UObject*`.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PetiBarang.generated.h"

UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko")
    int32 Kapasitas = 8;

    UPROPERTY()
    TObjectPtr<UObject> CadanganGC;
};
```

**Yang terjadi:** `Kapasitas` muncul di Details, bisa diubah desainer, Blueprint hanya baca. `CadanganGC` tidak tampil editor (tidak ada specifier tampilan) tetapi **tetap** menahan object dari GC. Field `UObject*` **tanpa** `UPROPERTY` tidak menahan GC.

Tipe yang didukung: numerik Unreal (`int32`, `float`), `bool`, `FString`, `FName`, `FText`, `FVector`, enum `UENUM`, `USTRUCT`, `TArray`/`TMap`/`TSet` dari tipe itu, `TSubclassOf`, `TSoftObjectPtr`, `TObjectPtr`.

**Biasanya digabungkan dengan:** specifier di bawah, `Category`, komponen.

**Jangan:** `UPROPERTY` pada `std::string` / `std::vector`. Jangan pointer `UObject` penting tanpa `UPROPERTY`. Jangan macro di field `static` sembarangan.

## VisibleAnywhere

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** terlihat di Details pada CDO **dan** instance, tetapi **tidak bisa diketik** (read-only di editor). Cocok komponen yang dibuat di constructor.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LampuJalan.generated.h"

class UStaticMeshComponent;

UCLASS()
class ALampuJalan : public AActor
{
    GENERATED_BODY()

public:
    ALampuJalan();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<UStaticMeshComponent> MeshLampu;
};
```

**Yang terjadi:** di Details ada kategori Komponen, `MeshLampu` terlihat (bisa expand collision/mesh), tetapi kamu tidak “mengganti pointer”-nya seperti property biasa. Ini pola resmi Epic untuk `CreateDefaultSubobject`.

`VisibleDefaultsOnly` / `VisibleInstanceOnly` membatasi di CDO saja atau instance saja.

**Biasanya digabungkan dengan:** `USceneComponent`, `UStaticMeshComponent`.

**Jangan:** `VisibleAnywhere` pada angka yang desainer harus ubah — pakai `EditAnywhere`. Jangan mengira Visible = tersembunyi dari Blueprint (itu `BlueprintRead*`).

## EditAnywhere

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** desainer mengubah nilai di **default class** dan di **instance** yang ditaruh di level.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PintuLatihan.generated.h"

UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Pintu")
    float LamaBuka = 1.2f;

    UPROPERTY(EditAnywhere, Category = "Pintu")
    FName TagKunci = TEXT("KunciMerah");
};
```

**Yang terjadi:** tiap pintu di peta boleh `LamaBuka` berbeda. Mengubah default Blueprint mengubah instance yang belum di-override. Ini specifier paling sering untuk knobs desain.

**Biasanya digabungkan dengan:** `BlueprintReadWrite` atau `BlueprintReadOnly`, `Category`, `ClampMin` meta.

**Jangan:** `EditAnywhere` pada pointer yang harus diisi runtime saja (bingung desainer). Jangan angka tanpa satuan di tooltip — tambah `meta=(ToolTip="Detik")`.

## EditDefaultsOnly

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** hanya diubah di default class / Blueprint CDO, **bukan** per instance di level. Cocok: kelas projectile, kurva damage, setting yang harus seragam.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Pintu")
    TSubclassOf<AActor> EfekBukaClass;
};
```

**Yang terjadi:** di Class Defaults kamu pilih class efek. Instance di level tidak menampilkan (atau tidak mengizinkan) override field ini, tergantung tampilan Editor — nilai sama untuk semua instance class itu kecuali kamu memakai pola lain.

**Biasanya digabungkan dengan:** `TSubclassOf`, data yang “satu per jenis”.

**Jangan:** `EditDefaultsOnly` pada posisi per-instance (pintu A vs B). Jangan campur dengan nilai yang level-designer harus bedakan.

## EditInstanceOnly

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** hanya di instance yang ditaruh (atau spawn yang kamu set), bukan mengubah CDO. Cocok: ID peti *khusus level ini*.

**Contoh implementasi:**

```cpp
UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditInstanceOnly, Category = "Toko")
    FName IdPetiDiLevel;
};
```

**Yang terjadi:** menaruh dua peti, masing-masing ID berbeda. Mengubah Class Defaults tidak menyediakan field ini (atau tidak untuk diedit di situ). Mencegah “saya ubah default malah semua peti ketimpa ID”.

**Biasanya digabungkan dengan:** save per-instance, referensi actor di level (`AActor*` EditInstanceOnly).

**Jangan:** `EditInstanceOnly` pada setting yang harus sama di semua instance — sulit dijaga.

## BlueprintReadOnly

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** graph Blueprint bisa **membaca** nilai, tidak bisa menulis node Set.

**Contoh implementasi:**

```cpp
UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Toko")
    int32 JumlahIsi = 0;
};
```

**Yang terjadi:** Blueprint anak bisa `Get Jumlah Isi` untuk UI, tetapi tidak menimpa dari graph. C++ tetap bisa `JumlahIsi = 3`. Editor visibility terpisah: di sini VisibleAnywhere (read-only di Details).

**Biasanya digabungkan dengan:** state yang hanya berubah dari C++ / server.

**Jangan:** `BlueprintReadOnly` + berharap desainer mengisi di graph. Jangan lupa tanpa `BlueprintRead*` property **tidak** muncul di Blueprint meski `EditAnywhere`.

## BlueprintReadWrite

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** Blueprint boleh Get dan Set.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pintu")
    bool bTerkunci = true;
};
```

**Yang terjadi:** Event Graph bisa `Set b Terkunci`. Kuat untuk prototipe; mudah diubah dari banyak tempat — disiplin nama dan komentar.

**Biasanya digabungkan dengan:** `EditAnywhere`, desain cepat, prototyping.

**Jangan:** semua field `ReadWrite` tanpa aturan. Jangan `ReadWrite` pada data server-kritis tanpa replikasi / authority.

## Category

**Tipe:** specifier organisasi Details / palet Blueprint

**Untuk apa:** mengelompokkan “Toko|Stok” atau `Pintu`. Subkategori dengan `|`.

**Contoh implementasi:**

```cpp
UPROPERTY(EditAnywhere, Category = "Toko|Harga")
int32 HargaDasar = 1000;

UPROPERTY(EditAnywhere, Category = "Toko|Harga")
float Multiplier = 1.f;
```

**Yang terjadi:** Details menampilkan grup Toko, sub Harga. Fungsi `UFUNCTION(..., Category="Toko")` muncul di palet dengan kategori itu.

**Biasanya digabungkan dengan:** semua property yang tampil.

**Jangan:** 30 kategori acak. Jangan nama beda tipis (`Toko` vs `toko`) — jadi dua grup.

## meta AllowPrivateAccess

**Tipe:** meta specifier

**Untuk apa:** field `private` tetap bisa diakses Blueprint / Details sesuai `BlueprintRead*` / Edit, tanpa membuatnya `public` di C++.

**Contoh implementasi:**

```cpp
UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko",
              meta = (AllowPrivateAccess = "true"))
    int32 KodeRahasiaEditor = 0;
};
```

**Yang terjadi:** C++ luar class tidak bisa baca `KodeRahasiaEditor`. Blueprint/Editor bisa sesuai specifier. Pola resmi banyak template Epic (`ACharacter` components).

**Biasanya digabungkan dengan:** komponen `private` + `VisibleAnywhere`.

**Jangan:** mengira ini keamanan multiplayer (client masih bisa lihat property jika direplikasi/exposed). Jangan typo `"ture"`.

## Transient

**Tipe:** specifier `UPROPERTY`

**Untuk apa:** **tidak** disimpan ke disk (level/ark) dan tidak di-serialize default. Nilai runtime: cache, timer state.

**Contoh implementasi:**

```cpp
UPROPERTY(Transient)
TObjectPtr<AActor> CachePemainTerdekat;
```

**Yang terjadi:** pointer dihitung saat main, tidak tertanam di file map. Setelah reload editor, field kosong (kecuali kamu isi lagi di `BeginPlay`).

**Biasanya digabungkan dengan:** cache, `TWeakObjectPtr` (alternatif), flag runtime.

**Jangan:** `Transient` pada data desain yang harus tersimpan. Jangan mengira Transient = tidak di-GC (tetap `UPROPERTY` menahan jika `UObject*`).

## Replicated

**Tipe:** specifier jaringan

**Untuk apa:** server mengirim nilai ke client yang relevan. Ini API replikasi resmi Unreal.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BenderaSkor.generated.h"

UCLASS()
class ABenderaSkor : public AActor
{
    GENERATED_BODY()

public:
    ABenderaSkor();

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Skor")
    int32 Skor = 0;

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
```

```cpp
#include "BenderaSkor.h"
#include "Net/UnrealNetwork.h"

ABenderaSkor::ABenderaSkor()
{
    bReplicates = true;
}

void ABenderaSkor::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ABenderaSkor, Skor);
}
```

**Yang terjadi:** actor mereplikasi. Perubahan `Skor` di server sampai ke client. Tanpa `bReplicates`, `GetLifetimeReplicatedProps`, dan `DOREPLIFETIME`, specifier `Replicated` tidak cukup. `ReplicatedUsing = OnRep_Skor` memanggil fungsi saat nilai tiba (untuk FX/UI).

Ini **bukan** cara menyuntik skor ke game orang; ini cara membuat game milikmu sinkron.

**Biasanya digabungkan dengan:** `HasAuthority`, `UFUNCTION(Server)`, GameState.

**Jangan:** mereplikasi pointer besar tiap frame tanpa perlu. Jangan ubah `Skor` di client lalu heran di-reset. Jangan lupa `DOREPLIFETIME`.

## TArray TMap sebagai UPROPERTY

**Tipe:** kontainer yang didukung UHT

**Untuk apa:** daftar/kamus yang bisa diedit di Details dan di-GC dengan benar.

**Contoh implementasi:**

```cpp
UPROPERTY(EditAnywhere, Category = "Toko")
TArray<FName> DaftarBarang;

UPROPERTY(EditAnywhere, Category = "Toko")
TMap<FName, int32> StokPerNama;

UPROPERTY(EditAnywhere, Category = "Toko")
TArray<TObjectPtr<AActor>> PintuTerkait;
```

**Yang terjadi:** desainer menambah elemen di Details. `TArray<AActor*>` menahan referensi actor (hati-hati hard reference). `std::vector` tidak muncul dan tidak aman untuk GC.

**Biasanya digabungkan dengan:** `Find`, `Add`, loop `for (int32 i = 0; i < Arr.Num(); ++i)`.

**Jangan:** `TArray<std::string>`. Jangan array `UObject*` tanpa `UPROPERTY`.

## UFUNCTION BlueprintCallable

**Tipe:** macro + specifier fungsi

**Untuk apa:** node yang bisa dipanggil dari Event Graph / fungsi Blueprint.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Pintu")
    void BukaPintu()
    {
        bTerkunci = false;
        UE_LOG(LogTemp, Log, TEXT("Pintu dibuka"));
    }

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pintu")
    bool bTerkunci = true;
};
```

**Yang terjadi:** di Blueprint, palet menampilkan `Buka Pintu`. Memanggilnya menjalankan C++. Parameter menjadi pin. `TArray` sebagai parameter butuh aturan (`UPARAM` / const ref).

**Biasanya digabungkan dengan:** `Category`, `meta=(ToolTip=...)`, `BlueprintPure` untuk getter.

**Jangan:** `BlueprintCallable` pada fungsi `Tick` internal. Jangan tipe parameter yang UHT tidak kenal (`std::string`).

## BlueprintPure

**Tipe:** specifier `UFUNCTION`

**Untuk apa:** node **tanpa execution pin** (seperti getter), dianggap tidak punya side effect.

**Contoh implementasi:**

```cpp
UFUNCTION(BlueprintPure, Category = "Pintu")
bool ApakahTerkunci() const
{
    return bTerkunci;
}
```

**Yang terjadi:** node hijau/pure, bisa dicabang ke banyak Get tanpa urutan exec. Jangan isi `BukaPintu` sebagai Pure — side effect bisa dipanggil berkali-kali tak terduga.

**Biasanya digabungkan dengan:** getter, hitung sederhana.

**Jangan:** Pure + mengubah state. Jangan query mahal sebagai Pure di graph yang dievaluasi sering.

## BlueprintImplementableEvent

**Tipe:** specifier `UFUNCTION`

**Untuk apa:** C++ **mendeklarasikan** event; implementasinya di Blueprint, **tanpa** body C++.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Pintu")
    void OnPintuTerbuka();

    UFUNCTION(BlueprintCallable, Category = "Pintu")
    void BukaPintu()
    {
        bTerkunci = false;
        OnPintuTerbuka();
    }

    UPROPERTY(BlueprintReadOnly, Category = "Pintu")
    bool bTerkunci = true;
};
```

**Yang terjadi:** `BukaPintu` (C++ atau BP) memanggil `OnPintuTerbuka`. Jika Blueprint tidak mengimplementasikan, panggilan no-op (aman). Desainer menambah suara/animasi tanpa recompile C++.

Tidak boleh menulis definisi C++ untuk fungsi itu (UHT yang membuat stub).

**Biasanya digabungkan dengan:** FX, UI, event desain.

**Jangan:** logika gameplay wajib hanya di event ini jika C++ juga harus jalan di dedicated server tanpa BP — pertimbangkan `BlueprintNativeEvent`.

## BlueprintNativeEvent

**Tipe:** specifier `UFUNCTION`

**Untuk apa:** ada default C++ (`Nama_Implementation`), Blueprint boleh override.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Pintu")
    void TerapkanWarna();

    void TerapkanWarna_Implementation()
    {
        UE_LOG(LogTemp, Log, TEXT("Warna default C++"));
    }
};
```

**Yang terjadi:** jika BP tidak override, `_Implementation` jalan. Jika BP override, graph BP jalan; bisa `Call Parent` untuk tetap menjalankan C++. Pola resmi “default + kustomisasi”.

**Biasanya digabungkan dengan:** damage hook, filter, setup visual.

**Jangan:** menulis `TerapkanWarna` body tanpa `_Implementation`. Jangan lupa `BlueprintCallable` jika ingin dipanggil dari graph (NativeEvent bisa dipanggil dari C++ langsung).

## UFUNCTION Server

**Tipe:** specifier RPC (jalankan di server)

**Untuk apa:** client **meminta** server menjalankan fungsi. Validasi dan perubahan state resmi di server.

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    APintuLatihan();

    UFUNCTION(Server, Reliable, WithValidation)
    void ServerBukaPintu();

    void ServerBukaPintu_Implementation()
    {
        bTerkunci = false;
    }

    bool ServerBukaPintu_Validate()
    {
        return true;  // latihan: selalu terima; produksi: cek jarak/item
    }

    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Pintu")
    bool bTerkunci = true;
};
```

```cpp
APintuLatihan::APintuLatihan()
{
    bReplicates = true;
}
```

**Yang terjadi:** pemain di client memanggil `ServerBukaPintu()`. Engine mengirim RPC ke server, `_Validate` lalu `_Implementation` jalan di server, `bTerkunci` berubah dan mereplikasi. `WithValidation` wajib di beberapa versi/pola Server RPC; di UE5 modern bisa tanpa, tetapi `_Implementation` tetap wajib.

Ini cara **membuat** game multiplayer, bukan menembus server orang.

**Biasanya digabungkan dengan:** `Reliable`, `HasAuthority`, PlayerController RPC (sering lebih tepat daripada actor sembarangan).

**Jangan:** mempercayai argumen client tanpa cek. Jangan RPC tiap Tick. Jangan Server RPC pada actor yang tidak `bReplicates` / tidak punya koneksi.

## Client dan NetMulticast

**Tipe:** specifier RPC

**Untuk apa:** `Client` = server menyuruh **satu** client (punya owner connection). `NetMulticast` = server menyiarkan ke semua yang relevan (FX).

**Contoh implementasi:**

```cpp
UFUNCTION(Client, Reliable)
void ClientTampilPesan(const FString& Pesan);

void AContohController::ClientTampilPesan_Implementation(const FString& Pesan)
{
    UE_LOG(LogTemp, Log, TEXT("UI: %s"), *Pesan);
}

UFUNCTION(NetMulticast, Unreliable)
void MulticastMainkanSuara();

void APintuLatihan::MulticastMainkanSuara_Implementation()
{
    // putar SFX lokal di tiap mesin
}
```

**Yang terjadi:** server panggil `ClientTampilPesan` pada PlayerController pemilik — hanya mesin itu yang log/UI. `NetMulticast` dari server memicu implementasi di server+client untuk efek. Multicast **unreliable** cocok suara yang boleh hilang jika paket drop.

Jangan mengandalkan multicast untuk mengubah skor (pakai replicated + authority).

**Biasanya digabungkan dengan:** FX, HUD, `Unreliable` untuk efek.

**Jangan:** multicast state penting. Jangan Client RPC dari client. Jangan spam.

## Reliable

**Tipe:** specifier RPC

**Untuk apa:** `Reliable` = engine mengulang sampai sampai (atau timeout). `Unreliable` = fire-and-forget.

**Contoh implementasi:**

```cpp
UFUNCTION(Server, Reliable)
void ServerKonfirmasiBeli(int32 IdBarang);

UFUNCTION(NetMulticast, Unreliable)
void MulticastPercikanDebu(FVector Lokasi);
```

**Yang terjadi:** beli item harus sampai (Reliable). Debu boleh hilang (Unreliable) agar tidak menumpuk antrian. Terlalu banyak Reliable memenuhi bandwidth.

**Biasanya digabungkan dengan:** Server RPC gameplay vs multicast VFX.

**Jangan:** semua RPC Reliable “supaya aman”. Jangan Unreliable untuk inventory.

## USTRUCT

**Tipe:** macro struct direfleksikan

**Untuk apa:** kelompok field yang bisa `UPROPERTY`, dikirim Blueprint, disimpan.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "BarisInventori.generated.h"

USTRUCT(BlueprintType)
struct FBarisInventori
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
    FName IdBarang;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
    int32 Jumlah = 1;
};
```

**Yang terjadi:** `TArray<FBarisInventori>` bisa diedit di Details. `BlueprintType` membuat BP melihat struct. Tanpa `GENERATED_BODY` / `generated.h`, UHT gagal.

`USTRUCT` **bukan** `UObject`: tidak di-GC sendiri, tidak `NewObject`. Disalin by value.

**Biasanya digabungkan dengan:** `TArray`, save game, tabel.

**Jangan:** `USTRUCT` berisi `std::vector`. Jangan pointer `UObject` di struct tanpa `UPROPERTY` jika array-nya `UPROPERTY` — field dalam struct juga harus `UPROPERTY` agar GC/editor benar.

## UENUM

**Tipe:** macro enumerasi Blueprint

**Untuk apa:** pilihan tetap di Details (dropdown) dan graph.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "EStatusPesanan.generated.h"

UENUM(BlueprintType)
enum class EStatusPesanan : uint8
{
    Draf UMETA(DisplayName = "Draf"),
    Dibayar UMETA(DisplayName = "Dibayar"),
    Selesai UMETA(DisplayName = "Selesai")
};
```

**Yang terjadi:** property `EStatusPesanan Status` tampil dropdown. Underlying `uint8` wajib untuk banyak jalur UHT. `UMETA(Hidden)` menyembunyikan nilai.

**Biasanya digabungkan dengan:** `switch`, `UPROPERTY`, state.

**Jangan:** `enum` lama tanpa `enum class`. Jangan underlying `int` jika UHT menolak — pakai `uint8`.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menyingkat “tidak muncul di Blueprint / tidak mereplikasi / GC makan object”.

**Contoh implementasi:**

```cpp
UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

public:
    // Salah: tidak UPROPERTY, GC bisa memungut
    UStatistikToko* StatistikMentah;

    // Benar
    UPROPERTY()
    TObjectPtr<UStatistikToko> StatistikAman;

    // Salah harapan: EditAnywhere tanpa BlueprintRead* → tidak ada pin BP
    UPROPERTY(EditAnywhere, Category = "Toko")
    int32 HanyaDiDetails = 0;
};
```

**Yang terjadi:** `StatistikMentah` raw tidak menahan GC. `HanyaDiDetails` bisa diedit di Editor tetapi graph BP tidak melihatnya. Tambah `BlueprintReadWrite`/`ReadOnly` jika BP perlu.

**Biasanya digabungkan dengan:** file 07 GC, file 11 expose ke BP.

**Jangan:** lupa `DOREPLIFETIME`; `std::` di UPROPERTY; Server RPC tanpa `_Implementation`; Pure dengan side effect.
