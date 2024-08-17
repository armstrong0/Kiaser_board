# Kiaser_board


The file Kaiser_board.cpp  contains instructions for building a template of a Kaiser board.  Kaiser is a card game popular in the Canadian prairies.

An executable is built from the cpp file and the simple_svg file.

That executable "gen_kaiser_board" creates and svg file.  

That svg file when printed at 100 dot per inch will produce a temple with a nominal hole spacing of 0.25 of an inch.

Various image manipulation programs can turn that svg file into a dot matrix image file which in turn can be used by splittopages the get two files that will print onto 8.5 x 11.  

I used gimp to convert the file to jpq.  Then used imagemagick to split into two pages.  

magick Kaiser_board.jpg -crop 2x1@ +repage %02d.jpg

I then used gimp with pixels/inch set to 100 to print the two pieces.

The template is 17 inches long!

Feel free to use and or modify this...


