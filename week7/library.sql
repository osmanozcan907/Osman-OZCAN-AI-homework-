SELECT books.title, authors.first_name, authors.last_name
FROM books
JOIN book_authors ON books.id = book_authors.book_id
JOIN authors ON book_authors.author_id = authors.id;
