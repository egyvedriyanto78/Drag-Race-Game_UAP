/* ---------------------------------------------
 * Program ini kami buat untuk menyelesaikan 
 * tugas akhir projek untuk memenuhi nilai akhir
 *
 * Program ini kami beri nama 
 * " Drag Race Game "
 *
 * Dibuat pada Akhir bulan November sampai 10 Desember 2021
 * oleh :
 *	1.	Egy Vedriyanto 
 *		2117051035
 * 	2.	Ikhsan Saputra
 * 		2117051037
 *	3.	Muhammad Hafiz Atsal 
 *		2117051084
 *
 * file ini juga dapat dilihat pada akun github
 * kami.
 * --------------------------------------------- */

#include <iostream>
//library untuk menggunakan cout dan cin
#include <dos.h> 
//library untuk menggunakan dapat menambahkan sound dan sleep
#include <windows.h>
//library untuk menggunakan pemberian warna pada kalimat dan background serta peletakan posisi
#include <time.h>
//library yang digunakan untuk mendefinisikan tanggal dan waktu
#include <conio.h>
//library untuk menggunakan getch

#define LEBAR_LAYAR 105
//Mendefinisikan bahwa lebar layar 105
#define TINGGI_LAYAR 26
//Mendefinisikan bahwa tinggi layar 26
#define LEBAR_AREA 70 
//Mendefinisikan bahwa lebar layar game 70

using namespace std; 
//Memudahkan membuat code
 
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD PosisiCursor;
//Di gunakan untuk menempatkan kursor di tempat yang tidak dapat dicapai bila
//hanya menggunakan sekuensi program saja

int Xmusuh[3];
// posisi musuh 
int Ymusuh[3];
// posisi musuh
int enemies[3];
// muncul dan menghilangnya musuh

char car[4][4] = { ' ','^','^',' ',
				   '0','=','=','0',
				   ' ','|','|',' ',
				   '0','=','=','0' }; 
//bentuk mobil						
					
int posisi = LEBAR_AREA/2;
//letak awal mobil 
int score = 0; 
//score awal

void gotoxy(int x, int y){
	PosisiCursor.X = x;
	PosisiCursor.Y = y;
	SetConsoleCursorPosition(console, PosisiCursor);
}
//Di gunakan untuk menempatkan kursos di tempat yang tidak dapat dicapai bila
//hanya menggunakan sekuensi program saja

void setcursor(bool visible, DWORD size) {
	if(size == 0)
		size = 20;//default cursor size	

	
	CONSOLE_CURSOR_INFO lpCursor;
	//untuk memodifikasi lokasi tinggi dan visibilitas	
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console,&lpCursor);
}

void EnemyComes(int io)
	//Menentukan kedatangan musuh 
	{Xmusuh[io] = 17 + rand()%(35);  
} 	//menentukan random arah kemunculan musuh

void BuatMusuh(int io) 
	//Membuat tampilan musuh
{
	if( enemies[io] == true ){
		gotoxy(Xmusuh[io], Ymusuh[io]);   cout<<" ** ";  
		gotoxy(Xmusuh[io], Ymusuh[io]+1); cout<<"0**0"; 
		gotoxy(Xmusuh[io], Ymusuh[io]+2); cout<<" ** "; 
		gotoxy(Xmusuh[io], Ymusuh[io]+3); cout<<"0**0"; 
	} 
}
void HapusMusuh(int io)
	//Menghilangkan tampilan musuh saat dilewati 
{
	if( enemies[io] == true ){
		gotoxy(Xmusuh[io], Ymusuh[io]);   cout<<"    ";  
		gotoxy(Xmusuh[io], Ymusuh[io]+1); cout<<"    "; 
		gotoxy(Xmusuh[io], Ymusuh[io]+2); cout<<"    "; 
		gotoxy(Xmusuh[io], Ymusuh[io]+3); cout<<"    "; 
	} 
}

void border()
	//Membuat pembatas 
{  
	for(int x=0; x<TINGGI_LAYAR; x++){
		for(int y=0; y<15; y++){
			gotoxy(0+y,x); cout<<"#";
			gotoxy(LEBAR_AREA-y,x); cout<<"#";
		}
	} 
		//Membuat bentuk pembatas lebar layar
	for(int x=0; x<TINGGI_LAYAR; x++){
		gotoxy(LEBAR_LAYAR,x); cout<<"|";
	} 
}

