#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#define MAX_PRODUCT_NAME 9
#define MAX_BRAND_NAME 9
#define MAX_BRANCH_NAME 15
#define NEW_FATURE_NAME 9
#define NEW_FEATURE_STR 20
#define MAX_FEATURES 20
#define MAX_LINE_LENGTH 255




void prodPrinter();

char* trim(char* str) {
    char* end;

    // Trim leading whitespace
    while(isspace((unsigned char)*str)) str++;

    if(*str == 0) { // All spaces?
        return str;
    }

    // Trim trailing whitespace
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;

    // Write new null terminator
    *(end+1) = 0;

    return str;
}


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
    int featuresCount = 0;
    featureCount(&featuresCount);

    char features[featuresCount][15];
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
        if(choosedid>linenums-1){
            errorflag =1;
        }
        else{errorflag=0;}
    } while (errorflag);






    fgets(buffer,MAX_LINE_LENGTH,fp);
    puts(buffer);
    fputs(buffer,fp2);
    char *token = strtok(buffer,",");
    int r=0;
    while(token != NULL){
        strcpy(features[r],token);
        r++;
        token = strtok(NULL,",");
    }
    char newg[15];
    char givenlabel[15];
    int chosenlabel = 99;
    

    
    while(fgets(buffer,MAX_LINE_LENGTH,fp)){
        int tempId;
        sscanf(buffer,"%d,%*[^\n]\n",&tempId);
        if(tempId < choosedid){
            fputs(buffer,fp2);
        }
        else if(tempId == choosedid){
            //pID,Type,Name,Brand,Price
            token = strtok(buffer,",");
            int m=0;
            while(token != NULL){
                if(m==chosenlabel){
                    if(m==featuresCount-1){
                        fprintf(fp2,"%s",newg);
                    }else{
                        fprintf(fp2,"%s,",newg);

                    }                    
                }else{
                    if(m==featuresCount-1){
                        fprintf(fp2,"%s",token);
                    }else{
                        fprintf(fp2,"%s,",token);
                    }
                    
                }
                m++;
                token = strtok(NULL,",");
            }
        }
        else{
            fputs(buffer,fp2);
        }
        
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


int stockQueryop1(){
    int givenpid;
    int errorFlag =0;
    char bname[15];
    char bnameGiven[15];
    int stockValue =0;


    int lineCount =0;
    FILE *fp = fopen("products.txt","r");
    char line[MAX_LINE_LENGTH];
    while(fgets(line,MAX_LINE_LENGTH,fp)){
        puts(line);
        lineCount++;
    }
    fclose(fp);
    
    do
    {
        if(errorFlag){
            puts("Please give and valid id.");
        }
        else{
            puts("Please give the id of product u wanna query the stock values.");
        }
        scanf("%d",&givenpid);
        if(givenpid > lineCount-1 || givenpid < 1){
            errorFlag = 1;
        }else{
            errorFlag =0;
        }
    } while (errorFlag);
    
    //sID,pID,branch,current_stock

    fp = fopen("stocks.txt","r");
    int r=0;
    while (fgets(line,MAX_LINE_LENGTH,fp))
    {   
        if(r==0){
            puts(line);
        }else{
            sscanf(line,"%*d,%*d,%[^,],%*d\n",bname);
            puts(bname);
        }
        r++;
    }
    r=0;
    rewind(fp);
    bname[0] = '\0';
    printf("\nPlease give a branch-name: ");
    scanf("%s",bnameGiven);
    while(fgets(line,MAX_LINE_LENGTH,fp)){
        int tempid;
        if(r==0){

        }else{
            sscanf(line,"%*d,%d,%[^,],%d\n",&tempid,bname,&stockValue);
            
            
            if(strcasecmp(bname,bnameGiven)==0 && tempid == givenpid){
               // printf("productId = %d branch = %s stockvalue = %d\n",tempid,bname,stockValue);
            }
            
        }
        r++;
        fclose(fp);
    }
    


}

int brandStockControl(){//burada kladim
    char givenBrand[MAX_BRAND_NAME];
    int givenpid;
    printf("\nGive an brand name to list all of their products with stock values:");
    scanf("%s",givenBrand);
    FILE *fp = fopen("products.txt","r");
    char line[MAX_LINE_LENGTH];
    int r =0;
    int matchedcount =0;
    int *pids = malloc(10*sizeof(int));
    float *prices = malloc(10*sizeof(float));
    int *stockvals = malloc(30*sizeof(int));

    while(fgets(line,MAX_LINE_LENGTH,fp)){
       
        if(r==0){

        }
        else{
            char tempBrand[15];
            float temprice;
            sscanf(line,"%d,%*[^,],%*[^,],%[^,],%f",&givenpid,tempBrand,&temprice);
            
            if(strcmp(givenBrand,tempBrand)==0){
            
                pids[matchedcount] = givenpid;
                prices[matchedcount] = temprice;
                matchedcount++;
            }
        }
        r++;
    }
    fclose(fp);
    FILE *fp2 = fopen("stocks.txt","r");
   

    while(fgets(line,MAX_LINE_LENGTH,fp2)){
        int tempId;
        int tempstock;
        sscanf(line,"%*[^,],%d,%*[^,],%d\n",&tempId,&tempstock);
        int f=0;
        for(int j=0;j<matchedcount;j++){
            if(tempId == pids[j]){
                stockvals[f] = tempstock;
                f++;

            }
        }
    }

    for(int i=0;i<20;i++){
        printf("%d\n",stockvals[i]);
    }

    char *entry = (char*)malloc(155 * sizeof(char));
    char **twoD = (char**)malloc(matchedcount * sizeof(char*));
    for(int m=0;m<matchedcount;m++){
        twoD[m] = (char*)malloc(155*sizeof(char));
        sprintf(entry,"pid = %d, price = %.2f, stockValue = %d\n",pids[m],prices[m],stockvals[m]);
        strcpy(twoD[m],entry);

    }
    free(entry);

    for(int i=0;i<matchedcount;i++){
        puts(twoD[i]);
    }


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
    
    char tempLine[265];
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

int featureCount(int *fc){
    FILE *fp = fopen("products.txt","r");
    char c;

    while((c=getc(fp)) != '\n'){
        if(c == ','){
            *fc += 1;
        }

    }
    *fc += 1;

    return *fc;
}
int queryProd(int featureExists){
    FILE *fp = fopen("products.txt","r");
    int featurecount =0;
    
    featureCount(&featurecount);
    char featuresArray[featurecount][16];

    
   
    char firtsline[MAX_LINE_LENGTH];
    fgets(firtsline,MAX_LINE_LENGTH,fp);
    char *token = strtok(firtsline,",");
    int r =0;
    while (token != NULL)
    {
        int i =0;
        while(token[i] != '\n'){
            token[i] = tolower(token[i]);
            i++;
        }
        strcpy(featuresArray[r],token);
        token = strtok(NULL,",");
        r++;
    }
    char filter[100];
    printf("\nGive the filters u wanna use(brand,sutas,type,c,price,high-low):  ");
    scanf("%s",filter);
    int i = 0;
    while(filter[i] != '\n'){
        if(filter[i] != ','){
            filter[i] = tolower(filter[i]);

        }
        i++;
    }
    char values[featurecount][NEW_FEATURE_STR];
    token = strtok(filter,",");
    int valuesCount = 0;
    float priceHigh;
    float priceLow;
    int is_price =0;
    
    
    while (token != NULL) {
    int found = 0;
    
    
    

    for (int m = 0; m < featurecount; m++) {
        
        
        if (strcmp(trim(token), trim(featuresArray[m])) == 0) {
            printf("Match found: %s\n", trim(token));
            found = 1;
            is_price =1;
            break;
        }
    }



    
    
    if (!found) {
        if(is_price){
            sscanf(token,"%f-%f",&priceHigh,&priceLow);
            is_price=0;
        }
          else{
            strcpy(values[valuesCount], token);}  
            valuesCount++;
    }
    token = strtok(NULL, ",");
}


    
   
    char line[MAX_LINE_LENGTH];        
    
    int matchfound = 0;
    while(fgets(line,MAX_LINE_LENGTH,fp)){  
    
    int dingedCount = 0;
    
    for(int i=0;i<valuesCount;i++){
        char lineCopy[MAX_LINE_LENGTH];
        char lineCopy2[MAX_LINE_LENGTH];
        strcpy(lineCopy, line);
        


        
        float tempPrice = 0.0;
    
       
       
        token = strtok(lineCopy, ",");
        
        
        //token = strtok(line,",");
        while(token != NULL){
            if(strcasecmp(token,values[i]) == 0){
                dingedCount++;
                
                break;
            }
            else {
            }

            token = strtok(NULL,",");
        }
    }
    
    if(dingedCount >= valuesCount){
        puts(line);
        matchfound++;
    }
    }
    if(matchfound){
    
    }else{
        puts("None matched products had found.");
    }

}




int main(){
    brandStockControl();
    return 0;
    updateAproduct();
    return 0;
    stockQueryop1();
    return 0;
    int featureCount;
    int featureExists;
    int menuchoice;
    int linecount;
    int tempchoice;
    linecount = linecountReturn(&featureCount);
    //add_feature(linecount,&featureExists);
    queryProd(0);
    return 0;
    queryProd(0);
    return 0;
    searchProducts(featureExists,linecount);
    return 0;
    add_feature(linecount,&featureExists);
    
    
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
        tempchoice =0;
        puts("1)List all products.");
        puts("2)Filter products by,brand,type,price,or a user-defined feature.");
        puts("3)Back to main menu.");
        scanf("%d",&tempchoice);
        switch (tempchoice)
        {
        case 1:
            FILE *fp = fopen("products.txt","r");
            char comingChar;
            while(feof(fp) != 0){
                comingChar = getc(fp);
                putchar(comingChar);
            }
            fclose(fp);
            break;
        
        case 2:
            queryProd(featureExists);
            break;
        case 3:
            goto menuw;
            break;
        default:
            break;
        }

        break;
    case 3:
        tempchoice =0;
        //check stock status
        puts("1)Query the stock of a given product in a specified branch.");
        //takes product id and branch name
        puts("2)Query to list the stock of all products in a branch.");
        
        puts("3)List out-of-stock products in a branch.");
        puts("4)Return to main menu.");
        scanf("%d",&tempchoice);
        switch (tempchoice)
        {
        case 1:
            stockQueryop1();
            break;
        case 2:
            brandStockControl();
            break;
        case 3:

        default:
            break;
        }
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