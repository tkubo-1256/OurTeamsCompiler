//means.c
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "others.c"
#include "main.h"

#define N 128
KeyId getToken2();

KeyId Token2;
FILE *fl4;
FILE *fl5;
FILE *fl6;
int point_outIdTb2=0;//変数出力表の添字
int outIdnum2=0;//何回目に変数を出力するか
int point_IdstrTb2=0;//変数文字列表の添字
int Idnum2=0;//変数の個数
int point_numTb2=0;//数表の添字
  

void put_IdstrTb();
void put_outIdTb();
void de();
void means(){
  //  printf("means starts\n");
  int strnum2=0;//文字列の個数
  int point_strTb2=0;//文字列表のポインタ
  fl4=fopen("cLang.c","w");
  fl5=fopen("zisaku_token","r");


  //上をいれる
  fprintf(fl4,"#include<stdio.h>\nmain(){\n");
  
  //変数の定義をcLang.cへ挿入
  if(Idnum!=0){
    int y;
    fprintf(fl4,"int ");
    for(y=0;y<Idnum;y++){
      put_IdstrTb();
      if(y==Idnum-1){
	break;
      }
      fprintf(fl4,",");	 
    }
    fprintf(fl4,";\n");
  }

  
  Token2=getToken2();//beginをとばす
  Token2=getToken2();//１文字先取りで考える
  while(1){
    switch(Token2){
    case Begin:
      Token2=getToken2();
      fprintf(fl4,"{\n");
      break;
      
    case End:
      Token2=getToken2();
      fprintf(fl4,"}\n");
      
      if(Token2==Period){
	goto END;
      }
      break;
    case Scan:
      Token2=getToken2();//(をとる
      Token2=getToken2();//変数をとる
      Token2=getToken2();//,か
      int i=0;
      int j=0;
      while(Token2==Comma){
	i++;
	Token2=getToken2();//変数とる
	Token2=getToken2();//,か
	
      }

      
      fprintf(fl4,"scanf(\"%%");
      fprintf(fl4,"d");
      for(j=0;j<i;j++){
	fprintf(fl4,",%%");
	fprintf(fl4,"d");
      }
      fprintf(fl4,"\",&");
      
    
      put_outIdTb();
   
      
     
      
      for(j=0;j<i;j++){
	fprintf(fl4,",&");
	put_outIdTb();
	
      }
      
      fprintf(fl4,");\n");
      Token2=getToken2();//ピリオドとる
      Token2=getToken2();//１文字先取り

      break;
      
      
    case Print:
      Token2=getToken2();// (とる
      
      do{
	Token2=getToken2();// " or $ or )をとる    
	if(Token2==Double_Quotation){
	  char str3[128];
	  int i3=str2[strnum2++];
	  int i4=0;
	  while(strTb[i3]!='&'){
	    str3[i4++]=strTb[i3++];
	   
	  }
	  str3[i4]='\0';
	  
	  
	  fprintf(fl4,"printf(\"");
	  if(strcmp(str3,"\\\\")==0){
	    
	    fprintf(fl4,"\\");
	    fprintf(fl4,"n");
	  }else{

	  fprintf(fl4,"%s",str3);
	  }
	  fprintf(fl4,"\");\n");
	  Token2=getToken2();//文字列とる
	  Token2=getToken2();//"とる
	  Token2=getToken2();//+or)をとる
	  
	}else{
	  //変数ならば
	  fprintf(fl4,"printf(\"%%");
	  fprintf(fl4,"d\",");
	  put_outIdTb();
	  fprintf(fl4,");\n");
	  Token2=getToken2();//+ or )
	}	  
      }while(Token2==Plus);
      Token2=getToken2();//ピリオドとる
      Token2=getToken2();//先取りで
      
      
      break;
      
    case For:
      Token2=getToken2();//(とる
      Token2=getToken2();// .orその他をとる
      fprintf(fl4,"for(");
      
      while(Token2!=Period){	
	de();
	
	//printf("%d\n",Token2);
      }
   
      fprintf(fl4,";");
      Token2=getToken2();
      while(Token2!=Period){
	de();
      }
      fprintf(fl4,";");
      Token2=getToken2();
      
      break;


    case Id:
      Token2=getToken2();
      put_outIdTb();
      break;
    
    case Num:
      fprintf(fl4,"%d",numTb[point_numTb2++]);
      Token2=getToken2();
      break;
    
    default:
      de();
      break;
    }
  }
      
  
 END:
  
  //できました
  //cLang();//実行
  
  fclose(fl4);
  fclose(fl5);
  
  //  printf("正常終了\n");
}

KeyId  getToken2(){
  int i;
   fscanf(fl5,"%d",&i);
   
   return (KeyId)i;
}

void put_IdstrTb(){
  char str4[128];
  int ii3=Id2[Idnum2++].p;
  int ii4=0;
  while(IdstrTb[ii3]!='&'){
    str4[ii4++]=IdstrTb[ii3++];
    
  }
  str4[ii4]='\0';
 
  fprintf(fl4,"%s",str4);

  

}

void put_outIdTb(){
  
  char str4[128];
  int ii3=outId[outIdnum2++];
  int ii4=0;
  while(outIdTb[ii3]!='&'){
    str4[ii4++]=outIdTb[ii3++];
    
  }
  str4[ii4]='\0';
 
  fprintf(fl4,"%s",str4);
}      
      
void de(){
  int i;
  for (i=0; i<end_of_keyWdT2; i++){
    if (Token2==KeyWdT2[i].keyId2) {
      if(Token2==Id){
	put_outIdTb();
      }else if(Token2==Num){
	fprintf(fl4,"%d",numTb[point_numTb2++]);
      }else{
	fprintf(fl4,"%s",KeyWdT2[i].word2);
      }
     //cToken = temp; printed = 0;
      Token2=getToken2();
      break;
    
    }
  
  }
  
}

