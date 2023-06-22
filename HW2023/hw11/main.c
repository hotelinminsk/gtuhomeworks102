#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>


#define MAX_TXT_NAME 20
#define MAX_NAME 30
#define MAX_TREE_LEN 50
int familyTreeCounter = 0;


struct node{
    char *name;
    int age;
    struct node* Mother;
    struct  node* Father;
};


struct tree{
    char *treename;
    struct node** familyMembers;
    int nodecount;
};

typedef struct node Person;
typedef struct tree Tree;

int menu(){
    int choiceReturn;
    int errorFlag = 0;
    do
    {
        if(errorFlag){
            puts("You gave an invalid input please give 1,2,3 or 4: ");
        } 
        else{
            puts("*****************");
            puts("Family Tree System Menu:");
            puts("1-Add Family Tree\n2-Remove Family Tree\n3-Load Family Tree\n4-Exit");
        }
        scanf("%d",&choiceReturn);

        if(choiceReturn!=1 && choiceReturn != 2 && choiceReturn!= 3 && choiceReturn!=4){
            errorFlag = 1;
        }else{
            errorFlag = 0;
        }   
    
    } while (errorFlag);
    
return choiceReturn;
}

int is_m_inOtherFamily(Tree** allTrees,Person* newPerson,char* mothername){
    int found = 0;
    for(int i=0;i<familyTreeCounter;i++){
        for(int j=0;j<allTrees[i]->nodecount;j++){
            if(strcmp(allTrees[i]->familyMembers[j]->name,mothername)==0){
                newPerson->Mother = allTrees[i]->familyMembers[j];
                found = 1;
                break;
            }
        }
    }
    return found;
}

int is_f_inOtherFamily(Tree** allTrees,Person* newPerson, char* fathername){
    int found = 0;
    for(int i=0;i<familyTreeCounter;i++){
        for(int j=0;j<allTrees[i]->nodecount; j++){
            if(strcmp(allTrees[i]->familyMembers[j]->name,fathername)==0){
                newPerson->Father = allTrees[i]->familyMembers[j];
                found= 1;
                break;
            }
        }
    }
    return found;
}

