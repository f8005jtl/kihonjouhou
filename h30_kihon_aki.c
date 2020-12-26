// 平成30年度 秋期基本情報試験 午後 問9
// テーマ：路線構成の鉄道模型における列車の運行をシミュレーションするプログラムである。

#include<stdio.h> // printf使いたいので追加
#include<stddef.h> // 基本的なマクロや定数を定義 stdio.hがあれば不要

#define RED (0) // 信号機に表示する色の定義
#define GREEN (1)

// -------------------
// 構造体
// -------------------
// 鉄道模型の列車情報
struct train_info{
  int number;// 列車の番号
  struct block_info* dest;// 列車の終着駅を出口とする区間
};

// 鉄道模型の区間情報
struct block_info{
  int n;// printf確認用に使用した
  struct train_info* train;// 区間内にいる列車を表現した
  struct block_info* next[2];// 次区間(出口で接続する区間)を表現した
  int signal;// 信号機に表示する色(RED or GREEN)
};

// -------------------
// プロトタイプ宣言
// -------------------
// ヌルチェック
int nullcheck(void*);
// 信号点灯処理
void set_signals(struct block_info[],int);
// 最終区間に到達したか
int find_block(struct block_info*,struct block_info*);
// 進行できる列車がいるかどうか
void proceed(struct block_info[],int);
// プログラムの実行
void start(struct block_info[],int);

int nullcheck(void *n){
  if(n == NULL){
    return 0;
  }
  return 1;
}

void set_signals(struct block_info blocks[],int nblocks){
  int i;
  struct block_info* block;
  for(i=0;i<nblocks;i++){
    block=&blocks[i];
    if(block->train==NULL){ // a
      block->signal = GREEN;
    }
    else{
      block->signal = RED;
    }
  }
}
int find_block(struct block_info* block,struct block_info* dest){
  int i;
  if(block == dest){// 同じ区間か
    return 1;
  }
  for(i=0;i<2;i++){
    if(block->next[i]==NULL){
      continue;
    }
    if(find_block(block->next[i],dest)==1) {// d
      return 1;
    }
  }
  return 0;
}

void proceed(struct block_info blocks[],int nblocks){
  int i,j;
  struct block_info* block;
  // 区間ノードの表示
  printf("区間の処理前\n");
  printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
  printf("・block_info\n");
  printf(" | 区間  ");for(int k=0;k<9;k++)printf(" | 区間%d",k);printf(" | \n");
  printf(" |train  ");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].train)?blocks[k].train->number:999);printf(" | \n");
  printf(" |next[0]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[0])?blocks[k].next[0]->n:999);printf(" | \n");
  printf(" |next[1]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[1])?blocks[k].next[1]->n:999);printf(" | \n");
  printf(" |signal ");for(int k=0;k<9;k++)printf(" |%5s ",blocks[k].signal ? "GREEN" : "RED");printf(" | \n");
  printf("------------------------------------------------------------------------------------------\n");

  for(i=nblocks-1; i>=0; i--){
    block = &blocks[i];
    if(block->train == NULL){// 列車が区間内にいるか
      continue;// 進行しない
    }
    if(block == block->train->dest){// b 終着区間の処理
      block->train = NULL;// 路線上から取り除く
      continue;
    }
    for(j=0;j<2;j++){
      if(block->next[j]==NULL){
        continue;
      }
      if(block->next[j]->signal==RED){// 信号が赤
        continue;
      }
      if(find_block(block->next[j],block->train->dest) == 1){// 終着区間か(同じ区間か)
        block->next[j]->train=block->train;
        block->next[j]->signal = RED;
        block->train = NULL;
        break;// c
      }
    }
    /*
    // 区間ノードの表示
    printf("区間%dの処理後\n",i);
    printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
    printf("・block_info\n");
    printf(" | 区間  ");for(int k=0;k<9;k++)printf(" | 区間%d",k);printf(" | \n");
    printf(" |train  ");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].train)?blocks[k].train->number:999);printf(" | \n");
    printf(" |next[0]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[0])?blocks[k].next[0]->n:999);printf(" | \n");
    printf(" |next[1]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[1])?blocks[k].next[1]->n:999);printf(" | \n");
    printf(" |signal ");for(int k=0;k<9;k++)printf(" |%5s ",blocks[k].signal ? "GREEN" : "RED");printf(" | \n");
    printf("------------------------------------------------------------------------------------------\n");*/
  }
  // 区間ノードの表示
  printf("区間の処理後\n");
  printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
  printf("・block_info\n");
  printf(" | 区間  ");for(int k=0;k<9;k++)printf(" | 区間%d",k);printf(" | \n");
  printf(" |train  ");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].train)?blocks[k].train->number:999);printf(" | \n");
  printf(" |next[0]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[0])?blocks[k].next[0]->n:999);printf(" | \n");
  printf(" |next[1]");for(int k=0;k<9;k++)printf(" |%4d  ",nullcheck(blocks[k].next[1])?blocks[k].next[1]->n:999);printf(" | \n");
  printf(" |signal ");for(int k=0;k<9;k++)printf(" |%5s ",blocks[k].signal ? "GREEN" : "RED");printf(" | \n");
  printf("------------------------------------------------------------------------------------------\n");
}
void start(struct block_info blocks[],int nblocks){
  int i;
  set_signals(blocks,nblocks);
  for(i=0;i<4;i++){
    proceed(blocks,nblocks);
    set_signals(blocks,nblocks);
  }
}

