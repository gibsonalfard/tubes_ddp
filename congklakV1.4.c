#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<windows.h>
#define HIGHSCORE_FILENAME "score_congklak.dat"
//tetes
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
void maju(int lubang, int giliran);	//giliran pada diganti jadi integer, algoritma yg tio kepikiran buat ganti giliran perlu var integer
void tembak(int lubang,int giliran,int kewuk[]);	// jadi giliran diganti ke integer asalnya bool
int openScore();
void saveScore();
void swap(int tuker,int tukar);
int cekSwap(int i,int j,int choice);
void showHighscore();
bool pickKosong(int pick);
void gotoxy(int x, int y);

int kewuk[14] = {7,7,7,7,7,7,7,7,7,7,7,7,7,7};
int hand=0; //biji ditangan
pemain P[2];
highscore show[100],raw,temp;
int turn;	// Variabel penentu giliran, asalnya giliran tipe bool, diganti jadi integer global supaya bisa diganti nilai di modul maju()

int main(){
    int menu;
    do{
        system("cls");
        gotoxy(48,5);printf("===========================\n");
        gotoxy(48,6);printf(" / |7||7||7||7||7||7||7| \\\n");
		gotoxy(48,7);printf("||0|  C O N G K L A K  |0||\n"); 
		gotoxy(48,8);printf(" \\ |7||7||7||7||7||7||7| /\n");
        gotoxy(48,9);printf("===========================\n");
		gotoxy(48,10);printf("    1.Mulai Permainan\n");
        gotoxy(48,11);printf("    2.Highscore\n");
        gotoxy(48,12);printf("    3.Tentang Aplikasi\n");
        gotoxy(48,13);printf("    4.Bantuan\n");
        gotoxy(48,14);printf("    5.Keluar\n");
        gotoxy(48,16);printf(" Menu yang dipilih : ");scanf("%d",&menu);

        if(menu==1){
            playGame();
        }else if(menu==2){
            showHighscore();
        }else if(menu==3){
			printf("    Status : Belum Selesai\n");
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

void playGame(){	//yang perlu ditambahin modul : pemeriksa akhir permainan, pemanggilan modul penulis highscore "saveScore()".
	char name[25];
	int lubang,i;
	int biji;
	/*
	for(i=0;i<14;i++){ //buat me reset isi kewuk setiap game di mulai
		kewuk[i]=7;		// Kan udah diglobal, jadi ini bisa di komen
	}
	*/
	system("cls");
	gotoxy(42,9);printf("Nama anda (Maks. 25 Karakter) : "); scanf(" %[^\n]",name);

	generatePlayer(P,name);
	turn = suitTangan();	//cheat udah dibuat pilih 4 kalau mau giliran pertama

	if(turn==0){
		gotoxy(42,17);printf("Komputer Main Duluan\n");
	}else{
		gotoxy(42,17);printf("Anda Main Duluan\n");
	}
	gotoxy(42,18);system("pause");

	board();
	do{
		if(turn==1){
			P[0].numberOfTake++;	//data highscore jumlah giliran
			system("cls");
			board();
			gotoxy(20,15);printf("Masukkan Nomor Lubang (1-7): ");scanf("%d",&lubang);	//perlu pemeriksaan player jangan milih lubang yang 0, tapi kalau semua lubang isinya 0 gimana???
			
			if((lubang<=0 || lubang>= 8) || pickKosong(lubang)){
				system("cls");
			}
			else{
				maju(lubang, turn);
				board();
			}
		}else{
			system("cls");
			board();
			srand(time(NULL));
			lubang = rand()%7 + 9;	//ini perlu diganti, pas tio mainin komputer milih lubang yang isinya 0/kewuk kosong
			//lubang != 14; lubang = 16, base dihitung lubang
			gotoxy(20,15);
			printf("Komputer memilih lubang %d\n",lubang);
			system("pause");
			maju(lubang,turn);
		}
	}while(7>5);
}

bool suitTangan(){
	int opsi=0,komputer;

	do{
		//system("cls");
		if(opsi != 0){
			printf("Maaf, Inputan anda Salah");
			//Kondisi jika user memasukan inputan yang salah
		}
		gotoxy(48,11);printf("1. Kertas\n");
		gotoxy(48,12);printf("2. Gunting\n");
		gotoxy(48,13);printf("3. Batu\n");
		gotoxy(42,15);printf("Masukan Pilihan : "); scanf("%d",&opsi);
	}while(opsi < 1 || opsi > 5);

	if(opsi!=4){
		komputer = suitKomputer(opsi);
	
		if((opsi % 3) > (komputer % 3)){
			if(opsi == 2 && komputer == 3){
				return 0;
			}
			return 1;
		}else{
			if(opsi == 3 && komputer == 2){
				return 1;
			}
			return 0;
		}
	}else if(opsi == 5){
		return 0;
	}else{
		return 1;	//Cheat
	}
}

int suitKomputer(int pilihan){
	int hasil;
	srand(time(NULL));

	do{
		hasil = rand() % 3 + 1;
	}while(hasil == pilihan);

	switch(hasil){
		case 1:	gotoxy(42,16);printf("Komputer Memilih Kertas\n");	break;
		case 2:	gotoxy(42,16);printf("Komputer Memilih Gunting\n");	break;
		case 3:	gotoxy(42,16);printf("Komputer Memilih Batu\n");		break;
	}

	return hasil;
}

void generatePlayer(pemain P[], char nama[]){
	int i = 0;

	for(i=0;i<2;i++){
		if(i == 0){
			strcpy(P[i].nama,nama);
			P[i].isComputer = false;
			P[i].bijiCollected = 0;
			P[i].numberOfShoot = 0;	//data highscore direset setiap game dimulai
			P[i].numberOfTake = 0;
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

void board(){	//hand dimunculin di board
	char papan[5][25]={
						{'-','-','-','9','-','-','A','-','-','B','-','-','C','-','-','D','-','-','E','-','-','F','-','-','-'},
						{'/',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','\\'},
						{'|','|','X','|',' ',' ',' ',' ',' ',' ',' ',' ','Z',' ',' ',' ',' ',' ',' ',' ',' ','|','X','|','|'},
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
			}else if(papan[i][j] == 'Z'){
				printf(" %d",hand);
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

void maju(int lubang, int giliran){
	int realPosition,i,player=giliran;	//jml diganti sama hand sama tio, jadi di board bisa dimunculin gimana??; tio ngebuat var player karena var giliran diisi sama var turn dan var turn nilainya diubah di modul ini, takutnya jadi bug
	bool out=true;						//X diganti sama gibran jadi realPosition
	
	do{
		if(lubang>8 && lubang<16){
			realPosition = lubang - 9;
		}else{
			realPosition = 14-lubang;
		}
		hand = kewuk[realPosition];
		kewuk[realPosition] = 0;
		lubang++;
		
		while(hand > 0){
			if(lubang%8 == 0){
				if(turn==1 && lubang  == 8){
					P[0].bijiCollected =P[0].bijiCollected + 1;
				}else if(lubang == 16 && turn==0){
					P[1].bijiCollected =P[1].bijiCollected + 1;
				}else{
					hand++;	
				}
			}
			else if(lubang>9){
				realPosition++;
				kewuk[realPosition] = kewuk[realPosition]+1;
			}else if(lubang == 9){
				realPosition = 0;
				kewuk[realPosition] = kewuk[realPosition]+1;
			}else if(lubang==1){
				realPosition=13;
				kewuk[realPosition]=kewuk[realPosition]+1;
			}else{
				realPosition--;
				kewuk[realPosition] = kewuk[realPosition]+1;
			}
			
			hand--;
			
			if(lubang == 16){
				lubang = 1;
			}else{
				lubang++;
			}
			board();
			Sleep(1000);
		}
		
		if(lubang-1==0){
			printf("Posisi Terakhir : 16, isinya ada : %d\n",P[1].bijiCollected);
			out=false;
		}else if(lubang-1==8){
			printf("Posisi Terakhir : 8, isinya ada : %d\n",P[0].bijiCollected);
			out=false;
		}else{
			printf("Posisi Terakhir : %d, isinya ada : %d\n",lubang-1,kewuk[realPosition]);
			if(kewuk[realPosition]==1) {
				out=false;
				turn=(turn+1)%2;	//giliran/turn diganti hanya jika biji terakhir jatuh dilubang non-base yang kosong
			}
		}
		system("pause");
		lubang = lubang - 1;
	}while(out);	//out >> kalau biji terakhir di base giliran tidak berubah
	
	if (kewuk[realPosition]==1) {
		tembak(lubang,player,kewuk);
		if(player==1){
			P[0].numberOfShoot++;	// data higscore banyak nembak
		}
	}
}

bool pickKosong(int pick){
	int realPosition;
	
	if (pick>8){
		realPosition=pick-9;
	}else {
		realPosition=14-pick;
	}
	
	if(kewuk[realPosition] == 0){
		return true;
	}else{
		return false;
	}
}

void tembak(int lubang, int giliran, int kewuk[]) {
	int realPosition; //X diganti sama gibran jadi realPosition
	if (lubang>8){
		realPosition=lubang-9;
	}else {
		realPosition=14-lubang;
	}
	
	if (giliran==1) {
		if (kewuk[realPosition-7]>0) {
			P[0].bijiCollected=P[0].bijiCollected+kewuk[realPosition]+kewuk[realPosition-7];
			kewuk[realPosition]=0;
			kewuk[realPosition-7]=0;
		}
	} else {
		if (kewuk[realPosition+7]>0) {
			P[1].bijiCollected=P[1].bijiCollected+kewuk[realPosition]+kewuk[realPosition+7];
			kewuk[realPosition]=0;
			kewuk[realPosition+7]=0;
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
            printf("4.Banyak Giliran\n");   //dari terkecil? makin dikit makin bagus atau sebaliknya??
            printf("5.Kembali ke menu utama\n\n");
            printf("Masukkan pilihan : ");scanf("%d",&pilihan);
        }while(pilihan<1 || pilihan>5); 
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
        system("pause");
    }while(pilihan!=5);
}

void gotoxy(int x, int y) {
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
