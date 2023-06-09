#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 255
#define ISBN_LEN 15
#define BOOK_TITLE 50
#define BOOK_AUTHOR 45
#define STU_NAME 45
#define ID_MAX 30
//Book  Structure:The  structure  to  hold  book  information  (ISBN  number,  title,  author,  publication  year, reserved status)
//Student Structure:The structure to hold student information (name, ID, borrowed books).

struct book{
    char* isbn;
    char* title;
    char* author;
    int publication_year;
    int is_reserved;
    struct book* nxtBook;
    char* stuid;
};

struct student{
    char *name;
    char *id;
    struct book* borrowedBooks;
    struct student* nxtStudent;
    int borrowed;
    int borrowed_count;
    char *bookisbn;
};



typedef struct book Book;
typedef struct student Student;

Book* fill_bookStruct(char *filename){
    Book* root = NULL;
    Book* currBook = NULL;
    

    char line[MAX_LINE_LEN];
    FILE *fp = fopen(filename,"r");

    fgets(line,MAX_LINE_LEN,fp); // skips the first line

    
    while(fgets(line,MAX_LINE_LEN,fp)){
        Book *newBook = (Book*)malloc(sizeof(Book));
        newBook->nxtBook = NULL;

        newBook->author = (char*)malloc(BOOK_AUTHOR * sizeof(char));
        newBook->isbn = (char*)malloc(ISBN_LEN * sizeof(char));
        newBook->title = (char*)malloc(BOOK_TITLE * sizeof(char));
        newBook->stuid = (char*)malloc(ID_MAX * sizeof(char));

        char tempibn[ISBN_LEN];
        char temptitle[BOOK_TITLE];
        char tempauthor[BOOK_AUTHOR];
        char tempstuid[ID_MAX];


        sscanf(line, "%[^,],%[^,],%[^,],%d,%d,%[^\n]", tempibn, temptitle, tempauthor, &(newBook->publication_year), &(newBook->is_reserved), tempstuid);
        strcpy(newBook->isbn, tempibn);
        strcpy(newBook->title, temptitle);
        strcpy(newBook->author, tempauthor);
        strcpy(newBook->stuid, tempstuid);


        if(root == NULL){
            root = newBook;
            currBook=root;
        }else{
            currBook->nxtBook = newBook;
            currBook=newBook;
        }
    }

return root;
//152907715X,American Psycho,Bret Easton Ellis,2022,0
}
//AHMET BAHA,200104004059,No

Student* fill_studentStruct(char *filename){
    Student* root = NULL;
    Student* currStudent = NULL;
    char line[MAX_LINE_LEN];
    FILE *fp = fopen(filename,"r");
    fgets(line,MAX_LINE_LEN,fp); // append over first line
    while(fgets(line,MAX_LINE_LEN,fp)){
        Student *newStudent = (Student*)malloc(sizeof(Student));
        newStudent->name = (char*)malloc(STU_NAME * sizeof(char));
        newStudent->nxtStudent = (Student*)malloc(sizeof(Student));
        newStudent->bookisbn = (char*)malloc(ISBN_LEN * sizeof(char));
        newStudent->id = (char*)malloc(ID_MAX *sizeof(char));
        char tempname[STU_NAME];
        char tempId[ID_MAX];
        char tempbookisbn[ISBN_LEN];
        
        sscanf(line,"%[^,],%d,%d,%[^\n]\n",tempname,tempId,&newStudent->borrowed,tempbookisbn);
        strcpy(newStudent->name,tempname);
        strcpy(newStudent->bookisbn,tempbookisbn);
        strcpy(newStudent->id,tempId);
        if(newStudent->borrowed){
            newStudent->borrowedBooks = (Book*)malloc(sizeof(Book));
        }
        else{
            newStudent->borrowedBooks = NULL;
        }

        
        if(root==NULL){
            root = newStudent;
            currStudent = root;
        }else{
            currStudent->nxtStudent = newStudent;
            currStudent=newStudent;
        }

    }


    return root;

}


