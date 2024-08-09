/*******************************************************************************
*  The "New BSD License" : http://www.opensource.org/licenses/bsd-license.php  *
********************************************************************************

Copyright (c) 2010, Mark Turney
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the <organization> nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/

#include "simple_svg_1.0.0.hpp"
#include <math.h>

using namespace svg;
// This is a modification of the older version where there wer two lines, essentially an oval. 
// This has a central line and then one above and below.  The one aboe if the positive line 
// whilst the one below is the negative line...
int
main ()
{
    Color pdpBlack (23, 23, 27);
    Color pdpWhite (224, 226, 206);

    const int hole_spacing = 25;
    const int row_spacing = 50;

    // The half circles of holes at either end have half circumference of 18 * hole spacing.
    // The C = pi * diameter
    // diameter = C/pi; 
    int diameter = 2 * (18 * hole_spacing) / M_PI;
    int radius = diameter / 2;

    int x_dim = 1650;
    int y_dim = 450;
    int x_origin = x_dim / 2;
    int y_origin = y_dim / 2;
    Dimensions dimensions (x_dim, y_dim);
    Document doc ("Kaiser_board.svg",
                  Layout (dimensions, Layout::BottomLeft));

    // Red image border.
    Polygon border (Fill (pdpWhite), Stroke (1, Color::Red));
    border << Point (0, 0) << Point (dimensions.width, 0)
        << Point (dimensions.width, dimensions.height) << Point (0,
                                                                 dimensions.
                                                                 height);
    doc << border;

    int x, y;
    x = x_origin - hole_spacing / 2;
    y = y_origin + row_spacing / 2;
    // draw the start holes
    for (int m = 0; m < 2; m++)
    {

        doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                       Stroke (2, pdpBlack));
        doc << Line (Point (x - 7, y), Point (x + 7, y),
                     Stroke (2, pdpBlack));
        doc << Line (Point (x, y - 7), Point (x, y + 7),
                     Stroke (2, pdpBlack));
        y = y_origin - row_spacing / 2;
        doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                       Stroke (2, pdpBlack));
        doc << Line (Point (x - 7, y), Point (x + 7, y),
                     Stroke (2, pdpBlack));
        doc << Line (Point (x, y - 7), Point (x, y + 7),
                     Stroke (2, pdpBlack));
        x = x + hole_spacing;
        y = y_origin + row_spacing / 2;
    }

    // doc << Line (Point (x, y - 7), Point (x, y + 7), Stroke (2, pdpBlack));
    // now go both ways from center
    for (int seg = 0; seg < 4; seg++)
    {
        int startx = x_origin + 3 * hole_spacing + seg * 6 * hole_spacing;
        int startxn = x_origin - 3 * hole_spacing - seg * 6 * hole_spacing;
        int a[] = { y_origin - row_spacing / 2, y_origin + row_spacing / 2 };
      for (auto & y:a)
        {
            for (int k = 0; k < 5 * hole_spacing; k = k + hole_spacing)
            {
                x = k + startx;
                doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                               Stroke (2, pdpBlack));
                doc << Line (Point (x + 7, y), Point (x - 7, y),
                             Stroke (2, pdpBlack));
                doc << Line (Point (x, y - 7), Point (x, y + 7),
                             Stroke (2, pdpBlack));
                x = -k + startxn;
                doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                               Stroke (2, pdpBlack));
                doc << Line (Point (x + 7, y), Point (x - 7, y),
                             Stroke (2, pdpBlack));
                doc << Line (Point (x, y - 7), Point (x, y + 7),
                             Stroke (2, pdpBlack));
            }
        }
    }
    // half circle 
    // calculate the angle.  want 5 holes so  4 spaces - plus one at either end
    int delta_angle = 180 / 4;
    // calculate the approximate radius
    radius =
        ceil ((float) hole_spacing / ((float) delta_angle / 360 * 2 * M_PI));

    int x1 = x_origin - (3 * hole_spacing + 4 * 6 * hole_spacing);
    int x2 = x_origin + (3 * hole_spacing + 4 * 6 * hole_spacing);

    for (int circ = 1; circ < 3; circ++)
    {
        for (int angle = -90; angle < 91; angle = angle + delta_angle)
        {
            float arg = (float) -angle / 360 * 2 * M_PI;
            float S, C;
            C = cos (arg);
            S = sin (arg);

            if (circ == 1)
            {
                x = x1 - radius * C;
                y = y_origin + (radius * S + radius + row_spacing / 2);
            }
            else
            {
                x = x2 + radius * C;
                y = y_origin - (radius * S + radius + row_spacing / 2);
            }
            doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                           Stroke (2, pdpBlack));
            doc << Line (Point (x - 7, y), Point (x + 7, y),
                         Stroke (2, pdpBlack));
            doc << Line (Point (x, y - 7), Point (x, y + 7),
                         Stroke (2, pdpBlack));

            // x = x_origin - (radius + row_spacing) * C - hole_spacing;
            if (circ == 1)
            {
                x = x - row_spacing * C;
                y = y_origin + radius * S + row_spacing * S + radius +
                    row_spacing / 2;
            }
            else
            {
                x = x + row_spacing * C;
                y = y_origin - radius * S - row_spacing * S - radius -
                    row_spacing / 2;
            }
            doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                           Stroke (2, pdpBlack));
            doc << Line (Point (x - 7, y), Point (x + 7, y),
                         Stroke (2, pdpBlack));
            doc << Line (Point (x, y - 7), Point (x, y + 7),
                         Stroke (2, pdpBlack));
        }
    }
    // We have 4 tracks to make, two sets of x values, one starting on the left
    // moving right and one starting on the right and moring left
    // we have 4 sets of y values

    int startxn = x_origin + 5 * 6 * hole_spacing + hole_spacing;
    int startx = x_origin - 5 * 6 * hole_spacing - hole_spacing;
    int a[] = {
        y_origin + row_spacing / 2 + 2 * radius + row_spacing,
        y_origin + row_spacing / 2 + 2 * radius,
        y_origin - row_spacing / 2 - 2 * radius,
        y_origin - row_spacing / 2 - 2 * radius - row_spacing
    };
    int xstart;
    int x_inc_sign;
    for (int track = 0; track < 4; track++)
    {
        y = a[track];
        if (track < 2)
        {
            xstart = startx;
            x_inc_sign = 1;
        }
        else
        {
            xstart = startxn;
            x_inc_sign = -1;
        }

        for (int seg = 0; seg < 8; seg++)
        {
            xstart = xstart + x_inc_sign * 6 * hole_spacing;
            for (int k = 0; k < 5 * hole_spacing; k = k + hole_spacing)
            {
                if ((seg == 7) && (k == 2 * hole_spacing))
                {
                    break;

                }
                x = x_inc_sign * k + xstart;
                doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                               Stroke (2, pdpBlack));
                doc << Line (Point (x + 7, y), Point (x - 7, y),
                             Stroke (2, pdpBlack));
                doc << Line (Point (x, y - 7), Point (x, y + 7),
                             Stroke (2, pdpBlack));
            }
        }
    }
    x = x_origin - 737;
    int x_inc = 1.5 * hole_spacing;
    int x_Bid = x - 33;
    int x_numbers = x - 2 * hole_spacing + 20;
    int x_suits = x_numbers;

    int x_suits_dots = x - 20;
    int x_num_dots = x_suits_dots;


    y = y_origin - 90;
    int y_Bid = y +20;
    int y_numbers = y - 25;
    int y_suits = y_numbers - 60;
    int y_num_dots = y - 40;
    int y_suits_dots = y_num_dots - 60;
    doc << Text (Point (x_Bid, y_Bid), "Bid", pdpBlack,
                 Font (40, "Liberation Mono Bold"));
    x = x_num_dots;
    y = y_num_dots;
    for (int k = 1; k < 5; k++)
    {
        doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                       Stroke (2, pdpBlack));
        doc << Line (Point (x - 7, y), Point (x + 7, y),
                     Stroke (2, pdpBlack));
        doc << Line (Point (x, y - 7), Point (x, y + 7),
                     Stroke (2, pdpBlack));
        x = x + x_inc;
    }
    x = x_suits_dots;
    y = y_suits_dots;
    for (int k = 1; k < 6; k++)
    {

        doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                       Stroke (2, pdpBlack));
        doc << Line (Point (x - 7, y), Point (x + 7, y),
                     Stroke (2, pdpBlack));
        doc << Line (Point (x, y - 7), Point (x, y + 7),
                     Stroke (2, pdpBlack));
        x = x + x_inc;
    }

    int y2 = y_suits;
    y = y_numbers;
    x = x_suits;
    for (int k = 0; k < 6; k++)
    {
        switch (k)
        {
        case 0:
            doc << Text (Point (x, y2), "H", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            doc << Text (Point (x, y), "7", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;

        case 1:
            doc << Text (Point (x, y2), "C", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            doc << Text (Point (x, y), "8", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;

        case 2:
            doc << Text (Point (x, y2), "D", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            doc << Text (Point (x, y), "9", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;

        case 3:
            doc << Text (Point (x, y2), "S", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            doc << Text (Point (x, y), "10", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        case 4:
            doc << Text (Point (x, y2), "N", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;

        }
        x = x + x_inc;
    }

    // now the game counting holes
    for (int k = 0; k < 6; k++) // up to five games
    {
        x = x_origin + k * hole_spacing * 1.5 + 23 * hole_spacing - 5;

        for (int m = 0; m < 2; m++)     // two teams
        {
            y = y_origin + m * hole_spacing + 89 - hole_spacing / 2;

            doc << Circle (Point (x, y), 13, Fill (pdpWhite),
                           Stroke (2, pdpBlack));
            doc << Line (Point (x - 7, y), Point (x + 7, y),
                         Stroke (2, pdpBlack));
            doc << Line (Point (x, y - 7), Point (x, y + 7),
                         Stroke (2, pdpBlack));


        }
        y = y_origin + 130;
        x = x - hole_spacing / 3 -4 ;
        switch (k)
        {
        case 0:
            break;
        case 1:
            doc << Text (Point (x, y), "1", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        case 2:
            doc << Text (Point (x, y), "2", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        case 3:
            doc << Text (Point (x, y), "3", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        case 4:
            doc << Text (Point (x, y), "4", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        case 5:
            doc << Text (Point (x, y), "5", pdpBlack,
                         Font (40, "Liberation Mono Bold"));
            break;
        }
        doc << Text (Point (x_origin + 651 + hole_spacing, y_origin + 165),
                     "Wins", pdpBlack, Font (40, "Liberation Mono Bold"));
    }

    //remaining Text
    doc << Text (Point (x_origin - 770, y_origin + 165), "Kaiser", pdpBlack,
                 Font (70, "Liberation Mono Bold"));
    doc << Text (Point (x_origin - 45, y_origin - 10), "Start", pdpBlack,
                 Font (40, "Liberation Mono Bold"));

    doc << Text (Point (x_origin - 7 * hole_spacing, y_origin - 193), "52",
                 pdpBlack, Font (40, "Liberation Mono Bold"));
    doc << Text (Point (x_origin - 19 * hole_spacing, y_origin - 193), "62",
                 pdpBlack, Font (40, "Liberation Mono Bold"));
    doc << Text (Point (x_origin + 17 * hole_spacing, y_origin + 165), "-62",
                 pdpBlack, Font (40, "Liberation Mono Bold"));
    doc << Text (Point (x_origin + 5 * hole_spacing, y_origin + 165), "-52",
                 pdpBlack, Font (40, "Liberation Mono Bold"));
    // plus and minus
    doc <<
        Text (Point
              (x_origin - 1.5 * hole_spacing, y_origin + row_spacing - 10),
              "-", pdpBlack, Font (40, "Liberation Mono Bold"));
    // plus and minus
    doc <<
        Text (Point
              (x_origin + 0.5 * hole_spacing, y_origin + row_spacing - 10),
              "+", pdpBlack, Font (40, "Liberation Mono Bold"));
    // plus and minus

    // tic marks
    doc << Line (Point (x_origin, y_origin + row_spacing),
                 Point (x_origin, y_origin - row_spacing), Stroke (4,
                                                                   pdpBlack));
    doc <<
        Line (Point
              (x_origin + 6 * hole_spacing,
               y_origin + 2 * radius + 2 * row_spacing),
              Point (x_origin + 6 * hole_spacing, y_origin + 2 * radius),
              Stroke (4, pdpBlack));
    doc <<
        Line (Point
              (x_origin + 18 * hole_spacing,
               y_origin + 2 * radius + 2 * row_spacing),
              Point (x_origin + 18 * hole_spacing, y_origin + 2 * radius),
              Stroke (4, pdpBlack));

    doc <<
        Line (Point
              (x_origin - 18 * hole_spacing,
               y_origin - 2 * radius - 2 * row_spacing),
              Point (x_origin - 18 * hole_spacing, y_origin - 2 * radius),
              Stroke (4, pdpBlack));
    doc <<
        Line (Point
              (x_origin - 6 * hole_spacing,
               y_origin - 2 * radius - 2 * row_spacing),
              Point (x_origin - 6 * hole_spacing, y_origin - 2 * radius),
              Stroke (4, pdpBlack));
    doc.save ();
}
