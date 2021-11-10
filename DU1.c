#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#define DBL_EPSILON __DBL_EPSILON__

double perimFigure(char chm, double s1,double s2, double s3){
    double result;

    switch (chm)
    {
    case 'T':
        result=s1+s2+s3;
        return result;
        break;
    case 'R':
        result=2*(s1+s2);
        return result;
        break;
    case 'S':
        result=4*s1;
        return result; 
        break;
    default:
        break;
    }
    return 0;

}

double areaFigure(char chm, double s1,double s2, double s3){
    double area;
    double halfPer;

    switch (chm){
        case 'T':
            halfPer=(s1+s2+s3)/2;
            area=sqrt(halfPer*(halfPer-s1)*(halfPer-s2)*(halfPer-s3));
            return area;
            break;
        case 'R':
            area=s1*s2;
            return area;
            break;
        case 'S':
            area=pow(s1,2.0);
            return area;
            break;
        default:
            break;
        }
    return 0;
}

int isValidFigure(char chm, double s1, double s2, double s3){
    switch (chm)
    {
        case 'T':
            if((s1+s2>s3)&&(s1+s3>s2)&&(s2+s3>s1)&&(s1>0)&&(s2>0)&&(s3>0)
            &&!(fabs(s1+s2-s3)<=100*DBL_EPSILON*fabs(s1+s2+s3))
            &&!(fabs(s1+s3-s2)<=100*DBL_EPSILON*fabs(s1+s3+s1))
            &&!(fabs(s2+s3-s1)<=100*DBL_EPSILON*fabs(s2+s3+s1))){
            
                return 0;  
            }else{
                printf("Nespravny vstup.\n");
                return 1;
            }   
            break;
        case 'R':
            if ((s1==s2)||(s1<=0)||(s2<=0)){
                printf("Nespravny vstup.\n");
                return 1;
            }else{
                
                return 0;
            }
        case 'S':
            if(s1>0){
                return 0;
            }else{
                printf("Nespravny vstup.\n");
                return 1;
            }



        default:
            //return 1;
            break;
    }
    return 0;
}

const char* figureNameYes(char chm){
    switch (chm)
    {
    case 'T':
        return "trojuhelnik";
        break;
    case 'R':
        return "obdelnik";
        break;
    
    case 'S':
        return "ctverec";
        break;
    default:
        break;
    }
return 0;

}

char findCharSignPer(double per, double per2){
    
    if((fabs(per-per2)<=1024*DBL_EPSILON*(fabs(per)+fabs(per2)))){
        return '=';
    }
    else if(per<per2){
        return '<';
    }
    else if(per>per2){
        return '>';
    }
    return 0;
    
}
char findCharSignArea(double area1, double area2){
    if((fabs(area1-area2)<=128*DBL_EPSILON*(fabs(area1)+fabs(area2)))){
        return '=';
    }
    else if(area1<area2){
        return '<';
    }
    else if(area1>area2){
        return '>';
    }
    return 0;
  
}

int main(){
    double a=0, b=0, d=0, a2=0, b2=0, d2=0, perT=0, perR=0, perS=0, areaT=0,
    areaR=0, areaS=0,perT2=0, perR2=0, perS2=0, areaT2=0, areaR2=0, areaS2=0,per=0,per2=0,area=0,area2=0;
    char c=0, c2=0; int read=0;
    char compare=0, compare2=0;
    printf("Obrazec #1\n");
    scanf(" %c",&c);

    switch (c){
        case 'T':
            if(scanf("%lf %lf %lf",&a,&b,&d )!=3){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c,a,b,d)==0){
                    perT=perimFigure(c,a,b,d);
                    areaT=areaFigure(c,a,b,d);
                    per=perT;
                    area=areaT;
                    /*printf("%c %lf %lf %lf\n", c,a,b,d);
                    printf("%.32lf and %lf and %s\n",per, area, figureNameYes(c));*/   
                }
                else{
                    return 1;
                }
            }
            break;

        case 'R':
            read = scanf(" %lf %lf",&a,&b );
            if(read!=2){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c,a,b,d)==0){
                    perR=perimFigure(c,a,b,d);
                    per=perR;
                    areaR=areaFigure(c,a,b,d);
                    area=areaR;
                    /*printf("%c %lf %lf\n", c,a,b);
                    printf("%lf and %lf\n",per, area); */   

                }
                else{
                    return 1;
                }
            }
            break;

        case 'S':
            read = scanf(" %lf",&a );
            if(read!=1){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c,a,b,d)==0){
                    perS=perimFigure(c,a,b,d);
                    areaS=areaFigure(c,a,b,d);
                    per=perS;
                    area=areaS;
                   /* printf("%c %lf\n", c,a);
                    printf("%lf and %lf\n",per, area); */   

                }
                else{
                    return 1;
                } 
            }
            break;
        default:
            printf("Nespravny vstup.\n");
            return 1;
            break;
    }
    





    printf("Obrazec #2\n");
    scanf(" %c ",&c2);
    switch(c2){
    case 'T':
            read = scanf("%lf %lf %lf",&a2,&b2,&d2 );
            if(read!=3){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c2,a2,b2,d2)==0){
                    perT2=perimFigure(c2,a2,b2,d2);
                    areaT2=areaFigure(c2,a2,b2,d2);
                    per2=perT2;
                    area2=areaT2;
                   /* printf("%c %lf %lf %lf\n", c2,a2,b2,d2);
                    printf("%lf and %lf\n",per2, area2);*/   
                }
                else{
                    return 1;
                }
            }
            break;

        case 'R':
            read = scanf(" %lf %lf",&a2,&b2 );
            if(read!=2){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c2,a2,b2,d2)==0){
                    perR2=perimFigure(c2,a2,b2,d2);
                    areaR2=areaFigure(c2,a2,b2,d2);
                    per2=perR2;
                    area2=areaR2;
                    /*printf("%c %lf %lf\n", c2,a2,b2);
                    printf("%.32lf and %lf\n",per2, area2);  */  

                }
                else{
                    return 1;
                }
            }
            break;

        case 'S':
            read = scanf(" %lf",&a2 );
            if(read!=1){
                printf("Nespravny vstup.\n");
                return 1;
            }
            else{
                if(isValidFigure(c2,a2,b2,d2)==0){
                    perS2=perimFigure(c2,a2,b2,d2);
                    areaS2=areaFigure(c2,a2,b2,d2);
                    per2=perS2;
                    area2=areaS2;
                    /*printf("%c %lf\n", c2,a2);
                    printf("%lf and %lf\n",per2, area2);*/    

                }
                else{
                    return 1;
                }
            }
            break;
        default:
            printf("Nespravny vstup.\n");
            return 1;
            break;
    }
    compare=findCharSignPer(per,per2);
    compare2=findCharSignArea(area, area2);
     // printf("the perimeter of the first figure is %c than second figure\n",compare);
    //printf("the area of the first figure is %c than second figure\n", compare2);
    printf("Obvod: %s #1 %c %s #2\n",figureNameYes(c), compare, figureNameYes(c2));
    printf("Obsah: %s #1 %c %s #2\n",figureNameYes(c), compare2, figureNameYes(c2));

   // printf("%s",compare=findCharSignPer(per,per2));

    //printf("Obvod: %s #1 %c %s #2");

  return 0;
    
}  