int printTotxt(int method,Book* newBook){
    if(method){
        FILE *fp = fopen("LibraryBookInfo.txt","a");
        //ISBN,Title,Author,PublicationYear,ReservedStatus
        fprintf(fp,"%s,%s,%s,%d,%d,%s\n",newBook->isbn,newBook->title,newBook->author,newBook->publication_year,newBook->is_reserved,newBook->stuid);

        fclose(fp);
        return 1;
    }
    else{
        FILE *fpRead = fopen("LibraryBookInfo.txt","r");
        FILE *fpWrite = fopen("libtemp.txt","w");

        char line[MAX_LINE_LEN];
        fgets(line,MAX_LINE_LEN,fpRead);//first line
        fputs(line,fpWrite);
        fprintf(fpWrite,"%s,%s,%s,%d,%d,%s\n",newBook->isbn,newBook->title,newBook->author,newBook->publication_year,newBook->is_reserved,newBook->stuid);
        while (fgets(line,MAX_LINE_LEN,fpRead))
        {
            fputs(line,fpWrite);
        }
        

        
        
        remove("LibraryBookInfo.txt");
        rename("libtemp.txt", "LibraryBookInfo.txt");
      
        fclose(fpRead);
        fclose(fpWrite);
        return 1;
        

    }

    return 0;
   
}

int addBook(char* isbn,char*title,char* author,int pYear,int method,Book *rootBook){
    Book* currBook = rootBook;
    Book* newBook = (Book*)malloc(sizeof(Book));
    newBook->isbn = (char*)malloc((strlen(isbn)+1)*sizeof(char));
    newBook->title = (char*)malloc((strlen(title)+1)*sizeof(char));
    newBook->author = (char*)malloc((strlen(author)+1)*sizeof(author));
    newBook->is_reserved = 0;
    newBook->stuid = (char*)malloc(ID_MAX*sizeof(char));
    strcpy(newBook->isbn,isbn);
    strcpy(newBook->title,title);
    strcpy(newBook->author,author);
    strcpy(newBook->stuid,"0");
    newBook->publication_year = pYear;
    newBook->nxtBook = NULL;
    if(method == 1){
        //method 1 = > LAST IN FIRST OUT
        while(currBook->nxtBook != NULL){
            currBook = currBook->nxtBook;
        }
        currBook->nxtBook = newBook;
        printTotxt(1,newBook);

        
    }
    else{
        newBook->nxtBook = rootBook;
        rootBook = newBook;
        printTotxt(0,newBook);
        //METHOD 2 *> fırst in fırst out

    }

    

    
}
//BITTI
//ISBN,Title,Author,PublicationYear,ReservedStatus,StuId
void updateBook(char *isbn,char* feature,char *value,Book* rootBook){
    Book* currBook = rootBook;
    int bookFound = 0;
    FILE *updBooklib = fopen("updatebooklib.txt","w");
    FILE *readfromLib = fopen("LibraryBookInfo.txt","r");
    
    char line[MAX_LINE_LEN];
    fgets(line,MAX_LINE_LEN,readfromLib);
    fputs(line,updBooklib);
    int tempPubYear;
    //fclose(updBooklib);    
    while (fgets(line, MAX_LINE_LEN, readfromLib) != NULL) {
        if (strcmp(isbn, currBook->isbn) == 0) {
            puts("Book Found!");
            if (strcmp(feature, "title") == 0) {
                strcpy(currBook->title, value);
            } else if (strcmp(feature, "author") == 0) {
                strcpy(currBook->author, value);
            } else if (strcmp(feature, "publicationyear") == 0) {
                sscanf(value, "%d", &(currBook->publication_year));
            }

            fprintf(updBooklib, "%s,%s,%s,%d,%d,%s\n", currBook->isbn, currBook->title, currBook->author,
                    currBook->publication_year, currBook->is_reserved, currBook->stuid);

            bookFound = 1;
        } else {
            fputs(line, updBooklib);
        }

        currBook = currBook->nxtBook;
    }

    fclose(updBooklib);
    fclose(readfromLib);

    remove("LibraryBookInfo.txt");
    rename("updatebooklib.txt","LibraryBookInfo.txt");
    
}

