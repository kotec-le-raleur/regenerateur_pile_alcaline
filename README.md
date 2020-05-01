# regenerateur_pile_alcaline
Encore un schéma pour tenter de faire revivre les piles alcalines


"Yacc" est un acronyme bien connu des développeurs logiciels.
Yet Another Compiler Compiler (« Encore un autre compilateur de compilateur »)

Ce soir je vous présente "Yarab" 

# Yet Another Regenerator Alkaline Batterie"

 Ce serpent de mer de l'électronique a de nombreux avatars, plus ou moins compliqués et, on l'espère, une certaine efficacité.

 Voici le mien, à base de l'inévitable ATTiny85.
 L'avantage d'utiliser un micro-controleur est:
 -- réduire le nombre de  composants externes
 -- une grande marge de réglage de l'impulsion de charge
 -- des mesures précises de tension avec ou sans charge
 -- un affichage sur console série ou grapheur du commerce.
 -- l'arret automatique en fin de "recharge"
 -- l'évaluation de la résistance interne de la pile.




 J'ai fait le choix d'utiliser une référence de tension externe car les références internes
 ne m'ont pas convainçue.
 L'entrée PB0 ( pin 5) du circuit sert ici d'entrée de la tensionde référence. 
 Cette tension, qui doit être très stable, est faite avec le circuit TL431 et une résistance.
 L'avantage est que l'étalonnage se réduit à la mesure avec un multimètre de cette tension (2.493 V dans mon montage) et au report de     cette valeur dans le code. 
 \#define  REF_EXT      2.493
 Le montage est insensible vis à vis de la tension d'alimentation, qui peut être variable selon 
 l'adaptateur secteur --> 5V utilisé.
 La tension à mesurer est entre 1.3 et 1.75 V , une référence de 2.048 V serait plus adaptée, mais je n'en n'avait pas sous la main.
 
 la méthode de "régénération" est par impulsion de charge pendant 50 ms à 100 mA, puis une décharge de 2 ms à 50 mA.
 La tension de la pile en charge est moyennée sur les 32 mesures. La quantité d'énergie est calculée en tenant compte des impulsions et   des ratios charge/décharge.
 On fait 5*32 = 160 cycles ainsi, puis la lecture de la tension sans charge et enfin une lecture de la tension avec un débit de 50 mA.

 Un calcul permet d'évaluer la résistance interne . Bien sûr, ce n'est pas une valeur très précise, mais plutôt une indication de la     "santé" de la pile .

#  Explication sur le schéma:

    PINS    ATT85
           ________-_______
           | 1:RST  8: Vcc |
    TX+Led | 2:PB3  7: PB2 |Cmd drain 50mA
    A2 Pile| 3:PB4  6: PB1 |Cmd charge 100mA
           | 4:Gnd  5: PB0 |External Ref ==> TL431
           ----------------- 

 PB3 est la sortie série à 9600 bd (modifiable) et active aussi la led rouge 
 PB4 est l'entrée analogique, reliée directement au pole + de la pile
 PB0 est l'entrée de la référence de tension du TL431
 PB1 commande la charge à travers une résistance de 33 ohm et un PNP 2N2907
 PB2 active la décharge de la pile à travers une résistance de 24 ohm et un 2N7000.
 Un condensateur de 2200µF est placé entre le + et - fournit par la prise mini USB 

 Il me manque une IO pour implémenter un afficheur I2C , mais je voulais réserver PB0 à la référence de tension.
 


