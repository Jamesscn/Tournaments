#define CsBot_AI_H //DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif //The robot ID : It must be two char, such as '00','kl' or 'Cr'.
char AI_MyID[2] = {'0', '2'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;
volatile int lcolor = 0;
volatile int fr = 0;
volatile int kso = 0;
volatile int compaz = 0;
volatile int t = 0;
volatile int rcolor = 0;
volatile int rai = 0;
volatile int lef = 0;
volatile int tt = 0;
int x = 45;
#define CsBot_AI_C //DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char *GetDebugInfo()
{
    char info[1024];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;", Duration, SuperDuration, bGameEnd, CurAction, CurGame, SuperObj_Num, SuperObj_X, SuperObj_Y, Teleport, LoadedObjects, US_Front, US_Left, US_Right, CSLeft_R, CSLeft_G, CSLeft_B, CSRight_R, CSRight_G, CSRight_B, PositionX, PositionY, TM_State, Compass, Time, WheelLeft, WheelRight, LED_1, MyState);
    return info;
}

DLL_EXPORT char* GetTeamName()
{
     return "CoSpace Team";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int *packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0];
    packet[0] = US_Front;
    sum += US_Front;
    US_Left = AI_IN[1];
    packet[1] = US_Left;
    sum += US_Left;
    US_Right = AI_IN[2];
    packet[2] = US_Right;
    sum += US_Right;
    CSLeft_R = AI_IN[3];
    packet[3] = CSLeft_R;
    sum += CSLeft_R;
    CSLeft_G = AI_IN[4];
    packet[4] = CSLeft_G;
    sum += CSLeft_G;
    CSLeft_B = AI_IN[5];
    packet[5] = CSLeft_B;
    sum += CSLeft_B;
    CSRight_R = AI_IN[6];
    packet[6] = CSRight_R;
    sum += CSRight_R;
    CSRight_G = AI_IN[7];
    packet[7] = CSRight_G;
    sum += CSRight_G;
    CSRight_B = AI_IN[8];
    packet[8] = CSRight_B;
    sum += CSRight_B;
    PositionX = AI_IN[9];
    packet[9] = PositionX;
    sum += PositionX;
    PositionY = AI_IN[10];
    packet[10] = PositionY;
    sum += PositionY;
    TM_State = AI_IN[11];
    packet[11] = TM_State;
    sum += TM_State;
    Compass = AI_IN[12];
    packet[12] = Compass;
    sum += Compass;
    Time = AI_IN[13];
    packet[13] = Time;
    sum += Time;
    packet[14] = sum;
}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void Game0()
{
    if(LoadedObjects>6){
        LoadedObjects=6;
    }
    if (US_Front > 10)
    {
        fr = 1;
    }
    else
    {
        fr = 0;
    }

    if (US_Right > 20)
    {
        rai = 1;
    }
    else if (US_Right < 8)
    {
        rai = 2;
    }
    else
    {
        rai = 0;
    }

    if (US_Left > 20)
    {
        lef = 1;
    }
    else if (US_Left < 8)
    {
        lef = 2;
    }
    else
    {
        lef = 0;
    }

    if (CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 200 && CSLeft_G <= 255 && CSLeft_B >= 250 && CSLeft_B <= 255)
    {
        lcolor = 1; //WWHHHHHHIIIIIIIIIIIITEEEEEEEEEEEEEEE
    }
    else
    {
        if (CSLeft_R >= 0 && CSLeft_R <= 100 && CSLeft_G >= 0 && CSLeft_G <= 100 && CSLeft_B >= 0 && CSLeft_B <= 100)
        {
            lcolor = 2; //BBBBBBBLLLLLLLLLAAAAAAAAAAACCCCCCCCKKKKKKKK
        }
        else
        {
            if (CSLeft_R >= 0 && CSLeft_R <= 100 && CSLeft_G >= 245 && CSLeft_G <= 255 && CSLeft_B >= 245 && CSLeft_B <= 255)
            {
                lcolor = 3; //CCCCCCYYYYYYYYYYYAAAAAAAAAAAAAANNNNNNNNNN
            }
            else
            {
                if (CSLeft_R >= 190 && CSLeft_R <= 250 && CSLeft_G >= 100 && CSLeft_G <= 200 && CSLeft_B >= 0 && CSLeft_B <= 115)
                {
                    lcolor = 4; //OOOOOOOORRRRRRRRAAAAAAAAAANNNNNGGGGEEEEEE
                }
                else
                {
                    if (CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 0 && CSLeft_G <= 70 && CSLeft_B >= 0 && CSLeft_B <= 70)
                    {
                        lcolor = 5; //RRRRRRRREEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD
                    }
                    else
                    {
                        if (CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 50)
                        {
                            lcolor = 6; //GGGGGGRRRRREEEEEEEEEEEEEEEEEEEEENNNNNNNNN
                        }
                        else
                        {
                            if (CSLeft_R >= 20 && CSLeft_R <= 90 && CSLeft_G >= 90 && CSLeft_G <= 155 && CSLeft_B >= 200 && CSLeft_B <= 255)//LUZySOMBRA
                            {
                                lcolor = 7; //BBBBBLLLLUUUUUUUUUUUUEEEEEEEEEEEEEEEEEEEEE
                            }
                            else
                            {
                                if ((CSLeft_R >= 230 && CSLeft_R <= 240 && CSLeft_G >= 240 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 5)//LUZTRAMPA
                                ||(CSLeft_R >= 250 && CSLeft_R <= 255 && CSLeft_G >= 250 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 60)//LUZLINEA
                                ||(CSLeft_R >= 200 && CSLeft_R <= 210 && CSLeft_G >= 210 && CSLeft_G <= 220 && CSLeft_B >= 0 && CSLeft_B <= 5)//SOMBRATRAMPA
                                ||(CSLeft_R >= 250 && CSLeft_R <= 255 && CSLeft_G >= 250 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 60))//SOMBRALINEA
                                {
                                    lcolor = 8; //YYYYYYYYEEEEEEEEELLLLLLLLLOOOOOOOOWWWWWWWW
                                }
                                else
                                {
                                    if (CSLeft_R >= 0 && CSLeft_R <= 60 && CSLeft_G >= 0 && CSLeft_G <= 60 && CSLeft_B > 220 && CSLeft_B <= 255)
                                    {
                                        lcolor = 9; //DAAAAARRRRRRRKKKKKKBLLLLLUEEEEEEEEEEEEEEEE
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 200 && CSRight_G <= 255 && CSRight_B >= 250 && CSRight_B <= 255)
    {
        rcolor = 1; //WHITE
    }
    else
    {
        if (CSRight_R >= 0 && CSRight_R <= 100 && CSRight_G >= 0 && CSRight_G <= 100 && CSRight_B >= 0 && CSRight_B <= 100)
        {
            rcolor = 2; //BLACK
        }
        else
        {
            if (CSRight_R >= 0 && CSRight_R <= 100 && CSRight_G >= 245 && CSRight_G <= 255 && CSRight_B >= 245 && CSRight_B <= 255)
            {
                rcolor = 3; //CYAN
            }
            else
            {
                if (CSRight_R >= 190 && CSRight_R <= 250 && CSRight_G >= 100 && CSRight_G <= 200 && CSRight_B >= 0 && CSRight_B <= 115)
                {
                    rcolor = 4; //ORANGE
                }
                else
                {
                    if (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 0 && CSRight_G <= 70 && CSRight_B >= 0 && CSRight_B <= 70)
                    {
                        rcolor = 5; //RRRRRRRREEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD
                    }
                    else
                    {
                        if (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 50)
                        {
                            rcolor = 6; //GGGGGGRRRRREEEEEEEEEEEEEEEEEEEEENNNNNNNNN
                        }
                        else
                        {
                            if (CSRight_R >= 20 && CSRight_R <= 90 && CSRight_G >= 90 && CSRight_G <= 155 && CSRight_B >= 200 && CSRight_B <= 255)//LUZySOMBRA
                            {
                                rcolor = 7; //BBBBBLLLLUUUUUUUUUUUUEEEEEEEEEEEEEEEEEEEEE
                            }
                            else
                            {
                                if ((CSRight_R >= 230 && CSRight_R <= 240 && CSRight_G >= 240 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 5)//LUZTRAMPA
                                ||(CSRight_R >= 250 && CSRight_R <= 255 && CSRight_G >= 250 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 60)//LUZLINEA
                                ||(CSRight_R >= 200 && CSRight_R <= 210 && CSRight_G >= 210 && CSRight_G <= 220 && CSRight_B >= 0 && CSRight_B <= 5)//SOMBRATRAMPA
                                ||(CSRight_R >= 250 && CSRight_R <= 255 && CSRight_G >= 250 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 60))//SOMBRALINEA
                                {
                                    rcolor = 8; //YYYYYYYYEEEEEEEEELLLLLLLLLOOOOOOOOWWWWWWWW
                                }
                                else
                                {
                                    if (CSRight_R >= 0 && CSRight_R <= 60 && CSRight_G >= 0 && CSRight_G <= 60 && CSRight_B > 220 && CSRight_B <= 255)
                                    {
                                        rcolor = 9; //DAAAAARRRRRRRKKKKKKBLLLLLUEEEEEEEEEEEEEEEE
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }



    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    else if (Duration > 0)
    {
        Duration--;
    }
    else if (1==1) //Caso1
    {
        Duration = 0;
        CurAction = 1;
    }
    

    switch (CurAction)
    {
    case 1: //Caso1
        if (Compass<x||Compass<x-2)
        {
            WheelLeft=1;
            WheelRight=3;
        }else if(Compass>x||Compass>x+2){
            WheelLeft=3;
            WheelRight=1;
        }else if(Compass==x||Compass==x+1||Compass==x+2||Compass==x-2||Compass==x-1){
            WheelLeft=3;
            WheelRight=3;
        }
        MyState = 0;
        break;


    
    default:
        break;
    }
}

void Game1()
{
    {
    if(LoadedObjects>6){
        LoadedObjects=6;
    }
    if (US_Front > 10)
    {
        fr = 1;
    }
    else
    {
        fr = 0;
    }

    if (US_Right > 20)
    {
        rai = 1;
    }
    else if (US_Right < 8)
    {
        rai = 2;
    }
    else
    {
        rai = 0;
    }

    if (US_Left > 20)
    {
        lef = 1;
    }
    else if (US_Left < 8)
    {
        lef = 2;
    }
    else
    {
        lef = 0;
    }

    if (CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 200 && CSLeft_G <= 255 && CSLeft_B >= 250 && CSLeft_B <= 255)
    {
        lcolor = 1; //WWHHHHHHIIIIIIIIIIIITEEEEEEEEEEEEEEE
    }
    else
    {
        if (CSLeft_R >= 0 && CSLeft_R <= 100 && CSLeft_G >= 0 && CSLeft_G <= 100 && CSLeft_B >= 0 && CSLeft_B <= 100)
        {
            lcolor = 2; //BBBBBBBLLLLLLLLLAAAAAAAAAAACCCCCCCCKKKKKKKK
        }
        else
        {
            if (CSLeft_R >= 0 && CSLeft_R <= 100 && CSLeft_G >= 245 && CSLeft_G <= 255 && CSLeft_B >= 245 && CSLeft_B <= 255)
            {
                lcolor = 3; //CCCCCCYYYYYYYYYYYAAAAAAAAAAAAAANNNNNNNNNN
            }
            else
            {
                if (CSLeft_R >= 190 && CSLeft_R <= 250 && CSLeft_G >= 100 && CSLeft_G <= 200 && CSLeft_B >= 0 && CSLeft_B <= 115)
                {
                    lcolor = 4; //OOOOOOOORRRRRRRRAAAAAAAAAANNNNNGGGGEEEEEE
                }
                else
                {
                    if (CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 0 && CSLeft_G <= 70 && CSLeft_B >= 0 && CSLeft_B <= 70)
                    {
                        lcolor = 5; //RRRRRRRREEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD
                    }
                    else
                    {
                        if (CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 50)
                        {
                            lcolor = 6; //GGGGGGRRRRREEEEEEEEEEEEEEEEEEEEENNNNNNNNN
                        }
                        else
                        {
                            if (CSLeft_R >= 20 && CSLeft_R <= 90 && CSLeft_G >= 90 && CSLeft_G <= 155 && CSLeft_B >= 200 && CSLeft_B <= 255)//LUZySOMBRA
                            {
                                lcolor = 7; //BBBBBLLLLUUUUUUUUUUUUEEEEEEEEEEEEEEEEEEEEE
                            }
                            else
                            {
                                if ((CSLeft_R >= 230 && CSLeft_R <= 240 && CSLeft_G >= 240 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 5)//LUZTRAMPA
                                ||(CSLeft_R >= 250 && CSLeft_R <= 255 && CSLeft_G >= 250 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 60)//LUZLINEA
                                ||(CSLeft_R >= 200 && CSLeft_R <= 210 && CSLeft_G >= 210 && CSLeft_G <= 220 && CSLeft_B >= 0 && CSLeft_B <= 5)//SOMBRATRAMPA
                                ||(CSLeft_R >= 250 && CSLeft_R <= 255 && CSLeft_G >= 250 && CSLeft_G <= 255 && CSLeft_B >= 0 && CSLeft_B <= 60))//SOMBRALINEA
                                {
                                    lcolor = 8; //YYYYYYYYEEEEEEEEELLLLLLLLLOOOOOOOOWWWWWWWW
                                }
                                else
                                {
                                    if (CSLeft_R >= 0 && CSLeft_R <= 60 && CSLeft_G >= 0 && CSLeft_G <= 60 && CSLeft_B > 220 && CSLeft_B <= 255)
                                    {
                                        lcolor = 9; //DAAAAARRRRRRRKKKKKKBLLLLLUEEEEEEEEEEEEEEEE
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 200 && CSRight_G <= 255 && CSRight_B >= 250 && CSRight_B <= 255)
    {
        rcolor = 1; //WHITE
    }
    else
    {
        if (CSRight_R >= 0 && CSRight_R <= 100 && CSRight_G >= 0 && CSRight_G <= 100 && CSRight_B >= 0 && CSRight_B <= 100)
        {
            rcolor = 2; //BLACK
        }
        else
        {
            if (CSRight_R >= 0 && CSRight_R <= 100 && CSRight_G >= 245 && CSRight_G <= 255 && CSRight_B >= 245 && CSRight_B <= 255)
            {
                rcolor = 3; //CYAN
            }
            else
            {
                if (CSRight_R >= 190 && CSRight_R <= 250 && CSRight_G >= 100 && CSRight_G <= 200 && CSRight_B >= 0 && CSRight_B <= 115)
                {
                    rcolor = 4; //ORANGE
                }
                else
                {
                    if (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 0 && CSRight_G <= 70 && CSRight_B >= 0 && CSRight_B <= 70)
                    {
                        rcolor = 5; //RRRRRRRREEEEEEEEEEEEEEEEEEEEDDDDDDDDDDDDD
                    }
                    else
                    {
                        if (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 50)
                        {
                            rcolor = 6; //GGGGGGRRRRREEEEEEEEEEEEEEEEEEEEENNNNNNNNN
                        }
                        else
                        {
                            if (CSRight_R >= 20 && CSRight_R <= 90 && CSRight_G >= 90 && CSRight_G <= 155 && CSRight_B >= 200 && CSRight_B <= 255)//LUZySOMBRA
                            {
                                rcolor = 7; //BBBBBLLLLUUUUUUUUUUUUEEEEEEEEEEEEEEEEEEEEE
                            }
                            else
                            {
                                if ((CSRight_R >= 230 && CSRight_R <= 240 && CSRight_G >= 240 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 5)//LUZTRAMPA
                                ||(CSRight_R >= 250 && CSRight_R <= 255 && CSRight_G >= 250 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 60)//LUZLINEA
                                ||(CSRight_R >= 200 && CSRight_R <= 210 && CSRight_G >= 210 && CSRight_G <= 220 && CSRight_B >= 0 && CSRight_B <= 5)//SOMBRATRAMPA
                                ||(CSRight_R >= 250 && CSRight_R <= 255 && CSRight_G >= 250 && CSRight_G <= 255 && CSRight_B >= 0 && CSRight_B <= 60))//SOMBRALINEA
                                {
                                    rcolor = 8; //YYYYYYYYEEEEEEEEELLLLLLLLLOOOOOOOOWWWWWWWW
                                }
                                else
                                {
                                    if (CSRight_R >= 0 && CSRight_R <= 60 && CSRight_G >= 0 && CSRight_G <= 60 && CSRight_B > 220 && CSRight_B <= 255)
                                    {
                                        rcolor = 9; //DAAAAARRRRRRRKKKKKKBLLLLLUEEEEEEEEEEEEEEEE
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (SuperDuration > 0)
    {
        SuperDuration--;
    }
    else if (Duration > 0)
    {
        Duration--;
    }
    else if ((lcolor == 7 && rcolor == 1) 
    || (lcolor == 1 && rcolor == 7) 
    || (lcolor == 1 && rcolor == 1) 
    || (lcolor == 7 && rcolor == 7))
    {
        Duration = 0;
        CurAction = 1;
    }
    else if (((lcolor == 5 && rcolor == 7) 
    || (lcolor == 5 && rcolor == 5) 
    || (lcolor == 5 && rcolor == 1) 
    || (lcolor == 7 && rcolor == 5) 
    || (lcolor == 1 && rcolor == 5) 
    || (lcolor == 2 && rcolor == 2) 
    || (lcolor == 1 && rcolor == 2) 
    || (lcolor == 2 && rcolor == 1) 
    || (lcolor == 3 && rcolor == 3) 
    || (lcolor == 1 && rcolor == 3) 
    || (lcolor == 3 && rcolor == 7)
    || (lcolor == 7 && rcolor == 3)
    || (lcolor == 7 && rcolor == 2)
    || (lcolor == 2 && rcolor == 7)
    || (lcolor == 3 && rcolor == 1)) && (LoadedObjects < 6))
    {
        Duration = 49;
        CurAction = 2;
    }
    else if (lcolor == 8 || rcolor == 8)
    {
        Duration = 0;
        CurAction = 3;
    }
    else if ((lcolor == 4 || rcolor == 4) && LoadedObjects != 0)
    {
        Duration = 49;
        CurAction = 4;
    }
    else if ((lcolor == 4 && rcolor == 4) && LoadedObjects == 0)
    {
        Duration = 49;
        CurAction = 5;
    }
    else if (((lcolor == 5 && rcolor == 7) 
    || (lcolor == 5 && rcolor == 5) 
    || (lcolor == 5 && rcolor == 1) 
    || (lcolor == 7 && rcolor == 5) 
    || (lcolor == 1 && rcolor == 5) 
    || (lcolor == 2 && rcolor == 2) 
    || (lcolor == 1 && rcolor == 2) 
    || (lcolor == 2 && rcolor == 1) 
    || (lcolor == 3 && rcolor == 3) 
    || (lcolor == 1 && rcolor == 3) 
    || (lcolor == 3 && rcolor == 1)) && (LoadedObjects == 6))
    {
        Duration = 0;
        CurAction = 6;
    }
    else if ((lcolor == 7 && rcolor == 8)||(lcolor == 8 && rcolor == 7))
    {
        Duration = 0;
        CurAction = 7;
    }
    else if (lef==2||rai==2)
    {
        Duration = 0;
        CurAction = 9;
    }

    switch (CurAction)
    {
    case 1:
        if (fr == 1 && (lcolor != 5 || rcolor != 5) && (lcolor != 4 || rcolor != 4) || (lcolor == 9 || rcolor == 9))
        {
            WheelLeft = 2;
            WheelRight = 2;
            if (lcolor == 9 || rcolor == 9)
            {
                LoadedObjects = 0;
            }
            LED_1 = 0;
        }
        else if (fr == 0 || lef == 0 || rai == 0 || rcolor == 8 || lcolor == 8)
        {
            compaz = Compass;
            compaz = compaz;
            if (fr == 0 && lef == 0 && rai == 0)
            {
                if (compaz + 180 > Compass)
                {
                    WheelLeft = -2;
                    WheelRight = 2;
                }
            }
            else if (fr == 0 && lef == 0 && rai == 0 && lcolor != 8 && rcolor == 8)
            {
                if (compaz + 20 > Compass)
                {
                    WheelLeft = -2;
                    WheelRight = 2;
                }
            }
            else if (fr == 0 && lef == 0 && rai == 0 && lcolor == 8 && rcolor != 8)
            {
                if (compaz - 20 < Compass)
                {
                    WheelLeft = 2;
                    WheelRight = -2;
                }
            }
            else if (fr == 1 && lef == 1 && rai == 1 && lcolor != 8 && rcolor == 8)
            {
                if (compaz + 20 > Compass)
                {
                    WheelLeft = -2;
                    WheelRight = 2;
                }
            }
            else if (fr == 1 && lef == 1 && rai == 1 && lcolor == 8 && rcolor != 8)
            {
                if (compaz - 20 < Compass)
                {
                    WheelLeft = 2;
                    WheelRight = -2;
                }
            }
            else if (fr == 0 && (US_Left > US_Right))
            {
                if (compaz + 90 > Compass)
                {
                    WheelLeft = -2;
                    WheelRight = 2;
                }
            }
            else if (fr == 0 && (US_Left < US_Right))
            {
                if (compaz - 90 < Compass)
                {
                    WheelLeft = 2;
                    WheelRight = -2;
                }
            }
            else if (lef == 2 && US_Right > US_Left)
            {
                if (compaz + 25 > Compass)
                {
                    WheelLeft = 2;
                    WheelRight = -2;
                }
            }
            else if (rai == 2 && US_Left > US_Right)
            {
                if (compaz - 25 < Compass)
                {
                    WheelLeft = -2;
                    WheelRight = 2;
                }
            }
            else if (lcolor == 8 && US_Right < 20)
            { ///////////////////////
                if (compaz - 180 < Compass)
                {
                    WheelLeft = -x;
                    WheelRight = -(x + 1);
                }
            }
            else if (rcolor == 8 && US_Left < 20)
            { ///////////////////////
                if (compaz + 180 > Compass)
                {
                    WheelLeft = -(x + 1);
                    WheelRight = -x;
                }
            }
        }
        MyState = 0;
        break;
    case 2:
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 1;
        MyState = 0;
        if (Duration == 1)
        {
            LoadedObjects = LoadedObjects + 1;
            WheelLeft = 0;
            WheelRight = 0;
        }
        break;
    case 3:
        if (rcolor == 8 && lcolor != 8)
        {
            compaz = Compass;
            compaz = compaz;
            if (compaz - 45 < Compass)
            {
                WheelLeft = -1;
                WheelRight = -6;
            }
        }
        else if (rcolor != 8 && lcolor == 8)
        {
            compaz = Compass;
            compaz = compaz;
            if (compaz + 45 > Compass)
            {
                WheelLeft = -6;
                WheelRight = -1;
            }
        }
        LED_1 = 0;
        break;
    case 4:
        if ((lcolor == 4 && rcolor == 5) 
        || (lcolor == 4 && rcolor == 7) 
        || (lcolor == 4 && rcolor == 8)
        || (lcolor == 4 && rcolor == 1))
        {
            WheelLeft = -2;
            WheelRight = 3;
            LED_1 = 0;
        }
        else 
        if ((lcolor == 5 && rcolor == 4) 
        || (lcolor == 7 && rcolor == 4) 
        || (lcolor == 8 && rcolor == 4)
        || (lcolor == 1 && rcolor == 4))
        {
            WheelLeft = 3;
            WheelRight = -2;
            LED_1 = 0;
            MyState = 0;
        }
        else
         if (lcolor == 4 && rcolor == 4)
        {
            if(LoadedObjects!=0){
            WheelLeft = 0;
            WheelRight = 0;
            LED_1 = 2;
            MyState = 0;
            if(Duration==1){
            LoadedObjects = 0;     
            }           
            }
        }
        

        break;
    case 5:
        if(US_Front<10){
             WheelLeft = -6;
             WheelRight = -1;
        }else {
                WheelLeft = 2;
                WheelRight = 2;
        }
        
    
        LED_1 = 0;
        MyState = 0;
        break;
    case 6:
        WheelLeft = 2;
        WheelRight = 2;
        LED_1 = 0;
        MyState = 0;
        break;
    case 7:
        LoadedObjects = 0;
    
     case 9:
        compaz = Compass;
        compaz = compaz;
        if(rai==2){
        if (compaz + 5 > Compass){
                WheelLeft = 2;
                WheelRight = -2;
        }
        }else if(lef==2){
        if (compaz - 5 > Compass){
                WheelLeft = -2;
                WheelRight = 2;
        }
        }else if(lef==2&&rai==2){
        if (compaz - 5 > Compass){
                WheelLeft = -3;
                WheelRight = 3;
        }
        }
        LED_1 = 0;
        MyState = 0;
        break;
    default:
        break;
    }
}
}

DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
    case 9:
        break;
    case 10:
        WheelLeft = 0;
        WheelRight = 0;
        LED_1 = 0;
        MyState = 0;
        break;
    case 0:
        Game0();
        break;
    case 1:
        Game1();
        break;
    default:
        break;
    }
}