void student_borrowedBooks(Student *topStudent,char* stuid){
    Student *currentStudent = topStudent;
    int matchStudentFound = 0;
    while(currentStudent->nxtStudent != NULL){
        if(strcmp(stuid,currentStudent->id)==0){
            matchStudentFound = 1;
            break;

        }
        else{
            matchStudentFound = 0;
        }
        currentStudent= currentStudent->nxtStudent;
    }

    if(matchStudentFound){
        if(currentStudent->borrowedBooks != NULL){
            printf("\nStudent= %s's borrowed book is = %s.",currentStudent->id,currentStudent->borrowedBooks->title);
            return;
        }
        else{
            puts("This user doesnt have any borrowed books yet.");
            return;
        }
    }else{
        puts("Couldn't find an student with matching id!");
        return;
    }

}

void deleteBookFromTxt(char* isbn){
//    sscanf(line,"%[^,],%[^,],%[^,],%d,%d",tempibn,temptitle,tempauthor,&currBook->publication_year,&currBook->is_reserved);
    
    FILE *fpRead = fopen("LibraryBookInfo.txt","r");
    FILE *fpWrite = fopen("librartempt.txt","w");
    char isbnFromFile[ISBN_LEN];
    char line[MAX_LINE_LEN];
    while ((fscanf(fpRead,"%[^,],%*[^\n]",isbnFromFile))==0)
    {
        if(strcmp(isbn,isbnFromFile)==0){
            ;
        }
        else{
            fgets(line,MAX_LINE_LEN,fpRead);
            fputs(line,fpWrite);
        }
    }
    
    fclose(fpWrite);
    fclose(fpRead);
}
void deleteBook(char *isbn,Book* bookroot){
    Book* currentBook = bookroot;
    Book* prevBook = NULL;

    FILE *updtBooksLib = fopen("updated.txt","w");
    FILE *readFromLib = fopen("LibraryBookInfo.txt","r");
    puts(currentBook->isbn);
    int bookFound = 0;
    int lineCount =0;
    //Book* nextBook = NULL;
    char line[MAX_LINE_LEN];
    fgets(line,MAX_LINE_LEN,readFromLib);
    fputs(line,updtBooksLib);
    while(currentBook != NULL){
        lineCount++;
        if(strcmp(currentBook->isbn,isbn) == 0){
            bookFound=1;
            puts("Matching isbn has found!");
            break;
        }else{
            bookFound = 0;
        }

        prevBook = currentBook;
        currentBook = currentBook->nxtBook;
    }
    int count = 0;
    while(fgets(line,MAX_LINE_LEN,readFromLib)){
        count++;
        if(count==lineCount){
            continue;
        }
        else{
            fputs(line,updtBooksLib);
        }
    }
    fclose(updtBooksLib);
    fclose(readFromLib);
    remove("LibraryBookInfo.txt");
    rename("updated.txt","LibraryBookInfo.txt");

    if(bookFound){
    
        puts("Matching isbn has found!");

        if(currentBook->nxtBook == NULL){
            free(currentBook->author);
            free(currentBook->title);
            free(currentBook->isbn);
            free(currentBook->nxtBook);
            free(currentBook);


        }else{
            prevBook->nxtBook = currentBook->nxtBook;
            free(currentBook->author);
            free(currentBook->title);
            free(currentBook->isbn);
            free(currentBook->nxtBook);
            free(currentBook);
        }
    }else{
        puts("Couldnt find the book with the given isbn.");
    }
}

