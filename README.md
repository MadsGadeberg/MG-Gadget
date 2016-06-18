# MG-Gadget


Danish README
Funktioner som controlleren har.
Lock/unlock
Motorcyklen kan låses og låses op ved hjælp af tastekombinationer med højre og venstre trykknap.
For at låse motorcyklen op/ tænde motorcyklen trykkes begge knapperne ned hvorefter den højre slippes efterfulgt af begge knapper igen trykkes ned.
For at låse motorcyklen bruges overnævnte kombination bare spejlvendt. Det vil sige den venstre slippes og trykkes. Disse kombinationer ændres selvfølgelig før den endelige version.

Ved tænd/sluk blinker blinklysene med forskelligt antal så man får en bekræftelse på om motorcyklen er slukket eller tændt.


Både højre og venstre knap har 2 forskellige funktioner alt efter om man trykker på den eller holder den nede. Disse funktioner kan inverteres ved brug af "config0" porten. Dette er nyttigt hvis man for eksempel har en motorcykel uden blinklys. Så vil man gerne have nogle andre funktioner ved almindeligt tryk i stedet for blinklys.

Venstre trykknap
Ved tryk slukker/tænder man kørelyset.
Ved at holde knappen nede blinkes der.
Disse funktioner kan inverteres ved at Sætte "config0" porten til plus.
Hvis motorcyklen er slukket kan positionslyset tændes ved at holde venstre trykknap inde.

Højre trykknap
Ved tryk skiftes imellem kort/langt lys.
Ved at holde knappen nede blinkes der.
Disse funktioner kan ligeledes inverteres ved at Sætte "config0" porten til plus

Højre og Venstre
Ved tryk på begge knapper slukkes spændingen til tændspolerne i 5 sekunder. "Engine Kill"