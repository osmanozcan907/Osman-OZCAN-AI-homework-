import csv

def main():
    input_file = "favorites.csv"
    output_file = "language_summary.csv"
    counts = {}

    try:
        # 1. Adım: Veriyi Oku ve Say
        with open(input_file, "r") as file:
            reader = csv.DictReader(file)
            for row in reader:
                lang = row["language"]
                if lang in counts:
                    counts[lang] += 1
                else:
                    counts[lang] = 1

        # 2. Adım: Sonuçları Yeni CSV Dosyasına Yaz
        # 'w' modu dosyayı yazma amaçlı açar (varsa üzerine yazar)
        with open(output_file, "w", newline='') as file:
            # Sütun başlıklarını belirliyoruz
            writer = csv.writer(file)
            writer.writerow(["language", "votes"]) # Header (Başlık) satırı
            
            # Sözlükteki her bir dili ve oy sayısını satır satır yazıyoruz
            for lang in sorted(counts):
                writer.writerow([lang, counts[lang]])

        print(f"Successfully created {output_file} with {len(counts)} languages.")

    except FileNotFoundError:
        print(f"Error: {input_file} not found.")
    except KeyError:
        print("Error: Ensure CSV has a 'language' column.")

if __name__ == "__main__":
    main()
