# Séance du 14 Décembre 2018 (Séance #1)

Pour la première séance nous avons défini les tâches que chacun réalisera durant les prochaines séances, ainsi que le planning de notre projet.
On a donc réflechi aux composants dont on aurait besoin afin de les commander en avance. J'ai réalisé le design de notre maquette afin de placer les composants aux emplacements qui corresponderaient le plus à notre idée du projet :

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/design.jpg?raw=true "Design")

Ce design nous à aussi permis de nous mettre d'accord sur la structure et la taille de la maquette. Visualiser la maison et la dessiner nous a aussi donné de nouvelles idées comme : un thermostat, un capteur de pluie ou un capteur de mouvement exterieur pour allumer la lumière à l'arrivé de quelqu'un. Ces modifications ne sont pas encore sur le design car ce seront des ajouts supplémentaires si le reste fonctionne.


J'ai par la suite réalisé une maquette en carton (voir ci dessous) afin de dimensionner la structure totale et la taille adéquate pour les différents composants.

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/maquette1.jpg?raw=true "Maquette")


On voulait d'abord partir sur un interrupteur pour détecter l'ouverture de la porte (et des fenêtres), mais on s'est rendu compte qu'avec l'interrupteur il fallait exercer une force pour la fermer la porte, elle s'ouvrait donc toute seule si on la lachait.
On a donc pensé à un interrupteur "artisanal", c'est à dire une tige métalique placée sur la porte qui vient taper une plaque reliée à la masse quand la porte est fermée.
Le code correspondant se trouve [ici](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Projet/ouverturePorte/ouverturePorte.ino).
      
      
# Séance du 18 Décembre 2018 (Séance #2)

Au début de cette séance, j'ai réalisé des mesures sur la maquette pour placer tous les composants. J'ai placé le capteur de mouvement à différents endroits et fait des tests pour trouver là où il marche le mieux. 

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/MiseEnPlace_Capteur.jpg?raw=true "Capteur")
      


J'ai ensuite essayé de placer le moteur (modèle : SG90) qui servira de verrou à différents endroits pour fermer convenablement la porte.
En placant la LED qui devait servire d'ampoule pour éclairer la pièce, je me suis rendu compte que les petites LED n'étaient pas assez puissantes pour qu'on les voit, il faut donc des LED plus grosses.

En placant les composants que l'on avait déjà, jai remarqué qu''il manquait de place dans la maquette que j'ai ralisé, j'ai donc décidé d'agrandir la pièce et donc de supprimer la seconde pièce de l'étage pour ne faire qu'une pièce par étage.

Par la suite j'ai programmé le servomoteur en liaison avec l'application pour pouvoir controler la fermeture et l'ouverture du verrou. J'ai rencontré un problème pour trouver le bon angle de fermeture car le moteur n'est pas assez précis si on lui donne un angle en degré. 
Il y a aussi fallu changer l'application et créer une nouvelle case dans l'application dédiée au verrou.


# Séance du 11 Janvier 2019 (Séance #3)

Pendant cette séance je me suis occupé de la maquette finale de notre maison. 

Dans un premier temps j'ai fini de placer les différents capteurs, bouton et autre périphériques sur la maquette en carton pour dimensionner correctement la maquette finale. 

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/EmplacementDuMoteur.jpg?raw=true "Moteur")

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/EmplacementSonette.jpg?raw=true "Sonette")

On a donc décidé de réaliser la maquette finale en bois en la faisant au FabLab de Sophia.  Il a donc fallu chercher et télécharger le logiciel nécessaire à la réalisation du "plan" de la maison, j'ai pris Inkscape complété par BoxGenerator. Ne trouvant pas de doc claire pour ce que je voulais faire, je suis donc allé au FabLab, où d'autres groupes m'ont expliqué le fonctionnement du logiciel. J'ai fini par réaliser le "plan" que voici :

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/PlanMaisonEnBois.jpg?raw=true "Plan")
      

# Séance du 18 Janvier 2019 (Séance #4)

Je suis allé au FabLab pour faire la découpe de la maison, mais il y a eu un problème au niveau des dimensions. La découpeuse laser ne supporte qu'un certain format de planches. C'est donc pour cela que nous avons tout revu sur la maquette, la maison n'a maintenant plus qu'un étage ce qui a permis d'imprimer au format souhaité. J'ai donc refait le plan et je suis retourné au FabLab découper la maison :


