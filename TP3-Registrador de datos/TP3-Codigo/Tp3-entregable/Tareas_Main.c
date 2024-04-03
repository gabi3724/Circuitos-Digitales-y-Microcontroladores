/*
 * Tareas_Main.c
 *
 * Created: 26/6/2022 17:28:20
 *  Author: valen
 */ 

extern char Buffer[10];
extern int modo;
extern int haydato;
extern int modo;
extern int modoAnt;


void Tareas_Main_Tarea1(){
	int temp,temp_dec,hum;
	dht11_iniciaryleerdato(&temp, &temp_dec, &hum);
	Buffer[13]='0'+temp/10;
	Buffer[14]='0'+ temp%10;
	
	Buffer[16]='0'+temp_dec/10;
	Buffer[17]='0'+ temp_dec%10;
	
	Buffer[33]='0'+hum/10;
	Buffer[34]='0'+hum%10;
}

void Tareas_Main_leercomando(char *s){
	if (s[0]=='O'){
		if (s[1]=='N' || s[1]=='F'){
			if (s[1]=='N'){
				if (s[2]=='\n'){
					modo=1;
				}
				else{
					modoAnt=modo;
					modo=4;
				}
			}
			else{
				if (s[2]=='F'){
					if (s[3]=='\n'){
						modo=2;
					}
					else{
						modoAnt=modo;
						modo=4;
					}
				}
				else{
					modoAnt=modo;
					modo=4;
				}
			}
		}
		else{
			modoAnt=modo;
			modo=4;
		}
	}
	else{
		if (s[0]=='R'){
			if (s[1]=='S'){
				if (s[2]=='T'){
					if (s[3]=='\n'){
						modo=3;
					}
					else{
						modoAnt=modo;
						modo=4;
					}
				}
			}
			else{
				modoAnt=modo;
				modo=4;
			}
		}
		else{
			modoAnt=modo;
			modo=4;
		}
	}
}