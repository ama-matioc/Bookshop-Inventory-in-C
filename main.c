#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

struct book
{
    int id;
    char title[100];
    char author[100];
    int stock;
    int price;
} b;
void add()
{
    system("cls");
    printf("\n\t\t\t\t\t\t\tAdd a new book");
    printf("\n\nBook ID: ");
    int id = 0;
    scanf("%d", &id);

    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (b.id == id)
        {
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (found)
    {
        printf("\n\n\t\t\t\t\tBook with ID %d already exists in the inventory!\n", b.id);
        printf("\n\t\t\t\t\t\tPlease enter another book ID\n");
        sleep(3);
        add();
        return;
    }

    b.id = id;
    printf("\nBook title: ");
    scanf(" %[^\n]", b.title);
    printf("\nBook author: ");
    scanf(" %[^\n]", b.author);
    printf("\nBook price: ");
    scanf("%d", &b.price);
    printf("\nNo. of copies to add: ");
    int nr;
    scanf("%d", &nr);

    b.stock = 0;
    if (nr > 0)
        b.stock += nr;

    fp = fopen("inventory.txt", "a");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    fprintf(fp, "%d, %s, %s, %d, %d\n", b.id, b.title, b.author, b.stock, b.price);
    fclose(fp);

    printf("\n\n\t\t\t\t\t\tThe book was added successfully!\n\n");
    printf("\t\t\t\t\t\tPress 'm' to go back to the menu");
    switch(getch())
    {
    case 'm':
        menu();
        break;
    }
}
void del()
{
    system("cls");
    printf("\n\t\t\t\t\t\t\tDelete a book \n\n");
    int id;
    printf("Enter the ID of the book to delete: ");
    scanf("%d", &id);

    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }
    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (b.id != id)
        {
            fprintf(temp, "%d, %s, %s, %d, %d\n", b.id, b.title, b.author, b.stock, b.price);
        }
        else
        {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    if (found == 1)
    {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
        printf("\n\n\t\t\t\t\t\t The book was deleted successfully!\n\n");
    }
    else
    {
        remove("temp.txt");
        printf("\n\n\t\t\t\t\t\tBook not found in the inventory!\n\n");
    }
    printf("\t\t\t\t\t\tPress 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void update()
{
    system("cls");
    printf("\t\t\t\t\t\t\t Update a book");
    printf("\n\nBook ID: ");
    int id;
    scanf("%d", &id);

    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (b.id == id)
        {
            found = 1;
            printf("\nCurrent details of the book:\n\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStock: %d\nPrice: %d\n\n", b.id, b.title, b.author, b.stock, b.price);

            printf("Enter new details of the book:\n\n");
            printf("Book id: %d\n", b.id);
            printf("Book title: ");
            scanf(" %[^\n]", b.title);
            printf("Book author: ");
            scanf(" %[^\n]", b.author);
            printf("Book stock: ");
            scanf("%d", &b.stock);
            printf("Book price: ");
            scanf("%d", &b.price);
            fprintf(temp, "%d, %s, %s, %d, %d\n", b.id, b.title, b.author, b.stock, b.price);
            printf("\n\t\t\t\t\t\tThe book was updated successfully!\n\n\n");
            printf("Current book information: \nID: %d \nTitle: %s \nAuthor: %s \nStock: %d \nPrice: %d\n", b.id, b.title, b.author, b.stock, b.price);
        }
        else
        {
            fprintf(temp, "%d, %s, %s, %d, %d\n", b.id, b.title, b.author, b.stock, b.price);
        }
    }
    fclose(fp);
    fclose(temp);

    if (found == 0)
    {
        remove("temp.txt");
        printf("\n\n\t\t\t\t\t\t   Book with ID %d not found!\n\n", id);
    }
    else
    {
        remove("inventory.txt");
        rename("temp.txt", "inventory.txt");
    }

    printf("\t\t\t\t\t\tPress 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void show_inv()
{
    system("cls");
    printf ("\n\n--------------------------------------------------- FULL INVENTORY -----------------------------------------------------\n");
    print_f();
    printf("\n\n\t\t\t\t\t\tPress 'm' to go back to the menu");

    switch(getch())
    {
    case 'm':
        menu();
        break;
    }
}
void print_f()
{
    printf("\n\nID\t\tTITLE\t\t\tAUTHOR\t\t\t    STOCK\tPRICE\n");
    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        printf("%-10d%-30s%-30s%-10d%-10d\n", b.id, b.title, b.author, b.stock, b.price);
    }
    fclose(fp);
}
void sort()
{
    system("cls");
    printf("Sort by: \n");
    printf("1. Book ID\n");
    printf("2. Book title\n");
    printf("3. Book author\n");
    printf("4. Low stock\n");
    switch (getch())
    {
    case '1':
        sortid();
        break;
    case '2':
        sorttitle();
        break;
    case '3':
        sortauthor();
        break;
    case '4':
        sortstock();
        break;
    }

    switch(getch())
    {
    case 'm':
        menu();
        break;
    }
}
void sortstock()
{
    system("cls");
    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i, j, n = 0;
    char line[256];
    struct book books[100];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &books[n].id, books[n].title, books[n].author, &books[n].stock, &books[n].price);
        n++;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (books[j].stock > books[j + 1].stock)
            {
                struct book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        fprintf(temp, "%d, %s, %s, %d, %d\n", books[i].id, books[i].title, books[i].author, books[i].stock, books[i].price);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    printf("\n\n\t\t\t\t\tThe book inventory was sorted successfully!\n");
    print_f();
    printf("\n\n\t\t\t\t\t    Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void sortid()
{
    system("cls");
    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i, j, n = 0;
    char line[256];
    struct book books[100];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &books[n].id, books[n].title, books[n].author, &books[n].stock, &books[n].price);
        n++;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (books[j].id > books[j + 1].id)
            {
                struct book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        fprintf(temp, "%d, %s, %s, %d, %d\n", books[i].id, books[i].title, books[i].author, books[i].stock, books[i].price);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    printf("\n\n\t\t\t\t\tThe book inventory was sorted successfully!\n");
    print_f();
    printf("\n\n\t\t\t\t\t    Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void sorttitle()
{
    system("cls");
    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i, j, n = 0;
    char line[256];
    struct book books[100];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &books[n].id, books[n].title, books[n].author, &books[n].stock, &books[n].price);
        n++;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(books[j].title, books[j + 1].title)>0)
            {
                struct book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        fprintf(temp, "%d, %s, %s, %d, %d\n", books[i].id, books[i].title, books[i].author, books[i].stock, books[i].price);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    printf("\n\n\t\t\t\t\tThe book inventory was sorted successfully!\n");
    print_f();
    printf("\n\n\t\t\t\t\t    Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void sortauthor()
{
    system("cls");
    FILE *fp, *temp;
    fp = fopen("inventory.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL || temp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int i, j, n = 0;
    char line[256];
    struct book books[100];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &books[n].id, books[n].title, books[n].author, &books[n].stock, &books[n].price);
        n++;
    }

    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (strcmp(books[j].author, books[j + 1].author)>0)
            {
                struct book temp = books[j];
                books[j] = books[j + 1];
                books[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < n; i++)
    {
        fprintf(temp, "%d, %s, %s, %d, %d\n", books[i].id, books[i].title, books[i].author, books[i].stock, books[i].price);
    }

    fclose(fp);
    fclose(temp);

    remove("inventory.txt");
    rename("temp.txt", "inventory.txt");

    printf("\n\n\t\t\t\t\tThe book inventory was sorted successfully!\n");
    print_f();
    printf("\n\n\t\t\t\t\t    Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}

void search()
{
    system("cls");
    printf("Search by: \n");
    printf("1. Book ID\n");
    printf("2. Book title\n");
    printf("3. Book author\n");
    switch (getch())
    {
    case '1':
        searchid();
        break;
    case '2':
        searchtitle();
        break;
    case '3':
        searchauthor();
        break;
    }

    switch(getch())
    {
    case 'm':
        menu();
        break;
    }
}
void searchid()
{
    system("cls");
    fflush(stdin);
    printf("\n\n\t\t\t\t\t\t\t Search by ID");
    printf("\n\nEnter the book ID: ");
    int id;
    scanf("%d", &id);

    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (b.id == id)
        {
            found = 1;
            printf("\nDetails of the book with the ID %d:\n\n", b.id);
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStock: %d\nPrice: %d\n\n", b.id, b.title, b.author, b.stock, b.price);
            break;
        }
    }
    fclose(fp);

    if (found == 0)
        printf("\n\n\t\t\t\t\t\t   Book with ID %d was not found!\n\n", id);

    printf("\t\t\t\t\t\tPress 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void searchtitle()
{
    system("cls");
    fflush(stdin);
    printf("\t\t\t\t\t\tSearch by book title");
    printf("\n\nEnter the book title: ");
    char title[100];
    fgets(title, sizeof(title), stdin);
    strtok(title, "\n");

    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (strcmp(title, b.title)==0)
        {
            found = 1;
            printf("\nDetails of the book with the title %s:\n\n", b.title);
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStock: %d\nPrice: %d\n\n", b.id, b.title, b.author, b.stock, b.price);
            break;
        }
    }
    fclose(fp);

    if (found == 0)
        printf("\n\n\t\t\t\t\t  Book with title %s was not found!\n\n", title);

    printf("\t\t\t\t\t  Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void searchauthor()
{
    system("cls");
    fflush(stdin);
    printf("\t\t\t\t\t\tSearch by book author");
    printf("\n\nEnter the book author: ");
    char author[100];
    fgets(author, sizeof(author), stdin);
    strtok(author, "\n");

    FILE *fp;
    fp = fopen("inventory.txt", "r");
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    int found = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp))
    {
        sscanf(line, "%d, %[^,], %[^,], %d, %d", &b.id, b.title, b.author, &b.stock, &b.price);
        if (strcmp(author, b.author)==0)
        {
            found ++;
            printf("\nDetails of the book by the author %s:\n\n", b.author);
            printf("ID: %d\nTitle: %s\nAuthor: %s\nStock: %d\nPrice: %d\n\n", b.id, b.title, b.author, b.stock, b.price);
        }
    }
    fclose(fp);

    if (found == 0)
        printf("\n\n\t\t\t\t\tBook with author %s was not found!\n\n", author);

    printf("\t\t\t\t\t  Press 'm' to go back to the menu");
    switch (getch())
    {
    case 'm':
        menu();
        break;
    }
}
void menu()
{
    system("cls");
    printf ("\n\t\t\t\t\t\t *End Of Story* Inventory ");
    printf("\n\n--------------------------------------------------------- MENU ---------------------------------------------------------\n\n");
    printf("1. Add a book\n");
    printf("2. Delete a book\n");
    printf("3. Update a book\n");
    printf("4. View the inventory\n");
    printf("5. Sort the inventory\n");
    printf("6. Search a book\n");
    printf("7. Exit \n\n");

    printf("Choose what you want to do: ");

    switch (getch())
    {
    case '1':
        add();
        break;
    case '2':
        del();
        break;
    case '3':
        update();
        break;
    case '4':
        show_inv();
        break;
    case '5':
        sort();
        break;
    case '6':
        search();
        break;
    case '7':
        system("taskkill /F /IM cb_console_runner.exe");
        break;
    default:
        printf("\n\n\t\t\t\t\t\tEnter a number between 1-7!");
        sleep(2);
        menu();
    }

}
int main()
{
    menu();
    return 0;
}
