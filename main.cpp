#include <raylib.h>
#include "ball.h"
#include <cmath>
#include <bits/stdc++.h>
#include <iostream>
#include <string>

int l=0,i,j,k,dmg_total=0,s,l2=0,q,r,l3=1,n,max;
int Basic_damage=100; //character basic ability
/*int swap(int m,int n){
    int temp=n;
    n=m;
    m=temp;
    return 0;
}*/
int check_down(int a[5][7],int b[5][7],int pos_x,int pos_y,int n){
    if(a[pos_x][pos_y]!=a[pos_x][pos_y+1] or pos_y+1>=n){
        if(l>1){
        dmg_total=dmg_total+pow((double)Basic_damage,1+0.05*l);
        for(j=pos_y-l;j<pos_y+1;j++){
            b[pos_x][j]=a[pos_x][j]*-1;
        }
        return 0;
        }
    }
    else if(a[pos_x][pos_y]==a[pos_x][pos_y+1]){
        l=l+1;
        check_down(a,b,pos_x,pos_y+1,n);
        return 0;
    }
  return 0;
}
int check_right(int a[5][7],int b[5][7],int pos_x,int pos_y,int n){
    if(a[pos_x][pos_y]!=a[pos_x+1][pos_y] or pos_x+1>=n ){
        if(l>1){
            dmg_total=dmg_total+pow((double)Basic_damage,1+0.05*l);
            for(k=pos_x-l;k<pos_x+1;++k){
                b[k][pos_y]=a[k][pos_y]*-1;         
                //return i;
            }
        }
    }
    else if(a[pos_x][pos_y]==a[pos_x+1][pos_y]){
        l=l+1;
        check_right(a,b,pos_x+1,pos_y,n);
    }
  return 0;
}
int falling_down_info (int a[5][7],int b[5][7],int c[5][7],int d[5][7],int lineX,int lineY_num){ 
    //a=Mapcolor,b=distanceFD,c=real_num,d=num0
    int distance=0,m=0,n=6,i=0;
    while(i<lineY_num){
        if(a[lineX][lineY_num-i-1]==0){
            distance++;
            b[lineX][lineY_num-i-1]=a[lineX][lineY_num-i-1];
            c[lineX][m]=GetRandomValue(1,4);
            d[lineX][m]=1;
            m++;            
        }
        else if(a[lineX][lineY_num-i-1]!=0){
            b[lineX][lineY_num-i-1]=distance;
            c[lineX][n]=a[lineX][lineY_num-i-1];
            d[lineX][n]=0;
            n--;
        }
        i++;
    }
    return 0; 
}
int detect(int a[5][7],int b[5][7]){
    //a=mapcolor,b=delta2
    n=0;
    for(i=0;i<5;i++){
        for(j=0;j<7;j++){
            b[i][j]=0;
        }
    }
    for(i=0;i<5;i++){
        for(j=0;j<7;j++){
            check_right(a,b,i,j,5);
            l=0;
            if(b[i][j]!=0){
                n++;
                break;
            }
        }
    }
    for(i=0;i<5;i++){
        for(j=0;j<7;j++){
            check_down(a,b,i,j,7);
            l=0;
            if(b[i][j]!=0){
                n++;
                break;
            }
        }
    }
    return n;
}

int const_find(int a[5][7],int b[5][7],int c[5][7],int d[5][7]){
    //a=MapColor,b=distanceFD,c=real_num,d=num0
    //Initialization
    int delta2[5][7];
    bool calculate=true;
    
    for(i=0;i<5;i++){
        for(j=0;j<7;j++){
            //delta2[i][j]=0;
            b[i][j]=0;
            c[i][j]=0;
            d[i][j]=0;
            //real_num[i][j]=0;
        }
    }
    if(calculate==true){
        n=detect(a,delta2);
            
        if(n==0){
            calculate=false;
        }
        else{
            for(i=0;i<5;i++){
                for(j=0;j<7;j++){
                    check_right(a,delta2,i,j,5);
                    l=0;
                }
            }
            for(i=0;i<5;i++){
                for(j=0;j<7;j++){
                    check_down(a,delta2,i,j,7);
                    l=0;
                }
            }  
            for(i=0;i<5;++i){
                for(j=0;j<7;++j){
                    if(delta2[i][j]!=0){
                        a[i][j]=a[i][j]+delta2[i][j];
                    }
                    
                }
            }
            //falling down
            for(i=0;i<5;++i){
                falling_down_info(a,b,c,d,i,7);
            }   
        }
    }
    max=0;
    for(i=0;i<5;i++){
        for(j=0;j<7;j++){
            if(b[i][j]>max){
                max=b[i][j];
            }
        }
    }
    return 0;
}
    
