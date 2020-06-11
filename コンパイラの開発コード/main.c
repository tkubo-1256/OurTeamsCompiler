//main.c 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "others.c"
#include "koubun.h"
#include "means.h"
#define MAXNAME 31			/*　名前の最大長さ　*/
#define MAXLINE 120		/*　１行の最大文字数　*/
#define MAXNUM 14		/*　定数の最大桁数　*/
static int lineIndex=-1;			/*　次に読む文字の位置　*/
static char ch;				/*　最後に読んだ文字　*/
static char line[MAXLINE];	/*　１行分の入力バッファー　*/



int strnum;//文字列の個数
int point_strTb;//文字列表の添字

int point_IdstrTb;//変数文字列表の添字
int Idnum;//変数の個数

int point_outIdTb;//変数出力表の添字
int outIdnum;//何回目に変数を出力するか

int point_numTb;//数表の添字

KeyId token;
FILE *fl2;
FILE *fl2_2;
FILE *fl2_3;
KeyId nextToken();
char nextChar();
void error(int i);

static KeyId charClassT[256];		/*　文字の種類を示す表にする　*/

static void initCharClassT()		/*　文字の種類を示す表を作る関数　*/
{
	int i;
	for (i=0; i<256; i++)
		charClassT[i] = others;
	for (i='0'; i<='9'; i++)//0は文字コード９６
		charClassT[i] = digit;
	for (i='A'; i<='Z'; i++)
		charClassT[i] = letter;
	for (i='a'; i<='z'; i++)
		charClassT[i] = letter;
	//othersの定義をする

	charClassT['$']=Dollar;       
	charClassT['"']=Double_Quotation;
	charClassT['%']=Remainder;
	charClassT['+'] = Plus; charClassT['-'] = Minus;
	charClassT['*'] = Mult; charClassT['/'] = Div;
	charClassT['('] = Lparen; charClassT[')'] = Rparen;
	charClassT['='] = Equal; charClassT['<'] = Lss;
	charClassT['>'] = Gtr; charClassT[','] = Comma;
	charClassT['.'] = Period; 
	charClassT['\\'] = Backslash; 
	charClassT['\n'] = mmm;//終了合図 
	
	
}



char str[MAXLINE];
main(){
  
  FILE *fl;
  
  strnum=0;//文字列の個数
  point_strTb=0;//文字列表のポインタ
  point_IdstrTb=0;//変数文字列表の添字
  Idnum=0;//変数の個数
  point_outIdTb=0;//変数出力表の添字
  outIdnum=0;//何回目に変数を出力するか
  point_numTb=0;//数表の添字
  
  initCharClassT();
  printf("自作言語を書き込んだファイル名を入力してください。\n");
  char filename[128];    
  scanf("%s",filename);
  
  fl=fopen(filename,"r");
  if(fl==NULL){
    printf("%s not open!\ncomfirm!!!\n",filename);
    exit(0);
  }
  
  fl2=fopen("zisaku_token","w");
  //fl2_2=fopen("Idtable","w");
  while(fgets(str,sizeof(str),fl)!=NULL){
   
   
    ch=str[0];//1文字先読み
    do{
      token=nextToken();
      if(token==others){
	error(0);
      }
      if(token!=mmm&&token!=others){
	fprintf(fl2, "%d ", token);
      }
      if(ch=='\0'){ 
	goto EEND;
      }
    } while(token!=mmm);//(\n)が帰ってきたらその列は終了。
    fprintf(fl2,"\n");
  }
 EEND:
  fclose(fl2);
  
  printf("字句解析終了\n");
  //構文解析
  koubun();
  printf("構文解析終了\n");
  

  //意味解析
  means();
  printf("意味解析終了\n");
  
  

  fclose(fl);
  //  fclose(fl2_2);
  //printf("%s\n",IdstrTb);//変数文字列表の内容

  printf("正常終了です。\nzisaku_tokenに自作言語のtokenが書き込まれています。\ncLang.cに命令が書き込まれています。実行してください。\n");
}


char nextChar()				/*　次の１文字を返す関数　*/
{

	if (lineIndex == -1){
	  int ii;
	  for(ii=0;str[ii]!='\0';ii++){
	    line[ii]=str[ii];
	  }
	  line[ii]='\0';
	  //	  strcpy(line,str);
	  lineIndex = 1;
	  
	}
	if ((ch = line[lineIndex++]) == '\n'){	 /*　chに次の１文字　*/
		lineIndex = -1;				/*　それが改行文字なら次の行の入力準備　*/
		return '\n';				/*　文字としては改行文字を返す　*/
	}
	return ch;
}

