# Formatter

## Install Vs Code extension (maybe this is not necessary)
https://marketplace.visualstudio.com/items?itemName=xaver.clang-format

change formatter to use this one

## Install Clang-format on linux

```bash
sudo apt install clang-format
```

## generate clang style based on LLVM style for example and place the file at root of the project

```
clang-format -style=LLVM -dump-config > .clang-format
```

## on each .cpp file, run this command to format it (if vscode is configured)

```bash
Ctrl + Shift + I
```

## Format all files with clang. In the root, run this command.

```bash
find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;
```