# régénérateur de piles alcalines
Encore un schéma pour tenter de faire revivre les piles alcalines <br>


"Yacc" est un acronyme bien connu des développeurs logiciels.<br>
Yet Another Compiler Compiler (« Encore un autre compilateur de compilateur »)

<b>Ce soir je vous présente "Yarab" </b>

## Yet Another Regenerator Alkaline Batterie"
 Ce serpent de mer de l'électronique a de nombreux avatars, plus ou moins compliqués et, on l'espère, une certaine efficacité.<br>
 Voici le mien, à base de l'inévitable ATTiny85.<br>
 L'avantage d'utiliser un micro-controleur est:<br>
 ```
 -- réduire le nombre de  composants externes
 -- une grande marge de réglage de l'impulsion de charge
 -- des mesures précises de tension avec ou sans charge
 -- un affichage sur console série ou grapheur du commerce.
 -- l'arret automatique en fin de "recharge"
 -- l'évaluation de la résistance interne de la pile.
```



  J'ai fait le choix d'utiliser une référence de tension externe car les références internes <br>
  ne m'ont pas convainçue.<br>
  L'entrée PB0 ( pin 5) du circuit sert ici d'entrée de la tensionde référence.<br> 
  Cette tension, qui doit être très stable, est faite avec le circuit TL431 et une résistance.<br>
  L'avantage est que l'étalonnage se réduit à la mesure avec un multimètre de cette tension <br>
  (2.493 V dans mon montage) et au report de cette valeur dans le code. <br>
  <h4>\#define  REF_EXT      2.493 </h4><br>
  Le montage est insensible vis à vis de la tension d'alimentation, qui peut être variable selon <br>
  l'adaptateur secteur --> 5V utilisé.<br>
  La tension à mesurer est entre 1.3 et 1.75 V , une référence de 2.048 V serait plus adaptée,<br>
  mais je n'en n'avait pas sous la main.<br>
  La méthode de "régénération" est par impulsion de charge pendant 50 ms à 100 mA, <br>
  puis une décharge de 2 ms à 50 mA.<br>
 La tension de la pile en charge est moyennée sur les 32 mesures. La quantité d'énergie est calculée <br>
 en tenant compte des impulsions et   des ratios charge/décharge.<br>
 
 On fait 5*32 = 160 cycles ainsi, puis la lecture de la tension sans charge <br>
 et enfin une lecture de la tension avec un débit de 50 mA.<br>

 Un calcul permet d'évaluer la résistance interne . <br>
 Bien sûr, ce n'est pas une valeur très précise, mais plutôt une indication de la "santé" de la pile .<br>

#  Explication sur le schéma:

    PINS    ATT85
           ________-_______
           | 1:RST  8: Vcc |
    TX+Led | 2:PB3  7: PB2 |Cmd drain 50mA
    A2 Pile| 3:PB4  6: PB1 |Cmd charge 100mA
           | 4:Gnd  5: PB0 |External Ref ==> TL431
           ----------------- 
```
 PB3 est la sortie série à 9600 bd (modifiable) et active aussi la led rouge 
 PB4 est l'entrée analogique, reliée directement au pole + de la pile
 PB0 est l'entrée de la référence de tension du TL431
 PB1 commande la charge à travers une résistance de 33 ohm et un PNP 2N2907
 PB2 active la décharge de la pile à travers une résistance de 24 ohm et un 2N7000.
 ```
 Un condensateur de 2200µF est placé entre le + et - fournit par la prise mini USB <br>

 Il me manque une IO pour implémenter un afficheur I2C , mais je voulais réserver PB0 à la référence de tension.<br>
 


