#include "ppmlib.h"

void escreve_strCor(ppm img, char s[], ponto o, int font_size, rgb cor){
	int i;
	ponto per=o;
	for(i=0;s[i]!=0;i++){
		escreve_charCor(img,s[i],per,font_size, cor);
		if(per.y+font_size*10>img->cab->largura){
			if(s[i+1]!=0 && s[i+1]!=' '){
				per.y+=font_size*4;
				escreve_hifenCor(img,per,font_size,cor);
			}
			per.y=o.y;
			per.x+=font_size*8;

		}
		else
			per.y+=font_size*4;
	}
}

void escreve_charCor(ppm img, char c, ponto o, int size, rgb cor){
	switch(c){
		case 'a':
		escreve_aCor(img,o,size,cor);
		break;
		case 'b':
		escreve_bCor(img,o,size,cor);
		break;
		case 'c':
		escreve_cCor(img,o,size,cor);
		break;
		case 'd':
		escreve_dCor(img,o,size,cor);
		break;
		case 'e':
		escreve_eCor(img,o,size,cor);
		break;
		case 'f':
		escreve_fCor(img,o,size,cor);
		break;
		case 'g':
		escreve_gCor(img,o,size,cor);
		break;
		case 'h':
		escreve_hCor(img,o,size,cor);
		break;
		case 'i':
		escreve_iCor(img,o,size,cor);
		break;
		case 'j':
		escreve_jCor(img,o,size,cor);
		break;
		case 'k':
		escreve_kCor(img,o,size,cor);
		break;
		case 'l':
		escreve_lCor(img,o,size,cor);
		break;
		case 'm':
		escreve_mCor(img,o,size,cor);
		break;
		case 'n':
		escreve_nCor(img,o,size,cor);
		break;
		case 'o':
		escreve_oCor(img,o,size,cor);
		break;
		case 'p':
		escreve_pCor(img,o,size,cor);
		break;
		case 'q':
		escreve_qCor(img,o,size,cor);
		break;
		case 'r':
		escreve_rCor(img,o,size,cor);
		break;
		case 's':
		escreve_sCor(img,o,size,cor);
		break;
		case 't':
		escreve_tCor(img,o,size,cor);
		break;
		case 'u':
		escreve_uCor(img,o,size,cor);
		break;
		case 'v':
		escreve_vCor(img,o,size,cor);
		break;
		case 'x':
		escreve_xCor(img,o,size,cor);
		break;
		case 'z':
		escreve_zCor(img,o,size,cor);
		break;
		case 'S':
		escreve_SCor(img,o,size,cor);
		break;
		case 'V':
		escreve_VCor(img,o,size,cor);
		break;
	}
}

/*Minusculas*/

//cor

void escreve_aCor(ppm img, ponto o, int size, rgb cor){
	int t = 5*size;
	ponto p[6];
	p[0]=cria_ponto(o.x,o.y+2*t/5);
	p[1]=cria_ponto(o.x+2*t/5,o.y+t/5);
	p[2]=cria_ponto(o.x+t,o.y+2*t/5);
	p[3]=cria_ponto(o.x+2*t/5,o.y+7*t/10);
	p[4]=cria_ponto(o.x+4*t/5,o.y+4*t/5);
	p[5]=cria_ponto(o.x+3*t/5,o.y+t+t/10);
	desCurvaCor(img,p[1],p[0],p[3],cor);
	desCurvaCor(img,p[1],p[2],p[3],cor);
	desCurvaCor(img,p[3],p[4],p[5],cor);
}

