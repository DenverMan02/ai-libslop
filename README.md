# ai-libslop

PvZ2 9.6.1 ARM64 library based on Chairlib (by renojson) with SnowieLib compatibility and Pool Stage module integration.

## Features
- **Chairlib base**: Restores and introduces custom zombies, plants, grid items, and stage modules.
- **SnowieLib compatibility**: Coexists with SnowieLib by disabling conflicting PlantType/ZombieType registry hooks, camel framework hooks, wave hook, and piano hook.
- **Corpse HP fix**: Proper headless/corpse state transitions when reaching 0 HP.
- **Pool Stage**: Integrated PoolStage and PoolStageProperties modules with toxic water / tide water region handling.
