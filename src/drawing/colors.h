//
//  colors.h
//  Lenza
//
//  Created by Andrea Biagioni on 02/06/22.
//

#ifndef colors_h
#define colors_h

#include <stdio.h>
#include <math.h>

typedef struct
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}RGB;

typedef struct
{
    double H;
    double S;
    double V;
}HSV;

RGB HSVToRGB(HSV hsv);

#endif /* colors_h */