void escreve_bCor(ppm img, ponto o, int size, rgb cor){
	int t=4*size;
	ponto p[11];
	o.y+=t/5;
	p[0]=cria_ponto(o.x+4*t/5,o.y);
	p[1]=cria_ponto(o.x+t,o.y+t/10);
	p[2]=cria_ponto(o.x+4*t/5,o.y+3*t/10);
	p[3]=cria_ponto(o.x+t/5,o.y+3*t/5);
	p[4]=cria_ponto(o.x,o.y+3*t/10);
	p[5]=cria_ponto(o.x+t/5,o.y+t/10);
	p[6]=cria_ponto(o.x+t,o.y+t/5);
	p[7]=cria_ponto(o.x+4*t/5,o.y+4*t/5);
	p[8]=cria_ponto(o.x+11*t/20,o.y+17*t/20);
	p[9]=cria_ponto(o.x+t/2,o.y+7*t/10);
	p[10]=cria_ponto(o.x+t/2,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[2],cor);
	desCurvaCor(img,p[2],p[6],p[7],cor);
	desCurvaCor(img,p[7],p[8],p[9],cor);
	desCurvaCor(img,p[9],p[8],p[10],cor);
}

void escreve_cCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	p[0]=cria_ponto(o.x+3*t/5,o.y-t/20);
	p[1]=cria_ponto(o.x+t-t/5,o.y+t/20);
	p[2]=cria_ponto(o.x+3*t/5,o.y+t/10);
	p[3]=cria_ponto(o.x+t/5,o.y+5*t/10);
	p[4]=cria_ponto(o.x,o.y+19*t/20);
	p[5]=cria_ponto(o.x+3*t/5,o.y+5*t/10);
	p[6]=cria_ponto(o.x+4*t/5,o.y+4*t/5);
	p[7]=cria_ponto(o.x+7*t/10,o.y+9*t/10);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[3],p[5],cor);
	desCurvaCor(img,p[5],p[6],p[7],cor);
}


void escreve_dCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[11];
	o.x-=t/10;
	o.y-=t/5;
	p[0]=cria_ponto(o.x+4*t/5,o.y+t/5);
	p[1]=cria_ponto(o.x+7*t/10,o.y+t/10);
	p[2]=cria_ponto(o.x+7*t/10,o.y+4*t/10);
	p[3]=cria_ponto(o.x+2*t/5,o.y+t/2);
	p[4]=cria_ponto(o.x+2*t/5,o.y+8*t/10);
	p[5]=cria_ponto(o.x+t/5,o.y+15*t/20);
	p[6]=cria_ponto(o.x,o.y+9*t/10);
	p[7]=cria_ponto(o.x+7*t/10,o.y+7*t/10);
	p[8]=cria_ponto(o.x+4*t/5,o.y+t);
	p[9]=cria_ponto(o.x+t,o.y+t/2);
	p[10]=cria_ponto(o.x+7*t/10,o.y+8*t/10);
	desCurvaCor(img,p[0],p[1],p[4],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[4],p[7],p[8],cor);
	desCurvaCor(img,p[2],p[9],p[10],cor);
}

void escreve_eCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	p[0]=cria_ponto(o.x+7*t/10,o.y);
	p[1]=cria_ponto(o.x+9*t/10,o.y+t/5);
	p[2]=cria_ponto(o.x+7*t/10,o.y+t/2);
	p[3]=cria_ponto(o.x+t/10,o.y+9*t/10);
	p[4]=cria_ponto(o.x+t/10,o.y+7*t/10);
	p[5]=cria_ponto(o.x+t/10,o.y+3*t/10);
	p[6]=cria_ponto(o.x+11*t/10,o.y+4*t/5);
	p[7]=cria_ponto(o.x+7*t/10,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[2],cor);
	desCurvaCor(img,p[2],p[6],p[7],cor);
}

