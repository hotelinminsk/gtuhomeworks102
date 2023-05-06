int x=0;
   int counter=0;
    while(fgets(line,MAX_LINE_LENGTH,fp)){
        if(x==1){
            break;
        }
        char *token = strtok(line," ");
        while(token != NULL){
            char *cleanedStr;
            cleanedStr = getStrCleaned(token);
            puts(cleanedStr);
            if(strcmp(cleanedStr,word) == 0){
                *matchCount = *matchCount + 1;
                counter++;
                puts("they are same");
                x=1;
            }
            

            token = strtok(NULL," ");
        }
        

    }
