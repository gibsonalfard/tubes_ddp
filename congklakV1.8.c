#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include<conio.h>
#include<windows.h>
#define HIGHSCORE_FILENAME "score_congklak.dat"

typedef struct{
	char nama[25];
	int bijiCollected;
	int numberOfShoot;
	int numberOfTake;
	bool isComputer;
	int status;    //buat nampung apa player menang atau kalah
}pemain;

typedef struct{
	char name[25];
	int bijiCollected;
	int numberOfShoot;
	int numberOfTake;
	int status;
}highscore;

void playGame();
bool suitTangan();
int suitKomputer(int pilihan);
void generatePlayer(pemain P[], char nama[]);
void board();
int WinOrLose();
bool isPlaying();
void maju(int lubang, int giliran);	//giliran pada diganti jadi integer, algoritma yg tio kepikiran buat ganti giliran perlu var integer
void tembak(int lubang,int giliran);	// jadi giliran diganti ke integer asalnya bool
int openScore();
void saveScore();
void swap(int tuker,int tukar);
int cekSwap(int i,int j,int choice);
void sortHighscore(int choice,int N);
void showHighscore();
bool pickKosong(int pick);
int computerPick();
void gotoxy(int x, int y);
bool daerahKosong(int giliran);
void tentang();
void bantuan();

int kewuk[14] = {7,7,7,7,7,7,7,7,7,7,7,7,7,7};
int hand=0; //biji ditangan
pemain P[2];
highscore show[100],raw,temp;
int turn;	// Variabel penentu giliran, asalnya giliran tipe bool, diganti jadi integer global supaya bisa diganti nilai di modul maju()

int main(){
    char menu;
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
        gotoxy(48,16);printf(" Menu yang dipilih : ");scanf(" %c",&menu);
		//if(scanf("%d",&menu)==0) break;
        if(menu=='1'){
            playGame();
        }else if(menu=='2'){
            showHighscore();
        }else if(menu=='3'){
			system("cls");
			tentang();
			
			gotoxy(45,22);system("pause");
        }else if(menu=='4'){
			system("cls");
			bantuan();
			
			gotoxy(45,22);system("pause");
        }else if(menu=='5'){
            gotoxy(45,18);printf("    Selamat Tinggal\n");
            gotoxy(45,20);system("pause");    //di pause supaya teksnya bisa kebaca dulu
		}else{
			gotoxy(45,18);printf("    Menu tidak tersedia\n");
            gotoxy(45,20);system("pause");
            system("cls");
            bantuan();
            gotoxy(45,20);system("pause");
        }
    }while(menu!=5);
	return 0;
}

void playGame(){	//yang perlu ditambahin modul : pemeriksa akhir permainan, pemanggilan modul penulis highscore "saveScore()".
	/*
	Deskripsi	: Melakukan proses permainan congklak
	I.S			: Game belum dimulai
	F.S			: Game berhasil dibuat dan dapat dimainkan
	*/
	char name[25];
	int lubang,i;
	int biji;

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

	//board();
	do{
		if(turn==1){
			if(!daerahKosong(turn)){
				P[0].numberOfTake++;	//data highscore jumlah giliran
				system("cls");
				board(-1);
				gotoxy(42,15);printf("Masukkan Nomor Lubang (1-7): ");scanf(" %d",&lubang);	//perlu pemeriksaan player jangan milih lubang yang 0, tapi kalau semua lubang isinya 0 gimana???
				
				if((lubang<=0 || lubang>= 8) || pickKosong(lubang)){
					system("cls");
				}
				else{
					maju(lubang, turn);
					board(-1);
				}
			}else{
				turn = 0;
			}
		}else{
			if(!daerahKosong(turn)){
				system("cls");
				board(-1);
				srand(time(NULL));
				lubang = computerPick();

				gotoxy(45,15);printf("Komputer memilih lubang %d\n",lubang);
				gotoxy(42,16);system("pause");
				maju(lubang,turn);
			}else{
				turn = 1;
			}
		}
	}while(isPlaying());
	P[0].status=WinOrLose();
	saveScore();
	showHighscore();
}

