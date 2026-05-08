import csv

def clean_data(input_f="messy_data.csv", output_f="cleaned_data.csv"):
    stats = {"rows": 0, "fixed_name": 0, "fixed_email": 0, "fixed_age": 0}
    cleaned = []
    try:
        with open(input_f, "r") as f:
            for row in csv.DictReader(f):
                stats["rows"] += 1
                name = row["name"].strip().title() or "Unknown"
                if name == "Unknown" or name != row["name"].strip(): stats["fixed_name"] += 1
                email = row["email"].strip().lower()
                if "@" not in email: email, stats["fixed_email"] = "invalid", stats["fixed_email"] + 1
                try: age = int(row["age"].strip())
                except: age, stats["fixed_age"] = 0, stats["fixed_age"] + 1
                cleaned.append({"name": name, "email": email, "age": age})
        with open(output_f, "w", newline='') as f:
            writer = csv.DictWriter(f, fieldnames=["name", "email", "age"])
            writer.writeheader()
            writer.writerows(cleaned)
        print(f"Report: {stats['rows']} processed. Fixes: Name({stats['fixed_name']}), Email({stats['fixed_email']}), Age({stats['fixed_age']}). Saved to {output_f}")
    except FileNotFoundError: print("Error: messy_data.csv not found.")

if __name__ == "__main__": clean_data()