int main() 
{
    //Initialization
    constexpr int screenWidth =768;
    constexpr int screenHeight = 1024;
    Ball ball;
    InitWindow(screenWidth, screenHeight, "FXCKing project!");
    srand(getpid());
    Rectangle box[5][7];
    Rectangle choose; //被選到的
    Rectangle LineHorizonal[8],LineVertical[6]; //襪潮是框
    Rectangle boxB = {0, 0, 40, 40};// Box B: Mouse 
    Rectangle boxCollisionup = {0},boxCollisiondown={0},boxCollisionleft={0},boxCollisionright={0}; // Collision rectangle
    Color boxcolor,boxcolor2,LineColor={180,180,180,190};  
    int MapColor[5][7],delta[5][7],distanceFD[5][7],real_num[5][7],delta2[5][7],num0[5][7],char1[10],char2[10];
    int i,j,firX=0,firY=0,k=0,temp,t=0,t2=0,u=0;
    
    SetMousePosition(0,0);
    
    //picture import and change picture into texture2D
    Image ruby = LoadImage("picture/ruby.png"); //紅寶石
    ImageResize(&ruby, 78, 78);  //resize
    Texture2D textureR =LoadTextureFromImage(ruby);
    UnloadImage(ruby);
    Image emerald = LoadImage("picture/emerald.png");  //綠寶石
    ImageResize(&emerald, 78, 78);
    Texture2D textureG =LoadTextureFromImage(emerald);
    UnloadImage(emerald);
    Image sapphire = LoadImage("picture/sapphire.png");  //藍寶石
    ImageResize(&sapphire, 78, 78);
    Texture2D textureB =LoadTextureFromImage(sapphire);
    UnloadImage(sapphire);
    Image topaz =LoadImage("picture/topaz.png");//黃寶石
    ImageResize(&topaz,78,78);
    Texture2D textureY=LoadTextureFromImage(topaz);
    UnloadImage(topaz);
    Image WHAT = LoadImage("picture/WHAT.jpg");  //test(rikki)
    ImageResize(&WHAT, 80, 80);
    Texture2D test =LoadTextureFromImage(WHAT);
    UnloadImage(WHAT);

    //box position 
    for (i=0; i<5; i++){
        for (j=0; j<7; j++){
            box[i][j]=Rectangle{GetScreenWidth()/2.0f+85*(float)i-212.5f,GetScreenHeight()+85*(float)j-595.0f,80,80};
            //map[i][j]=rand()%3;
            MapColor[i][j]=GetRandomValue(1,4);   
            delta[i][j]=0;
            delta2[i][j]=0;
            distanceFD[i][j]=0;
            real_num[i][j]=0;
            num0[i][j]=0;

        } 
    }
    for(i=0;i<10;i++){
        char1[i]=0;
        char2[i]=0;
    }
    /*for (j=0; j<7; j++){
        distanceFD[j]=0;    //calculate the distance of every boxes in a vertical line before falling down
        num[j]=0;   //write down the numbers in a vertical line that are not 0
    }*/
    //Lines position and its longity
    for(i=0;i<8;i++){
        LineHorizonal[i]=Rectangle{GetScreenWidth()/2.0f-217.5f,GetScreenHeight()+85*(float)i-600.0f,430,5};
    }
    for(i=0;i<6;i++){
        LineVertical[i]=Rectangle{GetScreenWidth()/2.0f+85*(float)i-217.5f,GetScreenHeight()-600.0f,5,600};
    }
    //int screenUpperLimit = 40;      // Top menu limits
    
    bool pause = false;             // Movement pause
    bool collisionup = false,collisiondown=false,collisionleft=false,collisionright=false;  // Collision detection
    bool anime=false;         
    int start=0;   //1=move,2=anme_FD
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    { 
        // Update timer;
        
        //-----------------------------------------------------

        // Update player-controlled-box (box02)
        boxB.x = GetMouseX() - boxB.width/2;
        boxB.y = GetMouseY() - boxB.height/2;

        // Make sure Box B does not go out of move area limits
        if(boxB.x < GetScreenWidth()/2.0f-212.5f) boxB.x=GetScreenWidth()/2.0f-212.5f;
        if(boxB.x+boxB.width > GetScreenWidth()/2.0f+207.5f) boxB.x=GetScreenWidth()/2.0f+207.5f-boxB.width;
        if(boxB.y < GetScreenHeight()-595.0f) boxB.y=GetScreenHeight()-595.0f;
        if(boxB.y+boxB.height > GetScreenHeight()-5) boxB.y=GetScreenHeight()-boxB.height-5;

        // Pause Box A movement
        if (IsKeyPressed(KEY_SPACE)) pause = !pause;
        //choose which box to start
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
            firX=(GetMouseX()+212.5-GetScreenWidth()/2)/85;
            firY=(GetMouseY()+595-GetScreenHeight())/85;
            choose.height=90;
            choose.width=90;
            choose.x=GetScreenWidth()/2.0f+85*(float)firX-217.5f;
            choose.y=GetScreenHeight()+85*(float)firY-600.0f;
            boxcolor2={255,255,0,150};  
        }
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            start=1; 
            choose.x=GetMouseX()-45;
            choose.y=GetMouseY()-45;
            // Check boxes collision
            if(firX!=0) collisionleft=CheckCollisionRecs(box[firX-1][firY],boxB);
            if(firX!=4) collisionright=CheckCollisionRecs(box[firX+1][firY],boxB);
            if(firY!=0) collisionup=CheckCollisionRecs(box[firX][firY-1],boxB);
            if(firY!=6) collisiondown=CheckCollisionRecs(box[firX][firY+1],boxB);
            // Get collision rectangle (only on collision)
            if (collisionup) boxCollisionup=GetCollisionRec(box[firX][firY-1],boxB);
            if (collisiondown) boxCollisiondown=GetCollisionRec(box[firX][firY+1],boxB);
            if (collisionleft) boxCollisionleft=GetCollisionRec(box[firX-1][firY],boxB);
            if (collisionright) boxCollisionright=GetCollisionRec(box[firX+1][firY],boxB);
        }

        //歸位
        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            start=0;
            boxcolor2={0,0,0,0};
            //calculate whether there are boxes which are connected in the map
                for(i=0;i<5;i++){
                    for(j=0;j<7;j++){
                        check_right(MapColor,delta,i,j,5);
                        l=0;
                    }
                }
                for(i=0;i<5;i++){
                    for(j=0;j<7;j++){
                        check_down(MapColor,delta,i,j,7);
                        l=0;
                    }
                }  
                for(i=0;i<5;++i){
                    for(j=0;j<7;++j){
                        if(delta[i][j]!=0){
                            MapColor[i][j]=MapColor[i][j]+delta[i][j];
                        }
                    }
                }
                //falling down
                for(i=0;i<5;++i){
                    falling_down_info(MapColor,distanceFD,real_num,num0,i,7);
                }
                max=0;
                for(i=0;i<5;i++){
                    for(j=0;j<7;j++){
                        if(distanceFD[i][j]>max){
                          max=distanceFD[i][j];
                        }
                    }
                }
                anime=true;
                
            //}
        }

        //Make sure box[firX][firY] and choose do not go out
        if(box[firX][firY].x<GetScreenWidth()/2.0f-212.5f) box[firX][firY].x=GetScreenWidth()/2.0f-212.5f;
        if(box[firX][firY].x+box[firX][firY].width>GetScreenWidth()/2.0f+207.5f) box[firX][firY].x=GetScreenWidth()/2.0f+207.5f-box[firX][firY].width;
        if(box[firX][firY].y<GetScreenHeight()-595.0f) box[firX][firY].y=GetScreenHeight()-595.0f;
        if(box[firX][firY].y+box[firX][firY].height>GetScreenHeight()-5) box[firX][firY].y=GetScreenHeight()-box[firX][firY].height-5;
        if(choose.x<GetScreenWidth()/2.0f-217.5f) choose.x=GetScreenWidth()/2.0f-217.5f;
        if(choose.x+choose.width>GetScreenWidth()/2.0f+212.5f) choose.x=GetScreenWidth()/2.0f+212.5f-choose.width;
        if(choose.y<GetScreenHeight()-600.0f) choose.y=GetScreenHeight()-600.0f;
        if(choose.y+choose.height>GetScreenHeight()) choose.y=GetScreenHeight()-choose.height;
        
        //find the largest collision area(at least:960/1600)
        if (collisionup!=0 or collisiondown!=0 or collisionleft!=0 or collisionright!=0){
            int collision_Area=0;
            if((int)boxCollisionup.width*(int)boxCollisionup.height>collision_Area){
                collision_Area=(int)boxCollisionup.width*(int)boxCollisionup.height;
                k=0;
            }
            if((int)boxCollisiondown.width*(int)boxCollisiondown.height>collision_Area){
                collision_Area=(int)boxCollisiondown.width*(int)boxCollisiondown.height;
                k=1;
            } 
            if((int)boxCollisionleft.width*(int)boxCollisionleft.height>collision_Area) {
                collision_Area=(int)boxCollisionleft.width*(int)boxCollisionleft.height;
                k=2;
            }
            if((int)boxCollisionright.width*(int)boxCollisionright.height>collision_Area){
                collision_Area=(int)boxCollisionright.width*(int)boxCollisionright.height;
                k=3;
            } 
            // swap two boxes
            if(collision_Area>960){
                switch (k){
                    case 0:
                        temp=MapColor[firX][firY];
                        MapColor[firX][firY]=MapColor[firX][firY-1];
                        MapColor[firX][firY-1]=temp;
                        box[firX][firY].x=GetScreenWidth()/2-212.5+85*firX;
                        box[firX][firY].y=GetScreenHeight()-595+85*firY;
                        collision_Area=0;
                        firY=firY-1;
                        collisionup=false;
                        collisiondown=false;
                        collisionleft=false;
                        collisionright=false;
                        boxCollisionup.height=0;
                        boxCollisionup.width=0;
                        boxCollisiondown.height=0;
                        boxCollisiondown.width=0;
                        boxCollisionleft.height=0;
                        boxCollisionleft.width=0;
                        boxCollisionright.height=0;
                        boxCollisionright.width=0;
                        break;
                    case 1:
                        //swap(MapColor[firX][firY],MapColor[firX][firY+1]);
                        temp=MapColor[firX][firY];
                        MapColor[firX][firY]=MapColor[firX][firY+1];
                        MapColor[firX][firY+1]=temp;
                        box[firX][firY].x=GetScreenWidth()/2-212.5+85*firX;
                        box[firX][firY].y=GetScreenHeight()-595+85*firY;
                        collision_Area=0;
                        //MapColor[firX][firY]=4;
                        collisionup=false;
                        collisiondown=false;
                        collisionleft=false;
                        collisionright=false;
                        firY=firY+1;
                        boxCollisionup.height=0;
                        boxCollisionup.width=0;
                        boxCollisiondown.height=0;
                        boxCollisiondown.width=0;
                        boxCollisionleft.height=0;
                        boxCollisionleft.width=0;
                        boxCollisionright.height=0;
                        boxCollisionright.width=0;
                        break;
                    case 2:  
                        temp=MapColor[firX][firY];
                        MapColor[firX][firY]=MapColor[firX-1][firY];
                        MapColor[firX-1][firY]=temp;
                        box[firX][firY].x=GetScreenWidth()/2-212.5+85*firX;
                        box[firX][firY].y=GetScreenHeight()-595+85*firY;
                        collision_Area=0;
                        firX=firX-1;
                        //MapColor[firX][firY]=4;
                        collisionup=false;
                        collisiondown=false;
                        collisionleft=false;
                        collisionright=false;
                        //swap(MapColor[firX][firY],MapColor[firX-1][firY]);
                        boxCollisionup.height=0;
                        boxCollisionup.width=0;
                        boxCollisiondown.height=0;
                        boxCollisiondown.width=0;
                        boxCollisionleft.height=0;
                        boxCollisionleft.width=0;
                        boxCollisionright.height=0;
                        boxCollisionright.width=0;
                        break;
                    case 3:
                        temp=MapColor[firX][firY];
                        MapColor[firX][firY]=MapColor[firX+1][firY];
                        MapColor[firX+1][firY]=temp;
                        box[firX][firY].x=GetScreenWidth()/2-212.5+85*firX;
                        box[firX][firY].y=GetScreenHeight()-595+85*firY;
                        collision_Area=0;
                        firX=firX+1;
                        //MapColor[firX][firY]=4;
                        collisionup=false;
                        collisiondown=false;
                        collisionleft=false;
                        collisionright=false;
                        boxCollisionup.height=0;
                        boxCollisionup.width=0;
                        boxCollisiondown.height=0;
                        boxCollisiondown.width=0;
                        boxCollisionleft.height=0;
                        boxCollisionleft.width=0;
                        boxCollisionright.height=0;
                        boxCollisionright.width=0;
                        break;
                    default:
                        break;
                    }
            }
        }
        //continuously look for the same 
        
        
        //-----------------------------------------------------
        // Draw
        //-----------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);
            
        // DrawRectangle(0, 0, screenWidth, screenUpperLimit, collision? RED : BLACK);
        //draw 框
        for(i=1;i<7;i++){
            DrawRectangleRec(LineHorizonal[i],{190,190,190,150});
        }
        for(i=1;i<5;i++){
            DrawRectangleRec(LineVertical[i],{190,190,190,150});
        }
        DrawRectangleRec(LineHorizonal[0],LineColor);
        DrawRectangleRec(LineHorizonal[7],LineColor);
        DrawRectangleRec(LineVertical[0],LineColor);
        DrawRectangleRec(LineVertical[5],LineColor);
        //draw box
        if(anime!=true){
        for (i=0;i<5;i++){
            for (j=0;j<7;j++){    
                    switch (MapColor[i][j]){
                        case 1:
                            DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595,WHITE);
                            break;
                        case 2:
                            DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595,WHITE);
                            break;
                        case 3:
                            DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595,WHITE);
                            break;
                        case 4:
                            DrawTexture(textureY,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595,WHITE);
                            break;
                        default:
                            break;
                    }                          
                }  
            }
        }
        DrawRectangleRec(choose,boxcolor2);
        //move
        if(start==1){
                int x=GetMouseX(),y=GetMouseY();
                if(GetMouseX()< GetScreenWidth()/2.0f-172.5f) x= GetScreenWidth()/2.0f-172.5f;
                if(GetMouseX()> GetScreenWidth()/2+167.5) x= GetScreenWidth()/2+167.5;
                if(GetMouseY()< GetScreenHeight()-555) y= GetScreenHeight()-555;
                if(GetMouseY()> GetScreenHeight()-45) y= GetScreenHeight()-45;
                switch (MapColor[firX][firY]){
                case 0:
                    DrawTexture(test,x-40,y-40,WHITE);
                    break;
                case 1:
                    DrawTexture(textureR,x-39,y-39,WHITE);
                    break;
                case 2:
                    DrawTexture(textureG,x-39,y-39,WHITE);
                    break;
                case 3:
                    DrawTexture(textureB,x-39,y-39,WHITE);
                    break;
                case 4:
                    DrawTexture(textureY,x-39,y-39,WHITE);
                    break;
                default:
                    break;
                }
            }
        //falling down anime    
        if (anime==true){
            t++; 
            if(17*t>=max*85){
                //t2++;
                for(i=0;i<5;i++){
                    for(j=0;j<7;j++){
                        MapColor[i][j]=real_num[i][j];
                        switch (MapColor[i][j]){
                            case 1:
                               DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                               break;
                            case 2:
                               DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                               break;
                            case 3:
                               DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                               break;
                            case 4:
                               DrawTexture(textureY,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                               break;   
                           default:
                               DrawTexture(test,0,0,WHITE);
                               break;
                            }
                        /*if(17*t2<=510 and num0[i][j]==1){
                            switch (MapColor[i][j]){
                                case 1:
                                   DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+17*t2-85*(6-j),WHITE);
                                   break;
                                case 2:
                                   DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+17*t2-85*(6-j),WHITE);
                                   break;
                                case 3:
                                   DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+17*t2-85*(6-j),WHITE);
                                   break;
                               default:
                                   DrawTexture(test,0,0,WHITE);
                                   break;
                                }
                            }
                            else if (17*t2>510 and num0[i][j]==1){
                                switch (MapColor[i][j]){
                                    case 1:
                                       DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                    case 2:
                                       DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                    case 3:
                                       DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                   default:
                                       DrawTexture(test,0,0,WHITE);
                                       break;
                                }
                            }
                            else if(num0[i][j]==0){
                                switch (MapColor[i][j]){
                                    case 1:
                                       DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                    case 2:
                                       DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                    case 3:
                                       DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j,WHITE);
                                       break;
                                   default:
                                       DrawTexture(test,0,0,WHITE);
                                       break;
                                }
                            }*/
                        }
                        
                }       
                if(17*t>=max*85+595){
                    if(detect(MapColor,delta2)!=0){
                        const_find(MapColor,distanceFD,real_num,num0);
                        t=0;
                        t2=0;
                        u=0;
                        anime=true;
                    }
                    else if(detect(MapColor,delta2)==0){
                        anime=false;
                        int e=1;
                        while(dmg_total/pow(10,e)!=0){
                            temp=pow(10,e);
                            char1[e-1]=(dmg_total%temp)/pow(10,e-1);
                        }
                        char1[e-1]=dmg_total/pow(10,e-1);
                        char1[e]=10;
                        int f=0;
                        while(char1[f]!=10){
                            char2[e-f-1]=char1[f];
                            f++;
                        }
                        DrawText(std::to_string(char2).c_str(),GetScreenWidth()-40,GetScreenHeight()-40,10,GRAY);
                        dmg_total=0;
                        u=0;
                        t2=0;
                        t=0;
                    }
                } 
            }
            //Faling down anime
            for(i=0;i<5;i++){
                for(j=0;j<7;j++){
                    int dn=distanceFD[i][j]*85;
                    if(17*t<=dn){
                        switch(MapColor[i][j]){
                            case 1:
                                DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595+t*17,WHITE);
                                break;
                            case 2:
                                DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595+t*17,WHITE);
                                break;
                            case 3:
                                DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+85*j-595+t*17,WHITE);
                                break;
                            case 4:
                                DrawTexture(textureY,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()-595+85*j+t*17,WHITE);
                                break;
                            default:
                                break;
                        }
                    }
                    else if(17*t>dn and MapColor[i][j]!=0){ 
                        switch (real_num[i][j+(dn/85)]){
                            case 1:
                                DrawTexture(textureR,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+(85*j)+dn-595,WHITE);
                                break;
                            case 2:
                                DrawTexture(textureG,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+(85*j)+dn-595,WHITE);
                                break;
                            case 3:
                                DrawTexture(textureB,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+(85*j)+dn-595,WHITE);
                                break;
                            case 4:
                                DrawTexture(textureY,GetScreenWidth()/2+85*i-212.5,GetScreenHeight()+(85*j)+dn-595,WHITE);
                                break;
                            default:
                                break;
                        }
                    }
                }
            }
        }    

        DrawRectangleRec(boxB, {0,0,0,100});
            
        // Draw leave instructions
        DrawText("Press Esc to Leave", GetScreenWidth()/2+150, 10, 20, LIGHTGRAY);

        DrawFPS(10, 10);

        EndDrawing();
        //-----------------------------------------------------
    }
    // De-Initialization
    UnloadTexture(textureR);
    UnloadTexture(textureG);
    UnloadTexture(textureB);
    UnloadTexture(textureY);
    UnloadTexture(test);
    //---------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //----------------------------------------------------------
}