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

#ifndef MZC2D64_H_
#define MZC2D64_H_

/* unsigned long long x,y Morton Z code encoding/decoding/manipulation */

#include <limits.h>
/* c header for uintXX_t */
#include <inttypes.h>

/* Morton Code bitMasks - beats looking at all the numbers */

#define MC2DMASK64X  0x5555555555555555
#define MC2DMASK64Y  0xAAAAAAAAAAAAAAAA

/* ullMC2Dspread(4294967295) - max for 32 bits */
#define MC2D64MAXX   6148914691236517205 

/* C++ crowd seems to hate defines: leave out #include <inttypes.h> 
#include <stdint.h>

const uint64_t MC2DMASK64X = 0x5555555555555555; 
const uint64_t MC2DMASK64Y = 0xAAAAAAAAAAAAAAAA; 

const uint64_t MC2D64MAXX = 6148914691236517205;
*/

/* Morton codes - Thanks to -
fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
gist.github.com/aavenel/a5349516aa33b7499eef */

/* push everything apart to make space */
uint64_t ullMC2Dspread(uint64_t);

/* inverse of spread */
uint32_t ullMC2Dcompact(uint64_t);

/* put x,y coordinates into Morton code form */
uint64_t ullMC2Dencode(uint32_t, uint32_t);

/* get the original x / y coordinate from the Morton code */
uint32_t ullMC2DdecodeX(uint64_t);
uint32_t ullMC2DdecodeY(uint64_t);

/* get the spread x / y coordinate from the Morton code */
uint64_t ullMC2DgetX(uint64_t);
uint64_t ullMC2DgetY(uint64_t);

/* Tesseral arithmetic  - Thanks to -
   asgerhoedt.dk/?p=276
   cgi.csc.liv.ac.uk/~frans/OldResearch/dGKBIS/tesseral.html
   bitmath.blogspot.my/search?q=tesseral */

/* individual coordinates of two Morton codes */
uint64_t ullMC2Dxplusx(uint64_t, uint64_t);
uint64_t ullMC2Dxminusx(uint64_t, uint64_t);

uint64_t ullMC2Dyplusy(uint64_t, uint64_t);
uint64_t ullMC2Dyminusy(uint64_t, uint64_t);

/* all coordinates of two Morton codes */
uint64_t ullMC2DplusMC(uint64_t, uint64_t);
uint64_t ullMC2DminusMC(uint64_t, uint64_t);

/* coordinate +/- any number: first argument is a morton code, second is spread(v) 
   or to simply increment/decrement, pass 1 without spread() as the second argument */
uint64_t ullMC2Dxplusv(uint64_t, uint64_t);
uint64_t ullMC2Dxminusv(uint64_t, uint64_t);

uint64_t ullMC2Dyplusv(uint64_t, uint64_t);
uint64_t ullMC2Dyminusv(uint64_t, uint64_t);

/* all coordinates */
uint64_t ullMC2Dplusv(uint64_t, uint64_t);
uint64_t ullMC2Dminusv(uint64_t, uint64_t);

/* coordinate divided by 2 */
uint64_t ullMC2Dhalfx(uint64_t);
uint64_t ullMC2Dhalfy(uint64_t);

/* element-wise min/max - diagonal corners of a box */
uint64_t ullMCMC2Dminxy(uint64_t, uint64_t);
uint64_t ullMCMC2Dmaxxy(uint64_t, uint64_t); 
/* center of element-wise min/max */ 
uint64_t ullMCMC2Dmidxy(uint64_t, uint64_t);

/* (these ? zero : amount_out_of_bounds) as the designated coordinate */
uint64_t ullMC2Dxplusx_o(uint64_t, uint64_t);
uint64_t ullMC2Dxminusx_o(uint64_t, uint64_t);

uint64_t ullMC2Dyplusy_o(uint64_t, uint64_t);
uint64_t ullMC2Dyminusy_o(uint64_t, uint64_t);

uint64_t ullMC2DplusMC_o(uint64_t, uint64_t);
uint64_t ullMC2DminusMC_o(uint64_t, uint64_t);

/* use spread(v) as second argument, first is a morton code */
uint64_t ullMC2Dxplusv_o(uint64_t, uint64_t);
uint64_t ullMC2Dxminusv_o(uint64_t, uint64_t);

