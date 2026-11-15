# Deadly Dave voor LG webOS TV

Bouw vanuit de checkout in Ubuntu onder WSL.

```sh
bash scripts/build-webos.sh
```

De build gebruikt CMake, de [webOS ARM-toolchain](https://github.com/webosbrew/native-toolchain)
en `ares-package` uit de webOS CLI. Standaard zoekt het script de SDK in
`~/arm-webos-linux-gnueabi_sdk-buildroot`. Stel `WEBOS_SDK` in als die elders
staat. Het script downloadt en controleert de vastgelegde SDL-webOS-release.

Het IPK staat in `dist/webos/` en bevat de ARM-binary, de Wayland-versie van
SDL2, de spelbestanden en het launchericoon. Op de afstandsbediening beweeg je
met de pijltjes, spring je met Omhoog, schiet je met OK (Enter) en zet je de
jetpack aan of uit met 0. Met Back open of sluit je het pauzemenu. Kies
`QUIT` in dat menu om af te sluiten. Instellingen en highscores gebruiken
de SDL-voorkeursmap van de app.

```sh
ares-install -d G3 dist/webos/com.timmods.deadlydave_0.1.16_arm.ipk
ares-launch -d G3 com.timmods.deadlydave
```

Vervang `G3` door de apparaatnaam uit `ares-setup-device --list`.
