/*
The MIT License(MIT)

Copyright(c) 2015 Inkblot Sdn. Bhd.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and / or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef MZC2D32_H_
#define MZC2D32_H_

/* unsigned (long) int x,y Morton Z code encoding/decoding/manipulation */

#include <limits.h>
/* c header for uintXX_t */
#include <inttypes.h>

/* Morton Code bitMasks - beats looking at all the numbers */

#define MC2DMASK32X  0x55555555
#define MC2DMASK32Y  0xAAAAAAAA

/* ullMC2Dspread(65535) - max for 16 bits */
#define MC2D32MAXX   1431655765 

/* C++ crowd seems to hate defines: leave out #include <inttypes.h> 
#include <stdint.h>

const uint32_t MC2DMASK32X = 0x09249249;  
const uint32_t MC2DMASK32Y = 0x12492492;  

const uint32_t MC2D64MAXX = 1431655765;
*/

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


/* Morton codes */
uint32_t ulMC2Dspread(uint32_t w) {
    w &= 0x0000ffff;                /* w = ---- ---- ---- ---- fedc ba98 7654 3210 */
    w = (w ^ (w << 8)) & 0x00ff00ff;  /* w = ---- ---- fedc ba98 ---- ---- 7654 3210 */
    w = (w ^ (w << 4)) & 0x0f0f0f0f;  /* w = ---- fedc ---- ba98 ---- 7654 ---- 3210 */
    w = (w ^ (w << 2)) & 0x33333333;  /* w = --fe --dc --ba --98 --76 --54 --32 --10 */
    w = (w ^ (w << 1)) & 0x55555555;  /* w = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0 */
    return w;
    }

/* inverse of Spread */
uint16_t ulMC2Dcompact(uint32_t w)  {
    w &= 0x55555555;                /* w = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0 */
    w = (w ^ (w >> 1)) & 0x33333333;  /* w = --fe --dc --ba --98 --76 --54 --32 --10 */
    w = (w ^ (w >> 2)) & 0x0f0f0f0f;  /* w = ---- fedc ---- ba98 ---- 7654 ---- 3210 */
    w = (w ^ (w >> 4)) & 0x00ff00ff;  /* w = ---- ---- fedc ba98 ---- ---- 7654 3210 */
    w = (w ^ (w >> 8)) & 0x0000ffff;  /* w = ---- ---- ---- ---- fedc ba98 7654 3210 */
	return (uint16_t)w;
    }


uint32_t ulMC2Dencode(uint16_t x, uint16_t y)  {
   return ((ulMC2Dspread((uint32_t)x)) | (ulMC2Dspread((uint32_t)y) << 1));
   }

uint16_t ulMC2DdecodeX(uint32_t code) {
    return ulMC2Dcompact(code);
    }
    
uint16_t ulMC2DdecodeY(uint32_t code) {
    return ulMC2Dcompact(code >> 1);    
    }

uint32_t ulMC2DgetX(uint32_t code) {
    return (code & MC2DMASK32X);    
    }
    
uint32_t ulMC2DgetY(uint32_t code) {
    return (code & MC2DMASK32Y);    
    }

    
/* Tesseral arithmetic */
uint32_t ulMC2Dxplusv(uint32_t p, uint32_t v)  {
    uint32_t xsum = (p | MC2DMASK32Y) + v;
    return ((xsum & MC2DMASK32X) | (p & MC2DMASK32Y)); 
    }

uint32_t ulMC2Dxminusv(uint32_t p, uint32_t v) {
    uint32_t xdif = (p & MC2DMASK32X) - v;
    return ((xdif & MC2DMASK32X) | (p & MC2DMASK32Y));
    }

uint32_t ulMC2Dyplusv(uint32_t p, uint32_t v)  {
    uint32_t ysum = (p | MC2DMASK32X) + (v<< 1);
    return ((ysum & MC2DMASK32Y) | (p & MC2DMASK32X)); 
    }

uint32_t ulMC2Dyminusv(uint32_t p, uint32_t v) {
    uint32_t ydif = (p & MC2DMASK32Y) - (v<< 1);
    return ((ydif & MC2DMASK32Y) | (p & MC2DMASK32X));
    }

uint32_t ulMC2Dxplusx(uint32_t p, uint32_t q)  {
    uint32_t xsum = (p | MC2DMASK32Y) + (q & MC2DMASK32X);
    return ((xsum & MC2DMASK32X) | (p & MC2DMASK32Y)); 
    }

