#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define HIGHSCORE_FILENAME "score_congklak.dat"

typedef struct{
	char nama[25];
	int bijiCollected;
	int numberOfShoot;
	int numberOfTake;
	bool isComputer;
	bool status;    //buat nampung apa player menang atau kalah
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
void tembak(int lubang,bool giliran,int kewuk[]);
int openScore();
void saveScore();
void swap(int tuker,int tukar);
int cekSwap(int i,int j,int choice);
void showHighscore();
void gotoxy(int x, int y);

int kewuk[14] = {7,7,7,7,7,7,7,7,7,7,7,7,7,7};
pemain P[2];
highscore show[100],raw,temp;

int main(){
    int menu;
    do{
        system("cls");
        printf("===========================\n");
        printf(" / |7||7||7||7||7||7||7| \\\n||0|  C O N G K L A K  |0||\n \\ |7||7||7||7||7||7||7| /\n");
        printf("===========================\n");
		printf("    1.Mulai Permainan\n");
        printf("    2.Highscore\n");
        printf("    3.Tentang Aplikasi\n");
        printf("    4.Bantuan\n");
        printf("    5.Keluar\n");
        printf("    Menu yang dipilih : ");scanf(" %d",&menu);

        if(menu==1){
            playGame();
        }else if(menu==2){
            showHighscore();
        }else if(menu==3){

        }else if(menu==4){

        }else if(menu==5){
            printf("    Selamat Tinggal\n");
            system("pause");    //di pause supaya teksnya bisa kebaca dulu
		}else{
			printf("    Menu tidak tersedia\n");
            system("pause");	//ga penting da, sok weh hapus kalo mau lol
        }
    }while(menu!=5);
	return 0;
}

void playGame(){
	char name[25];
	bool giliran;
	int lubang;
	int biji;

	printf("Nama anda (Maks. 25 Karakter) : "); scanf(" %[^\n]",name);

	generatePlayer(P,name);
	giliran = suitTangan();

	if(!giliran){
		printf("Komputer Main Duluan\n");
	}else{
		printf("Anda Main Duluan\n");
	}
	system("pause");

	board();
	Awal :
	if(giliran){
        do{
			board();
			gotoxy(20,15);printf("Masukkan Nomor Lubang : ");scanf("%d",&lubang);

			if(lubang==0 || lubang>= 8){
				system("cls");
				goto Awal;
			}else{
				maju(lubang, giliran);
				board();
				//ganti();
			}
		}while(7<5);
	}else{
		srand(time(NULL));
		do{
			lubang = rand()%15 + 9;
		}while(lubang < 9 || lubang > 15);
		//lubang = 14;
		printf("lubang %d",lubang);
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
	pemain tempe;

	tempe = P[0];
	P[0] = P[1];
	P[1] = tempe;
}
*/

void board(){
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
				if(giliran && lubang  == 8){
					P[0].bijiCollected =P[0].bijiCollected + 1;
				}else if(lubang == 16 && !giliran){
					P[1].bijiCollected =P[1].bijiCollected + 1;
					printf("Disini\n");	
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
			Sleep(1000);
		}
		printf("Posisi Terakhir : %d, isinya ada : %d\n",lubang-1,kewuk[x]);
		system("pause");
		lubang = lubang - 1;
	}while(kewuk[x] != 1);
	
	if (kewuk[x]==1) {
		tembak(lubang,giliran,kewuk);
	}
}

//void ganti() {

void tembak(int lubang, bool giliran, int kewuk[]) {
	int x;
	if (lubang>8){
		x=lubang-9;
	}else {
		x=14-lubang;
	}
	
	if (giliran) {
		if (kewuk[x-7]>0) {
			P[0].bijiCollected=P[0].bijiCollected+kewuk[x]+kewuk[x-7];
			kewuk[x]=0;
			kewuk[x-7]=0;
		}
	} else {
		if (kewuk[x+7]>0) {
			P[1].bijiCollected=P[1].bijiCollected+kewuk[x]+kewuk[x+7];
			kewuk[x]=0;
			kewuk[x+7]=0;
		}
	}
}

int openScore(){
    int nomor=0;
    FILE *hai=fopen(HIGHSCORE_FILENAME,"r");
    while(fread(&show[nomor],sizeof(highscore),1,hai)==1){
    	nomor++;
	}
    fclose(hai);
    return nomor;
}


void saveScore(){
    strcpy(raw.name,P[0].nama);
    raw.bijiCollected=P[0].bijiCollected;
    raw.numberOfShoot=P[0].numberOfShoot;
    raw.numberOfTake=P[0].numberOfTake;
    raw.status=P[0].status;
    FILE *hai=fopen(HIGHSCORE_FILENAME,"a");
    fwrite(&raw,sizeof(highscore),1,hai);
    fclose(hai);
}

void swap(i,j){
    temp=show[i];
    show[i]=show[j];
    show[j]=temp;
}

int cekSwap(int i,int j,int choice){
    if(choice==1){
        return strcmp(show[j].name,show[i].name)<0;
    }else if(choice==2){
        return show[j].bijiCollected>show[i].bijiCollected;
    }else if(choice==3){
        return show[j].numberOfShoot>show[i].numberOfShoot;
    }else if(choice==4){
        return show[j].numberOfTake<show[i].numberOfTake;
    }
}

void sortHighscore(int choice,int N){
    int i,j;
    for(i=0;i<N-1;i++){
        for(j=i+1;j<N;j++){
            if(cekSwap(i,j,choice)){
                swap(i,j);
            }
        }
    }
}

void showHighscore(){
    int N,pilihan=0,i;
   	N=openScore();
    do{
        do{
            system("cls");
            printf("||Menu Highscore||\n");
            printf("Urutkan score berdasarkan\n");
            printf("1.Nama\n");
            printf("2.Biji Terkumpul\n");   //dari terbesar atau descending
            printf("3.Banyak Menembak\n");  //dari terbesar juga
            printf("4.Banyak Giliran\n");   //dari terkecil? ga yakin urg
            printf("5.Kembali ke menu utama\n\n");
            printf("Masukkan pilihan : ");scanf("%d",&pilihan);
            if(pilihan<1){  //algoritma yang meriksa input termasuk pilihan atau ga
                pilihan=6;  //kalau input dibawah 0(tidak tesedia)
            }               //dibuat jadi 6 supaya diulang
        }while(pilihan>5);  //kalo input ga ada di pilihan di ulang
        if (pilihan!=5){
            sortHighscore(pilihan,N);
            printf("Nama Pemain\tBiji Terkumpul\tBanyak Menembak\tBanyak Giliran\n");
            for(i=0;i<N;i++){
                printf("%-20s \t",show[i].name);
                printf("%d\t\t",show[i].bijiCollected);
                printf("%d\t\t",show[i].numberOfShoot);
                printf("%d\t\t",show[i].numberOfTake);
                if (show[i].status==true){
                    printf("Menang\n");
                }else{
                    printf("Kalah\n");
                }
            }
        }
        system("pause");//kalau ga ada pause langsung balik ke pilihan lagi
    }while(pilihan!=5);
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
