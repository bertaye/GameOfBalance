 #include<allegro.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>


void Baslat(); //main içinde kalabalýk yapmasýn diye ayrý tanýmlanmýþ allegro için baþlatýcý ve bitirici fonksiyonlar.
void Bitir();
typedef struct { //fonksiyona göndereceðimiz yapý, böylelikle deðerleri daha kolay saklayabiliyoruz.
	int xkoord;
	int ykoord;
	int en;
	int boy;
}koordinatlar; 


int teraziNesne(koordinatlar terazi, koordinatlar nesne);
int degdiMi(koordinatlar kukla , koordinatlar nesne, int genislikKukla, int uzunlukKukla); //bize girilenlerin deðip deðmediðini kontrol eder.(mouse-kukla-nesne vb)
int main(){
	int i=0,sayac=0,t;




	int ctrl=0,s=0 ,k=0, gameOver=0,sonuc=0;
	int * tasiyici;
	int skor[15]={0};
	int right = 0, klavye = 0, mouse = 0, sustur=0; //mouse-klavye secim ekranina gecis icin kontrol.
	PALETTE palette = {63,0,63};
	srand(time(NULL));
	int rastgeleSure = (4000+ rand()%6000)/CLOCKS_PER_SEC ; 
	int rastgeleSure2 = (20000 + rand()%20000)/CLOCKS_PER_SEC;
	int rastgelehiz[3];
	rastgelehiz[0] = rand()%3 +1;
	rastgelehiz[1] = rand()%3 +1;
	rastgelehiz[2] = rand()%3 +1;

 int  f1 ; //f1 f2 for döngüleri için.
//int rastgele;
	koordinatlar objeler[10] = {
	{rand()%900, -100 , 30,30},
	{rand()%900, -100, 35, 28},
	{rand()%900, -100, 27, 50},
	{rand()%900, -100, 50, 33},
	{rand()%900, -100, 50, 33},
	{rand()%900, -100, 50, 35},
	{rand()%900, -100, 60, 43},
    {rand()%900, -100, 50, 50},
	{rand()%900, -100, 50, 47} } ;
int teraziX=400, teraziY =500, mumyaX = 800 + rand()%100, mumyaY=450, mumyasolX = 20+rand()%100 ,mumyasolY = 450;

	koordinatlar kutsalobjeler[10] = {
	{rand()%900, -100 , 30,30},
	{rand()%900, -100, 35, 28},
	{rand()%900, -100, 27, 50} };
	koordinatlar terazi0 = {teraziX,teraziY,100,55};  //***********TERAZÝ  BURDA*********

	koordinatlar mumyaKukla = { mumyaX, mumyaY , 90, 120 };


	koordinatlar kutsalobj[3] ={ {rand()%900,-140,70,66},{rand()%900,-140,80,86},{rand()%900,-140,50,90}};

	koordinatlar mumyasolKukla = { mumyasolX, mumyasolY , 90, 120 };



	int kontrol1 = 0 , kontrol2 ,kontrol3, kontrol4;
	i = 5;
	Baslat();
	BITMAP *terazi[10];
	terazi[0] = load_bitmap("einstein.bmp",palette);
	terazi[1] = load_bitmap("terazi1.bmp",palette);
	terazi[2] = load_bitmap("terazi2.bmp",palette);
	terazi[3] = load_bitmap("terazi3.bmp",palette);
	terazi[4] = load_bitmap("terazi4.bmp",palette);
	terazi[5] = load_bitmap("terazi5.bmp",NULL);
	terazi[6] = load_bitmap("terazi6.bmp",palette);
	terazi[7] = load_bitmap("terazi7.bmp",palette);
	terazi[8] = load_bitmap("terazi8.bmp",palette);
	terazi[9] = load_bitmap("terazi9.bmp",palette);

	BITMAP* mumyaSol[8];
	mumyaSol[0] = load_bitmap("mumya0.bmp",NULL);
	mumyaSol[1] = load_bitmap("mumya1.bmp",NULL);
	mumyaSol[2] = load_bitmap("mumya2.bmp",NULL);
	mumyaSol[3] = load_bitmap("mumya3.bmp",NULL);
	mumyaSol[4] = load_bitmap("mumya4.bmp",NULL);
	mumyaSol[5] = load_bitmap("mumya5.bmp",NULL);


	BITMAP* mumya[8];
	mumya[0] = load_bitmap("mumyasol0.bmp",NULL);
	mumya[1] = load_bitmap("mumyasol1.bmp",NULL);
	mumya[2] = load_bitmap("mumyasol2.bmp",NULL);
	mumya[3] = load_bitmap("mumyasol3.bmp",NULL);
	mumya[4] = load_bitmap("mumyasol4.bmp",NULL);
	mumya[5] = load_bitmap("mumyasol5.bmp",NULL);



	BITMAP* obje[10];
	obje[0] = load_bitmap("obje0.bmp",palette);  //50X50 PARA
	obje[1] = load_bitmap("obje1.bmp",palette);  //50X27 ANAHTAR
	obje[2] = load_bitmap("obje2.bmp",palette);  //50X48 KALKAN
	obje[3] = load_bitmap("obje3.bmp",palette);  //50X33 PARÞÖMEN
	obje[4] = load_bitmap("obje4.bmp",palette);  //50X33 KÝTAP
	obje[5] = load_bitmap("obje5.bmp",palette);  //50X50 KUPA
	obje[6] = load_bitmap("obje6.bmp",palette);  //50X41 PARA2
	obje[7] = load_bitmap("obje7.bmp",palette);  //50X35 KÝTAPLAR
	obje[8] = load_bitmap("obje8.bmp",palette);  //60X43 HANÇER


	BITMAP *kutsalobje[3];
	kutsalobje[0] = load_bitmap("kutsalobje0.bmp",NULL);
	kutsalobje[1] = load_bitmap("kutsalobje1.bmp",NULL);
	kutsalobje[2] = load_bitmap("kutsalobje2.bmp",NULL);



	SAMPLE *Oynanis = load_sample("oynanis.wav");//oynarkenki oyun muzigi.
	SAMPLE *Giris = load_sample("giris.wav"); //ana menüdeki giris muzigi.
	BITMAP* KlavyeMouse = load_bitmap("klavye-mouse.bmp",NULL);
	BITMAP *TalimatlarArkaPlan = load_bitmap("TalimatlarArkaPlan.bmp",NULL);
    BITMAP *OyunArkaPlan = load_bitmap("oyunarkaplan4.bmp",NULL);
    BITMAP *button1 = load_bitmap("start.bmp",palette);
	BITMAP* button2 = load_bitmap("talimatlar.bmp",palette);
	BITMAP *GirisResmi = load_bitmap("Giris.bmp",NULL); //bu bize boþ bir bitmap yaratýcak.
	BITMAP *AraKatman = create_bitmap(920,583);
	BITMAP *AraKatman2 = create_bitmap(920,583);
	show_mouse(screen);
    play_sample(Giris,255,128,1000,0); //while ýn içine alýrsak döngüye giriyor.
    while(!key[KEY_ESC]){ 

		koordinatlar mouse = {mouse_x , mouse_y};
		koordinatlar kukla = {370,390};
		koordinatlar kukla2 = {335,460};
        //textprintf_ex(screen,font,10,10,makecol(255,100,200),-1,"X KOORD: %d , Y KOORD: %d",mouse.xkoord,mouse.ykoord); hata ayýklama 
		kontrol1 = degdiMi(kukla,mouse,144,52);
		kontrol2 = degdiMi(kukla2,mouse,218,64);
		draw_sprite(AraKatman,GirisResmi,0,0);  //ilk yüklememizi arakatmana yaptýk ki ekrana yazdýrýrken kesilmeler yaþanmasýn dosya hafýzada hazýr olsun.
	    draw_sprite(AraKatman,button1,370,390);
	    draw_sprite(AraKatman,button2,335,460);
		rest(10);
	draw_sprite(screen,AraKatman,0,0);
	if((kontrol1==1) && (mouse_b & 1))
		break;
	//clear_bitmap(AraKatman);

	if((kontrol2==1) && (mouse_b & 1)){
		while(!key[KEY_RIGHT]){
		clear_bitmap(AraKatman);
        draw_sprite(AraKatman,TalimatlarArkaPlan,0,0);
	    draw_sprite(screen,AraKatman,0,0);
		right++;

		}
	break;
	}

}

	    
		while(!(klavye>0 || mouse >0)){  //seçim yaparken birine týklarsa while dan çýkýlýr
			clear_bitmap(AraKatman);
		draw_sprite(AraKatman,KlavyeMouse,0,0);
		draw_sprite(screen,AraKatman,0,0);
		if((mouse_x>=56 && mouse_x <= 422 && mouse_y >= 202 && mouse_y <=285) && (mouse_b & 1))
			klavye++;
		if((mouse_x>=486 && mouse_x <= 843 && mouse_y >= 202 && mouse_y <=285)&& (mouse_b & 1))
			mouse++;
	   clear_bitmap(AraKatman);
		}

		int obj = rand()%3;
    int	rastgele[3];
    rastgele[0] = rand()%9;
	rastgele[1] = rand()%9;
	rastgele[2] = rand()%9;
    clock_t now, then, now1, then1, nowSkor, thenSkor;
    now = clock();
	then = clock();
	now1=clock(); //kutsal nesnelere için
	then1=clock();
	nowSkor=clock();
	thenSkor=clock(); //skor hesaplarken
	stop_sample(Giris);
		play_sample(Oynanis,255,128,1000,1);
	while(!gameOver){ // *****************DÜZELTMEYÝ UNUTMA*************
	now = clock();



		kontrol1 = 0; //kontrol degiskenlerimizi 0 ladik
		kontrol2 = 0;
		kontrol3 = 0;
    
    
	draw_sprite(AraKatman,OyunArkaPlan,0,0);
	if((now-then)/CLOCKS_PER_SEC>rastgeleSure)
		{
			if(k%2==0){
			draw_sprite(AraKatman,mumyaSol[s],mumyasolKukla.xkoord,mumyasolKukla.ykoord);
			s++;
			mumyasolKukla.xkoord++;
			rest(10);
			if(s>5)
				s=0;
			if(terazi0.xkoord<(mumyasolKukla.xkoord+mumyasolKukla.en))
				gameOver = 1;
			ctrl++;
			if(ctrl>300){
				ctrl=0;
				then=clock();
				rastgeleSure = (4000+ rand()%6000)/CLOCKS_PER_SEC ;
				mumyasolKukla.xkoord = 20 + rand()%100;
				k++;


			}
			}
			else{

			draw_sprite(AraKatman,mumya[s],mumyaKukla.xkoord,mumyaKukla.ykoord);
			s++;
			mumyaKukla.xkoord--;
			rest(10);
			if(s>5)
				s=0;
			if(terazi0.xkoord+terazi0.en>(mumyaKukla.xkoord))
				gameOver=1;
			ctrl++;
			if(ctrl>300){
				ctrl=0;
				then=clock();
				rastgeleSure = (4000+ rand()%6000)/CLOCKS_PER_SEC ;
				mumyaKukla.xkoord = 800 + rand()%100;
				k++;


			}
			}
		}
	if((now1-then1)/CLOCKS_PER_SEC>rastgeleSure2){
		draw_sprite(AraKatman,kutsalobje[obj],kutsalobj[obj].xkoord,kutsalobj[obj].ykoord);
		kutsalobj[obj].ykoord+=2;
	    sayac++;
		kontrol4 = teraziNesne(terazi0,kutsalobj[obj]);
		if(kontrol4!=0){
			skor[11-obj]+=500;
			if(skor[9]>=500 &&skor[10]>=500&&skor[11]>=500)
				gameOver=1;
			kutsalobj[obj].ykoord = -140;
		then1 = clock();
		obj = rand()%3;
		i=5;

		}if(kutsalobj[obj].ykoord>560){
			kutsalobj[obj].ykoord = -140;
		then1 = clock();
		obj = rand()%3;
		}

		    
	}



	draw_sprite(AraKatman,obje[rastgele[0]],objeler[rastgele[0]].xkoord,objeler[rastgele[0]].ykoord);
	draw_sprite(AraKatman,obje[rastgele[1]],objeler[rastgele[1]].xkoord,objeler[rastgele[1]].ykoord);
	draw_sprite(AraKatman,obje[rastgele[2]],objeler[rastgele[2]].xkoord,objeler[rastgele[2]].ykoord);
	draw_sprite(AraKatman,terazi[i],terazi0.xkoord,terazi0.ykoord);
	draw_sprite(screen,AraKatman,0,0);


	if(key[KEY_S]){ //s tusunua basildiginda
		sustur++;
		if((sustur%2==1)) //s tusuna tek sayida basarsa(bir kere basti sonra acmak icin bir daha basti vb)
		stop_sample(Oynanis);
		if(sustur%2==0)
			play_sample(Oynanis,255,128,1000,0);

	}

	if(mouse>0){///mouse ile oynatýr
	if(mouse_x>(terazi0.xkoord+terazi0.en/2)) {
		terazi0.xkoord+=4;
	if(terazi0.xkoord+terazi0.en==920)
		terazi0.xkoord=terazi0.xkoord;
	}
	if(mouse_x<(terazi0.xkoord+terazi0.en/2)){
		terazi0.xkoord-=4;
	if(terazi0.xkoord+terazi0.en==920)
		terazi0.xkoord=terazi0.xkoord;
	}
	}

	if(klavye>0){//klavye ile oynatýr.
	if(key[KEY_LEFT]) {
		if(terazi0.xkoord==0)
		terazi0.xkoord=terazi0.xkoord;
		else
		terazi0.xkoord-=4;
	}
	else if(key[KEY_RIGHT]){
		if(terazi0.xkoord+terazi0.en==920)
		terazi0.xkoord=terazi0.xkoord;
	else
		terazi0.xkoord+=4; 

	}
	}

	objeler[rastgele[0]].ykoord += rastgelehiz[0];
	objeler[rastgele[1]].ykoord += rastgelehiz[1];
    objeler[rastgele[2]].ykoord += rastgelehiz[2];
    kontrol1 = teraziNesne(terazi0,objeler[rastgele[0]]);
	kontrol2 = teraziNesne(terazi0,objeler[rastgele[1]]);
    kontrol3 = teraziNesne(terazi0,objeler[rastgele[2]]);
	if(kontrol1!=0){
	if(kontrol1==-1 && (rastgele[0]==0 ||rastgele[0]==1 || rastgele[0]==2 || rastgele[0]==3)){
		i -= 1; objeler[rastgele[0]].ykoord = -100; 
		skor[rastgele[0]] += 10;
	}



	if(kontrol1==-1 && (rastgele[0]==4 || rastgele[0]==5 ||  rastgele[0]==6)) {
		i -=2; objeler[rastgele[0]].ykoord = -100;
	    skor[rastgele[0]] += 20;
	}

	if(kontrol1==-1 && (rastgele[0]==7)){
		i -= 3; objeler[rastgele[0]].ykoord = -100;
		skor[rastgele[0]] += 30;
	}

	if(kontrol1==-1 && (rastgele[0]==8)){

		i-=4; objeler[rastgele[0]].ykoord = -100; 
	skor[rastgele[0]] += 40;
	}

	//þimdi sol kefe için.
	if(kontrol1==1 && (rastgele[0]==0 ||rastgele[0]==1 || rastgele[0]==2 || rastgele[0]==3)){
		i += 1; objeler[rastgele[0]].ykoord = -100;
		skor[rastgele[0]] += 10;
	}
	if(kontrol1==1 && (rastgele[0]==4 || rastgele[0]==5 ||  rastgele[0]==6)){
		i +=2; objeler[rastgele[0]].ykoord = -100;
		skor[rastgele[0]] += 20;
	}
	if(kontrol1==1 && (rastgele[0]==7)){
		i += 3; objeler[rastgele[0]].ykoord = -100;
		skor[rastgele[0]] += 30;
	}
	if(kontrol1==1 && (rastgele[0]==8)) {  /// puanlama-bug-farklý hýzlar-arkaplan-talimatlar-oynanýþ müziði-mumya-fare ile kontrol? - ikili oynanýþ? -
		i+=4;  objeler[rastgele[0]].ykoord = -100;
		skor[rastgele[0]] += 40;
	}
	}
	if(kontrol2!=0){
	if(kontrol2==-1 && (rastgele[1]==0 ||rastgele[1]==1 || rastgele[1]==2 || rastgele[1]==3)){
		i -= 1; objeler[rastgele[1]].ykoord = -100; 
	skor[rastgele[1]] += 10;
	}

	if(kontrol2==-1 && (rastgele[1]==4 || rastgele[1]==5 ||  rastgele[1]==6)) {
		i -=2; objeler[rastgele[1]].ykoord = -100; 
	skor[rastgele[1]] += 20;}

	if(kontrol2==-1 && (rastgele[1]==7)){
		i -= 3; objeler[rastgele[1]].ykoord = -100;
	skor[rastgele[1]] += 30;}

	if(kontrol2==-1 && (rastgele[1]==8)){

		i-=4; objeler[rastgele[1]].ykoord = -100; 
	skor[rastgele[1]] += 40;
	}

	//þimdi sol kefe için.
	if(kontrol2==1 && (rastgele[1]==0 ||rastgele[1]==1 || rastgele[1]==2 || rastgele[1]==3)){
		i += 1; objeler[rastgele[1]].ykoord = -100;
		skor[rastgele[1]] += 10;
	}
	if(kontrol2==1 && (rastgele[1]==4 || rastgele[1]==5 ||  rastgele[1]==6)){
		i +=2; objeler[rastgele[1]].ykoord = -100;
		skor[rastgele[1]] += 20;
	}
	if(kontrol2==1 && (rastgele[1]==7)){
		i += 3; objeler[rastgele[1]].ykoord = -100;
		skor[rastgele[1]] += 30;
	}
	if(kontrol2==1 && (rastgele[1]==8)) {  /// puanlama-bug-farklý hýzlar-birden çok nesne-arkaplan-talimatlar-oynanýþ müziði-mumya-fare ile kontrol? - ikili oynanýþ? -
		i+=4;  objeler[rastgele[1]].ykoord = -100;
		skor[rastgele[1]] += 40;
	}
	}

	if(kontrol3!=0){
	if(kontrol3==-1 && (rastgele[2]==0 ||rastgele[2]==1 || rastgele[2]==2 || rastgele[2]==3)){
		i -= 1; objeler[rastgele[2]].ykoord = -100; 
	skor[rastgele[2]] += 10;
	}

	if(kontrol3==-1 && (rastgele[2]==4 || rastgele[2]==5 ||  rastgele[2]==6)) {
		i -=2; objeler[rastgele[2]].ykoord = -100; 
	skor[rastgele[2]] += 20;}

	if(kontrol3==-1 && (rastgele[2]==7)){
		i -= 3; objeler[rastgele[2]].ykoord = -100;
	skor[rastgele[2]] += 30;}

	if(kontrol3==-1 && (rastgele[2]==8)){

		i-=4; objeler[rastgele[2]].ykoord = -100; 
	skor[rastgele[2]] += 40;
	}

	//þimdi sol kefe için.
	if(kontrol3==1 && (rastgele[2]==0 ||rastgele[2]==1 || rastgele[2]==2 || rastgele[2]==3)){
		i += 1; objeler[rastgele[2]].ykoord = -100;
		skor[rastgele[2]] += 10;
	}
	if(kontrol3==1 && (rastgele[2]==4 || rastgele[2]==5 ||  rastgele[2]==6)){
		i +=2; objeler[rastgele[2]].ykoord = -100;
		skor[rastgele[2]] += 20;
	}
	if(kontrol3==1 && (rastgele[2]==7)){
		i += 3; objeler[rastgele[2]].ykoord = -100;
		skor[rastgele[2]] += 30;
	}
	if(kontrol3==1 && (rastgele[2]==8)) {  /// puanlama-bug-farklý hýzlar-birden çok nesne-arkaplan-talimatlar-oynanýþ müziði-mumya-fare ile kontrol? - ikili oynanýþ? -
		i+=4;  objeler[rastgele[2]].ykoord = -100;
		skor[rastgele[2]] += 40;
	}
	}
	if(i>9 || i<1){
		gameOver=1;
	};
	 

	for(f1=0; f1<3 ; f1++)
		if(objeler[rastgele[f1]].ykoord==-100 ||objeler[rastgele[f1]].ykoord > 560){
			objeler[rastgele[f1]].ykoord=-100;
			rastgele[f1] = rand()%9;
			rastgelehiz[f1] = rand()%3 + 1;
		}


	rest(10);
	for(t=0;t<13;t++){
		if(skor[t]==0){
		sonuc+=skor[t];
		}

	}
	   clear_bitmap(AraKatman);
	   

	   now= clock();
	   now1=clock();
	}
	for(t=0;t<13;t++){

		sonuc+=skor[t];


	}
	stop_sample(Oynanis);
	rest(1000);

clear_bitmap(AraKatman);
BITMAP *OyunSonu=load_bitmap("OyunSonu.bmp",palette);
draw_sprite(AraKatman,OyunSonu,0,0);
	  textprintf_centre_ex(AraKatman, font, SCREEN_W / 2, 300,
                           makecol(255, 255, 255), -1,
                           "SKORUNUZ: %d",sonuc);
	  draw_sprite(screen,AraKatman,0,0);
	while(!key[KEY_ESC]){



	}
	   
                           

	 

	Bitir();
	return 0;

	}




