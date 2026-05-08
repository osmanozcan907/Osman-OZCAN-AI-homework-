from cs50 import SQL

# Connect to the SQLite database file
db = SQL("sqlite:///favorites.db")

# Execute a powerful SQL query that does three things at once:
# 1. SELECTs the language and counts all occurrences (AS n)
# 2. GROUP BY language: Collapses all identical entries into a single row per language
# 3. ORDER BY n DESC: Sorts the results so the highest count appears first
rows = db.execute(
    "SELECT language, COUNT(*) AS n FROM favorites GROUP BY language ORDER BY n DESC"
)

# db.execute returns a list of dictionaries, for example:
# [{'language': 'Python', 'n': 196}, {'language': 'C', 'n': 40}, ...]
for row in rows:
    # Print the language and its corresponding count side-by-side
    print(row["language"], row["n"])
