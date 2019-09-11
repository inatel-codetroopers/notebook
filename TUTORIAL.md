# Formatação do código

Usaremos clang-format.

## Instalação no linux

```bash
sudo apt install clang-format
```

## Gerando um estilo

Na raiz do projeto, rode o comando abaixo para gerar um estilo basedo no LLVM.
Altere depois o tamanho da coluna para 71, para caber o código em duas páginas
no notebook.

```bash
clang-format -style=LLVM -dump-config > .clang-format
```

## Para formatar todos os códigos do projeto

Rode o seguinte comando na raiz do projeto.

```bash
find . -regex '.*\.\(cpp\|hpp\|cc\|cxx\)' -exec clang-format -style=file -i {} \;
```

## Instalar extensão para seu uso no vscode (caso use vscode)

https://marketplace.visualstudio.com/items?itemName=xaver.clang-format

Configure a extensão no VsCode.

Para formater um arquivo, com ele aberto, use a seguinte combinação de
teclas.

```bash
Ctrl + Shift + I
```

