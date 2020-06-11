//others.c
/*
  予約語の名前
  Begin  0
  End    1
  Endp	 2 いらん	       
  Scan   3
  Print  4
  Else	 5 いらん 
  If     6
  For    7
  end_of_KeyWd   8

  演算子と区切り記号の名前
  Dollar            9    (&)
  Assign            10   (<-)
  Compare           11   (<-<-)
  Equal             12   (=)使ってない
  Lparen            13    (
  Rparen            14    )
  Period            15   (.)
  Double_Quotation  16   (")
  Plus              17   (+) 
  Minus		    18	 (-)
  Mult              19   (-)
  Div               20   (*)
  Remainder         21   (%)
  Backslash         22   (\)使ってない
  Ln                23   (\\)
  NotEq             24   (-<)
  Comma             25   (.)
  PlusPlus          26   (++)
  MinusMinus        27   (--)
  Lss               28   (<)
  Gtr               29   (>)
  LssEq             30   (<<-)
  GtrEq             31   (><-)
  end_of_KeySym     32   

  トークンの種類
  Id                33
  Num               34
  nul		    35
  end_of_Token,     36
  
  上記以外の文字の種類
  letter           37 文字列
  digit            38 いらん
  colon            39  いらん
  others           40
  mmm	           41  

*/


#define  MAXNAME 31   //identに入るmax文字数　identはnextToken()で使われる
#define  MAXID 128    //変数は１２８個作れる
#define  MAX_IDSTRTB 1024  //変数文字列表のmax領域
typedef  enum  keys {			/*　キーや文字の種類（名前）　*/////////////////////変更あり
  Begin, End,
  Endp,				/*　予約語の名前　*/
  Scan,Print,
  Else,	
  If, For,
  end_of_KeyWd,/*　予約語の名前はここまで　*/
  /*　演算子と区切り記号の名前　*/
  Dollar,
  Assign,Compare, //assigh (<-) compare(<-<-)
  Equal,
  Lparen, Rparen,
  Period,Double_Quotation ,
  Plus, Minus,			
  Mult, Div,
  Remainder, // %
  Backslash,
  Ln,        // (改行)
  NotEq,//(-<)
  Comma,
  PlusPlus,MinusMinus,// (++) (--)
  Lss, Gtr,//(< >)
  LssEq, GtrEq,//(<<- ><-) 
  end_of_keyWdT2,				/*　演算子と区切り記号の名前はここまで　*/
  Id, Num, nul,				/*　トークンの種類　*/
  end_of_Token,
  letter, digit, colon, others,mmm, //=41		/*　上記以外の文字の種類　*/
} KeyId;




struct keyWd {				/*　予約語や記号と名前(KeyId)　*/
	char *word;
	KeyId keyId;
};

static struct keyWd KeyWdT[] = {
	/*　予約語や記号と名前(KeyId)の表　*/
	{"begin", Begin},
	{"end", End},
	{"end.", Endp},
	{"scan", Scan},
	{"print", Print},
	{"else", Else},
	{"if", If},
	{"for", For},
	{"$dummy1",end_of_KeyWd},

};


struct keyWd2 {				/*　予約語や記号と名前(KeyId)　*/
	char *word2;
	KeyId keyId2;
};

static struct keyWd2 KeyWdT2[] = {
	/*　予約語や記号と名前(KeyId)の表　*/
	{"begin", Begin},
	{"end", End},
	{"if", If},    	
	/*　記号と名前(KeyId)の表　*/
       	{"=", Assign},
	{"==", Compare},
	{"(", Lparen},
	{")", Rparen},
	{";\n", Period},//\nも入れたい-------------------------
       	{"+", Plus},
	{"-", Minus},
	{"*", Mult},
	{"/", Div},
      	{"%", Remainder},
	{"\n",Ln},             //注意
     	{"!=",NotEq},
	{"++",PlusPlus},
	{"--",MinusMinus},
	{"<", Lss},
	{">", Gtr},
	{"<=", LssEq},
	{">=", GtrEq},
	{"Id",Id },
	{"Num", Num},
	{"$dummy2",end_of_keyWdT2},

};






//記号表につていーーーーーーーーーーーーーーーーーーーーーー

//変数表
typedef struct Tb{
  int p;
  int cnt;
}Id_Tb;

char IdstrTb[MAX_IDSTRTB];///変数文字列表. 変数名が入る
Id_Tb	Id2[MAXID];//変数は１２８個作れる

int str2[64];//文字は６４個作れる
char strTb[2048];//文字列表

int outId[128];//変数は１２８回出力できる
char outIdTb[1024];//変数出力表

int numTb[128];//数は１２８個作れる 数表
