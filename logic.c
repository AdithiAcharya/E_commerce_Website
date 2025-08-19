


#include <stdio.h>
#include <string.h>
#define MAX_ITEMS 10
#define MAX_CART_ITEMS 20

typedef enum {
    MEN,
    WOMEN,
    KIDS
} Category;

typedef struct {
    char name[50];
    float price;
    int quantity;
} Item;

typedef struct {
    Item item;
    int quantity;
} CartItem;

CartItem cart[MAX_CART_ITEMS];
int cart_size = 0;

void display_categories() {
    printf("Select Category:\n");
    printf("1. Men\n");
    printf("2. Women\n");
    printf("3. Kids\n");
}

int get_category_choice() {
    int choice;
    do {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3)
        {
            printf("Invalid choice.\n");
            while (getchar() != '\n');
        }
    }
    while (choice < 1 || choice > 3);
    return choice - 1;
}

void display_clothing_types(Category category) {
    switch (category) {
        case MEN:
            printf("Select Clothing Type (Men):\n");
            printf("1. Western\n");
            printf("2. Ethnic\n");
            break;
        case WOMEN:
            printf("Select Clothing Type (Women):\n");
            printf("1. Western\n");
            printf("2. Ethnic\n");
            printf("3. Traditional\n");
            break;
        case KIDS:
            printf("Select Clothing Type (Kids):\n");
            printf("1. Casual\n");
            printf("2. Formal\n");
            break;
    }
}

int get_clothing_type_choice(Category category) {
    int choice;
    do {
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            while (getchar() != '\n');
        } else {
            switch (category)
            {
                case MEN:
                    if (choice < 1 || choice > 2)
                    {
                        printf("Invalid choice.\n");
                    }
                    break;
                case WOMEN:
                    if (choice < 1 || choice > 3)
                    {
                        printf("Invalid choice.\n");
                    }
                    break;
                case KIDS:
                    if (choice < 1 || choice > 2)
                    {
                        printf("Invalid choice.\n");
                    }
                    break;
            }
        }
    }
    while ((category == MEN && (choice < 1 || choice > 2)) ||
             (category == WOMEN && (choice < 1 || choice > 3)) ||
             (category == KIDS && (choice < 1 || choice > 2)));
    return choice - 1;
}

void display_dresses(Category category, int clothing_type) {
    switch (category) {
        case MEN:
            if (clothing_type == 0)
            {
                printf("Select Dress (Men - Western):\n");
                printf("1. Pants\n");
                printf("2. T-Shirt\n");
                printf("3. Shirt\n");
                printf("4. Suit\n");
            }
            else
            {
                printf("Select Dress (Men - Ethnic):\n");
                printf("1. Kurta\n");
                printf("2. Dhoti\n");
                printf("3. Sherwani\n");
            }
            break;
        case WOMEN:
            if (clothing_type == 0)
            {
                printf("Select Dress (Women - Western):\n");
                printf("1. Jeans\n");
                printf("2. Dress\n");
                printf("3. Top\n");
                printf("4. Skirt\n");
            }
            else if (clothing_type == 1)
            {
                printf("Select Dress (Women - Ethnic):\n");
                printf("1. Saree\n");
                printf("2. Salwar Kameez\n");
                printf("3. Lehenga\n");
            }
            else
            {
                printf("Select Dress (Women - Traditional):\n");
                printf("1. Lehenga\n");
                printf("2. Anarkali Suit\n");
            }
            break;
        case KIDS:
            if (clothing_type == 0)
            {
                printf("Select Dress (Kids - Casual):\n");
                printf("1. T-Shirt\n");
                printf("2. Shorts\n");
                printf("3. Jeans\n");
                printf("4. Dress\n");
            }
            else
            {
                printf("Select Dress (Kids - Formal):\n");
                printf("1. Shirt\n");
                printf("2. Dress Pants\n");
                printf("3. Suit\n");
            }
            break;
    }
}

void add_to_cart(Item item, int quantity) {
    if (cart_size < MAX_CART_ITEMS) {
        cart[cart_size].item = item;
        cart[cart_size].quantity = quantity;
        cart_size++;
        printf("Item added to cart successfully.\n");
    }
    else
    {
        printf("Cart is full.\n");
    }
}