void escreve_fCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[11];
	o.x-=t/10;
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+17*t/20,o.y+5*t/18);
	p[2]=cria_ponto(o.x+6*t/10,o.y+t/2);
	p[3]=cria_ponto(o.x+3*t/10,o.y+7*t/9);
	p[4]=cria_ponto(o.x+t/10,o.y+2*t/3);
	p[5]=cria_ponto(o.x+2*t/10,o.y+4*t/9);
	p[6]=cria_ponto(o.x+11*t/10,o.y+7*t/18);
	p[7]=cria_ponto(o.x+15*t/10,o.y+2*t/3);
	p[8]=cria_ponto(o.x+10*t/10,o.y+8*t/9);
	p[9]=cria_ponto(o.x+9*t/10,o.y+5*t/9);
	p[10]=cria_ponto(o.x+5*t/10,o.y+4*t/5);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[2],cor);
	desCurvaCor(img,p[2],p[6],p[7],cor);
	desCurvaCor(img,p[7],p[8],p[2],cor);
	desCurvaCor(img,p[2],p[9],p[10],cor);
}

void escreve_gCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	o.x-=t/10;
	p[0]=cria_ponto(o.x+3*t/10,o.y+7*t/9);
	p[1]=cria_ponto(o.x+t/10,o.y+3*t/9);
	p[2]=cria_ponto(o.x+8*t/10,o.y+2*t/9);
	p[3]=cria_ponto(o.x+7*t/10,o.y+5*t/9);
	p[4]=cria_ponto(o.x+13*t/10,o.y+6*t/9);
	p[5]=cria_ponto(o.x+14*t/10,o.y+3*t/9);
	p[6]=cria_ponto(o.x+9*t/10,o.y+4*t/9);
	p[7]=cria_ponto(o.x+3*t/10,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[0],cor);
	desCurvaCor(img,p[0],p[4],p[5],cor);
	desCurvaCor(img,p[5],p[6],p[7],cor);
}

void escreve_hCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[10];
	o.x-=t/10;
	p[0]=cria_ponto(o.x+19*t/20,o.y);
	p[1]=cria_ponto(o.x+t,o.y+t/8);
	p[2]=cria_ponto(o.x+7*t/10,o.y+2*t/8);
	p[3]=cria_ponto(o.x+t,o.y+3*t/16);
	p[4]=cria_ponto(o.x+t/2,o.y+3*t/8);
	p[5]=cria_ponto(o.x+t/10,o.y+6*t/8);
	p[6]=cria_ponto(o.x+2*t/5,o.y+5*t/8);
	p[7]=cria_ponto(o.x+4*t/5,o.y+6*t/8);
	p[8]=cria_ponto(o.x+t,o.y+7*t/8);
	p[9]=cria_ponto(o.x+9*t/10,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[3],p[4],p[5],cor);
	desCurvaCor(img,p[2],p[6],p[7],cor);
	desCurvaCor(img,p[7],p[8],p[9],cor);
}

void escreve_iCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[6];
	o.x-=3*t/10;
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+9*t/10,o.y+t/5);
	p[2]=cria_ponto(o.x+2*t/5,o.y+t/2);
	p[3]=cria_ponto(o.x+4*t/5,o.y+3*t/5);
	p[4]=cria_ponto(o.x+9*t/10,o.y+9*t/10);
	p[5]=cria_ponto(o.x+t/5,o.y+t/2);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCirculoCorprn(img,p[5],size/100+1,cor);
}

void escreve_jCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[10];
	o.x-=t/10;
	p[0]=cria_ponto(o.x+8*t/10,o.y);
	p[1]=cria_ponto(o.x+4*t/5,o.y+3*t/8);
	p[2]=cria_ponto(o.x+2*t/5,o.y+9*t/16);
	p[3]=cria_ponto(o.x+7*t/10,o.y+4*t/8);
	p[4]=cria_ponto(o.x+t,o.y+5*t/8);
	p[5]=cria_ponto(o.x+7*t/5,o.y+11*t/16);
	p[6]=cria_ponto(o.x+8*t/5,o.y+4*t/8);
	p[7]=cria_ponto(o.x+13*t/10,o.y+t/6);
	p[8]=cria_ponto(o.x+2*t/5,o.y+7*t/8);
	p[9]=cria_ponto(o.x+t/5,o.y+9*t/16);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[6],p[7],p[3],cor);
	desLinhaCor(img,p[3],p[8],cor);
	desCirculoCorprn(img,p[9],size/100+1,cor);
}