bool suitTangan(){
	/*
	Deskripsi	: Melakukan pemrosesan suit dari mulai pemain memasukan pilihan sampai dengan hasil dari suit
	Input		: -
	Output		: kondisi apakah pemain mulai duluan atau komputer duluan
	*/
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
	/*
	Deskripsi	: Menentukan pilihan suit dari komputer secara random, 
				  dengan aturan komputer tidak bisa memilih pilihan yang sama dengan pemain
				  sehingga kemungkinannya hanya menang dan kalah
	Input		: pilihan bertipe integer sebagai parameter input, yang merepresentasikan pilihan pemain
	Output		: hasil bertipe integer yang menunjukan pilihan komputer yang berbeda dengan pemain
	*/
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
	/*
	Deskripsi	: Melakukan proses pembuatan (generate) pemain dari game congklak
	I.S			: Pemain belum dibuat dan array of record masih bernilai tak tentu
	F.S			: Pemain dibuat dan array of record memiliki nilai 
				  yang menampung data masing-masing pemain
	*/
	int i = 0;

	for(i=0;i<2;i++){
		if(i == 0){
			strcpy(P[i].nama,nama);
			P[i].isComputer = false;
			P[i].bijiCollected = 0;
			P[i].numberOfShoot = 0;
			P[i].numberOfTake = 0;
		}else{
			strcpy(P[i].nama,"Computer");
			P[i].isComputer = true;
		}
		P[i].bijiCollected = 0;
	}
}

void board(int lubang){
	/*
	Deskripsi	: Membuat board (papan permainan) congklak dan menempatkan biji pada posisinya
	I.S			: Papan permainan tidak dicetak ke layar
	F.S			: Papan permainan dicetak ke layar beserta dengan posisi biji
				  yang datanya berasal dari variable global kewuk
	*/
	HANDLE hdl = GetStdHandle(STD_OUTPUT_HANDLE);
	char papan[5][25]={
						{'-','-','-','9','-','-','A','-','-','B','-','-','C','-','-','D','-','-','E','-','-','F','-','-','-'},
						{'/',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','\\'},
						{'|','|','X','|',' ',' ',' ',' ',' ',' ',' ',' ','Z',' ',' ',' ',' ',' ',' ',' ',' ','|','X','|','|'},
						{'\\',' ','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|','|','x','|',' ','/'},
						{'-','-','-','7','-','-','6','-','-','5','-','-','4','-','-','3','-','-','2','-','-','1','-','-','-'},
					  };
	int i,j,x,y,number = 10,index = 0, z=0,posisi;
	char giliran[9];
	system("cls");
	if(lubang>8 && lubang<16){
		posisi = lubang - 9;
	}else{
		posisi = 14-lubang;
	}
	
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
				if(index == posisi && (lubang != 8 && lubang != 16)){
					SetConsoleTextAttribute(hdl,12);	
				}
				printf(" %d",kewuk[index]);
				SetConsoleTextAttribute(hdl,15);	
				index++;
			}else if(papan[i][j] == 'X'){
				if(z != turn && z == (lubang/-8)+1 && lubang%8 == 0){
					SetConsoleTextAttribute(hdl,12);	
				}
				printf(" %d",P[z].bijiCollected);
				SetConsoleTextAttribute(hdl,15);

				z++;
			}else if(papan[i][j] == 'Z'){
				printf(" %d",hand);
			}else{
				printf(" %c",papan[i][j]);
			}
		}
		printf("\n");
	}
	
	if(turn == 1){
		strcpy(giliran,"Pemain");
	}else{
		strcpy(giliran,"Komputer");
	}
	gotoxy(50,0);printf("Giliran : %s",giliran);
}