uint64_t ullMC2Dyplusv_o(uint64_t, uint64_t);
uint64_t ullMC2Dyminusv_o(uint64_t, uint64_t);

uint64_t ullMC2Dplusv_o(uint64_t, uint64_t);
uint64_t ullMC2Dminusv_o(uint64_t, uint64_t);


/* Morton codes */
uint64_t ullMC2Dspread(uint64_t w)  {
    w &= 0x00000000ffffffff;
    w = (w ^ (w << 16)) & 0x0000ffff0000ffff;
    w = (w ^ (w << 8 )) & 0x00ff00ff00ff00ff;
    w = (w ^ (w << 4 )) & 0x0f0f0f0f0f0f0f0f;
    w = (w ^ (w << 2 )) & 0x3333333333333333;
    w = (w ^ (w << 1 )) & 0x5555555555555555;
    return w;
    } 

/* inverse of Spread */
uint32_t ullMC2Dcompact(uint64_t w) {
    w &= 0x5555555555555555;
    w = (w ^ (w >> 1 )) & 0x3333333333333333;
    w = (w ^ (w >> 2 )) & 0x0f0f0f0f0f0f0f0f;
    w = (w ^ (w >> 4 )) & 0x00ff00ff00ff00ff;
    w = (w ^ (w >> 8 )) & 0x0000ffff0000ffff;
    w = (w ^ (w >> 16)) & 0x00000000ffffffff;
    return (uint32_t)w;
    }


uint64_t ullMC2Dencode(uint32_t x, uint32_t y)  {
   return ((ullMC2Dspread((uint64_t)x)) | (ullMC2Dspread((uint64_t)y) << 1));
   }

uint32_t ullMC2DdecodeX(uint64_t code) {
    return ullMC2Dcompact(code);
    }
    
uint32_t ullMC2DdecodeY(uint64_t code) {
    return ullMC2Dcompact(code >> 1);    
    }

uint64_t ullMC2DgetX(uint64_t code) {
    return (code & MC2DMASK64X);    
    }
    
uint64_t ullMC2DgetY(uint64_t code) {
    return (code & MC2DMASK64Y);    
    }

    
/* Tesseral arithmetic */
uint64_t ullMC2Dxplusv(uint64_t p, uint64_t v)  {
    uint64_t xsum = (p | MC2DMASK64Y) + v;
    return ((xsum & MC2DMASK64X) | (p & MC2DMASK64Y)); 
    }

uint64_t ullMC2Dxminusv(uint64_t p, uint64_t v) {
    uint64_t xdif = (p & MC2DMASK64X) - v;
    return ((xdif & MC2DMASK64X) | (p & MC2DMASK64Y));
    }

uint64_t ullMC2Dyplusv(uint64_t p, uint64_t v)  {
    uint64_t ysum = (p | MC2DMASK64X) + (v<< 1);
    return ((ysum & MC2DMASK64Y) | (p & MC2DMASK64X)); 
    }

uint64_t ullMC2Dyminusv(uint64_t p, uint64_t v) {
    uint64_t ydif = (p & MC2DMASK64Y) - (v<< 1);
    return ((ydif & MC2DMASK64Y) | (p & MC2DMASK64X));
    }

uint64_t ullMC2Dxplusx(uint64_t p, uint64_t q)  {
    uint64_t xsum = (p | MC2DMASK64Y) + (q & MC2DMASK64X);
    return ((xsum & MC2DMASK64X) | (p & MC2DMASK64Y)); 
    }

uint64_t ullMC2Dxminusx(uint64_t p, uint64_t q) {
    uint64_t xdif = (p & MC2DMASK64X) - (q & MC2DMASK64X);
    return ((xdif & MC2DMASK64X) | (p & MC2DMASK64Y));
    } 

uint64_t ullMC2Dyplusy(uint64_t p, uint64_t q)  {
    uint64_t ysum = (p | MC2DMASK64X) + (q & MC2DMASK64Y);
    return ((ysum & MC2DMASK64Y) | (p & MC2DMASK64X));
    }

