# 12 — Resep dan kesalahan umum

[← Blueprint vs C++](11-unreal-blueprint-vs-cpp.md) · [README](README.md)

Resep di bawah merangkai file 01–11 menjadi potongan yang bisa ditiru. Semua memakai API publik: gerak actor, pickup, pintu, nyawa. Bukan exploit, wallhack, atau edit memori game tertutup.

## Daftar isi

- [Resep: actor yang bergerak](#resep-actor-yang-bergerak)
- [Resep: koin overlap](#resep-koin-overlap)
- [Resep: pintu bertag kunci](#resep-pintu-bertag-kunci)
- [Resep: nyawa di komponen](#resep-nyawa-di-komponen)
- [Resep: spawn beberapa prop](#resep-spawn-beberapa-prop)
- [Resep: program C++ biasa toko](#resep-program-c-biasa-toko)
- [Error: include tidak ketemu](#error-include-tidak-ketemu)
- [Error: generated.h / GENERATED_BODY](#error-generatedh--generated_body)
- [Error: modul Build.cs](#error-modul-buildcs)
- [Error: nullptr dan GetWorld](#error-nullptr-dan-getworld)
- [Error: Tick berat](#error-tick-berat)
- [Error: UPROPERTY tidak muncul](#error-uproperty-tidak-muncul)
- [Error: input diam](#error-input-diam)
- [Error: double possess / cube default](#error-double-possess--cube-default)
- [Error: GC memakan object](#error-gc-memakan-object)
- [Error: circular include](#error-circular-include)
- [Error: access specifier UHT](#error-access-specifier-uht)
- [Daftar periksa sebelum Play](#daftar-periksa-sebelum-play)

## Resep: actor yang bergerak

**Tipe:** resep (AActor + Tick + DeltaTime)

**Untuk apa:** platform / platformer latihan yang geser bolak-balik tanpa Character Movement.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlatformGeser.generated.h"

UCLASS()
class APlatformGeser : public AActor
{
    GENERATED_BODY()

public:
    APlatformGeser();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, Category = "Gerak")
    FVector Offset = FVector(300.f, 0.f, 0.f);

    UPROPERTY(EditAnywhere, Category = "Gerak")
    float Kecepatan = 120.f;

protected:
    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

private:
    FVector Awal;
    float Arah = 1.f;
};
```

```cpp
#include "PlatformGeser.h"
#include "Components/StaticMeshComponent.h"

APlatformGeser::APlatformGeser()
{
    PrimaryActorTick.bCanEverTick = true;
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
}

void APlatformGeser::BeginPlay()
{
    Super::BeginPlay();
    Awal = GetActorLocation();
}

void APlatformGeser::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    const FVector Tujuan = Awal + Offset;
    const FVector Sekarang = GetActorLocation();
    const FVector Target = (Arah > 0.f) ? Tujuan : Awal;
    const FVector Baru = FMath::VInterpConstantTo(Sekarang, Target, DeltaTime, Kecepatan);
    SetActorLocation(Baru);

    if (FVector::DistSquared(Baru, Target) < 4.f)
    {
        Arah *= -1.f;
    }
}
```

**Yang terjadi:** di `BeginPlay` posisi awal disimpan. Tiap frame platform berjalan konstan `Kecepatan` cm/s menuju `Awal+Offset`, lalu balik. `VInterpConstantTo` + `DeltaTime` membuat gerak tidak bergantung FPS. Isi mesh di Details. Letakkan di level, Play.

Karakter di atas platform: aktifkan `SetUpdateOverlaps` / berdiri dengan collision; untuk membawa pawn, sering `Attach` atau gunakan moving platform character movement (`bSweep` / base movement) — mulai dari collision blocking dulu.

**Biasanya digabungkan dengan:** `EditAnywhere` Offset, mesh cube, Character yang berdiri di atas.

**Jangan:** `SetActorLocation` dengan angka tetap tanpa `DeltaTime` (`+ 5` per frame = lebih cepat di 120 FPS). Jangan `GetAllActors` di Tick platform. Jangan physics simulate + set location tiap frame.

## Resep: koin overlap

**Tipe:** resep (Box trigger + PlayerState)

**Untuk apa:** pickup yang menambah skor di PlayerState, lalu `Destroy`.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KoinLatihan.generated.h"

class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class AKoinLatihan : public AActor
{
    GENERATED_BODY()

public:
    AKoinLatihan();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<USphereComponent> Area;

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<UStaticMeshComponent> Mesh;

    UPROPERTY(EditAnywhere, Category = "Koin")
    int32 Nilai = 1;

    UFUNCTION()
    void SaatOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
```

```cpp
#include "KoinLatihan.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Character.h"
#include "TokoPlayerState.h"

AKoinLatihan::AKoinLatihan()
{
    Area = CreateDefaultSubobject<USphereComponent>(TEXT("Area"));
    SetRootComponent(Area);
    Area->InitSphereRadius(50.f);
    Area->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    Area->SetGenerateOverlapEvents(true);

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    Mesh->SetupAttachment(Area);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AKoinLatihan::BeginPlay()
{
    Super::BeginPlay();
    Area->OnComponentBeginOverlap.AddDynamic(this, &AKoinLatihan::SaatOverlap);
}

void AKoinLatihan::SaatOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    ACharacter* Karakter = Cast<ACharacter>(OtherActor);
    if (!IsValid(Karakter) || !HasAuthority())
    {
        return;
    }

    if (ATokoPlayerState* PS = Karakter->GetPlayerState<ATokoPlayerState>())
    {
        PS->Koin += Nilai;
    }
    Destroy();
}
```

**Yang terjadi:** character masuk bola → server menambah `Koin` → koin hilang. Client melihat skor jika `Koin` `Replicated` (file 10). Mesh tidak block. `HasAuthority` mencegah double-count aneh di net.

**Biasanya digabungkan dengan:** `ATokoPlayerState`, HUD, `OnKoinDiambil` BP event.

**Jangan:** overlap tanpa `UFUNCTION`. Jangan simpan skor di koin. Jangan destroy tanpa filter (hancur karena debris).

## Resep: pintu bertag kunci

**Tipe:** resep (tag + UFUNCTION)

**Untuk apa:** pintu terbuka hanya jika pawn punya tag `KunciMerah` (latihan; produksi: inventory).

**Contoh implementasi:**

```cpp
UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Pintu")
    FName TagKunci = TEXT("KunciMerah");

    UFUNCTION(BlueprintCallable, Category = "Pintu")
    bool CobaBuka(AActor* Peminta)
    {
        if (!IsValid(Peminta) || !Peminta->ActorHasTag(TagKunci))
        {
            UE_LOG(LogTemp, Log, TEXT("Tidak ada kunci"));
            return false;
        }
        Destroy();  // latihan: pintu hilang
        return true;
    }
};
```

**Yang terjadi:** overlap BP atau C++ memanggil `CobaBuka(Other)`. Jika tag cocok, pintu hancur. Kunci bisa berupa actor yang `Tags.Add` saat diambil.

**Biasanya digabungkan dengan:** overlap, Gameplay Tags (lebih baik jangka panjang), inventory C++.

**Jangan:** cek tag di client saja untuk pintu penting di multiplayer. Jangan `Destroy` mesh dunia yang seharusnya animasi buka (pakai flag + rotasi).

## Resep: nyawa di komponen

**Tipe:** resep (UActorComponent)

**Untuk apa:** memakai ulang nyawa pada peti, musuh, pemain.

**Contoh implementasi:**

```cpp
UCLASS(ClassGroup = (Latihan), meta = (BlueprintSpawnableComponent))
class UKomponenNyawa : public UActorComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Nyawa")
    int32 Maks = 100;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nyawa")
    int32 Sekarang = 100;

    UFUNCTION(BlueprintCallable, Category = "Nyawa")
    void Rusak(int32 Jumlah)
    {
        if (!GetOwner() || !GetOwner()->HasAuthority())
        {
            return;
        }
        Sekarang = FMath::Max(0, Sekarang - Jumlah);
        if (Sekarang == 0)
        {
            GetOwner()->Destroy();
        }
    }
};
```

**Yang terjadi:** `Rusak(40)` di server. Di 0, owner hancur. Tambahkan komponen ke musuh di ctor atau BP. UI baca `Sekarang`.

Untuk pemain, `Destroy` owner terlalu kasar — panggil GameMode respawn, jangan hancurkan PlayerController.

**Biasanya digabungkan dengan:** `BlueprintReadOnly`, GameMode `RestartPlayer`, `Replicated` nyawa.

**Jangan:** nyawa hanya di widget. Jangan `Rusak` dari client tanpa Server RPC.

## Resep: spawn beberapa prop

**Tipe:** resep (`SpawnActor` + `TSubclassOf`)

**Untuk apa:** mengisi rak saat `BeginPlay` tanpa menaruh 20 instance manual.

**Contoh implementasi:**

```cpp
UCLASS()
class ARakSpawner : public AActor
{
    GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> KelasProp;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    int32 Jumlah = 5;

    UPROPERTY(EditAnywhere, Category = "Spawn")
    float Jarak = 80.f;

    virtual void BeginPlay() override
    {
        Super::BeginPlay();
        UWorld* W = GetWorld();
        if (!W || !KelasProp)
        {
            UE_LOG(LogTemp, Error, TEXT("RakSpawner: isi KelasProp"));
            return;
        }
        for (int32 i = 0; i < Jumlah; ++i)
        {
            const FVector L = GetActorLocation() + FVector(0.f, i * Jarak, 0.f);
            W->SpawnActor<AActor>(KelasProp, L, GetActorRotation());
        }
    }
};
```

**Yang terjadi:** lima prop berjajar di sumbu Y. Isi `KelasProp` dengan BP kotak. Log error jika lupa assign.

**Biasanya digabungkan dengan:** `FActorSpawnParameters`, random `FMath::RandRange`.

**Jangan:** spawn di Tick. Jangan spawn di constructor.

## Resep: program C++ biasa toko

**Tipe:** resep (STL, tanpa Unreal)

**Untuk apa:** latihan 01–05: stok, map harga, sort, jumlah.

**Contoh implementasi:**

```cpp
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>

int main() {
    std::map<std::string, int> harga{{"Buku", 45000}, {"Pensil", 3000}, {"Pena", 8000}};
    std::vector<std::string> belanja{"Buku", "Pensil", "Pensil"};

    std::vector<int> tagihan;
    for (const std::string& nama : belanja) {
        auto it = harga.find(nama);
        if (it == harga.end()) {
            std::cerr << "Tidak ada harga: " << nama << '\n';
            return 1;
        }
        tagihan.push_back(it->second);
    }

    const int total = std::accumulate(tagihan.begin(), tagihan.end(), 0);
    std::sort(tagihan.begin(), tagihan.end());

    std::cout << "Item termurah: " << tagihan.front() << '\n';
    std::cout << "Total: " << total << '\n';
    return 0;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -o toko toko.cpp && ./toko
```

**Yang terjadi:** dua pensil + buku = 51000. Sort membuat termurah 3000. Compile dengan g++/MSVC seperti README.

**Biasanya digabungkan dengan:** file 03–05, class `Barang` file 02.

**Jangan:** menempel ini ke `Tick` Unreal. Jangan `std::map` sebagai `UPROPERTY`.

## Error: include tidak ketemu

**Tipe:** kesalahan compile

**Untuk apa:** membaca pesan `fatal error: 'X.h' file not found` / `cannot open include`.

**Contoh implementasi:**

```cpp
// Salah di modul game tanpa path/modul
#include "EnhancedInputComponent.h"

// Benar: header + Build.cs "EnhancedInput"
#include "EnhancedInputComponent.h"
```

**Yang terjadi:** tiga dunia berbeda:

1. **C++ biasa:** `g++` tidak punya `-I` ke folder header. `#include <vector>` butuh standard lib. Header milikmu: `#include "Toko.h"` dan compile `Toko.cpp` bersama, atau `-I`.
2. **Unreal:** header engine ketemu hanya lewat UBT. Jangan `g++ AActor.cpp`.
3. **Modul lupa:** Enhanced Input, AI Module, UMG — tambah `Build.cs`, generate project files.

Path Unreal: `#include "GameFramework/Actor.h"` bukan path disk penuh.

**Biasanya digabungkan dengan:** `Build.cs`, IDE generate files.

**Jangan:** copy header engine ke folder tugas. Jangan `#include` `.generated.h` orang lain.

## Error: generated.h / GENERATED_BODY

**Tipe:** kesalahan UHT

**Untuk apa:** memperbaiki `#include "X.generated.h"` dan body macro.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KoinLatihan.generated.h"  // HARUS terakhir

UCLASS()
class AKoinLatihan : public AActor
{
    GENERATED_BODY()
public:
};
```

**Yang terjadi:** `generated.h` **bukan** kamu tulis. UHT membuatnya. Harus include terakhir di header `UCLASS`. Nama file = nama header. Tanpa `GENERATED_BODY`: error member generated hilang. Edit `.generated.h` akan ditimpa.

Jika UHT gagal, baca log **UnrealHeaderTool** di atas error MSVC — sering specifier salah, koma di `UCLASS`, atau tipe `UPROPERTY` tidak didukung.

**Biasanya digabungkan dengan:** Live Coding gagal → compile penuh.

**Jangan:** memindahkan `generated.h` ke atas `CoreMinimal.h`. Jangan commit file generated jika proyekmu mengabaikannya (ikut aturan repo). Jangan rename class tanpa rename file.

## Error: modul Build.cs

**Tipe:** kesalahan taut (linker / include)

**Untuk apa:** `unresolved external` atau include hilang setelah pakai API modul lain.

**Contoh implementasi:**

```csharp
PublicDependencyModuleNames.AddRange(new string[]
{
    "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG", "AIModule"
});
```

**Yang terjadi:** tiap modul = library. `UUserWidget` butuh `UMG` (+ sering `Slate`). `AAIController` butuh `AIModule`. Setelah ubah, tutup Editor, generate Visual Studio files, compile.

**Biasanya digabungkan dengan:** dokumentasi class Epic (modul tercantum).

**Jangan:** menambah 20 modul “jaga-jaga”. Jangan edit `Engine/Source` untuk “biar ketemu”.

## Error: nullptr dan GetWorld

**Tipe:** kesalahan runtime (crash)

**Untuk apa:** menghindari akses dunia/object yang belum hidup.

**Contoh implementasi:**

```cpp
void AKoinLatihan::ContohAman()
{
    UWorld* Dunia = GetWorld();
    if (!Dunia)
    {
        return;
    }

    APawn* P = UGameplayStatics::GetPlayerPawn(Dunia, 0);
    if (!IsValid(P))
    {
        return;
    }

    const FVector L = P->GetActorLocation();
    UE_LOG(LogTemp, Log, TEXT("%s"), *L.ToString());
}
```

**Yang terjadi:** constructor, CDO, object editor: `GetWorld()` null. `GetPlayerPawn` sebelum spawn: null. `Destroy` sudah dipanggil: `IsValid` false. Crash klasik: `GetWorld()->SpawnActor` di ctor, atau `OtherActor->` di overlap tanpa cek.

**Biasanya digabungkan dengan:** `BeginPlay`, `IsValid`, `TWeakObjectPtr`.

**Jangan:** `GetWorld()->` berantai. Jangan cache pawn 10 menit tanpa cek. Jangan `ensure(P)` lalu tetap dereference di Shipping tanpa return.

## Error: Tick berat

**Tipe:** kesalahan performa / desain

**Untuk apa:** mengenali pekerjaan yang **tidak** boleh tiap frame.

**Contoh implementasi:**

```cpp
// SALAH
void AMusuhLatihan::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    TArray<AActor*> Semua;
    UGameplayStatics::GetAllActorsOfClass(this, ATokoCharacter::StaticClass(), Semua);
    // Load file, Spawn tanpa batas, UE_LOG tiap frame, Find object path...
}

// LEBIH BAIK
void AMusuhLatihan::BeginPlay()
{
    Super::BeginPlay();
    GetWorldTimerManager().SetTimer(TimerCari, this, &AMusuhLatihan::PerbaruiTarget, 0.3f, true);
}

void AMusuhLatihan::PerbaruiTarget()
{
    // query jarang, atau Perception AI
}
```

**Yang terjadi:** `GetAllActorsOfClass` memindai dunia. 200 musuh × 60 FPS = 12.000 scan/detik. Gejala: FPS drop, hitch. Ganti: cache di BeginPlay, timer 0.2–0.5 s, overlap sensor, `TObjectPtr` yang diisi desainer, AI Perception.

Tick visual ringan (putar koin) OK. Matikan Tick: `PrimaryActorTick.bCanEverTick = false` atau `SetActorTickEnabled(false)`.

**Biasanya digabungkan dengan:** `FTimerHandle`, event overlap, Insights `stat actor`.

**Jangan:** log setiap Tick. Jangan spawn di Tick. Jangan `LoadSynchronous` di Tick. Jangan sort array besar di Tick tanpa butuh.

## Error: UPROPERTY tidak muncul

**Tipe:** kesalahan editor / BP

**Untuk apa:** field ada di C++ tetapi Details/BP kosong.

**Contoh implementasi:**

```cpp
// Tidak tampil di BP graph
UPROPERTY(EditAnywhere, Category = "Toko")
int32 Harga;

// Tampil di Details dan BP
UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Toko")
int32 Harga;
```

**Yang terjadi:** `Edit*` = Details. `BlueprintRead*` = graph. Keduanya terpisah (file 08). Sebab lain: compile UHT gagal, kamu melihat class lama, property `private` tanpa `AllowPrivateAccess`, kategori ter-collapse, instance vs defaults (`EditInstanceOnly`).

`std::string` tidak pernah tampil.

**Biasanya digabungkan dengan:** compile sukses, buka ulang BP, file 08.

**Jangan:** menambah `UPROPERTY` di `.cpp`. Jangan tipe STL.

## Error: input diam

**Tipe:** kesalahan setup

**Untuk apa:** karakter tidak gerak.

**Contoh implementasi:**

```cpp
void ATokoCharacter::SetupPlayerInputComponent(UInputComponent* Comp)
{
    Super::SetupPlayerInputComponent(Comp);
    if (!AksiPindah || !MappingPemain)
    {
        UE_LOG(LogTemp, Error, TEXT("Assign IA dan IMC di Class Defaults BP"));
    }
}
```

**Yang terjadi:** checklist file 09–10: EnhancedInput di `Build.cs`; Project Settings Default Input Component Class = Enhanced; IMC di-`AddMappingContext`; action di-`BindAction`; asset diisi di **BP anak**; GameMode pawn = BP itu; possessed; input mode Game; PIE window fokus.

**Biasanya digabungkan dengan:** file 09, PlayerController.

**Jangan:** bind Axis string lama + mengira Enhanced otomatis. Jangan tes input di dedicated server.

## Error: double possess / cube default

**Tipe:** kesalahan GameMode vs instance

**Untuk apa:** dua tubuh, atau cube terbang, atau pawn di 0,0,0.

**Contoh implementasi:**

```cpp
ATokoGameMode::ATokoGameMode()
{
    DefaultPawnClass = ATokoCharacter::StaticClass();  // lebih baik BP lewat Defaults
}
```

**Yang terjadi:** `AutoPossessPlayer = Player 0` pada pawn di level **plus** GameMode spawn = dua karakter. `DefaultPawnClass` tertinggal `DefaultPawn` = cube. Tidak ada `PlayerStart` = spawn aneh. World Settings override GameMode lama.

**Biasanya digabungkan dengan:** World Settings, PlayerStart, `TSubclassOf` BP.

**Jangan:** AutoPossess di setiap pawn tes. Jangan lupa override level.

## Error: GC memakan object

**Tipe:** kesalahan lifetime Unreal

**Untuk apa:** pointer tiba-tiba invalid setelah beberapa frame.

**Contoh implementasi:**

```cpp
// Raw tanpa UPROPERTY: GC boleh memungut UObject
UStatistikToko* Raw;

UPROPERTY()
TObjectPtr<UStatistikToko> Aman;
```

**Yang terjadi:** `NewObject` tanpa outer/root + tanpa `UPROPERTY` → object hilang. Gejala: crash acak di PIE, `IsValid` false “padahal baru dibuat”. Perbaikan: `UPROPERTY`, outer `this`, atau `AddToRoot` (jarang, harus `RemoveFromRoot`).

Actor: `Destroy` lalu pointer field lain — pakai `IsValid` / `TWeakObjectPtr`.

**Biasanya digabungkan dengan:** file 06–07, `NewObject`.

**Jangan:** `unique_ptr<UObject>`. Jangan `AddToRoot` lalu lupa (bocor).

## Error: circular include

**Tipe:** kesalahan compile header

**Untuk apa:** `A` include `B` include `A` → tipe tidak lengkap.

**Contoh implementasi:**

```cpp
// PintuLatihan.h
#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PintuLatihan.generated.h"

class AKoinLatihan;  // forward declaration

UCLASS()
class APintuLatihan : public AActor
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, Category = "Toko")
    TSubclassOf<AKoinLatihan> Hadiah;
};
```

```cpp
// PintuLatihan.cpp
#include "PintuLatihan.h"
#include "KoinLatihan.h"  // lengkap di cpp
```

**Yang terjadi:** header hanya pointer/`TSubclassOf`/`TObjectPtr` — cukup *forward declare*. Include penuh di `.cpp`. Siklus `UCLASS` juga membingungkan UHT.

`#pragma once` wajib. Jangan include `.generated.h` milik class lain.

**Biasanya digabungkan dengan:** `class AFoo;`, `TObjectPtr<AFoo>`.

**Jangan:** include header besar di header “supaya nyaman”. Jangan forward declare lalu pakai sebagai nilai by-value.

## Error: access specifier UHT

**Tipe:** kesalahan / kejutan akses

**Untuk apa:** property `private` tidak ter-expose, atau `UFUNCTION` di tempat salah.

**Contoh implementasi:**

```cpp
UCLASS()
class APetiBarang : public AActor
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Toko",
              meta = (AllowPrivateAccess = "true"))
    int32 Kode = 0;
};
```

**Yang terjadi:** tanpa meta, BP/Details bisa menolak akses field private. `UFUNCTION` harus terlihat UHT di section yang valid. Beberapa specifier menuntut `public`. Baca error UHT harfiah.

**Biasanya digabungkan dengan:** file 08 `AllowPrivateAccess`.

**Jangan:** membuat semua `public` hanya karena satu property tidak tampil — cek specifier dulu.

## Daftar periksa sebelum Play

**Tipe:** resep cek

**Untuk apa:** lima menit sebelum bertanya “mengapa tidak jalan”.

**Contoh implementasi:**

```text
[ ] Compile C++ sukses (tidak hanya Live Coding gagal diam-diam)
[ ] Class GameMode terpasang di World Settings / Project
[ ] DefaultPawnClass = Blueprint anak yang ada mesh-nya
[ ] PlayerStart ada, tidak di dalam dinding
[ ] UPROPERTY asset (IMC, IA, mesh) ter-assign di BP
[ ] Enhanced Input: modul + Default Input Component Class
[ ] Tidak ada GetWorld di constructor
[ ] Overlap: UFUNCTION + generate overlap + profile
[ ] Pointer: IsValid sebelum pakai
[ ] Tidak ada GetAllActors / log di Tick
```

**Yang terjadi:** sebagian besar bug pemula tertangkap list ini. Jika crash, buka `Saved/Logs` dan callstack pertama yang file-mu.

**Biasanya digabungkan dengan:** seluruh folder ensiklopedia ini.

**Jangan:** mengubah 15 hal sekaligus lalu tidak tahu yang memperbaiki. Ubah satu, Play, ulang.

---

Kembali ke [README C++](README.md) atau [daftar ensiklopedia](../README.md).
