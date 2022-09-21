#include <stdio.h>

#define SelfID 1
#define LED_TYPE WS2812
#define COLOR_ORDER GRB

#define LED_STRIP_COLUMN 8 //列
#define LED_STRIP_ROW 40   //行

#define LED_BRI

char *ssid = (char *)"robomasterserver"; //添加了(char*)
char *password = (char *)"12345678";     //
int Matrix[LED_STRIP_COLUMN][LED_STRIP_ROW];
int StartFlag = 0;
int HitFlag = 0;
int UdpPort = 2333;
int ReturnUdpPort = 2334;
void LED_Refresh()
{
    int k = 0;
    for (int i = LED_STRIP_ROW; i > 0; i--)
    {
        for (int j = LED_STRIP_COLUMN; j > 0; j--)
        {
            if (Matrix[j][i])
            {
                printf("■");
            }
            else
            {
                printf("□");
            }
        }
        printf("\n");
    }
    printf("\n");
}
int main(int argc, char const *argv[])
{

    while (1)
    {
        if (1)
        {
            for (int row_count = 0; row_count < 9; row_count++)
            {
                for (int i = 0; i < LED_STRIP_ROW; i++)
                {
                    switch (i % 9 + row_count)
                    { /*
                     000111000
                     000011100
                     000001110
                     000000111
                     000000111
                     000001110
                     000011100
                     000111000
                     */
                    //学长写的,直接抄了
                    case 0:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 0;
                    }
                    break;

                    case 1:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 0;
                    }
                    break;
                    case 2:
                    {
                        Matrix[i][0] = 0;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 1;
                        Matrix[i][4] = 1;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 0;
                    }
                    break;
                    case 3:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 1;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 1;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 1;
                    }
                    break;
                    case 4:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 1;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 1;
                        Matrix[i][7] = 1;
                    }
                    break;
                    case 5:
                    {
                        Matrix[i][0] = 1;
                        Matrix[i][1] = 0;
                        Matrix[i][2] = 0;
                        Matrix[i][3] = 0;
                        Matrix[i][4] = 0;
                        Matrix[i][5] = 0;
                        Matrix[i][6] = 0;
                        Matrix[i][7] = 1;
                    }
                    break;
                    default:
                    {

                        for (int j = 0; j < LED_STRIP_COLUMN; j++)
                        {
                            Matrix[i][j] = 0;
                        
                        }
                    }
                        if (i = LED_STRIP_ROW)
                        {
                            LED_Refresh();
                        }

                        sleep(1);
                    }
                }
            }
        }
    }
    return 0;
}