uint32_t ulMC2Dxminusx(uint32_t p, uint32_t q) {
    uint32_t xdif = (p & MC2DMASK32X) - (q & MC2DMASK32X);
    return ((xdif & MC2DMASK32X) | (p & MC2DMASK32Y));
    } 

uint32_t ulMC2Dyplusy(uint32_t p, uint32_t q)  {
    uint32_t ysum = (p | MC2DMASK32X) + (q & MC2DMASK32Y);
    return ((ysum & MC2DMASK32Y) | (p & MC2DMASK32X));
    }

uint32_t ulMC2Dyminusy(uint32_t p, uint32_t q) {
    uint32_t ydif = (p & MC2DMASK32Y) - (q & MC2DMASK32Y);
    return ((ydif & MC2DMASK32Y) | (p & MC2DMASK32X));
    } 

uint32_t ulMC2DplusMC(uint32_t p, uint32_t q)  {
    uint32_t xsum = (p | MC2DMASK32Y) + (q & MC2DMASK32X);
    uint32_t ysum = (p | MC2DMASK32X) + (q & MC2DMASK32Y);
    return ((xsum & MC2DMASK32X) | (ysum & MC2DMASK32Y));
    }

uint32_t ulMC2DminusMC(uint32_t p, uint32_t q) {
    uint32_t xdif = (p & MC2DMASK32X) - (q & MC2DMASK32X);
    uint32_t ydif = (p & MC2DMASK32Y) - (q & MC2DMASK32Y);
    return ((xdif & MC2DMASK32X) | (ydif & MC2DMASK32Y));
    }
    
uint32_t ulMC2Dplusv(uint32_t p, uint32_t v)  {
    uint32_t xsum = (p | MC2DMASK32Y) + v;
    uint32_t ysum = (p | MC2DMASK32X) + (v<< 1);
    return ((xsum & MC2DMASK32X) | (ysum & MC2DMASK32Y));
    }

uint32_t ulMC2Dminusv(uint32_t p, uint32_t v) {
    uint32_t xdif = (p & MC2DMASK32X) - v;
    uint32_t ydif = (p & MC2DMASK32Y) - (v<< 1);
    return ((xdif & MC2DMASK32X) | (ydif & MC2DMASK32Y));
    }

uint32_t ulMC2Dhalfx(uint32_t p)  {
    uint32_t halfx = (p & MC2DMASK32X) >> 2;
    return ((halfx) | (p & MC2DMASK32Y)); 
    }

uint32_t ulMC2Dhalfy(uint32_t p) {
    uint32_t halfy = (p & MC2DMASK32Y) >> 2;
    return ((halfy) | (p & MC2DMASK32X));
    }   
    
uint32_t ulMCMC2Dminxy(uint32_t p, uint32_t q) {
    uint32_t xp = (p & MC2DMASK32X);
    uint32_t yp = (p & MC2DMASK32Y);
    uint32_t xq = (q & MC2DMASK32X);
    uint32_t yq = (q & MC2DMASK32Y);
    return ((xp > xq) ? xq : xp) + ((yp > yq) ? yq : yp);
    }

uint32_t ulMCMC2Dmaxxy(uint32_t p, uint32_t q) {
    uint32_t xp = (p & MC2DMASK32X);
    uint32_t yp = (p & MC2DMASK32Y);
    uint32_t xq = (q & MC2DMASK32X);
    uint32_t yq = (q & MC2DMASK32Y);
    return ((xp < xq) ? xq : xp) + ((yp < yq) ? yq : yp);
    }

uint32_t ulMCMC2Dmidxy(uint32_t p, uint32_t q) {
    uint32_t xymin = ulMCMC2Dminxy(p,q);
    uint32_t xydif = ulMC2DminusMC(ulMCMC2Dmaxxy(p,q),xymin);
    
    uint32_t xyhaf = ulMC2Dhalfx(xydif);
    xyhaf = ulMC2Dhalfy(xyhaf);

    return ulMC2DplusMC(xymin,xyhaf); 
    }

uint32_t ulMC2Dxplusv_o(uint32_t p, uint32_t v)  {
    uint32_t xsum = ((p | MC2DMASK32Y) + v) & MC2DMASK32X;
    return ((xsum > MC2D32MAXX) ? ((xsum - MC2D32MAXX) & MC2DMASK32X) : 0); 
    }

uint32_t ulMC2Dxminusv_o(uint32_t p, uint32_t v) {
    uint32_t mp = (p & MC2DMASK32X);
    return ((v > mp) ? ((v - mp) & MC2DMASK32X) : 0); 
    }

