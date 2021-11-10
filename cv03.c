#include <stdio.h>

int main(void){
	printf("Zadejte barvu v RGB formatu:\n");
	int a,b,c,read;
	read=scanf(" rgb ( %d , %d , %d )", &a, &b, &c);
	if ((a<0||a>255||b<0||b>255||c<0||c>255)||read!=3){
		printf("Nespravny vstup.\n");
	}
	else{
		if(a>-1&&a<16&&b>16&&c>16){
		
			printf("#0%X%X%X\n",a,b,c);
		}
		else if(b>-1&&b<16&&a>16&&c>16){
			printf("#%X0%X%X\n",a,b,c);
		}
		else if(c>-1&&c<16&&a>16&&b>16){
			printf("#%X%X0%X\n",a,b,c);
		}
		else if((a>-1&&a<16)&&(b>-1&&b<16)&&c>16){
			printf("#0%X0%X%X\n",a,b,c);
		}
		else if((a>-1&&a<16)&&(c>-1&&c<16)&&b>16){
			printf("#0%X%X0%X\n",a,b,c);
		}
		else if((b>-1&&b<16)&&(c>-1&&c<16)&&a>16){
			printf("#%X0%X0%X\n",a,b,c);
		}
		else if((b>-1&&b<16)&&(c>-1&&c<16)&&a>-1&&a<16){
			printf("#0%X0%X0%X\n",a,b,c);
		}
		else{
			printf("#%X%X%X\n",a,b,c);
		}
	}
	
	
	


	return 0;
}