// エントリポイント
int main(){
  // 区間ノードの生成
  struct block_info kukans[] = {{0,NULL,NULL,NULL,0},{1,NULL,NULL,NULL,0},{2,NULL,NULL,NULL,0},{3,NULL,NULL,NULL,0},
    {4,NULL,NULL,NULL,0},{5,NULL,NULL,NULL,0},{6,NULL,NULL,NULL,0},{7,NULL,NULL,NULL,0},{8,NULL,NULL,NULL,0}};

  // 列車ノードの生成
  struct train_info trains[] = {{0,NULL},{1,NULL},{2,NULL},{3,NULL},{4,NULL}};

  // 各ノードに「次の場所」を追加(区間)
  kukans[0].train = &trains[4];
  kukans[1].train = &trains[3];
  kukans[3].train = &trains[2];
  kukans[4].train = &trains[1];
  kukans[8].train = &trains[0];

  kukans[0].next[0] = &kukans[2];
  kukans[1].next[0] = &kukans[2];
  kukans[2].next[0] = &kukans[3];
  kukans[3].next[0] = &kukans[4];
  kukans[3].next[1] = &kukans[7];
  kukans[4].next[0] = &kukans[5];
  kukans[4].next[1] = &kukans[6];
  kukans[7].next[0] = &kukans[8];

  // 各ノードに「次の場所」を追加(列車)
  trains[0].dest = &kukans[8];
  trains[1].dest = &kukans[5];
  trains[2].dest = &kukans[6];
  trains[3].dest = &kukans[5];
  trains[4].dest = &kukans[8];

  // 区間ノードの表示
  printf("信号点灯処理 実行前  ※999はNULLです。\n");
  printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
  for(int i=0;i<9;i++){
    printf("区間%d | train=&列車%3d | next[0]=&区間%3d next[1]=&区間%3d | signal=%s \n",i,nullcheck(kukans[i].train)?kukans[i].train->number:999,nullcheck(kukans[i].next[0])?kukans[i].n:999,nullcheck(kukans[i].next[1])?kukans[i].n:999,kukans[i].signal ? "GREEN" : "RED");
  }
  printf("------------------------------------------------------------------------------------------\n");
  for(int i=0;i<5;i++){
    printf("列車%d | number=%d | dest=&区間%d \n",i,trains[i].number,nullcheck(trains[i].dest)?trains[i].dest->n:999);
  }
  printf("------------------------------------------------------------------------------------------\n\n");

  // 信号点灯処理
  set_signals(kukans,9);

  // 区間ノードの表示
  printf("信号点灯処理 実行後  ※999はNULLです。\n");
  printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
  for(int i=0;i<8;i++){
    printf("区間%d | train=&列車%3d | next[0]=&区間%3d next[1]=&区間%3d | signal=%s \n",i,nullcheck(kukans[i].train)?kukans[i].train->number:999,nullcheck(kukans[i].next[0])?kukans[i].n:999,nullcheck(kukans[i].next[1])?kukans[i].n:999,kukans[i].signal ? "GREEN" : "RED");
  }
  printf("------------------------------------------------------------------------------------------\n");
  for(int i=0;i<5;i++){
    printf("列車%d | number=%d | dest=&区間%d \n",i,trains[i].number,nullcheck(trains[i].dest)?trains[i].dest->n:999);
  }
  printf("------------------------------------------------------------------------------------------\n\n");

  // 進行できる列車がいるかどうか
  proceed(kukans,9);
/*
  // 区間ノードの表示
  printf("進行処理 実行後  ※999はNULLです。\n");
  printf("▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽▽\n");
  for(int i=0;i<8;i++){
    printf("区間%d | train=&列車%3d | next[0]=&区間%3d next[1]=&区間%3d | signal=%s \n",i,nullcheck(kukans[i].train)?kukans[i].train->number:999,nullcheck(kukans[i].next[0])?kukans[i].n:999,nullcheck(kukans[i].next[1])?kukans[i].n:999,kukans[i].signal ? "GREEN" : "RED");
  }
  printf("------------------------------------------------------------------------------------------\n");
  for(int i=0;i<5;i++){
    printf("列車%d | number=%d | dest=&区間%d \n",i,trains[i].number,nullcheck(trains[i].dest)?trains[i].dest->n:999);
  }
  printf("------------------------------------------------------------------------------------------\n\n");
*/
  return 0;
}
