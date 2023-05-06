while(fgets(line,10*MAX_LINE_LENGTH,fp)){
            char* token = strtok(line," ");
            while(token != NULL){
                
                if(isStrignored(token,ignoreStrs,i)){
                    char *cleanedStr = NULL;
                    cleanedStr = getStrCleaned(token);
                    strcpy(words[z],cleanedStr);
                    z++;
                    puts(cleanedStr);
                
                }                
                token = strtok(NULL," ");
            }
        
        }