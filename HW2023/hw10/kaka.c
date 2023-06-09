while (fgets(line, MAX_LINE_LEN, fp)) {
        currBook = (Book*)malloc(sizeof(Book));
        currBook->nxtBook = NULL;
        currBook->author = NULL;
        currBook->isbn = NULL;
        currBook->title = NULL;

        char tempibn[ISBN_LEN];
        char temptitle[BOOK_TITLE];
        char tempauthor[BOOK_AUTHOR];

        sscanf(line, "%[^,],%[^,],%[^,],%d,%d", tempibn, temptitle, tempauthor, &currBook->publication_year, &currBook->is_reserved);

        currBook->isbn = (char*)malloc((strlen(tempibn) + 1) * sizeof(char));
        currBook->title = (char*)malloc((strlen(temptitle) + 1) * sizeof(char));
        currBook->author = (char*)malloc((strlen(tempauthor) + 1) * sizeof(char));

        strcpy(currBook->isbn, tempibn);
        strcpy(currBook->title, temptitle);
        strcpy(currBook->author, tempauthor);

        if (root == NULL) {
            root = currBook;
        } else {
            Book* tempBook = root;
            while (tempBook->nxtBook != NULL) {
                tempBook = tempBook->nxtBook;
            }
            tempBook->nxtBook = currBook;
        }
    }