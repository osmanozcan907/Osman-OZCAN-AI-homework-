-- ============================================================
-- MASTER SQL BOOTCAMP: FROM ZERO TO DATABASE ARCHITECT
-- Databases: school.db & library.db
-- Concept: Week 8 SQL Intensive
-- ============================================================

/* 
   INSTRUCTIONS:
   1. Use a tool like SQLite3 to run this script.
   2. This file covers: Design, Queries, Joins, Aggregates, Subqueries, and Optimization.
*/

-- ============================================================
-- SECTION 1: DATABASE ARCHITECTURE (The Design Phase)
-- ============================================================

-- Creating the School Infrastructure
CREATE TABLE IF NOT EXISTS departments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    name TEXT NOT NULL,
    building TEXT
);

CREATE TABLE IF NOT EXISTS students (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    email TEXT UNIQUE NOT NULL,
    enrollment_year INTEGER,
    gpa REAL
);

CREATE TABLE IF NOT EXISTS courses (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    code TEXT UNIQUE NOT NULL,
    title TEXT NOT NULL,
    credits INTEGER NOT NULL,
    department_id INTEGER,
    FOREIGN KEY (department_id) REFERENCES departments(id)
);

CREATE TABLE IF NOT EXISTS enrollments (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    student_id INTEGER NOT NULL,
    course_id INTEGER NOT NULL,
    UNIQUE(student_id, course_id),
    FOREIGN KEY (student_id) REFERENCES students(id),
    FOREIGN KEY (course_id) REFERENCES courses(id)
);

-- ============================================================
-- SECTION 2: BASIC DATA RETRIEVAL (The SELECT Phase)
-- ============================================================

-- 1.1: Get full names of all students
SELECT first_name, last_name FROM students;

-- 1.3: Filter students with high academic standing
SELECT first_name, last_name, gpa FROM students WHERE gpa > 3.5;

-- 2.12: CHALLENGE - Find students with exactly 4-letter first names
SELECT * FROM students WHERE first_name LIKE '____';

-- ============================================================
-- SECTION 3: RELATIONAL DATA (The JOIN Phase)
-- ============================================================

-- 3.1: Combine Student names with their enrolled Course titles
SELECT s.first_name, s.last_name, c.title
FROM students s
JOIN enrollments e ON s.id = e.student_id
JOIN courses c ON e.course_id = c.id;

-- 3.5: Identify students with NO enrollments (Left Join Pattern)
SELECT s.first_name, s.last_name
FROM students s
LEFT JOIN enrollments e ON s.id = e.student_id
WHERE e.id IS NULL;

-- ============================================================
-- SECTION 4: DATA ANALYTICS (The AGGREGATE Phase)
-- ============================================================

-- 4.3: Calculate the average GPA rounded for reporting
SELECT ROUND(AVG(gpa), 2) AS institutional_average_gpa FROM students;

-- 4.7: Identify popular courses (More than 3 students)
SELECT c.title, COUNT(e.id) AS enrollment_count
FROM courses c
JOIN enrollments e ON c.id = e.course_id
GROUP BY c.id
HAVING enrollment_count > 3;

-- ============================================================
-- SECTION 5: ADVANCED LOGIC (The SUBQUERY & TRANSACTION Phase)
-- ============================================================

-- 5.1: List students performing better than the global average
SELECT first_name, last_name, gpa 
FROM students 
WHERE gpa > (SELECT AVG(gpa) FROM students);

-- 7.7: Atomic Transaction - Enrolling a student and ensuring integrity
BEGIN TRANSACTION;
    INSERT INTO enrollments (student_id, course_id) VALUES (1, 101);
    -- If one fails, the whole block fails (Atomic property)
COMMIT;

-- ============================================================
-- SECTION 6: PERFORMANCE TUNING (The INDEX Phase)
-- ============================================================

-- Create indexes to speed up heavy search queries
CREATE INDEX IF NOT EXISTS idx_student_email ON students(email);
CREATE INDEX IF NOT EXISTS idx_student_gpa ON students(gpa);

-- View the execution plan to verify efficiency
EXPLAIN QUERY PLAN 
SELECT * FROM students WHERE email = 'test@school.edu';

-- ============================================================
-- OUTPUT FORMATTING
-- ============================================================
.headers on
.mode column
SELECT 'SUCCESS: All exercises and schemas compiled into a single master file.' AS status;