void escreve_kCor(ppm img, ponto o, int size, rgb cor){
	int t=size*4;
	ponto p[7];
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+3*t/5,o.y+t/5);
	p[2]=cria_ponto(o.x,o.y);
	p[3]=cria_ponto(o.x+4*t/5,o.y+7*t/10);
	p[4]=cria_ponto(o.x+t,o.y+t);
	p[5]=cria_ponto(o.x+3*t/5,o.y+2*t/5);
	p[6]=cria_ponto(o.x,o.y+t);
	ponto l=cria_ponto(o.x+3*t/5,o.y+t/10);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,l,p[3],p[4],cor);
	desCurvaCor(img,l,p[5],p[6],cor);
}

void escreve_lCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	o.x-=t/20;
	p[0]=cria_ponto(o.x+8*t/10,o.y);
	p[1]=cria_ponto(o.x+t,o.y+t/5);
	p[2]=cria_ponto(o.x+8*t/10,o.y+t/2);
	p[3]=cria_ponto(o.x+t/10,o.y+8*t/10);
	p[4]=cria_ponto(o.x-t/10,o.y+6*t/10);
	p[5]=cria_ponto(o.x+t/10,o.y+2*t/10);
	p[6]=cria_ponto(o.x+12*t/10,o.y+4*t/5);
	p[7]=cria_ponto(o.x+8*t/10,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[2],cor);
	desCurvaCor(img,p[2],p[6],p[7],cor);
}

void escreve_mCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[7];
	o.x-=3*t/10;
	p[0]=cria_ponto(o.x+t,o.y-t/10);
	p[1]=cria_ponto(o.x,o.y+t/6);
	p[2]=cria_ponto(o.x+t,o.y+2*t/6);
	p[3]=cria_ponto(o.x,o.y+3*t/6+t/10);
	p[4]=cria_ponto(o.x+t,o.y+4*t/6);
	p[5]=cria_ponto(o.x,o.y+5*t/6+t/10);
	p[6]=cria_ponto(o.x+t,o.y+9*t/10);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
}

void escreve_nCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[5];
	o.x-=3*t/10;
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+t/4,o.y+7*t/20);
	p[2]=cria_ponto(o.x+9*t/10,o.y+9*t/20);
	p[3]=cria_ponto(o.x+2*t/5,o.y+8*t/10);
	p[4]=cria_ponto(o.x+t,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
}

void escreve_oCor(ppm img, ponto o, int size, rgb cor){
	int t=size*4;
	ponto p[8];
	o.x+=t/10;
	o.y+=t/10;
	p[0]=cria_ponto(o.x,o.y+4*t/5);
	p[1]=cria_ponto(o.x,o.y);
	p[2]=cria_ponto(o.x+4*t/5,o.y+t/10);
	p[3]=cria_ponto(o.x+t,o.y+4*t/5);
	p[4]=cria_ponto(o.x-t/14,o.y+t/5);
	p[5]=cria_ponto(o.x+2*t/5,o.y+t/2);
	p[6]=cria_ponto(o.x+t/2,o.y+4*t/5);
	p[7]=cria_ponto(o.x+t/5,o.y+t+t/10);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[0],cor);
	desCurvaCor(img,p[0],p[4],p[5],cor);
	desCurvaCor(img,p[5],p[6],p[7],cor);
}

