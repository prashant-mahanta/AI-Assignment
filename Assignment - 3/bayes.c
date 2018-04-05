#include<stdio.h>
#include<math.h>

int main(){

	int train[6670][192],test[3333][192],classLabel_tra[6670],classLabel_test[3333],i,j;
	float bayes[192][5][10]={0},res=0,max=0;
	float class_count[10]={0},a[10]={0};
	int count=0,out,k,h;

	FILE *ft = NULL;
	ft = fopen("pp_tra.dat","r");

	for(i=0;i<6670;i++){
		for(j=0;j<192;j++){
      		fscanf(ft,"%d",&train[i][j]);
    	}
    	fscanf(ft,"%d",&classLabel_tra[i]);
  	}
  	fclose(ft);

  	for(i=0;i<6670;i++){
  		for(j=0;j<192;j++){
  			bayes[j][train[i][j]][classLabel_tra[i]]+=1;
  		}
  		class_count[classLabel_tra[i]]+=1;
  	}
		float bayes2[192][5][10]={0};
  	for(i=0;i<6670;i++){
  		for(j=0;j<192;j++){
  			bayes2[j][train[i][j]][classLabel_tra[i]]=(float)(bayes[j][train[i][j]][classLabel_tra[i]])/class_count[classLabel_tra[i]];
  		}
  	}

  	ft = fopen("pp_tes.dat","r");

  	for(i=0;i<3333;i++){
  		for(j=0;j<192;j++){
  			fscanf(ft,"%d",&test[i][j]);
  		}
  		fscanf(ft,"%d",&classLabel_test[i]);
  	}

  	fclose(ft);

  	for(i=0;i<3333;i++){
  		for(k=0;k<10;k++){
  			res=0;
	  		for(j=0;j<192;j++){
	  			res+=log(bayes2[j][test[i][j]][k]);
  			}
  			res+=log(class_count[k]/6670.0);
				a[k]=res;
  		}
			max=a[0];
			out=0;
			for(h=1;h<10;h++){
				if(max<a[h]){
					max=a[h];
					out=h;
				}
			}
  		if(out==classLabel_test[i]){
				count++;
			}

  	}

  	printf("Accuracy:: %f\n",(count/3333.0)*100);
	return 0;
}
