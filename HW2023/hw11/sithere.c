#include <stdio.h>
#include <stdlib.h>

struct student{
    char *name;
    int id;
    int age;
};

typedef struct student Stu;


void main(void){
    Stu yahya;
    yahya.name = (char*)malloc(sizeof(char) * 25);
    puts("Give an student name");

    scanf("%[^\n]",yahya.name);
    puts("Give an student id");
    scanf("%d",&yahya.id);
    puts("Give an student age");
    scanf("%d",&yahya.age);



    FILE *fp = fopen("student1.dat","wb");
    fwrite(&yahya,sizeof(Stu),1,fp);

    fclose(fp);
    

    fp = fopen("student1.dat","rb");
    char name[25];
    int age1;
    int id1;
    Stu newStu;
    fread(&newStu,sizeof(Stu),1,fp);

    printf("%s\t%d\t%d\n",newStu.name,newStu.id,newStu.age);


}