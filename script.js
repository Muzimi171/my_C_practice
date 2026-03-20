// Sample recipes to initialize the app
const sampleRecipes = [
    {
        id: 1,
        name: "Chocolate Chip Cookies",
        description: "Delicious homemade cookies with chocolate chips, butter, and vanilla. Perfect for dessert or snacking."
    },
    {
        id: 2,
        name: "Spaghetti Carbonara",
        description: "Classic Italian pasta with creamy sauce made from eggs, cheese, and pancetta. Quick and easy to prepare."
    },
    {
        id: 3,
        name: "Grilled Salmon",
        description: "Fresh salmon fillet grilled to perfection with lemon and herbs. Healthy and delicious dinner option."
    },
    {
        id: 4,
        name: "Vegetable Stir-Fry",
        description: "Colorful mix of fresh vegetables sautéed with garlic and ginger. Served over rice or noodles."
    },
    {
        id: 5,
        name: "Chocolate Brownies",
        description: "Rich and fudgy brownies made with quality chocolate. Great for chocolate lovers everywhere."
    }
];

// Initialize recipes from localStorage or use sample recipes
let recipes = JSON.parse(localStorage.getItem('recipes')) || sampleRecipes;
let nextId = Math.max(...recipes.map(r => r.id), 0) + 1;

// DOM Elements
const recipeForm = document.getElementById('recipeForm');
const recipeNameInput = document.getElementById('recipeName');
const recipeDescriptionInput = document.getElementById('recipeDescription');
const recipeList = document.getElementById('recipeList');

// Event Listeners
recipeForm.addEventListener('submit', addRecipe);

// Initialize the app
renderRecipes();

// Add a new recipe
function addRecipe(e) {
    e.preventDefault();

    const name = recipeNameInput.value.trim();
    const description = recipeDescriptionInput.value.trim();

    if (name === '' || description === '') {
        alert('Please fill in all fields');
        return;
    }

    const newRecipe = {
        id: nextId++,
        name: name,
        description: description
    };

    recipes.push(newRecipe);
    saveRecipes();
    renderRecipes();

    // Clear the form
    recipeForm.reset();
    recipeNameInput.focus();
}

// Delete a recipe
function deleteRecipe(id) {
    recipes = recipes.filter(recipe => recipe.id !== id);
    saveRecipes();
    renderRecipes();
}

// Render all recipes to the DOM
function renderRecipes() {
    recipeList.innerHTML = '';

    if (recipes.length === 0) {
        recipeList.innerHTML = '<div class="empty-message">No recipes yet. Add your first recipe above!</div>';
        return;
    }

    recipes.forEach(recipe => {
        const recipeCard = createRecipeCard(recipe);
        recipeList.appendChild(recipeCard);
    });
}

// Create a recipe card element
function createRecipeCard(recipe) {
    const card = document.createElement('div');
    card.className = 'recipe-card';
    card.innerHTML = `
        <div class="recipe-content">
            <div class="recipe-name">${escapeHtml(recipe.name)}</div>
            <div class="recipe-description">${escapeHtml(recipe.description)}</div>
        </div>
        <button class="btn-delete" onclick="deleteRecipe(${recipe.id})">Delete</button>
    `;
    return card;
}

// Save recipes to localStorage
function saveRecipes() {
    localStorage.setItem('recipes', JSON.stringify(recipes));
}

// Escape HTML to prevent XSS attacks
function escapeHtml(text) {
    const map = {
        '&': '&amp;',
        '<': '&lt;',
        '>': '&gt;',
        '"': '&quot;',
        "'": '&#039;'
    };
    return text.replace(/[&<>"']/g, m => map[m]);
}
