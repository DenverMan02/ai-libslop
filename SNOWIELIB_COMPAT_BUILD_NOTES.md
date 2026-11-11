# Updated Chairlib build tree

This tree is prepared from the uploaded ARM64 Chairlib source for coexistence with SnowieLib.

Disabled for compatibility:
- PlantType constructor/mapper/reflection hooks
- ZombieType constructor/typename-map/reflection hooks
- Board Wave hook
- Piano list hook
- All hooks inside ZombieCamel.cpp

The actual Chairlib content and its other hooks are otherwise left intact.

## Build

Build `Release|ARM64` with Visual Studio 2022 and the Android C++/NDK workload/toolchain. The original project targeted ARM64.

`build_release_arm64.bat` is a convenience wrapper for `msbuild`.

This environment does not contain an Android NDK, so no Android `.so` binary is claimed as compiled here.


## Additional SnowieLib compatibility change: Camel framework disabled entirely

The Chairlib README warns that **all Camel hooks** must be disabled when using SnowieLib. For the safe build, the Camel framework is disabled entirely:
- `ZombieCamel.cpp` implementation disabled.
- `ZombieCamel.h` declarations disabled.
- `ZombieCamel` / `ZombieCamelTouch` includes and `modInit()` calls removed from `Main.cpp`.
- Camel translation units removed from the Visual Studio project/filter list.

This intentionally gives up Chairlib's Camel-specific framework/customization rather than relying only on hook comments.
