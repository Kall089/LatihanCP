# 10 — GameMode, Pawn, Character, Controller

[← Komponen dan input](09-unreal-komponen-input.md) · [README](README.md) · [Lanjut: Blueprint vs C++ →](11-unreal-blueprint-vs-cpp.md)

Unreal memisahkan **aturan pertandingan** (GameMode), **tubuh di dunia** (Pawn/Character), dan **yang mengendalikan** (Controller). Memahami tiga ini mencegah “input tidak jalan” dan “skor hilang saat respawn”. API publik, untuk *membuat* game.

## Daftar isi

- [AGameModeBase](#agamemodebase)
- [kelas default GameMode](#kelas-default-gamemode)
- [AGameStateBase](#agamestatebase)
- [APlayerState](#aplayerstate)
- [APawn](#apawn)
- [ACharacter](#acharacter)
- [UCharacterMovementComponent](#ucharactermovementcomponent)
- [AController](#acontroller)
- [APlayerController](#aplayercontroller)
- [AAIController](#aaicontroller)
- [Possess dan UnPossess](#possess-dan-unpossess)
- [SetupPlayerInputComponent](#setupplayerinputcomponent)
- [RestartPlayer](#restartplayer)
- [GetPlayerController dan GetPlayerPawn](#getplayercontroller-dan-getplayerpawn)
- [AHUD](#ahud)
- [APlayerStart](#aplayerstart)
- [World Settings](#world-settings)
- [Kesalahan umum bab ini](#kesalahan-umum-bab-ini)

## AGameModeBase

**Tipe:** class (aturan di **server** / standalone)

**Untuk apa:** siapa pawn-nya, kapan spawn, apakah match mulai, login pemain. Tidak ada di client murni — jangan simpan skor yang harus dilihat semua orang hanya di sini (itu GameState).

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TokoGameMode.generated.h"

UCLASS()
class ATokoGameMode : public AGameModeBase
{
    GENERATED_BODY()

public:
    ATokoGameMode();

    UPROPERTY(EditDefaultsOnly, Category = "Toko")
    int32 SkorMenang = 10;

    virtual void BeginPlay() override;
};
```

```cpp
#include "TokoGameMode.h"
#include "TokoCharacter.h"
#include "TokoPlayerController.h"

ATokoGameMode::ATokoGameMode()
{
    DefaultPawnClass = ATokoCharacter::StaticClass();
    PlayerControllerClass = ATokoPlayerController::StaticClass();
}

void ATokoGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Match latihan, target skor %d"), SkorMenang);
}
```

**Yang terjadi:** saat dunia memakai GameMode ini, pemain baru mendapat `ATokoCharacter` dikendalikan `ATokoPlayerController`. Set juga di Editor: Project Settings / World Settings → GameMode Override, atau Class Defaults jika kamu sudah set di ctor — World Settings menimpa.

`AGameMode` (bukan Base) menambah flow match `InProgress`/`WaitingToStart`. Untuk latihan, `AGameModeBase` cukup.

**Biasanya digabungkan dengan:** `DefaultPawnClass`, GameState, PlayerStart.

**Jangan:** mereplikasi data UI dari GameMode ke client (object ini tidak ada di client). Jangan logic visual di GameMode.

## kelas default GameMode

**Tipe:** `TSubclassOf` member `AGameModeBase`

**Untuk apa:** memilih class yang di-spawn engine saat login / start.

**Contoh implementasi:**

```cpp
ATokoGameMode::ATokoGameMode()
{
    DefaultPawnClass = ATokoCharacter::StaticClass();
    PlayerControllerClass = ATokoPlayerController::StaticClass();
    HUDClass = ATokoHUD::StaticClass();
    GameStateClass = ATokoGameState::StaticClass();
    PlayerStateClass = ATokoPlayerState::StaticClass();
    SpectatorClass = ASpectatorPawn::StaticClass();
}
```

**Yang terjadi:** lima class terhubung. Jika `DefaultPawnClass` masih `ADefaultPawn` (kubus terbang), karakter kustommu tidak muncul — gejala “saya buat character tapi yang spawn cube”. Isi **Blueprint anak** lewat `TSubclassOf` di Defaults jika mesh/AnimBP ada di BP.

| Member | Peran |
| --- | --- |
| `DefaultPawnClass` | tubuh default |
| `PlayerControllerClass` | otak pemain |
| `HUDClass` | HUD lokal (client) |
| `GameStateClass` | state match yang mereplikasi |
| `PlayerStateClass` | skor/nama per pemain, mereplikasi |

**Biasanya digabungkan dengan:** World Settings, Blueprint parent.

**Jangan:** hanya membuat class tanpa memasang di GameMode. Jangan `HUDClass` di dedicated server mengharapkan gambar (HUD lokal).

## AGameStateBase

**Tipe:** class (state pertandingan yang **ada di server dan client**)

**Untuk apa:** waktu match, skor tim, daftar player state — data yang semua orang boleh tahu.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "TokoGameState.generated.h"

UCLASS()
class ATokoGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Toko")
    int32 TotalKoinTerkumpul = 0;

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
```

```cpp
#include "TokoGameState.h"
#include "Net/UnrealNetwork.h"

void ATokoGameState::GetLifetimeReplicatedProps(
    TArray<FLifetimeProperty>& OutLifetimeProps) const
{
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(ATokoGameState, TotalKoinTerkumpul);
}
```

**Yang terjadi:** server menambah `TotalKoinTerkumpul`; client melihat angka sama (setelah replikasi). Widget membaca GameState, bukan GameMode.

Akses: `GetWorld()->GetGameState<ATokoGameState>()`. Bisa null di awal.

**Biasanya digabungkan dengan:** `DOREPLIFETIME`, UI, `HasAuthority` saat menulis.

**Jangan:** menulis GameState dari client. Jangan data rahasia musuh (fog of war) di sini tanpa filter.

## APlayerState

**Tipe:** class per-pemain yang mereplikasi

**Untuk apa:** skor, nama, ping. Hidup lebih lama daripada pawn (pawn bisa mati/respawn, PlayerState tetap).

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "TokoPlayerState.generated.h"

UCLASS()
class ATokoPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
    UPROPERTY(Replicated, BlueprintReadOnly, Category = "Toko")
    int32 Koin = 0;

    virtual void GetLifetimeReplicatedProps(
        TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};

// .cpp: DOREPLIFETIME(ATokoPlayerState, Koin);
```

**Yang terjadi:** mengambil koin di server: `Cast<ATokoPlayerState>(Pawn->GetPlayerState())->Koin++`. UI client membaca koin. Respawn pawn baru, koin tidak reset (kecuali kamu reset).

**Biasanya digabungkan dengan:** GameState, `GetPlayerState`, HUD.

**Jangan:** simpan koin hanya di pawn. Jangan ubah dari client.

## APawn

**Tipe:** class (tubuh yang bisa di-possess)

**Untuk apa:** objek dikendalikan controller: kendaraan, spectator, karakter kustom tanpa `ACharacter`.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "DroneLatihan.generated.h"

UCLASS()
class ADroneLatihan : public APawn
{
    GENERATED_BODY()

public:
    ADroneLatihan();

    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
```

**Yang terjadi:** drone adalah pawn: bisa `Possess`, punya `AddMovementInput` jika ada movement component yang kamu pasang. **Tidak** otomatis punya capsule + jalan + lompat — itu `ACharacter`.

`ADefaultPawn` (template) adalah pawn flying dengan collision sederhana.

**Biasanya digabungkan dengan:** `UFloatingPawnMovement`, kamera, Controller.

**Jangan:** mengira semua pawn bisa `Jump()`. Jangan input di pawn yang tidak possessed.

## ACharacter

**Tipe:** class (pawn + capsule + mesh + character movement)

**Untuk apa:** orang yang berjalan, jatuh, lompat, crouch — 90% latihan FPS/third person.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TokoCharacter.generated.h"

UCLASS()
class ATokoCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ATokoCharacter();

protected:
    virtual void BeginPlay() override;
    virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
```

```cpp
#include "TokoCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

ATokoCharacter::ATokoCharacter()
{
    bUseControllerRotationYaw = false;
    GetCharacterMovement()->bOrientRotationToMovement = true;
    GetCharacterMovement()->MaxWalkSpeed = 450.f;
}
```

**Yang terjadi:** karakter menoleh ke arah gerak, kecepatan jalan 450 cm/s. `Jump()` dan gravity sudah ada di movement component. Mesh/AnimBP biasanya di Blueprint anak agar art tidak di-path C++.

**Biasanya digabungkan dengan:** Enhanced Input, spring arm, `GetCapsuleComponent`.

**Jangan:** menulis ulang gravitasi di Tick. Jangan `SetActorLocation` tiap frame menimpa movement (bertarung dengan komponen).

## UCharacterMovementComponent

**Tipe:** class komponen

**Untuk apa:** berjalan, jatuh, terbang, swim, prediksi client — otak gerak `ACharacter`.

**Contoh implementasi:**

```cpp
void ATokoCharacter::BeginPlay()
{
    Super::BeginPlay();
    UCharacterMovementComponent* Move = GetCharacterMovement();
    Move->JumpZVelocity = 500.f;
    Move->AirControl = 0.15f;
    Move->MaxAcceleration = 1500.f;
}
```

**Yang terjadi:** lompat lebih tinggi, kontrol udara sedikit, akselerasi 1500. Property ini juga di Details. Mengubah `MaxWalkSpeed` saat sprint adalah pola resmi (`MaxWalkSpeed = 750` lalu kembali).

**Biasanya digabungkan dengan:** `AddMovementInput`, `Jump`, crouch `bCanCrouch`.

**Jangan:** meniru gerak dengan `AddActorWorldOffset` pada Character tanpa menonaktifkan movement — hasil bergetar. Jangan mengubah ratusan flag tanpa baca tooltip.

## AController

**Tipe:** class (otak, **bukan** mesh)

**Untuk apa:** possess pawn, rotasi kontrol, keputusan AI atau input manusia. Hidup terpisah dari tubuh.

**Contoh implementasi:**

```cpp
AController* Otak = GetController();
if (IsValid(Otak))
{
    APawn* Tubuh = Otak->GetPawn();
    (void)Tubuh;
}
```

**Yang terjadi:** dari character, `GetController()` adalah PlayerController atau AIController. Dari controller, `GetPawn()` tubuh saat ini. Saat mati, kamu bisa `UnPossess` lalu possess pawn baru tanpa menghancurkan controller.

**Biasanya digabungkan dengan:** `Possess`, PlayerState (controller punya player state).

**Jangan:** menaruh mesh di controller. Jangan mengira controller hancur saat pawn `Destroy` (tidak otomatis).

## APlayerController

**Tipe:** class controller manusia (lokal + koneksi)

**Untuk apa:** input, kamera/HUD, RPC pemain, UI. Satu per pemain.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TokoPlayerController.generated.h"

UCLASS()
class ATokoPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

    UFUNCTION(BlueprintCallable, Category = "Toko")
    void BukaMenuToko();
};
```

```cpp
#include "TokoPlayerController.h"

void ATokoPlayerController::BeginPlay()
{
    Super::BeginPlay();
    bShowMouseCursor = false;
}

void ATokoPlayerController::BukaMenuToko()
{
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
```

**Yang terjadi:** saat main, kursor tersembunyi. `BukaMenuToko` menyerahkan input ke UI. Kembalikan `FInputModeGameOnly()` saat tutup. Enhanced Input context sering ditambah di sini (`OnPossess`).

RPC `Server...` sering diletakkan di PlayerController karena jelas pemilik koneksinya.

**Biasanya digabungkan dengan:** HUD/Widget, Enhanced Input subsystem, `GetPawn`.

**Jangan:** input mode UI tanpa cara keluar. Jangan logika score-only di PC tanpa PlayerState jika multiplayer.

## AAIController

**Tipe:** class controller AI

**Untuk apa:** possess pawn NPC, Behavior Tree, `MoveToActor`. Bukan PlayerController.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TokoAIController.generated.h"

UCLASS()
class ATokoAIController : public AAIController
{
    GENERATED_BODY()

public:
    virtual void OnPossess(APawn* InPawn) override;
};
```

```cpp
#include "TokoAIController.h"

void ATokoAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
    // RunBehaviorTree(BTAsset);  // jika pakai AI Module
    UE_LOG(LogTemp, Log, TEXT("AI possess %s"), *GetNameSafe(InPawn));
}
```

**Yang terjadi:** saat NPC di-spawn dengan `AutoPossessAI` atau `SpawnDefaultController`, AI controller ini menempel. Modul `AIModule` perlu di `Build.cs` untuk `AAIController` / BT.

**Biasanya digabungkan dengan:** Behavior Tree, Blackboard, `NavMesh`.

**Jangan:** `APlayerController` pada NPC. Jangan `MoveTo` tanpa NavMesh (gagal diam).

## Possess dan UnPossess

**Tipe:** fungsi `AController`

**Untuk apa:** mengikat/melepas otak ke tubuh.

**Contoh implementasi:**

```cpp
#include "TokoPlayerController.h"
#include "TokoCharacter.h"

void ATokoPlayerController::GantiTubuh(ATokoCharacter* Baru)
{
    if (!IsValid(Baru))
    {
        return;
    }
    UnPossess();
    Possess(Baru);
}
```

**Yang terjadi:** input dan view pindah ke `Baru`. Pawn lama tidak otomatis hancur. GameMode `RestartPlayer` memakai pola spawn + possess secara resmi.

`AutoPossessPlayer` di pawn instance: Player 0 possess saat mulai (berguna tes, hati-hati vs GameMode spawn ganda).

**Biasanya digabungkan dengan:** respawn, kendaraan (possess mobil, unpossess karakter).

**Jangan:** possess dari client sembarangan di multiplayer (server authority). Jangan possess pawn yang sudah dimiliki tanpa unpossess.

## SetupPlayerInputComponent

**Tipe:** fungsi virtual `APawn`

**Untuk apa:** bind input **setelah** pawn akan dikendalikan. Dipanggil engine saat possess / setup.

**Contoh implementasi:**

Lihat file 09 `BindAction`. Inti:

```cpp
void ATokoCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    // Bind Enhanced Input di sini
}
```

**Yang terjadi:** tanpa override + bind, karakter diam meski IMC sudah di-add (tergantung di mana kamu bind). Beberapa orang bind di PlayerController — sah, tapi pawn movement sering di pawn/`SetupPlayerInputComponent`.

**Biasanya digabungkan dengan:** Enhanced Input, `Super::`.

**Jangan:** bind di constructor pawn. Jangan bind duplikat tanpa clear (double move).

## RestartPlayer

**Tipe:** fungsi `AGameModeBase`

**Untuk apa:** spawn pawn default untuk controller dan possess — respawn resmi.

**Contoh implementasi:**

```cpp
#include "TokoGameMode.h"

void ATokoGameMode::RespawnPemain(AController* C)
{
    if (!IsValid(C))
    {
        return;
    }
    RestartPlayer(C);
}
```

**Yang terjadi:** engine mencari `APlayerStart` (atau titik lain), spawn `DefaultPawnClass`, possess. Override `RestartPlayer` / `FindPlayerStart` / `ChoosePlayerStart` untuk aturan spawn kustom (tim, checkpoint).

**Biasanya digabungkan dengan:** `APlayerStart`, death, `PlayerState` yang tetap.

**Jangan:** `SpawnActor` pawn + lupa possess. Jangan respawn tiap frame.

## GetPlayerController dan GetPlayerPawn

**Tipe:** fungsi `UGameplayStatics`

**Untuk apa:** mengambil pemain lokal / indeks (0 = player pertama).

**Contoh implementasi:**

```cpp
#include "Kismet/GameplayStatics.h"
#include "TokoCharacter.h"

void ContohCariPemain(const UObject* WorldContext)
{
    APawn* P = UGameplayStatics::GetPlayerPawn(WorldContext, 0);
    APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContext, 0);
    if (IsValid(P))
    {
        UE_LOG(LogTemp, Log, TEXT("Pawn %s"), *P->GetName());
    }
    (void)PC;
}
```

**Yang terjadi:** di standalone, indeks 0 adalah kamu. Di split-screen, 1, 2, ... Dedicated server: hati-hati “player 0”. Untuk referensi umum, `UGameplayStatics::GetAllActorsOfClass` mahal — cache di `BeginPlay` jika perlu.

**Biasanya digabungkan dengan:** kamera follow, UI, AI mengejar pemain (lebih baik Perception).

**Jangan:** tiap Tick `GetAllActorsOfClass`. Jangan andalkan index 0 di server multi-client tanpa `PlayerController` yang benar.

## AHUD

**Tipe:** class gambar 2D lama / debug

**Untuk apa:** `DrawText` debug, atau jembatan ke widget. Game baru lebih sering **UMG Widget** dari PlayerController.

**Contoh implementasi:**

```cpp
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TokoHUD.generated.h"

UCLASS()
class ATokoHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;
};
```

```cpp
#include "TokoHUD.h"

void ATokoHUD::DrawHUD()
{
    Super::DrawHUD();
    DrawText(TEXT("Toko latihan"), FLinearColor::White, 20.f, 20.f);
}
```

**Yang terjadi:** teks sudut kiri atas tiap frame (debug). Produksi: `CreateWidget` + `AddToViewport` di PlayerController. `HUDClass` di GameMode menentukan class ini.

**Biasanya digabungkan dengan:** GameMode `HUDClass`, debug score.

**Jangan:** UI kompleks hanya dengan `DrawHUD`. Jangan `DrawHUD` berat (texture load).

## APlayerStart

**Tipe:** actor titik spawn

**Untuk apa:** menandai lokasi/rotasi munculnya pawn.

**Contoh implementasi:**

Tidak wajib C++. Taruh `PlayerStart` di level. Custom:

```cpp
// GameMode override singkat
AActor* ATokoGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
    // panggil Super atau pilih PlayerStart bertag "Toko"
    return Super::ChoosePlayerStart_Implementation(Player);
}
```

**Yang terjadi:** `RestartPlayer` memakai start yang dipilih. Beberapa `PlayerStart` + tag membedakan tim. Jika tidak ada, engine memakai fallback (bisa 0,0,0 atau warning).

**Biasanya digabungkan dengan:** GameMode, navmesh, overlap “zona aman”.

**Jangan:** menaruh start di dalam collision (stuck). Jangan lupa rotasi hadap.

## World Settings

**Tipe:** setting per-level di Editor

**Untuk apa:** **GameMode Override** level ini, daming, world partition — menimpa project default.

**Contoh implementasi:**

Tidak ada `main()`. Di Editor: Window → World Settings → GameMode Override = `BP_TokoGameMode` (anak `ATokoGameMode`).

**Yang terjadi:** level “Toko” memakai mode toko; level “Menu” bisa mode lain. C++ ctor GameMode tetap default jika override tidak diisi.

**Biasanya digabungkan dengan:** beberapa peta, tes cepat.

**Jangan:** bingung “class sudah benar di C++ tapi level memakai override lama”. Cek World Settings dulu.

## Kesalahan umum bab ini

**Tipe:** catatan praktik

**Untuk apa:** spawn cube, input mati, skor hilang, AI diam.

**Contoh implementasi:**

```cpp
void ATokoGameMode::BeginPlay()
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Pawn default: %s"),
           *GetNameSafe(DefaultPawnClass.Get()));
}
```

**Yang terjadi:** log nama class pawn. Jika `DefaultPawn`, kamu belum memasang karakter. Checklist: GameMode terpasang (World Settings) → DefaultPawnClass benar → PlayerStart ada → Character possessed → IMC + bind → EnhancedInput module.

Skor hilang: disimpan di pawn yang di-`Destroy`. Pindah ke PlayerState.

**Biasanya digabungkan dengan:** file 09 input, file 12 resep.

**Jangan:** menumpuk `AutoPossessPlayer` + GameMode spawn (dua tubuh). Jangan menulis skor ke GameMode untuk HUD client.
