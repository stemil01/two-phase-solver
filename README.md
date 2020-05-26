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
Na 100 slucajno generisanih pozicija kocke od 100 poteza prosecna duzina resenja bez ikakvih dodataka je 22.9 poteza, dok se dodavanjem vremena ona poboljsava tako sto se vec za 2 sekunde prosek smanjuje ispod 20 poteza (tacnije 19.96 na ovom testu).

[zvanicnoj stranici]: http://kociemba.org/cube.htm
