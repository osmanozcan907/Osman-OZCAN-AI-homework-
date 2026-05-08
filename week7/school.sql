import sqlite3

# Bellekte (RAM) geçici bir veritabanı oluşturup bağlanıyoruz
db = sqlite3.connect(":memory:")
db.row_factory = sqlite3.Row  # Sonuçları sözlük (dictionary) benzeri yapıda almak için
cursor = db.cursor()

# 1. İlişkisel Tablo Yapısını Kuruyoruz (Öğrenci, Bölüm ve Ders Kaydı)
cursor.executescript("""
    CREATE TABLE depts (id INTEGER PRIMARY KEY, name TEXT, building TEXT);
    CREATE TABLE students (id INTEGER PRIMARY KEY, name TEXT, gpa REAL);
    CREATE TABLE enrollments (id INTEGER PRIMARY KEY, student_id INTEGER, dept_id INTEGER, 
                              FOREIGN KEY(student_id) REFERENCES students(id),
                              FOREIGN KEY(dept_id) REFERENCES depts(id));
    
    INSERT INTO depts (name, building) VALUES ('Yapay Zeka', 'Teknokent'), ('Yazılım', 'Mühendislik');
    INSERT INTO students (name, gpa) VALUES ('Osman Özcan', 3.9), ('Alice', 3.5);
    INSERT INTO enrollments (student_id, dept_id) VALUES (1, 1), (2, 2);
""")

# 2. Verileri Birleştirip Anlamlı Hale Getiren SQL Sorgusu (JOIN Operasyonu)
# Burada 3 farklı tabloyu tek bir 'paragraf' gibi birleştiriyoruz
query = """
    SELECT s.name, s.gpa, d.name AS bolum, d.building 
    FROM students s
    JOIN enrollments e ON s.id = e.student_id
    JOIN depts d ON e.dept_id = d.id
    ORDER BY s.gpa DESC;
"""

# 3. Sonuçları Ekrana Basıyoruz
print(f"{'Öğrenci':<15} | {'GPA':<5} | {'Bölüm':<15} | {'Bina'}")
print("-" * 55)
for row in cursor.execute(query):
    print(f"{row['name']:<15} | {row['gpa']:<5} | {row['bolum']:<15} | {row['building']}")

db.close()