void BuatMobil()
	//Membuat tampilan mobil dan posisi awal mobil
{
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			gotoxy(j+posisi, i+22); cout<<car[i][j];
		}
	}
}
void HapusMobil()
//Menghapus tampilan mobil 
{
	for(int x=0; x<4; x++){
		for(int y=0; y<4; y++){
			gotoxy(y+posisi, x+22); cout<<" ";
		}
	}
}

void resetMusuh(int io)
//Mereset musuh yang telah dilewati
{
	HapusMusuh(io);
	Ymusuh[io] = 1;
	EnemyComes(io);
}

int crash()
//fungi yang menandakan situasi ketika terjadi tabrakan 
{
	if( Ymusuh[0]+4 >= 23 ){
		if( Xmusuh[0] + 4 - posisi >= 0 && Xmusuh[0] + 4 - posisi < 9  ){
			return 1;//agar program dapat membaca fungsi crash
		}
	}
	return 0;
} 

void dead()
//tampilan yang akan muncul dilayar ketika terjadi tabrakan
{
	system("cls");
	cout<<endl;
	cout<<"\t\t-----------------------------"<<endl;
	cout<<"\t\t-------> You are dead <------"<<endl;
	cout<<"\t\t-----------------------------"<<endl<<endl<<endl;
	cout<<"\t\tYour Score\t: "<<score;
	cout<<endl<<endl;
	cout<<"\t\tTekan tombol apa saja untuk kembali ke Menu.";
	getch();
}

void UpScore()
//menentukan posisi tampilan score
{
	gotoxy(LEBAR_AREA + 7, 8);cout<<"Score : "<<score<<endl;
}

void username()
//prosedur yang memuat username 
{
	string ID;
	gotoxy(15,5);cout<<"-- SILAHKAN MASUKKAN USERNAME ANDA ! --";
	gotoxy(15,9);cout<<"---------------------------------------";
	gotoxy(15,11);cout<<"---------------------------------------";
	gotoxy(15,10);cout<<"username : ";
	getline(cin,ID);
	getch();
	gotoxy(15,5);cout<<"                       			          ";
	gotoxy(15,9);cout<<"              			                  ";
	gotoxy(15,11);cout<<"              			                  ";
	gotoxy(15,10);cout<<"              			                  ";
	gotoxy(LEBAR_AREA + 3, 18);cout<<"===============================";
	gotoxy(LEBAR_AREA + 3, 19);cout<<"ID : "<<ID;
	gotoxy(LEBAR_AREA + 3, 20);cout<<"===============================";
}

void play()
//Ini merupakan prosedur utama yang memuat hampir semua fungsi dalam game
{
	posisi = -1 + LEBAR_AREA/2;
	//agar posisi awal mobil tepat di tengah area
	score = 0;
	//score awal yang diberikan =0
	enemies[0] = 1;
	enemies[1] = 0;
	Ymusuh[0] = Ymusuh[1] = 1;
	  
	system("cls"); 
	//sistem yang dapat menghapus layar screen
	username();
	//Memasukkan fungsi username
	border(); 
	//memasukkan prosedur border
	UpScore();
	//memasukkan prosedur UpScore
	EnemyComes(0);
	EnemyComes(1);
	
	gotoxy(LEBAR_AREA + 5, 3);cout<<"^^================^^";
	gotoxy(LEBAR_AREA + 5, 4);cout<<"|| Drag Race Game ||";
	gotoxy(LEBAR_AREA + 5, 5);cout<<"<<================>>";
	gotoxy(LEBAR_AREA + 7, 12);cout<<"Cara Gerak : ";
	gotoxy(LEBAR_AREA + 3, 13);cout<<"=========================";
	gotoxy(LEBAR_AREA + 3, 14);cout<<" A atau 4 untuk ke- kiri";
	gotoxy(LEBAR_AREA + 3, 15);cout<<" D atau 6 untuk ke- kanan";
	gotoxy(LEBAR_AREA + 3, 16);cout<<"=========================";  
	//Menentukan posisi munculnya tulisan diatas
	
	gotoxy(18, 5);cout<<"Tekan apa saja untuk memulai !";
	getch();
	gotoxy(18, 5);cout<<"                               ";
	
	while(1){
		if(kbhit())//untuk dapat menentukan apakah tombol telah ditekan atau tidak (conio.h)
		{
			char key = getch();
			if( key=='a' || key=='A' || key=='4'){
				if( posisi > 18 )
					posisi -= 4;
			}
			if( key=='d' || key=='D' || key=='6'){
				if( posisi < 50 )
					posisi += 4;
			} 
			if(key==27){
				break;
			}
		} 
		
		BuatMobil(); 
		BuatMusuh(0); 
		BuatMusuh(1); 
		if( crash() == true  ){
			dead();
			return;
		} 
		Sleep(50);
		HapusMobil();
		HapusMusuh(0);
		HapusMusuh(1);   
		
		if( Ymusuh[0] == 8 )
			if( enemies[1] == 0 )
				enemies[1] = 1;
		
		if( enemies[0] == 1 )
			Ymusuh[0] += 1;
		
		if( enemies[1] == 1 )
			Ymusuh[1] += 1;
		 
		if( Ymusuh[0] > TINGGI_LAYAR-4 ){
			resetMusuh(0);
			score++;
			//score++ agar ketika situasi tersebut terjadi maka score bertambah 
			UpScore();
		}
		if( Ymusuh[1] > TINGGI_LAYAR-4 ){
			resetMusuh(1);
			score++;
			UpScore();
		}
	}
	
}

