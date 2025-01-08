#include <stdio.h>

int maxim = 65536;
int bitmap[65536];
int weights1[65536];
int weights2[65536];
int weights3[65536];

int filesize = 66614;

void readimg();
int calculate();
void update();
int processimg();
void guessimg();
void train();
void outputs();


int main(){
    int i;
    for (i = 0; i < maxim; i++){
            weights1[i] = 0;
            weights2[i] = 0;
            weights3[i] = 0;
        }
    train();
}

void readimg(char loc[]){
    FILE *fptr;
    int x;
    fptr = fopen(loc,"rb");
    
    unsigned char tmpfile[filesize];
    
    fread(tmpfile, filesize,1, fptr);
    for(x = (filesize - maxim); x < filesize ; x++){
        
        if (tmpfile[x] == 0){
            bitmap[x - (filesize - maxim)] = 0;
        }else{
            bitmap[x - (filesize - maxim)] = 1;
        }
        
    }

    fclose(fptr);
}

int calculate(int weight){
    int temp = 0;
    int i = 0;
    
    if(weight == 1){
        for (i = 0; i < maxim; i++){
            temp = temp + (bitmap[i] * weights1[i]);
        }
    }else if(weight == 2){
        for (i = 0; i < maxim; i++){
            temp = temp + (bitmap[i] * weights2[i]);
        }
    }else if(weight == 3){
        for (i = 0; i < maxim; i++){
            temp = temp + (bitmap[i] * weights3[i]);
        }
    }
    return temp;
}

void update(int ans, int weight){
    int temp = 0;
    int i = 0;
    
    if(weight == 1){
        if (ans == 0){
            for (i = 0; i < maxim; i++){
                weights1[i] = weights1[i] - bitmap[i];
            }
        }else{
            for (i = 0; i < maxim; i++){
                weights1[i] = weights1[i] + bitmap[i];
            }
        }
    }else if(weight == 2){
        if (ans == 0){
            for (i = 0; i < maxim; i++){
                weights2[i] = weights2[i] - bitmap[i];
            }
        }else{
            for (i = 0; i < maxim; i++){
                weights2[i] = weights2[i] + bitmap[i];
            }
        }
    }else if(weight == 3){
        if (ans == 0){
            for (i = 0; i < maxim; i++){
                weights3[i] = weights3[i] - bitmap[i];
            }
        }else{
            for (i = 0; i < maxim; i++){
                weights3[i] = weights3[i] + bitmap[i];
            }
        }
    }
    
}

int processimg(int ans, int weight, int ist){
    
    if (weight == 1){
        if (ans == 0){
            if (calculate(1) > 0){
                ist += 1;
                update(0,1);
            }
        }else if (ans == 1){
            if (calculate(1) < 1){
                ist += 1;
                update(1,1);
            }
        }
    }
    if (weight == 2){
        if (ans == 0){
            if (calculate(2) > 0){
                ist += 1;
                update(0,2);
            }
        }else if (ans == 1){
            if (calculate(2) < 1){
                ist += 1;
                update(1,2);
            }
        }
    }
    if (weight == 3){
        if (ans == 0){
            if (calculate(3) > 0){
                ist += 1;
                update(0,3);
            }
        }else if (ans == 1){
            if (calculate(3) < 1){
                ist += 1;
                update(1,3);
            }
        }
    }
    //printf(" %d ",ist);
    return ist;
    
}

void guessimg(){
    if (calculate(1) >= 1){
        printf("Square\n");
    }else if (calculate(2) >= 1){
        printf("Circle\n");
    }else if (calculate(3) >= 1){
        printf("Triangle\n");
    }else{
        printf("Not like anything i had ever seen\n");
    }
}

void train(){
    int istrained = 0;
    while (istrained != 1){
        istrained = 1;
        int a = 0;
        while (a < 300){
            int i;
            char loc[15];
            sprintf(loc,"1/%d.bmp",a);
            readimg(loc);
            istrained = processimg(1,1,istrained);
            for(i = 0; i< 15; i++){
                loc[i] = 0;
            }
            
            sprintf(loc,"2/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,1,istrained);
            for(i = 0; i< 15; i++){
                loc[i] = 0;
            }
            
            /*
            sprintf(loc,"3/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,1,istrained);
            for(int i = 0; i< 15; i++){
                loc[i] = 0;
            }*/
            
            sprintf(loc,"1/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,2,istrained);
            for(i = 0; i< 15; i++){
                loc[i] = 0;
            }
            sprintf(loc,"2/%d.bmp",a);
            readimg(loc);
            istrained = processimg(1,2,istrained);
            for(i = 0; i< 15; i++){
                loc[i] = 0;
            }
            
            /*
            sprintf(loc,"3/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,3,istrained);
            for(int i = 0; i< 15; i++){
                loc[i] = 0;
            }*/
            
            
            /*
            sprintf(loc,"1/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,3,istrained);
            for(int i = 0; i< 15; i++){
                loc[i] = 0;
            }
            sprintf(loc,"2/%d.bmp",a);
            readimg(loc);
            istrained = processimg(0,3,istrained);
            for(int i = 0; i< 15; i++){
                loc[i] = 0;
            }
            sprintf(loc,"3/%d.bmp",a);
            readimg(loc);
            istrained = processimg(1,3,istrained);
            for(int i = 0; i< 15; i++){
                loc[i] = 0;
            }*/
            
            a ++;
            
            //printf("%d Images Trained\n",a);
            
            
        }
        printf("%d\n",istrained);
        
    }
    outputs(1);
    outputs(2);
}

void outputs(int num){
    FILE *fptr;
    FILE *fptw;
    
    int x;
    int y = 0;
    fptr = fopen("1/0.bmp","rb");
    
    unsigned char tmpfile[filesize];
    
    fread(tmpfile, filesize,1, fptr);
    
    if (num == 1){
        for(x = (filesize - maxim); x < filesize ; x++){
            tmpfile[x] = weights1[x - (filesize - maxim)] + 128;
        }   
        
        fptw = fopen("outp1.bmp","wb");
        fwrite(tmpfile, 1 , sizeof(tmpfile), fptw);
        
    }else if(num == 2){
        for(x = (filesize - maxim); x < filesize ; x++){
            tmpfile[x] = weights2[x - (filesize - maxim)] + 128;
        }   
        
        fptw = fopen("outp2.bmp","wb");
        fwrite(tmpfile, 1 , sizeof(tmpfile), fptw);
        
    }else if(num ==3){
        for(x = (filesize - maxim); x < filesize ; x++){
            tmpfile[x] = weights3[x - (filesize - maxim)] + 128;
        }   
        
        fptw = fopen("outp3.bmp","wb");
        fwrite(tmpfile, 1 , sizeof(tmpfile), fptw);
        
    }
    

    fclose(fptr);
    fclose(fptw);
}

