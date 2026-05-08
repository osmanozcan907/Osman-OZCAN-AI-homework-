from cs50 import SQL

# Connect to the SQLite database
db = SQL("sqlite:///favorites.db")

# Prompt the user for a specific problem name to count
# Example inputs: "Scratch", "Mario", "Speller"
favorite = input("Favorite: ")

# Execute a SQL query to count occurrences
# The '?' is a placeholder that prevents SQL Injection
# 'AS n' gives the count column a specific name for easier access
rows = db.execute(
    "SELECT COUNT(*) AS n FROM favorites WHERE problem = ?", favorite
)

# db.execute returns a LIST of DICTIONARIES. 
# Even if there is only one result, it's still at index 0.
row = rows[0]

# Access the value using the alias 'n' we defined in the query
print(row["n"])
