#include<allegro.h>

void Baslat();
void Bitir();

int main(){
	
	int x = 50, y=50;
	Baslat();
	BITMAP *button1 = load_bitmap("button1.bmp",NULL);
	BITMAP *button2 = load_bitmap("button2.bmp",NULL);
	BITMAP *ArkaPlanResmi = load_bitmap("einstein.bmp",NULL); //bu bize boþ bir bitmap yaratýcak.
	BITMAP *AraKatman = create_bitmap(640,480);
	SAMPLE *Ses = load_sample("evillaugh.wav");  //BITMAP gibi. sample olarak bir dosyaya kaydediyoruz.
	while(!key[KEY_ESC]){
	blit(ArkaPlanResmi,AraKatman,0,0,0,0,640,480);  //ilk yüklememizi arakatmana yaptýk ki ekrana yazdýrýrken kesilmeler yaþanmasýn dosya hafýzada hazýr olsun.
	blit(button1,AraKatman,0,0,100,140,299,74);
	blit(button2,AraKatman,0,0,100,138,264,98);
	circlefill(AraKatman,x,y,25,makecol(250,0,0)); //dairemizi ara katmana yükledik.

	if(key[KEY_DOWN])
		y++;
	else if(key[KEY_UP]){
		y--;
		play_sample(Ses,255,128,1000,0); //buradaki deðiþkenleri kaðýtta açýkladým.
	}
	if(key[KEY_LEFT])
		x--;
	else if(key[KEY_RIGHT])
		x++;
	
	rest(10);
	blit(AraKatman,screen,0,0,0,0,640,480); //arakatmandan ekrana aktarýyoruz
	clear_bitmap(AraKatman); // artýk burda arakatmaný temizliyoruz.
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
res = set_gfx_mode(GFX_AUTODETECT_WINDOWED,640,480,0,0);
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