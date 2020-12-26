// 平成31年度 春期基本情報試験 午後 問9
// テーマ：入力ファイルを読み込んで、文字コードごとの出現回数を印字するプログラムである。

#include <stdio.h>
//#define InName "h31_kihon_haru.c" /* 入力ファイル名 */
#define InName "nekoneko.c"
/* 配列入れ替えマクロ https://9cguide.appspot.com/c_swap.htmlより */
#define Swap(a,b) ((a != b)? (a += b,b = a - b,a -= b) : 0 )

/* エントリポイント */
int main(){
  FILE *infile;
  int chr,i;// ①
  int ih,ix,code[256];// 設問2より追加
  long cnt;
  long freq[256]; /* freq[i]:文字コードiの出現回数 */

  for(chr=0;chr<= 255;chr++)
    freq[chr] = 0;// 文字配列の初期化

  infile = fopen(InName,"rb");// バイナリファイルの読み込み処理
  cnt = 0;
  while((chr=fgetc(infile)) != EOF){
    cnt++;
    freq[chr]++;
  }
  fclose(infile);

  printf("cnt=%ld | chr=%d\n",cnt,chr);
  printf("%10ld bytes processed\n\n",cnt);// a 何バイト分を読み込んだか表示
  for(i=0;i<64;i++){
    for(chr = i; chr <= i+192;chr+=64){// b,c
      if((0x20 <= chr) && (chr <= 0x7E))
        printf(" %10ld %02X '%c'",freq[chr],chr,chr);
      else
        printf(" %10ld %02X なし",freq[chr],chr);
    }
    printf("\n");
  }
  // ②
  for (i=0;i<=255;i++)
    code[i] = i;
  ih = 255;// ③
  while(ih > 0){// ④ 255回ループ
    ix = 0; //最後の設問
    for (i=0;i<ih;i++){// ⑤
      if(freq[i] < freq[i+1]){// ⑥ 出現回数が多いほどcodeのトップになる。※ihが逆なので注意
        Swap(code[i],code[i+1]);// 文字位置のコピー
        Swap(freq[i],freq[i+1]);// 出現回数のコピー
        //printf("Swap：code[%d]='%c' <==> code[%d]='%c' \n",i,code[i],i+1,code[i+1]);
        //printf("      freq[%d]='%ld' <==> freq[%d]='%c' \n",i,freq[i],i+1,(int)freq[i+1]);
        ix=i;// ⑦
        //printf("%d\n",i);
      }
    }
    //ih--;// ⑧
    ih=ix;
    printf("%d\n",ih);
  }
  printf("\n");
  for(i=0;i<64;i++){
    for(chr = i; chr <= i+192;chr+=64){
      if((0x20 <= code[chr]) && (code[chr] <= 0x7E))
        printf(" %10ld %02X '%c'",freq[chr],code[chr],code[chr]);
      else
        printf(" % 10ld %02X ", freq[chr],code[chr]);
    }
    printf("\n");
  }
}





/*
void Swap(int *x,int *y){
  int temp;
  temp = *x;// xが指す変数の値を退避
　*x = *y;// yが指す変数の値をxが指す変数に代入
　*y = temp;// tempに退避しておいたxが指す変数の値をyが指す変数に代入
}
*/