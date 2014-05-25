#include "REG320.h"
#include<intrins.h>

data char nodata_a[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
data char nodata_b[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
data char nodata_c[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
//nodata 拿來存運算元

data unsigned char row1[16] = {'D','0','1','8','2','7','3','2','0','0',':','0','0',':','0','0'};
data unsigned char row2[16] = {'X','X','X','X','X','X','X','X','X','X','X','X','X','X','X','X'};
// row1 row2 分別是LCM的兩行display buffer

unsigned char pao_ma_run = 1; // 跑馬燈要不要動的旗標
unsigned char dgt_clk_rest = 0; //要不要重置時鐘的旗標
unsigned char HTimer1 = 0xF0; // 高位Timer計時器
unsigned char LTimer1 = 0xFF; // 低位Timer計時器
unsigned char timeCount = 0x00; // 跑馬燈的累加器
unsigned char timeFull = 60; // 累計多少跑馬燈動一次
unsigned char lcm_cmd = 0x00; //要對LCM下甚麼命定
unsigned char op = 0; // 存放案了甚麼運算子

void io(void); //初始化
void setLCM(void); // 送指令給LCM 相當於組語範例 WriteIR
void intt(void); // 中斷發生會執行這個涵式 (跑馬燈還有時鐘)
void pao_ma_light(void); // 跑馬燈
void digitalclock(void); // 時鐘
void delay(unsigned char dt); //延遲
void display(void); //顯示到LCM

unsigned char key(void); //掃描鍵盤
void loadKeytoData(void); // 處理鍵盤輸入的值
void loadDatatoRow(char input[]); //將要顯示的值轉成ASCII放到display buffer
void add(void); //加法
void sub(void); //減法
void mul(void); //乘法
void div(void); //除法

void io(void)//IO初始化
{
	P1MODL = 0x00; //鍵盤
	P1MODH = 0xAA; //鍵盤
	P3MODH = 0xA8; //LCM指令線
	p0oe = 0xff;   //LCM資料線
	P0 = 0x00;
	P1 = 0x00;
	P3 = 0x00;
	delay(50);
	//初始化LCM
	lcm_cmd = 0x30;
	setLCM();
	setLCM();
	setLCM();
	lcm_cmd = 0x38;
	setLCM();
	lcm_cmd = 0x08;
	setLCM();
	lcm_cmd = 0x01;
	setLCM();
	lcm_cmd = 0x06;
	setLCM();
	lcm_cmd = 0x0e;
	setLCM();
	return;
}

void setLCM()
{
	RS_LCM = 0;
	RS_LCM = 0;
	RW_LCM = 0;
	RW_LCM = 0;
	EN_LCM = 1;
	EN_LCM = 1;
	P0 = lcm_cmd;
	P0 = lcm_cmd;
	delay(5);
	EN_LCM = 0;
	EN_LCM = 0;
	return;
}

void intt() interrupt 3 using 3
{
	TH1 = HTimer1;
	TL1 = LTimer1;
	if(timeCount >= timeFull && pao_ma_run == 1){
		pao_ma_light();
		timeCount = 0;
	}
	if(dgt_clk_rest == 0){
		digitalclock();
	}
	display();
	timeCount += 2;
	return;
}

void pao_ma_light()
{
	unsigned char tmp = 0;
	tmp = row1[7];
	row1[7] = row1[6];
	row1[6] = row1[5];
	row1[5] = row1[4];
	row1[4] = row1[3];
	row1[3] = row1[2];
	row1[2] = row1[1];
	row1[1] = row1[0];
	row1[0] = tmp;
	return;
}

void digitalclock()
{
	unsigned char time[6];
	time[0] = row1[8]-48;
	time[1] = row1[9]-48;
	time[2] = row1[11]-48;
	time[3] = row1[12]-48;
	time[4] = row1[14]-48;
	time[5] = row1[15]-48;
	time[5]++;
	if(time[5] > 9){
		time[4] += time[5]/10;
	}
	if(time[4] > 5){
		time[3] += time[4]/6;
	}
	if(time[3] > 9){
		time[2] += time[3]/10;
	}
	if(time[2] > 5){
		time[1] += time[2]/6;
	}
	if(time[1] > 9){
		time[0] += time[1]/10;
	}
	if(time[0] >= 1 && time[1] >= 2){
		time[0] = 0;
		time[1] = 0;
	}
	time[5] = time[5]%10;
	time[4] = time[4]%6;
	time[3] = time[3]%10;
	time[2] = time[2]%6;
	time[1] = time[1]%10;
	row1[8] = time[0]+48;
	row1[9] = time[1]+48;
	row1[11]= time[2]+48;
	row1[12]= time[3]+48;
	row1[14]= time[4]+48;
	row1[15]= time[5]+48;
	return;
}

void delay(char dt)//呼叫nop，傳入值是nop的次數
{
	for(dt; dt>0; dt--){
		_nop_();
	}
	return;
}

void display(void)//顯示功能
{
	unsigned char i;
	lcm_cmd = 0x80;
	setLCM();//顯示第一行
	for(i=0; i<=15; i++){
		RS_LCM = 1;
		RS_LCM = 1;
		RW_LCM = 0;
		RW_LCM = 0;
		EN_LCM = 1;
		EN_LCM = 1;
		P0 = row1[i];
		P0 = row1[i];
		EN_LCM = 0;
		EN_LCM = 0;
	}
	lcm_cmd = 0xC0;
	setLCM();//顯示第二行
	for(i=0; i<=15; i++){
		RS_LCM = 1;
		RS_LCM = 1;
		RW_LCM = 0;
		RW_LCM = 0;
		EN_LCM = 1;
		EN_LCM = 1;
		P0 = row2[i];
		P0 = row2[i];
		EN_LCM = 0;
		EN_LCM = 0;
	}
	return;
}

void main(void)
{
	io();
	IE = 0x88;
	TMOD = 0x10;
	TH1 = HTimer1;
	TL1 = LTimer1;
	TR1 = 1;
	while(1){
		display();
		loadKeytoData();
	}
}

unsigned char key(void)
{
	unsigned char keyvalue = 255;//讀取鍵盤的回傳值，沒有按回傳255
	unsigned char keypress = 255;//判斷按鍵是否按著，沒按是255

	while(1){
		display();
		keypress = 255;

		P1 = 0xef;
		P1 = 0xef;
		if(P1 == 0xee){
			keyvalue = 1;//鍵盤回傳值1
			keypress = 0;//有按鍵盤所以值改0
		}
		if(P1 == 0xed){
			keyvalue = 2;//以下類推
			keypress = 0;
		}
		if(P1 == 0xeb){
			keyvalue = 3;
			keypress = 0;
		}
		if(P1 == 0xe7){
			keyvalue = 11;
			keypress = 0;
		}

		P1 = 0xdf;
		P1 = 0xdf;
		if(P1 == 0xde){
			keyvalue = 4;
			keypress = 0;
		}
		if(P1 == 0xdd){
			keyvalue = 5;
			keypress = 0;
		}
		if(P1 == 0xdb){
			keyvalue = 6;
			keypress = 0;
		}
		if(P1 == 0xd7){
			keyvalue = 12;
			keypress = 0;
		}

		P1 = 0xbf;
		P1 = 0xbf;
		if(P1 == 0xbe){
			keyvalue = 7;
			keypress = 0;
		}
		if(P1 == 0xbd){
			keyvalue = 8;
			keypress = 0;
		}
		if(P1 == 0xbb){
			keyvalue = 9;
			keypress = 0;
		}
		if(P1 == 0xb7){
			keyvalue = 13;
			keypress = 0;
		}

		P1 = 0x7f;
		P1 = 0x7f;
		if(P1 == 0x7E){
			keyvalue = 255;
			keypress = 0;
		}
		if(P1 == 0x7d){
			keyvalue = 0;
			keypress = 0;
		}
		if(P1 == 0x7b){
			keyvalue = 16;
			keypress = 0;
		}
		if(P1 == 0x77){
			keyvalue = 14;
			keypress = 0;
		}
		
		if(P1 == 0x7C){
			keyvalue = 15;
			keypress = 0;
		}//0011

		dgt_clk_rest = 0;
		if(P1 == 0x7A){
			keyvalue = 255;
			keypress = 0;
			dgt_clk_rest = 1;
			row1[8]  = '0';
			row1[9]  = '0';
			row1[11] = '0';
			row1[12] = '0';
			row1[14] = '0';
			row1[15] = '0';
			continue;
		}//0101

		pao_ma_run = 1;
		if(P1 == 0x76){
			pao_ma_run = 0;
			keyvalue = 255;
			keypress = 0;
			row1[7] = '2';
			row1[6] = '3';
			row1[5] = '7';
			row1[4] = '2';
			row1[3] = '8';
			row1[2] = '1';
			row1[1] = '0';
			row1[0] = 'D';
			continue;
		}//0110
		//1248
		
		delay(36);
		if(keypress == 255){
			return keyvalue;
		}//直到按鍵放開 (keypress=255) 才回傳鍵值
	}
}

void loadKeytoData()
{
	unsigned char i;
	unsigned char k = key();
	while(k != 255){//有按鍵的話(回傳值不等於255)判斷按了哪顆做不同的事
		if (k < 10) {//0~9是正常的值
			for(i=15; i>0; i--){
				nodata_b[i] = nodata_b[i-1];
			}
			nodata_b[0] = k;
			loadDatatoRow(nodata_b);
			break;
		}

		else if(k == 16 || k == 12 || k == 13 || k == 14){//分別是加減乘除
			op = k;
			for(i=0; i<16; i++){
				nodata_a[i] = nodata_b[i];
				nodata_b[i] = 0;
			}
			break;
		}

		else if(k == 15){//清除
			for(i = 0; i < 16; i++){
				nodata_a[i] = 0;
				nodata_b[i] = 0;
				nodata_c[i] = 0;
			}
			op = 0;
			loadDatatoRow(nodata_c);
			break;
		}

		else if(k == 11){//等號鍵，判斷剛按了哪顆建，做計算結果
			switch(op){
				case 16:
					add();
					for(i=0; i<16; i++){
						nodata_a[i] = nodata_c[i];
						nodata_b[i] = 0;
						nodata_c[i] = 0;
					}
					loadDatatoRow(nodata_a);
					break;
				case 14:
					sub();
					for(i=0; i<16; i++){
						nodata_a[i] = nodata_c[i];
						nodata_b[i] = 0;
						nodata_c[i] = 0;
					}
					loadDatatoRow(nodata_a);
					break;
				case 12:
					mul();
					for(i=0; i<16; i++){
						nodata_a[i] = nodata_c[i];
						nodata_b[i] = 0;
						nodata_c[i] = 0;
					}
					loadDatatoRow(nodata_a);
					break;
				case 13:
					div();
					for(i=0; i<16; i++){
						nodata_a[i] = nodata_c[i];
						nodata_b[i] = 0;
						nodata_c[i] = 0;
					}
					loadDatatoRow(nodata_a);
					break;
			}
			break;
		}

		else{
			for(i = 0; i < 16; i++){
				nodata_a[i] = 8;
				nodata_b[i] = 8;
				nodata_c[i] = 8;
			}
			op = 0;
			loadDatatoRow(nodata_c);
			break;
		}
	}
	return;
}

void loadDatatoRow(unsigned char input[])
{
	unsigned char i,c=0;

	for(i=15; i>0; i--){
		if(input[i] == 0)
			c++;
		else
			break;
	}//計算前面連續幾個零

	for (i = 0; i < 16; i++){
		if(c>0){
			row2[i] = ' ';//前面連續的零顯示空白字元
			c--;
		}
		else{
			row2[i] = input[15-i] + 48;//轉ASCII
		}
	}
	return;
}

void add()
{
	unsigned char i;
	for (i=0; i < 16; i++) {  // 對應的位數相加
		nodata_c[i] += nodata_a[i] + nodata_b[i];
		if (i<15){
			nodata_c[i+1] += nodata_c[i] / 10;    // 進位
			nodata_c[i] %= 10;  
		}
		else{
			nodata_c[i] %= 10;
		}
	}
	return;
}

void sub()
{
	unsigned char i;
	for(i=0; i<16; i++){
		nodata_c[i] = nodata_a[i] - nodata_b[i];
	}
	for(i=0; i<16-1; i++){ // 一口氣借位和補位
		if(nodata_c[i] < 0){
			nodata_c[i+1]--;           // 借位
			nodata_c[i] += 10;         // 補位
		}
	}
	return;
}

void mul()
{
	unsigned char i,j;
	for (i=0; i<16; i++){
		nodata_c[i] = 0;
	}
	for (i=0; i<16; i++){
		for (j=0; j<16; j++){
			if (i+j < 16){
				nodata_c[i+j] += nodata_a[i] * nodata_b[j];
			}
			//利用多項式相乘的概念
			// X^(i+j) = X^i * X^j

			if (j < 15){
				nodata_c[j+1] += nodata_c[j] / 10;  //進位
				nodata_c[j] %= 10;
			}
			else{
				nodata_c[j] %= 10;
			}
		}
	}
	return;
}

void div()
{
	char tmul[10][17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char tsub[17] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	char i,k,j,cmp;//cmp == resault of largerthan;

	for (k=0; k<=9; k++){
		//mul(b[], k, tmul[]);
			for(j=0; j<=17; j++){
				tmul[k][j] = 0;
			}
			for (j=0; j<16; j++){
				tmul[k][j] += nodata_b[j] * k;
				tmul[k][j+1] += tmul[k][j] / 10;
				tmul[k][j] %= 10;
			}//mul
	}//先把除數*0~9的結果存起來

	for (i=16-1; i>=0; i--){

		for(j = 17-1; j>0; j--){
			tsub[j] = tsub[j-1];
		}
		tsub[0] = nodata_a[i];
		//不斷對其要除的位數

		for (k=9; k>=0; k--){
			//比較 被除數 > (除數*K) 
			//如果小於K即為正確商值
			for (j=17-1; j>=0; j--){// 從高位數開始比，對應的位數相比較
				cmp = 1;
				if (tsub[j] != tmul[k][j]){// 發現 a b 不一樣大
					if(tsub[j] > tmul[k][j]){
						cmp = 1;
						break;
					}
					else{//tsub[j] < tmul[k][j]
						cmp = 0;
						break;
					}
				}
			}//largerthan

			if (cmp == 1){

				nodata_c[i] = k;
				//此時的K值就是當位數正確的商

				//sub(tsub[], tmul[], tsub[])
				for (j=0; j<16; j++){
					tsub[j] = tsub[j] - tmul[k][j];
				}
				for (j = 0; j<16-1; j++){ // 一口氣借位和補位
					if (tsub[j] < 0){
						tsub[j+1]--;           // 借位
						tsub[j] += 10;         // 補位
					}
				}//sub
				//被除數 - (除數*正確的商) 剩下來的餘數繼續下一位數對齊

				break;
			}//處理每位的商&餘數

		}
	}
	return;
}
