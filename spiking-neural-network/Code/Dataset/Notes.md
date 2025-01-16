On a un dataset de labels conséquent de ouf

On a donc: 
- Choisis 3 thèmes généraux: Animaux, Music et Son de choses (sound of things)
    - Ces thèmes se déclinent en sous-thèmes (animaux domestiques, sauvages, ...) qui se déclinent eux-même en sous-sous-thèmes (chien, chat, ...).
- Nous allons répertorier les labels et adresses de sous-sous thèmes des 3 grand thèmes dans un fichier .csv de manière à avoir suffisament de labels ayant un thème général unique, cela nous permet également de mieux maitriser le nombre de téléchargement à effectuer (500 animaux, 500 musiques, 500 sons de "choses") 

```python
categorie_name = "data\\Categories\\Animals\\Animals.csv"
list_name = ["Cat", "Dog"]

os.makedirs("data", exist_ok=True)
os.makedirs("data\\Categories\\Animals", exist_ok=True)
```

```python
# We browse a class_labels_indices.csv file and retrieve the label associated with name, forming a list of names.
categorie_name = "data\\Categories\\Music\\Instruments.csv"
list_name = ["Plucked string instrument", "Keyboard (musical)", "Percussion", "Orchestra", "Brass instrument", "Bowed string instrument", "Wind instrument, woodwind instrument", "Harp", "Choir", "Bell", "Harmonica", "Bass (instrument role)", "Musical ensemble"]

os.makedirs("data", exist_ok=True)
os.makedirs("data\\Categories\\Music", exist_ok=True)
```

```python
categorie_name = "data\\Categories\\SoT\\sound_of_things"
list_name = ["Vehicle", "Engine", "Domestic sounds, home sounds", "Bell", "Alarm", "Mechanisms", "Tools", "Explosion", "Wood", "Glass", "Liquid", "Miscellaneous sources", "Specific impact sounds"]

os.makedirs("data", exist_ok=True)
os.makedirs("data\\Categories\\SoT", exist_ok=True)
```

- On a des duplicas : 
    - On a des duplicas d'animaux dans le dataset animaux (chien et chat dans la même video)
    - On a des duplicas de musique dans le dataset animaux (des videos de musique dans le dataset animaux)
    - On a des duplicas de sot dans le dataset animaux (des videos de sot dans le dataset animaux)
    - Et vise-versa
- Donc on va supprimer les duplicas: 
    - D'animaux dans animaux (en enlevant les videos qui ont le même lien youtube)
    - De musique dans animaux (en enlevant les videos qui ont le même lien youtube)
    - De sot dans animaux (en enlevant les videos qui ont le même lien youtube)
- On obtient donc un csv final avec des sons d'animaux ou y'a pas de musique ou de sot (parfait pour la classification)
- Puis on réitère l'opération pour les autres thèmes

```python
csv_file = "data\\Categories\\Animals\\Animals.csv"
duplicated_csv_file_Animal = csv_file.replace(".csv", "_duplicated.csv")
duplicated_csv_file_Music = "data\\Categories\\Music\\Instruments.csv"
duplicated_csv_file_SoT = "data\\Categories\\SoT\\sound_of_things.csv"
reduced_csv_file_animal = csv_file.replace(".csv", "_animals_reduced.csv")
reduced_csv_file_music = csv_file.replace(".csv", "_music_reduced.csv")
reduced_csv_file_sot = csv_file.replace(".csv", "_final_reduced.csv")

create_reduced_csv_file(csv_file, duplicated_csv_file_Animal, reduced_csv_file_animal)
create_reduced_csv_file(reduced_csv_file_animal, duplicated_csv_file_Music, reduced_csv_file_music)
create_reduced_csv_file(reduced_csv_file_music, duplicated_csv_file_SoT, reduced_csv_file_sot)

# On supprime les fichiers csv intermédiaires
os.remove(reduced_csv_file_animal)
os.remove(reduced_csv_file_music)
```

```python
csv_file = "data\\Categories\\Music\\Instruments.csv"
duplicated_csv_file_Animal = "data\\Categories\\Animals\\Animals.csv" 
duplicated_csv_file_Music = csv_file.replace(".csv", "_duplicated.csv")
duplicated_csv_file_SoT = "data\\Categories\\SoT\\sound_of_things.csv"
reduced_csv_file_animal = csv_file.replace(".csv", "_final_reduced.csv")
reduced_csv_file_music = csv_file.replace(".csv", "_music_reduced.csv")
reduced_csv_file_sot = csv_file.replace(".csv", "_sot_reduced.csv")

create_reduced_csv_file(csv_file, duplicated_csv_file_Music, reduced_csv_file_music)
create_reduced_csv_file(reduced_csv_file_music, duplicated_csv_file_SoT, reduced_csv_file_sot)
create_reduced_csv_file(reduced_csv_file_sot, duplicated_csv_file_Animal, reduced_csv_file_animal)

# On supprime les fichiers csv intermédiaires
os.remove(reduced_csv_file_sot)
os.remove(reduced_csv_file_music)
```
