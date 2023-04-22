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

struct new_feature{
    char *new_feature_name;
    char* string_value;
    
};
typedef struct new_feature Feature;

struct stock{
    int sid;
    int pid;
    char* branch;
    int current_stock;
};

typedef struct stock Stock;

struct product
{
    int pid;
    char type;
    char* name;
    char* brand;
    float price;
    Stock* stockPKey;
    Feature** featurePKey;
    

};


typedef struct product Product;





int menu(){
    //1-file operations
    //query products
    //check stock status
    //stock control by brand
    //export report
    //The available operations are explained in more detail in the following sections. After the user has selected
    int choice;
    int errorFlag = 0;
    
    while(getchar() != '\n');
    do
    {
        printf("Welcome the operator,please select an option to continue;\n");
        if(errorFlag){
            printf("Please give a valid input!\n");

        }
        printf("1- File Operations\n2- Query products\n3-check stock status\n4-Stock control by brand\n5-Exit the operator\n");
        scanf("%d",&choice);
        if(choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5){
            errorFlag = 1;
        }

    } while (errorFlag);
    

    return choice;
}

int linecountReturn(FILE *filePtr){
    int lineCount = 0;
    char c;
    while((c = fgetc(filePtr)) != EOF){
        
        if(c == '\n'){
            lineCount++;
        }
    }
    return lineCount+1;
}




