# 09 — Komponen dan Enhanced Input

[← UPROPERTY / UFUNCTION](08-unreal-uproperty-ufunction.md) · [README](README.md) · [Lanjut: GameMode, Pawn, Controller →](10-unreal-gamemode-pawn-controller.md)

Actor adalah “amplop”. Yang terlihat dan bergerak sering **komponen**: scene (punya transform), mesh, kamera. Input modern Unreal 5 memakai **Enhanced Input**: asset `UInputAction` + `UInputMappingContext`, bukan Axis/Action name string lama.

Modul `EnhancedInput` harus ada di `Build.cs`. Ini API publik input, bukan membaca memori game lain.

## Daftar isi

- [UActorComponent](#uactorcomponent)
- [USceneComponent](#uscenecomponent)
- [CreateDefaultSubobject](#createdefaultsubobject)
- [SetupAttachment](#setupattachment)
- [UStaticMeshComponent](#ustaticmeshcomponent)
- [USkeletalMeshComponent](#uskeletalmeshcomponent)
- [UCameraComponent](#ucameracomponent)
- [USpringArmComponent](#uspringarmcomponent)
- [UCapsuleComponent](#ucapsulecomponent)
- [UBoxComponent overlap](#uboxcomponent-overlap)
- [SetRelativeLocation](#setrelativelocation)
- [Enhanced Input](#enhanced-input)
- [UInputAction](#uinputaction)
- [UInputMappingContext](#uinputmappingcontext)
- [BindAction](#bindaction)
- [FInputActionValue](#finputactionvalue)
- [AddMappingContext](#addmappingcontext)
- [Input Action di Build.cs](#input-action-di-buildcs)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## UActorComponent

**Tipe:** class (komponen tanpa transform sendiri)

**Untuk apa:** menempelkan perilaku pada actor: inventory logic, health, timer, audio non-spasial. Tidak punya lokasi relatif kecuali diturunkan ke scene.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KomponenNyawa.generated.h"

UCLASS(ClassGroup = (Latihan), meta = (BlueprintSpawnableComponent))
class UKomponenNyawa : public UActorComponent
{
    GENERATED_BODY()

public:
    UKomponenNyawa()
    {
        PrimaryComponentTick.bCanEverTick = false;
    }

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Nyawa")
    int32 Maks = 100;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Nyawa")
    int32 Sekarang = 100;

    UFUNCTION(BlueprintCallable, Category = "Nyawa")
    void Rusak(int32 Jumlah)
    {
        Sekarang = FMath::Max(0, Sekarang - Jumlah);
    }
};
```

**Yang terjadi:** kamu menambah komponen ini di constructor actor (`CreateDefaultSubobject`) atau di Blueprint. `Rusak(30)` menurunkan nyawa. `BlueprintSpawnableComponent` mengizinkan Add Component di BP. Tidak muncul sebagai anak 3D di viewport kecuali kamu pakai scene component.

**Biasanya digabungkan dengan:** actor pemilik `GetOwner()`, `BeginPlay` komponen, `UPROPERTY` di actor.

**Jangan:** memakai `UActorComponent` jika kamu butuh posisi di ruang — pakai `USceneComponent`. Jangan Tick komponen tanpa perlu.

## USceneComponent

**Tipe:** class (komponen ber-transform)

**Untuk apa:** titik di ruang relatif parent: socket kosong, akar hirarki, tempat attach kamera.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TiangBendera.generated.h"

UCLASS()
class ATiangBendera : public AActor
{
    GENERATED_BODY()

public:
    ATiangBendera();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<USceneComponent> Akar;

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<USceneComponent> TitikBendera;
};
```

```cpp
#include "TiangBendera.h"
#include "Components/SceneComponent.h"

ATiangBendera::ATiangBendera()
{
    Akar = CreateDefaultSubobject<USceneComponent>(TEXT("Akar"));
    SetRootComponent(Akar);

    TitikBendera = CreateDefaultSubobject<USceneComponent>(TEXT("TitikBendera"));
    TitikBendera->SetupAttachment(Akar);
    TitikBendera->SetRelativeLocation(FVector(0.f, 0.f, 200.f));
}
```

**Yang terjadi:** actor punya root di (0,0,0) lokal, dan anak 200 cm ke atas. Mesh/partikel bisa di-attach ke `TitikBendera`. `GetComponentLocation()` memberi posisi dunia.

Setiap actor yang bergerak di dunia butuh **root** `USceneComponent` (atau turunan: capsule, mesh).

**Biasanya digabungkan dengan:** `SetupAttachment`, mesh, spring arm.

**Jangan:** dua root. Jangan `SetupAttachment` ke komponen yang belum dibuat. Jangan `SetRootComponent` di `BeginPlay` tanpa sadar memutus hirarki.

## CreateDefaultSubobject

**Tipe:** fungsi template (hanya constructor)

**Untuk apa:** membuat komponen default yang muncul di semua instance dan di Blueprint parent.

**Contoh implementasi:**

```cpp
Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
Mesh->SetupAttachment(Akar);
```

**Yang terjadi:** nama `TEXT("Mesh")` harus unik per class instance CDO. Blueprint anak melihat komponen ini dan bisa override mesh asset. Dipanggil di luar constructor → assert/crash.

Untuk komponen runtime dinamis: `NewObject<UStaticMeshComponent>(this, TEXT("Dinamis"))` lalu `RegisterComponent` / `AttachToComponent` — lebih banyak langkah; pemula tetap ctor.

**Biasanya digabungkan dengan:** `SetRootComponent`, `VisibleAnywhere`.

**Jangan:** `CreateDefaultSubobject` di `BeginPlay`. Jangan nama duplikat. Jangan `new UStaticMeshComponent`.

## SetupAttachment

**Tipe:** fungsi `USceneComponent`

**Untuk apa:** menempelkan komponen ke parent **di constructor** (sebelum register).

**Contoh implementasi:**

```cpp
Kamera->SetupAttachment(Lengan, USpringArmComponent::SocketName);
```

**Yang terjadi:** kamera mengikuti ujung spring arm. Setelah actor di dunia, pakai `AttachToComponent` dengan `FAttachmentTransformRules`, bukan `SetupAttachment`.

**Biasanya digabungkan dengan:** spring arm, socket skeletal mesh (`AttachToComponent(Mesh, Rules, TEXT("hand_r"))`).

**Jangan:** `SetupAttachment` di `BeginPlay`. Jangan attach ke `nullptr`.

## UStaticMeshComponent

**Tipe:** class komponen

**Untuk apa:** menampilkan mesh statis (prop, koin, pintu), collision, material.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KotakProp.generated.h"

UCLASS()
class AKotakProp : public AActor
{
    GENERATED_BODY()

public:
    AKotakProp();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<UStaticMeshComponent> Mesh;
};
```

```cpp
#include "KotakProp.h"
#include "Components/StaticMeshComponent.h"

AKotakProp::AKotakProp()
{
    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
    SetRootComponent(Mesh);
    Mesh->SetSimulatePhysics(false);
    Mesh->SetCollisionProfileName(TEXT("BlockAll"));
}
```

**Yang terjadi:** actor adalah kotak. Isi static mesh asset di Details (atau `ConstructorHelpers::FObjectFinder` — hati-hati path). Collision `BlockAll` menahan pawn. `SetSimulatePhysics(true)` menyerahkan ke physic.

`SetMaterial`, `GetMaterial`, `SetVisibility` sering dipakai runtime.

**Biasanya digabungkan dengan:** `UBoxComponent` trigger terpisah, material instance.

**Jangan:** physics + `SetActorLocation` tiap Tick tanpa pahami (bertarung). Jangan mesh berat tanpa LOD di scene besar.

## USkeletalMeshComponent

**Tipe:** class komponen

**Untuk apa:** mesh bertulang + animasi (karakter). `ACharacter` sudah punya `GetMesh()`.

**Contoh implementasi:**

```cpp
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"

void AKarakterLatihan::BeginPlay()
{
    Super::BeginPlay();
    if (USkeletalMeshComponent* SK = GetMesh())
    {
        SK->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        SK->PlayAnimation(AnimIdle, true);  // sederhana; lebih baik AnimBP
    }
}
```

**Yang terjadi:** mesh karakter mendapat collision query/physics sesuai setting, memutar animasi idle looping. Produksi memakai **Animation Blueprint**, bukan `PlayAnimation` terus-menerus.

**Biasanya digabungkan dengan:** `UAnimInstance`, `ACharacter`, socket senjata.

**Jangan:** `PlayAnimation` menimpa AnimBP tanpa alasan. Jangan skeletal untuk kotak statis.

## UCameraComponent

**Tipe:** class komponen

**Untuk apa:** mata pemain / cutscene. View dari komponen yang aktif.

**Contoh implementasi:**

```cpp
#include "KarakterLatihan.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

AKarakterLatihan::AKarakterLatihan()
{
    Lengan = CreateDefaultSubobject<USpringArmComponent>(TEXT("Lengan"));
    Lengan->SetupAttachment(RootComponent);
    Lengan->TargetArmLength = 300.f;
    Lengan->bUsePawnControlRotation = true;

    Kamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Kamera"));
    Kamera->SetupAttachment(Lengan, USpringArmComponent::SocketName);
    Kamera->bUsePawnControlRotation = false;
}
```

**Yang terjadi:** kamera di ujung lengan 300 cm. Gerak mouse (control rotation) memutar lengan, kamera tetap menghadap arah lengan. Ini pola third person resmi.

`APlayerController` menentukan view target, biasanya pawn.

**Biasanya digabungkan dengan:** `USpringArmComponent`, `bUsePawnControlRotation`, Enhanced Input look.

**Jangan:** dua kamera aktif tanpa aturan. Jangan `bUsePawnControlRotation` true di kamera *dan* lengan tanpa paham double rotation.

## USpringArmComponent

**Tipe:** class komponen

**Untuk apa:** menjaga jarak kamera, collision probe agar tidak menembus dinding.

**Contoh implementasi:**

```cpp
Lengan->TargetArmLength = 400.f;
Lengan->bDoCollisionTest = true;
Lengan->SocketOffset = FVector(0.f, 70.f, 80.f);
```

**Yang terjadi:** kamera cenderung 400 cm di belakang, bergeser offset, memendek jika ada dinding di antara (collision test). Tanpa ini, kamera third person sering masuk geometri.

**Biasanya digabungkan dengan:** `UCameraComponent`, look input.

**Jangan:** collision test off di ruang sempit lalu heran kamera clip. Jangan arm length 0 sebagai first person — lebih jelas kamera di kepala.

## UCapsuleComponent

**Tipe:** class komponen

**Untuk apa:** collision karakter (berdiri, crouch). `ACharacter` memakai capsule sebagai root.

**Contoh implementasi:**

```cpp
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"

AKarakterLatihan::AKarakterLatihan()
{
    GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
}
```

**Yang terjadi:** radius 42, half-height 96 (tinggi total 192 cm). Mesh biasanya di-offset supaya kaki di tanah. Mengubah size runtime perlu hati-hati (stuck di langit-langit).

**Biasanya digabungkan dengan:** `UCharacterMovementComponent`, mesh.

**Jangan:** capsule terlalu kecil (masuk celah) atau terlalu besar (nyangkut pintu). Jangan menonaktifkan collision capsule lalu heran jatuh tembus.

## UBoxComponent overlap

**Tipe:** class (`UBoxComponent` / `UPrimitiveComponent` overlap)

**Untuk apa:** volume pemicu: pickup, checkpoint, zona toko. Query overlap, bukan blocking (sering).

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZonaToko.generated.h"

class UBoxComponent;

UCLASS()
class AZonaToko : public AActor
{
    GENERATED_BODY()

public:
    AZonaToko();

    UPROPERTY(VisibleAnywhere, Category = "Komponen")
    TObjectPtr<UBoxComponent> Area;

    virtual void BeginPlay() override;

    UFUNCTION()
    void SaatMulaiOverlap(
        UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);
};
```

```cpp
#include "ZonaToko.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"

AZonaToko::AZonaToko()
{
    Area = CreateDefaultSubobject<UBoxComponent>(TEXT("Area"));
    SetRootComponent(Area);
    Area->SetBoxExtent(FVector(150.f, 150.f, 100.f));
    Area->SetCollisionProfileName(TEXT("Trigger"));
    Area->SetGenerateOverlapEvents(true);
}

void AZonaToko::BeginPlay()
{
    Super::BeginPlay();
    Area->OnComponentBeginOverlap.AddDynamic(this, &AZonaToko::SaatMulaiOverlap);
}

void AZonaToko::SaatMulaiOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (Cast<ACharacter>(OtherActor))
    {
        UE_LOG(LogTemp, Log, TEXT("Pemain masuk toko"));
    }
}
```

**Yang terjadi:** kotak 150×150×100 cm. Saat character masuk, log. `AddDynamic` **wajib** `UFUNCTION()` pada handler. Profile `Trigger` biasanya overlap, tidak block. Isi collision channel di project jika tidak jalan.

`OnComponentEndOverlap` untuk keluar zona.

**Biasanya digabungkan dengan:** `Cast`, tag, GameMode event.

**Jangan:** lupa `UFUNCTION` pada callback (bind gagal senyap/crash). Jangan overlap + `Destroy` tanpa filter (hancur karena brush). Jangan bind setiap Tick.

## SetRelativeLocation

**Tipe:** fungsi `USceneComponent`

**Untuk apa:** geser komponen terhadap parent, bukan dunia.

**Contoh implementasi:**

```cpp
void ATiangBendera::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const FVector Rel = TitikBendera->GetRelativeLocation();
    TitikBendera->SetRelativeLocation(Rel + FVector(0.f, 0.f, FMath::Sin(GetWorld()->GetTimeSeconds()) * 10.f * DeltaTime));
}
```

**Yang terjadi:** titik bendera berayun pelan di sumbu Z lokal. `SetWorldLocation` mengabaikan parent (posisi dunia mutlak).

**Biasanya digabungkan dengan:** animasi sederhana, offset kamera.

**Jangan:** mencampur relative/world tanpa gambar hirarki. Jangan Tick sinus jika Timeline/Anim cukup.

## Enhanced Input

**Tipe:** sistem input UE5 (modul `EnhancedInput`)

**Untuk apa:** memetakan tombol/gamepad ke **Input Action** asset, dengan trigger (Pressed, Hold, Pulse) dan value (bool, sumbu 1D/2D).

**Contoh implementasi:**

Alur resmi (bukan satu file):

1. Content Browser → Input → **Input Action** `IA_Pindah` (Value Axis2D).
2. **Input Action** `IA_Loncat` (Digital / bool).
3. **Input Mapping Context** `IMC_Pemain`: WASD → `IA_Pindah`, Space → `IA_Loncat`.
4. Di Pawn/Controller C++: pointer ke IMC + IA, `AddMappingContext`, `BindAction`.

Ini menggantikan `BindAxis("MoveForward")` string lama (`UInputComponent`). Enhanced Input lebih rapi, bisa prioritas context (UI vs gameplay).

**Yang terjadi:** menekan W mengirim nilai 2D ke callback `Pindah`. Context bisa ditambah/dihapus saat buka menu.

**Biasanya digabungkan dengan:** `APlayerController` / `ACharacter`, `UEnhancedInputLocalPlayerSubsystem`.

**Jangan:** mencampur Axis Mapping lama dan Enhanced tanpa rencana. Jangan hardcode key di C++ jika desainer harus remap — isi di IMC asset.

## UInputAction

**Tipe:** `UDataAsset` input

**Untuk apa:** satu “maksud”: Loncat, Serang, Pindah, Lihat. Bukan key fisik.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "KarakterLatihan.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class AKarakterLatihan : public ACharacter
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputMappingContext> MappingPemain;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> AksiPindah;

    UPROPERTY(EditDefaultsOnly, Category = "Input")
    TObjectPtr<UInputAction> AksiLoncat;

protected:
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

    void Pindah(const FInputActionValue& Nilai);
    void LoncatMulai(const FInputActionValue& Nilai);
};
```

**Yang terjadi:** di Class Defaults, kamu drag asset `IA_Pindah` ke `AksiPindah`. C++ tidak peduli apakah W, stick, atau panah — itu urusan Mapping Context.

Value type action harus cocok: Axis2D → `Get<FVector2D>()`.

**Biasanya digabungkan dengan:** IMC, `BindAction`, `EditDefaultsOnly`.

**Jangan:** `FindObject` path string rapuh di runtime jika bisa `UPROPERTY`. Jangan salah value type (bool vs axis).

## UInputMappingContext

**Tipe:** `UDataAsset` kumpulan binding

**Untuk apa:** satu set “saat bermain” atau “saat menu”: key → action + modifier (Negate, Swizzle).

**Contoh implementasi:**

Tidak ditulis penuh di C++. Di Editor: tambah mapping `IA_Pindah` ke 2D (WASD: W = Y+, S = Y- + Negate, dll. atau satu mapping stick).

Di C++ kamu hanya menyimpan pointer dan `AddMappingContext(MappingPemain, 0)` — angka adalah prioritas (lebih tinggi menang saat konflik).

**Yang terjadi:** menambah IMC menu prioritas tinggi menimpa serang; menghapus IMC mengembalikan gameplay.

**Biasanya digabungkan dengan:** subsystem local player, UI.

**Jangan:** puluhan IMC tanpa prioritas. Jangan lupa remove context saat tidak relevan (menu+gerak bersamaan).

## BindAction

**Tipe:** fungsi `UEnhancedInputComponent`

**Untuk apa:** menghubungkan action ke method C++ pada trigger tertentu.

**Contoh implementasi:**

```cpp
#include "KarakterLatihan.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

void AKarakterLatihan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
    if (!EIC)
    {
        UE_LOG(LogTemp, Error, TEXT("Pakai Enhanced Input Component di project settings"));
        return;
    }

    if (AksiPindah)
    {
        EIC->BindAction(AksiPindah, ETriggerEvent::Triggered, this, &AKarakterLatihan::Pindah);
    }
    if (AksiLoncat)
    {
        EIC->BindAction(AksiLoncat, ETriggerEvent::Started, this, &AKarakterLatihan::LoncatMulai);
    }
}

void AKarakterLatihan::Pindah(const FInputActionValue& Nilai)
{
    const FVector2D Sumbu = Nilai.Get<FVector2D>();
    const FRotator Yaw(0.f, GetControlRotation().Yaw, 0.f);
    const FVector Maju = FRotationMatrix(Yaw).GetUnitAxis(EAxis::X);
    const FVector Kanan = FRotationMatrix(Yaw).GetUnitAxis(EAxis::Y);
    AddMovementInput(Maju, Sumbu.Y);
    AddMovementInput(Kanan, Sumbu.X);
}

void AKarakterLatihan::LoncatMulai(const FInputActionValue& Nilai)
{
    (void)Nilai;
    Jump();
}
```

**Yang terjadi:** selama action “triggered” (stick/WASD ditahan), `Pindah` menambah movement character. Saat loncat **Started** (baru ditekan), `Jump()`. `Triggered` untuk analog terus-menerus; `Started`/`Completed` untuk tombol sekali.

Project Settings → Input → Default Input Component Class harus **EnhancedInputComponent**.

**Biasanya digabungkan dengan:** `AddMovementInput`, look `AddControllerYawInput`.

**Jangan:** `BindAction` pada `UInputComponent` lama tanpa cast. Jangan `Triggered` pada loncat (berulang tiap frame = spam jump). Jangan bind jika action pointer null tanpa log.

## FInputActionValue

**Tipe:** struct nilai input

**Untuk apa:** membawa bool / float / `FVector2D` / `FVector` sesuai asset.

**Contoh implementasi:**

```cpp
void AKarakterLatihan::Lihat(const FInputActionValue& Nilai)
{
    const FVector2D Delta = Nilai.Get<FVector2D>();
    AddControllerYawInput(Delta.X);
    AddControllerPitchInput(Delta.Y);
}
```

**Yang terjadi:** mouse/stick 2D memutar kontrol yaw/pitch. `Get<T>()` salah tipe → nilai 0 / assert tergantung build. Cocokkan dengan Value Type di `UInputAction`.

`IsNonZero()`, `Get<bool>()` untuk digital.

**Biasanya digabungkan dengan:** look, move, axis pintu.

**Jangan:** `Get<float>` pada Axis2D. Jangan lupa sensitivity (kali skala di IMC modifier atau C++).

## AddMappingContext

**Tipe:** fungsi `UEnhancedInputLocalPlayerSubsystem`

**Untuk apa:** mengaktifkan IMC untuk local player.

**Contoh implementasi:**

```cpp
void AKarakterLatihan::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Sub =
                ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            if (MappingPemain)
            {
                Sub->AddMappingContext(MappingPemain, 0);
            }
        }
    }
}
```

**Yang terjadi:** setelah possess, mapping WASD hidup. Dedicated server tidak punya local player — bind di pawn yang possessed client. Beberapa template menambah context di PlayerController `BeginPlay` / `OnPossess` — itu juga benar, bahkan lebih rapi untuk split responsibility.

`RemoveMappingContext` saat mati/menu.

**Biasanya digabungkan dengan:** `SetupPlayerInputComponent`, IMC asset.

**Jangan:** `AddMappingContext` berulang tiap Tick. Jangan lupa include `EnhancedInputSubsystems.h`. Jangan mengharapkan input di dedicated server.

## Input Action di Build.cs

**Tipe:** konfigurasi modul

**Untuk apa:** agar `#include "EnhancedInputComponent.h"` resolve.

**Contoh implementasi:**

```csharp
// NamaProyek.Build.cs
PublicDependencyModuleNames.AddRange(new string[]
{
    "Core",
    "CoreUObject",
    "Engine",
    "InputCore",
    "EnhancedInput"
});
```

**Yang terjadi:** UBT menautkan modul. Tanpa ini: compile error “cannot open include file”. Setelah ubah `Build.cs`, generate project files / restart sering perlu.

**Biasanya digabungkan dengan:** semua file 09 Enhanced Input.

**Jangan:** menambah modul acak. Jangan mengedit `Build.cs` engine.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** input “tidak jalan” dan overlap senyap.

**Contoh implementasi:**

```cpp
void AKarakterLatihan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (!AksiPindah)
    {
        UE_LOG(LogTemp, Error, TEXT("AksiPindah kosong — assign di Class Defaults"));
    }
}
```

**Yang terjadi:** lupa drag asset adalah sebab #1. Sebab #2: Default Input Component Class masih lama. Sebab #3: IMC tidak di-`AddMappingContext`. Sebab #4: Pawn tidak possessed.

Overlap: handler bukan `UFUNCTION`, atau collision preset tidak generate overlap, atau object type tidak overlap channel.

**Biasanya digabungkan dengan:** file 10 possess, file 12 resep gerak.

**Jangan:** menyalahkan “C++ rusak” sebelum cek asset pointer, project settings, dan possess.
