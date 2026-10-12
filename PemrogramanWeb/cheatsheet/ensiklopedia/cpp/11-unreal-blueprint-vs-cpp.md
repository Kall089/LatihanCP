# 11 — Blueprint vs C++: kapan dan cara expose

[← GameMode dan Pawn](10-unreal-gamemode-pawn-controller.md) · [README](README.md) · [Lanjut: resep dan kesalahan →](12-resep-dan-kesalahan.md)

Blueprint dan C++ **bukan musuh**. Pola resmi Epic: C++ untuk fondasi (class, net, performa, API rapi), Blueprint untuk merangkai, tuning, FX, prototipe cepat. Keduanya memakai object model yang sama (`UCLASS`). Bukan “cheat editor”; ini alur kerja tim.

## Daftar isi

- [kapan Blueprint](#kapan-blueprint)
- [kapan C++](#kapan-c)
- [parent C++ anak Blueprint](#parent-c-anak-blueprint)
- [Blueprintable dan BlueprintType](#blueprintable-dan-blueprinttype)
- [expose property](#expose-property)
- [expose fungsi](#expose-fungsi)
- [event ke Blueprint](#event-ke-blueprint)
- [panggil Blueprint dari C++](#panggil-blueprint-dari-c)
- [panggil C++ dari Blueprint](#panggil-c-dari-blueprint)
- [TSubclassOf diisi Blueprint](#tsubclassof-diisi-blueprint)
- [soft reference asset](#soft-reference-asset)
- [UDataAsset](#udataasset)
- [Construction Script vs constructor](#construction-script-vs-constructor)
- [compile time dan Live Coding](#compile-time-dan-live-coding)
- [Blueprint nativization catatan](#blueprint-nativization-catatan)
- [pembagian kerja tim](#pembagian-kerja-tim)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## kapan Blueprint

**Tipe:** panduan kerja

**Untuk apa:** memilih BP saat iterasi visual/data lebih penting daripada kompilasi C++.

**Contoh implementasi:**

```cpp
// C++ hanya menyediakan hook; FX di Blueprint
UCLASS()
class AKoinLatihan : public AActor
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintImplementableEvent, Category = "Koin")
    void OnKoinDiambil();

    UFUNCTION(BlueprintCallable, Category = "Koin")
    void Ambil()
    {
        OnKoinDiambil();  // BP: suara, partikel, anim
        Destroy();
    }
};
```

**Yang terjadi:** programmer mengunci aturan “ambil = event + destroy”. Artis mengisi `OnKoinDiambil` tanpa membuka Visual Studio. Cocok: materi, timeline pintu, widget, level scripting, prototipe mechanic seminggu.

Blueprint unggul: tuning angka di Details, merangkai komponen, anim notify visual, UI.

**Biasanya digabungkan dengan:** `BlueprintImplementableEvent`, Timeline, AnimBP, UMG.

**Jangan:** seluruh AI kompleks + netcode hanya di Event Graph raksasa (sulit diff, sulit review). Jangan BP untuk loop ribuan actor per frame tanpa profil.

## kapan C++

**Tipe:** panduan kerja

**Untuk apa:** fondasi yang jarang berubah, performa, networking, tool, algoritma.

**Contoh implementasi:**

```cpp
UCLASS()
class UInventoriKomponen : public UActorComponent
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Toko")
    bool CobaTambah(FName Id, int32 Jumlah);

private:
    UPROPERTY()
    TMap<FName, int32> Stok;
};
```

**Yang terjadi:** aturan stok, stack max, save, replikasi — di C++ mudah diuji dan di-diff Git. Blueprint memanggil `CobaTambah` tanpa menyalin map logic di 20 graph.

Pilih C++ jika: RPC, pathfinding kustom, parser, kumpulan data besar, kode yang sama dipakai banyak class, tim butuh code review ketat.

**Biasanya digabungkan dengan:** `UFUNCTION` tipis sebagai API, tes otomatis (jika kamu setup).

**Jangan:** C++ untuk “geser lampu 5 cm” yang desainer ubah tiap jam — buang waktu compile. Jangan porting seluruh prototipe BP ke C++ tanpa butuh.

## parent C++ anak Blueprint

**Tipe:** pola proyek resmi

**Untuk apa:** class C++ = tulang; Blueprint = kulit (mesh, nilai default, event visual).

**Contoh implementasi:**

```cpp
UCLASS(Blueprintable, BlueprintType)
class ATokoCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> MappingPemain;
};
```

**Yang terjadi:** Content Browser → Blueprint Class → parent `TokoCharacter`. Di BP: assign skeletal mesh, AnimBP, IMC, kamera. GameMode `DefaultPawnClass` = `BP_TokoCharacter`, bukan class C++ telanjang (yang mesh-nya kosong).

Ini pola First Person / Third Person template Epic.

**Biasanya digabungkan dengan:** `TSubclassOf<ATokoCharacter>`, World Settings.

**Jangan:** menduplikasi class C++ hanya untuk ganti mesh — itu BP anak. Jangan parent BP ke BP ke BP 8 tingkat tanpa alasan (pecah).

## Blueprintable dan BlueprintType

**Tipe:** specifier `UCLASS` / `USTRUCT`

**Untuk apa:** `Blueprintable` = boleh jadi parent BP (actor/component). `BlueprintType` = tipe bisa dipakai sebagai variabel BP (struct, object).

**Contoh implementasi:**

```cpp
UCLASS(Blueprintable)
class APintuLatihan : public AActor
{
    GENERATED_BODY()
};

USTRUCT(BlueprintType)
struct FBarisInventori
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
    FName Id;
};
```

**Yang terjadi:** `APintuLatihan` muncul di dialog “All Classes” saat buat Blueprint. `FBarisInventori` bisa jadi variabel graph / pin. `NotBlueprintable` menyembunyikan class abstrak (`UCLASS(Abstract, NotBlueprintable)`).

**Biasanya digabungkan dengan:** `Abstract`, `meta=(DisplayName)`.

**Jangan:** `Blueprintable` pada helper yang tidak boleh di-spawn. Jangan lupa `BlueprintType` pada struct lalu heran BP tidak melihat.

## expose property

**Tipe:** pola `UPROPERTY`

**Untuk apa:** desainer mengisi angka/asset tanpa recompile.

**Contoh implementasi:**

```cpp
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pintu",
          meta = (ClampMin = "0.1", ClampMax = "10.0", ToolTip = "Detik animasi buka"))
float LamaBuka = 1.0f;

UPROPERTY(EditAnywhere, Category = "Pintu")
TObjectPtr<UCurveFloat> KurvaBuka;
```

**Yang terjadi:** slider Details 0.1–10, tooltip jelas. Kurva diisi asset. Graph BP bisa Set/Get karena `ReadWrite`. C++ membaca nilai yang sudah dituning.

Lihat file 08 untuk Visible/Edit/ReadOnly.

**Biasanya digabungkan dengan:** Category, `EditDefaultsOnly` untuk class-wide.

**Jangan:** expose 80 field tanpa kategori. Jangan `ReadWrite` pada pointer jaringan sensitif.

## expose fungsi

**Tipe:** pola `UFUNCTION`

**Untuk apa:** API yang BP panggil seperti library.

**Contoh implementasi:**

```cpp
UFUNCTION(BlueprintCallable, Category = "Toko", meta = (ToolTip = "False jika penuh"))
bool CobaTambah(FName Id, int32 Jumlah);

UFUNCTION(BlueprintPure, Category = "Toko")
int32 JumlahOf(FName Id) const;
```

**Yang terjadi:** dua node di palet Toko. `CobaTambah` punya exec pin. `JumlahOf` pure. Nama parameter menjadi label pin (`Id`, `Jumlah`).

`CallInEditor` membuat tombol di Details untuk fungsi tanpa parameter (berguna tool level).

**Biasanya digabungkan dengan:** `Category`, `UPARAM(ref)` untuk out param.

**Jangan:** fungsi 12 parameter (buat struct). Jangan `std::string` di signature UFUNCTION.

## event ke Blueprint

**Tipe:** `BlueprintImplementableEvent` / `BlueprintNativeEvent`

**Untuk apa:** C++ memicu momen; BP mengisi presentasi atau override aturan.

**Contoh implementasi:**

```cpp
UFUNCTION(BlueprintNativeEvent, Category = "Koin")
int32 HitungNilaiKoin() const;

int32 AKoinLatihan::HitungNilaiKoin_Implementation() const
{
    return NilaiDasar;
}
```

**Yang terjadi:** default C++ mengembalikan `NilaiDasar`. BP anak bisa override jadi 2× di malam hari. Gameplay tetap punya fallback jika lupa override.

Event `OnKoinDiambil` Implementable = murni presentasi.

**Biasanya digabungkan dengan:** file 08, FX.

**Jangan:** event tanpa nama jelas. Jangan NativeEvent tanpa `_Implementation`.

## panggil Blueprint dari C++

**Tipe:** pola (event / ProcessEvent / interface)

**Untuk apa:** menjalankan graph yang tidak ada di C++.

**Contoh implementasi:**

```cpp
// 1) Paling rapi: deklarasi event
OnKoinDiambil();  // ImplementableEvent

// 2) Interface Blueprint
if (Other->Implements<UInteraksiToko>())
{
    IInteraksiToko::Execute_MulaiInteraksi(Other, this);
}
```

**Yang terjadi:** (1) stub C++ memanggil graph jika ada. (2) interface `UINTERFACE` + `MulaiInteraksi` bisa diimplementasi BP atau C++; `Execute_` aman. Menghindari `FindFunction` string rapuh.

Ada `UFunction*` + `ProcessEvent` — last resort, rawan typo.

**Biasanya digabungkan dengan:** `UINTERFACE`, `BlueprintImplementableEvent`.

**Jangan:** `ProcessEvent` nama string di Tick. Jangan mengandalkan graph jika dedicated server tanpa BP loaded (atur project).

## panggil C++ dari Blueprint

**Tipe:** pola (node Callable / parent call)

**Untuk apa:** graph memanggil fondasi.

**Contoh implementasi:**

```cpp
UFUNCTION(BlueprintCallable, Category = "Toko")
void Ambil();
```

Di Event Graph: node `Ambil` → exec ke destroy/FX. Atau Event `BeginPlay` (engine) → node C++.

`Call Parent Function` pada override NativeEvent menjalankan `_Implementation`.

**Yang terjadi:** satu sumber kebenaran di C++, BP merangkai kapan dipanggil (overlap, tombol UI).

**Biasanya digabungkan dengan:** overlap BP, Widget button OnClicked.

**Jangan:** menyalin isi `Ambil` ke graph “supaya lebih cepat” lalu lupa update C++.

## TSubclassOf diisi Blueprint

**Tipe:** class template UHT

**Untuk apa:** C++ spawn “jenis” yang dipilih desainer (BP anak).

**Contoh implementasi:**

```cpp
UPROPERTY(EditAnywhere, Category = "Spawn")
TSubclassOf<AKoinLatihan> KelasKoin;

void ASpawnerKoin::SpawnSatu()
{
    if (UWorld* W = GetWorld(); W && KelasKoin)
    {
        W->SpawnActor<AKoinLatihan>(KelasKoin, GetActorTransform());
    }
}
```

**Yang terjadi:** Details hanya menerima `AKoinLatihan` atau anaknya (`BP_KoinEmas`). Spawn memakai class BP: mesh/FX dari BP, fungsi C++ dari parent. `TSubclassOf<AActor>` terlalu longgar.

**Biasanya digabungkan dengan:** projectile, pickup, AI pawn class.

**Jangan:** `UClass*` mentah tanpa `TSubclassOf` (kurang aman di editor). Jangan hardcode `StaticClass()` jika artis harus ganti BP.

## soft reference asset

**Tipe:** `TSoftObjectPtr` / `TSoftClassPtr`

**Untuk apa:** merujuk asset **tanpa** selalu me-load ke memori (level besar).

**Contoh implementasi:**

```cpp
UPROPERTY(EditAnywhere, Category = "Toko")
TSoftObjectPtr<UStaticMesh> MeshOpsional;

void AKotakProp::MuatMesh()
{
    if (UStaticMesh* M = MeshOpsional.LoadSynchronous())
    {
        Mesh->SetStaticMesh(M);
    }
}
```

**Yang terjadi:** map tidak memaksa mesh ter-load sampai `LoadSynchronous` / async stream. `TObjectPtr<UStaticMesh>` keras: buka level = load mesh. Soft cocok katalog banyak item.

Ada `FStreamableManager` untuk async.

**Biasanya digabungkan dengan:** `UDataAsset` katalog, World Partition.

**Jangan:** `LoadSynchronous` di Tick. Jangan soft ptr lalu lupa load (mesh null).

## UDataAsset

**Tipe:** class data di Content Browser

**Untuk apa:** data desain terpisah dari actor: harga barang, dialog, tabel wave.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataBarang.generated.h"

UCLASS(BlueprintType)
class UDataBarang : public UPrimaryDataAsset
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko")
    FText NamaTampil;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko")
    int32 Harga = 100;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko")
    TSoftObjectPtr<UTexture2D> Ikon;
};
```

**Yang terjadi:** buat asset `DA_Buku` di Content, isi harga/ikon. Actor toko punya `UPROPERTY UDataBarang*`. Ganti harga tanpa recompile C++ dan tanpa membuka Blueprint actor.

`UPrimaryDataAsset` + Asset Manager untuk bundle/soft.

**Biasanya digabungkan dengan:** `TMap<FName, UDataBarang*>`, UI.

**Jangan:** menaruh data 200 item sebagai `UPROPERTY` di GameMode. Jangan `UDataAsset` untuk object yang harus tick.

## Construction Script vs constructor

**Tipe:** dua tahap “saat dibuat di editor”

**Untuk apa:** constructor C++ = komponen default. Construction Script BP = merakit berdasarkan property yang desainer geser *di viewport* (tangga N anak, pagar).

**Contoh implementasi:**

```cpp
ATiangBendera::ATiangBendera()
{
    Akar = CreateDefaultSubobject<USceneComponent>(TEXT("Akar"));
    SetRootComponent(Akar);
}

virtual void OnConstruction(const FTransform& Transform) override
{
    Super::OnConstruction(Transform);
    // update preview editor saat property berubah
}
```

**Yang terjadi:** menggeser instance di Editor memanggil Construction Script / `OnConstruction`, **bukan** `BeginPlay`. Cocok preview. Jangan spawn gameplay di construction (berantakan di editor).

**Biasanya digabungkan dengan:** `EditAnywhere` yang memengaruhi preview, Instanced Static Mesh.

**Jangan:** logic match di Construction Script. Jangan `SpawnActor` di `OnConstruction` tanpa `if (!GetWorld()->IsGameWorld())` sadar.

## compile time dan Live Coding

**Tipe:** alur kerja Editor

**Untuk apa:** memilih kapan tutup Editor vs Live Coding.

**Contoh implementasi:**

Tidak ada kode. Alur:

1. Ubah `.cpp` kecil (isi fungsi) → **Live Coding** / Compile di Editor sering cukup.
2. Ubah `UCLASS` specifier, parent class, tambah `UFUNCTION` baru, ubah `Build.cs` → sering **tutup Editor**, compile IDE, buka lagi.
3. Ubah Blueprint saja → compile BP (kuning), tanpa C++.

**Yang terjadi:** Live Coding gagal atau aneh setelah ganti header besar — bukan “C++ rusak”, restart. Hot Reload lama lebih rapuh daripada Live Coding UE5; tetap restart jika ragu.

**Biasanya digabungkan dengan:** iterasi API vs iterasi angka (angka = Details, tanpa compile).

**Jangan:** 40 kali Live Coding setelah merombak hierarki. Jangan edit `.generated.h`.

## Blueprint nativization catatan

**Tipe:** catatan versi

**Untuk apa:** memahami bahwa “compile BP ke C++” (nativization UE4) **bukan** alur utama UE5.

**Contoh implementasi:**

Tidak dipakai. Di UE5, Blueprint tetap interpreted/VM + optimasi engine. Jangan mengandalkan nativization UE4. Performa: kurangi Tick BP, pindahkan loop berat ke C++, pakai event.

**Yang terjadi:** jika kamu baca tutorial UE4 “nativize for ship”, abaikan untuk proyek UE5 baru kecuali dokumentasi versimu secara eksplisit masih mendukung.

**Biasanya digabungkan dengan:** profil (`stat unit`, Insights).

**Jangan:** menunda pindah logic berat ke C++ karena “nanti di-nativize”.

## pembagian kerja tim

**Tipe:** resep kolaborasi

**Untuk apa:** menghindari konflik Git: BP binary vs C++ teks.

**Contoh implementasi:**

| Orang | Sentuh |
| --- | --- |
| Programmer | `.h` `.cpp` `Build.cs`, API `UFUNCTION` |
| Designer | Blueprint anak, DataAsset, IMC, level |
| Art | mesh, material, AnimBP |

Konflik BP sulit di-merge. Pecah Blueprint (bukan satu `BP_God` 800 node). C++ API stabil mengurangi edit BP massal.

**Yang terjadi:** programmer menambah `CobaTambah` → desainer pakai node baru tanpa rebase class. Git merengek lebih jarang.

**Biasanya digabungkan dengan:** parent C++ + anak BP, DataAsset.

**Jangan:** semua orang mengedit `BP_Character` raksasa bersamaan. Jangan menyimpan level + ganti parent C++ tanpa komunikasi (reset property).

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** “node tidak muncul”, “spawn class kosong”, “FX tidak jalan”.

**Contoh implementasi:**

```cpp
UFUNCTION(BlueprintCallable, Category = "Toko")
void Ambil();  // tanpa ini, graph tidak melihat Ambil
```

**Yang terjadi:** fungsi C++ biasa tidak otomatis jadi node. Property tanpa `BlueprintRead*` tidak jadi pin. Event Implementable tidak wajib diisi — jika FX “tidak ada”, cek BP anak override, dan GameMode memakai **BP anak** bukan C++ parent.

Spawn `StaticClass()` parent → mesh default kosong. Isi `TSubclassOf` dengan BP.

**Biasanya digabungkan dengan:** file 08 specifier, file 10 DefaultPawnClass.

**Jangan:** mencari node dengan nama C++ raw jika `meta=DisplayName` beda. Jangan lupa compile BP setelah ubah parent header (refresh node).