void loading()
	//Prosedur untuk menambahkan loading screen sebelum masuk menu
{
	
	for(int i=1; i<=3; i++){
		system("cls");
		gotoxy(15,10);cout<<"LOADING [-]";
		Sleep(500);
		gotoxy(15,10);cout<<"LOADING [-][-]";
		Sleep(500);
		gotoxy(15,10);cout<<"LOADING [-][-][-]";
		Sleep(500);
		gotoxy(15,10);cout<<"LOADING [-][-][-][-]";
		Sleep(500);
		gotoxy(15,10);cout<<"LOADING [-][-][-][-][-]";
		Sleep(500);
		gotoxy(15,10);cout<<"LOADING [-][-][-][-][-][-]";
		Sleep(500);
	}
	system("cls");
	gotoxy(15,15);cout<<"SELAMAT BERMAIN ! ";
}

void logo()
//logo hasil iseng , hehe
{
	gotoxy(59,6);  cout<<"  ^^^^^^^^^^^^^^^^^^^^^^^^^"; 
	gotoxy(59,7);  cout<<" ==========================="; 
	gotoxy(59,8);  cout<<"/     ____         ____     \\"; 
	gotoxy(59,9);  cout<<"|    |____|       |____|    |";
	gotoxy(59,10); cout<<"|             ^             |"; 
	gotoxy(59,11); cout<<"|          _______          |";
	gotoxy(59,12); cout<<"\\                           /";
	gotoxy(59,13); cout<<" ===========================";
}

void menu()
	//Prosedur menu dan memasukkan fungsi play
{
	do{
		system("cls");
		loading();
		logo();
		gotoxy(10,5); cout<<"^^==========================^^"; 
		gotoxy(10,6); cout<<"||      Drag Race Game      ||"; 
		gotoxy(10,7); cout<<"<<==========================>>";
		gotoxy(60,15); cout<<"==========================="; 
		gotoxy(60,16); cout<<"|Game created by :        |"; 
		gotoxy(60,17); cout<<"|                         |";
		gotoxy(60,18); cout<<"| - Egy Vedriyanto        |"; 
		gotoxy(60,19); cout<<"| - Ikhsan Saputra        |";
		gotoxy(60,20); cout<<"| - Muhamad Hafiz Atsal   |";
		gotoxy(60,21); cout<<"==========================="; 
		gotoxy(10,9); cout<<"1. Bermain";	 
		gotoxy(10,10); cout<<"2. Keluar";
		gotoxy(10,12); cout<<"Pilihan : ";
		char opt = getche();
		//getche fungsinya sama dengan getch bedanya dapat menampilkan karakter yang diinput
		//option
		if( opt=='1') play();
		//jika menjawab 1 maka bermain
		else if( opt=='2') exit(0);
		//jika 2 maka exit atau memberhentikan program secara paksa/manual
		
	}while(true);	
	//while true
}

int main()
	//Fungsi utama
{
	system ("color D0");
	//Sistem untuk menambahkan warna
	setcursor(0,0); 
	srand( (unsigned)time(NULL)); 
	//syarat agar dapat menggunakan tools srand/rand
	menu(); 
	//Memasukkan fungsi menu
	
	getch();
	//Menjeda ketika mengakhiri program
	return 0;
	//Menandakan bahwa program telah selesai
}
