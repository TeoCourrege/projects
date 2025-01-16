import os
# List the folders in the "data\\Categories" folder
list_categories = os.listdir("data\\Categories")



# In each of these files, there is 2 csv files, one with the name "name.csv" and one with the name "name_duplicated.csv"
# We define a function to create a 3rd csv file with the name "name_reduced.csv" where we remove the lines that are in the "name_duplicated.csv" file and that are also in the "name.csv" file.
def create_reduced_csv_file(csv_file, duplicated_csv_file, reduced_csv_file):
    # getting a list of the first column of the duplicated csv file
    list_of_first_column = []
    with open(duplicated_csv_file, 'r') as f:
        for line in f:
            list_of_first_column.append(line.split(',', 1)[0])
    # Browse the csv file and remove the lines that are in the duplicated csv file
    with open(csv_file, 'r') as f:
        with open(reduced_csv_file, 'w') as g:
            for line in f:
                if line.split(',', 1)[0] not in list_of_first_column:
                    g.write(line)
                else:
                    #print("Line removed : " + line)
                    pass

    return len(list_of_first_column)
        

csv_file = "data\\Categories\\SoT\\sound_of_things.csv"
duplicated_csv_file_Animal = "data\\Categories\\Animals\\Animals.csv" 
duplicated_csv_file_Music = "data\\Categories\\Music\\Instruments.csv"
duplicated_csv_file_SoT = csv_file.replace(".csv", "_duplicated.csv")

reduced_csv_file_animal = csv_file.replace(".csv", "_final_reduced.csv")
reduced_csv_file_music = csv_file.replace(".csv", "_music_reduced.csv")
reduced_csv_file_sot = csv_file.replace(".csv", "_sot_reduced.csv")

create_reduced_csv_file(csv_file, duplicated_csv_file_SoT, reduced_csv_file_sot)
create_reduced_csv_file(reduced_csv_file_sot, duplicated_csv_file_Music, reduced_csv_file_music)
create_reduced_csv_file(reduced_csv_file_music, duplicated_csv_file_Animal, reduced_csv_file_animal)

# On supprime les fichiers csv intermédiaires
os.remove(reduced_csv_file_music)
os.remove(reduced_csv_file_sot)