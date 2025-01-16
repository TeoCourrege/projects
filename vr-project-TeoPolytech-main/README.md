# Projet de Réalité Virtuelle

- Vous allez utiliser ce repository tout au long du cours pour faire évoluer votre projet, au gré des TP.
- Vous allez mettre à jour régulièrement le ReadMe en mettant votre nom et en expliquant ce que vous avez fait (ou pas) dans chaque TD. En particulier les bonus ou les commandes clavier à utiliser.
- Vous aller créer chaque semaine un `tag` TP1, TP2, ..., TP7, TP8 pour marquer l'évolution de l'état de votre projet.


# Courrege Téo

## TP1 : premier cube 

- 14/12/2023: étapes du TP complétées.
- Bonus: Rajout de commandes clavier et souris pour gérer la translation du cube avec les touches ZQSD ainsi
  que la vitesse de rotation avec la molette souris.

## TP2 : conception objet

- 21/12/2023: étapes du TP complétées.
- Bonus: Rajout des différents points de vues

## TP3 : textures

- 11/01/2024: étapes du TP complétées.
- Bonus: Rajout du zoom avec la molette souris et d'un slider pour changer la taille du tore

## TP4 : lumières

- 18/01/2024: étapes du TP complétées.
- Bonus: Rajout du zoom avec la molette souris et d'un slider pour changer la taille du tore

## TP5 : animation et vision 3D
- 25/01/2024: étapes du TP complétées.
- Bonus: Rajout d'un slider pour selectionner la cible de la camera et d'une check box pour suivre les objets en mouvement

## TP6 : intégration modèle 3D
- 01/02/2024: étapes du TP complétées.
- Bonus: Ajout de labels pour connaitre l'altitude et la vitesse de l'avion

## TP7 : caméra subjective
- 08/02/2024: étapes du TP complétées.  
- Bonus: ajout d'un viseur pour la camera subjective, possibilité de change de caméra pour l'avion
- Controles : - Caméra subjective : flèches clavier haut bas gauche droite pour bouger
              - Caméra BB8 : ZQSD pour bouger, molette pour zoomer/dézoomer
              - Caméra avion (activer l'animation pour faire bouger l'avion) : ZQSD pour bouger, W accélération, X décéleration



## TP8 : version mobile

## Commandes Git

### Pour cloner ce *repository* dans votre machine locale 

```
cd RepertoireDeTravail
git clone  https://github.com/UCA-PNS-MAM5-VR/vr-project-IdGithub.git
```
où `IdGithub` est votre identifiant dans github.

Ce sera dans `RepertoireDeTravail` que vous allez construire votre projet Qt.

### Pour faire des commit dans votre *repository* local

```
git add -A
git commit -m "message"
```

### Pour pousser sur le repository distant de github

```
git push
```

### Pour ajouter un tag 

C'est à dire [étiqueter](https://git-scm.com/book/fr/v2/Les-bases-de-Git-%C3%89tiquetage) l'état de votre projet à un certain instant, il faut faire 

```
git tag -a NomDuTag -m "message"
git push
```

ainsi la date du tag est enregistrée. Je vais pouvoir vérifier qu'il respecte les délais du rendu.

Pour revenir à l'état du projet correpondant à un certain tag, la commande est :

```
git checkout NomDuTag
```

puis 

```
git checkout main
```

pour revenir à l'état final.

### Branches

Vous avez le droit de créer des *branches* pour tester des fonctionnalités mais ce sera la branche *main* qui sera évaluée par moi, les autres étant ignorées.


