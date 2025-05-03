# Unofficial Xenia: Femtofork for Fable II

This is an unofficial fork of [Xenia Canary](https://github.com/xenia-canary/xenia-canary);
it implements game-specific-hacks and features, unsuitable for mainline Xenia, that make emulating Fable II more pleasant.

## Differences from Xenia Canary summarised

Put briefly, these are the changes made by this fork:
- The black-texture-bug no longer occurs for the player-character nor their dog.
	- This applies even when resolution-scaling is active.
	- This applies only to the D3D12 renderer. The black-texture-bug still occurs with the Vulkan renderer (the ground is transparent with the Vulkan renderer, regardless).
- There are a few additional patches included in the `4D5307F1 - Fable II (GOTY_Platinum Edition).patch.toml` file.

## Caveats

This has been tested only with Fable II's GOTY/Platinum Edition, some fixes/features may not work for other versions of the game. \
Please file an issue if you find that a fix/feature does not work in your version of the game.

## Usage

**Do not report bugs experienced when using this fork to the Xenia team, without first verifying that they also occur in the latest version of Xenia Canary.** \
Similarly, do not request support from the Xenia team for features specific to this fork.

Avoid playing games other than Fable II with this fork—who knows what the game-specific-hacks could do elsewhere?

### Step-by-step

1. Download the latest build of this fork from the [Releases](https://github.com/just-harry/unofficial-xenia-femtofork-for-fable-ii/releases) page.
2. Follow [Xenia Canary's Quickstart guide](https://github.com/xenia-canary/xenia-canary/wiki/Quickstart).

### Migrating from Xenia Canary to this fork

It is recommended that you make a copy of the folder that your installation of Xenia Canary resides in, instead of overwriting its files.

Simply replace the existing files of Xenia Canary with the files you downloaded for this fork.

If you had configured game patches previously, you will need to reconfigure them if you overwrote the `patches` folder.

If you had previously enabled the `readback_resolve` setting to fix the black-texture-bug, you can disable it for a massive performance boost.

### Pre-existing save files affected by the black-texture-bug

If your Fable II save file is already affected by the black-texture-bug, loading the save file in this fork will not immediately fix it.

To fix the bug for the player-character, do something that will cause the game to regenerate the player-character's textures, such as changing the player-character's makeup, or altering their morality/purity significantly.

To fix the bug for the player-character's clothing (such as gloves), unequip and reequip the affected clothing.

The bug should be fixed for the player-character's dog simply by loading the save. If not, significantly alter the player-character's morality, or use a dog-breed-changing potion.

## Issues not solved

These issues, which are present in Xenia Canary, still occur in this fork:
- The exploding-dog-mesh bug is still present. (Sometimes, the dog's 3D model will glitch out and stretch out across the screen.)
- Lines of dialogue are sometimes skipped.
- When resolution-scaling is active, the player-character's textures and clothing textures may be corrupted in the "Clothing" menu. \
This corruption can cause the guest to crash. \
(**Save your game before entering the "Clothing" menu when playing with resolution scaling.**)
- The game may freeze during a loading-screen, necessitating a restart of the emulator.
- The guest may crash during a loading-screen.
- The guest may crash when navigating menus.
- The guest may crash at various other points.

## Differences from Xenia Canary detailed

Put less briefly, these are the changes made by this fork and the issues they solve.

### The dreaded black-texture-bug

With Xenia's default settings, when the player-character reaches adulthood, their textures will disappear ([pictured here](https://github.com/xenia-canary/game-compatibility/issues/74#issuecomment-1098722361))—the same applies to their dog. \
This isn't really a bug, it's more a consequence of the reality of emulating a unified-memory-architecture on machines with very much ununified-memory, but that doesn't make for a catchy name: so bug it is.

It is possible to avoid this issue in mainline Xenia by enabling the `readback_resolve` setting.
But this comes at great cost: doing so _obliterates_† the frame-rate, and if that alone wasn't bad enough, it also works only if resolution-scaling is disabled.

†. To contextualise this usage of _obliterates_: on the author's machine, with resolution-scaling disabled, and `readback_resolve` disabled, a frame-rate ranging between 180 and 400 can be achieved at the shore of Bower Lake (near the foresty bit towards the north-east).
When `readback_resolve` is enabled, the frame-rate instead ranges between **25** and 60. Those are the figures for a Ryzen 7950X3D paired with a Radeon 7900 XTX. _Obliterates_.

It is possible to workaround this issue by loading an affected save with `readback_resolve` enabled and resolution-scaling disabled, and then doing something that causes the player-character's textures (and their dog's) to be regenerated, and then saving the game.
Then, that save can be loaded with `readback_resolve` disabled and resolution-scaling enabled, and the textures will still be as they should... until the game regenerates the textures again for whatever reason. \
Possible? Yes. Practical? Only for masochists.

Now knowing that we can workaround the issue manually, surely we can automate a similar workaround? \
Indeed we can, and that's exactly what this fork does. \
The key insight here is that we don't need to have readback-resolve enabled all the time, we need it enabled only when the game is regenerating the textures affected by the issue.
In fact, we don't even need to enable it, we just need to perform readback when the affected textures are resolved.

So, after much exposition, what this fork does to prevent the black-texture-bug is: it simply performs readback only for the textures that need it, when they need it.

There's still one problem with that approach, however, in mainline Xenia readback-resolve works only when resolution-scaling is disabled. \
This fork lifts that limitation by downscaling upscaled textures when reading them back to the CPU. (So simple a solution it hurts).

### Additional Patches

This fork includes additional patches over the patch file for Fable II found in [Xenia Canary's Game Patches repo](https://github.com/xenia-canary/game-patches).

Those patches are:
1. A patch for skipping the unskippable intro videos that play when the game launches. (Authored by me).
2. A patch that prevents the irritating strobing of certain lighting effects when resolution scaling is enabled, which was authored by Guy, and taken from the description of [Guy's "Fable 2 PC Ultimate Guide"](https://www.youtube.com/watch?v=98ACUnkzqx0). (Cheers, Guy).

Some patches were removed, those patches are:
1. Guy's "Disable Texture Morphing" patch, as it shouldn't be needed with this fork. (Sorry, Guy).