Tree *addFamilyTree(Tree** allTrees){
    Person *rootFather = (Person*)malloc(sizeof(Person));
    Person *rootMother = (Person*)malloc(sizeof(Person));
    Person **treePersons = (Person**)malloc(MAX_TREE_LEN*sizeof(Person*));
    Person *lastPerson = NULL;
    int treeCount = 0;
    int menuChoice = 0;
    int errorFlag = 0;
    int isFirstNode = 1;
    char txtName[MAX_TXT_NAME];
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    newTree->nodecount = 0;
    newTree->treename = (char*)malloc(MAX_TXT_NAME * sizeof(char));
    sprintf(txtName,"familytree%d.txt",familyTreeCounter+1);
    puts(txtName);
    strcpy(newTree->treename,txtName);
    newTree->familyMembers = (Person**)malloc(MAX_TREE_LEN*sizeof(Person*));

    do
    {
        do
        {
            if(errorFlag){
                puts("Invalid input please give 1,2 or 3");
            }else{
                puts("1-Add Node\n2-Save Family Tree\n3-Exit");
            }
            scanf("%d",&menuChoice);
            if(menuChoice != 1 && menuChoice != 2 && menuChoice != 3){
                errorFlag = 1;
            }
            else{
                errorFlag = 0;
            }
        } while (errorFlag);
        

        printf("Menu choice = %d\n",menuChoice);
        if(menuChoice==1){
             if(isFirstNode==1){
                isFirstNode=0;
                puts("|This is the first node of this family tree.Please give Mother and Father names|");

                rootFather->name = (char*)malloc(MAX_NAME*sizeof(char));
                rootFather->Father = NULL;
                rootFather->Mother = NULL;
                rootMother->name = (char*)malloc(MAX_NAME*sizeof(char));
                rootMother->Father = NULL;
                rootMother->Mother = NULL;

                puts("Please give the rootFather's name");
                scanf("%s",rootFather->name);
                puts("Please give the rootFather's age");
                scanf("%d",&rootFather->age);
                puts("Please give the rootFMother's name");
                scanf("%s",rootMother->name);
                puts("Please give the rootFMother's age");
                scanf("%d",&rootMother->age);


                Person *newPerson = (Person*)malloc(sizeof(Person));
                newPerson->name = (char*)malloc(MAX_NAME*sizeof(char));

                puts("Enter the name of the person");
                scanf("%s",newPerson->name);
                puts("Enter the age of the person");
                scanf("%d",&newPerson->age);
                newPerson->Father = rootFather;
                newPerson->Mother = rootMother;
                newTree->familyMembers[treeCount++] = rootFather;
                newTree->familyMembers[treeCount++] = rootMother;
                newTree->familyMembers[treeCount++] = newPerson;
                newTree->nodecount = newTree->nodecount+3;
            }
            else if(isFirstNode==0){
                int is_motherExists = 0;
                int is_fatherExists = 0;
                int searchVal = 0;
                char motherName[MAX_NAME];
                char fatherName[MAX_NAME];
                Person *newPerson = (Person*)malloc(sizeof(Person));
                newPerson->name = (char*)malloc(MAX_NAME*sizeof(char));
                puts("Enter the name of the person");
                scanf("%s",newPerson->name);
                puts("Enter the age of the person");
                scanf("%d",&newPerson->age);
                while (getchar() != '\n');

                do
                {
                    puts("Enter the name of the mother");
                    scanf("%s",motherName);
                    for(int i=0;i<treeCount;i++){
                        if(strcmp(motherName,newTree->familyMembers[i]->name)==0){
                            puts("Mother has found on the family tree!");
                            newPerson->Mother = newTree->familyMembers[i];
                            is_motherExists= 1;
                            break;
                        }
                    }
                    if(is_motherExists==0 && allTrees != NULL){
                        puts("This person doesn't exists on the same tree,wanna look other trees?(1-Yes 2-No): ");
                        scanf("%d",&searchVal);
                        if(searchVal==1){
                            int motherFound = 0; 
                            motherFound = is_m_inOtherFamily(allTrees,newPerson,motherName);
                            if(motherFound){
                                puts("Mother has found in other family tree.");

                                is_motherExists = 1;
                            }else{
                                is_motherExists = 0;
                                puts("Mother has not found in any other family tree.");
                            }
                        }else if(searchVal==2){
                            is_motherExists = 0;
                            puts("Give an mother name in this family tree!");
                        }
                    }
                    else if(is_motherExists == 0 && allTrees == NULL){
                        puts("This person doesn't exists in any tree. Please give another mother name!");
                        is_motherExists = 0;
                    }
                } while (is_motherExists == 0);
                  
              do
              {
                puts("Enter the name of the father");
                scanf("%s",fatherName);
                for(int i=0;i<treeCount;i++){
                    if(strcmp(fatherName,newTree->familyMembers[i]->name)==0){
                        puts("Father has found in the same family tree!");
                        newPerson->Father = newTree->familyMembers[i];
                        is_fatherExists=1;
                        break;
                    }
                }
                if(is_fatherExists==0 && allTrees != NULL){
                    puts("This person doesn't exists on the same tree,wanna look other trees?(1-Yes 2-No):");
                    scanf("%d",&searchVal);
                    if(searchVal==1){
                        int fatherfound = 0;
                        fatherfound = is_f_inOtherFamily(allTrees,newPerson,fatherName);
                        if(fatherfound){
                            puts("Father has found in other family tree.");
                            is_fatherExists = 1;
                        }
                        else{
                            is_fatherExists = 0;
                            puts("Father gas not found in any other family tree.");
                        }
                    }else{
                        is_fatherExists= 0;
                        puts("Give another father name in this family tree!");
                    }
                }
                else if(is_fatherExists==0 && allTrees == NULL){
                    puts("This person doesn't exist in any tree. Please give another father name!");
                    is_fatherExists=0;
                }
              } while (is_fatherExists == 0);


              newTree->familyMembers[treeCount++] = newPerson;
              newTree->nodecount++;
            }
        }
        else if(menuChoice == 2){
               puts("Merhaba");
               FILE* fp = fopen(newTree->treename, "w");
                if (fp == NULL) {
                printf("Error opening file %s\n", newTree->treename);
                exit(1);
                }

                //puts(newTree->familyMembers[0]->name);

                fputs("Name | Age | Father | Mother\n", fp);
                //printf("%s,%s,%s",newTree->familyMembers[0]->name,newTree->familyMembers[1]->name,newTree->familyMembers[2]->name);
                for (int i = 0; i < treeCount; i++) {
                    fprintf(fp, "%s|%d|%s|%s|\n", newTree->familyMembers[i]->name, newTree->familyMembers[i]->age,
                    newTree->familyMembers[i]->Father ? newTree->familyMembers[i]->Father->name : "NOT KNOWN",
                    newTree->familyMembers[i]->Mother ? newTree->familyMembers[i]->Mother->name : "NOT KNOWN");
                }
                
                fclose(fp);

                allTrees[familyTreeCounter++] = newTree;
            }
    } while (menuChoice != 3);
    

return newTree;
///stopeed here
}

