/**
 * script.js — Final Project: FocusTask Manager
 * ===========================================
 * Requirements fulfilled: 
 * - const/let usage
 * - async/await fetch with try/catch
 * - localStorage persistence
 * - Modular named functions
 */

// --- 1. STATE & SELECTORS ---
const STORAGE_KEY = 'focustask_data';
let tasks = JSON.parse(localStorage.getItem(STORAGE_KEY)) || [];

const taskForm = document.querySelector('#task-form');
const taskList = document.querySelector('#task-list');
const taskTitleInput = document.querySelector('#task-title');
const priorityInput = document.querySelector('#task-priority');
const quoteContainer = document.querySelector('#quote-box'); // Opsiyonel: HTML'e eklenebilir

// --- 2. INITIALIZATION ---
document.addEventListener('DOMContentLoaded', () => {
  renderTasks();
  fetchDailyInspiration();
});

// --- 3. CORE FUNCTIONS (CRUD) ---

/**
 * Görevleri localStorage'a kaydeder ve arayüzü günceller.
 */
function syncStorage() {
  localStorage.setItem(STORAGE_KEY, JSON.stringify(tasks));
  renderTasks();
}

/**
 * Yeni görev oluşturur.
 */
function addTask(event) {
  event.preventDefault();

  const title = taskTitleInput.value.trim();
  const priority = priorityInput.value;

  if (!title) return;

  const newTask = {
    id: Date.now(),
    title,
    priority,
    completed: false,
    createdAt: new Date().toISOString()
  };

  tasks.unshift(newTask);
  taskForm.reset();
  syncStorage();
}

/**
 * Görevi siler.
 */
function deleteTask(id) {
  tasks = tasks.filter(task => task.id !== id);
  syncStorage();
}

/**
 * Görevi tamamlandı/tamamlanmadı olarak işaretler.
 */
function toggleTask(id) {
  tasks = tasks.map(task => 
    task.id === id ? { ...task, completed: !task.completed } : task
  );
  syncStorage();
}

// --- 4. ASYNC API CALL (Requirement) ---

/**
 * Harici API'den rastgele bir motivasyon sözü çeker.
 */
async function fetchDailyInspiration() {
  try {
    const response = await fetch('https://dummyjson.com/quotes/random');
    
    if (!response.ok) throw new Error('Network response failed');
    
    const data = await response.json();
    displayQuote(data.quote, data.author);
  } catch (error) {
    console.error('Quote Fetch Error:', error);
    displayQuote("Focus on being productive instead of busy.", "Tim Ferriss");
  }
}

// --- 5. UI RENDERING ---

/**
 * Görev listesini DOM'a basar.
 */
function renderTasks() {
  taskList.innerHTML = '';

  if (tasks.length === 0) {
    taskList.innerHTML = '<li class="empty-msg">No tasks yet. Start by adding one!</li>';
    return;
  }

  tasks.forEach(task => {
    const li = document.createElement('li');
    li.className = `task-item ${task.priority} ${task.completed ? 'done' : ''}`;
    
    li.innerHTML = `
      <div class="task-content">
        <input type="checkbox" ${task.completed ? 'checked' : ''} 
               onchange="toggleTask(${task.id})">
        <span>${task.title}</span>
      </div>
      <button class="delete-btn" onclick="deleteTask(${task.id})">Delete</button>
    `;
    taskList.appendChild(li);
  });
}

/**
 * Çekilen sözü ekranda gösterir.
 */
function displayQuote(text, author) {
  const quoteArea = document.querySelector('#quote-display');
  if (quoteArea) {
    quoteArea.innerHTML = `<p>"${text}" — <strong>${author}</strong></p>`;
  }
}

// --- 6. EVENT LISTENERS ---
taskForm.addEventListener('submit', addTask);

// Global erişim için (onclick attribute'ları için gerekli)
window.toggleTask = toggleTask;
window.deleteTask = deleteTask;

console.log('Final project script loaded. Time to build something great! 🚀');