int computerPick(){
	/*
	Deskripsi	: Melakukan pemrosesan lubang mana yang akan dipilih oleh komputer 
				  berdasarkan beberapa pertimbangan
	Input		: kewuk bertipe array dengan 14 elemen sebagai variable global
	Output		: pick bertipe integer sebagai hasil pilihan lubang yang akan diambil
	*/
	int pick, index,realPosition, pickPosition;
	bool memilih = false;

	index = 9;
	pick = 9;
	while(index < 16 && !memilih){
		realPosition = index - 9;

		if(kewuk[realPosition] + index == 16){
			pick = index;
			memilih = true;
		}

		index = index + 1;
	}

	index = 9;
	while(index < 16 && !memilih){
		realPosition = index - 9;
		pickPosition = pick - 9;

		if(kewuk[realPosition] > kewuk[pickPosition]){
			pick = index;
		}
		index = index + 1;
	}

	return pick;
}

bool isPlaying(){
	/*
	Deskripsi	: Melakukan pengecekan apakah permainan masih berlangsung atau tidak
	Input		: kewuk bertipe array dengan 14 elemen sebagai variable global
	Output		: kondisi bertipe boolean menunjukan true or false
	*/
	int i = 0;
	bool playing = false;

	while((i<14) && !playing){
		if(kewuk[i] != 0){
			playing = true;
		}
		i = i + 1;
	}

	return playing;
}

int WinOrLose(){
	/*
	Deskripsi	: Melakukan pengecekan siapakah pemenang dari game yang dijalankan
	Input		: P bertipe record pemain, sebagai variable global
 	Output		: integer yang menunjukan status permainan bagi user, apakah menang, kalah, atau seri
	*/
	if(P[0].bijiCollected>P[1].bijiCollected){
		return 1;
	}else if(P[0].bijiCollected<P[1].bijiCollected){
		return 0;
	}else{
		return 2;
	}
}

bool daerahKosong(int giliran){
	/*
	Deskripsi	: Melakukan pengecekan apakah daerah pemain yang hendak bermain kosong atau tidak
	Input		: giliran bertipe integer sebagai parameter input
	Output		: kosong bertipe boolean, menunjukan apakah daerah pemain kosong atau tidak
	*/
	int awal,akhir;
	bool kosong = true;

	switch(giliran){
		case 0:
			awal = 0;
			akhir = 6;
		break;
		case 1:
			awal = 7;
			akhir = 13;
		break;
		default:
			awal = 0;
		break;
	}

	while(awal<=akhir && kosong){
		if(kewuk[awal] != 0){
			kosong = false;
		}
		awal = awal + 1;
	}

	return kosong;
}

void maju(int lubang, int giliran){
	/*
	Deskripsi	: Melakukan langkah maju berdasarkan jumlah biji (kewuk) yang ada ditangan pemain
	I.S			: Biji congklak (kewuk) masih berada pada lubang yang dipilih oleh pemain
	F.S			: Lubang yang dipilih menjadi kosong lalu biji pada lubang tersebut 
				  disebarkan sesuai aturan congklak
	*/
	int realPosition,i,player=giliran;
	bool out=true;

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
			board(lubang-1);
			Sleep(800);
		}
		
		if(lubang-1==0){
			gotoxy(43,15);
			printf("Posisi Terakhir : 16, isinya ada : %d\n",P[1].bijiCollected);
			gotoxy(45,16);system("pause");
			out=false;
		}else if(lubang-1==8){
			gotoxy(43,15);
			printf("Posisi Terakhir : 8, isinya ada : %d\n",P[0].bijiCollected);
			gotoxy(45,16);system("pause");
			out=false;
		}else{
			//gotoxy(43,15);
			//printf("Posisi Terakhir : %d, isinya ada : %d\n",lubang-1,kewuk[realPosition]);
			if(kewuk[realPosition]==1) {
				out=false;
				turn=(turn+1)%2;	//giliran/turn diganti hanya jika biji terakhir jatuh dilubang non-base yang kosong
			}
		}
		lubang = lubang - 1;
	}while(out);	//out >> kalau biji terakhir di base giliran tidak berubah

	if (kewuk[realPosition]==1 && (lubang != 0 && lubang != 8)) {
		tembak(lubang,player);
		if(player==1){
			P[0].numberOfShoot++;	// data higscore banyak nembak
		}
	}
}