uint32_t ulMC2Dyplusv_o(uint32_t p, uint32_t v)  {
    uint32_t yasx = ((p & MC2DMASK32Y)>> 1);
    uint32_t xsum = ((yasx | MC2DMASK32Y) + v) & MC2DMASK32X;
    return ((xsum > MC2D32MAXX) ? (((xsum - MC2D32MAXX)<< 1) & MC2DMASK32Y) : 0); 
    }
    
uint32_t ulMC2Dyminusv_o(uint32_t p, uint32_t v) {
    uint32_t mp = (p & MC2DMASK32Y);
    uint32_t vy = v << 1;
    return ((vy > mp) ? ((vy - mp) & MC2DMASK32Y) : 0); 
    }

uint32_t ulMC2Dxplusx_o(uint32_t p, uint32_t q)  {
    uint32_t xsum = ((p | MC2DMASK32Y) + (q & MC2DMASK32X)) & MC2DMASK32X;
    return ((xsum > MC2D32MAXX) ? ((xsum - MC2D32MAXX) & MC2DMASK32X) : 0); 
    }  
  
uint32_t ulMC2Dxminusx_o(uint32_t p, uint32_t q) {
    uint32_t mp = (p & MC2DMASK32X);
    uint32_t mq = (q & MC2DMASK32X);
    return ((mq > mp) ? ((mq - mp) & MC2DMASK32X) : 0); 
    }

uint32_t ulMC2Dyplusy_o(uint32_t p, uint32_t q)  {
    uint32_t rx = ((p & MC2DMASK32Y)>> 1);
    uint32_t sx = ((q & MC2DMASK32Y)>> 1);
    uint32_t xsum = ((rx | MC2DMASK32Y) + (sx & MC2DMASK32X)) & MC2DMASK32X;
    return ((xsum > MC2D32MAXX) ? (((xsum - MC2D32MAXX) & MC2DMASK32X)<< 1) : 0); 
    }  

uint32_t ulMC2Dyminusy_o(uint32_t p, uint32_t q) {
    uint32_t mp = (p & MC2DMASK32Y);
    uint32_t mq = (q & MC2DMASK32Y);
    return ((mq > mp) ? ((mq - mp) & MC2DMASK32Y) : 0); 
    }
    
uint32_t ulMC2DplusMC_o(uint32_t p, uint32_t q) {
    uint32_t xo = ulMC2Dxplusx_o(p,q);
    uint32_t yo = ulMC2Dyplusy_o(p,q);
    return ((xo & MC2DMASK32X) | (yo & MC2DMASK32Y));
    }
    
uint32_t ulMC2DminusMC_o(uint32_t p, uint32_t q) {
    uint32_t xo = ulMC2Dxminusx_o(p,q);
    uint32_t yo = ulMC2Dyminusy_o(p,q);
    return ((xo & MC2DMASK32X) | (yo & MC2DMASK32Y));
    }

uint32_t ulMC2Dplusv_o(uint32_t p, uint32_t v) {
    uint32_t xo = ulMC2Dxplusv_o(p,v);
    uint32_t yo = ulMC2Dyplusv_o(p,v);
    return ((xo & MC2DMASK32X) | (yo & MC2DMASK32Y));
    } 
    
uint32_t ulMC2Dminusv_o(uint32_t p, uint32_t v) {
    uint32_t xo = ulMC2Dxminusv_o(p,v);
    uint32_t yo = ulMC2Dyminusv_o(p,v);
    return ((xo & MC2DMASK32X) | (yo & MC2DMASK32Y));
    } 


#endif

/*
#include <stdio.h>

int main() {

    uint16_t ax=600, ay=500, bx=300, by=200, m = 451;
    
    uint32_t ae = ulMC2Dencode(ax,ay);
    uint32_t be = ulMC2Dencode(bx,by);

    printf("X: %u | Y: %u\n", ulMC2DdecodeX(ae),ulMC2DdecodeY(ae));
    printf("X: %u | Y: %u\n", ulMC2DdecodeX(be),ulMC2DdecodeY(be));

    uint32_t mp = ulMCMC2Dmidxy(ae,be); 
    printf("mid- X: %u  | Y: %u\n", ulMC2DdecodeX(mp),ulMC2DdecodeY(mp));

    uint32_t mx = ulMC2Dminusv_o(be,ulMC2Dspread((uint32_t)m));
    printf("v_o- X: %u  | Y: %u\n", ulMC2DdecodeX(mx),ulMC2DdecodeY(mx));
    
    return 0;
    }
*/
