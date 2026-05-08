.headers on
.mode column

-- 5.1: Students with GPA above the average (school.db)
SELECT first_name, last_name, gpa 
FROM students 
WHERE gpa > (SELECT AVG(gpa) FROM students);

-- 5.2: Students enrolled in CS50 (use subquery) (school.db)
SELECT first_name, last_name 
FROM students 
WHERE id IN (
    SELECT student_id FROM enrollments WHERE course_id = (
        SELECT id FROM courses WHERE code = 'CS50'
    )
);

-- 5.3: Students NOT enrolled in CS50 (school.db)
SELECT first_name, last_name 
FROM students 
WHERE id NOT IN (
    SELECT student_id FROM enrollments WHERE course_id = (
        SELECT id FROM courses WHERE code = 'CS50'
    )
);

-- 5.4: Courses taught by the highest-paid teacher (school.db)
SELECT code, title 
FROM courses 
WHERE teacher_id = (SELECT id FROM teachers ORDER BY salary DESC LIMIT 1);

-- 5.5: Students enrolled in 3 or more courses (subquery in FROM) (school.db)
SELECT name 
FROM (
    SELECT s.first_name || ' ' || s.last_name AS name, COUNT(e.id) AS count
    FROM students s
    JOIN enrollments e ON s.id = e.student_id
    GROUP BY s.id
) 
WHERE count >= 3;

-- 5.6: Members who borrowed more than 2 books (library.db)
SELECT first_name, last_name 
FROM members 
WHERE id IN (
    SELECT member_id FROM loans GROUP BY member_id HAVING COUNT(*) > 2
);

-- 5.7: Books with more pages than average (library.db)
SELECT title, pages 
FROM books 
WHERE pages > (SELECT AVG(pages) FROM books);

-- 5.8: Students with at least one grade (EXISTS) (school.db)
SELECT first_name, last_name 
FROM students s
WHERE EXISTS (
    SELECT 1 FROM enrollments e 
    JOIN grades g ON e.id = g.enrollment_id 
    WHERE e.student_id = s.id
);

-- 5.9: Courses with no grades recorded (NOT EXISTS) (school.db)
SELECT title 
FROM courses c
WHERE NOT EXISTS (
    SELECT 1 FROM enrollments e 
    JOIN grades g ON e.id = g.enrollment_id 
    WHERE e.course_id = c.id
);

-- 5.10 CHALLENGE: Course(s) with the most enrollments (no LIMIT) (school.db)
-- LIMIT kullanmadan en yükseği bulmak için ALL veya alt sorgu ile MAX kullanılır
SELECT title 
FROM courses 
WHERE id IN (
    SELECT course_id 
    FROM enrollments 
    GROUP BY course_id 
    HAVING COUNT(*) = (
        SELECT MAX(count) 
        FROM (SELECT COUNT(*) AS count FROM enrollments GROUP BY course_id)
    )
);
