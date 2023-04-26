#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_PRODUCT_NAME 8
#define MAX_BRAND_NAME 5
#define MAX_BRANCH_NAME 15
#define NEW_FATURE_NAME 9
#define NEW_FEATURE_STR 20
#define MAX_FEATURES 20
#define MAX_LINE_LENGTH 255

struct product{
    int pid;
    char type;
    char *name;
    char *brand;
    float price;
    char **features;

};
typedef struct product Product;
//pID,Type,Name,Brand,Price




void prodPrinter();

int menu(){
    //1-file operations
    //query products
    //check stock status
    //stock control by brand
    //export report
    //The available operations are explained in more detail in the following sections. After the user has selected
    int choice;
    int errorFlag = 0;
    
    
    do
    {
        printf("Welcome the operator,please select an option to continue;\n");
        if(errorFlag){
            printf("Please give a valid input!\n");

        }
        printf("1- File Operations\n2- Query products\n3-check stock status\n4-Stock control by brand\n5-Export report\n");
        scanf("%d",&choice);
        if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5){
            errorFlag = 1;
        }

    } while (errorFlag);
    

    return choice;
}

int linecountReturn(int *featureCount){
    FILE *fp = fopen("products.txt","r");
    int lineCount = 0;
    int ftc = 0;
    char c;
    *featureCount = 0;
    while((c=getc(fp)) != '\n'){
        if(c==','){
            *featureCount = (*featureCount)+1;
            
        }
    }
    rewind(fp);

    *featureCount = *featureCount - 4;


    while((c = fgetc(fp)) != EOF){
        
        if(lineCount == 0){

        }
        if(c == '\n'){
            lineCount++;
        }
    }
    fclose(fp);
    return lineCount+1;
}






int fileOperations(){
    int submenuChoice;
    int errorFlag = 0;
    do
    {
        if(errorFlag){
            printf("\nPlease give a valid input!");
        }
        printf("\n1- Add a new product\n2- Delete a product\n 3-Update a product\n4- Add feature to products\n5- Add new stock entry\n6- Delete a stock entry\n7- Update a stock entry\n 8- Back to main menu;");
        scanf("%d",&submenuChoice);
    } while (errorFlag);

    switch (submenuChoice)
    {
    case 1:
        /*add new product */
        break;
    
    case 2:
    /* delete a product*/
        break;
    case 3:
    /* update a product*/
        break;
    case 4:
    /* add feature to products*/
        break;
    case 5:
    /*add a new stock entry */
        break;
    case 6:
    /*delete a stock entry */ 
        break;
    case 7:
    /*update a stock entry */
        break;

    default:
        break;
    }
    
}
//pID,Type,Name,Brand,Price
/*
 int pid;
    char type;
    char *name;
    char *brand;
    float price;
    char **features;
*/
Product* strctFiller(){
    
    int featureCount;
    //printf("here is okay.");

    int proCount = linecountReturn(&featureCount);
   // printf("linoecount return = %d",proCount);
    Product *productArray = (Product*)malloc(proCount * sizeof(Product));
    FILE *fp = fopen("products.txt","r");
    char buffer[MAX_LINE_LENGTH];
    fgets(buffer,MAX_LINE_LENGTH,fp); //skipping the first line
    int counter = 0;
    while(fgets(buffer,MAX_LINE_LENGTH,fp)){
        productArray[counter].name = (char*)malloc(15 * sizeof(char));
        productArray[counter].brand = (char*)malloc(15 * sizeof(char));
        
        if(featureCount > 0){
            char restofLine[MAX_LINE_LENGTH];
            sscanf(buffer,"%d,%c,%s,%s,%f,%[^\n]",&productArray[counter].pid,&productArray[counter].type,productArray[counter].name,productArray[counter].brand,&productArray[counter].price,restofLine);            
            int x = 0;

            while(restofLine[x] != '\0'){
                x++;
            }
            restofLine[x] = '\0';
            //restofLine[strcspn(restofLine, "\n")] = '\0'; //strip newline character
            char *token = strtok(restofLine,",");
            int j = 0;
            productArray[counter].features = (char**)malloc(featureCount * sizeof(char*));
            
            while(token != NULL){
                printf("in the token loop.");
                productArray[counter].features[j] = (char*)malloc((NEW_FEATURE_STR+1) * sizeof(char));
                int k=0;
                while(token[k] != '\0'){
                     productArray[counter].features[j][k] = token[k];
                    k++;
                }
                productArray[counter].features[j][k] = '\0';
                //strcpy(productArray[counter].features[j])
                token = strtok(NULL,",");

            }

        }
        else{
            puts(buffer);
            //sscanf(buffer,"%d,%c,%s,%s,%f,%*[^\n]",&productArray[counter].pid,&productArray[counter].type,productArray[counter].name,productArray[counter].brand,&productArray[counter].price);
            sscanf(buffer,"%d,%c,%[^,],%[^,],%f%*[^\n]",&productArray[counter].pid,&productArray[counter].type,productArray[counter].name,productArray[counter].brand,&productArray[counter].price);
            printf("%f",productArray[counter].price);
        }
        counter++;
    }

    //printf("%s,%d",productArray[0].name,productArray[0].pid);

    fclose(fp);
    
    return productArray;
}

