## Alpha Ring
### A Modding Tool for MCC

[![Build status](https://ci.appveyor.com/api/projects/status/o3qbtc7jirw81xmb?svg=true)](https://ci.appveyor.com/project/WinterSquire/alpharing)

### Showcase

![](https://raw.githubusercontent.com/WinterSquire/Images/master/AlphaRing/Camera.PNG)

![](https://raw.githubusercontent.com/WinterSquire/Images/master/AlphaRing/Object.PNG)

![](https://raw.githubusercontent.com/WinterSquire/Images/master/AlphaRing/Splitscreen%208%20players.png)

![](https://raw.githubusercontent.com/WinterSquire/Images/master/AlphaRing/Splitscreen%20H3.PNG)

![](https://raw.githubusercontent.com/WinterSquire/Images/master/AlphaRing/Splitscreen%20With%20Mod.PNG)

### Features
* Splitscreen (all games)
* Camera Tool (H3)
* Object Browser (H3)

### Installation
Download the latest stable build from the [Releases](https://github.com/WinterSquire/AlphaRing/releases) page.

Place the DLL into the "Halo The Master Chief Collection\mcc\binaries\win64" directory and launch the game with EAC off.

For Running on Steam Deck/Linux, add the following command in the Steam Game Launch Options:
``` 
WINEDLLOVERRIDES="WTSAPI32=n,b" %command%
```

### Usage
Toggle menu: `F4` or `Controller Back` + `Controller Start`

When the menu is open, game input is disabled.

**Split Screen:**
- Supports 3 or 4 players in Halo 1, Halo 3, Halo 3: ODST, Halo: Reach, and Halo 4.
- Not supported for Co-Op in Halo 2. Attempting to do so will cause the game to get stuck at loading.
- For 3 or 4 players in Co-Op in Halo 1 and Halo 4, you can only start the game with a maximum of 2 players.
- In Halo 1, you need to add other players while loading the map on the counter in the Halo 1 Page, or if the map is loaded, restart the mission.
- In Halo 4, you need to add them while loading the map or in the game on the counter in the Alpha Ring Page.

### Credits
- [Assembly](https://github.com/XboxChaos/Assembly) for the tag group research.
- [Blender](https://github.com/blender/blender) for the bezier curve calculation.
- [Priception](https://github.com/Priception) for adding UI controller support and helping with the interface and crash issue.