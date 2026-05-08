import csv

# Open the CSV file in read mode
with open("favorites.csv", "r") as file:
    
    # Create a reader object to iterate over lines in the CSV
    reader = csv.reader(file)
    
    # Skip the header row (the first line with column names)
    next(reader)
    
    # Loop through each remaining row in the CSV
    for row in reader:
        # Print the data in the second column (index 1)
        # Assuming index 1 is the 'language' column
        print(row[1])