bool pickKosong(int pick){
	/*
	Deskripsi	: Melakukan pengecekan apakah lubang yang dipilih oleh pemain kosong
	Input		: pick bertipe integer sebagai parameter input, menunjukan nomor lubang yang dipilih
	Output		: kondisi apakah lubang tersebut kosong atau tidak
	*/
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

void tembak(int lubang, int giliran) {
	/*
	Deskripsi	: Melakukan proses tembak daerah musuh
	I.S			: Biji pada lubang biji terakhir jatuh dan yang tegak lurus 
				  dengan lubang tersebut masih pada kondisi seperti putaran akan berakhir
	F.S			: Jika memungkinkan akan dilakukan operasi menembak, sehingga lubang biji terakhir jatuh
				  dan lubang yang tegak lurus dengan lubang tersebut akan dikosongkan dan biji (kewuk) 
				  akan dipindahkan ke-base (lumbung) pemain yang melakukan proses tembak
				  
	*/
	int realPosition, tembak, lumbung = 2;

	if(lubang > 8){
		realPosition = lubang - 9;
	}else{
		realPosition = 14-lubang;
	}

	if(giliran == 1 && lubang < 8){
		tembak = realPosition - 7;
		if(kewuk[tembak] > 0){
			lumbung = 0;
		}
	}else if(giliran == 0 && lubang > 8){
		tembak = realPosition + 7;
		if(kewuk[tembak] > 0){
			lumbung = 1;
		}
	}else{
		gotoxy(35,15);printf("Maaf, kamu tidak bisa menembak dari daerah musuh :(\n");
		gotoxy(45,16);system("pause");
	}

	if(lumbung < 2){
		P[lumbung].bijiCollected = P[lumbung].bijiCollected + kewuk[realPosition] + kewuk[tembak];
		kewuk[realPosition] = 0;
		kewuk[tembak] = 0;

		board(-1);
		gotoxy(30,15);
		printf("Bang!! %s Menembak Daerah Musuh, Lumbung %s Berisi %d \n",
				giliran ? "Kamu" : "Computer",giliran ? "Kamu" : "Computer",P[lumbung].bijiCollected);
		gotoxy(45,18);system("pause");
	}
}

//Modul bertipe fungsi untuk mendapat nilai panjang data dalam file
int openScore(){
    int nomor=0;
    FILE *hai=fopen(HIGHSCORE_FILENAME,"r");
    while(fread(&show[nomor],sizeof(highscore),1,hai)==1){
    	nomor++;    //loop akan terus dilakukan seiring dengan bertambahnya nilai nomor
	}               //      hingga end of file ditemukan
    fclose(hai);
    return nomor;
}

//Modul untuk menuliskan data pemain ke file score_congklak.dat
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

//modul tipe prosedur untuk menukar isi array global "show" pada ruang i dan j
void swap(i,j){
    temp=show[i];
    show[i]=show[j];
    show[j]=temp;
}

//modul tipe fungsi untuk menghasilkan algoritma boolean sebagai penentu dilakukanya modul swap
int cekSwap(int i,int j,int choice){
    if(choice==1){
        return strcmp((show[j].name),(show[i].name))<0;
    }else if(choice==2){
        return show[j].bijiCollected>show[i].bijiCollected;
    }else if(choice==3){
        return show[j].numberOfShoot>show[i].numberOfShoot;
    }else if(choice==4){
        return show[j].numberOfTake<show[i].numberOfTake;
    }
}

//modul tipe prosedur untuk melakukan sort berdasarkan pilihan(choice) oleh user
void sortHighscore(int choice,int N){
    int i,j;
    for(i=0;i<N-1;i++){
        for(j=i+1;j<N;j++){
            if(cekSwap(i,j,choice)){    //modul cekSwap akan menghasilkan algoritma boolean
                swap(i,j);
            }
        }
    }
}

//modul tipe prosedur untuk menampilkan highscore dan sebagai wadah dipanggilnya modul-modul highscore
void showHighscore(){
    int N,pilihan=0,i,y=14;
   	N=openScore();
    do{
        do{
            system("cls");
            gotoxy(48,1);printf("||Menu Highscore||\n");
            gotoxy(48,2);printf("Urutkan score berdasarkan\n");
            gotoxy(48,3);printf("1.Nama\n");
            gotoxy(48,4);printf("2.Biji Terkumpul\n");   //data di-sort dari terbesar atau descending
            gotoxy(48,5);printf("3.Banyak Menembak\n");  //data di-sort dari terbesar
            gotoxy(48,6);printf("4.Banyak Giliran\n");   //data di-sort dari terkecil, karena makin cepat permainan selesai makin bagus
            gotoxy(48,7);printf("5.Kembali ke menu utama\n\n");
            gotoxy(48,8);printf("Masukkan pilihan : ");scanf("%d",&pilihan);
        }while(pilihan<1 || pilihan>5);
        if (pilihan!=5){
            sortHighscore(pilihan,N);   //data di-sort berdasarkan pilihan
            printf("\n||======================||======================||======================||======================||==============||\n");
            printf("||Nama Pemain\t\t||Biji Terkumpul\t||Banyak Menembak\t||Banyak Giliran\t||Status\t||\n");
            printf("||======================||======================||======================||======================||==============||\n");
			for(i=0;i<N;i++){
                printf("||%-20s  ",show[i].name);    		//agar tampilan highscore selalu terlihat rapih panjang nama yang ditampilkan dibatasi
                printf("||%d\t\t\t",show[i].bijiCollected);     //untuk menghindari nama yang panjang
                printf("||%d\t\t\t",show[i].numberOfShoot); 
                printf("||%d\t\t\t",show[i].numberOfTake);
                if (show[i].status==1){
                    printf("||Menang\t||\n");
                }else if(show[i].status==2){
                    printf("||Draw\t||\n");
                }else{
                	printf("||Kalah\t||\n");
				}
				y++;
            }
        }
        gotoxy(48,y);system("pause");
    }while(pilihan!=5);
}

void tentang(){
	/*
	Deskripsi	: Menampilkan tentang aplikasi dari file bernama "about.txt"
	I.S			: tentang aplikasi tidak ditampilkan dilayar dari file
	F.S			: tentang aplikasi diambil dari file, dan ditampilkan di layar
	*/
	int c=0,tmp = 0;
    FILE *tentang=fopen("about.txt","r");
    while(((c = getc(tentang)) != EOF) && tmp == 0){
		if(c == ';'){
			tmp = 1;
		}else{
			putchar(c);	
		}
	}
    fclose(tentang);
}

void bantuan(){
	/*
	Deskripsi	: Menampilkan instruksi bantuan bermain dari file bernama "about.txt"
	I.S			: instruksi tidak ditampilkan dilayar dari file
	F.S			: instruksi diambil dari file, dan ditampilkan di layar
	*/
	int c=0,tmp = 0;
    FILE *tentang=fopen("about.txt","r");
    while(((c = getc(tentang)) != EOF)){
		if(c == ';'){
			tmp = 1;
		}
		
		if(tmp == 1){
			putchar(c);	
		}
	}
    fclose(tentang);
}

void gotoxy(int x, int y) {
	/*
	Deskripsi	: Melakukan proses pemindahan kursor ke koordinat tertentu di command prompt
	I.S			: Kondisi kursor masih pada kondisi awal, yaitu X = 0, dan Y menyesuaikan dengan program
	F.S			: Kursor berpindah sesuai dengan koordinat X dan Y yang dimasukan sebagai parameter
	*/
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