void escreve_pCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[9];
	p[0]=cria_ponto(o.x+13*t/20,o.y+2*t/13);
	p[1]=cria_ponto(o.x+5*t/10,o.y+5*t/13);
	p[2]=cria_ponto(o.x+t/5,o.y+7*t/13);
	p[3]=cria_ponto(o.x+7*t/5,o.y+t/13);
	p[4]=cria_ponto(o.x+2*t/5,o.y+6*t/13);
	p[5]=cria_ponto(o.x+3*t/5,o.y+11*t/13);
	p[6]=cria_ponto(o.x+4*t/5,o.y+5*t/13);
	p[7]=cria_ponto(o.x+9*t/10,o.y+10*t/13);
	p[8]=cria_ponto(o.x+3*t/5,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desLinhaCor(img,p[2],p[3],cor);
	desCurvaCor(img,p[2],p[6],p[3],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[6],p[7],p[8],cor);
}

void escreve_qCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[9];
	o.x-=3*t/10;
	p[0]=cria_ponto(o.x+2*t/5,o.y+6*t/8);
	p[1]=cria_ponto(o.x+3*t/5,o.y+t/8);
	p[2]=cria_ponto(o.x+t,o.y+4*t/8);
	p[3]=cria_ponto(o.x+6*t/5,o.y+2*t/8);
	p[4]=cria_ponto(o.x+8*t/5,o.y+5*t/8);
	p[5]=cria_ponto(o.x+6*t/5,o.y+t);
	p[6]=cria_ponto(o.x+9*t/10,o.y+9*t/16);
	p[7]=cria_ponto(o.x+t,o.y+7*t/8);
	p[8]=cria_ponto(o.x+4*t/5,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[0],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[2],p[7],p[8],cor);
}

void escreve_rCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[7];
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+3*t/5,o.y+t/4);
	p[2]=cria_ponto(o.x+t/10,o.y+t/4);
	p[3]=cria_ponto(o.x+2*t/5,o.y+t/2);
	p[4]=cria_ponto(o.x+t/5,o.y+7*t/8);
	p[5]=cria_ponto(o.x+3*t/5,o.y+5*t/8);
	p[6]=cria_ponto(o.x+t,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
}

void escreve_sCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[5];
	o.x-=t/5;
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+4*t/5,o.y+t/2);
	p[2]=cria_ponto(o.x+3*t/10,o.y+2*t/5);
	p[3]=cria_ponto(o.x+t,o.y+t);
	p[4]=cria_ponto(o.x+t,o.y+3*t/5);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
}

void escreve_tCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+4*t/5,o.y+4*t/7);
	p[2]=cria_ponto(o.x+t/5,o.y+5*t/14);
	p[3]=cria_ponto(o.x+4*t/5,o.y+3*t/14);
	p[4]=cria_ponto(o.x+t,o.y+t);
	p[5]=cria_ponto(o.x+3*t/10,o.y+t/14);
	p[6]=cria_ponto(o.x+5*t/10,o.y+4*t/7);
	p[7]=cria_ponto(o.x+t/5,o.y+6*t/7);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[5],p[6],p[7],cor);
}

void escreve_uCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[7];
	p[0]=cria_ponto(o.x+t,o.y);
	p[1]=cria_ponto(o.x+9*t/10,o.y+t/7);
	p[2]=cria_ponto(o.x+t/5,o.y+5*t/14);
	p[3]=cria_ponto(o.x+3*t/2,o.y+t/2);
	p[4]=cria_ponto(o.x+t/5,o.y+5*t/7);
	p[5]=cria_ponto(o.x+8*t/10,o.y+6*t/7);
	p[6]=cria_ponto(o.x+9*t/10,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
}

void escreve_vCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[8];
	o.x+=t/10;
	p[0]=cria_ponto(o.x+3*t/5,o.y);
	p[1]=cria_ponto(o.x+t/5,o.y+t/10);
	p[2]=cria_ponto(o.x+3*t/10,o.y+3*t/10);
	p[3]=cria_ponto(o.x+6*t/5,o.y+6*t/10);
	p[4]=cria_ponto(o.x+3*t/10,o.y+8*t/10);
	p[5]=cria_ponto(o.x+t/10,o.y+7*t/10);
	p[6]=cria_ponto(o.x+3*t/10,o.y+6*t/10);
	p[7]=cria_ponto(o.x+2*t/5,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desLinhaCor(img,p[6],p[7],cor);
}

