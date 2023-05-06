#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <math.h>

#define MAX_WORD_SIZE 35
#define MAX_NUM_WORDS 1001
#define MAX_VEC_SIZE 200
#define MAX_LINE_LENGTH 100000

static char words[300000][MAX_WORD_SIZE];
struct inputWord{
    int exactMatch;
    int similarCount;
    char *wordText;
    double *vectorValues;
    int dictionaryPosition;
    
};

typedef struct inputWord inputW;

int strLenght(char  *str){
    int l=0;
    while(str[l] != '\0'){
        l++;
    }

    return l;
}


void strcopy(char *dest, const char *src) {
    int i;
    while((*dest++ = *src++)!='\0');
    *dest = '\0';


}


int isStrignored(char *str,char ignoreStrs[][MAX_WORD_SIZE],int numToigno){
    for(int i=0;i<numToigno;i++){
        if(strcmp(str,ignoreStrs[i]) == 0){
            //STR IS INSIDE THE IGNORE TXT SO RETURN 0;
            return 0;
        }
    }

    return 1;
}

char* getStrCleaned(char* str){
    int count =0;
    char* cleanStr = (char*)malloc((120) * sizeof(char));
    while(*str != '\0'){
        char comingChar = *str;
        if(isalnum(comingChar)){

            cleanStr[count++] = tolower(comingChar);
        }
        str++;
    }
    cleanStr[count] = '\0';
    int i=0;
    return cleanStr;
}

int closestInText1(inputW word,char fwords[][MAX_WORD_SIZE],char dict[][MAX_WORD_SIZE]){
    int walker=0;
    int walkerDict= 0;
    int positionOfWd = 0;
    while(strcmp(fwords[walker],"-")!=0){
        while(strcmp(dict[walkerDict],"-") != 0){
            
        }
    }
}


double doubledissimilarity(char * w1, char * w2, char dict[][MAX_WORD_SIZE], float threshold, int *position_of_orginalword ){
    puts("gets called dd");
    int i=0;
    double vectorsoforiginal[200];
    double vectors2[200];
    char *matchIndict;
    //w1 is input word, w2 is dict[i];
    
    
    //first take the original words vector values
    int linecount=0;
    FILE *fp = fopen("dictionary.txt","r");
    char templine[MAX_LINE_LENGTH];
    fgets(templine,MAX_LINE_LENGTH,fp);//jumping over the first line
    while(fgets(templine,MAX_LINE_LENGTH,fp)){
        char *token = strtok(templine," ");

        if(strcasecmp(token,w1)==0){
            token = strtok(NULL," ");
            int vectorindex = 0;
            while (token != NULL)
            {
                double tempvalue = 0.0;
                sscanf(token,"%lf",&tempvalue);
                vectorsoforiginal[vectorindex++] = tempvalue;
                token = strtok(NULL," ");
            }
            
        }   
        linecount++;
    }

    
    //WE TAKE THE ORIGINAL WORDS VECTORS.
    //NOW WE HAVE TO TAKE COMING WORD'S VECTORS
    int vInd=0;
    rewind(fp);
    fgets(templine,MAX_LINE_LENGTH,fp);//jumpoverthe firstline
    while(fgets(templine,MAX_LINE_LENGTH,fp)){
        char *token = strtok(templine," ");
        if(strcasecmp(token,w2)==0){
            int vectorindex = 0;
            while(token != NULL){
                double tempvalue=0.0;
                sscanf(token,"%lf",&tempvalue);
                vectors2[vectorindex++] = tempvalue;
                if(vectorindex==98){
                    token = strtok(NULL,"\n");
                }
                else{
                    token = strtok(NULL," ");

                }
            }

            
            break;
        }


    }

    //now we have to calculate the dissimilarity between 2 vectors
    double sum=0.0;
    for(int i=0;i<100;i++){
       //printf("vectororginal = %lf,vectors2 = %lf\n",vectorsoforiginal[i],vectors2[i]);
       sum += fabs((vectorsoforiginal[i] - vectors2[i]) * (vectorsoforiginal[i] - vectors2[i]));

    }

    //double distance = sqrt(sum);
    sum = sqrt(sum);
    //printf("Distance between = %s, %s is = %lf\n",w1,w2,sum);
    
    return sum;

}


