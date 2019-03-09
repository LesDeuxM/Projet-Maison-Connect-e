# Séance du 14 Décembre 2018 (Séance #1)

Lors de cette séance, j'ai tout d'abord établi la connexion Bluetooth entre mon téléphone et l'Arduino. Pour ce faire, j'ai installé l'IDE Android Studio permettant d'écrire des applications pour Android en langage Java. Pour le code, je me suis basé sur le travail de @OmarAflak qui partage sur son GithuB le code de [son application](https://play.google.com/store/apps/details?id=me.aflak.bluetoothterminal). De base, cette application fait le lien avec un appareil Bluetooth, permet d'envoyer des chaines de caractères et d'en recevoir à l'aide d'un champ de texte (cf. les captures d'écran montrées sur le Play Store). J'ai commencé à modifier le code et ajouter des boutons afin pour obtenir ceci :
<br>
<img src="./Annexe/Screenshot_20181214-190624_Smart'%20House.jpg" width="200"/>


Du côté Arduino, un delay manquant nous a fait perdre un peu de temps car les informations envoyées par le téléphone n'arrivaient pas bien à l'Arduino :<br> 
![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/probl%C3%A8me_delay_14-12.PNG?raw=true "Problème de delay")


Avec le code executé par l'Arduino, on peut à ce stade : allumer et eteindre le chauffage (caractérisé par une LED).
De plus, j'ai connecté la sonette à l'Arduino et lorsque l'on appuie dessus et que l'application est ouverte, un bruit de sonette est joué sur le téléphone.


# Séance du 18 Décembre 2018 (Séance #2)
Lors de cette séance, j'ai ajouté le code à l'Arduino ainsi qu'à l'application Android permettant la détection de mouvement dans la maison. Le capteur utilisé est le HC-SR501. Avant d'arriver, j'avais pris soin de faire les réglages de sensibilité su capteur (plus facile chez soi car en classe, il y a toujours du mouvement dans la salle, ce qui rend difficile les réglages). En effet, sans réglage, il renvoyait toujours 1 (= il détectait toujours du mouvement), même lorsqu'il n'y en avait pas. A ce jour, la détection d'un mouvement met sur le téléphone un son d'alarme. Il a fallu rajouter des delay() au code côté Arduino pour que le son ne soit joué qu'une fois à chaque détection (sans delay, il etait joué au moins 20 fois). 

J'ai essayé de faire un popup (dialogAlert sur Android) qui s'ouvrirai lorsque quelqu'un sonne à la porte, permettant de lui ouvrir le vérou (caractérisé par le Servo Moteur), mais à chaque fois que l'on sonnait, l'application se fermait (problème de code sûrement) Je prévois pour la prochaine séance de faire fonctionner cette fonction.
Finnalement, j'ai réorganisé le code Arduino et préparé les emplacements de chaque pin pour les nouveaux capteurs, les prochains buzzer ainsi que les nouvelles LED.

Ci joint l'avancé de l'application (Dans la démo, on teste la sonette et l'alarme) : 
https://drive.google.com/file/d/13t0iF7GPJzR1jNBM_e7JL7vdc0fB-TrO/view?usp=sharing

# Séance du 11 Janvier 2019 (Séance #3)
Lors de cette séance, j'ai avancé l'application Android permettant de commander la maison. Voici la liste des fonctions ajoutées :
Info : Toutes les fonctions  expliquées ci-desssous sont montrées dans la vidéo ci-joint :
https://drive.google.com/open?id=1RcVH9dT-0l4eX9bJahoKkkDsa0AhNvdw
- J'ai remplacé les boutons "Allumer lumière, chauffage, ouvrir porte" etc... par des interrupteurs (switchs). Lors du lancement de l'application, le programme demande à l'Arduino l'état de chaque élément (exemple : lumièreSalon = 1 => lumière salon allumée, porte = 0 => porte fermée...). Les switchs sont alors mis au bon état dès le lancement. On peut ensuite changer leur état simplement en cliquant dessus. L'ergonomie en est bien meilleure. 
- Lorsque quelqu'un sonne, en plus de jouer un bruit de sonette sur le téléphone, un popup ("DialogAlert" sur Android) demande si l'on ouvre la porte. Si l'on ouvre la porte, l'état sur Switch "Porte" est changé.
- J'ai effectué la migration de l'Arduino Uno vers l'Arduino Mega car l'Arduino Uno ne nous permettait pas continuer le projet, avec les futurs composants qui vont arriver prochainement (led RGB, capteur Température, Buzzer ...) Tout fonctionne comme avant.
- Enfin, dans le peu de temps qu'il me restait, j'ai ajouté une SeekBar dans l'application qui permettra, quand on aura la led RGB de chosir la couleur de cette dernière. Cette barre va donner un chiffre de 0 à 16 777 216, ce qui donnera une couleur en decimal, convertie en hexadécimal (type #ffee12) puis enfin, l'arduino convertira ce code en RGB pour par la suite mettre la LED à la couleur souhaitée.

# Séance du 18 Janvier 2019 (Séance #4)
Lors de cette séance nous nous sommes tout d'abord rendu au Fablab avec les planches de bois d'épaisseur 5mm pour construire notre maquette à la découpeuse laser. Vu que les planches n'étaient pas à la bonne dimension pour la découpeuse laser, on a utilisé une scie sauteuse pour les mettre aux bonne dimensions. Une fois les plances découpées, il a fallu attendre que la découpeuse face le travail.
![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/decoupeuse%20laser.jpg?raw=true)
![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/Scie%20sauteuse.jpg?raw=true)
J'ai pendant ce temps modifié le code permettant l'affichage au choix d'un ou 3 curseurs pour la couleur de la LED RGB du salon. La partie XML du code est faite (partie XML : ensembles des déclarations des boutons, switch etc dans l'appli Android), il ne manque plus qu'à faire que le switch affiche en fonction du choix 1 ou 3 curseurs, dans la partie code Java de l'appli. Je finaliserai ceci dans les prochains jours.

Une fois la maison assemblée, nous nous sommes rendu compte qu'une pièce était trop petite. Nous avons donc utilisé les bords laissés par la découpeuse, et collé avec de la colle et du scotch pour allonger la pièce, sauf que ça la rendait maintenant un peu trop grande. Nous avons donc raccourci les bords avec une lime.

# Séance du 06 Février 2019 (Séance #5)
Lors de cette séance, j'ai commencé par faire des recherches sur la manière qui serait la plus simple pour contrôler/recevoir les informations de tous les capteurs de la maison. La solution qui semble être la plus simple à mettre en oeuvre est une "Realtime Database". C'est une base de donnée stockée sur un compte FireBase (outil développé par Google) et qui permet de stocker dans notre cas les variables d'état de led, sonette,... 

![alt text](https://github.com/LesDeuxM/Projet-Maison-Connectee/blob/master/Annexe/database.PNG?raw=true "Screenshot de la database")

J'ai donc dû recréer \* une application Android qui cette fois modifie les valeurs de la base de donnée, plutot que de communiquer les informations changées à l'Arduino. Avancement : Toutes les fonctions permettant de changer l'état des leds, du RGB du salon sont opérationnelles. Reste à faire : Réagir lorsqu'une valeur de la database change (quand on active la sonette, quand il pleut...) et surtout programmer le module Wifi à l'Arduino pour qu'il récupère les états stockés sur la database et les change quand il le faut.

\* Recréer une application : L'ancienne application avait été écrite sur Android Studio (interpreteur Java adapté au développement d'applications Android) avec pour base un code qui établissait la connexion Bluetooth entre le Smartphone et l'Arduino. La nouvelle application a elle été écrite de A à Z, reprenant les fonctions principales de l'ancienne. Cette fois, plutôt que d'envoyer les infos par Bluetooth à l'Arduino, on modifie les variables contenues dans la base de donnée FireBase. Parmis les avantages : On peut "communiquer" avec la maison de n'importe où, il suffit d'une connexion Internet. De plus, l'application se lance directement, plus besoin de passer par une page permettant de choisir avec quel module Bluetooth on souhaitait communiquer, l'appli se connecte toute seule à la base de donnée, et est donc opérationnelle dès son lancement.
Ci dessous un schéma montrant le nouveau moyen de communication mis en oeuvre :

<img src="./Annexe/Schema%20changement%20application.jpg" alt = "Schema changement d'appli" width="300"/>


# Séance du 13 Février 2019 (Séance #6)
Durant cette séance, j'ai travaillé principalement sur le module Wifi ESP32. Le but était que l'ESP puisse récupérer les valeurs stockées dans la base de donnée FireBase. Après un certain temps de recherche, j'ai trouvé une librairie qui permet de faire communiquer l'ESP et la base de donnée. (https://github.com/ioxhop/IOXhop_FirebaseESP32).

Je peux donc à ce stade récupérer et modifier les valeurs contenues dans la base de donnée FireBase, à partir de l'ESP.

Il va par la suite falloir que l'ESP communique toutes ces données à l'Arduino pour qu'il réagisse en conséquence. L'Arduino devra aussi communiquer les évènements de la maison à l'ESP (types sonette, detecteru mouvement, pluie, effraction). 

On ne connecte pas tous les capteurs & composants directement à l'ESP car ils fonctionnent pour la plupart en 5V alors que l'ESP ne donne que du 3V3. De plus, nous avons besoin de beaucoup de ports (pour le clavier par ex.) donc nous gardons l'Arduino Mega.

J'ai aussi continué la nouvelle version de l'Application Android pour que cette dernière mette à jour à l'ouverture l'état des switchs et des barres RGB en fonction des valeurs récupérées dans la base de donnée. 
J'ai aussi rajouté une fonction qui grise les barres de choix de couleur de lumière du salon lorsque cette dernière est etteinte (Voir vidéo ouverture application ci dessous)

https://drive.google.com/open?id=19PgDLSF_0CexZjGUuD3kIShT8tevaGxK

En fin de séance, j'ai réalisé les soudures des contacts se trouvant à la fenêtre, à la porte ainsi que la sonette (1 fil vers 2 fils "->=").

# Séance du 27 Février 2019 (Séance #7)
Durant cette séance, j'ai travaillé sur la communication entre l'ESP 32 et l'Arduino. Cette liaison s'est avérée.. compliquée. Dans le sens ESP -> Arduino : pas de soucis. Mais impossible de recevoir des données de l'Arduino sur l'ESP, malgré le pont diviseur de tension mis en place pour abaisser la tensions du Tx de l'Arduino (5V) en 3.3V . Après de nombreuses tentatives infructueuses, je n'ai pas trouvé de solution à ce problème (deux autres groupes de la classe ont le même soucis). Je pense que le problème vient du pont de resistance, les tutoriels sur Internet utilisaient tous un convertisseur de niveau logique 5V->3.3V bidirectionnel. J'en ai donc commandé un mais pas sûr qu'il arrive à temps. Heureusement, le projet n'est pas bloqué pour autant et on peut contourner ce problème en exécutant des fonctions sur l'ESP directement. 

J'ai consacré l'autre partie de la séance à faire que l'on reçoive une notification (même lorsque l'application est fermée) sur notre téléphone lorsqu'un un des évènements suivant est detecté : Appuie sur la sonette, detection ouverture de porte/fenetre, detection de pluie, de mouvement. Pour se faire, j'utilise encore Firebase qui propose un outil de "Cloud messaging" et qui permet, avec une simple requete HTTP (envoyée par l'ESP), d'envoyer une notification avec le contenu que l'on souhaite sur notre Smartphone.

J'ai aussi ajouté dans l'application android un carré de prévisualisation de la couleur que l'on choisit avec les barres RGB (pour controlet la LED RGB du salon).

# Dernière Séance (6 Mars 2019)
Durant cette séance, j'ai réalisé différentes taches :
- Finalisation de l'application, et de son design (voir Capture d'écran) : Mise en block des catégorie (chauffage, lumière, activation des alarmes concernant la pluie, le detecteur de mvt, d'effraction et la sonette). Chaque catégorie possède une icone et l'icone de la catégorie lumière salon change de couleur en fonction de la couleur que l'on renseigne avec les barres R, G, B.
<img src="./Annexe/Application%20Finale.jpg" width="300"/>

- Finalisation du code de l'ESP : Tous les composants fonctionnnent ensemble, toutes les receptions de notifications sur le téléphone fonctionnent.
- Concernant la porte : encore des difficultés dans l'établissement de la connexion ESP/Arduino : Faire fonctionner les librairies SoftwareSerial et Servo en même temps sur l'Arduino s'est avéré compliqué. Nous avons enfin réasolu ce soucis le lendemainn, en mettant le Servo en PWM9 et le RX en PWM3
- Concernant la maison en elle même : Nous avons collé les plaques de bois entre elles (elles tenaient jusqu'à présent grace à des bouts de scotch pas très estétique mais pratique dans le cas où nous aurions eu besoin de la redémonter pour faire un trou ou autre par exemple.

