//koubun.c 
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "others.c"
#include "main.h"
KeyId getToken(); 
void program();
void statement();
void print();
void condition();
void syoki();//初期状態
void zougen();//増減
void expression();
void term();
void factor();
void error2(int i);

KeyId token2;
FILE *fl3;

void koubun(){
  //軸解析が終わって
  fl3=fopen("zisaku_token","r");

  
  token2=getToken();
  
  
  program();
  // token2=getToken();
  // printf("%d\n",token2);
    
  //  printf("%s\n",strTb);//文字列表の出力

  fclose(fl3);
}

void program(){
  /*
  if(token2==Begin){
    token2=getToken();
  }else{
    error();
  }
  
  if(token2==Period){
    token2=getToken();
  }else{
    error();
  }
  
  block();
  
  if(token2==End){
    token2=getTOken();
  }else{
    error();
  }
  
  if(token2=Period){
  }else{
    error();
  }
  */  
  statement();
  
   
    
  if(token2==Period){
  
  }else{
    error2(1);
  }
  
  
}


void statement(){
  switch(token2){
  case Id:
    token2=getToken();
    
    if(token2==Assign){
      token2=getToken();
    }else{
      error2(2);
    }
    
    expression();
    
  
    if(token2==Period){
      token2=getToken();
    }else{
      error2(3);
    }
    
    break;
    
  case If:
    token2=getToken();
    
    if(token2==Lparen){
      token2=getToken();
    }else{
      error2(4);
    }
    
    condition();
    
    if(token2==Rparen){
      token2=getToken();
    }else{
      error2(5);
    }
    
    statement();
    break;
    
    
  case Begin:
    
    token2=getToken();
    
    while(1){
      statement();
      
      if(token2==End){
       
	token2=getToken();
	
	break;
      }
    }
    break;

  case Scan:
   token2=getToken();
    
    if(token2==Lparen){
      token2=getToken();
    }else{
      error2(6);
    }
    
   while(1){
     if(token2==Id){
       token2=getToken();
     }else{
       error2(7);
     }
     
     if(token2!=Comma){
	break;
     }
      token2=getToken();
    }
    
    if(token2==Rparen){
      token2=getToken();
    }else{
      error2(8);
    }
    
    if(token2==Period){
      token2=getToken();
    }else{
      error2(9);
    }   
    break;
   
  case Print:
    token2=getToken();
    
    if(token2==Lparen){
      token2=getToken();
    }else{
      error2(10);
    }
      
    while(1){
      print();
      
      
      if(token2!=Plus){
	
	break;
     }
     token2=getToken();
   }
    
   if(token2==Rparen){
      token2=getToken();
   }else{
     error2(11);
   }
    
   if(token2==Period){
     token2=getToken();
   }else{
     error2(12);
   }   break;
   
  case For:
    token2=getToken();
    if(token2==Lparen){
      token2=getToken();
    }else{
      error2(13);
    }
    
    syoki();
    
    if(token2==Period){
      token2=getToken();
   }else{
     error2(14);
   }
   
    condition();
    
    if(token2==Period){
      token2=getToken();
   }else{
     error2(15);
   }
   
    zougen();
    
    if(token2==Rparen){
      token2=getToken();
   }else{
     error2(16);
   }
   
    statement();
    break;
    
  default:
    break;
  }
  
}
void print(){
    
  switch(token2){
  case Double_Quotation:
    
    token2=getToken();
      
    if(token2==letter){
      token2=getToken();
    }else{
      error2(17);
    }

      
      if(token2==Double_Quotation){
	token2=getToken();
      }else{
	error2(18);
      }
    
      break;
      
  case Id:
    token2=getToken();
    break;
   
  default:
    break;
  }//switch終了
  
}

void condition(){
  expression();
  
  switch(token2){
  case Compare:
    token2=getToken();
    break;
  
  case NotEq:
    token2=getToken();
    break;
    
  case Lss:
  token2=getToken();
    break;

  case Gtr:
    token2=getToken();
    break;
    
  case LssEq:
    token2=getToken();
    break;
    
  case GtrEq:
    token2=getToken();
    break;
  
  default:
    error2(19);
  
  }
  expression();
}