int updateAproduct(){
    int featurecount;
    int errorflag =0;
    FILE *fp = fopen("products.txt","r");
    FILE *fp2 = fopen("temp2.txt","w");
    int linenums = linecountReturn(&featurecount);
    rewind(fp);
    char buffer[MAX_LINE_LENGTH];
    char type;
    char tempname[15];
    char brand[15];
    float price;
    int choosedid;
    int linec = 0;
    prodPrinter();
    do
    {
        if(errorflag){
            printf("\nPlease give a valid input: ");

        }
        else{
        printf("\nPlease give the id of product you wanna update: ");

        }
        
        scanf("%d",&choosedid);
        if(choosedid>linenums){
            errorflag =1;
        }
        else{errorflag=0;}
    } while (errorflag);
    
    
    while(fgets(buffer,MAX_LINE_LENGTH,fp)){
        int tempId;
        if(linec < choosedid){
            fputs(buffer,fp2);
        }
        else if(linec == choosedid){
            //pID,Type,Name,Brand,Price

            //sscanf(buffer,"%d%*[^\n]",&tempId);
            printf("\nGive the updated type name: ");
            scanf(" %c",&type);
            while(getchar() != '\n');
            printf("\nGive the updated name: ");
            scanf("%s",tempname);
            printf("\nGive the updated brand: ");
            scanf("%s",brand);
            printf("\nGive updated price: ");
            scanf("%f",&price);
            fprintf(fp2,"%d,%c,%s,%s,%.2f",choosedid,type,tempname,brand,price);
            for(int j=0;j<featurecount;j++){
                char fname[NEW_FEATURE_STR];
                printf("\nGive the updated feature name: ");
                scanf("%s",fname);
                fprintf(fp2,",%s",fname);
            }
            fprintf(fp2,"\n");
        }
        else{
            fputs(buffer,fp2);
        }
        linec++;
    }
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp2.txt","products.txt");
}


void prodPrinter(){
    FILE *fp = fopen("products.txt","r");
    char *emptyBuffer = malloc(MAX_LINE_LENGTH*sizeof(char));

    fgets(emptyBuffer,MAX_LINE_LENGTH,fp);
    free(emptyBuffer);
    char comingChar;
    while((comingChar = fgetc(fp)) != EOF){
        putchar(comingChar);
    }
    fclose(fp);
}

