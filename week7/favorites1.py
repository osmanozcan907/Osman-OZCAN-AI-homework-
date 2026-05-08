import csv

with open("favorites.csv", "r") as file:
    reader = csv.reader(file)
    next(reader)
    
    for row in reader:
        # TODO: Store row[1] in a variable called 'favorite'
        # Assigning a name makes the code much easier to read
        favorite = row[1]
        
        # TODO: Print favorite
        print(favorite)
