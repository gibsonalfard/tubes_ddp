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
//void swapPlayer(pemain P[]);
int suitKomputer(int pilihan);
void generatePlayer(pemain P[], char nama[]);
void board();
bool isPlay();
void maju(int lubang, bool giliran);
void gotoxy(int x, int y);
void tembak(int lubang,bool giliran);

int kewuk[14] = {7,7,7,7,7,7,7,7,7,7,7,7,7,7};
pemain P[2];

int main(){
	playGame();
	return 0;
}

void playGame(){
	char name[25];
	bool giliran;
	int lubang;
	
	printf("Nama anda (Maks. 25 Karakter) : "); scanf("%[^\n]",name);
	
	generatePlayer(P,name);
	giliran = suitTangan();
	
	if(!giliran){
		printf("Komputer Main Duluan\n");
	}else{
		printf("Anda Main Duluan\n");		
	}
	system("pause");
	
	board();
	
	if(giliran){
		board();
		gotoxy(30,15);printf("Masukkan Nomor Lubang : ");scanf("%d",&lubang);
		
		if(lubang == 9){
			
		}else{
			maju(lubang,giliran);
		}	
	}else{
		srand(time(NULL));
		do{
			lubang = rand()%15 + 9;
		}while(lubang < 9 || lubang > 15);
		
		gotoxy(30,15);printf("Komputer Memilih Lubang Nomor : %d",lubang);
		system("pause");
		maju(lubang,giliran);
	}
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

/*
void swapPlayer(pemain P[]){
	pemain temp;
	
	temp = P[0];
	P[0] = P[1];
	P[1] = temp;
}
*/

void board(){
	char papan[5][25]={
						{' ','-','-','9','-','-','A','-','-','B','-','-','C','-','-','D','-','-','E','-','-','F','-','-',' '},
						{'/',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','\\'},
						{'|','|','X','|',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','|','X','|','|'},
						{'\\',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','/'},
						{' ','-','-','7','-','-','6','-','-','5','-','-','4','-','-','3','-','-','2','-','-','1','-','-',' '},
					  };
	int i,j,x,y,number = 10,index = 0, z=0;
	system("cls");
	y = 2;
	for(i=0;i<5;i++){
		y = y + 2;
		x = 20;
		for(j=0;j<25;j++){
			x = x + 3;
			gotoxy(x,y);
			if((int)papan[i][j] > 64 && (int)papan[i][j] < 71){
				printf("%d",number);
				number++;
			}else if(papan[i][j] == 'x'){
				printf(" %d",kewuk[index]);
				index++;
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

bool isPlay(int kewuk[]){
	int i = 0;
	bool end = true;
	
	while((i<14) && end){
		if(kewuk[i] != 0){
			end = false;
		}
	}
	
	return end;
}

void maju(int lubang, bool giliran){
	int x,i,jml;
	
	do{
		if(lubang > 8){
			x = lubang - 9;
		}else{
			x = 14-lubang;	
		}
		jml = kewuk[x];
		kewuk[x] = 0;
		lubang++;
		
		while(jml > 0){
			if(lubang%8 == 0){
				if(giliran && lubang == 8){
					P[0].bijiCollected =P[0].bijiCollected + 1;
				}else if(lubang == 16 && !giliran){
					P[1].bijiCollected =P[1].bijiCollected + 1;
				}else{
					jml++;	
				}
			}
			else if(lubang>9){
				x++;
				kewuk[x] = kewuk[x]+1;
			}else if(lubang == 9){
				x = 0;
				kewuk[x] = kewuk[x]+1;
			}else{
				x--;
				kewuk[x] = kewuk[x]+1;
			}
			
			jml--;
			
			if(lubang == 16){
				lubang = 1;
				x = 14;
			}else{
				lubang++;
			}
			board();
			gotoxy(40,15);printf("Sisa Biji ditangan : %d", jml);
			Sleep(1000);
		}
		
		gotoxy(40,15);printf("Posisi Terakhir : %d, isinya ada : %d\n",lubang-1,kewuk[x]);
		gotoxy(40,17);system("pause");
		lubang = lubang - 1;
	}while(kewuk[x] != 1 && lubang%8 != 0);
	
	if(kewuk[x] == 1){
		tembak(lubang,giliran);
	}
}

void tembak(int lubang,bool giliran){
	int realPosition, tembak, lumbung;
	
	if(lubang > 8){
		realPosition = lubang - 9;
	}else{
		realPosition = 14-lubang;	
	}
	
	if(giliran && lubang < 8){
		tembak = realPosition - 7;
		if(kewuk[tembak] > 0){
			lumbung = 0;
		}
	}else if(!giliran && lubang > 8){
		tembak = realPosition + 7;
		if(kewuk[tembak] > 0){
			lumbung = 1;
		}
	}else{
		exit(0);
	}
	
	P[lumbung].bijiCollected = P[lumbung].bijiCollected + kewuk[realPosition] + kewuk[tembak];
	kewuk[realPosition] = 0;
	kewuk[tembak] = 0;
	
	board();
	gotoxy(30,15);
	printf("Bang!! %s Menembak Daerah Musuh, Lumbung %s Berisi %d \n",
			giliran ? "Kamu" : "Computer",giliran ? "Kamu" : "Computer",P[lumbung].bijiCollected);
	gotoxy(40,18);system("pause");
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