KeyId nextToken()			/*　次のトークンを読んで返す関数　*/
{
	int i = 0;
	int num;
	KeyId cc;
	KeyId temp;
	char ident[MAXNAME];
	while (1){				/*　空欄を捨てる　*/
	  if (ch == ' '){
	    ch=nextChar();
	  }else{
	    break;
	  }
	}
	
		
	switch (cc = charClassT[ch]) {//cc=(begin=0・・の)表のどれか
	case letter: 				
		do {
			if (i < MAXNAME)
				ident[i] = ch;
			i++; ch = nextChar();
		} while (  charClassT[ch] == letter);
		if (i >= MAXNAME){
		  printf("too long error\n");
		  //errorMessage("too long");
			i = MAXNAME - 1;
		}	
		ident[i] = '\0';
	     
		
		int i4=0;
		for (i=0; i<end_of_KeyWd; i++){
			if (strcmp(ident, KeyWdT[i].word) == 0) {
			  
			  temp= KeyWdT[i].keyId;/*　予約語の場合　*/
				//cToken = temp; printed = 0;
				i4=1;
				break;
			}
		}
		if(i4!=1){
		  error(1);
		}
		break;
	case Dollar://変数
	        do {
		  if (i < MAXNAME){
			  if(ch!='$'){ 
			    ident[i] = ch;
			    i++;
			  }
			ch = nextChar();
		  }
		} while (  charClassT[ch] == letter|| charClassT[ch] == digit );
		if (i >= MAXNAME){
		  printf("too long error\n");
		  //errorMessage("too long");
			i = MAXNAME - 1;
		}	
		ident[i] = '\0'; //EOS
	       
		temp= Id;		/*　ユーザの宣言した名前の場合　*/
		
		//まず変数出力表に変数をいれる
		int j;
		outId[outIdnum++]=point_outIdTb;
		for(j=0;j<i;j++){
		  outIdTb[point_outIdTb+j]=ident[j];
		}
		point_outIdTb+=j;
		outIdTb[point_outIdTb++]='&';
	       
		
		

		j=0;	
		//変数文字列表に変数が入っているかどうか確かめる
		if(Idnum!=0){
		  int s=0,z=0;//z:変数文字列表の添字
		  char str2[128];
		  for(s=0;s<Idnum;s++){
		    z=Id2[s].p;
		    j=0;
		    while(IdstrTb[z]!='&'){
		      str2[j++]=IdstrTb[z++];
		    }
		    
		    str2[j]='\0';
		    
		    if(strcmp(str2,ident)==0){
		      goto bk;//今回きた変数が既に、変数文字列表に入っているなら、下の操作をとばす
		    
		    }
		  } 
		}
		
		//なければ、変数文字列表に変数をいれる
		Id2[Idnum++].p=point_IdstrTb;
		for(j=0;j<i;j++){
		  IdstrTb[point_IdstrTb+j]=ident[j];
		}
		point_IdstrTb+=j;
		IdstrTb[point_IdstrTb++]='&';
		
		
		break;

	bk:	break;
	  
       
	case digit: 					/* number */
		num = 0;
		do {
			num = 10*num+(ch-'0');
			i++; ch = nextChar();
		} while (charClassT[ch] == digit);
      		if (i>MAXNUM)
		  printf("too large error\n");
		  //errorMessage("too large");
      		temp= Num;
		  //numに値がある
		
		//数表にいれる
		numTb[point_numTb++]=num;
		break;
	//①受理かnullのもの (例 \\)

	case Double_Quotation:
	  
	  ch=nextChar();
	  if(ch!='+'&&ch!=')'){
	    fprintf(fl2,"%d ",Double_Quotation);
	    //文字列表に加える			
	        i=0;		
		temp=letter;
		while(charClassT[ch]!=Double_Quotation){	   
		    ident[i++]=ch;	 
		    ch=nextChar();
     
		}
		//printf("%d\n",i);
	       
		int t=0;
		str2[strnum++]=point_strTb;

		for(t=0;t<i;t++){
		  strTb[point_strTb+t]=ident[t];
		}
		point_strTb+=t;
		strTb[point_strTb++]='&';
	
	  }
	  else{
	    temp=Double_Quotation;
	  }
	  break;
	  
     	case Backslash:
	  
	  if ((ch = nextChar()) == '\\') { /* (\のとき) */
			ch = nextChar();
			temp= letter;		/* "\\" */
		       
			
			// \nを文字列表に加える
			str2[strnum++]=point_strTb;
			strTb[point_strTb++]='$';
			strTb[point_strTb++]='$';
			strTb[point_strTb++]='$';
			
			strTb[point_strTb++]='&';
			
			break;
	  } else {
	    error(0);
			
			break;
		}
        
       
        //②複数のもの（例 - -< --） 
	case Lss:
	  if ((ch = nextChar()) == '<') {
	    if (ch = nextChar() == '-') {	
	      temp= LssEq;/*　"<<-"　*/	
	      ch=nextChar();
	      break;
	    }else   error(0);
	    
	  }else if (ch == '-') {
	    ch = nextChar();
	    if(ch == '<'){
	      ch=nextChar();
	      if(ch=='-'){
		temp=Compare;/*　"<-<-"　*/
		ch=nextChar();
		break;
	      }else  error(0);
	      
	    }else{
	    temp= Assign;		/*　"<-"　*/
	    
	    break;
	    }
	  }else{ 
	    temp= Lss;           /*　"<"　*/
	    break;
	  }
	  
       
	  
	case Gtr:
	  if ((ch = nextChar()) == '<') {
	    ch = nextChar();
	    if(ch=='-'){      
	      temp = GtrEq;		/*　"><-"　*/
	      ch=nextChar();
	      break;
	    } else error(0);
	  }else{
	    temp = Gtr;
	    break;
	  }
	
	case Plus:
		if ((ch = nextChar()) == '+') {
			ch = nextChar();
			temp = PlusPlus;		/*　"++"　*/
			break;
		} else {
			temp = Plus;
			break;
		}

	case Minus:
		if ((ch = nextChar()) == '-') {
			ch = nextChar();
			temp = MinusMinus;		/*　"--"　*/
			break;
		} else if (ch == '<') {
			ch = nextChar();
			temp = NotEq;		/*　"-<"　*/
			break;
		} else {
			temp = Minus;
			break;
		}

        case mmm:
	  temp=cc;break;
	  
	  
	default:
		temp= cc;
		ch = nextChar(); break;
	}

	return temp;
}

void error(int i) {
  
  switch(i){
  case 0:
    printf("予約語にない文字列や定義されていない記号が使われています。error code(0)\n");
    exit(0);
    
  case 1:
    printf("予約語のスペルが間違っています。error code(1)\n");
    exit(0);
  }

}