int deleteAproduct(int featureExist){
    int id_todel = 0;
    
    printf("\n");
    prodPrinter();
    printf("\nPlease give the id of which product you wanna delete: ");
    scanf("%d",&id_todel);
    while(getchar() != '\n');
    FILE *fp = fopen("products.txt","r");
    FILE *fp2 = fopen("temp.txt","w");
    int lineCount = 1;
    char buffer[MAX_LINE_LENGTH];
    
    while(fgets(buffer,MAX_LINE_LENGTH,fp)){
        lineCount++;
       
        if(lineCount == id_todel){
            continue;
        }
        if(lineCount > id_todel){
            int pid;
            char name[15];
            char brand[15];
            char type;
            float price;
            char resofline[255];
            if(featureExist){
                sscanf(buffer,"%d,%c,%[^,],%[^,],%f,%[^\n]\n",&pid,&type,name,brand,&price,resofline);
                pid =pid - 1;
                fprintf(fp2,"%d,%c,%s,%s,%.2f,%s\n",pid,type,name,brand,price,resofline);

            }else{
                sscanf(buffer,"%d,%c,%[^,],%[^,],%f",&pid,&type,name,brand,&price);
                pid =pid- 1;
                fprintf(fp2,"%d,%c,%s,%s,%.2f\n",pid,type,name,brand,price);


            }
            
        }else{
            fputs(buffer,fp2);
        }
        
    }                    
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
    return 1;
}



int updateAstockEntry(){
    int linecount = 0;
    int idtoup =0;
    int errorflag =0;
    char c;
    FILE *fp = fopen("stocks.txt","r");
    while(feof(fp) ==0){
        c = getc(fp);
        putchar(c);
        if(c == '\n'){
            linecount++;
        }
    }

    do
    {
        if(errorflag){
            printf("\nPlease give an id between 1 and %d",linecount);
        }
        else{
            printf("\nGive the id of entry yo wanna update: ");
        }
        scanf("%d",&idtoup);
        if(idtoup>linecount || idtoup<1){
            errorflag =1;
        }
        else{
            errorflag =0;
        }
    } while (errorflag);

    rewind(fp);
FILE *fp2 = fopen("tempupdt.txt","w");
int tempid;
char tempname[MAX_BRANCH_NAME];
int tempstock;
char buffer[MAX_LINE_LENGTH];
fgets(buffer,MAX_LINE_LENGTH,fp);
fputs(buffer,fp2);
while(fgets(buffer,MAX_LINE_LENGTH,fp)){
    int comingid;
    sscanf(buffer,"%d%*[^\n]",&comingid);
    if(comingid == idtoup){
        printf("\nGive the updated pid: ");
        scanf("%d",&tempid);
        printf("\nGive the updated branchname: ");
        scanf("%s",tempname);
        printf("\nGive updated stock value: ");
        scanf("%d",&tempstock);
        fprintf(fp2,"%d,%d,%s,%d\n",comingid,tempid,tempname,tempstock);
    }
    else{
        fputs(buffer,fp2);
    }
}
fclose(fp);
fclose(fp2);
remove("stocks.txt");
rename("tempupdt.txt","stocks.txt");


}