uint64_t ullMC2Dyminusy(uint64_t p, uint64_t q) {
    uint64_t ydif = (p & MC2DMASK64Y) - (q & MC2DMASK64Y);
    return ((ydif & MC2DMASK64Y) | (p & MC2DMASK64X));
    } 

uint64_t ullMC2DplusMC(uint64_t p, uint64_t q)  {
    uint64_t xsum = (p | MC2DMASK64Y) + (q & MC2DMASK64X);
    uint64_t ysum = (p | MC2DMASK64X) + (q & MC2DMASK64Y);
    return ((xsum & MC2DMASK64X) | (ysum & MC2DMASK64Y));
    }

uint64_t ullMC2DminusMC(uint64_t p, uint64_t q) {
    uint64_t xdif = (p & MC2DMASK64X) - (q & MC2DMASK64X);
    uint64_t ydif = (p & MC2DMASK64Y) - (q & MC2DMASK64Y);
    return ((xdif & MC2DMASK64X) | (ydif & MC2DMASK64Y));
    }
    
uint64_t ullMC2Dplusv(uint64_t p, uint64_t v)  {
    uint64_t xsum = (p | MC2DMASK64Y) + v;
    uint64_t ysum = (p | MC2DMASK64X) + (v<< 1);
    return ((xsum & MC2DMASK64X) | (ysum & MC2DMASK64Y));
    }

uint64_t ullMC2Dminusv(uint64_t p, uint64_t v) {
    uint64_t xdif = (p & MC2DMASK64X) - v;
    uint64_t ydif = (p & MC2DMASK64Y) - (v<< 1);
    return ((xdif & MC2DMASK64X) | (ydif & MC2DMASK64Y));
    }

uint64_t ullMC2Dhalfx(uint64_t p)  {
    uint64_t halfx = (p & MC2DMASK64X) >> 3;
    return ((halfx) | (p & MC2DMASK64Y)); 
    }

uint64_t ullMC2Dhalfy(uint64_t p) {
    uint64_t halfy = (p & MC2DMASK64Y) >> 3;
    return ((halfy) | (p & MC2DMASK64X));
    }   
    
uint64_t ullMCMC2Dminxy(uint64_t p, uint64_t q) {
    uint64_t xp = (p & MC2DMASK64X);
    uint64_t yp = (p & MC2DMASK64Y);
    uint64_t xq = (q & MC2DMASK64X);
    uint64_t yq = (q & MC2DMASK64Y);
    return ((xp > xq) ? xq : xp) + ((yp > yq) ? yq : yp);
    }

uint64_t ullMCMC2Dmaxxy(uint64_t p, uint64_t q) {
    uint64_t xp = (p & MC2DMASK64X);
    uint64_t yp = (p & MC2DMASK64Y);
    uint64_t xq = (q & MC2DMASK64X);
    uint64_t yq = (q & MC2DMASK64Y);
    return ((xp < xq) ? xq : xp) + ((yp < yq) ? yq : yp);
    }

uint64_t ullMCMC2Dmidxy(uint64_t p, uint64_t q) {
    uint64_t xymin = ullMCMC2Dminxy(p,q);
    uint64_t xydif = ullMC2DminusMC(ullMCMC2Dmaxxy(p,q),xymin);
    
    uint64_t xyhaf = ullMC2Dhalfx(xydif);
    xyhaf = ullMC2Dhalfy(xyhaf);

    return ullMC2DplusMC(xymin,xyhaf); 
    }

uint64_t ullMC2Dxplusv_o(uint64_t p, uint64_t v)  {
    uint64_t xsum = ((p | MC2DMASK64Y) + v) & MC2DMASK64X;
    return ((xsum > MC2D64MAXX) ? ((xsum - MC2D64MAXX) & MC2DMASK64X) : 0); 
    }

uint64_t ullMC2Dxminusv_o(uint64_t p, uint64_t v) {
    uint64_t mp = (p & MC2DMASK64X);
    return ((v > mp) ? ((v - mp) & MC2DMASK64X) : 0); 
    }

uint64_t ullMC2Dyplusv_o(uint64_t p, uint64_t v)  {
    uint64_t yasx = ((p & MC2DMASK64Y)>> 1);
    uint64_t xsum = ((yasx | MC2DMASK64Y) + v) & MC2DMASK64X;
    return ((xsum > MC2D64MAXX) ? (((xsum - MC2D64MAXX)<< 1) & MC2DMASK64Y) : 0); 
    }
    
