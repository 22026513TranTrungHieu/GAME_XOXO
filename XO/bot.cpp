
#include "bot.h"


bool gameEnd(bool a[])
{
    if( a[0] && a[3] && a[4] )
    {
        return 1;
    }
    else
    if( a[0] && a[1] && a[2] )
    {
        return 1;
    }
    else
    if( a[0] && a[5] && a[8] )
    {
        return 1;
    }
    else
    if( a[1] && a[5] && a[7] )
    {
        return 1;
    }
    else
    if( a[2] && a[6] && a[8] )
    {
        return 1;
    }
    else
    if( a[3] && a[5] && a[6] )
    {
        return 1;
    }
    else
    if( a[4] && a[7] && a[8] )
    {
        return 1;
    }
    else
    if( a[2] && a[5] && a[4] )
    {
        return 1;
    }
    else
        return 0;
}

void controlBot(int movated, int &bot, bool xx[], bool oo[])
{
    if(movated == 1)
    {
        if( xx[ 5 ] )
            bot = 0;
        else
            bot = 5;
    }
    else
    {
        //di de thang
        if( oo[ 0 ] && oo [ 1 ] && !xx[ 2 ])
        {
            bot = 2;
        }
        else
        if( oo[ 0 ] && oo[ 2 ] && !xx [ 1 ])
        {
            bot = 1;
        }
        else
        if( oo[ 0 ] && oo[ 3 ] && !xx[ 4 ])
        {
            bot = 4;
        }
        else
        if( oo[ 0 ] && oo[ 4 ] && !xx[ 3 ])
        {
            bot = 3;
        }
        else
        if( oo[ 0 ] && oo[ 5 ] && !xx[ 8 ])
        {
            bot = 8;
        }
        else
        if( oo[ 0 ] && oo[ 8 ] && !xx[ 5 ])
        {
            bot = 5;
        }
        else
        if( oo[ 1 ] && oo[ 2 ] && !xx[ 0 ])
        {
            bot = 0;
        }
        else
        if( oo[ 1 ] && oo[ 5 ] && !xx[ 7 ])
        {
            bot = 7;
        }
        else
        if( oo[ 1 ] && oo[ 7 ] && !xx[ 5 ])
        {
            bot = 5;
        }
        else
        if( oo[ 2 ] && oo[ 6 ] && !xx[ 8 ])
        {
            bot = 8;
        }
        else
        if( oo[ 2 ] && oo[ 8 ] && !xx[ 6 ])
        {
            bot = 6;
        }
        else
        if( oo[ 2 ] && oo[ 5 ] && !xx[ 4 ])
        {
            bot = 4;
        }
        else
        if( oo[ 2 ] && oo[ 4 ] && !xx[ 5 ])
        {
            bot = 5;
        }
        else
        if( oo[ 3 ] && oo[ 4 ] && !xx[ 0 ])
        {
            bot = 0;
        }
        else
        if( oo[ 3 ] && oo[ 5 ] && !xx[ 6 ])
        {
            bot = 6;
        }
        else
        if( oo[ 3 ] && oo[ 6 ] && !xx[ 5 ])
        {
            bot = 5;
        }
        else
        if( oo[ 4 ] && oo[ 5 ] && !xx[ 2 ])
        {
            bot = 2;
        }
        else
        if( oo[ 4 ] && oo[ 7 ] && !xx[ 8 ])
        {
            bot = 8;
        }
        else
        if( oo[ 4 ] && oo[ 8 ] && !xx[ 7 ])
        {
            bot = 7;
        }
        else
        if( oo[ 5 ] && oo[ 6 ] && !xx[ 3 ])
        {
            bot = 3;
        }
        else
        if( oo[ 5 ] && oo[ 7 ] && !xx[ 1 ])
        {
            bot = 1;
        }
        else
        if( oo[ 5 ] && oo[ 8 ] && !xx[ 0 ])
        {
            bot = 0;
        }
        else
        if( oo[ 7 ] && oo[ 8 ] && !xx[ 4 ])
        {
            bot = 4;
        }
        else
        if( oo[ 6 ] && oo[ 8 ] && !xx[ 2 ])
        {
            bot = 2;
        }
        // di de chan
        else
        if( xx[ 0 ] && xx [ 1 ] && !oo[ 2 ])
        {
            bot = 2;
        }
        else
        if( xx[ 0 ] && xx[ 2 ] && !oo [ 1 ])
        {
            bot = 1;
        }
        else
        if( xx[ 0 ] && xx[ 3 ] && !oo[ 4 ])
        {
            bot = 4;
        }
        else
        if( xx[ 0 ] && xx[ 4 ] && !oo[ 3 ])
        {
            bot = 3;
        }
        else
        if( xx[ 0 ] && xx[ 5 ] && !oo[ 8 ])
        {
            bot = 8;
        }
        else
        if( xx[ 0 ] && xx[ 8 ] && !oo[ 5 ])
        {
            bot = 5;
        }
        else
        if( xx[ 1 ] && xx[ 2 ] && !oo[ 0 ])
        {
            bot = 0;
        }
        else
        if( xx[ 1 ] && xx[ 5 ] && !oo[ 7 ])
        {
            bot = 7;
        }
        else
        if( xx[ 1 ] && xx[ 7 ] && !oo[ 5 ])
        {
            bot = 5;
        }
        else
        if( xx[ 2 ] && xx[ 6 ] && !oo[ 8 ])
        {
            bot = 8;
        }
        else
        if( xx[ 2 ] && xx[ 8 ] && !oo[ 6 ])
        {
            bot = 6;
        }
        else
        if( xx[ 2 ] && xx[ 5 ] && !oo[ 4 ])
        {
            bot = 4;
        }
        else
        if( xx[ 2 ] && xx[ 4 ] && !oo[ 5 ])
        {
            bot = 5;
        }
        else
        if( xx[ 3 ] && xx[ 4 ] && !oo[ 0 ])
        {
            bot = 0;
        }
        else
        if( xx[ 3 ] && xx[ 5 ] && !oo[ 6 ])
        {
            bot = 6;
        }
        else
        if( xx[ 3 ] && xx[ 6 ] && !oo[ 5 ])
        {
            bot = 5;
        }
        else
        if( xx[ 4 ] && xx[ 5 ] && !oo[ 2 ])
        {
            bot = 2;
        }
        else
        if( xx[ 4 ] && xx[ 7 ] && !oo[ 8 ])
        {
            bot = 8;
        }
        else
        if( xx[ 4 ] && xx[ 8 ] && !oo[ 7 ])
        {
            bot = 7;
        }
        else
        if( xx[ 5 ] && xx[ 6 ] && !oo[ 3 ])
        {
            bot = 3;
        }
        else
        if( xx[ 5 ] && xx[ 7 ] && !oo[ 1 ])
        {
            bot = 1;
        }
        else
        if( xx[ 5 ] && xx[ 8 ] && !oo[ 0 ])
        {
            bot = 0;
        }
        else
        if( xx[ 7 ] && xx[ 8 ] && !oo[ 4 ])
        {
            bot = 4;
        }
        else
        if( xx[ 6 ] && xx[ 8 ] && !oo[ 2 ])
        {
            bot = 2;
        }

    }
    if(bot == 9)
    {
        if(xx[0] && xx[8])
        {
            bot = 1;
        }
        else
        if(xx[2] && xx[4])
        {
            bot = 1;
        }
        else
        if(!oo[0] && !xx[0])
        {
            bot = 0;
        }
        else
        if(!oo[2] && !xx[2])
        {
            bot = 2;
        }
        else
        if(!oo[4] && !xx[4])
        {
            bot = 4;
        }
        else
        if(!oo[8] && !xx[8])
        {
            bot = 8;
        }
        else
            for(int j=1; j<9; j++)
            if(!oo[j] && !xx[j])
            {
                bot = j;
            }
    }
}
