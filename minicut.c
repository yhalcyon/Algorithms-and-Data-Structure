/*
 * C++ program implementing the karger minicut algorithm
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "ran.c"

#define NODE 200
#define EDGE 3000
#define loop 400000

int main(){

  FILE *fp;
  int i,j,k,m,n,g,h,pick,tempm,tempn;
  int a[NODE][EDGE];
  int a1[NODE][EDGE];
  int length[NODE];
  int length1[NODE];
  int Edges[20000][2];
  int node = 200;
  int index;
  int edge;
  int min=10000;
  long totaledge;
  char temp[500];
  
  int flag;
  char * pch;


    srand((unsigned)time(NULL));
    for(i=0;i<NODE;i++){
      for(j=0;j<EDGE;j++){
	a1[i][j] = NODE+1;
      }
      length1[i] = 0;
    }
    do{
    fp = fopen("data","r");
    }while(fp == NULL);
    
    i = 0;
    while(fgets(temp,500,fp)){
      if(temp[0] < '0' || temp[0] > '9') break;
      j = 0;
      index = 0;
      while(temp[index] != '\r'){
	if(temp[index] != '\t'){
	  a1[i][j] = atoi(temp+index);
	  if(a1[i][j] < 10) index++;
	  else if(a1[i][j] < 100) index+=2;
	  else index+=3;
	  j++;
	}
	else
	  {
	    index++;
	  }
      }
      length1[i] = j-1;
      i++;
    }

  
  for(k=0;k<loop;k++){
    i = rand();
    i = I_ran4(i);
    for(i=0;i<NODE;i++){
      for(j=0;j<EDGE;j++){
	a[i][j] = a1[i][j];
      }
      length[i] = length1[i];
    }

/*     for(i=0;i<NODE;i++){ */
/*       for(j=0;j<=length[i];j++){ */
/* 	printf("%d\t",a[i][j]); */
/*       } */
/*       printf("\r\n"); */
/*     } */
    
    for(node=NODE;node>2;node--){
      totaledge = 0;
      for(i=0;i<node;i++){
	for(j=1;j<=length[i];j++){
	  Edges[totaledge][0] = a[i][0];
	  Edges[totaledge][1] = a[i][j];
	  totaledge++;
	}
      }
      pick = (int)(ran()*totaledge);
      tempm = Edges[pick][0];
      tempn = Edges[pick][1];
      for(i=0;i<node;i++){
	if(a[i][0] == tempm) m = i;
	if(a[i][0] == tempn) n = i;
      }
      for(j=1;j<=length[m];j++){
	if(a[m][j] == a[n][0]){
	  a[m][j] = a[m][length[m]];
	  length[m]--;
	  j--;
	}
      }
      for(j=1;j<=length[n];j++){
	if(a[n][j] == a[m][0]){
	  a[n][j] = a[n][length[n]];
	  length[n]--;
	  j--;
	}
      }

      if(m<n)
	{
	  for(g=0;g<node;g++){
	    for(h=1;h<=length[g];h++){
	      if(a[g][h] == a[n][0]) a[g][h] = a[m][0];
	    }
	  }
	  for(j=1;j<=length[n];j++){
	    a[m][length[m]+j] = a[n][j];
	  }
	  length[m] += length[n];
	  for(j=0;j<=length[node-1];j++){
	    a[n][j]=a[node-1][j];
	  }
	  length[n] = length[node-1];	  
	}
      else{
	for(g=0;g<node;g++){
	  for(h=1;h<=length[g];h++){
	    if(a[g][h] == a[m][0]) a[g][h] = a[n][0];
	  }
	}
	for(j=1;j<=length[m];j++){
	  a[n][length[n]+j] = a[m][j];
	}
	length[n] += length[m];
	for(j=0;j<=length[node-1];j++){
	  a[m][j]=a[node-1][j];
	}
	length[m] = length[node-1];
      }
    }
    if(node != 2)
      {
	printf("Error!");
	exit(0);
      }    
    edge = (length[0] + length[1])/2;
    if(edge<min) min=edge;
  }
  printf("The mini cut is: %d\n",min);
}
  



