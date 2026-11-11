# Corpse HP removal v2

This version removes Chairlib's early head-drop transition that left zombies with positive HP after entering the bleeding/headless state.

## What changed

- Restored `HeadDropFraction` to `0.3f` so the property itself remains unchanged.
- Removed the Chairlib branch that entered bleeding/head-drop when HP was merely below `HeadDropFraction * max HP`.
- Kept head-drop handling in the zero-HP death path, matching the observed vanilla 9.6.1 control flow around `0xC450BC`.
- No artificial `m_hitpoints = 0.0f` assignment is used to fake the result.
- The existing armor overflow handling and other Pharaoh code remain untouched in this revision.
- The SnowieLib compatibility changes from the previous build remain, including disabling the Camel, Piano, Board Wave, and PlantType/ZombieType conflict hooks.

## Expected behavior

A zombie should reach 0 HP before entering the head-drop/bleeding state. Head drop should still occur when applicable, but there should be no positive HP remaining in the corpse state.
