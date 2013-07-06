char c[] = "Wiadomosc";

void change_letter(int i){
	c[i] = c[i] + 1;
	printf(c);
}

int main(){
	int i;
	for(i = 0; i < 9; ++i){
		change_letter(i);
	}
}
