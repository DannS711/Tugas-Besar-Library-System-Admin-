#include <stdio.h>
#include <string.h>
#include <windows.h>
////////////////////////////Books/////////////////////////////////
int BookID[100] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
char books[100][100] =
    {
        "To Kill a Mockingbird",
        "1984",
        "The Great Gatsby",
        "The Catcher in the Rye",
        "The Hobbit",
        "Pride and Prejudice",
        "Moby-Dick",
        "The Lord of the Rings",
        "Harry Potter and the Sorcerers Stone",
        "Crime and Punishment"}; // dummy data
//////////////////////////////////////////////////////////////////

// User //
int UserID[10];
char Username[10][100]; // Maksimal 10 pengguna, setiap username maks 99 karakter
char Password[10][100]; // Maksimal 10 pengguna, setiap password maks 99 karakter
int userBorrowMax = 3;
//////////

// User borrowed books //
int UserID;
int BookID;
char borrowedBookName[3][100];
/////////////////////////

int i;
int firstmenuselect, secondmenuselect;

void accList(int *userCount)
{
    for (int i = 0; i < 10; i++)
    {
        printf("[%d]\n", i);
        printf("  UserID : %d\n", UserID[i]);
        printf("  Username : %s\n", Username[i]);
        printf("  Password : %s\n\n", Password[i]);
    }
}

int signUpProcess(int *userCount)
{
    if (*userCount >= 10)
    {
        printf("Akun sudah mencapai batas!\n");
        return 0;
    }

    printf("Sign Up\n");

    printf("Enter Username: ");
    scanf("%99s", Username[*userCount]); // contoh input = qwerty (no space)

    printf("Enter Password: ");
    scanf("%99s", Password[*userCount]);

    UserID[*userCount] = *userCount + 1;
    (*userCount)++;

    printf("Signup berhasil! Akun tersimpan.\n\n");

    return 0;
}

int loginProcess(int totalUser)
{
    char inputUser[100], inputPass[100];
    int LoginUserID;

    if (totalUser == 0)
    {
        printf("Belum ada akun. Silakan Sign Up dulu.\n");
        return -1;
    }

    printf("=== Login ===\n");

    printf("Enter Username: ");
    scanf("%99s", inputUser); // contoh: test (no space)

    printf("Enter Password: ");
    scanf("%99s", inputPass); // contoh: 123 (no space)

    // cek availability akunnya
    for (int i = 0; i < totalUser; i++)
    {
        if (strcmp(inputUser, Username[i]) == 0 &&
            strcmp(inputPass, Password[i]) == 0)
        {
            printf("Login berhasil! Selamat datang %s\n", Username[i]);
            return i + 1; // return index of logged-in user sebagai id-nya
        }
    }

    printf("Username atau Password salah!\n");
    return -1;
}

int bookList(int *TBPtr)
{
    for (i = 0; i < *TBPtr; i++)
    {
        printf("%d. %s\n", BookID[i], books[i]);
    }
    return 0;
}

char searchBook()
{
    char bookName[100];
    printf("Enter book name: ");
    scanf(" %[^\n]", bookName);

    for (i = 0; i < 10; i++)
    {
        if (strstr(books[i], bookName) != NULL) // nyari character yang sesuai di string / you can say .include() in JS
        {
            printf("%d. %s\n", i + 1, books[i]);
        }
    }
}

void addBook(int *bookCount)
{
    getchar();
    printf("Add your book to library: ");
    // printf("%d", *bookCount); // output = 10
    fgets(books[*bookCount], sizeof(books[*bookCount]), stdin);

    books[*bookCount][strcspn(books[*bookCount], "\n")] = '\0'; // remove newline

    BookID[*bookCount] = *bookCount + 1;
    (*bookCount)++;

    printf("Book successfully added!");
}

void borrowBook(int *ID_Ptr, int *TB_Ptr)
{
    int pickBook;

    for (i = 0; i < *TB_Ptr; i++)
    {
        printf("%d. %s\n", BookID[i], books[i]); // cari bukunya
    }

    printf("Pick a book you want to borrow: ");
    scanf("%d", &pickBook);

    int found = 0;
    for (i = 0; i < *TB_Ptr; i++)
    {
        if (pickBook == BookID[i])
        {
            found = 1;
            printf("\nBorrow success!\n");
            printf("User %d borrowed: %s\n", *ID_Ptr, books[i]);
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");
}

void returnBook(int *ID_Ptr, int *TB_Ptr)
{
    for (i = 0; i < *TB_Ptr; i++)
    {
        printf("%d. %s\n", BookID[i], books[i]); // cari bukunya
    }

    getchar();   

    printf("Enter Book Name = ");
    fgets(books[*TB_Ptr], sizeof(books[*TB_Ptr]), stdin);
    books[*TB_Ptr][strcspn(books[*TB_Ptr], "\n")] = 0;

    printf("Your book has successfully returned to the system!\n\n");
}

int main()
{
    int totalUser = 0, totalBooks = 10;
    int firstmenuselect, secondmenuselect;

    while (1)
    {
        printf("\nPlease Login to your account\n");
        printf("1. Login\n");
        printf("2. Sign Up\n");
        printf("0. Exit\n");
        printf("Select menu number: ");
        scanf("%d", &firstmenuselect);

        if (firstmenuselect == 1)
        {
            // ==== LOGIN ====
            int loggedInUserID = loginProcess(totalUser);

            if (loggedInUserID != -1) // cek klo login berhasil
            {
                printf("\nWelcome, %s!\n", Username[loggedInUserID]);

                // ==== BOOK MENU LOOP ====
                while (1)
                {
                    printf("\n--- Book Menu ---\n");
                    printf("1. Book list\n");
                    printf("2. Add book\n");
                    printf("3. Search book\n");
                    printf("4. Borrow book\n");
                    printf("5. Return book\n");
                    printf("6. Logout\n");
                    printf("Select option: ");
                    scanf("%d", &secondmenuselect);

                    if (secondmenuselect == 1)
                        bookList(&totalBooks);
                    else if (secondmenuselect == 2)
                        addBook(&totalBooks);
                    else if (secondmenuselect == 3)
                        searchBook();
                    else if (secondmenuselect == 4)
                        borrowBook(&loggedInUserID, &totalBooks);
                    else if (secondmenuselect == 5)
                        returnBook(&loggedInUserID, &totalBooks);
                    else if (secondmenuselect == 6)
                    {
                        printf("Logging out...\n");
                        Sleep(2000);
                        break;
                    }
                    else
                        printf("Invalid option!\n");
                }
            }
        }
        else if (firstmenuselect == 2)
        {
            signUpProcess(&totalUser);
        }
        else if (firstmenuselect == 99)
        {
            accList(&totalUser);
        }
        else if (firstmenuselect == 0)
        {
            printf("Exiting...\n");
            Sleep(2000);
            break;
        }
        else
        {
            printf("Please enter a correct menu.\n");
        }
    }

    return 0;
}

// note: setelah exit terminal, data yang di input diterminal semuanya ke reset dan tidak tersimpan ke global array for some reason???????.