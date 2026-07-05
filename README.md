# 🚀 Tank Battle Blaster (Unreal Engine)

## Overview
This project is a **third-person tank battle game** built in Unreal Engine.  
The player controls a tank to destroy enemy AI turrets, with full gameplay loop including **UI, AI, damage system, level management, and effects**.  
It was developed as part of my **Unreal learning journey and portfolio expansion**.

## 🎮 Gameplay
- Control the **tank base** with WASD keys for movement.
- Rotate the **tank top** using mouse cursor position for aiming.
- Fire projectiles with left mouse click.
- Enemy AI turrets detect the player within range and shoot projectiles.
- Victory message displayed once all turrets are destroyed, followed by level progression.

## 🔹 Key Features & Learning
- **UI Systems**: Countdown timer, input enabling after timer ends, victory messages, level transitions.
- **Player Controls**: Keyboard + mouse integration, aiming and shooting mechanics.
- **Enemy AI**: Range detection using vector calculations, projectile firing logic.
- **Damage & Health System**: Projectiles apply damage, health components reduce HP, destruction triggers particle & sound effects.
- **Level Management**: Tracks destroyed turrets, loads next level, loops back to first level after completion.
- **Immersion Effects**: Camera shake on hits and destruction events.

## 🛠️ Unreal Functions Used
- `MessageTextBlock->SetText` for UI updates  
- `UGameplayStatics::OpenLevel`, `UGameplayStatics::GetAllActorsOfClass` for level management  
- `CreateWidget`, `ScreenMessageWidget->AddToPlayerScreen()` for UI creation  
- `GetWorldTimerManager().SetTimer` for countdown logic  
- `GetOwner()->OnTakeAnyDamage`, `UGameplayStatics::ApplyDamage` for damage handling  
- `UNiagaraFunctionLibrary::SpawnSystemAtLocation` for particle effects  
- `UGameplayStatics::PlaySoundAtLocation` for sound effects  
- `PlayerController->ClientStartCameraShake` for camera shake  
- `PlayerController->GetHitResultUnderCursor`, `EnhanceInputComp->BindAction` for input & aiming  
- `FVector::Dist` for AI range detection  
- `GetWorld()->SpawnActor` for projectile spawning  

## 🚀 Why This Project Matters
This project strengthened my skills in **Unreal gameplay framework, UI integration, AI systems, and event-driven programming**, while reinforcing my adaptability across **Unity (8+ years)** and **Unreal (1 year)**.

## ▶️ How to Run
1. Clone the repository.  
2. Open the project in Unreal Engine (5.x recommended).  
3. Build and run in editor or package for Windows.  
4. Play as the tank, destroy enemy turrets, and progress through levels!  

---
