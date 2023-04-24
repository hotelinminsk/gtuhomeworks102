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
    FILE *fp = fopen("products.txt","r");
    FILE *fp2 = fopen("temp.txt","w");
    int lineCount = 1;
    char buffer[MAX_LINE_LENGTH];
    
    while(fgets(buffer,MAX_LINE_LENGTH,fp)){
        lineCount++;
        printf("line con = %d,idtodel = %d\n",lineCount,id_todel);
        puts(buffer);
        if(lineCount<id_todel){
            fputs(buffer,fp2);           
        }
        else if(lineCount == id_todel){
            continue;
        }
        if(lineCount>id_todel){
            int pid;
            char name[15];
            char brand[15];
            char type;
            float price;
            char resofline[255];
            if(featureExist){
                sscanf(buffer,"%d,%c,%[^,],%[^,],%f,%[^\n]\n",&pid,&type,name,brand,&price,resofline);
                pid =pid - 1;
                fprintf(fp2,"%d,%c,%s,%s,%f,%s",pid,type,name,brand,price,resofline);

            }else{
                sscanf(buffer,"%d,%c,%[^,],%[^,],%f",&pid,&type,name,brand,&price);
                pid =pid- 1;
                fprintf(fp2,"%d,%c,%s,%s,%.2f\n",pid,type,name,brand,price);


            }
            
        }
    }                    
    fclose(fp);
    fclose(fp2);
    remove("products.txt");
    rename("temp.txt","products.txt");
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
    int pid = lineCount + 1;
    printf("\nPlease give properties of item which u wanna add:\n1)Give a Type(D=drinks,Y=Meal):");
    scanf("%c",&type);
    while (getchar() != '\n');
    
    printf("\n2)Give the name of product: ");
    scanf("%s",prodName); 
    printf("\n3)Give the brand of product: ");
    scanf("%s",brand);
    printf("\n4)Give the price of product: ");
    scanf("%f",&price);

    
    

    fprintf(fp,"\n%d,%c,%s,%s,%.2f",pid,type,prodName,brand,price);
    for(int i =0;i<commaCount-4;i++){
            char tempFeature[NEW_FEATURE_STR];
            printf("\nGive the new features value: ");
            scanf("%s",tempFeature);
            while(getchar() != '\n');

            fprintf(fp,",%s",tempFeature);
        }

}

int add_feature(int lineCount){
    
    FILE *fp = fopen("products.txt","r");
    char buffer[255];
    memset(buffer,0,sizeof(buffer));
    
    
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
    printf("buferlen = %d",bufferlen);

    buffer[bufferlen-1] = ',';
    printf("buferlen=%d",bufferlen);
    
    for(int i=0;featureName[i] !='\0';i++){
        flen++;
    }
    //'flen = \n'
    printf("flen %d",flen);

    for(int i = 0;i<flen;i++){
        buffer[bufferlen++] = featureName[i];
    }
    buffer[bufferlen] = '\n';
    FILE *fp2 = fopen("requ.txt","w");
    fputs(buffer,fp2);
    
    char tempLine[MAX_LINE_LENGTH];
    
    while(fgets(tempLine,MAX_LINE_LENGTH,fp)){
       int len =0;
       int j=0;
       char null[7]= ",null\n";
       while(tempLine[j] != '\0'){
        len++;
        j++;
       }
       len = len-1;
        for(int i=0;i<7;i++){
            tempLine[len++] = null[i];
        }
        //fputs(tempLine,fp2);
        fputs(tempLine,fp2);
    }

    remove("products.txt");
    rename("requ.txt","products.txt");

    fclose(fp);
    fclose(fp2);

        

    
    


}

void main(){
    deleteAproduct(0);
    //prodPrinter();
    int menu_choice;
    int lineCount;
    int featureCount;
    FILE* filePtr = NULL;
    filePtr = fopen("products.txt","r");
    rewind(filePtr);
    lineCount=linecountReturn(filePtr);
    printf("Number of lines in file: %d\n", lineCount);
    fclose(filePtr);
    //add_feature(lineCount);
    filePtr = fopen("products.txt","r");
    lineCount=linecountReturn(filePtr);
    addProduct(lineCount);
    //Product *product = strctFiller(lineCount,featureCount,filePtr);

    //rewind(filePtr);
    //add_feature(filePtr,lineCount);
   

    
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