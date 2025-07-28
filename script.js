document.addEventListener('DOMContentLoaded', () => {
    const api = 'api.php';

    // --- DOM Elements ---
    const categoryButtons = document.querySelectorAll('.category-btn');
    const clothingTypePanel = document.getElementById('clothing-type-panel');
    const clothingTypesContainer = document.getElementById('clothing-types');
    const itemsPanel = document.getElementById('items-panel');
    const itemsGrid = document.getElementById('items-grid');

    const cartButton = document.getElementById('cart-button');
    const cartCountSpan = document.getElementById('cart-count');
    const cartModal = document.getElementById('cart-modal');
    const closeModalButton = document.querySelector('.close-button');
    const cartItemsContainer = document.getElementById('cart-items');
    const cartTotalContainer = document.getElementById('cart-total');
    const placeOrderBtn = document.getElementById('place-order-btn');

    let currentCategory = '';
    let currentClothingType = '';

    // --- Event Listeners ---

    // 1. Listen for clicks on Category buttons
    categoryButtons.forEach(button => {
        button.addEventListener('click', () => {
            currentCategory = button.dataset.category;
            itemsPanel.style.display = 'none'; // Hide items when category changes
            fetchClothingTypes(currentCategory);
        });
    });

    // 2. Listen for clicks on dynamically created Clothing Type buttons
    clothingTypesContainer.addEventListener('click', (e) => {
        if (e.target.classList.contains('clothing-type-btn')) {
            currentClothingType = e.target.dataset.type;
            fetchItems(currentCategory, currentClothingType);
        }
    });

    // 3. Listen for clicks on dynamically created "Add to Cart" buttons
    itemsGrid.addEventListener('click', (e) => {
        if (e.target.classList.contains('add-to-cart-btn')) {
            const card = e.target.closest('.item-card');
            const itemName = card.dataset.name;
            const itemPrice = card.dataset.price;
            const quantity = card.querySelector('input[type="number"]').value;
            addToCart(itemName, itemPrice, quantity);
        }
    });
    
    // 4. Cart modal listeners
    cartButton.addEventListener('click', viewCart);
    closeModalButton.addEventListener('click', () => cartModal.style.display = 'none');
    window.addEventListener('click', (e) => {
        if (e.target === cartModal) {
            cartModal.style.display = 'none';
        }
    });

    // 5. Place Order listener
    placeOrderBtn.addEventListener('click', placeOrder);
    
    // --- Functions ---

    async function fetchClothingTypes(category) {
        const response = await fetch(`${api}?action=get_clothing_types&category=${category}`);
        const types = await response.json();
        
        clothingTypesContainer.innerHTML = ''; // Clear previous types
        types.forEach(type => {
            const button = document.createElement('button');
            button.className = 'clothing-type-btn';
            button.dataset.type = type.id;
            button.textContent = type.name;
            clothingTypesContainer.appendChild(button);
        });
        clothingTypePanel.style.display = 'block';
    }

    async function fetchItems(category, clothingType) {
        const response = await fetch(`${api}?action=get_items&category=${category}&type=${clothingType}`);
        const items = await response.json();

        itemsGrid.innerHTML = ''; // Clear previous items
        items.forEach(item => {
            const card = `
                <div class="item-card" data-name="${item.name}" data-price="${item.price}">
                    <h3>${item.name}</h3>
                    <p class="price">$${item.price.toFixed(2)}</p>
                    <input type="number" value="1" min="1">
                    <button class="add-to-cart-btn">Add to Cart</button>
                </div>
            `;
            itemsGrid.innerHTML += card;
        });
        itemsPanel.style.display = 'block';
    }

    async function addToCart(name, price, quantity) {
        if (quantity < 1) {
            alert("Quantity must be at least 1.");
            return;
        }

        const formData = new FormData();
        formData.append('action', 'add_to_cart');
        formData.append('name', name);
        formData.append('price', price);
        formData.append('quantity', quantity);

        const response = await fetch(api, { method: 'POST', body: formData });
        const result = await response.json();

        if (result.success) {
            updateCartCount();
            alert(`${quantity} x ${name} added to cart!`);
        }
    }

    async function updateCartCount() {
        const response = await fetch(`${api}?action=get_cart_count`);
        const result = await response.json();
        cartCountSpan.textContent = result.count;
    }

    async function viewCart() {
        const response = await fetch(`${api}?action=get_cart`);
        const cartData = await response.json();
        
        cartItemsContainer.innerHTML = '';
        if (cartData.items.length === 0) {
            cartItemsContainer.innerHTML = '<p>Your cart is empty.</p>';
            placeOrderBtn.style.display = 'none';
        } else {
             placeOrderBtn.style.display = 'block';
        }

        cartData.items.forEach(item => {
            const itemElement = document.createElement('p');
            itemElement.textContent = `${item.name} - $${item.price.toFixed(2)} x ${item.quantity}`;
            cartItemsContainer.appendChild(itemElement);
        });

        cartTotalContainer.textContent = `Total: $${cartData.total.toFixed(2)}`;
        cartModal.style.display = 'block';
    }

    async function placeOrder() {
        const response = await fetch(`${api}?action=place_order`);
        const result = await response.json();
        
        alert(`Order placed successfully!\nTotal: $${result.total.toFixed(2)}`);
        
        cartModal.style.display = 'none';
        updateCartCount();
    }

    // Initial cart count update on page load
    updateCartCount();
});