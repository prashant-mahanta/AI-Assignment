//-----------3 Layer Neural Network using ANSI C------------------------------//
//Prashant Kumar Mahanta
//201601066
//Wasim Ishaq Khan
//201601107
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<limits.h>
#include<math.h>
#include<time.h>
# define epoch 100
int readFile(int train[][17], char fileName[], int actualOutput[]){
	FILE *fp;
	int i=0, j=0, k=0, l=0;
	int Class_Label, x_box, y_box, width, height, onpix, x_bar, y_bar, x2bar, y2bar, xybar, x2ybr, xy2br, x_ege, xegvy, y_ege, yegvx;  
	char data[1000];
	char *token;
	fp = fopen(fileName, "r");
	while((fscanf(fp, "%[^\n]s", data))==1){
		if(i!=0){
			j=0;	
			l=0;
			token = strtok(data, "\","); //split
			while(token!=NULL){
				switch(j){
					case 0:
						Class_Label = atoi(token);
						actualOutput[k] = Class_Label;
						train[k][l] = 1;
						//printf("%d\n", Class_Label);
						break;
					case 1:
						x_box = atoi(token);
						train[k][l] = x_box;
						//printf("%d\n", x_box);
						break;
					case 2:
						y_box = atoi(token);
						train[k][l] = y_box;
						//printf("%d\n", y_box);
						break;
					case 3:
						width = atoi(token);
						train[k][l] = width;
						//printf("%d\n", width);
						break;
					case 4:
						height = atoi(token);
						train[k][l] = height;
						//printf("%d\n", height);
						break;
					case 5:
						onpix = atoi(token);
						train[k][l] = onpix;
						//printf("%d\n", onpix);
						break;
					case 6:
						x_bar = atoi(token);
						train[k][l] = x_bar;
						//printf("%d\n", x_bar);
						break;
					case 7:
						y_bar = atoi(token);
						train[k][l] = y_bar;
						//printf("%d\n", y_bar);
						break;
					case 8:
						x2bar = atoi(token);
						train[k][l] = x2bar;
						//printf("%d\n", x2bar);
						break;
					case 9:
						y2bar = atoi(token);
						train[k][l] = y2bar;
						//printf("%d\n", y2bar);
						break;
					case 10:
						xybar = atoi(token);
						train[k][l] = xybar;
						//printf("%d\n", xybar);
						break;
					case 11:
						x2ybr = atoi(token);
						train[k][l] = x2ybr;
						//printf("%d\n", x2ybr);
						break;
					case 12:
						xy2br = atoi(token);
						train[k][l] = xy2br;
						//printf("%d\n", xy2br);
						break;
					case 13:
						x_ege = atoi(token);
						train[k][l] = x_ege;
						//printf("%d\n", x_ege);
						break;
					case 14:
						xegvy = atoi(token);
						train[k][l] = xegvy;
						//printf("%d\n", xegvy);
						break;
					case 15:
						y_ege = atoi(token);
						train[k][l] = y_ege;
						//printf("%d\n", y_ege);
						break;
					case 16:
						yegvx = atoi(token);
						train[k][l] = yegvx;
						//printf("%d\n", yegvx);
						break;
				}
				j++;
				l++;
				token = strtok(NULL, "\",");
			}
			k++;
			fseek(fp, 2, 1);
		}
		if(i==0){
			fseek(fp, 2, 1);	
		}
		++i;
	}
	return k;
}

void setWeight(float weightInputHidden[][9], float weightHiddenOutput[][10], int layer){
	int i;
	srand(time(NULL));
	for(i=0;i<17;++i){
		for(int j=0;j<layer;++j){
		weightInputHidden[i][j] = (float)(rand() % 4 - 1)/100;
		}
	}

	for(i=0;i<layer+1;++i){
		for(int j=0;j<10;++j){
		weightHiddenOutput[i][j] = (float)(rand() % 4 - 1)/100;
		}
	}

	/*for(i=0;i<17;++i){
		for(int j=0;j<layer;++j){
			printf("%f ", weightInputHidden[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<layer;++i){
		for(int j=0;j<10;++j){
			printf("%f ", weightHiddenOutput[i][j]);
		}
		printf("\n");
	}*/
}

