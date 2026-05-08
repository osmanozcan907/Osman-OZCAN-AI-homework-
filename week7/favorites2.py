import csv

with open("favorites.csv", "r") as file:
    # TODO: Create a csv.DictReader (not csv.reader)
    # This automatically uses the first row as the keys for each dictionary
    reader = csv.DictReader(file)
    
    # TODO: Loop over rows and print row["language"]
    for row in reader:
        # Instead of row[1], we use the actual header name
        print(row["language"])