int productFeatureCount(FILE* filePtr){
    int commaCounter = 0;
    rewind(filePtr);
    char* buffer = malloc(100*sizeof(char));
    fgets(buffer,100,filePtr);
    char comingChar;
    for(int i=0;buffer[i] != '\n';i++){
        if(buffer[i] == ','){
            commaCounter++;
        }
    }
    rewind(filePtr);
    free(buffer);
    int featureCount = commaCounter +1;
    return featureCount;
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
Product* strctFiller(int lnC, int featrC, FILE* filePtr) {
    int lineiC = 0;
    int indexCount = 0;
    printf("Is there a problem NOT");
    Product *prdctPointer = (Product*) malloc(lnC * sizeof(Product));
    while (!feof(filePtr)) {
        if (lineiC == 0) {
            fscanf(filePtr, "%*[^\n]\n");
            printf("Is there a problem NOT");
        } else {
            printf("Is there a problem NOT");

            prdctPointer[indexCount].brand = (char*) malloc(MAX_BRAND_NAME * sizeof(char));
            prdctPointer[indexCount].name = (char*) malloc(MAX_PRODUCT_NAME * sizeof(char));
            prdctPointer[indexCount].stockPKey = (Stock*) malloc(sizeof(Stock));
            prdctPointer[indexCount].featurePKey = NULL;

            if (featrC > 5) {
                prdctPointer[indexCount].featurePKey = (Feature**) malloc((featrC-5) * sizeof(Feature*));
                int featureCount = 0;
                for (int i = 0; i < featrC-5; i++) {
                    prdctPointer[indexCount].featurePKey[i] = (Feature*) malloc(sizeof(Feature));
                    prdctPointer[indexCount].featurePKey[i]->new_feature_name = (char*) malloc(NEW_FATURE_NAME * sizeof(char));
                    prdctPointer[indexCount].featurePKey[i]->string_value = (char*) malloc(NEW_FEATURE_STR * sizeof(char));
                    prdctPointer[indexCount].featurePKey[i]->string_value = "null";
                }
            }
            int count = 0;
            char buffer[MAX_LINE_LENGTH];
            char comingChar = fgetc(filePtr);
            while (comingChar != '\n' && comingChar != EOF) {
                buffer[count++] = comingChar;
                comingChar = fgetc(filePtr);
            }
            buffer[count] = '\0';
            int i = 0;
            count = 0;
            int featureCount = 0;
            while (buffer[i] != '\0') {
                if (buffer[i] == ',') {
                    count++;
                } else {
                    // 1,D,Ayran,Sutas,20.5

                           
                    if (count <= 1) {
                    prdctPointer[indexCount].type = buffer[i];
                } else if (count == 2) {
                    if (buffer[i] != ',') {
                        prdctPointer[indexCount].brand[i - (count - 2) - 1] = buffer[i];
                    }
                } else if (count == 3) {
                    if (buffer[i] != ',') {
                        prdctPointer[indexCount].name[i - (count - 3) - 1] = buffer[i];
                    }
                } else if (count == 4) {
                    if (buffer[i] != ',') {
                        prdctPointer[indexCount].stockPKey->supplier[i - (count - 4) - 1] = buffer[i];
                    }
                } else if (count == 5) {
                    if (buffer[i] != ',') {
                        prdctPointer[indexCount].price = (prdctPointer[indexCount].stockPKey->price * 10) + (buffer[i] - '0');
                    }
                }
            }
            i++;
        }
        indexCount++;
    }
    lineiC++;
}
return prdctPointer;
}


/*
Product* strctFiller(int lnC,int featrC,FILE* filePtr){
    int lineiC=0;
    int indexCount = 0;
    printf("Is there a problem NOT");
    Product *prdctPointer = (Product*)malloc(lnC * sizeof(Product));
    while(feof(filePtr) == 0){
        if(lineiC==0){
            fscanf(filePtr,"%*[^\n]\n");
            printf("Is there a problem NOT");

        }
        else{
            printf("Is there a problem NOT");

            prdctPointer[indexCount].brand = (char*)malloc(MAX_BRAND_NAME * sizeof(char));
            prdctPointer[indexCount].name = (char*)malloc(MAX_PRODUCT_NAME * sizeof(char));
            prdctPointer[indexCount].stockPKey = (Stock*)malloc(sizeof(Stock));
            prdctPointer[indexCount].featurePKey = NULL;

            if(featrC > 5){
                prdctPointer[indexCount].featurePKey = (Feature**)malloc((featrC-5) * sizeof(Feature*));
                int featureCount = 0;
                for(int i=0;i<featrC-5;i++){
                    prdctPointer[indexCount].featurePKey[i] = (Feature*)malloc(sizeof(Feature));
                    prdctPointer[indexCount].featurePKey[i]->new_feature_name = (char*)malloc(NEW_FATURE_NAME*sizeof(char));
                    prdctPointer[indexCount].featurePKey[i]->string_value = (char*)malloc(NEW_FEATURE_STR * sizeof(char));
                    prdctPointer[indexCount].featurePKey[i]->string_value = "null";
                }                
            }///BURADA KALDIM BUYUK IHTIMAL SWITCH CASE ILE FEATURELAR EKLENECEK
            int count = 0;
            char buffer[MAX_LINE_LENGTH];
            char comingChar = fgetc(filePtr);
            while(comingChar != '\n' && comingChar != EOF){
                buffer[count++] = comingChar;
                comingChar = fgetc(filePtr);
            }
            buffer[count] = '\0';
            int i=0;
            count = 0;
            int featureCount = 0;
            while(buffer[i] != '\0'){
                if(buffer[i] == ','){
                    count++;
                }
                else{
                    //1,D,Ayran,Sutas,20.5

                    switch (count)
                    {
                    case 0:
                        prdctPointer[indexCount].pid = prdctPointer[indexCount].pid * 10 + buffer[i] - '0';
                        break;
                    case 1:
                        prdctPointer[indexCount].type = buffer[i];
                        break;
                    case 2:
                        prdctPointer[indexCount].name[count-1] = buffer[i];
                        break;
                    case 3:
                        prdctPointer[indexCount].brand[count-1] = buffer[i];
                        break;
                    case 4:
                        prdctPointer[indexCount].price = prdctPointer[indexCount].price * 10 + buffer[i] - '0';
                        break;
                    case 5:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 6:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 7:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 8:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 9:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 10:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 11:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 12:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 13:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 14:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 15:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 16:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 17:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 18:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 19:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 20:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 21:
                    prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 22:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 23:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    case 24:
                        prdctPointer[indexCount].featurePKey[featureCount]->string_value[count-1] = buffer[i];
                        featureCount++;
                        break;
                    default:
                        break;
                    }count++;
                }
                i++;
            }
            indexCount++;
        }
        lineiC++;
    }
    return prdctPointer;
}
*/
//1,D,Ayran,Sutas,20.5,saefasef,fsdf
int add_feature(FILE* filePtr,int lineCount){
    rewind(filePtr);
    char featureName[NEW_FATURE_NAME];
    printf("\nGive the name of which you want to add:");
    scanf("%s",featureName);
    char comingChar;
    int commaCount = 0;
    while((comingChar = fgetc(filePtr)) != '\n'){
        if(comingChar == ','){
            commaCount++;
        }
    };
    filePtr = filePtr-1;
    fprintf(filePtr,",%s\n",featureName);


}

void main(){
    int menu_choice;
    int lineCount;
    int featureCount;
    FILE* filePtr = fopen("products.txt","r");
    featureCount = productFeatureCount(filePtr);
    printf("Number of features in file: %d\n", featureCount);
    rewind(filePtr);
    lineCount=linecountReturn(filePtr);
    printf("Number of lines in file: %d\n", lineCount);
    rewind(filePtr);
    Product *product = strctFiller(lineCount,featureCount,filePtr);

    //rewind(filePtr);
    //add_feature(filePtr,lineCount);
    for(int j=0;j<lineCount;j++){
        
        printf("id=%d isim = %s price = %f\n",product[j].pid,product[j].name,product[j].price);

    }

    
    //productArrayCreator();
    /*
    while((menu_choice = menu()) != 5){
        switch (menu_choice)
        {
        case 1:
            printf("%d",menu_choice);
            //file operations
            break;
        
        default:
            break;
        }
    }
    */
}