int  read_text(const char  * text_file, const char  * ignore_file, char words[][MAX_WORD_SIZE]){
    int numOflinesIgnore =0;
    FILE *ignoreF = NULL;
    words[MAX_LINE_LENGTH][MAX_WORD_SIZE];
    ignoreF=fopen(ignore_file,"r");
    FILE *textF = fopen(text_file,"r");
    if(ignoreF!=NULL){
        char temp[MAX_LINE_LENGTH];
        while(fgets(temp,MAX_LINE_LENGTH,ignoreF)){
            numOflinesIgnore++;
        }
        rewind(ignoreF);
        char ignoreStrs[numOflinesIgnore][MAX_WORD_SIZE];
        int i=0;
        char line[MAX_LINE_LENGTH];
        while(fgets(line,MAX_LINE_LENGTH,ignoreF)){
            sscanf(line,"%s",ignoreStrs[i]);
            i++;
        }

        char comingChar;
        char comingStr[50];
        char cleanStr[50];
        int count = 0;
        int j=0;
        fclose(ignoreF);
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
        strcpy(words[j],"-");
        //words[j][1] = '\0';
        
        return j;
        


    }else{
        printf("Error oppening file!");
    }

}



/*READ DICTIONARY*/
int read_dict(const char * file_name, char dict[][MAX_WORD_SIZE]){
    FILE *fp = fopen(file_name,"r");
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

        dict[numofwords][0] = '-';
        dict[numofwords][1] = '\0';

        int m =0;

        return numofwords;
        }else{
            return -1;
        }
}




int checkIfInDict(char *word,char dict[][MAX_WORD_SIZE],int *dictPosition){
    int walker = 0;
    int found=-1;
    while(dict[walker][0] != '-'){
        if(strcasecmp(word,dict[walker])==0){
            puts("Found.");
            found = walker;
            break;
        }
        walker++;
    }
    
    *dictPosition = found;

}

int checkTheBook(char *word,char book[][MAX_WORD_SIZE],int *matchCount){
    
    int exactMatch =0;

    int walker = 0;
    while(strcmp(book[walker],"-") != 0){
        if(strcmp(word,book[walker]) == 0){
            
           (*matchCount) += 1;

        }
        walker++;

    }

    
    
}

int main(int argc,char *argv[]){
    char dict[1002][MAX_WORD_SIZE];
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
    inputW *inputsa = (inputW*)malloc(wordCount*sizeof(inputW));

    char enteredWords[wordCount][35];

    token = strtok(inputCopy," ");
    
    //WE PUT THE COMING INPUTS INSIDE EVERY INPUTW STRUCT
    while(token !=NULL){
        char *temp;
        inputsa[indexCounter].wordText = (char*)malloc(35 * sizeof(char));
        temp = getStrCleaned(token);
        strcopy(inputsa[indexCounter].wordText,temp);
        strcopy(enteredWords[indexCounter],temp);
        indexCounter++;
        token = strtok(NULL," ");

    }

    


//FIRST WE CHECK IF THE GIVEN WORD IS IN THE INPUT FILE ITSELF, IF IT IS WE INCREMENT THE EXACTHMATCH INTEGER ON THE WORD OBJECT ITSELF 
    for(int a=0;a<wordCount;a++){
        
        inputsa[a].exactMatch = 0;
        int pTocount = inputsa[a].exactMatch;
        int *posP = &inputsa[a].dictionaryPosition;
        char *ptoWord = inputsa[a].wordText;
        checkTheBook(ptoWord,words,&pTocount);
        printf("exact match = %d",pTocount);
    }

// NOW WE HAVE TO CHECK IF ANYWORD'S EXACT MATCH INT IS LESS THAN 1 IF THAT WE GONNA USE DICTIONARY

    int posofOriginal = 0;
    checkIfInDict(enteredWords[0],dict,&posofOriginal);
        if(posofOriginal > 0){
            puts("dictionaryde var");
            for(int m=0;m<1001;m++){
                double sum;
                sum = doubledissimilarity("pigling",dict[m],dict,2.0,&posofOriginal);

                printf("distance between = %s,%s is = %lf\n",enteredWords[0],dict[m],sum);
            }
            
        }
    
    /*
    for(int b=0;b<wordCount;b++){
        checkIfInDict(inputsa[b].wordText,dict,&inputsa[b].dictionaryPosition);
        if(inputsa[b].dictionaryPosition > 0){
            puts("dictionaryde var");
            posofOriginal = inputsa[b].dictionaryPosition;
            for(int m=0;m<1001;m++){
                double sum;
                sum = doubledissimilarity(inputsa[b].wordText,dict[m],dict,2.0,&posofOriginal);

                printf("distance between = %s,%s is = %lf\n",inputsa[b].wordText,dict[m],sum);
            }
            
        }
    }
    
    */
    //NOW WE GONNA SEND THE MATCHED STRING IN DIRECTORY TO DISSIMILARITY FUNCTION,


    

    
}