void filterAndSortBooks(int filterChoice,char* filter,int sortChoice,Book* bookroot){
    /*void filterAndSortBooks(int filterChoice, char* filter, int sortChoice)•filterChoice: 
    The user's choice for filtering the books. 0 for filtering by author, 1 for filtering by publication year.
    •filter: The filter criteria in string format.•sortChoice:
     The user's choice for sorting the books. 0 for sorting by title, 1 for sorting by author, 2 for sorting by publication year.*/

    Book* currentbook = bookroot;
    int foundBooks = 0;

    if(filterChoice==0){
        //filter by author
        while(currentbook!=NULL){
            if(strcmp(currentbook->author,filter) == 0){
                foundBooks++;
            }
            currentbook = currentbook->nxtBook;
        }

        currentbook = bookroot;
        printf("Found %d books.\n",foundBooks);
        //6
        //ISBN,Title,Author,PublicationYear,ReservedStatus,StuId
    if(foundBooks>0){   
        Book* filteredBooks[foundBooks];
        int indexCount = 0;
        while(currentbook!=NULL){
            if(strcmp(currentbook->author,filter) == 0){
                filteredBooks[indexCount++] = currentbook;
            }
            currentbook = currentbook->nxtBook;
        }
        
        Book* tempBook = NULL;
        if(sortChoice==0){

            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(strcmp(filteredBooks[j]->title,filteredBooks[j+1]->title)<0){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                }
            }
        }
        else if(sortChoice==1){
            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(strcmp(filteredBooks[j]->author,filteredBooks[j+1]->author)<0){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                }
            }

        }else if(sortChoice==2){
            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(filteredBooks[j]<filteredBooks[j+1]){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                }
            }
        }
    
        //ISBN,Title,Author,PublicationYear,ReservedStatus,StuId
    
    for(int i=0;i<foundBooks;i++){
        printf("%s,%s,%s,%d,%d,%s\n",filteredBooks[i]->isbn,filteredBooks[i]->title,filteredBooks[i]->author,filteredBooks[i]->publication_year,filteredBooks[i]->is_reserved,filteredBooks[i]->stuid);
    }


    }else{
        puts("Couldnt find a book that satisfies the filter requirements.");
    }

    }else if(filterChoice == 1){
            //filter by publication year
            int publicYear;
            sscanf(filter,"%d",&publicYear);
           
            foundBooks=0;
            currentbook = bookroot;
            while(currentbook!=NULL){
                if(currentbook->publication_year==publicYear){
                    foundBooks++;
                }
                
                currentbook = currentbook->nxtBook;
            }
            if(foundBooks>0){
            Book* tempBook = NULL;
            Book* filteredBooks[foundBooks];
            currentbook=bookroot;
            int indexCount = 0;
            while(currentbook!=NULL){
                if(currentbook->publication_year==publicYear){
                    filteredBooks[indexCount++] = currentbook;
                }

                currentbook=currentbook->nxtBook;
            }

            if(sortChoice==0){

            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(strcmp(filteredBooks[j]->title,filteredBooks[j+1]->title)<0){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                }
            }
            }
            else if(sortChoice==1){
            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(strcmp(filteredBooks[j]->author,filteredBooks[j+1]->author)<0){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                }
                }

            }else if(sortChoice==2){
            for(int i=0;i<foundBooks;i++){
            for(int j=0;j<foundBooks-i-1;j++){
                if(filteredBooks[j]<filteredBooks[j+1]){
                    tempBook = filteredBooks[j];
                    filteredBooks[j] = filteredBooks[j+1];
                    filteredBooks[j+1] = tempBook;
                    }
                 }
                }
            }

            for(int i=0;i<foundBooks;i++){
                printf("%s,%s,%s,%d,%d,%s\n",filteredBooks[i]->isbn,filteredBooks[i]->title,filteredBooks[i]->author,filteredBooks[i]->publication_year,filteredBooks[i]->is_reserved,filteredBooks[i]->stuid);

            }
            }
            else{
                puts("Couldnt find a book that satisfies the filter requirements.");
            }

    }
}

