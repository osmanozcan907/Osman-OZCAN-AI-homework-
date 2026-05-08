/**
 * Exercise 7: Local Storage — Notes App
 */

// ============================================================
// TASK 1 — Initialize: Load notes from localStorage
// ============================================================

const STORAGE_KEY = 'week9_notes';

// localStorage'dan veriyi çek veya boş dizi ata
let notes = JSON.parse(localStorage.getItem(STORAGE_KEY)) || [];
let editingId = null; 

function saveNotes() {
  // Veriyi JSON string formatına çevirip kaydet
  localStorage.setItem(STORAGE_KEY, JSON.stringify(notes));
}

// ============================================================
// TASK 3 — Render Notes
// ============================================================

const notesContainer = document.querySelector('#notes-container');

function renderNotes(filter = '') {
  notesContainer.innerHTML = '';

  // TODO: Search filtreleme
  let filtered = notes.filter(n => 
    n.title.toLowerCase().includes(filter.toLowerCase()) || 
    n.body.toLowerCase().includes(filter.toLowerCase())
  );

  // TODO: Pinlenenleri başa alacak şekilde sıralama
  filtered.sort((a, b) => b.pinned - a.pinned || new Date(b.createdAt) - new Date(a.createdAt));

  if (filtered.length === 0) {
    notesContainer.innerHTML = `
      <div class="empty-state">
        <p>${filter ? `No results for "${filter}"` : 'No notes yet. Create your first one!'}</p>
      </div>`;
    return;
  }

  // Her not için kart oluşturma
  filtered.forEach(note => {
    const card = document.createElement('div');
    card.className = `note-card ${note.pinned ? 'pinned' : ''}`;
    
    // Tarih formatlama
    const date = new Date(note.createdAt).toLocaleDateString('tr-TR', {
      hour: '2-digit', minute: '2-digit'
    });

    // Body önizleme (100 karakter sınırı)
    const bodyPreview = note.body.length > 100 
      ? note.body.substring(0, 100) + '...' 
      : note.body;

    card.innerHTML = `
      <div class="note-header">
        <h3>${note.pinned ? '📌 ' : ''}${note.title}</h3>
        <small>${date}</small>
      </div>
      <p>${bodyPreview}</p>
      <div class="note-actions">
        <button data-id="${note.id}" data-action="edit">Edit</button>
        <button data-id="${note.id}" data-action="pin">${note.pinned ? 'Unpin' : 'Pin'}</button>
        <button data-id="${note.id}" data-action="delete" class="btn-delete">Delete</button>
      </div>
    `;
    notesContainer.appendChild(card);
  });
}

// ============================================================
// TASK 2 — Create & Update Notes
// ============================================================

const noteForm     = document.querySelector('#note-form');
const titleInput   = document.querySelector('#note-title');
const bodyInput    = document.querySelector('#note-body');
const submitBtn    = document.querySelector('#btn-submit');
const cancelBtn    = document.querySelector('#btn-cancel');

noteForm.addEventListener('submit', function(event) {
  event.preventDefault();

  const title = titleInput.value.trim();
  const body  = bodyInput.value.trim();

  if (!title) { titleInput.focus(); return; }

  if (editingId !== null) {
    // ===== TASK 4: UPDATE existing note =====
    notes = notes.map(n => {
      if (n.id === editingId) {
        return { ...n, title, body };
      }
      return n;
    });
    
    editingId = null;
    submitBtn.textContent = '💾 Save Note';
    cancelBtn.classList.add('hidden');
    document.querySelector('#form-title').textContent = 'New Note';

  } else {
    // ===== TASK 2: CREATE new note =====
    const newNote = {
      id: Date.now(), // Benzersiz ID için zaman damgası
      title: title,
      body: body,
      createdAt: new Date().toISOString(),
      pinned: false
    };
    notes.unshift(newNote); // Yeni notu başa ekle
  }

  saveNotes();
  renderNotes();
  noteForm.reset();
});

cancelBtn.addEventListener('click', function() {
  editingId = null;
  noteForm.reset();
  this.classList.add('hidden');
  submitBtn.textContent = '💾 Save Note';
  document.querySelector('#form-title').textContent = 'New Note';
});

// ============================================================
// TASKS 4 & 5 — Edit, Pin, Delete via Event Delegation
// ============================================================

notesContainer.addEventListener('click', function(event) {
  const btn = event.target.closest('button[data-action]');
  if (!btn) return;

  const id     = parseInt(btn.dataset.id);
  const action = btn.dataset.action;

  if (action === 'delete') {
    if (confirm('Are you sure you want to delete this note?')) {
      notes = notes.filter(n => n.id !== id);
      saveNotes();
      renderNotes();
    }
  }

  if (action === 'pin') {
    notes = notes.map(n => n.id === id ? { ...n, pinned: !n.pinned } : n);
    saveNotes();
    renderNotes();
  }

  if (action === 'edit') {
    const noteToEdit = notes.find(n => n.id === id);
    if (noteToEdit) {
      editingId = id;
      titleInput.value = noteToEdit.title;
      bodyInput.value = noteToEdit.body;
      
      // UI Güncelleme
      submitBtn.textContent = 'Update Note';
      cancelBtn.classList.remove('hidden');
      document.querySelector('#form-title').textContent = 'Edit Note';
      window.scrollTo(0, 0); // Formun olduğu sidebar'a odaklanmak için
    }
  }
});

// ============================================================
// TASK 6 — Search Filter
// ============================================================

const searchInput = document.querySelector('#search-input');
searchInput.addEventListener('input', (e) => {
  renderNotes(e.target.value);
});

// ============================================================
// Initialize
// ============================================================
renderNotes();