int deleteAstockEntry(){
    int linecount = 0;
    int idtodel =0;
    int errorflag =0;
    char c;
    FILE *fp = fopen("stocks.txt","r");
    while(feof(fp) ==0){
        c = getc(fp);
        putchar(c);
        if(c == '\n'){
            linecount++;
        }
    }

    do
    {
        if(errorflag){
            printf("\nPlease give an id between 1 and %d",linecount);
        }
        else{
            printf("\nGive the id of entry yo wanna del: ");
        }
        scanf("%d",&idtodel);
        if(idtodel>linecount || idtodel<1){
            errorflag =1;
        }
        else{
            errorflag =0;
        }
    } while (errorflag);
    printf("idtodel = %d\n",idtodel);
    rewind(fp);
    
    FILE *fp2 = fopen("stemp.txt","w");
    char temp[MAX_LINE_LENGTH];
    fgets(temp,MAX_LINE_LENGTH,fp);
    while(fgets(temp,MAX_LINE_LENGTH,fp)){
        int comingid;
        sscanf(temp,"%d%*[^\n]",&comingid);
        if(comingid == idtodel){
            continue;
        }
        else if(comingid>idtodel){
            char restofline[MAX_LINE_LENGTH];
            int tid;
            sscanf(temp,"%d%[^\n]\n",&tid,restofline);
            fprintf(fp2,"%d%s",tid-1,restofline);
        }
        
        else{
            fputs(temp,fp2);
        }
    }
    fclose(fp2);
    fclose(fp);

    remove("stocks.txt");
    rename("stemp.txt","stocks.txt");


}
int addStockEntry(){
    FILE *fp = fopen("products.txt","r");
    int errorflag = 0;
    int lineCount = 0;
    char comingchar;
    int tempid;
    int stock;
    char branchname[MAX_BRANCH_NAME];
    while(feof(fp) == 0){
        comingchar = getc(fp);
        if(comingchar == '\n'){
            lineCount++;
        }
    }
    fclose(fp);
    printf("%d",lineCount);

    do
    {
        if(errorflag){
            printf("\nPlease give an valid pid between 1 and %d",lineCount);

        }
        else{
            printf("\nPlease give an pid: ");

        }
        scanf("%d",&tempid);
        if(tempid > lineCount || tempid < 1){
            errorflag = 1;
        }
        else{
            errorflag =0;
        }
    } while (errorflag);
//sID,pID,branch,current_stock

    printf("\nPlease give an branch name: ");
    scanf("%s",branchname);
    printf("\nPlease give current stock value: ");
    scanf("%d",&stock);
    FILE *fp2 = NULL;
    fp2 = fopen("stocks.txt","r");
    int linec =0;
    while(feof(fp2) == 0){
        comingchar = getc(fp2);
        if(comingchar == '\n'){
            linec++;
        }
    }
    printf("linec%d\n",linec);
    fclose(fp2);
    fp2 = fopen("stocks.txt","a");
    fprintf(fp2,"\n%d,%d,%s,%d",linec+1,tempid,branchname,stock);
    fclose(fp2);
    

}
int addProduct(int lineCount){
    int commaCount = 0;
    int featureCount =0;
    int inFeature = 0;
    FILE* fp = fopen("products.txt","r");
    if(fp==NULL){
        printf("\nCould not open the file.");
        exit(1);
    }
    else{
        //1,D,Ayran,Sutas,20.5
        char comingChar;
        while((comingChar = fgetc(fp)) != '\n'){
            
            if(comingChar == ','){
                commaCount++;
            }
            
        }

        rewind(fp);
        
        
    }
    printf("Feature count = %d\n",featureCount);
    fclose(fp);
    printf("Linecount %d\n",lineCount);
    fp = fopen("products.txt","a");
    
    char prodName[15];
    char type = 'X';
    char brand[15];
    float price =0;
    int pid = lineCount;
    printf("\nPlease give properties of item which u wanna add:\n1)Give a Type(D=drinks,Y=Meal):");
    scanf("%c",&type);
    while (getchar() != '\n');
    
    printf("\n2)Give the name of product: ");
    scanf("%s",prodName); 
    printf("\n3)Give the brand of product: ");
    scanf("%s",brand);
    printf("\n4)Give the price of product: ");
    scanf("%f",&price);

    
    //printf("\n%d,%c,%s,%s,%.2f",pid,type,prodName,brand,price);
    

    fprintf(fp,"\n%d,%c,%s,%s,%.2f",pid,type,prodName,brand,price);
    for(int i =0;i<commaCount-4;i++){
            char tempFeature[NEW_FEATURE_STR];
            printf("\nGive the new features value: ");
            scanf("%s",tempFeature);
            while(getchar() != '\n');

            fprintf(fp,",%s",tempFeature);
        }
    fclose(fp);

}


int add_feature(int lineCount,int* featurexists){
    if(*featurexists == 0){
        *featurexists = 1;
    }
    FILE *fp = fopen("products.txt","r");
    char buffer[255];    
    fgets(buffer,255,fp);

    puts(buffer);     
    char featureName[NEW_FATURE_NAME];
    printf("\nGive the name of feature which you want to add:");
    scanf("%s",featureName);
    int bufferlen =0;
    int flen =0;
    for(int i=0;buffer[i] !='\0';i++){
        bufferlen++;
    }


    buffer[bufferlen-1] = ',';
    puts(buffer);
    
    for(int i=0;featureName[i] !='\0';i++){
        flen++;
    }
    
    
    
    
    for(int i = 0;i<flen;i++){
        buffer[bufferlen++] = featureName[i];
    }

    buffer[bufferlen] = '\n';
    buffer[bufferlen+1] = '\0';
    puts(buffer);
    FILE *fp2 = fopen("requ.txt","w");
    fputs(buffer,fp2);
    
    char tempLine[MAX_LINE_LENGTH];
    while(fgets(tempLine,MAX_LINE_LENGTH,fp)){
        char firstline[MAX_LINE_LENGTH];
        sscanf(tempLine,"%[^\n]",firstline);
        int i = 0;
        sprintf(tempLine,"%s,null\n",firstline);
        fputs(tempLine,fp2);
    }
    
    fputs(tempLine, fp2);

    fclose(fp2);
    fclose(fp);

    remove("products.txt");
    rename("requ.txt","products.txt");
    


}