void view_cart()
{
    if (cart_size == 0)
    {
        printf("Cart is empty.\n");
        return;
    }

    printf("Cart:\n");
    for (int i = 0; i < cart_size; i++) {
        printf("%d. %s - $%.2f x %d\n", i + 1, cart[i].item.name, cart[i].item.price, cart[i].quantity);
    }
}

void place_order()
{
    if (cart_size == 0)
    {
        printf("Cart is empty.\n");
        return;
    }

    float total = 0;
    printf("Order Summary:\n");
    for (int i = 0; i < cart_size; i++)
    {
        printf("%d. %s - $%.2f x %d\n", i + 1, cart[i].item.name, cart[i].item.price, cart[i].quantity);
        total += cart[i].item.price * cart[i].quantity;
    }
    printf("Total: $%.2f\n", total);
    cart_size = 0;
    printf("Order placed successfully.\n");
}
int main() {
    while (1)
    {
        display_categories();
        Category category = get_category_choice();
        display_clothing_types(category);
        int clothing_type = get_clothing_type_choice(category);
        display_dresses(category, clothing_type);

        Item items[MAX_ITEMS];
        int num_items = 0;
        switch (category)
        {
            case MEN:
                if (clothing_type == 0)
                {
                    strcpy(items[0].name, "Pants"); items[0].price = 40.0;
                    strcpy(items[1].name, "T-Shirt"); items[1].price = 20.0;
                    strcpy(items[2].name, "Shirt"); items[2].price = 30.0;
                    strcpy(items[3].name, "Suit"); items[3].price = 100.0;
                    num_items = 4;
                }
                else
                {
                    strcpy(items[0].name, "Kurta"); items[0].price = 50.0;
                    strcpy(items[1].name, "Dhoti"); items[1].price = 25.0;
                    strcpy(items[2].name, "Sherwani"); items[2].price = 150.0;
                    num_items = 3;
                }
                break;
            case WOMEN:
                if (clothing_type == 0)
                {
                    strcpy(items[0].name, "Jeans"); items[0].price = 50.0;
                    strcpy(items[1].name, "Dress"); items[1].price = 70.0;
                    strcpy(items[2].name, "Top"); items[2].price = 30.0;
                    strcpy(items[3].name, "Skirt"); items[3].price = 40.0;
                    num_items = 4;
                }
                else if (clothing_type == 1)
                {
                    strcpy(items[0].name, "Saree"); items[0].price = 100.0;
                    strcpy(items[1].name, "Salwar Kameez"); items[1].price = 60.0;
                    strcpy(items[2].name, "Lehenga"); items[2].price = 150.0;
                    num_items = 3;
                }
                else
                {
                    strcpy(items[0].name, "Lehenga"); items[0].price = 150.0;
                    strcpy(items[1].name, "Anarkali Suit"); items[1].price = 120.0;
                    num_items = 2;
                }
                break;
            case KIDS:
                if (clothing_type == 0)
                {
                    strcpy(items[0].name, "T-Shirt"); items[0].price = 15.0;
                    strcpy(items[1].name, "Shorts"); items[1].price = 20.0;
                    strcpy(items[2].name, "Jeans"); items[2].price = 30.0;
                    strcpy(items[3].name, "Dress"); items[3].price = 25.0;
                    num_items = 4;
                }
                else
                {
                    strcpy(items[0].name, "Shirt"); items[0].price = 25.0;
                    strcpy(items[1].name, "Dress Pants"); items[1].price = 30.0;
                    strcpy(items[2].name, "Suit"); items[2].price = 50.0;
                    num_items = 3;
                }
                break;
        }
        printf("Enter the item number to add to cart: ");
        int item_choice;
        scanf("%d", &item_choice);
       

        if (item_choice < 1 || item_choice > num_items)
        {
            printf("Invalid item choice.\n");
            continue;
        }
        printf("Enter the quantity: ");
        int quantity;
        scanf("%d", &quantity);
        add_to_cart(items[item_choice - 1], quantity);
        printf("Do you want to view the cart or place an order? (v/p): ");
        char action;
        while (getchar() != '\n');
        scanf("%c", &action);
        if (action == 'v')
        {
            view_cart();
        }
        else if (action == 'p')
        {
            place_order();
        }
        else
        {
            printf("Invalid action.\n");
        }
        printf("Do you want to continue shopping? (y/n): ");
        char cont;
        while (getchar() != '\n');
        scanf("%c", &cont);
        if (cont == 'n')
        {
            break;
        }
    }

    return 0;
}
