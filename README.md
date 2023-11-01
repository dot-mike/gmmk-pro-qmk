# My custom GMMK Pro keyboard layout

Make sure have cloned [QMK Firmware](https://github.com/qmk/qmk_firmware).
Setup this repo by cloning it and symlink it to the QMK Firwmare folder then compile.
```bash
git clone <gitrepo> ~/
ln -s ~/gmmk-pro-qmk ~/qmk_firmware/keyboards/gmmk/pro/iso/keymaps/dot-mike
cd ~/qmk_firmware/keyboards/gmmk/pro/iso/keymaps/dot-mike
qmk clean --all
qmk compile -kb gmmk/pro/iso -km dot-mike
ls ./build
```
