#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<windows.h>

typedef struct{
	char nama[25];
	int bijiCollected;
	bool isComputer;
}pemain;

typedef struct{
	char name[25];
	int bijiCollected;
	int numberOfShoot;
	int numberOfTake;
	bool status;
}highscore;

void playGame();
bool suitTangan();
void swapPlayer(pemain P[]);
int suitKomputer(int pilihan);
void generatePlayer(pemain P[], char nama[]);
void board();

int main(){
	playGame();
	return 0;
}

void playGame(){
	pemain P[2];
	char name[25];
	bool giliran;
	int kewuk[14] = {7,7,7,7,7,7,7,7,7,7,7,7,7,7};
	
	printf("Nama anda (Maks. 25 Karakter) : "); scanf("%[^\n]",name);
	
	generatePlayer(P,name);
	giliran = suitTangan();
	
	if(!giliran){
		printf("Komputer Main Duluan\n");
	}else{
		printf("Anda Main Duluan\n");		
	}
	system("pause");
	board(kewuk,P);
	
	
}

bool suitTangan(){
	int opsi=0,komputer;
	
	do{
		//system("cls");
		if(opsi != 0){
			printf("Maaf, Inputan anda Salah");		
			//Kondisi jika user memasukan inputan yang salah
		}
		printf("1. Kertas\n2. Gunting\n3. Batu\n");
		printf("Masukan Pilihan : "); scanf("%d",&opsi);
	}while(opsi < 1 || opsi > 3);
	
	komputer = suitKomputer(opsi);
	
	if((opsi % 3) > (komputer % 3)){
		if(opsi == 2 && komputer == 3){
			return false;
		}
		return true;
	}else{
		if(opsi == 3 && komputer == 2){
			return true;
		}
		return false;
	}
}

int suitKomputer(int pilihan){
	int hasil;
	srand(time(NULL));
	
	do{
		hasil = rand() % 3 + 1;
	}while(hasil == pilihan);
	
	switch(hasil){
		case 1:	printf("Komputer Memilih Kertas\n");	break;
		case 2:	printf("Komputer Memilih Gunting\n");	break;
		case 3:	printf("Komputer Memilih Batu\n");	break;
	}
	
	return hasil;
}

void generatePlayer(pemain P[], char nama[]){
	int i = 0;
	
	for(i=0;i<2;i++){
		if(i == 0){
			strcpy(P[i].nama,nama);
			P[i].isComputer = false;
		}else{
			strcpy(P[i].nama,"Computer");
			P[i].isComputer = true;
		}
		P[i].bijiCollected = 0;
	}
}

void swapPlayer(pemain P[]){
	pemain temp;
	
	temp = P[0];
	P[0] = P[1];
	P[1] = temp;
}

void board(int kewuk[],pemain P[]){
	char papan[5][25]={
						{'-','-','-','9','-','-','A','-','-','B','-','-','C','-','-','D','-','-','E','-','-','F','-','-','-'},
						{'/',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','\\'},
						{'|','|','X','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','X','|','|'},
						{'\\',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','/'},
						{'-','-','-','7','-','-','6','-','-','5','-','-','4','-','-','3','-','-','2','-','-','1','-','-','-'},
					  };
	int i,j,x,y,number = 10,index = 0, z=0;
	system("cls");
	y = 2;
	for(i=0;i<5;i++){
		y = y + 2;
		x = 30;
		for(j=0;j<25;j++){
			x = x + 2;
			gotoxy(x,y);
			if((int)papan[i][j] > 64 && (int)papan[i][j] < 71){
				printf("%d",number);
				number++;
			}else if(papan[i][j] == 'x'){
				printf(" %d",kewuk[index]);
			}else if(papan[i][j] == 'X'){
				printf(" %d",P[z].bijiCollected);
				z++;
			}else{
				printf(" %c",papan[i][j]);
			}
		}
		printf("\n");
	}
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
