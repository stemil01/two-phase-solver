# two-phase-solver
Implementacija two phase algoritma Herberta Kociembe za resavanje Rubikove kocke.
Algoritam nije optimalan po broju poteza, ali zato daje resenja duzeine priblizno optimalnom. 

## rezultati
Jos uvek nisam testirao program kako dolikuje ali za sada deluje da gotovo odmah daje resenja duzine do 26 poteza, prosek mi deluje da je oko 22-23 poteza.
Resenja prve faze su ocekivano brza jer nema gotovo nikakvog dodatnog racuna, dok se resenja druge faze takodje dosta brzo dobijaju, na moje iznenadjenje.

## pokretanje
Program je kompletno pisan u C++ i za kompajlovanje je koriscen GCC i testiran je na GNU/Linux sistemu, na kome se ocekuje da radi. Nije testirano ali bi verovatno isto radilo na bilo kom Unix sistemu. Da bi se pokrenuo moze se pozvati komandom 
```shell
$ make
```