int queryProducts(int featureexists){
    FILE *fp = fopen("products.txt","r");
    
    char firstline[MAX_LINE_LENGTH];
    int featurecount = 0;
    int valuecount = 0;
    int linecount = linecountReturn(&featurecount);
    featurecount = featurecount +4;
    fgets(firstline,MAX_LINE_LENGTH,fp);
    if(featureexists){
        char features[MAX_FEATURES][15];
        char filters_match[MAX_FEATURES][15];
        char values[MAX_FEATURES][15];
        int match_cound =0;
        char *token = strtok(firstline,",");
        int r=0;
        while(token != NULL){
            strcpy(features[r],token);
            token = strtok(NULL,",");
            r++;
        }
        char filter[100];
        printf("\nGive the filters u wanna use case sensitive (Brand,Sutas,Type,C): ");
        scanf("%s",filter);
        token = strtok(filter,",");
        while(token != NULL){
            int matched = 0;
            for(int m=0;m<r;m++){
                if(strcmp(token,features[m]) == 0){
                    strcpy(filters_match[match_cound],token);
                    match_cound++;
                    matched = 1;
                    break;
                }
            }
            if(!matched){
                strcpy(values[valuecount],token);
                valuecount++;
            }
            token = strtok(NULL,",");
        }
        
        //lastSearch(filters_match,values);
        }
    
    else{
        char features[5][15];
        char filters_matched[5][15];
        char values[5][15];
        int match_f = 0;
        char *token = strtok(firstline,",");
        int r=0;
        while(token != NULL){
            strcpy(features[r],token);
            token = strtok(NULL,",");
            r++;
        }

        char filter[100];
        printf("\nGive the filters u wanna use case sensitive (Brand,Sutas,Type,C): ");
        scanf("%s",filter);
        token = strtok(filter,",");
        while(token != NULL){
            int matched = 0;
            for(int m=0;m<r;m++){
                if(strcmp(token,features[m]) == 0){
                    strcpy(filters_matched[match_f],token);
                    match_f++;
                    matched = 1;
                    break;
                }
            }
            if(!matched){
                strcpy(values[valuecount],token);
                valuecount++;
            }
            token = strtok(NULL,",");
        }
        
       // lastSearch(filters_matched,values);
    }
}


