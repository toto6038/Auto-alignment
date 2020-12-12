//Word Processing
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
//#define DEBUG
char PARA[1500];
int LN=0;   //line number of printed text
int LW; //line width of output lines
int blank_num(int, int*);
int write(int, int);
int main(int argc, char* argv[]){
    int current_line=1;
    LW=atoi(argv[1]);
    char c;
    int i=0;
    while((c=getchar())!=EOF){  //讀到EOF為止
        if(c!='\n'){    //換行代表一段的結束
            PARA[i++]=c;
        }else{
            PARA[i]='\0';   //填完字串後，就在尾巴加上空字元表示結束
            current_line=write(current_line, i);
            memset(PARA,' ',1500);
            i=0;    //index of PARA
        }
    }
    return 0;
}
int blank_num(int pos, int* word){
    *word=0;
    int count=0,current_word=0;
    while(count<=LW-4){
        current_word=0;
        while(PARA[pos++]!=' '){
            count++,current_word++;
        }
        if(PARA[pos-1]==' '){
            *word += 1;
            count++;    //計入單字之間的空格
        }
    }
    count-=current_word;    //因為離開迴圈時，可能會多讀一個單字進來(才讓while的判斷式不成立)，所以把多餘的減回來
    if(current_word>0){
        count-=2, *word-=1; //count減掉多讀進來那個單字的頭尾空格
    }
    return LW-4-count;
}
int write(int line_num,int total_char){
    bool last_line;
    int print_count=0, width=LW-4,i,blank=0, word_count=0, blank_avg=0, mid=0;
    while(PARA[print_count]!='\0'){
        last_line=false;
        for(i=0;i<width;++i){
            if(PARA[print_count+i]=='\0'){
                last_line=true;
                break;
            }
        }
        if(!last_line){
            blank = blank_num(print_count, &word_count);
            blank_avg = 1 + blank/(word_count-1);
        }
        #ifdef DEBUG
        printf("blank=%d\n",blank);
        printf("Word in this line:%d\n", word_count);
        printf("%d",i);
        #endif
        for(i=0;i<width;++i){
            if(i==0){
                //每行開頭
                #ifndef DEBUG
                if((double)line_num/5 - line_num/5 == 0)   printf("%3d ",line_num); //每5行印一次行號
                else    printf("    "); //不印行號時，就直接以空白填充位置
                #endif
                if(line_num<=6){
                    //前六行置中
                    mid=(LW-4)/2;
                    mid=mid-(total_char-1)/2;
                    for(int k=0;k<mid-1;++k){
                        printf(" ");
                    }
                }
            }
            if(!last_line){ //印到每段的最後一行時，不用補空格
                if(PARA[print_count]==' '){
                    if(blank>0){
                        for(int j=0;j<blank_avg && blank>0;++j){
                            blank--,i++;
                            printf(" ");    //補空格
                        }
                    }
                }
            }
            printf("%c", PARA[print_count++]);
            if(PARA[print_count]=='\0') break;  //讀到字串結尾，離開迴圈
        }
        printf("\n");
        if(PARA[print_count]=='\0' && line_num>=6) printf("\n");    //前五行不用分隔每段
        if(PARA[print_count]==' ')  print_count++;  //印完每行的最後一個單字後，下一個字開始前會帶著空格，所以跳過那個空格
        line_num++;
    }
    return line_num;
}