float sigmoid(float x){
     float exp_value;
     float return_value;
     exp_value = exp((double) -x);
     return_value = 1 / (1 + exp_value);
     return return_value;
}

int indexMax(float multiply2[][10], int m, int n){
	int index = 0;
	float max =  multiply2[0][0];
	for(int i=0;i<m;++i){
		for(int j=1;j<n;++j){
			if(multiply2[i][j]>max){
				max = multiply2[i][j];
				index = j;
			}
		}
	}
	return index;
}

void trainPerceptron_1(int train[][17], int len, int actualTrainOutput[], float weightInputHidden[][9], float weightHiddenOutput[][10], int layer){
	int temp[17], i=0, c=0, d, k, l, index, j;
	float  multiply1[1][9], sigmoid_bar[1][9], sum = 0, multiply2[1][10], diff[1][10], trainOutput[1][10], output[1][10], hiddenOutput[9][10],
	deltaInput[1][9], hiddenInput[17][9], deltaK[10][1], outputTemp[1][10], lRate = 0.001;
	for(int to=0;to<epoch;++to){
		for(int i=0;i<len;i++){
			sum=0;
	      for(d=0;d<layer;d++){	
	        for(k=0;k<17;k++) {
	          sum=sum+(float)train[i][k]*weightInputHidden[k][d];
	        }
	        multiply1[c][d] = sum;	//1*5
	        sum = 0;
	      }
	      
	      for(l=0;l<1;++l){					//y
	      	for(k=0;k<layer+1;++k){
	      		if(l==0 && k==0){
	      			sigmoid_bar[l][k] = 1;	
	      		} else{
	      			sigmoid_bar[l][k] = (float)sigmoid(multiply1[l][k-1]);
	      		}
	      	}
	      }
	     for(l=0;l<1;l++) {					
	      for(d=0;d<10;d++) {
	        for(k=0;k<layer+1;k++) {
	          sum = sum + (float)sigmoid_bar[l][k]*weightHiddenOutput[k][d];
	        }
	        multiply2[l][d] = sum;	//1*10
	        sum = 0;
	      }
	    }
	    for(l=0;l<1;++l){		//f(netk)
	      	for(k=0;k<10;++k){
	      		output[l][k] = sigmoid(multiply2[l][k]);
	      		multiply2[l][k] = sigmoid(multiply2[l][k]);
	      	}
	      }

	      for(l=0;l<1;++l){			//f'(netk)
	      	for(k=0;k<10;++k){
	      		multiply2[l][k] = multiply2[l][k]*(1 - multiply2[l][k]);
	      	}
	      }

	    for(k=0;k<10;++k){			//actual output
	    	if((actualTrainOutput[i] - 1)==k){
	    		trainOutput[0][k] = 1.0;
	    	} else{
	    		trainOutput[0][k] = 0.0;
	    	}
	    }
	    for(l=0;l<1;++l){			//difference
	      	for(k=0;k<10;++k){
	      		diff[l][k] = trainOutput[l][k] - output[l][k];
	      	}
	    }
	    for(l=0;l<10;++l){			//deltaK   
	      		deltaK[l][0] = diff[0][l]*multiply2[0][l];
	    }
	    sum = 0;
	    for(l=0;l<layer+1;l++) {		//delta_wkj			
	      for(d=0;d<10;d++) {
	          hiddenOutput[l][d] = lRate*sigmoid_bar[0][l]*deltaK[0][d];
	      }
	    }
	     for(l=0;l<layer+1;++l){
	    	for(j=0;j<10;++j){
	    		weightHiddenOutput[l][j] = weightHiddenOutput[l][j] + hiddenOutput[l][j];
	    	}
	    }
	    sum = 0;
	    for(l=0;l<layer+1;++l){
	    	sigmoid_bar[0][l] = sigmoid_bar[0][l]*(1 - sigmoid_bar[0][l]);
	    }
	    for(j=1;j<layer+1;++j){				//deltaInput
	    	for(int r=0;r<10;++r){
	    		sum+=deltaK[r][0]*weightHiddenOutput[r][j]*sigmoid_bar[0][j];
	    	}
	    	deltaInput[0][j-1] = sum;
	    	sum = 0;
	    }
	    //(17*1 * 1*5)
	    for(l=0;l<17;++l){				//delta_wji
	    	for(k=0;k<layer;++k){
	    		hiddenInput[l][k] = lRate*train[i][l]*deltaInput[0][k];
	    	}
	    }
	    for(l=0;l<17;++l){
	    	for(j=0;j<layer;++j){
	    		weightInputHidden[l][j] = weightInputHidden[l][j] + hiddenInput[l][j];
	    	}
	    }
	}
	}
}
void testPerceptron(int test[][17], int len, int actualTestOutput[998], float weightInputHidden[][9], float weightHiddenOutput[][10], int layer, int flagg){
	float hiddenOutput[1][9], sigmoid_hidden[1][9], output[1][10], sum=0;
	int i, d, k, l, index, testOutput[1][10], flag=0, count=0;
	for(i=0;i<len;++i){
		sum=0;
	    for(d=0;d<layer;d++){	
	        for(k=0;k<17;k++) {
	          sum=sum+(float)test[i][k]*weightInputHidden[k][d];
	        }
	        hiddenOutput[0][d] = sum;	//1*5
	        sum = 0;
	      }					
	    for(k=0;k<layer+1;++k){		//y
	      		if(l==0 && k==0){
	      			sigmoid_hidden[0][k] = 1;	
	      		} else{
	      			sigmoid_hidden[0][k] = (float)sigmoid(hiddenOutput[0][k-1]);
	      	}
	    }
	    for(l=0;l<1;l++) {					
	      for(d=0;d<10;d++) {
	        for(k=0;k<layer+1;k++) {
	          sum = sum + (float)sigmoid_hidden[l][k]*weightHiddenOutput[k][d];
	        }
	        output[l][d] = sum;	//1*10
	        sum = 0;
	      }
	    }
	    for(l=0;l<1;++l){		//f(netk)
	      	for(k=0;k<10;++k){
	      		output[l][k] = sigmoid(output[l][k]);
	      	}
	      }
	      index = indexMax(output, 1, 10);
	    for(l=0;l<1;++l){		//function output
	    	for(k=0;k<10;++k){
	    		if(k!=index){
	    		output[l][k] = 0;
	    		}else{
	    			output[l][k] = 1;
	    		}	
	    	}
	    }
	    for(k=0;k<10;++k){			//actual output
	    	if((actualTestOutput[i] - 1)==k){
	    		testOutput[0][k] = 1;
	    	} else{
	    		testOutput[0][k] = 0;
	    	}
	    }

	    for(k=0;k<10;++k){
	    	if(testOutput[0][k] != output[0][k]){
	    		flag=1;
	    		break;
	    	}
	    }
	    if(flag==0){
	    	//if(count == 0)
	    		//printf("%d \n", actualTestOutput[i]);
	    	count++;
	    }
	    flag=0;
	}
	if(flagg==0){
		printf("Total matches using loss function as standard mean square loss and stopping criterion as %d epoches: %d\n", count, epoch);
		printf("The number of neurons in the hidden layer are: %d\n", layer);
		printf("The accuracy is: %f\n\n", (float)((count*100.0)/(float)999));
	}else{
		printf("Total matches using entropy loss are: %d\n", count);
		printf("The number of neurons in the hidden layer are: %d\n", layer);
		printf("The accuracy is: %f\n\n", (float)((count*100.0)/(float)999));		
	}
}
void trainPerceptron_2(int train[][17], int len, int actualTrainOutput[], float weightInputHidden[][9], float weightHiddenOutput[][10], int layer){
	int temp[17], i=0, c=0, d, k, l, index, j, epochi = 0;
	float  netj[1][8], sigmoid_hidden[1][9], sum = 0, multiply2[1][10], diff[1][10], trainOutput[1][10], sigmoid_output[1][10], hiddenOutput[9][10], 
	deltaInput[1][9], hiddenInput[17][9], deltaOutput[10][1], outputTemp[1][10], lRate = 0.001, sigmoid_diff_output[1][10], sigmoid_diff_input[1][9],
	sumWeightInputHidden[17][9], sumWeightHiddenOutput[9][10], weightHiddenOutputTemp[9][10], normih=10, normho=0, epsilon = 0.001, average = 0.015; 
	int count = 0;
	while(1){
		epochi++;
		for(l=0;l<17;++l){				
	   		for(k=0;k<layer;++k){
	    		sumWeightInputHidden[l][k] = 0.0;
	   		}
		}
		for(l=0;l<layer+1;++l){				
	   		for(k=0;k<10;++k){
	    		sumWeightHiddenOutput[l][k] = 0.0;
	   		}
		}
		//count = 0;
		for(int i=0;i<len;i++){
			sum=0;
	      for(d=0;d<layer;d++){	
	        for(k=0;k<17;k++) {
	          sum=sum+(float)train[i][k]*weightInputHidden[k][d];
	        }
	        netj[c][d] = sum;	//1*5
	        sum = 0;
	      }
	      
	      for(l=0;l<1;++l){					//y
	      	for(k=0;k<layer+1;++k){
	      		if(l==0 && k==0){
	      			sigmoid_hidden[l][k] = 1;	
	      		} else{
	      			sigmoid_hidden[l][k] = (float)sigmoid(netj[l][k-1]);
	      		}
	      	}
	      }
	      for(k=0;k<10;++k){		//f'(netk)
	      	sigmoid_diff_input[0][k] = sigmoid_hidden[0][k]*(1 - sigmoid_hidden[l][k]);
	      	}
	     for(l=0;l<1;l++) {					
	      for(d=0;d<10;d++) {
	        for(k=0;k<layer+1;k++) {
	          sum = sum + (float)sigmoid_hidden[l][k]*weightHiddenOutput[k][d];
	        }
	        multiply2[l][d] = sum;	//1*10
	        sum = 0;
	      }
	    }
	    for(l=0;l<1;++l){		//f(netk)
	      	for(k=0;k<10;++k){
	      		sigmoid_output[l][k] = sigmoid(multiply2[l][k]);
	      	}
	      }

	      for(l=0;l<1;++l){			//f'(netk)
	      	for(k=0;k<10;++k){
	      		sigmoid_diff_output[l][k] = sigmoid_output[l][k]*(1 - sigmoid_output[l][k]);
	      	}
	      }
	    for(k=0;k<10;++k){			//actual output
	    	if((actualTrainOutput[i] - 1)==k){
	    		trainOutput[0][k] = 1.0;
	    	} else{
	    		trainOutput[0][k] = 0.0;
	    	}
	    }
	    for(l=0;l<1;++l){			//difference
	      	for(k=0;k<10;++k){
	      		deltaOutput[l][k] = trainOutput[l][k] - sigmoid_output[l][k];
	      	}
	    }
	    sum = 0;
	    for(l=0;l<layer+1;l++) {		//delta_wkj			
	      for(d=0;d<10;d++) {
	          hiddenOutput[l][d] = lRate*sigmoid_hidden[0][l]*deltaOutput[0][d];
	      }
	    }
	    for(l=0;l<layer+1;++l){
	    	for(j=0;j<10;++j){
	    		weightHiddenOutputTemp[l][j] = weightHiddenOutput[l][j] + hiddenOutput[l][j];
	    	}
	    }
	    sum = 0;
	    int r;
	    for(j=0;j<layer+1;++j){				//deltaInput
	    	for(r=0;r<10;++r){
	    		//sum+=deltaOutput[r][0]*weightHiddenOutputTemp[j][r]*sigmoid_diff_output[0][r];
	    		sum+=deltaOutput[r][0]*weightHiddenOutput[j][r]*sigmoid_diff_input[0][r];
	    	}
	    	deltaInput[0][j] = sum;
	    	//printf("%f ", sum);
	    	//printf("%f ", deltaInput[0][j]);
	    	sum = 0;
	    }
	   // printf("\nhjhj\n");
	    //break;
	    //(17*1 * 1*5)
	    for(l=0;l<17;++l){				//delta_wji
	    	for(k=0;k<layer;++k){
	    		hiddenInput[l][k] = lRate*train[i][l]*deltaInput[0][k];
	    		//printf("%f ", hiddenInput[l][k]);
	    	}
	    	//printf("\n");
	    }
	    //printf("\nhello\n");
	    //break;
	    //break;
	    for(l=0;l<17;++l){				
	   		for(k=0;k<layer;++k){
	    		sumWeightInputHidden[l][k] += hiddenInput[l][k];
	    		//printf("%f ", sumWeightInputHidden[l][k]);	
	   		}
	   		//printf("\n");
		}
		//break;
		for(l=0;l<layer+1;++l){				
	   		for(k=0;k<10;++k){
	    		sumWeightHiddenOutput[l][k] += hiddenOutput[l][k];
	    		//printf("%f\n", sumWeightHiddenOutput[l][k]);
	   		}
		}	
	}
	 for(l=0;l<17;++l){				
	   		for(k=0;k<layer;++k){
	    		normih+=(sumWeightInputHidden[l][k]*sumWeightInputHidden[l][k]);
	    		//printf("%f ", sumWeightInputHidden[l][k]);	
	   		}
	   		//printf("\n");
		}

		normih = sqrt(normih);
		//break;
		for(l=0;l<layer+1;++l){				
	   		for(k=0;k<10;++k){
	    		normho += (sumWeightHiddenOutput[l][k]*sumWeightHiddenOutput[l][k]);
	   		}
		}
		normho = sqrt(normho);
		//printf("%f\n", normho);
	for(l=0;l<17;++l){
	    for(j=0;j<layer;++j){
	    	weightInputHidden[l][j] += sumWeightInputHidden[l][j];
	    	//printf("%f ", weightInputHidden[l][j]);
	    }
	    //printf("\nsd\n");
	}
	//break;
	for(l=0;l<layer+1;++l){
	    for(j=0;j<10;++j){
	    	weightHiddenOutput[l][j] += sumWeightHiddenOutput[l][j];
	    	//printf("%f ", weightHiddenOutput[l][j]);
	    }
	    //printf("\n");
	}
	/*for(l=0;l<17;++l){				
	   	for(k=0;k<layer;++k){
	    	if(sumWeightInputHidden[l][k] < epsilon)
	    		count++;
	    		//printf("%f ", sumWeightInputHidden[l][k]);	
	   	}
	   		//printf("\n");
	}
		//break;
	for(l=0;l<layer+1;++l){				
	   	for(k=0;k<10;++k){
	    	if(sumWeightHiddenOutput[l][k] < epsilon)
	    		count++;
	   	}
	}*/	
	average = (normho+normih)/2.0;
	if(average<epsilon || epochi > epoch){
		//printf("%d %f %f\n", epochi, normih, normho);
		break;
		}	
	}
	//printf("%d\n", count);
}
int main(){   
	char trainFileName[] = {"train.csv"};
	char testFileName[] = {"test.csv"};
	int train[2216][17], actualTrainOutput[2216], test[998][17], actualTestOutput[998];
	float weightInputHidden[17][9], weightHiddenOutput[9][10];
	int lenTrain = readFile(train, trainFileName, actualTrainOutput);
	int lenTest = readFile(test, testFileName, actualTestOutput);
	for(int layer=5;layer<9;++layer){
		setWeight(weightInputHidden, weightHiddenOutput, layer);
		//using epoch as stopping criterion
		//trainPerceptron_1(train, lenTrain, actualTrainOutput, weightInputHidden, weightHiddenOutput, layer);
		/*for(int l=0;l<17;++l){
	    	for(int j=0;j<layer;++j){
	    		printf("%f ", weightInputHidden[l][j]);// = weightInputHidden[l][j] + hiddenInput[l][j];
	    	}
	    	printf("\n");
	    }
		printf("\n\n");
		for(int l=0;l<6;++l){
	    	for(int j=0;j<10;++j){
	    		printf("%f ", weightHiddenOutput[l][j]);// = weightInputHidden[l][j] + hiddenInput[l][j];
	    	}
	    	printf("\n");
	    }
	    printf("\n\n");*/
	    //using norm as stopping criterion
		trainPerceptron_2(train, lenTrain, actualTrainOutput, weightInputHidden, weightHiddenOutput, layer);
		testPerceptron(test, lenTest, actualTestOutput, weightInputHidden, weightHiddenOutput, layer, 1);
	}
	return 0 ; 
}