void sortByISBN(Book** head) {
    if (*head == NULL || (*head)->nxtBook == NULL) {
        // Empty list or only one node, no need for sorting
        return;
    }

    Book* prev = NULL;
    Book* current = *head;
    Book* next = current->nxtBook;

    while (next != NULL) {
        if (strcmp(current->isbn, next->isbn) > 0) {
            if (prev == NULL) {
                *head = next;
            } else {
                prev->nxtBook = next;
            }

            current->nxtBook = next->nxtBook;
            next->nxtBook = current;

            prev = next;
            next = current->nxtBook;
        } else {
            prev = current;
            current = next;
            next = next->nxtBook;
        }
    }
}


void reverseBookList(Book** topBook){
    Book* prev = NULL;
    Book* current = *topBook;
    Book* next = NULL;

    while (current != NULL) {
        next = current->nxtBook;
        current->nxtBook = prev;
        prev = current;
        current = next;
    }

    *topBook = prev;

    sortByISBN(topBook);
}

void linklistedwrite(Book* root){
    Book* currBook = root;

    while(currBook != NULL){
        puts(currBook->title);
        currBook = currBook->nxtBook;
    }
}

void searchBook(int searchChoice,char* searchValue,Book* root){
    //0 for isbn 1 for by author 2 by title
//ISBN,Title,Author,PublicationYear,ReservedStatus,StuId
    int bookFound = 0;
    Book* currBook = root;
    if(searchChoice==0){
        while(currBook!=NULL){
            if(strcmp(searchValue,currBook->isbn)){
                printf("%s,%s,%s,%d,%d,%s\n",currBook->isbn,currBook->title,currBook->author,currBook->publication_year,currBook->is_reserved,currBook->stuid);
                bookFound = 1;
                break;
            }
            currBook = currBook->nxtBook;
        }


    }else if(searchChoice==1){
        while(currBook!=NULL){
            if(strcmp(searchValue,currBook->author)){
                printf("%s,%s,%s,%d,%d,%s\n",currBook->isbn,currBook->title,currBook->author,currBook->publication_year,currBook->is_reserved,currBook->stuid);
                bookFound = 1;
                break;
            }
            currBook = currBook->nxtBook;
        }


    }else if(searchChoice==2){
        while(currBook!=NULL){
            if(strcmp(searchValue,currBook->title)){
                printf("%s,%s,%s,%d,%d,%s\n",currBook->isbn,currBook->title,currBook->author,currBook->publication_year,currBook->is_reserved,currBook->stuid);
                bookFound = 1;
                break;
            }
            currBook = currBook->nxtBook;
        }


    }
}

void clearLeadingNewline(char* str) {
    size_t len = strlen(str);
    if (len > 0 && str[0] == '\n') {
        memmove(str, str + 1, len);  // Shift characters one position to the left
    }
}

