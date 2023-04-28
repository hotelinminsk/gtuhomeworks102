int queryProd(int featureExists){
    FILE *fp = fopen("products.txt","r");
    int featurecount =0;
    char featuresArray[20][15];
    if(featureExists){
        linecountReturn(&featurecount);
    }
    featurecount =+ 4;
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
   
   
    char comingLabel[15];
    float priceHigh;
    float priceLow;
    
    while (token != NULL) {
    int found = 0;

    for (int m = 0; m < featurecount; m++) {
        if (strcasecmp(token, featuresArray[m]) == 0) {
            printf("Match found: %s\n", token);
            strcpy(comingLabel, token);
            found = 1;
            break;
        }
    }
    if (!found) {
        if (strcasecmp(comingLabel, "price") == 0) {
            sscanf(token, "%f-%f", &priceHigh, &priceLow);
        } else {
            strcpy(values[valuesCount], token);
            valuesCount++;
        }
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
        strcpy(lineCopy2, line);


        
        float tempPrice = 0.0;
        sscanf(lineCopy2, "%*d,%*c,%*s,%*s,%f%*[^\n]\n", &tempPrice);
        //sscanf(lineCopy,"%*[^0-9]%f%*[^0-9]\n",&tempPrice);
        puts("temp price: ");
        printf("%.2f",tempPrice);
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
        puts("Dinged count: ");
        printf("%d",dingedCount);
        puts("values count: ");
        printf("%d",valuesCount);
    }
    }
    if(matchfound){
    
    }else{
        puts("None matched products had found.");
    }

}