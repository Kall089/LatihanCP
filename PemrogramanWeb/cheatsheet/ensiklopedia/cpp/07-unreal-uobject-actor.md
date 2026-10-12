# 07 — Unreal: UObject, AActor, BeginPlay, Tick, Spawn

[← Memori](06-memory-smart-pointer.md) · [README](README.md) · [Lanjut: UPROPERTY dan UFUNCTION →](08-unreal-uproperty-ufunction.md)

Unreal membangun dunia dari **objek** yang dikenali *reflection* dan *garbage collector*. Puncak yang kamu taruh di level adalah **Actor**. File ini memakai **API publik** engine: `UObject`, `AActor`, `UWorld::SpawnActor`. Bukan cheat, inject, atau memodifikasi game orang lain.

Contoh di sini adalah class Unreal yang masuk akal (header + method). Compile lewat Unreal Editor / IDE, bukan `g++`.

## Daftar isi

- [UObject](#uobject)
- [UCLASS](#uclass)
- [GENERATED_BODY](#generated_body)
- [AActor](#aactor)
- [constructor AActor](#constructor-aactor)
- [BeginPlay](#beginplay)
- [Tick](#tick)
- [EndPlay](#endplay)
- [Destroy](#destroy)
- [SpawnActor](#spawnactor)
- [GetWorld](#getworld)
- [FVector FRotator FTransform](#fvector-frotator-ftransform)
- [SetActorLocation](#setactorlocation)
- [Tags dan ActorHasTag](#tags-dan-actorhastag)
- [IsValid](#isvalid)
- [HasAuthority](#hasauthority)
- [NewObject](#newobject)
- [Cast Unreal](#cast-unreal)
- [UE_LOG](#ue_log)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## UObject

**Tipe:** class (akar hampir semua object Unreal yang direfleksikan)

**Untuk apa:** mendapat nama, outer, garbage collection, `Cast`, `IsValid`, dan kemampuan `UPROPERTY`/`UFUNCTION` jika class-mu `UCLASS`.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "StatistikToko.generated.h"

UCLASS(BlueprintType)
class UStatistikToko : public UObject
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
    int32 JumlahTransaksi = 0;

    UFUNCTION(BlueprintCallable, Category = "Toko")
    void TambahTransaksi()
    {
        ++JumlahTransaksi;
    }
};
```

**Yang terjadi:** `UStatistikToko` adalah data object, **bukan** actor — tidak punya lokasi di dunia, tidak muncul di Outliner sebagai mesh. Kamu membuatnya dengan `NewObject<UStatistikToko>(this)` dari actor atau subsystem. GC memungutnya jika tidak ada `UPROPERTY` / outer yang menahan.

Hampir semua class engine (`UActorComponent`, `AActor`, `UWorld`) mewarisi `UObject` secara langsung atau tidak.

**Biasanya digabungkan dengan:** `NewObject`, `UPROPERTY` pointer, `UDataAsset` (data di Content Browser).

**Jangan:** `new UStatistikToko`. Jangan `delete`. Jangan mengira `UObject` otomatis ter-tick — hanya actor/component yang kamu nyalakan.

## UCLASS

**Tipe:** macro Unreal Header Tool

**Untuk apa:** menandai class agar UHT menghasilkan data refleksi: Blueprint bisa melihat, GC mengerti field, specifier (`abstract`, `Blueprintable`) berlaku.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PapanNama.generated.h"

UCLASS(Blueprintable)
class APapanNama : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Toko")
    FString TeksPapan = TEXT("Toko Belajar");
};
```

**Yang terjadi:** tanpa `UCLASS`, `APapanNama` hanyalah class C++ biasa — tidak muncul di dialog “New Blueprint”, `UPROPERTY` tidak di-parse. `Blueprintable` mengizinkan desainer membuat Blueprint anak. Default banyak actor sudah blueprintable.

Specifier sering: `abstract` (tidak di-spawn langsung), `Blueprintable` / `NotBlueprintable`, `hidecategories`, `meta=(DisplayName=...)`.

**Biasanya digabungkan dengan:** `GENERATED_BODY`, `*.generated.h` sebagai include **terakhir**.

**Jangan:** `UCLASS` pada class yang tidak mewarisi `UObject`. Jangan lupa modul di `Build.cs`. Jangan merapikan macro sampai pecah baris aneh yang UHT tidak paham (tetap satu `UCLASS(...)`).

## GENERATED_BODY

**Tipe:** macro (wajib di class `UCLASS` / `USTRUCT` / `UINTERFACE`)

**Untuk apa:** menyisipkan deklarasi yang ditulis UHT: `Super` typedef, helper reflection, constructor generated.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LampuTanda.generated.h"

UCLASS()
class ALampuTanda : public AActor
{
    GENERATED_BODY()

public:
    ALampuTanda();
};
```

```cpp
#include "LampuTanda.h"

ALampuTanda::ALampuTanda()
{
    PrimaryActorTick.bCanEverTick = false;
}
```

**Yang terjadi:** compile Unreal menjalankan UHT, menulis `LampuTanda.generated.h`. `GENERATED_BODY()` mengisi bagian class. Tanpa ini: error panjang tentang missing generated code. `Super::` tersedia karena macro.

Dulu ada `GENERATED_UCLASS_BODY()` — kode baru memakai `GENERATED_BODY()`.

**Biasanya digabungkan dengan:** include `Nama.generated.h` terakhir, constructor, `UPROPERTY`.

**Jangan:** menaruh kode di antara `UCLASS()` dan class yang membingungkan UHT. Jangan mengedit file `.generated.h`. Jangan `GENERATED_BODY` di class non-UHT.

## AActor

**Tipe:** class (object yang bisa ada di `UWorld`)

**Untuk apa:** benda di level: kotak, pintu, trigger, karakter (lewat turunan). Punya transform, komponen, lifespan, replikasi opsional.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KoinLatihan.generated.h"

UCLASS()
class AKoinLatihan : public AActor
{
    GENERATED_BODY()

public:
    AKoinLatihan();

    UPROPERTY(VisibleAnywhere, Category = "Koin")
    TObjectPtr<USceneComponent> Akar;
};
```

```cpp
#include "KoinLatihan.h"
#include "Components/SceneComponent.h"

AKoinLatihan::AKoinLatihan()
{
    PrimaryActorTick.bCanEverTick = false;
    Akar = CreateDefaultSubobject<USceneComponent>(TEXT("Akar"));
    SetRootComponent(Akar);
}
```

**Yang terjadi:** actor punya root component sehingga punya lokasi di dunia. Di Editor, kamu bisa drag `AKoinLatihan` (atau Blueprint anaknya) ke peta. `AActor` sudah menyediakan `GetActorLocation`, `SetActorHiddenInGame`, `Tags`, `Destroy`.

Prefix `A` = Actor, `U` = UObject non-actor, `F` = struct biasa / `USTRUCT`, `E` = enum. Itu konvensi Epic, bukan aturan C++.

**Biasanya digabungkan dengan:** komponen (file 09), `BeginPlay`, GameMode spawn.

**Jangan:** memakai `AActor` untuk data murni tanpa dunia — `UObject` / `UDataAsset` lebih ringan. Jangan membuat ribuan actor jika instancing / ISM cukup (optimasi, file 12).

## constructor AActor

**Tipe:** fungsi khusus

**Untuk apa:** `CreateDefaultSubobject`, set root, default `UPROPERTY`, flag tick. Dipanggil saat CDO (Class Default Object) dan saat instance dibuat.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"
#include "Components/StaticMeshComponent.h"

AKoinLatihan::AKoinLatihan()
{
    PrimaryActorTick.bCanEverTick = true;
    PrimaryActorTick.bStartWithTickEnabled = false;  // nyalakan nanti jika perlu

    Akar = CreateDefaultSubobject<USceneComponent>(TEXT("Akar"));
    SetRootComponent(Akar);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Akar);
}
```

**Yang terjadi:** setiap instance punya hirarki komponen yang sama. `CreateDefaultSubobject` **hanya** sah di constructor (bukan `BeginPlay`). Mengubah properti di constructor mengatur default CDO; desainer bisa override di instance / Blueprint.

`GetWorld()` di constructor sering `nullptr`. Jangan spawn, jangan query semua actor, jangan baca save game di sini.

**Biasanya digabungkan dengan:** `CreateDefaultSubobject`, `SetupAttachment`, `PrimaryActorTick`.

**Jangan:** `SpawnActor` di constructor. Jangan `CreateDefaultSubobject` di `BeginPlay` (pakai `NewObject` + `RegisterComponent` atau `AddComponent` — lebih rumit; pemula: buat di ctor). Jangan kerja I/O.

## BeginPlay

**Tipe:** fungsi virtual `AActor` / `UActorComponent`

**Untuk apa:** inisialisasi saat permainan (atau PIE) benar-benar mulai dan `GetWorld()` sudah sah: bind input, cache referensi, spawn anak, baca GameMode.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"
#include "Kismet/GameplayStatics.h"

void AKoinLatihan::BeginPlay()
{
    Super::BeginPlay();

    if (UWorld* Dunia = GetWorld())
    {
        const FVector Sini = GetActorLocation();
        UE_LOG(LogTemp, Log, TEXT("Koin muncul di %s"), *Sini.ToString());
    }

    APawn* Pemain = UGameplayStatics::GetPlayerPawn(this, 0);
    if (IsValid(Pemain))
    {
        UE_LOG(LogTemp, Log, TEXT("Ada pawn pemain: %s"), *Pemain->GetName());
    }
}
```

**Yang terjadi:** `Super::BeginPlay()` wajib agar rantai parent jalan. Log mencetak lokasi dan nama pawn jika ada. `BeginPlay` **bukan** constructor: di Editor, menggeser actor tidak memanggil `BeginPlay` sampai Play.

Urutan: constructor → (kadang `OnConstruction`) → `BeginPlay` saat start. Komponen `BeginPlay` terkait actor.

**Biasanya digabungkan dengan:** `GetWorld`, `IsValid`, bind Enhanced Input di Pawn/Controller.

**Jangan:** lupa `Super::BeginPlay()`. Jangan mengandalkan urutan `BeginPlay` antar actor acak tanpa eksplisit (beberapa butuh `bAllowTickBeforeBeginPlay` hati-hati). Jangan spawn tak terbatas di sini tanpa syarat.

## Tick

**Tipe:** fungsi virtual per-frame

**Untuk apa:** update yang **harus** tiap frame: gerak halus, timer visual, interpolasi. Bukan tempat load file.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

AKoinLatihan::AKoinLatihan()
{
    PrimaryActorTick.bCanEverTick = true;
}

void AKoinLatihan::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorWorldRotation(FRotator(0.f, 90.f * DeltaTime, 0.f));
}
```

**Yang terjadi:** setiap frame, koin berputar 90 derajat per detik di yaw, dikalikan `DeltaTime` agar tidak bergantung FPS. 30 FPS maupun 60 FPS menempuh sudut yang sama per detik.

`DeltaTime` adalah detik (sering ~0.016 pada 60 FPS). `bCanEverTick = false` (default banyak template) membuat `Tick` tidak dipanggil — hemat.

**Biasanya digabungkan dengan:** `FMath::Lerp`, gerak, `SetActorLocation`.

**Jangan:** `Tick` berat: `GetAllActorsOfClass` tiap frame, load disk, spawn tanpa batas, `UE_LOG` setiap frame di produksi. Jangan logika yang cukup `FTimerHandle` / event. Lihat file 12.

## EndPlay

**Tipe:** fungsi virtual

**Untuk apa:** cleanup saat actor keluar dunia: unbind, clear timer, lepaskan referensi.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"
#include "TimerManager.h"

void AKoinLatihan::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    GetWorldTimerManager().ClearAllTimersForObject(this);
    Super::EndPlay(EndPlayReason);
}
```

**Yang terjadi:** semua timer milik actor dibersihkan, lalu parent menyelesaikan `EndPlay`. Alasan (`Destroyed`, `LevelTransition`, `EndPlayInEditor`, `RemovedFromWorld`, `Quit`) bisa kamu `switch` jika cleanup berbeda.

**Biasanya digabungkan dengan:** `FTimerHandle`, delegate, unbind input.

**Jangan:** `Spawn` baru di `EndPlay` tanpa alasan. Jangan lupa `Super`. Jangan mengakses `GetWorld()` setelah super jika dunia sedang hilang — urutan: bersihkan milikmu dulu, lalu `Super`.

## Destroy

**Tipe:** fungsi `AActor`

**Untuk apa:** meminta actor dihancurkan secara legal (pending kill, `EndPlay`, lepas dari dunia). Bukan `delete this`.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::Ambil()
{
    // efek suara/partikel bisa di sini
    Destroy();
}
```

**Yang terjadi:** actor ditandai hancur. `IsValid(this)` akan false setelah proses. Jangan memakai `this` di sisa fungsi setelah `Destroy` kecuali sangat hati-hati (lebih baik `return` segera). Di multiplayer, penghancuran yang direplikasi punya aturan actor role — belajar `HasAuthority` dulu.

`Destroy()` pada client untuk actor yang direplikasi server sering tidak berlaku seperti yang kamu kira. Untuk latihan single player / listen server, panggil di server.

**Biasanya digabungkan dengan:** overlap pickup, umur `InitialLifeSpan`, GameMode.

**Jangan:** `delete this`. Jangan `Destroy` CDO. Jangan mengira `Destroy` sinkron selesai di baris berikutnya untuk semua callback.

## SpawnActor

**Tipe:** fungsi template `UWorld`

**Untuk apa:** membuat actor saat runtime di lokasi/rotasi tertentu.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnerKoin.generated.h"

class AKoinLatihan;

UCLASS()
class ASpawnerKoin : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AKoinLatihan> KelasKoin;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    int32 Jumlah = 3;

    virtual void BeginPlay() override
    {
        Super::BeginPlay();

        UWorld* Dunia = GetWorld();
        if (!Dunia || !KelasKoin)
        {
            return;
        }

        FActorSpawnParameters Param;
        Param.Owner = this;
        Param.SpawnCollisionHandlingOverride =
            ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

        for (int32 i = 0; i < Jumlah; ++i)
        {
            const FVector Lokasi = GetActorLocation() + FVector(i * 80.f, 0.f, 0.f);
            AKoinLatihan* Koin = Dunia->SpawnActor<AKoinLatihan>(KelasKoin, Lokasi, FRotator::ZeroRotator, Param);
            if (!IsValid(Koin))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawn koin %d gagal"), i);
            }
        }
    }
};
```

**Yang terjadi:** saat Play, spawner membuat `Jumlah` koin berjajar 80 unit. `TSubclassOf` diisi di Details (class C++ atau Blueprint anak). Spawn bisa gagal (kelas null, dunia null) — selalu cek. `Owner` membantu lifetime/replikasi.

`SpawnActorDeferred` + `FinishSpawning` dipakai jika kamu harus set properti **sebelum** `BeginPlay`.

**Biasanya digabungkan dengan:** `TSubclassOf`, `FActorSpawnParameters`, GameMode, projectile.

**Jangan:** spawn di constructor. Jangan spawn tiap `Tick` tanpa batas. Jangan mengabaikan `nullptr`. Jangan memakai ini untuk “menyuntik” object ke game tertutup orang lain.

## GetWorld

**Tipe:** fungsi `UObject` / `AActor` → `UWorld*`

**Untuk apa:** mengakses dunia: spawn, line trace, timer, GameMode, waktu.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void AKoinLatihan::JadwalkanHilang(float Detik)
{
    UWorld* Dunia = GetWorld();
    if (!Dunia)
    {
        return;
    }

    FTimerHandle Handle;
    Dunia->GetTimerManager().SetTimer(
        Handle, this, &AKoinLatihan::Ambil, Detik, false);

    AGameModeBase* Mode = UGameplayStatics::GetGameMode(Dunia);
    if (IsValid(Mode))
    {
        UE_LOG(LogTemp, Log, TEXT("GameMode: %s"), *Mode->GetName());
    }
}
```

**Yang terjadi:** jika dunia ada, timer memanggil `Ambil` setelah `Detik`, dan nama GameMode dilog. `GetWorld()` null pada CDO, beberapa object editor, constructor, object yang belum masuk dunia.

**Biasanya digabungkan dengan:** `SpawnActor`, `LineTrace`, `GetTimerManager`, `GetGameState`.

**Jangan:** `GetWorld()->...` tanpa cek. Jangan cache `UWorld*` lintas level tanpa invalidasi.

## FVector FRotator FTransform

**Tipe:** struct Unreal (`FVector`, `FRotator`, `FTransform`)

**Untuk apa:** posisi (cm), rotasi (pitch/yaw/roll derajat), transform lengkap + scale.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::ContohGerak()
{
    const FVector Sekarang = GetActorLocation();
    const FVector Maju = GetActorForwardVector() * 100.f;
    SetActorLocation(Sekarang + Maju);

    const FRotator Putar(0.f, 45.f, 0.f);
    AddActorLocalRotation(Putar);

    FTransform T = GetActorTransform();
    T.SetScale3D(FVector(1.5f, 1.5f, 1.5f));
    SetActorTransform(T);
}
```

**Yang terjadi:** actor geser 100 cm ke arah hadap, berputar yaw 45° lokal, scale 1.5. `FVector` adalah tiga `float` (`X` `Y` `Z`). Operasi `+` `-` `GetSafeNormal` `Size` sangat umum.

`FMath::Lerp`, `FMath::VInterpTo` untuk gerak halus di `Tick`.

**Biasanya digabungkan dengan:** `SetActorLocation`, komponen, trace.

**Jangan:** mencampur satuan (Unreal default 1 unit = 1 cm). Jangan `==` pada `FVector` hasil hitungan — `Equals` / `IsNearlyZero`.

## SetActorLocation

**Tipe:** fungsi `AActor`

**Untuk apa:** memindahkan root (dan komponen terikat) ke posisi dunia.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::LoncatKe(const FVector& Target)
{
    const bool bSukses = SetActorLocation(Target, true);
    if (!bSukses)
    {
        UE_LOG(LogTemp, Warning, TEXT("Tersumbat sweep"));
    }
}
```

**Yang terjadi:** `bSweep = true` menggeser dengan deteksi tabrakan; bisa gagal dan return false. `false` (default banyak overload) teleport tanpa sweep. Ada overload hit result.

`AddActorWorldOffset(FVector(0,0,10))` menambah relatif dunia. `SetActorLocation` mutlak.

**Biasanya digabungkan dengan:** `Tick` * `DeltaTime` * kecepatan, teleport checkpoint.

**Jangan:** set lokasi tiap Tick dengan query mahal. Jangan sweep tanpa memahami blocking collision.

## Tags dan ActorHasTag

**Tipe:** `TArray<FName> Tags` + fungsi cek

**Untuk apa:** menandai actor di Editor (`Enemy`, `Pickup`) tanpa class baru.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::BeginPlay()
{
    Super::BeginPlay();
    Tags.AddUnique(TEXT("Pickup"));

    if (ActorHasTag(TEXT("Pickup")))
    {
        UE_LOG(LogTemp, Log, TEXT("Ini pickup"));
    }
}
```

**Yang terjadi:** tag `Pickup` ditambah jika belum ada, lalu log. Di Details panel, array `Tags` bisa diisi desainer. Cari: `UGameplayStatics::GetAllActorsWithTag` — jangan tiap frame (file 12).

`FName` cepat dibanding `FString` untuk identitas.

**Biasanya digabungkan dengan:** overlap filter, query jarang, Gameplay Tags (sistem terpisah, lebih kaya).

**Jangan:** tag sebagai satu-satunya arsitektur besar (GameplayTag / interface lebih rapi). Jangan query all-with-tag di `Tick`.

## IsValid

**Tipe:** fungsi (`IsValid(const UObject*)`)

**Untuk apa:** cek pointer tidak null **dan** object belum pending kill / invalid.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::Ikuti(AActor* Target)
{
    if (!IsValid(Target))
    {
        return;
    }
    SetActorLocation(Target->GetActorLocation() + FVector(0.f, 0.f, 80.f));
}
```

**Yang terjadi:** jika target sudah `Destroy` atau null, fungsi diam. `if (Target)` hanya cek pointer, **bukan** pending kill — `IsValid` lebih tepat untuk `UObject`.

UE5: `TObjectPtr` + `IsValid(TargetKuat)`.

**Biasanya digabungkan dengan:** `TWeakObjectPtr::Get`, overlap, cache pointer.

**Jangan:** `Target->...` tanpa cek. Jangan `IsValid` lalu menyimpan raw dan memakai 2 detik kemudian tanpa cek ulang.

## HasAuthority

**Tipe:** fungsi `AActor` → `bool`

**Untuk apa:** di game yang punya server, memastikan logika “sumber kebenaran” jalan di server (ubah skor, destroy pickup).

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::Ambil()
{
    if (!HasAuthority())
    {
        return;
    }
    Destroy();
}
```

**Yang terjadi:** di standalone / listen server host, `HasAuthority()` biasanya true untuk actor server. Di client murni, false: fungsi return, destroy tidak dipaksa dari client. Ini **API resmi replikasi**, bukan hack.

Latihan single player tetap aman: authority ada.

**Biasanya digabungkan dengan:** `UFUNCTION(Server)`, `ROLE_Authority`, GameMode.

**Jangan:** memakai ini untuk cheat client (justru mencegah). Jangan mengabaikan authority lalu heran mengapa pickup “hilang hanya di satu mesin”.

## NewObject

**Tipe:** fungsi template

**Untuk apa:** membuat `UObject` non-actor (data, transient helper) dengan outer.

**Contoh implementasi:**

```cpp
#include "StatistikToko.h"
#include "KoinLatihan.h"

void AKoinLatihan::SiapkanStatistik()
{
    Statistik = NewObject<UStatistikToko>(this);
    Statistik->JumlahTransaksi = 0;
}

// Header: UPROPERTY() TObjectPtr<UStatistikToko> Statistik;
```

**Yang terjadi:** object data dimiliki `this` sebagai outer. Field `UPROPERTY Statistik` menahan GC. Tanpa `UPROPERTY` dan tanpa referensi lain, object bisa lenyap.

Bukan pengganti `SpawnActor`. Object ini tidak punya transform.

**Biasanya digabungkan dengan:** `UObject` helper, `UPROPERTY`, subsystem.

**Jangan:** `NewObject<AActor>` sebagai pengganti spawn (pakai `SpawnActor`). Jangan `NewObject` tanpa outer/root.

## Cast Unreal

**Tipe:** fungsi template `Cast<T>(UObject*)`

**Untuk apa:** downcast aman pada hierarki `UObject`. Gagal → `nullptr`, bukan exception.

**Contoh implementasi:**

```cpp
#include "GameFramework/Character.h"
#include "KoinLatihan.h"

void AKoinLatihan::SaatOverlap(AActor* Other)
{
    if (ACharacter* Karakter = Cast<ACharacter>(Other))
    {
        UE_LOG(LogTemp, Log, TEXT("Overlap karakter %s"), *Karakter->GetName());
    }
}
```

**Yang terjadi:** jika `Other` adalah `ACharacter` atau turunan, log nama. Jika pawn biasa bukan character, `Cast` null, cabang dilewati. Ini **bukan** `static_cast` C++ — ada cek tipe runtime UHT.

`CastChecked<T>` crash jika gagal (hanya jika “pasti benar”).

**Biasanya digabungkan dengan:** overlap, interface `Implements`, GameMode class.

**Jangan:** `static_cast<ACharacter*>(Other)` pada UObject. Jangan `Cast` di `Tick` pada ratusan actor jika tag/interface cukup.

## UE_LOG

**Tipe:** macro log

**Untuk apa:** menulis ke Output Log Editor / log file. Pengganti `std::cout` di Unreal.

**Contoh implementasi:**

```cpp
#include "KoinLatihan.h"

void AKoinLatihan::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("BeginPlay %s stok-int contoh=%d"), *GetName(), 3);
    UE_LOG(LogTemp, Warning, TEXT("Ini kuning di Output Log"));
    UE_LOG(LogTemp, Error, TEXT("Ini merah — pakai untuk gagal sungguhan"));
}
```

**Yang terjadi:** tiga baris di Output Log (`Window → Developer Tools → Output Log`). `TEXT("...")` adalah literal `TCHAR`. `*GetName()` karena `UE_LOG` format C-style butuh `TCHAR*`; `FString` di-`*` menjadi pointer.

Kategori kustom: `DEFINE_LOG_CATEGORY`. Verbosity: `Verbose`, `Log`, `Warning`, `Error`.

**Biasanya digabungkan dengan:** `IsValid` gagal, spawn gagal, debug gerak.

**Jangan:** `UE_LOG` tiap Tick di ship. Jangan `std::cout` mengharapkan muncul di Output Log. Jangan string dari pemain tanpa sadar format `%`.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** menyingkat crash constructor, Tick, dan spawn.

**Contoh implementasi:**

```cpp
#include "SpawnerKoin.h"

void ASpawnerKoin::BeginPlay()
{
    Super::BeginPlay();

    if (!GetWorld())
    {
        return;
    }
    if (!KelasKoin)
    {
        UE_LOG(LogTemp, Error, TEXT("KelasKoin belum diisi di Details"));
        return;
    }
}
```

**Yang terjadi:** early return mencegah spawn dengan kelas kosong — error yang sering “PIE lalu crash / tidak ada koin”. Isi `TSubclassOf` di Blueprint atau instance.

**Biasanya digabungkan dengan:** constructor vs `BeginPlay`, `IsValid`, file 12.

**Jangan:** `GetWorld()` di ctor; `delete` actor; Tick `GetAllActorsOfClass`; lupa `Super::BeginPlay`; `g++` file Unreal.