void escreve_xCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[11];
	p[0]=cria_ponto(o.x+3*t/5,o.y);
	p[1]=cria_ponto(o.x+t/10,o.y+2*t/7);
	p[2]=cria_ponto(o.x+t/5,o.y+4*t/7);
	p[3]=cria_ponto(o.x+3*t/10,o.y+9*t/14);
	p[4]=cria_ponto(o.x+3*t/5,o.y+9*t/14);
	p[5]=cria_ponto(o.x+t,o.y+t/2);
	p[6]=cria_ponto(o.x+4*t/5,o.y+t/7);
	p[7]=cria_ponto(o.x+3*t/10,o.y+5*t/7);
	p[8]=cria_ponto(o.x+t/5,o.y+t);
	p[9]=cria_ponto(o.x+9*t/10,o.y+5*t/7);
	p[10]=cria_ponto(o.x+t,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[4],p[7],p[8],cor);
	desCurvaCor(img,p[4],p[9],p[10],cor);
}

void escreve_zCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[9];
	p[0]=cria_ponto(o.x+2*t/5,o.y+2*t/13);
	p[1]=cria_ponto(o.x,o.y+8*t/13);
	p[2]=cria_ponto(o.x+2*t/5,o.y+11*t/13);
	p[3]=cria_ponto(o.x+t/2,o.y+8*t/13);
	p[4]=cria_ponto(o.x+6*t/10,o.y+6*t/13);
	p[5]=cria_ponto(o.x+6*t/5,o.y+11*t/13);
	p[6]=cria_ponto(o.x+8*t/5,o.y+7*t/13);
	p[7]=cria_ponto(o.x+4*t/5,o.y+7*t/13);
	p[8]=cria_ponto(o.x+3*t/5,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[6],p[7],p[8],cor);
}

/*Maiusculas*/

//cor

void escreve_SCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[9];
	o.x-=t;
	p[0]=cria_ponto(o.x+7*t/5,o.y);
	p[1]=cria_ponto(o.x+2*t,o.y+3*t/7);
	p[2]=cria_ponto(o.x+9*t/5,o.y+5*t/7);
	p[3]=cria_ponto(o.x+8*t/5,o.y+t);
	p[4]=cria_ponto(o.x+6*t/5,o.y+4*t/7);
	p[5]=cria_ponto(o.x+4*t/5,o.y+5*t/14);
	p[6]=cria_ponto(o.x+2*t/5,o.y+5*t/7);
	p[7]=cria_ponto(o.x+t/5,o.y+6*t/7);
	p[8]=cria_ponto(o.x+t/5,o.y+t);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
	desCurvaCor(img,p[4],p[5],p[6],cor);
	desCurvaCor(img,p[6],p[7],p[8],cor);
}

void escreve_VCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	ponto p[5];
	o.x-=t;
	p[0]=cria_ponto(o.x+t/5,o.y-t/5);
	p[1]=cria_ponto(o.x+4*t/5,o.y+t/6);
	p[2]=cria_ponto(o.x+2*t,o.y+t/3);
	p[3]=cria_ponto(o.x+t,o.y+t/2);
	p[4]=cria_ponto(o.x,o.y+13*t/15);
	desCurvaCor(img,p[0],p[1],p[2],cor);
	desCurvaCor(img,p[2],p[3],p[4],cor);
}

//Simbolos

//cor

void escreve_hifenCor(ppm img, ponto o, int size, rgb cor){
	int t=size*5;
	desCurvaCor(img,cria_ponto(o.x+4*t/10,o.y+t/10),cria_ponto(o.x+6*t/10,o.y+4*t/10),cria_ponto(o.x+5*t/10,o.y+9*t/10),cor);
}
