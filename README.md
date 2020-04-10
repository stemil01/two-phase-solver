# Algoritam za resavanje Rubikove kocke
Implementacija two phase algoritma Herberta Kociembe za resavanje Rubikove kocke.
Algoritam nije optimalan po broju poteza, ali zato daje resenja duzine priblizno optimalnom. 

## Rezultati
Jos uvek nisam testirao program kako dolikuje ali za sada deluje da gotovo odmah daje resenja duzine do 26 poteza, prosek mi deluje da je oko 22-23 poteza.
Resenja prve faze su ocekivano brza jer nema gotovo nikakvog dodatnog racuna, dok se resenja druge faze takodje dosta brzo dobijaju, na moje iznenadjenje.

## Pokretanje
Program je kompletno pisan u C++ i za kompajlovanje je koriscen GCC i testiran je na GNU/Linux sistemu, na kome se ocekuje da radi. Nije testirano ali bi verovatno isto radilo na bilo kom Unix sistemu. Da bi se pokrenuo moze se pozvati komandom 
```shell
$ make
```
Treba napomeniti da sam program zahteva oko **2GB** memorije kada se ucitaju svi podaci i za samo ucitavanje je potrebno oko 1-2 minuta. Ukoliko nema vec generisanih tabela, onda je neophodno generisati ih da bi program radio. Tabele *phase1_pruning* i *phase2_corner_UD_edge* su najzahtevnije. Za prvu je potrebno oko 20 minuta za pravljenje i program uzima oko **7GB** memorije u toku rada, za drugu je potrebno oko 10 minuta i potrebno je oko **6GB** memorije.
Kada su tabele kreirane opet znacajniju kolicinu memorije uzimaju vec pomenute dve, redom **1.5GB** i **4.6GB**. 
Ovo naravno zvuci preterano i cudno, ali imajte u ozbiru da sam ustedeo gde kod sam mogao da algoritam postane sto jednostavniji. Originalna verzija koristi simetrije kocke koje znacajno smanjuju kolicinu podataka potrebnih za cuvanje.

Celokupna ideja je preuzeta, kao sto je receno, od Herberta Kociembe koji je na svom zvanicnom sajtu detaljno objasnio detanje ovog algoritma ([zvanicna stranica] (http://kociemba.org/cube.htm))