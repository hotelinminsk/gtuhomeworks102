#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <math.h>

/*DEFINE */
#define MAX_WORD_SIZE 35
#define MAX_NUM_WORDS 1002
#define MAX_VEC_SIZE 200
#define MAX_LINE_LENGTH 1000000
/*DEFINE END*/

/*STRLEN FUNCTION'S MY VERSION */
int strLenght(char  *str){
    int l=0;
    while(str[l] != '\0'){
        l++;
    }

    return l;
}

/*STRCPY FUNCTIONS MUADIL*/
void strcopy(char *dest, const char *src) {
    int i;
    while((*dest++ = *src++)!='\0');
    *dest = '\0';


}

/*A FUNCTION TO CHECK IF THE COMING WORD FROM INPUT.TXT IS IGNORED OR NOT */
int isStrignored(char *str,char ignoreStrs[][MAX_WORD_SIZE],int numToigno){
    for(int i=0;i<numToigno;i++){
        if(strcmp(str,ignoreStrs[i]) == 0){
            //STR IS INSIDE THE IGNORE TXT SO RETURN 0;
            return 0;
        }
    }

    return 1;
}


/*CLEANING THE STRING FROM UNWANTED CHARACTERS*/
char* getStrCleaned(char* str){
    int count =0;
    char* cleanStr = (char*)malloc((120) * sizeof(char));
    while(*str != '\0'){
        char comingChar = *str;
        if(isalnum(comingChar)){

            cleanStr[count++] = tolower(comingChar);/*GETTING ALL STRS LOWERCASE*/
        }
        str++;
    }
    cleanStr[count] = '\0';
    int i=0;
    return cleanStr;
}



/*DOUBLE DISSIMALIRTY FUNCTION FOR CHECK CLOSENESS OF TWO WORDS*/
double doubledissimilarity(char *w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int *position_of_orginalword){

    float vector_w1[200],vector_w2[200];  /*WORD 1 AND WORD 2 S VECTOR ARRAYS*/
    FILE *fp = fopen("dictionary.txt","r");
    if(fp==NULL){
        puts("cant open the file");
        return -1;
    }

    char word[50]; /*coming word from dictionary.txt*/
    int w1_count = 0;
    while(fscanf(fp,"%s",word)== 1){
        if(strcmp(w1,word)==0){  /*if coming word is equal to given word take vector values and break the loop*/

            while(fscanf(fp,"%f",&vector_w1[w1_count++])){
                if(w1_count==200){
                    break;
                }
            }
            break;
        }
    }

    int w2_count =0;
    rewind(fp);
    char word2[50];
    while(fscanf(fp,"%s",word2)==1){
        if(strcmp(word2,w1) == 0){/*coming word is equal to w1 continue because it will give the same text*/
            continue;
        }
        if(strcmp(w2,word2)==0){ /*if coming word fro m dictionary.txt is equal to w2 take the vector values and break the loop*/
            while (fscanf(fp,"%f",&vector_w2[w2_count++]))
            {
                if(w2_count==200){
                    break;
                }
            }
            break;
            
        }
    }
    fclose(fp);
    double sum=0.0;
    for(int i=0;i<w1_count;i++){ /*distance formula*/
        sum += (vector_w1[i] - vector_w2[i])*(vector_w1[i] - vector_w2[i]);
    }
    
    
    sum = sqrt(sum); /*sqrt of sum*/
    
    if(1/sum >threshold){ 
        return 1/sum; /*return the inverse of sum*/
    }
    else{
        return -1;
    }
    

}

/*READING THE INPUT.TXT FILE AND PUTTING CLEAN STRS IN WORDS ARRAY*/
int  read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){
    int numOflinesIgnore =0;
    FILE *ignoreF = NULL;
    words[MAX_LINE_LENGTH][MAX_WORD_SIZE];
    ignoreF=fopen(ignore_file,"r");
    FILE *textF = fopen(text_file,"r");
    if(ignoreF!=NULL){
        char temp[MAX_LINE_LENGTH];
        while(fgets(temp,MAX_LINE_LENGTH,ignoreF)){
            numOflinesIgnore++; /*counting the lines in ignore.txt  before creating ignore strs array*/
        }
        rewind(ignoreF);
        char ignoreStrs[numOflinesIgnore][MAX_WORD_SIZE];/*creating ignore str array*/
        int i=0;
        char line[MAX_LINE_LENGTH];
        while(fgets(line,MAX_LINE_LENGTH,ignoreF)){
            sscanf(line,"%s",ignoreStrs[i]); /*getting ignored strs in array*/
            i++;
        }

        char comingChar;
        char comingStr[50];
        char cleanStr[50];
        int count = 0;
        int j=0;
        fclose(ignoreF);/*closing the file connection*/
        while(feof(textF) == 0){
           
            comingChar = fgetc(textF);
            
            if(isalnum(comingChar)){
                cleanStr[count++] = comingChar;
            }

            if(comingChar == 32 || comingChar == '\n'){
                cleanStr[count] = '\0';
                count = 0;
                if(strlen(cleanStr) >0){
                    
                    if(isStrignored(cleanStr,ignoreStrs,i)){
                        
                        strcopy(words[j],cleanStr);
                        
                        j++;
                    }

                }
            }

            
            

        }
        strcpy(words[j],"-");/*copiying the sentinel value*/
        
        return j;
        


    }else{
        printf("Error oppening file!");
    }

}



