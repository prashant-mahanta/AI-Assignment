#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<float.h>
typedef struct min{
  int class;
  float distance;
}MIN;
int best_k;
// distance between two points
double featureDis(int train[][193],int i,int j){
  double dis=0;

  for(int k=0;k<192;k++){
    int pp=(train[i][k]-train[j][k]);
    dis+=pp*pp;
  }
  double d;
  d=sqrt(dis);
  return d;
}
/*int compare (const void * a, const void * b)
{

  MIN *orderA = (MIN *)a;
  MIN *orderB = (MIN *)b;

  return (int)(orderA->distance - orderB->distance);
}*/
void put(double dist,MIN ksize[],int j){
  double x;
  int y,cj=j;
  for(int l=0;l<25;l++){
      if(dist<ksize[l].distance){
                            x=ksize[l].distance;
                            y=ksize[l].class;
                            ksize[l].distance=dist;
                            ksize[l].class=cj;
                            dist=x;
                            cj=y;
        }
    }
}
//Validation a fold
void valid(int validBlock,int train[][193],int classLabel[],int size,int e[]){
  int start,end,i,j,k;
  start=validBlock*size;end=start+size;
  //in each valid Block
  MIN dist[4447];
  MIN ksize[26];
  int inx=0,error=0;
  double dis;
  for(i=start;i<end;i++){
    //find distance from test Blocks
    for(j=0;j<25;j++){
      ksize[j].distance=DBL_MAX;
      ksize[j].class=-1;
    }
    for(j=0;j<start;j++){
      dis=featureDis(train,i,j);
      put(dis,ksize,j);
    }
    for(j=end;j<6670;j++){
      dis=featureDis(train,i,j);
      put(dis,ksize,j);
    }

    // printf("size= %d\n",inx);
    // for(j=0;j<25;j++){
    //  printf("%lf %d\n",ksize[j].distance,ksize[j].class );
    // }
    //qsort (dist, inx, sizeof(MIN), compare);
    // printf("-----------------\n" );
    //checking class for 1st one
    int count[10];
    for(j=0;j<10;j++){
      count[j]=0;
    }
    for(k=1;k<=25;k++){
      for(j=0;j<k;j++){
        count[classLabel[ksize[j].class]]+=1;
      }
      int max=-1,cj;
      //find nearest neighbour
      for(j=0;j<10;j++){
        if(max<count[j]){
          max=count[j];
          cj=j;
        }
      }
      // if classLabel not equal then increase the error
      if(classLabel[i]!=cj) e[k]+=1;

    }
  }


}
//The main Kth Nearest Neighbour
void knn_fn(int train[][193], int classLabel[]){
  int i,j,k;
  int size = 6670/3;
  int e1[26],e2[26],e3[26];
  int e[26];
  for(i=0;i<26;i++){
    e1[i]=0;e2[i]=0;e3[i]=0;
  }
  //Validate 1st fold
  valid(0,train,classLabel,size,e1);
  //Validate 2nd fold
  valid(1,train,classLabel,size,e2);
  //Validate 3rd fold
  valid(2,train,classLabel,size,e3);

  for(i=1;i<=25;i++){
    e[i]=(e1[i]+e2[i]+e3[i])/3;
    printf("** K= %d ** e: %d, e1: %f, e2: %f, e3: %f  Accuracy: %f\n",i,e[i],((6670-e1[i])/6670.0)*100,((6670-e2[i])/6670.0)*100,((6670-e3[i])/6670.0)*100,((6670-e[i])/6670.0)*100 );
  }
  int min=e[1],kb;
  for(i=1;i<=25;i++){
    if(min>e[i]){
      min=e[i];
      kb=i;
    }
  }
  best_k = kb;

}
//----------------------------------testing------------------------------------------------
//Distance between two points
double Distance(int train[][193],int testC[][193],int i,int j){
  double dis=0;
  for(int k=0;k<192;k++){
    int pp=(train[j][k]-testC[i][k]);
    dis+=(pp*pp);
  }
  double d;
  d=sqrt(dis);
  return d;
}
//testing of the data
int testing(int train[][193],int testC[][193],int classLabel[],int classLabelTest[],int best_k){
  int i,j;
  int error=0;
  MIN ksize[26];
  for(i=0;i<3333;i++){
    double dis=0;
    for(j=0;j<25;j++){
      ksize[j].distance=DBL_MAX;
      ksize[j].class=-1;
    }
    for(j=0;j<6670;j++){
      dis=Distance(train,testC,i,j);
      put(dis,ksize,j);
    }
    int count[10];
    for(j=0;j<10;j++){
      count[j]=0;
    }
      for(j=0;j<best_k;j++){
        count[classLabel[ksize[j].class]]+=1;
      }
      int max=-1,cj;
      //find nearest neighbour
      for(j=0;j<10;j++){
        if(max<count[j]){
          max=count[j];
          cj=j;
        }
      }
      // if classLabel not equal then increase the error
      if(classLabelTest[i]!=cj) error+=1;

  }
  //finally return the error
  return error;
}
//----------------------------------testing ends------------------------------------------

int main(){
  int test=0;
  int train[6671][193],classLabel[6671],classLabelTest[3334],testC[3334][193];
  FILE *ft = fopen("shuffled.dat","r");

  // read the input file. train[][] matrix contains all training dataset of all
  //features and classlabel[] contains their corresponding label
  for(int i=0; i<6670; i++){
    for(int j=0; j<192; j++){
      fscanf(ft,"%d",&train[i][j]);
    }
    fscanf(ft,"%d",&classLabel[test]);
    test++;
  }
  fclose(ft);
  knn_fn(train,classLabel);
  test=0;
  FILE *ft1 = fopen("pp_tes.dat","r");
  for(int i=0; i<3333; i++){
    for(int j=0; j<192; j++){
      fscanf(ft1,"%d",&testC[i][j]);
    }
    fscanf(ft1,"%d",&classLabelTest[test]);
    test++;
  }
  printf("best_k= %d\n",best_k);
  int error=testing(train,testC,classLabel,classLabelTest,best_k);
  printf("\nAccuracy in testing: %f\n",((3333-error)/3333.0)*100);

  return 0;
}
