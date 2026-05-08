import csv

# Open the favorites CSV file from the week1 directory
with open("../week1/favorites.csv", "r") as file:
    reader = csv.DictReader(file)
    counts = {}
    
    for row in reader:
        favorite = row["language"]
        # Update the tally for each language found
        if favorite in counts:
            counts[favorite] += 1
        else:
            counts[favorite] = 1

# --- Sorting Logic ---
# sorted() creates a new list from the dictionary keys
# key=counts.get tells Python to sort the keys based on their values (the numbers)
# reverse=True ensures the largest numbers come first (Descending Order)
for favorite in sorted(counts, key=counts.get, reverse=True):
    print(f"{favorite}: {counts[favorite]}")