END_OF_MAIN()

	void Baslat(){
int depth,res;
allegro_init();
depth = desktop_color_depth();
if(depth==0) depth = 32;
set_color_depth(depth);
res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,920,583,0,0);
if(res!=0){
allegro_message(allegro_error);
exit(-1);
}
install_timer();
install_keyboard();
install_mouse();
install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"A"); //ses yükleyicisi. bunu unutma.

}
void Bitir(){

clear_keybuf();
}

int degdiMi(koordinatlar kukla , koordinatlar nesne, int genislikKukla, int uzunlukKukla){
	int x1 = kukla.xkoord;
	int y1= kukla.ykoord;
	int x2= nesne.xkoord;
	int y2= nesne.ykoord;
	if(x1<=x2 && y1<=y2 && x1+genislikKukla>=x2 && y1+uzunlukKukla>=y2)
		return 1; //degdi mi? true(degdi)
	else
		return 0;
}

int teraziNesne(koordinatlar terazi0, koordinatlar nesne){
	int x1= terazi0.xkoord;
	int y1= terazi0.ykoord;
	int x2= nesne.xkoord;
	int y2= nesne.ykoord;
	int boy1= terazi0.boy;
	int genislik1=terazi0.en;
	int boy2= nesne.boy;
	int genislik2= nesne.en;
    if((x1<=x2) && (y1<=y2) && x1+genislik1>=x2 && y1+boy1>=y2){
		if((x2+genislik2/2)<=(x1+genislik1/2)) //nesnenin orta noktasý terazinin sol yarýsýna denk geliyorsa
			return -1; //burada terazi dizisinde bir önceki elemana geçeceðiz demek (resim dosyalarý bu sýraya göre tanýmlýlar.)
		else //sað yarýsý.
			return +1; //terazi dizisinde bir sonraki elemana geçeceðiz demek.
	}
	return 0;
}