void bookReservedStatus(char *bookisbn, char* stuid){
    FILE *readData = fopen("LibraryBookInfo.txt","r");
    FILE *writeData = fopen("bookTemp.txt","w");
    char line[MAX_LINE_LEN];
    
    int linecount=0;
    while(fgets(line,MAX_LINE_LEN,readData)){
        linecount++;
    }
    linecount--;
    rewind(readData);
    char tempisbn[ISBN_LEN];
    char temptitle[BOOK_TITLE];
    char tempauthor[BOOK_AUTHOR];
    char temppubYear[10];
    char tempReserved[2];
    int reservedStat;
    char tempStuid[ID_MAX];
    int indexC = 0 ;
    fgets(line,MAX_LINE_LEN,readData);
    fputs(line,writeData);
    while((fscanf(readData,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]%*c",tempisbn,temptitle,tempauthor,temppubYear,tempReserved,tempStuid))>0){
        indexC++;
        //clearLeadingNewline(tempisbn);
        if(strcmp(bookisbn,tempisbn)==0){
            puts("Book found!");
            reservedStat = 1;
            if(indexC == linecount){
            fprintf(writeData,"%s,%s,%s,%s,%s,%s",tempisbn,temptitle,tempauthor,temppubYear,"1",stuid);

            }else{
            fprintf(writeData,"%s,%s,%s,%s,%s,%s\n",tempisbn,temptitle,tempauthor,temppubYear,"1",stuid);

            }
        }else{
            reservedStat = 0;
            if(indexC==linecount){
            fprintf(writeData,"%s,%s,%s,%s,%s,%s",tempisbn,temptitle,tempauthor,temppubYear,tempReserved,tempStuid);
            }else{
            fprintf(writeData,"%s,%s,%s,%s,%s,%s\n",tempisbn,temptitle,tempauthor,temppubYear,tempReserved,tempStuid);
            }

        }
    }
    fclose(writeData);
    fclose(readData);

    remove("LibraryBookInfo.txt");
    rename("bookTemp.txt","LibraryBookInfo.txt");
}
void changeStudentReservedData(char* bookisbn,char* stuid){
    FILE* readFromStuinfo = fopen("StudentInfo.txt","r");
    FILE* writeData = fopen("stuTemp.txt","w");
    char tempname[STU_NAME];
    char stuDentid[ID_MAX];
    char tempid[ID_MAX];
    
    int haveBook;
    char bookiSbn[ISBN_LEN];
    char line[MAX_LINE_LEN];
    fgets(line,MAX_LINE_LEN,readFromStuinfo);
    fputs(line,writeData);

    while((fscanf(readFromStuinfo,"%[^,],%[^,],%d,%[^\n]",tempname,tempid,&haveBook,bookiSbn))>0){
        //printf("\ntempid = %s",tempid);
        if(strcmp(stuid,tempid)==0){
            haveBook = 1;
            fprintf(writeData,"%s,%s,%d,%s",tempname,tempid,haveBook,bookisbn);
        }
        else{
            fprintf(writeData,"%s,%s,%d,%s",tempname,tempid,haveBook,bookiSbn);
        }
    }
    fclose(writeData);
    fclose(readFromStuinfo);

    remove("StudentInfo.txt");
    rename("stuTemp.txt","StudentInfo.txt");
}

void borrowBook(char *isbn,Book *topbook,Student *topStudent){
    char studentid[ID_MAX];
    int isbookfound = 0;
    int isstudentFound = 0;
    printf("\nGive the students id: ");
    scanf("%s",studentid);
    Book* currBook = topbook;
    Student* currStudent = topStudent;

    while(currBook!=NULL){
        if(strcmp(currBook->isbn,isbn)==0){
            isbookfound = 1;
            break;
        }else{
            isbookfound = 0;
        }
        currBook= currBook->nxtBook;
    }
    if(isbookfound){
        puts("Book has found!");
        while(currStudent!=NULL){
            if(strcmp(currStudent->id,studentid)){
                isstudentFound = 1;
                break;
            }else{
                isstudentFound=0;
            }
            currStudent=currStudent->nxtStudent;
        }
            if(isstudentFound){
                puts("Student has found!");
                puts(currStudent->name);
                printf("Student id = %s\n",studentid);
                if(currBook->is_reserved){
                    puts("This book is reserved!");
                }else{
                    currBook->is_reserved= 1;
                    currStudent->borrowed = 1;
                    strcpy(currStudent->bookisbn,currBook->isbn);
                    currStudent->borrowedBooks = currBook;
                    changeStudentReservedData(currBook->isbn,studentid);
                    bookReservedStatus(currBook->isbn,studentid);
                    //buradakadlım
                }
            }else{
                puts("Student doesnt exists!");
            }
        }else{
        puts("Book doesnt exists!");
        return;
            }
};

void returnBook(char *isbn,Book *topbook,Student* topstudent){
    FILE *readData = fopen("LibraryBookInfo.txt","r");
    FILE *writeData = fopen("TempLibt.txt","w");
    char tempisbn[ISBN_LEN];
    char temptitle[BOOK_TITLE];
    char tempauthor[BOOK_AUTHOR];
    char temppubye[15];
    int tempreserved;
    char tempstuid[ID_MAX];

    Book* currBook = topbook;
    while(currBook!=NULL){
        if(strcmp(currBook->isbn,isbn)==0){
            if(currBook->is_reserved){
                currBook->is_reserved=0;
                break;
            }else{
                puts("This book is not reserved to anybody!");
                return;
            }
            

        }
        currBook = currBook->nxtBook;
    }

    Student* currStudent = topstudent;
    while(currStudent!=NULL){
        if(strcpy(currStudent->borrowedBooks->isbn,currBook->isbn)==0){
            currStudent->borrowedBooks = NULL;
            strcpy(currBook->stuid,"0");
            
        }
        currStudent = currStudent->nxtStudent;
    }
    char line[MAX_LINE_LEN];
    fgets(line,MAX_LINE_LEN,readData);
    fputs(line,writeData);
    while((fscanf(readData,"%[^,],%[^,],%[^,],%[^,],%d,%[^\n]%*c",tempisbn,temptitle,tempauthor,temppubye,&tempreserved,tempstuid))>0){
        if(strcmp(tempisbn,isbn)==0){
            fprintf(writeData,"%s,%s,%s,%s,%d,%s",tempisbn,temptitle,tempauthor,temppubye,0,"0");
        }
        else{
            fprintf(writeData,"%s,%s,%s,%s,%d,%s",tempisbn,temptitle,tempauthor,temppubye,tempreserved,tempstuid);

        }
    }

    fclose(readData);
    fclose(writeData);
    remove("LibraryBookInfo.txt");
    rename("TempLibt.txt","LibraryBookInfo.txt");

    readData = fopen("StudentInfo.txt","r");
    writeData = fopen("StuTemp.txt","w");

    char tempstuName[STU_NAME];
    char tempSid[ID_MAX];
    int temphavebook;
    char tempbookIsbn[ISBN_LEN];
    fgets(line,MAX_LINE_LEN,readData);
    fputs(line,writeData);
    while((fscanf(readData,"%[^,],%[^,],%d,%[^\n]%*c",tempstuName,tempSid,&temphavebook,tempbookIsbn))>0){
        if(strcpy(tempbookIsbn,isbn)==0){
            fprintf(writeData,"%s,%s,%d,%s\n",tempstuName,tempSid,temphavebook,"0");
        }else{
            fprintf(writeData,"%s,%s,%d,%s\n",tempstuName,tempSid,temphavebook,tempbookIsbn);
        }
    }




};

void main(){
    Book* topBook =  fill_bookStruct("LibraryBookInfo.txt");
    Student* topStudent = fill_studentStruct("StudentInfo.txt");
    puts(topStudent->name);

    int menuChoice = 0;
    int errorFlag = 0;
    puts("\t***MENU***");
    while(menuChoice != 9){
    do
    {
        if(errorFlag){
            puts("Give an valid input 1-8 =>");
        }
        else{
            puts("->1)Show a students borrowed books.\n->2)Add Book.\n->3)Delete a Book\n->4)Update a Book.\n->5)Filter And Sort Books\n->6)Reverse Book List\n->7)Search Books\n->8)Borrow and Return Books.\n->9)Exit");
        }
        scanf("%d",&menuChoice);
        if(menuChoice != 1 && menuChoice != 2 && menuChoice != 3 && menuChoice != 4 && menuChoice != 5 && menuChoice != 6 && menuChoice != 7 && menuChoice != 8 && menuChoice != 9){
            errorFlag = 1;
        }else{
            errorFlag = 0;
        }
    } while (errorFlag);
    while(getchar() != '\n');
    char studentid[ID_MAX];
    char tempisbn[ISBN_LEN];
    char temptitle[BOOK_TITLE];
    char tempauthor[BOOK_AUTHOR];
    int publicYear;
    int method;
    char featureName[25];
    char newfeaturevalue[25];

    int filterChoice;
    char filter[35];
    int sortChoice;
    int searchChoice;
    char searchValue[55];
    int borroworreturn;

    switch (menuChoice)
    {
    case 1:
        /* code */
        //show students borrowed books
        printf("Give an student id: ");
        scanf("%s",studentid);
        student_borrowedBooks(topStudent,studentid);
        break;
    //void addBook(char* isbn, char* title, char* author, int publicationYear, int method)
    case 2:
        printf("\nGive the isbn of the book you wanna add: ");
        fgets(tempisbn,ISBN_LEN,stdin);
        tempisbn[strcspn(tempisbn, "\n")] = '\0';
        printf("\nGive the title of the book you wanna add: ");
        fgets(temptitle,BOOK_TITLE,stdin);
        temptitle[strcspn(temptitle, "\n")] = '\0';
        printf("\nGive the author's name of the book you wanna add: ");
        fgets(tempauthor,BOOK_AUTHOR,stdin);
        tempauthor[strcspn(tempauthor, "\n")] = '\0';
        printf("\nGive the publish year of the book: ");
        scanf("%d",&publicYear);
        printf("\nGive the adding method LIFO(1)/FIFO(2): ");
        scanf("%d",&method);
        /*
        do
        {
            printf("\nGive the adding method LIFO(1)/FIFO(2): ");
            scanf("%d",method);
        } while (method != 1 && method != 2);
        */
        addBook(tempisbn,temptitle,tempauthor,publicYear,method,topBook);


        break;
    case 3:
        
        printf("\nPlease give the isbn number of the book to be deleted: ");
        scanf("%s",tempisbn);
        deleteBook(tempisbn,topBook);
        break;
    case 4:
    //ISBN,Title,Author,PublicationYear,ReservedStatus,StuId
    //void updateBook(char *isbn,char* feature,char *value,Book* rootBook)
        printf("\nPlease give the isbn number of the book you wanna update: ");
        scanf("%s",tempisbn);
        printf("\nPlease give the feature's name you wanna update case sensetive!(title,author,publicationyear): ");
        scanf("%s",featureName);
        printf("\nPlease give the %s features new value: ",featureName);
        scanf("%s",newfeaturevalue);
        updateBook(tempisbn,featureName,newfeaturevalue,topBook);
        //title author publicationyear

        break;
    case 5:
    /*void filterAndSortBooks(int filterChoice, char* filter, int sortChoice)•filterChoice: 
    The user's choice for filtering the books. 0 for filtering by author, 1 for filtering by publication year.
    •filter: The filter criteria in string format.•sortChoice:
     The user's choice for sorting the books. 0 for sorting by title, 1 for sorting by author, 2 for sorting by publication year.*/
        puts("Give your filter choice(0-filter by author,1-filter by publication year): ");
        scanf("%d",&filterChoice);
        puts("Give your filter criteria: ");
        scanf("%s",filter);
        puts("Give your sorting choice(0-sort by title,1-sort by author,2-sort by publicationyear): ");
        scanf("%d",&sortChoice);
        filterAndSortBooks(filterChoice,filter,sortChoice,topBook);
        break;
    case 6:
        puts("Reversed the linked list.");
        reverseBookList(&topBook);
        linklistedwrite(topBook);

        break;
    case 7:
        //void searchBook(int searchChoice,char* searchValue,Book* root){
        printf("Give the search choice(0-for isbn number, 1-for author, 2- for title): ");
        scanf("%d",&searchChoice);
        printf("\nGive the search value: ");
        scanf("%s",searchValue);
        searchBook(searchChoice,searchValue,topBook);
        break;
    case 8:
        printf("Borrow or return a book,(1-for borrow, 2-for return): ");
        scanf("%d",&borroworreturn);
        switch (borroworreturn)
        {
        case 1:
            printf("\nGive the isbn of book you wanna borrow: ");
            scanf("%s",tempisbn);
            borrowBook(tempisbn,topBook,topStudent);
            break;
        case 2:
        /*void returnBook(char* isbn)*/
            printf("\nGive the isbn of the book you wanna return: ");
            scanf("%s",tempisbn);
            returnBook(tempisbn,topBook,topStudent);

            break;
        default:
            break;
        }
        break;
    default:
        break;
    }


    }
    
}