/*READ DICTIONARY function */
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
    FILE *fp = fopen(file_name,"r");/*opening the file*/
    int numWords=0;
    int vecTorSize=0;
    if(fp!=NULL){
        int numofwords =0;
        char line[MAX_LINE_LENGTH];
        fgets(line,MAX_LINE_LENGTH,fp);
        sscanf(line,"%*[^0-9]%d%*[^0-9]%d",&numWords,&vecTorSize);
        //printf("numofwords = %d, vectorsize= %d",numWords,vecTorSize);
        while(fgets(line,MAX_LINE_LENGTH,fp)){
            sscanf(line,"%s",dict[numofwords]);
            
            numofwords++;
        }

        dict[numofwords+1][0] = '-';  /* sentinel values*/
        dict[numofwords+1][1] = '\0'; /* null terminator */

        int m =0;

        return numofwords;
        }else{
            return -1;
        }
}



/*function to check if given word is in dictionary or not*/
int checkIfInDict(char *word,char dict[][MAX_WORD_SIZE],int *dictPosition){
    int walker = 0;
    int found=-1;
    while(dict[walker][0] != '-'){
        if(strcasecmp(word,dict[walker])==0){
            puts("Found.");/*word is found */
            found = walker;
            return 1;
            break;
        }
        walker++;
    }
    
    *dictPosition = found;
    return 0;
}


/*a function to check */
int checkTheBook(char *word,char book[][MAX_WORD_SIZE],int *matchCount){
    
    int exactMatch =0;

    int walker = 0;
    while(strcmp(book[walker],"-") != 0){
        if(strcmp(word,book[walker]) == 0){
            exactMatch++;

        }
        walker++;

    }

    *matchCount = exactMatch;
    
}

/*a function to finding scale of occurences*/
int scaleFind(const int occurence[],int n){
    int max=0;

    for(int i=0;i<n;i++){
        if(occurence[i]>max){
            max = occurence[i];
        }
    }
    max = max/20;
    
    
    if(max>1){
        return max;
    }
    else{
        return 1;
    }
}

/*histogram function*/
int histogram(const char words[][MAX_WORD_SIZE],const int occurrences[], const char hist[][MAX_WORD_SIZE+5+20]){
    
    int histlen = 0;
    int scale =0;


    while(hist[histlen][0] != '-'){
        histlen++;
    }
    
    


    scale = scaleFind(occurrences,histlen/2);

    
    puts("----------------------------------------------");
    puts("Histogram");
    printf("Scale : %d\n",scale);
    puts("----------------------------------------------");


    int jumpR = histlen/2;
    for(int i=0;i<jumpR;i++){
        if(hist[i+jumpR][0] != '\0'){
            printf("\n%s -> %s: ",hist[i],hist[i+jumpR]);
            if(occurrences[i] > 0){
                for(int a=0;a<occurrences[i]/scale;a++){
                printf("+");
                 }
            }else{
                printf("no matches.");
            }
            
        }else{
            printf("\n%s: ",hist[i]);
            if(occurrences[i]>0){
                if(occurrences[i] > 0){
                for(int a=0;a<occurrences[i]/scale;a++){
                printf("*");
                 }
            }else{
                printf("no matches.");
            }
            }
            
        }
    }
    


}


/*a function to call doubledissimilarity function and return similar word*/
char*  histcreator(char *word1,char dict[][MAX_WORD_SIZE]){
    int m = 0;
    int bbeg =0;
    double max = 0.0;
    int position = 0;
    if(checkIfInDict(word1,dict,&m)){
        puts("Computing");
        for(int i = 0;dict[i][0] != '-';i++){
            double sum = doubledissimilarity(word1,dict[i],dict,0.15,&bbeg);

            if(sum!=0){
                if(sum>max){
                    max = sum;
                    position = i;
                }
            }
        }

        return dict[position];
        
    }

}