![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/DecoupeLaser.jpg?raw=true "Découpe")

Après avoir assemblé les pièces, j'ai vérifier que les dimensions concordaient avec tous les composants. Une des pièces avait due être séparée en deux pour des raison de dimension de découpe, on a eu du mal à la recoller donc on à utiliser du scotch peu estétique.

A la fin de la séance j'ai paramétré et codé le programme pour le digicode que nous placerons à l'entrée pour pouvoir ouvrir la porte sans l'application ni téléphone.

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/Digicode.jpg?raw=true "Digicode")


# Séance du 06 Fevrier 2019 (Séance #5)

Maintenant que la majorité des modules fonctionnent et que la maquette est finie, on a décidé de tout installer sur la maquette. 

Dans un premier temps, il à donc fallu fixer la porte et la fenetre. Les charnières ayant trop de jeu pour la porte on a décidé de mettre du gros scotch qui permet de la maintenir bien en place.

Ensuite j'ai fabriqué le système de detection d'ouverture de la porte et de la fenêtre. Pour se faire j'ai découpé dans une plaque métailque deux bouts que l'on colle sur le montant et sur la partie mobile, qui viennent se toucher à la manière d'un interupteur quand la porte et/ou fenêtre est fermée.

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/Fermeture.jpg?raw=true "Fermeture")

S'en suit l'instalation du digicode ainsi que la réalisation de tous les trous qui vont avec pour faire passer les fils jusque dans le toit où se trouve la carte Arduino.


# Séance du 13 Fevrier 2019 (Séance #6)

Dans la continuité de la dernière séance, j'ai durant celle ci fini de percer les trous pour faire passer les cables mais j'ai aussi réalisé des soudures et l'agencement des cables pour les relier à la carte Arduino. Il à donc fallu ralonger des cables dans le cas où ils étaient trop courts.

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/CarteArduino.jpg?raw=true "Arduino")

Une fois les soudures faites, il a fallu les placer et les couvrir de scotch pour éviter les faux contacts. 

![Alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/Soudure.jpg?raw=true "Soudure")

Les modules sont donc tous branchés, et il va falloir tester si tout fonctionne ensemble avec les nouveaux branchements.


# Séance du 27 Fevrier 2019 (Séance #7)

Maintenant que les modules sont branchés, je les ai éssayé un par un séparement pour verifier que les branchements étaient bons. J'ai rencontré un problème avec le digicode dont la matrice dépend des branchements, elle était donc inversée. C'est à dire que les touches ne renvoyaient pas le bon chiffre. J'ai dû modifier le code pour trouver le bon ordre des pins. 
Le deuxième soucis que j'ai rencontré est avec la détéction d'ouverture de la porte. En effet, deux plaques métaliques sont sensées rentrer en contact lorsque la porte est fermée, or la porte ferme mal et s'ouvre légérement dès qu'on la lache. IL a donc fallu trouver un moyen de la bloquer légérement lorsque qu'elle est totalement fermée.

Ensuite j'ai essayé de faire fonctionner le capteur de température que servira à faire un "thermostat" pour la maison, et ainsi modifier le chauffage caractérisé par une LED rouge. J'ai d'ailleurs découpé dans du PVC semi transparent ce qui représentera le radiateur. Malheureusement la plaque de PVC semble trop épaisse et les variations d'intensité de la LED ne se voient que très légérement, il va donc falloir que j'essaie une autre méthode.


# Séance du 6 Mars 2019 (Séance #8)

Pour la dernière séance il a fallu finir tout ce qu'on avait laisé en état de test. C'est à dire qu'il a fallu coller les murs de la maison entre eux, définir les bon pins et brancher tous les composants ensemble. 

Une fois cela fait j'ai codé le programme qui permet de décoder le message envoyé depuis l'ESP à l'Arduino. Malheureusement sur la carte que nous utilisions, une MEGA, nous n'avons pas réussi à faire fonctionner la transmission de données. Nous avons donc essayé avec une UNO, mais là aussi il y a eu un gros problème de transmission que nous avons enfin réussi à résoudre en changeant le servo de Pin car il intérférait avec la liaison RX-TX de l'ESP. 

Maintenant que la liaison marche, nous avons fini de faire correspondre le code de l'Arduino avec les messages envoyés par l'application via l'ESP.
