import csv

# Open the CSV file (using a relative path)
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    
    for row in reader:
        favorite = row["language"]
        
        # EAFP approach: "Easier to Ask Forgiveness than Permission"
        try:
            # Try to add 1 to the existing count
            counts[favorite] += 1
        except KeyError:
            # If the language isn't in the dictionary yet, a KeyError happens.
            # We catch it and initialize the count to 1.
            counts[favorite] = 1

# Print the results
for favorite in counts:
    print(f"{favorite}: {counts[favorite]}")