int searchProducts(int featureexists,int linecount){
    int schoice;
    int choice;
    float priceH;
    float priceL;
    char brand1[15];
    char type1;
    char matchedstrings[10][MAX_LINE_LENGTH];
    char *matchedstring = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    int matchCount =0;
    printf("\n1)List all products\n2)Filter products by brand,type,price or a user-defined feature\n3)Back to main menu.");
    scanf("%d",&schoice);
    FILE *fp = fopen("products.txt","r");
    char buffer[MAX_LINE_LENGTH];

    switch (schoice)
    {
    case 1:
        fgets(buffer,MAX_LINE_LENGTH,fp);
        while(fgets(buffer,MAX_LINE_LENGTH,fp)){
            puts(buffer);
        }
        break;
    
    case 2:
        
        printf("\n1)Filter by brand\n2)Filter by type\n3)Filter by price\n4)Filter by 2 or more features: ");
        scanf("%d",&choice);
        while(getchar() != '\n');
        switch (choice)

        {
        case 1:
            
            printf("\nGive an brand name to filter: ");
            scanf("%s",brand1);
            Product *productArray = (Product*)malloc(linecount * sizeof(Product));
            productArray=strctFiller();
            for(int i=0;i<linecount;i++){
                
                if(strcmp(productArray[i].brand,brand1)==0){
                    //pID,Type,Name,Brand,Price
                    sprintf(matchedstring,"%d,%c,%s,%s,%.2f",productArray[i].pid,productArray[i].type,productArray[i].name,productArray[i].brand,productArray[i].price);
                    strcpy(matchedstrings[i],matchedstring);
                    matchCount++;
                    
                }
                
                
            }
            free(productArray);
            free(matchedstring);
            
            break;
        case 2:
            printf("\nGive an type name to filter: ");
            scanf("%c",&type1);
            productArray = (Product*)malloc(linecount * sizeof(Product));
            productArray=strctFiller();
            for(int i=0;i<linecount;i++){
                
                if(productArray[i].type = type1){
                    //pID,Type,Name,Brand,Price
                    sprintf(matchedstring,"%d,%c,%s,%s,%.2f",productArray[i].pid,productArray[i].type,productArray[i].name,productArray[i].brand,productArray[i].price);
                    strcpy(matchedstrings[i],matchedstring);
                    matchCount++;
                    puts(matchedstring);
                }
                
                
            }
            free(productArray);
            free(matchedstring);
            break;
        case 3:
            productArray = (Product*)malloc(linecount * sizeof(Product));
            productArray=strctFiller();
            printf("\nGive the highest price: ");
            scanf("%f",&priceH);
            printf("\nGive the lower price: ");
            scanf("%f",&priceL);
            for(int i=0;i<linecount;i++){
                
                if(productArray[i].price>priceL && productArray[i].price<priceH){
                    //pID,Type,Name,Brand,Price
                    sprintf(matchedstring,"%d,%c,%s,%s,%.2f",productArray[i].pid,productArray[i].type,productArray[i].name,productArray[i].brand,productArray[i].price);
                    strcpy(matchedstrings[i],matchedstring);
                    matchCount++;
                    puts(matchedstring);
                }
                
                
            }
            free(productArray);
            free(matchedstring);
            
            break;
            
        default:
            break;
        }
        break;
    default:
        break;
    }
    fclose(fp);
}



int main(){
    int featureCount;
    int featureExists;
    int menuchoice;
    int linecount;
    int tempchoice;
    linecount = linecountReturn(&featureCount);
    searchProducts(featureExists,linecount);
    return 0;
    add_feature(linecount,&featureExists);
    Product *productArray = (Product*)malloc(linecount * sizeof(Product));
    productArray=strctFiller();
    printf("%d - %s - %s\n",productArray[0].pid,productArray[0].name,productArray[0].brand);

    
    menuw:

        menuchoice = menu();
       // printf("1- File Operations\n2- Query products\n3-check stock status\n4-Stock control by brand\n5-Exit the operator\n");
    
    switch (menuchoice)
    {
    case 1:
        //fileoperations
        
        printf("\nFile Operations\n1)Add new product\n2)Delete a product\n3)Update a product\n4)Add feature to products\n5)Add a new stock entry\n6)Delete a stock entry\n7)Update a stock entry\n8)Back to main menu\n");
        scanf("%d",&tempchoice);
        switch (tempchoice)
        {
        case 1:
            linecount = linecountReturn(&featureCount);
            addProduct(linecount);
            break;
        
        case 2:
            deleteAproduct(featureExists);
            break;
        case 3:
            updateAproduct();
            break;
        case 4:
            linecount = linecountReturn(&featureCount);
            add_feature(linecount,&featureExists);
            break;
        case 5:
            addStockEntry();
            break;
        case 6:
            deleteAstockEntry();
            break;
        case 7:
            updateAstockEntry();
            break;
        case 8:
            goto menuw;
        default:
            break;
        }
        break;
    
    case 2:
        //query products
        break;
    case 3:
        //check stock status
        break;
    case 4:
        //stock control by brand
        break;
    case 5:
        //export report
        break;

    default:
        break;
    }
    
}