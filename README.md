# My custom QMK keymaps

## Background
This repository is for my custom QMK code for both keymaps (i.e. just the
keyboard layout and features), as well as code for a handwired keyboard (the
matrix and keyboard layout).

I keep this as as separate directory to the forked `qmk_firmware` directory and
use the `setup` script to create symlinks into the relevant directories in
`qmk_firmware` so that I can build the firmware for my boards and layouts. I
shamelessly stole this idea from someone else's QMK configs, but I can't remember
which setup now, I'm afraid. I'm happy to include a link if someone recognises
it.

## TOTEM
Currently (December 2023) my daily driver.

I have a wired and a BLE version of the [TOTEM keyboard](https://github.com/GEIGEIGEIST/TOTEM/tree/main), and this firmware obviously runs the wired version (I have a [ZMK version too](https://github.com/bsag/zmk-config-bsag)). I started with @GEIGEIGEIST's own version of a QMK layout, then tweaked a lot. The layout itself and organisation of the layers is heavily influenced by [miryoku](https://github.com/manna-harbour/miryoku) (hence, 'miryokuish'), but it also uses ideas for combos and key overrides from [urob's config](https://github.com/urob/zmk-config/tree/main), like making `shift+,` into semi-colon, `shift+.` into colon, and `shift+?` into exclamation mark. 

I rely heavily on urob's 'Timeless Homerow Mods' in ZMK, and in searching for an equivalent for that in QMK, I found [Suraj's brilliant bilateral combinations](https://sunaku.github.io/home-row-mods.html#patches), which I use by simply forking his version of QMK and adding the config values he suggests. I have long been an fan of Home Row Mods (aka HRM), but they are not without their compromises of delays to typing of accidentally activating modifiers, but both of these solutions have pretty much removed all of those compromises and made typing feel completely natural, while enjoying super-convenient and ergonomic access to all my modifiers on the home row. I will gradually port this basic keymap and the HRM setup to all my keyboards, whether wired or BLE.

Build with:

```sh
qmk compile -kb totem -km miryokuish
```

## hwcrkbd
This is a handwired keyboard I built based around the Corne keyboard. It has
OLED screens and mini-E RGB LEDs.

Build with:

```sh
qmk compile -kb hwcrkbd -km bsag
```

## mini3x5
This is a keymap for a 34 key [Ferris Sweep v2.1](https://github.com/davidphilipbarr/Sweep) which is a super-compact 3x5+2 Kailh Choc keyboard. I've taken inspiration
from a lot of other users' keymaps:

- [Layer arrangement](https://github.com/treeman/qmk_firmware/tree/master/keyboards/splitkb/kyria/keymaps/treeman) and 'numword' setup from [Jonas Hietala](https://www.jonashietala.se/blog/2021/06/03/the-t-34-keyboard-layout/#base-layer)
- 'capsword' setup from [Pascal Getreuer](https://getreuer.info/posts/keyboards/caps-word/index.html)
- 'layer lock' also from [Pascal Getreuer](https://getreuer.info/posts/keyboards/layer-lock/index.html)

...and probably many others that I've forgotten about.

The layout uses combos on the base layer for easy access to punctuation on the
base layer that I don't have space for otherwise (all the types of braces, dash,
underscore, semi-colon and colon). I have tried a couple of non-qwerty base
layouts, but I currently use [Colemak Mod-DH](https://colemakmods.github.io/mod-dh/).

You can see the most recent layout [on Keyboard Layout Editor](http://www.keyboard-layout-editor.com/#/gists/fcb843070487acedcd6a3ca1cc022482), though I haven't
found a good way to represent combos, so you will have to look at `keymap.c` for those.

## mini3x6
This keymap is for a 42 key Corne keyboard, but only maps the 34 keys shared
with the Ferris. It's a temporary measure so that I can have the same layout on
keyboards at home and work, until I've had a chance to build another Ferris.
Likely to be temporary and not updated.
