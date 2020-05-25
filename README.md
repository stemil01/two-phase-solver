# Algoritam za slaganje Rubikove kocke
Implementacija two phase algoritma Herberta Kosiembe za resavanje Rubikove kocke.
Algoritam je kombinacija vise njih, a cela ideja moze se naci na Kosiembinoj [zvanicnoj stranici].
Resenja nisu optimalna po broju poteza, ali program za nekoliko sekundi daje resenja jako bliska optimalnom.

## Pokretanje
Program je pisan u C++ i za kompajlovanje je koriscen GCC. Komanda za kompajlovanje se nalazi u fajlu *Makefile* i moze se pozvati komandom
```shell
$ make
```
Za funkcionisanje je potrebno nekoliko fajlova koji se nalaze u folderu *resources*.
Ukoliko vec ne postoje, pri prvom koriscenu je potrebno da se generisu i ceo postupak moze da potraje oko 1 sat i zahteva otprilike 7GB RAM-a, a na disku oko 6GB.
Kada vec postoje ti fajlovi za njihovo ucitavanje je potrebno oko 2 minuta i program zahteva oko 2GB memorije.

## Rezultati
Jos uvek nisam testirao program kako dolikuje ali za sada deluje da gotovo odmah daje resenja duzine do 26 poteza, prosek mi deluje da je oko 22-23 poteza.
Resenja prve faze su ocekivano brza jer nema gotovo nikakvog dodatnog racuna, dok se resenja druge faze takodje dosta brzo dobijaju, na moje iznenadjenje.

[zvanicnoj stranici]: http://kociemba.org/cube.htm
