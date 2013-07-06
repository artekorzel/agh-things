int rec_fibonaci(int value);

int rec_fibonaci(int value){
	if(value == 1 || value == 2){
		return 1;
	}
	return rec_fibonaci(value-1) + rec_fibonaci(value-2);
}

int it_fibonaci(int value){
	int i;
	int a = 1;
	int b = 1;
	int c = 0;
	for(i = 2; i < value; ++i){
		c = a+b;
		a = b;
		b = c; 
	}
	return b;
}

int j = 6;

int main(){
	printf(it_fibonaci(j));
	printf(rec_fibonaci(j));
}
