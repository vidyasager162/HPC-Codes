#include <stdio.h>

int main(){
	int N = 1000000000, prime_count = 0,i = 2;
	char arr[1000000001] = {};
		for(int k = 0; k < N+1; k++){
			if(k % 2!= 0){
				if(k % i == 0){
				k + = 2;
			if(k % i == 0){
				arr[k] = 1;
				i++;
			printf("k: %d\n", arr[k]);
		}

	return 0;
}
