# notebook

## Depedências

SO Ubuntu.

Instale o Latex (o pacote full é pesado, cerca de 5G - é possível instalar apenas os necessários mas ai teria que ir vendo qual é necessário)

```
sudo apt install texlive-full 
```

## Build

Coloque no arquivo contents.txt os dados referentes as seções, nome código fonte e nome do algoritmo.
Separe o nome do código fonte e do algoritmo por um TAB.


Para gerar o PDF basta rodar no terminal o comando.

```
make
```

ou 

```
python generate_pdf.py
```

## Em caso de falha no build

Uma coisa que costuma causar problemas no build é a formatação do arquivo contents.txt (usar espaço ao invés de tabs) ou o uso de caracteres especiais nos códigos fontes (principalmente nos comentários).