/* main function */
int main(int argc,char *argv[]){
    static char dict[MAX_NUM_WORDS][MAX_WORD_SIZE];  /*initializing needed arrays*/
    static char words[300000][MAX_WORD_SIZE];
    int vectorSize,wordsLen; 
    char *dictionaryfile = "dictionary.txt";
    char *inputfile = "input.txt";
    char *ignorefile = "ignore.txt";
    
    
    char input[100];
    char inputCopy[100];
    int numofwords = read_dict(dictionaryfile,dict);
    read_text(inputfile,ignorefile,words);
    printf("Enter word(s): ");
    fgets(input,100,stdin);
    strcopy(inputCopy,input);
    int i=0;
    int wordCount=0;
    int indexCounter = 0;
   
    //COUNTING INPUTTED WORDS
    char *token = strtok(input," ");
    while(token !=NULL){
        wordCount++;
       // puts(token);
        token = strtok(NULL," ");
    }
    
    //PUTTING INPUTS IN ENTEREDWORDS ARRAY
    int matchCount[wordCount];
    char enteredWords[wordCount][MAX_WORD_SIZE];

    token = strtok(inputCopy," ");
    
    //WE PUT THE COMING INPUTS INSIDE EVERY enteredwordsarray
    while(token !=NULL){
        char *temp;
        temp = getStrCleaned(token);
        strcopy(enteredWords[indexCounter],temp);
        indexCounter++;
        token = strtok(NULL," ");

    }

    

    char similarWords[wordCount][MAX_WORD_SIZE];/*creating an array for any similar words*/
    for(int i = 0;i<wordCount;i++){
        similarWords[i][0] = '\0'; /*initilazing every  index of similarwords array to 0*/
    }
    
    int occurenceExact[wordCount];
    int CoccurenceExact[wordCount];  /*arrays for occurences*/
      /*arrays for occurences*/
    int similarOccurence[wordCount];
    for(int i=0;i<wordCount;i++){
        similarOccurence[i] = 0;
    }
    
//FIRST WE CHECK IF THE GIVEN WORD IS IN THE INPUT FILE ITSELF, IF IT IS WE INCREMENT THE EXACTHMATCH INTEGER ON THE WORD OBJECT ITSELF 
    
    for(int a=0;a<wordCount;a++){
        
        int exactMatch =0;
        
        checkTheBook(enteredWords[a],words,&exactMatch);
        occurenceExact[a] = exactMatch;
        CoccurenceExact[a] = exactMatch;

    }
    
// NOW WE HAVE TO CHECK IF ANYWORD'S EXACT MATCH INT IS LESS THAN 1 IF THAT WE GONNA USE DICTIONARY

    int posofOriginal = 0;
    int m=0;
    int positionofCloseone =0;
   float minsimilarity = -1;
   int j=0;

    char history[wordCount*2][60];
    
    for(int i = 0; i<wordCount;i++){
        char *returnedname;
        int similarmatch = 0;
        int tempint =0;
        if(occurenceExact[i] == 0 && checkIfInDict(enteredWords[i],dict,&tempint)){  /*IF WORDS EXACT MATCH IS EQUAL TO ZERO and given word is in dictionary */
        returnedname = histcreator(enteredWords[i],dict);
        strcopy(similarWords[i],returnedname);
        checkTheBook(returnedname,words,&similarmatch);
        CoccurenceExact[i]=similarmatch;
        similarOccurence[i]=similarmatch;}


    }
    enteredWords[wordCount][0] = '0';
    
    
    int wcopy = wordCount*2;
    int index = 0;
    for(int i=0; i<wordCount;i++){
        strcopy(history[i],enteredWords[i]);
        index++;
    }

    for (int i = wordCount - 1; i >= 0; i--) {
    strcopy(history[wcopy - 1], similarWords[i]);
    wcopy--;
    index++;
    if (index == wordCount * 2) {
        break;
    }
}
    

    history[wordCount*2][0] = '-';

    if(wordCount>1){
    
        histogram(words,CoccurenceExact,history);
    
    
    

    }
    else{
        if(occurenceExact[0]>0){
            printf("The word '%s' occured %d times in text.",enteredWords[0],occurenceExact[0]);
        }else{
            if(similarOccurence[0]>0){
            printf("The word '%s' doesnt appear in text but word '%s' appears %d times.",enteredWords[0],similarWords[0],similarOccurence[0]);

            }else{
                printf("The word '%s' doesnt appear in text.",enteredWords[0]);
            }
        }
    }
}