uint64_t ullMC2Dyminusv_o(uint64_t p, uint64_t v) {
    uint64_t mp = (p & MC2DMASK64Y);
    uint64_t vy = v << 1;
    return ((vy > mp) ? ((vy - mp) & MC2DMASK64Y) : 0); 
    }

uint64_t ullMC2Dxplusx_o(uint64_t p, uint64_t q)  {
    uint64_t xsum = ((p | MC2DMASK64Y) + (q & MC2DMASK64X)) & MC2DMASK64X;
    return ((xsum > MC2D64MAXX) ? ((xsum - MC2D64MAXX) & MC2DMASK64X) : 0); 
    }  
  
uint64_t ullMC2Dxminusx_o(uint64_t p, uint64_t q) {
    uint64_t mp = (p & MC2DMASK64X);
    uint64_t mq = (q & MC2DMASK64X);
    return ((mq > mp) ? ((mq - mp) & MC2DMASK64X) : 0); 
    }

uint64_t ullMC2Dyplusy_o(uint64_t p, uint64_t q)  {
    uint64_t rx = ((p & MC2DMASK64Y)>> 1);
    uint64_t sx = ((q & MC2DMASK64Y)>> 1);
    uint64_t xsum = ((rx | MC2DMASK64Y) + (sx & MC2DMASK64X)) & MC2DMASK64X;
    return ((xsum > MC2D64MAXX) ? (((xsum - MC2D64MAXX) & MC2DMASK64X)<< 1) : 0); 
    }  

uint64_t ullMC2Dyminusy_o(uint64_t p, uint64_t q) {
    uint64_t mp = (p & MC2DMASK64Y);
    uint64_t mq = (q & MC2DMASK64Y);
    return ((mq > mp) ? ((mq - mp) & MC2DMASK64Y) : 0); 
    }
    
uint64_t ullMC2DplusMC_o(uint64_t p, uint64_t q) {
    uint64_t xo = ullMC2Dxplusx_o(p,q);
    uint64_t yo = ullMC2Dyplusy_o(p,q);
    return ((xo & MC2DMASK64X) | (yo & MC2DMASK64Y));
    }
    
uint64_t ullMC2DminusMC_o(uint64_t p, uint64_t q) {
    uint64_t xo = ullMC2Dxminusx_o(p,q);
    uint64_t yo = ullMC2Dyminusy_o(p,q);
    return ((xo & MC2DMASK64X) | (yo & MC2DMASK64Y));
    }

uint64_t ullMC2Dplusv_o(uint64_t p, uint64_t v) {
    uint64_t xo = ullMC2Dxplusv_o(p,v);
    uint64_t yo = ullMC2Dyplusv_o(p,v);
    return ((xo & MC2DMASK64X) | (yo & MC2DMASK64Y));
    } 
    
uint64_t ullMC2Dminusv_o(uint64_t p, uint64_t v) {
    uint64_t xo = ullMC2Dxminusv_o(p,v);
    uint64_t yo = ullMC2Dyminusv_o(p,v);
    return ((xo & MC2DMASK64X) | (yo & MC2DMASK64Y));
    } 


#endif

/*
#include <stdio.h>
int main() {

    uint32_t ax=600, ay=500, bx=300, by=200, m = 451;
    
    uint64_t ae = ullMC2Dencode(ax,ay);
    uint64_t be = ullMC2Dencode(bx,by);

    printf("X: %u | Y: %u\n", ullMC2DdecodeX(ae),ullMC2DdecodeY(ae));
    printf("X: %u | Y: %u\n", ullMC2DdecodeX(be),ullMC2DdecodeY(be));

    uint64_t mp = ullMCMC2Dmidxy(ae,be); 
    printf("mid- X: %u  | Y: %u\n", ullMC2DdecodeX(mp),ullMC2DdecodeY(mp));

    uint64_t mx = ullMC2Dminusv_o(be,ullMC2Dspread((uint64_t)m));
    printf("v_o- X: %u  | Y: %u\n", ullMC2DdecodeX(mx),ullMC2DdecodeY(mx));

    return 0;
    }
*/
