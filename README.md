# Wordle

📘 Wordle game in the terminal using C++ & FTXUI

<div align="center">

![](test/__snapshot__/e2e.gif)

<!--prettier-ignore-->
**[Overview](https://github.com/jcbhmr/wordle#readme)**
| [Dev wiki](https://github.com/jcbhmr/wordle/tree/main/wiki#readme)
| [packages/fetch](https://github.com/jcbhmr/wordle/tree/main/packages/fetch#readme)
| [packages/html-location](https://github.com/jcbhmr/wordle/tree/main/packages/html-location#readme)

</div>

## Installation

[![GCC](https://img.shields.io/static/v1?style=for-the-badge&message=GCC&color=A42E2B&logo=GNU&logoColor=FFFFFF&label=)](https://gcc.gnu.org/)
[![Clang](https://img.shields.io/static/v1?style=for-the-badge&message=Clang&color=000000&logo=Apple&logoColor=FFFFFF&label=)](https://clang.llvm.org/)
[![C++](https://img.shields.io/static/v1?style=for-the-badge&message=C%2B%2B&color=00599C&logo=C%2B%2B&logoColor=FFFFFF&label=)](http://www.cplusplus.org/)
[![Conan](https://img.shields.io/static/v1?style=for-the-badge&message=Conan&color=6699CB&logo=Conan&logoColor=FFFFFF&label=)](https://conan.io/)

⚠️ This app requires you to compile it yourself [🍰](https://twitter.com/bbotezatu/status/768756952528723969) \
✅ This app successfully compiles using xmake on [the devcontainer](https://github.com/jcbhmr/wordle/blob/main/.devcontainer/devcontainer.json)

1. Clone this repository
   ```sh
   git clone https://github.com/jcbhmr/wordle.git
   ```
2. Ensure you have [`xmake`](https://xmake.io/#/) and [`conan`](https://docs.conan.io/en/latest/installation.html) installed on your system
3. Run the following commands:
   ```sh
   tools/gen-repo-index.sh
   xmake
   ```
5. 🎉 You can now run `xmake r` in your shell and play Wordle!

## Usage

![Terminal](https://img.shields.io/static/v1?style=for-the-badge&message=Terminal&color=4D4D4D&logo=Windows+Terminal&logoColor=FFFFFF&label=)

```
Usage: /workspaces/wordle/build/linux/x86_64/release/wordle [-h] [--dict VAR] [--answer] date

Positional arguments:
  date          Which date to use as the answer word [default: "2022-12-11T22:49:21+0000"]

Optional arguments:
  -h, --help    shows help message and exits
  -v, --version prints version information and exits
  -d, --dict    A JSON dictionary file to use (https://github.com/jcbhmr/wordle/blob/main/assets/dict/official.json) [default: "/home/codespace/.config/wordle/dict.json"]
  -a, --answer  Show the answer word
```
