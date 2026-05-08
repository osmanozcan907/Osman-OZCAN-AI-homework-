-- ============================================================
-- SQL MASTER FILE: From Basics to Database Design
-- ============================================================

.headers on
.mode column

-- ============================================================
-- SECTION 1: BASICS & QUERIES (school.db context)
-- ============================================================

-- 1.1 - 1.10: Basic Selections
SELECT first_name, last_name FROM students;
SELECT email FROM students ORDER BY email ASC;
SELECT first_name, last_name, gpa FROM students WHERE gpa > 3.5;
SELECT * FROM students WHERE enrollment_year = 2021;
SELECT * FROM students WHERE gpa BETWEEN 3.0 AND 3.5;
SELECT * FROM students WHERE email = 'grace@school.edu';
SELECT * FROM students ORDER BY id LIMIT 5;
SELECT first_name, last_name FROM students WHERE gpa IS NULL;
SELECT first_name, last_name, salary FROM teachers WHERE salary > 80000;
SELECT code, title FROM courses WHERE credits = 4;

-- 2.1 - 2.12: Advanced Filtering
SELECT * FROM students WHERE last_name LIKE '%s%';
SELECT * FROM teachers WHERE email LIKE '%@cs50.harvard.edu';
SELECT * FROM students ORDER BY gpa DESC LIMIT 5;
SELECT DISTINCT enrollment_year FROM students;
SELECT * FROM courses WHERE department_id IN (1, 2);
SELECT * FROM students WHERE enrollment_year NOT IN (2018);
SELECT * FROM courses ORDER BY credits DESC, title ASC;
SELECT * FROM students WHERE first_name LIKE '____'; -- 4 letters challenge

-- ============================================================
-- SECTION 2: JOINS & AGGREGATES
-- ============================================================

-- 3.1 - 3.4: Linking Tables
SELECT s.first_name, s.last_name, c.title
FROM students s
JOIN enrollments e ON s.id = e.student_id
JOIN courses c ON e.course_id = c.id;

-- 4.1 - 4.12: Statistics & Grouping
SELECT COUNT(*) AS total_students FROM students;
SELECT enrollment_year, COUNT(*) FROM students GROUP BY enrollment_year;
SELECT ROUND(AVG(gpa), 2) FROM students;
SELECT department_id, COUNT(*) FROM courses GROUP BY department_id;

SELECT c.title, COUNT(e.id) AS student_count
FROM courses c
JOIN enrollments e ON c.id = e.course_id
GROUP BY c.id
HAVING student_count > 3;

-- ============================================================
-- SECTION 3: SUBQUERIES
-- ============================================================

-- 5.1: GPA above average
SELECT first_name, last_name, gpa 
FROM students 
WHERE gpa > (SELECT AVG(gpa) FROM students);

-- 5.2: Enrolled in CS50 using Subquery
SELECT first_name, last_name FROM students 
WHERE id IN (
    SELECT student_id FROM enrollments WHERE course_id = (
        SELECT id FROM courses WHERE code = 'CS50'
    )
);

-- ============================================================
-- SECTION 4: DATABASE DESIGN (Schema Creation)
-- ============================================================

-- Social Media Design
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT UNIQUE NOT NULL,
    email TEXT UNIQUE NOT NULL
);

CREATE TABLE posts (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    user_id INTEGER,
    content TEXT NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users(id)
);

CREATE TABLE follows (
    follower_id INTEGER,
    followed_id INTEGER,
    PRIMARY KEY (follower_id, followed_id),
    FOREIGN KEY (follower_id) REFERENCES users(id),
    FOREIGN KEY (followed_id) REFERENCES users(id)
);

-- ============================================================
-- SECTION 5: DATA SEEDING & VERIFICATION
-- ============================================================

INSERT INTO users (username, email) VALUES ('osman', 'osman@mail.com'), ('ali', 'ali@mail.com');
INSERT INTO posts (user_id, content) VALUES (1, 'SQL ogreniyorum!'), (1, 'Veritabanı tasarımı harika.');

-- En çok post paylaşan kullanıcıyı bulma
SELECT u.username, COUNT(p.id) AS post_count
FROM users u
LEFT JOIN posts p ON u.id = p.user_id
GROUP BY u.id
ORDER BY post_count DESC;
