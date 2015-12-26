# Morton-Z-Code-C-library
Morton Z code encoding/decoding/manipulation - c headers 3D, 2D 32 and 64 bit

The Morton order is a mapping from an n-dimensional space onto a linear list of numbers. If you apply it to coordinates, the morton order defines a space-filling curve which is Z-shaped – so it is often is often called Z-order or Z-curve. This idea has inspired a lot of people doing great stuff with graphics (especially ray tracing and collision detection), compression, etc.

The other libraries seem to generally assume that a z-code will be generated each time coordinates are selected. This one uses "tesseral arithmetic" to directly add/subtract values to z-encoded coordinates, which makes it very efficient for defining a space and doing things inside (or outside) it. 

Nearly all of these functions could be made into one-liners with a little code golf; MSVC (by default) and GCC (with -O) will happily inline them. There is a little bit of test code at the end of each file for inspiration. 

A quick summary, from the 2d_32bit library - the others have the same functionality

/* Morton codes - Thanks to -
   fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
   www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
   gist.github.com/aavenel/a5349516aa33b7499eef */

/* push everything apart to make space */
uint32_t ulMC2Dspread(uint32_t);

/* inverse of spread */
uint16_t ulMC2Dcompact(uint32_t);

/* put x,y coordinates into Morton code form */
uint32_t ulMC2Dencode(uint16_t, uint16_t);

/* get the original x / y coordinate from the Morton code */
uint16_t ulMC2DdecodeX(uint32_t);
uint16_t ulMC2DdecodeY(uint32_t);

/* get the spread x / y coordinate from the Morton code */
uint32_t ulMC2DgetX(uint32_t);
uint32_t ulMC2DgetY(uint32_t);

/* Tesseral arithmetic  - Thanks to -
   asgerhoedt.dk/?p=276
   cgi.csc.liv.ac.uk/~frans/OldResearch/dGKBIS/tesseral.html
   bitmath.blogspot.my/search?q=tesseral */

/* individual coordinates of two Morton codes */
uint32_t ulMC2Dxplusx(uint32_t, uint32_t);
uint32_t ulMC2Dxminusx(uint32_t, uint32_t);

uint32_t ulMC2Dyplusy(uint32_t, uint32_t);
uint32_t ulMC2Dyminusy(uint32_t, uint32_t);

/* all coordinates of two Morton codes */
uint32_t ulMC2DplusMC(uint32_t, uint32_t);
uint32_t ulMC2DminusMC(uint32_t, uint32_t);

/* coordinate +/- any number: first argument is a morton code, second is spread(v) 
   or to simply increment/decrement, pass 1 without spread() as the second argument */
uint32_t ulMC2Dxplusv(uint32_t, uint32_t);
uint32_t ulMC2Dxminusv(uint32_t, uint32_t);

uint32_t ulMC2Dyplusv(uint32_t, uint32_t);
uint32_t ulMC2Dyminusv(uint32_t, uint32_t);

/* all coordinates */
uint32_t ulMC2Dplusv(uint32_t, uint32_t);
uint32_t ulMC2Dminusv(uint32_t, uint32_t);

/* coordinate divided by 2 */
uint32_t ulMC2Dhalfx(uint32_t);
uint32_t ulMC2Dhalfy(uint32_t);

/* element-wise min/max - diagonal corners of a box */
uint32_t ulMCMC2Dminxy(uint32_t, uint32_t);
uint32_t ulMCMC2Dmaxxy(uint32_t, uint32_t); 
/* center of element-wise min/max */ 
uint32_t ulMCMC2Dmidxy(uint32_t, uint32_t);

/* (these ? zero : amount_out_of_bounds) as the designated coordinate */
uint32_t ulMC2Dxplusx_o(uint32_t, uint32_t);
uint32_t ulMC2Dxminusx_o(uint32_t, uint32_t);

uint32_t ulMC2Dyplusy_o(uint32_t, uint32_t);
uint32_t ulMC2Dyminusy_o(uint32_t, uint32_t);

uint32_t ulMC2DplusMC_o(uint32_t, uint32_t);
uint32_t ulMC2DminusMC_o(uint32_t, uint32_t);

/* use spread(v) as second argument, first is a morton code */
uint32_t ulMC2Dxplusv_o(uint32_t, uint32_t);
uint32_t ulMC2Dxminusv_o(uint32_t, uint32_t);

uint32_t ulMC2Dyplusv_o(uint32_t, uint32_t);
uint32_t ulMC2Dyminusv_o(uint32_t, uint32_t);

uint32_t ulMC2Dplusv_o(uint32_t, uint32_t);
uint32_t ulMC2Dminusv_o(uint32_t, uint32_t);


