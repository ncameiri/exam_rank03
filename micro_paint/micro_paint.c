#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct t_img_set{
int width;
int height;
char back_fill;
char *img;
}s_img_set;

typedef struct t_rect_set
{
char type_of_r;
float x;
float y;
float width;
float height;
char fill;
}s_rect_set;



int start_img(s_img_set * img, FILE*file){
    if(fscanf(file,"%d %d %c\n",&img->width,&img->height,&img->back_fill) !=3)
        return 0;
    img->img=malloc((img->width * img->height) + 1);
    
    int i=0;

    while(i<(img->width * img->height))
    {
        img->img[i]=img->back_fill;
        i++;
    }
    img->img[i]=0;

    return 1;
}

void put_into_img(s_img_set *im,s_rect_set fig){
    int i=0,k=0;

    while(i<im->width)
    {
        k=0;
        while(k<im->height)
        {
            if((((fig.x)<=i || ((fig.x) + (fig.width))>=i ) || ((fig.y)>=k || ((fig.y +fig.height)<=k))))
               {k++;continue;}
            else
             {im->img[(k*im->width) + i]=fig.fill;
                 if(fig.x - k >1 /*&& (fig.x + fig.width) -k <1*/)
                 im->img[(i*im->width) + k]=fig.fill;
             }
            k++;
        }
        i++;
    }
}

int draw_rect(s_img_set * img, FILE *file){
    s_rect_set fig;
    while(fscanf(file,"%c %f %f %f %f %c\n",&fig.type_of_r,&fig.x,&fig.y,&fig.width,&fig.height,&fig.fill) == 6)
    {
        put_into_img(img,fig);
    }
}

void img_draw(s_img_set * img){
    int i,k;
    k=i=0;

    while(i<img->height){
       write(1,img->img + (i * img->width),img->width);
       write(1,"\n",1);
       i++;
    }
}

int main(int argc, char*argv[]){
    FILE * file;
    s_img_set img;
    char *a="a";
    
    if(argc != 2)
    {
        write(1,"Error: argument\n",16);
        return 1;
    }
    file=fopen(argv[1],"r");
    if (!file)
    {
        write(1,"Error: Operation file corrupted\n",32);
        return 1;
    }
    if (!start_img(&img,file))
    {
        write(1,"Error: Operation file corrupted\n",32);
        return 1;   
    }
    if (!draw_rect(&img,file))
    {
        write(1,"Error: Operation file corrupted\n",32);
        return 1;   
    }

    img_draw(&img);


}