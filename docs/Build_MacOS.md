## git clone repo

```
git clone https://github.com/MatsuriDayo/nekoray.git --recursive
```

## Prerequisites

1. install `CMake` `Ninja` `npm`
2. install Qt 6 (`brew install qt`)
3. install `appdmg` (`sudo npm install -g appdmg`)

## CMake parameters

same as Build_Linux

## C++ part

### Compile and install C/C++ dependencies 


```shell
./libs/build_deps_all.sh
```

### Start compiling

```shell
mkdir build
cd build
cmake -GNinja -DQT_VERSION_MAJOR=6 -DCMAKE_BUILD_TYPE=Release -DNKR_PACKAGE_MACOS=1 ..
ninja
```

### Go parts

./libs/build_go.sh

refer to [Build_Core.md](./Build_Core.md)


### Prepare core

Put `nekoray_core` `nekobox_core` into `build/nekoray.app/Contents/MacOS`

### geo（optional）

```shell
curl -Lso build/nekoray.app/Contents/MacOS/geoip.dat "https://github.com/Loyalsoldier/v2ray-rules-dat/releases/latest/download/geoip.dat"
curl -Lso build/nekoray.app/Contents/MacOS/geosite.dat "https://github.com/v2fly/domain-list-community/releases/latest/download/dlc.dat"
curl -Lso build/nekoray.app/Contents/MacOS/geoip.db "https://github.com/SagerNet/sing-geoip/releases/latest/download/geoip.db"
curl -Lso build/nekoray.app/Contents/MacOS/geosite.db "https://github.com/SagerNet/sing-geosite/releases/latest/download/geosite.db"
```

If the geo file is not included in the package, it can be set in the application

### Pack nekoray to dmg

```shell
appdmg appdmg.json /path/to/nekoray.dmg
```
