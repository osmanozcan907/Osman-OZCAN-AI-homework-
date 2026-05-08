import csv

# TODO: Open favorites.csv for reading
with open("favorites.csv", "r") as file:

    # TODO: Create a csv.reader object
    # This treats each line as a list of strings
    reader = csv.reader(file)

    # TODO: Skip the header row using next()
    # This prevents the script from printing the word "language"
    next(reader)

    # TODO: Loop over the remaining rows and print the language column
    for row in reader:
        # The language column is at index 1
        print(row[1])
