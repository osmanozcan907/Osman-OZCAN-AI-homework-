import csv

def main():
    file_path = "favorites.csv"
    # Yapı: {language: {problem: count}}
    data = {}

    try:
        with open(file_path, "r") as file:
            reader = csv.DictReader(file)
            
            for row in reader:
                lang = row["language"]
                prob = row["problem"]

                # Dil henüz sözlükte yoksa ekle
                if lang not in data:
                    data[lang] = {}
                
                # Problem o dilin altında yoksa ekle, varsa sayısını artır
                if prob not in data[lang]:
                    data[lang][prob] = 1
                else:
                    data[lang][prob] += 1

        # Rapor Başlığı
        print(f"{'Language':<15} | {'Most Common Problem'}")
        print("-" * 40)

        # Her dil için en sık rastlanan problemi bul ve yazdır
        for lang in sorted(data):
            # O dile ait problemler içinden değeri (count) en yüksek olanı bul
            most_common = max(data[lang], key=data[lang].get)
            print(f"{lang:<15} | {most_common}")

    except FileNotFoundError:
        print(f"Error: {file_path} not found.")
    except KeyError:
        print("Error: Ensure CSV has 'language' and 'problem' columns.")

if __name__ == "__main__":
    main()
