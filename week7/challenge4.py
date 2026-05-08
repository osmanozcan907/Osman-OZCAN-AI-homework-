import sqlite3

def main():
    # Veritabanına bağlan
    try:
        db = sqlite3.connect("favorites.db")
        cursor = db.cursor()
    except sqlite3.OperationalError:
        print("Error: favorites.db not found. Please follow setup instructions.")
        return

    while True:
        print("\n--- SQL Explorer ---")
        print("1. Show all unique languages")
        print("2. Count users for a specific language")
        print("3. Top 5 most common problems")
        print("4. Search for a keyword in problems")
        print("5. Exit")

        choice = input("\nChoose an option (1-5): ")

        if choice == '1':
            # Benzersiz dilleri listele
            rows = cursor.execute("SELECT DISTINCT(language) FROM favorites ORDER BY language")
            print("\nLanguages in database:")
            for row in rows:
                print(f"- {row[0]}")

        elif choice == '2':
            # Belirli bir dile ait kayıtları say (SQL Injection korumalı)
            lang = input("Enter language (e.g., C, Python, Scratch): ")
            rows = cursor.execute("SELECT COUNT(*) FROM favorites WHERE language = ?", (lang,))
            count = rows.fetchone()[0]
            print(f"\nThere are {count} users who prefer {lang}.")

        elif choice == '3':
            # En yaygın 5 problemi bul
            query = """
                SELECT problem, COUNT(*) AS count 
                FROM favorites 
                GROUP BY problem 
                ORDER BY count DESC 
                LIMIT 5
            """
            rows = cursor.execute(query)
            print("\nTop 5 Common Problems:")
            for row in rows:
                print(f"{row[1]:>3} votes: {row[0]}")

        elif choice == '4':
            # Problem içinde anahtar kelime ara
            search = input("Enter keyword to search in problems: ")
            # LIKE operatörü için % işaretlerini ekliyoruz
            rows = cursor.execute("SELECT DISTINCT(problem) FROM favorites WHERE problem LIKE ?", (f"%{search}%",))
            print(f"\nProblems containing '{search}':")
            results = rows.fetchall()
            if results:
                for row in results:
                    print(f"- {row[0]}")
            else:
                print("No matches found.")

        elif choice == '5':
            print("Goodbye!")
            break
        else:
            print("Invalid choice, try again.")

    # Bağlantıyı kapat
    db.close()

if __name__ == "__main__":
    main()
