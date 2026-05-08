import csv

# Open and process in a concise format
with open("favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        print(row["language"])