void remove_familyTree(Tree** allTrees) {
    int chosenTree;
    puts("Family Trees");
    puts("********************");

    for (int i = 0; i < familyTreeCounter; i++) {
        printf("%d) %s\n", i, allTrees[i]->treename);
    }

    puts("\nChoose the index of the tree to remove:");
    scanf("%d", &chosenTree);

    remove(allTrees[chosenTree]->treename);

    if (chosenTree >= 0 && chosenTree < familyTreeCounter) {
        // Free the memory associated with the chosen tree
        free(allTrees[chosenTree]->treename);
        for (int i = 0; i < allTrees[chosenTree]->nodecount; i++) {
            free(allTrees[chosenTree]->familyMembers[i]->name);
            free(allTrees[chosenTree]->familyMembers[i]);
        }
        free(allTrees[chosenTree]->familyMembers);
        free(allTrees[chosenTree]);

        // Shift the remaining trees to remove the gap
        for (int i = chosenTree; i < familyTreeCounter - 1; i++) {
            allTrees[i] = allTrees[i + 1];
        }

        // Update the counter
        familyTreeCounter--;
        printf("Tree at index %d has been removed.\n", chosenTree);
    } else {
        printf("Invalid tree index: %d\n", chosenTree);
    }
}



void load_familyTree(Tree** allTrees){
    DIR *directory;
    struct dirent *entry;

    directory = opendir(".");
    if(directory == NULL){
        puts("Error opening directory.\n");
        return;
    }
    char fileNames[30][65];
    int fileindexer = 0;
    while((entry = readdir(directory)) != NULL){
        if(entry->d_type == DT_REG && strstr(entry->d_name,".txt") != NULL){
            strcpy(fileNames[fileindexer],entry->d_name);
            printf("%d)%s\n",fileindexer++,entry->d_name);
        }
    }
    
    int chosenTree;
    puts("Choose the family tree u wanna load");
    scanf("%d",&chosenTree);

    char filename[65]; 

    strcpy(filename,fileNames[chosenTree]);

    puts(filename);

    FILE *fp = fopen(filename,"r");


    char line[255];
    fgets(line,255,fp);
    int howManyperson = 0;
    while(fgets(line,255,fp)){
        howManyperson++;
    }
    rewind(fp);
    fgets(line,255,fp);

    
    
    Person** allPersons = (Person**)malloc(howManyperson*sizeof(Person*));

    int indexCount = 0;
    while(fgets(line,255,fp)){
        Person* newPerson = (Person*)malloc(sizeof(Person));
        newPerson->name = (char*)malloc(MAX_NAME * sizeof(char));
        char mothername[MAX_NAME];
        char fathername[MAX_NAME];
        sscanf(line,"%[^|]|%d|%[^|]|%[^|]",newPerson->name,&newPerson->age,fathername,mothername);
        if(strcmp(fathername,"NOT KNOWN")==0){
            newPerson->Father = NULL;
        }else{
            newPerson->Father = (Person*)malloc(sizeof(Person));
            newPerson->Father->name = (char*)malloc(MAX_NAME * sizeof(char));
            strcpy(newPerson->Father->name,fathername);
        }
        if(strcmp(mothername,"NOT KNOWN")==0){
            newPerson->Mother = NULL;
        }else{
            newPerson->Mother = (Person*)malloc(sizeof(Person));
            newPerson->Mother->name = (char*)malloc(MAX_NAME * sizeof(char));
            strcpy(newPerson->Mother->name,mothername);
        }
        allPersons[indexCount++] = newPerson;
    }
    fclose(fp);
    printf("%s has been succesfully loaded!\n",filename);
    int menuChoice;
    puts("Select an operation\n1-Add new person\n2-Remove a person\n3-Print a Person's nuclear family\n4-Search Relatives of Given Person\n5-Return to the main menu");
    scanf("%d",&menuChoice);

    Person* addedPerson = NULL;
    char motherName[MAX_NAME];
    int is_motherfound = 0;
    char fatherName[MAX_NAME];
    int is_fatherfound = 0;

    char willDeletename[MAX_NAME];
    int is_deletedfound = 0;
    Person* personTodelete = NULL;
    int is_havechild = 0;
    int delete_choice = 0;

    char tempname[MAX_NAME];
    int tempage;
    char tempmothername[MAX_NAME];
    char tempfathername[MAX_NAME];

    char relativeSearchname[MAX_NAME];
    int searchtype;

    Person* searchedPerson = NULL;
    int personIndex;
    switch (menuChoice)
    {
    case 1:
        addedPerson = (Person*)malloc(sizeof(Person));
        addedPerson->name = (char*)malloc(MAX_NAME*sizeof(char));
        puts("Give the name of the person you wanna add");
        scanf("%s",addedPerson->name);
        puts("Give the persons age ");
        scanf("%d",&addedPerson->age);
        do
        {
            puts("Give the mother's name of person you wanna add:");
            scanf("%s",motherName);

            for(int i=0;i<indexCount;i++){
                if(strcmp(motherName,allPersons[i]->name)==0){
                    puts("Mother has found!");
                    addedPerson->Mother = allPersons[i];
                    is_motherfound = 1;
                    break;
                }
            }
            if(is_motherfound==0){
                puts("Mother has not found! Please give an valid mother name!");
            }
        } while (is_motherfound==0);
        
        do
        {
            puts("Give the father's name of person you wanna add:");
            scanf("%s",fatherName);

            for(int i=0;i<indexCount;i++){
                if(strcmp(fatherName,allPersons[i]->name)==0){
                    puts("Father has found!");
                    addedPerson->Father = allPersons[i];
                    is_fatherfound = 1;
                    break;
                }

            }
            if(is_fatherfound==0){
                puts("Father has not found! Please give a valid father name!");
            }
        } while (is_fatherfound==0);
        allPersons[indexCount++] = addedPerson;        
        
        FILE *file35 = fopen(filename,"a");
        fprintf(file35,"%s|%d|%s|%s|\n",addedPerson->name,addedPerson->age,addedPerson->Father->name,addedPerson->Mother->name);
        
        fclose(file35);
        break;
    

    case 2:
    do {
        puts("Give the name of the person you want to remove:");
        scanf("%s", willDeletename);

        for (int i = 0; i < indexCount; i++) {
            if (strcmp(willDeletename, allPersons[i]->name) == 0) {
                puts("Person has been found!");
                is_deletedfound = 1;
                personTodelete = allPersons[i];
                personIndex = i;
                break;
            }
        }

        if (is_deletedfound == 0) {
            puts("The person you want to delete does not exist in the tree. Please provide a valid name.");
        }
    } while (is_deletedfound == 0);

    for (int i = 0; i < indexCount; i++) {
        if (allPersons[i]->Father != NULL && allPersons[i]->Mother != NULL) {
            
            if ((strcmp(personTodelete->name, allPersons[i]->Father->name) == 0) || (strcmp(personTodelete->name, allPersons[i]->Mother->name) == 0)) {
                is_havechild = 1;
                break;
            }
        }
    }

   for(int i=0;i<indexCount;i++){
            puts(allPersons[i]->name);
           }
    if (is_havechild == 1) {
        puts("This person has children. Removing this person will also remove their children. Do you want to continue?\n1-Yes\n2-No");
        scanf("%d", &delete_choice);
        if (delete_choice == 1) {
            // Remove the person's children
            for(int i=0;i<indexCount;i++){
                if(allPersons[i]->Father!=NULL){ 
                if (strcmp(allPersons[i]->Father->name,personTodelete->name)==0 || strcmp(allPersons[i]->Mother->name,personTodelete->name)==0) {
                    free(allPersons[i]->name);
                    free(allPersons[i]);
                    // Remove the child from the array
                    for (int j = i; j < indexCount - 1; j++) {
                        allPersons[j] = allPersons[j + 1];
                    }
                    i--; // Decrement i to handle the shifted array elements
                    indexCount--;
                }
                }
            }
            
            
            for (int i = 0; i < indexCount; i++) {
            if (strcmp(personTodelete->name, allPersons[i]->name) == 0) {
            free(allPersons[i]->name);
            free(allPersons[i]);
            for (int j = i; j < indexCount - 1; j++) {
                allPersons[j] = allPersons[j + 1];
            }
                indexCount--;
                    break;
                }
            }
            


        
            FILE *fpTemp = fopen("temptree.txt", "w");    
            if (fpTemp == NULL) {
                puts("Error opening temporary file for writing.");
                break;
            }

           
            
            
           
           
            
            fputs("NAME|AGE|FATHER|MOTHER|\n",fpTemp);
            for(int i=0;i<indexCount;i++){
                puts(allPersons[i]->name);
                fprintf(fpTemp,"%s|%d|%s|%s|\n",allPersons[i]->name,allPersons[i]->age,allPersons[i]->Father ? allPersons[i]->Father->name : "NOT KNOWN",allPersons[i]->Mother ? allPersons[i]->Mother->name : "NOT KNOWN");

            }
        
            fclose(fpTemp);
            remove(filename);
            rename("temptree.txt",filename);

            break;
        } else {
            break;
        }


    } else {
        // Free memory for the person and their name
        free(allPersons[personIndex]->name);
        free(allPersons[personIndex]);

        // Shift remaining persons in the array to fill the gap
        for (int i = personIndex + 1; i < indexCount; i++) {
            allPersons[i - 1] = allPersons[i];
        }

        // Decrement the indexCount to reflect the removed person
        indexCount--;

        // Create a temporary file for writing
        FILE *fpTemp = fopen("temptree.txt", "w");
        if (fpTemp == NULL) {
            puts("Error opening temporary file for writing.");
            break;
        }

        // Write the header line to the temporary file
        fprintf(fpTemp, "|Name|Age|Father|Mother|\n");
        for(int i=0;i<indexCount;i++){
            fprintf(fpTemp,"%s|%d|%s|%s|\n",allPersons[i]->name,allPersons[i]->age,allPersons[i]->Father ? allPersons[i]->Father->name : "NOT KNOWN",allPersons[i]->Mother ? allPersons[i]->Mother->name : "NOT KNOWN");

        }
        
        fclose(fp);
        fclose(fpTemp);
        remove(filename);
        rename("temptree.txt",filename);

        break;
    }
    case 3:
        puts("Enter the name of the person: ");
        scanf("%s",relativeSearchname);

        for(int i=0;i<indexCount;i++){
            if(strcmp(relativeSearchname,allPersons[i]->name)==0){
                puts("Person has found!");
                searchedPerson = allPersons[i];
                break;
            }
        }
        if(searchedPerson != NULL){ 
        printf("Printing the nuclear family of %s:\n",relativeSearchname);
        printf("Father : %s\nMother: %s\n",searchedPerson->Father->name,searchedPerson->Mother->name);

        printf("Siblings:");
        for(int i=0;i<indexCount;i++){
            if((strcmp(searchedPerson->Father->name,allPersons[i]->Father->name)==0) && (strcmp(searchedPerson->Mother->name,allPersons[i]->Mother->name)==0)){
                printf("%s,",allPersons[i]->name);
            }
        }

        printf("\n");

        printf("Children:");

        for(int i=0;i<indexCount;i++){
            if((strcmp(allPersons[i]->Father->name,relativeSearchname)==0) || (strcmp(allPersons[i]->Mother->name,relativeSearchname)==0)){
                printf("%s,",allPersons[i]->name);
            }
        }

        }
        break;
    
    case 4:
        //search relatives of given person
        puts("Enter the name of the person: ");
        scanf("%s",relativeSearchname);

        for(int i=0;i<indexCount;i++){
            if(strcmp(relativeSearchname,allPersons[i]->name)==0){
                puts("Person has found!");
                searchedPerson = allPersons[i];
                break;
            }
        }

        puts("Select the type of relatives:\n1-Parents\n2-Spouse\n3-Children\n4-Grandsparents\n5-Cousins");
        scanf("%d",&searchtype);

        switch (searchtype)
        {
        case 1:
            printf("Person's father is = %s\n",searchedPerson->Father->name);
            printf("Person's mother is = %s\n",searchedPerson->Mother->name);
            break;
        
        case 2:
            for(int i=0;i<indexCount;i++){
                if( (strcmp(allPersons[i]->Father->name,relativeSearchname)==0))
                {
                    printf("Person's spouse is = %s",searchedPerson->Mother);
                    break;
                }
                else if((strcmp(allPersons[i]->Mother->name,relativeSearchname)==0)){
                    printf("Person's spouse is = %s",searchedPerson->Father);
                    break;
                }
            }
            break;
        case 3:
            for(int i=0;i<indexCount;i++){
                if((strcmp(allPersons[i]->Father->name,relativeSearchname)==0)){
                    printf("Child of %s -> %s\n",relativeSearchname,allPersons[i]->name);
                }
                else if((strcmp(allPersons[i]->Mother->name,relativeSearchname)==0)){
                    printf("Child of %s -> %s\n",relativeSearchname,allPersons[i]->name);
                }
            }
            break;
        
        case 4:
            printf("\nGrandparents of %s\n",searchedPerson->name);
            if(searchedPerson->Father->Father == NULL || searchedPerson->Father->Mother == NULL || searchedPerson->Mother->Father == NULL || searchedPerson->Mother->Mother == NULL){
                puts("One of grandparents are not known!");
            }
            else{
                printf("%s\n%s\n%s\n%s",searchedPerson->Father->Father->name,searchedPerson->Father->Mother->name,searchedPerson->Mother->Father->name,searchedPerson->Mother->Mother->name);
            }
            break;

        case 5:

            break;
        default:
            break;
        }




        break;
    
    default:
        break;
    }


    

    for(int i=0;i<indexCount;i++){
        free(allPersons[i]->name);
        free(allPersons[i]);
    }
    free(allPersons);


}
void main(void){
    int returnVal;
    int removeChoice = 0;
    Tree** allTrees = (Tree**)malloc(MAX_TREE_LEN * sizeof(Tree*)); // Allocate memory for allTrees
    do
    {
        returnVal = menu();

        switch (returnVal)
        {
        case 1:
                addFamilyTree(allTrees);
            break;
        
        case 2:
            remove_familyTree(allTrees);
            break;
        
        case 3:
            load_familyTree(allTrees);
            break;
        default:
            break;
        }
    } while (returnVal != 4);
    
    
    
    if (allTrees != NULL) {
        for (int i = 0; i < familyTreeCounter; i++) {
            Tree* tree = allTrees[i];
            for (int j = 0; j < tree->nodecount; j++) {
                free(tree->familyMembers[j]->name);
                free(tree->familyMembers[j]);
            }
            free(tree->treename);
            free(tree->familyMembers);
            free(tree);
        }
        free(allTrees);
    }


}


