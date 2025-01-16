import os 

# We browse a class_labels_indices.csv file and retrieve the label associated with name, forming a list of names.
categorie_name = "data\\Categories\\Animals\\Animals"
list_name = ["Cat", "Dog", "Horse", "Donkey, ass", "Cattle, bovinae", "Pig", "Goat", "Sheep", "Fowl", "Roaring cats (lions, tigers)", "Bird"]

os.makedirs("data", exist_ok=True)
os.makedirs("data\\Categories\\Animals", exist_ok=True)

def get_labels_from_csv(csv_file, list_name):
    """ 
    This function reads a CSV file and retrieves the labels associated with the names in the provided list.
    Args:
        csv_file (str): The path to the CSV file.
        list_name (list): The list of names for which to retrieve labels.
    Returns:
        list: A list of labels associated with the names in list_name.
    """
    labels = []
    with open(csv_file, 'r') as f:
        for line in f:
            # split the line but oly for 2 commas
            _, label, name = line.split(',', 2)
            name = name.replace('"', '').replace('\n', '')
            if name in list_name:
                labels.append(label)
    return labels

# We create a new csv file with the name categorie_name and we retrive all the lines from the "balanced_train_segments.csv" file such that at least one of the labels is in the list of labels.
def create_csv_file(csv_file, categorie_name, labels):
    """
    This function creates a new CSV file and writes lines from the original CSV file to it. 
    Only lines that contain at least one of the labels in the provided list are written to the new file.
    Args:
        csv_file (str): The path to the original CSV file.
        categorie_name (str): The name of the category, used to name the new CSV file.
        labels (list): The list of labels to look for in the original CSV file.
    """
    with open(categorie_name + '.csv', 'w') as f:
        with open(csv_file, 'r') as g:
            for line in g:
                for label in labels:
                    if label in line:
                        f.write(line)
                        break

# Count the number of lines in the new csv file where there are at least 2 labels in the list of labels in the same line, print the line and return the number of lines.
def count_lines(csv_file, labels):
    """
    This function counts the number of lines in a CSV file that contain at least two labels from the provided list.
    Args:
        csv_file (str): The path to the CSV file.
        labels (list): The list of labels to look for in the CSV file.
    Returns:
        int: The number of lines that contain at least two labels from the list.
    """
    count = 0
    with open(csv_file, 'r') as f:
        for line in f:
            if sum([1 for label in labels if label in line]) >= 2:
                count += 1
                print("Line no. " + str(count) + " : " + line)
    return count

# Function to write the above lines in a new csv file categorie_name_duplicated.csv
def write_duplicated_lines(csv_file, labels):
    """
    This function writes lines from the original CSV file to a new file. 
    Only lines that contain at least two labels from the provided list are written to the new file.
    Args:
        csv_file (str): The path to the original CSV file.
        labels (list): The list of labels to look for in the original CSV file.
    """
    with open(csv_file, 'r') as f:
        with open(categorie_name + '_duplicated.csv', 'w') as g:
            for line in f:
                if sum([1 for label in labels if label in line]) >= 2:
                    g.write(line)


create_csv_file('balanced_train_segments.csv', categorie_name, get_labels_from_csv('class_labels_indices.csv', list_name))
write_duplicated_lines(categorie_name + '.csv', get_labels_from_csv('class_labels_indices.csv', list_name))