void syoki(){//初期状態
  if(token2==Id){
     token2=getToken();
   }else{
     error2(20);
   }
  
  if(token2==Assign){
    token2=getToken();
  }else{
    error2(21);
   }
  
  if(token2==Num){
    token2=getToken();
  }else{
    error2(22);
  }
  



}
void zougen(){//増減

  if(token2==Id){
    token2=getToken();
  }else{
    error2(23);
  }
  
  switch(token2){
  case PlusPlus:
    token2=getToken();
    break;
  
  case MinusMinus:
    token2=getToken();
    break;
  default:
    error2(24);
  }
}

void expression(){
  
  switch(token2){
  case Plus:
    token2=getToken();
    break;
  
  case Minus:
    token2=getToken();
    break;
  
  default:
    break;
  }
  
  term();
 
  while(1){
    
    if(token2==Plus||token2==Minus){
      token2=getToken();
    }else{
      break;
    }
    
    term();
    
  }
}

void term(){
  
  factor();
  
    while(1){
    
    if(token2==Mult||token2==Div||token2==Remainder){
      token2=getToken();
    }else{
     
      break;
    }
    
    factor();

  }

}

void factor(){
  switch(token2){
  case Id:
    token2=getToken();
    break;
    
  case Num:
    token2=getToken();
    break;
  
  case Lparen:
    token2=getToken();
    
    expression();
    
    if(token2==Rparen){
      //token2=getToken();
    }else{
      error2(25);
    }   
    break;
  default:
    error2(26);
    
  }

}




void error2(int i){

  switch(i){
  case 1:
    printf("beginやendまたは、その周辺にエラーがあります。\n");
    break;
   case 2:
    printf("変数に値を代入するときは <- です。\n");
    break;
   case 3:
    printf("変数代入文にエラーがあります。\n");
    break;
  case 4:
    printf("if文に関するエラー。ifのあとは ( です。\n");
    break;
  case 5:
    printf("if文に関するエラー。条件文及びその周辺にエラーあります。\n");
    break;
  case 6:
    printf("scan文に関するエラー。scanのあとは ( です。\n");
    break;
  case 7:
    printf("scan文に関するエラー。\n");
    break;
  case 8:
    printf("scan文に関するエラー。\n");
    break;
   case 9:
     printf("scan文に関するエラー。scan文の最後にエラーあります。\n");
    break;
   case 10:
    printf("print文に関するエラー。printのあとは ( です。\n");
    break;
   case 11:
    printf("print文に関するエラー。\n");
    break;
   case 12:
    printf("print文に関するエラー。print文の最後にエラーがあります。\n");
    break;
   case 13:
    printf("for文に関するエラー。forのあとは ( です。\n");
    break;
  case 14:
    printf("for文に関するエラー。\n");
    break;
  case 15:
    printf("for文に関するエラー。\n");
    break;
  case 16:
    printf("for文に関するエラー。\n");
    break;
  case 17:
    printf("print文に関するエラー。\n");
    break;
  case 18:
    printf("print文に関するエラー。\n");
    break;
  case 19:
    printf("if文かfor文にエラーがあります。\n");
    break;
  case 20:
    printf("for文に関するエラー。\n");
    break;
  case 21:
    printf("for文に関するエラー。\n");
    break;
  case 22:
    printf("for文に関するエラー。\n");
    break;
  case 23:
    printf("for文に関するエラー。\n");
    break;
  case 24:
    printf("for文に関するエラー。\n");
    break;
 
  case 25:
    printf("エラーがあります。\n");
    break;
  
  case 26:
    printf("エラーがあります。\n");
    break;
  }
  
  
  printf("終了します。error code(%d)\n",i+1);
  exit(0) ;
}
KeyId  getToken(){
  int i;
  fscanf(fl3,"%d",&i);
 
  return (KeyId)i;
}


