for(int i=0;i<valuesCount;i++){
        char lineCopy[MAX_LINE_LENGTH];
        strcpy(lineCopy, line);
        token = strtok(lineCopy, ",");
        
        
        //token = strtok(line,",");
        while(token != NULL){
            printf("Comparing %s and %s\n", token, values[i]);
            if(strcasecmp(token,values[i]) == 0){
                dingedCount++;
                printf("Match found!\n");
                break;
            }
            else {
                printf("No match found.\n");
            }

            token = strtok(NULL,",");
        }
    }