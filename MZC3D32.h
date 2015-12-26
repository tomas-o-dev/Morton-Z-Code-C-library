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

#ifndef MZC3D32_H_
#define MZC3D32_H_

/* unsigned (long) int x,y,z Morton Z code encoding/decoding/manipulation */

#include <limits.h>
/* c header for uintXX_t */
#include <inttypes.h>

/* Morton Code bitMasks - beats looking at all the numbers
   32/3: only the first 10 bits are used */

#define MC3DMASK32X   0x09249249
#define MC3DMASK32Y   0x12492492
#define MC3DMASK32Z   0x24924924

#define MC3DMASK32XY  (MC3DMASK32X | MC3DMASK32Y)
#define MC3DMASK32XZ  (MC3DMASK32X | MC3DMASK32Z)
#define MC3DMASK32YZ  (MC3DMASK32Y | MC3DMASK32Z)

/* ullMC3Dspread(1023) - max for 10 bits */
#define MC3D32MAXX    153391689 

/* C++ crowd seems to hate defines: leave out #include <inttypes.h> 
#include <stdint.h>

const uint32_t MC3DMASK32X = 0x09249249;  
const uint32_t MC3DMASK32Y = 0x12492492;  
const uint32_t MC3DMASK32Z = 0x24924924; 

const uint32_t MC3DMASK32XY = (MC3DMASK32X | MC3DMASK32Y);
const uint32_t MC3DMASK32XZ = (MC3DMASK32X | MC3DMASK32Z);
const uint32_t MC3DMASK32YZ = (MC3DMASK32Y | MC3DMASK32Z);

const uint32_t MC3D64MAXX = 153391689;
*/

/* Morton codes - Thanks to -
fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
gist.github.com/aavenel/a5349516aa33b7499eef */

/* push everything apart to make space - only the first 10 bits are used */
uint32_t ulMC3Dspread(uint32_t);

/* inverse of spread */
uint16_t ulMC3Dcompact(uint32_t);

/* put x,y,z coordinates into Morton code form */
uint32_t ulMC3Dencode(uint16_t, uint16_t, uint16_t);

/* get the original x / y / z coordinate from the Morton code */
uint16_t ulMC3DdecodeX(uint32_t);
uint16_t ulMC3DdecodeY(uint32_t);
uint16_t ulMC3DdecodeZ(uint32_t);

/* get the spread x / y / z coordinate from the Morton code */
uint32_t ulMC3DgetX(uint32_t);
uint32_t ulMC3DgetY(uint32_t);
uint32_t ulMC3DgetZ(uint32_t);

/* Tesseral arithmetic  - Thanks to -
   asgerhoedt.dk/?p=276
   cgi.csc.liv.ac.uk/~frans/OldResearch/dGKBIS/tesseral.html
   bitmath.blogspot.my/search?q=tesseral */

/* individual coordinates of two Morton codes */
uint32_t ulMC3Dxplusx(uint32_t, uint32_t);
uint32_t ulMC3Dxminusx(uint32_t, uint32_t);

uint32_t ulMC3Dyplusy(uint32_t, uint32_t);
uint32_t ulMC3Dyminusy(uint32_t, uint32_t);

uint32_t ulMC3Dzplusz(uint32_t, uint32_t);
uint32_t ulMC3Dzminusz(uint32_t, uint32_t);

/* all coordinates of two Morton codes */
uint32_t ulMC3DplusMC(uint32_t, uint32_t);
uint32_t ulMC3DminusMC(uint32_t, uint32_t);

/* coordinate +/- any number: first argument is a morton code, second is spread(v) 
   or to simply increment/decrement, pass 1 without spread() as the second argument */
uint32_t ulMC3Dxplusv(uint32_t, uint32_t);
uint32_t ulMC3Dxminusv(uint32_t, uint32_t);

uint32_t ulMC3Dyplusv(uint32_t, uint32_t);
uint32_t ulMC3Dyminusv(uint32_t, uint32_t);

uint32_t ulMC3Dzplusv(uint32_t, uint32_t);
uint32_t ulMC3Dzminusv(uint32_t, uint32_t);

/* all coordinates */
uint32_t ulMC3Dplusv(uint32_t, uint32_t);
uint32_t ulMC3Dminusv(uint32_t, uint32_t);

/* coordinate divided by 2 */
uint32_t ulMC3Dhalfx(uint32_t);
uint32_t ulMC3Dhalfy(uint32_t);
uint32_t ulMC3Dhalfz(uint32_t);

/* element-wise min/max - diagonal corners of a box */
uint32_t ulMCMC3Dminxyz(uint32_t, uint32_t);
uint32_t ulMCMC3Dmaxxyz(uint32_t, uint32_t); 
/* center of element-wise min/max */ 
uint32_t ulMCMC3Dmidxyz(uint32_t, uint32_t);

/* (these ? zero : amount_out_of_bounds) as the designated coordinate */
uint32_t ulMC3Dxplusx_o(uint32_t, uint32_t);
uint32_t ulMC3Dxminusx_o(uint32_t, uint32_t);

uint32_t ulMC3Dyplusy_o(uint32_t, uint32_t);
uint32_t ulMC3Dyminusy_o(uint32_t, uint32_t);

uint32_t ulMC3Dzplusz_o(uint32_t, uint32_t);
uint32_t ulMC3Dzminusz_o(uint32_t, uint32_t);

uint32_t ulMC3DplusMC_o(uint32_t, uint32_t);
uint32_t ulMC3DminusMC_o(uint32_t, uint32_t);

/* use spread(v) as second argument, first is a morton code */
uint32_t ulMC3Dxplusv_o(uint32_t, uint32_t);
uint32_t ulMC3Dxminusv_o(uint32_t, uint32_t);

uint32_t ulMC3Dyplusv_o(uint32_t, uint32_t);
uint32_t ulMC3Dyminusv_o(uint32_t, uint32_t);

uint32_t ulMC3Dzplusv_o(uint32_t, uint32_t);
uint32_t ulMC3Dzminusv_o(uint32_t, uint32_t);

uint32_t ulMC3Dplusv_o(uint32_t, uint32_t);
uint32_t ulMC3Dminusv_o(uint32_t, uint32_t);


/* Morton codes */
/* push everything apart to make space - only the first 10 bits are used */

uint32_t ulMC3Dspread(uint32_t w) {
    w &=                0x000003ff; /* w = ---- ---- ---- ---- ---- --98 7654 3210 */
    w = (w | w << 16) & 0x030000ff; 
    w = (w | w <<  8) & 0x0300f00f;
    w = (w | w <<  4) & 0x030c30c3;
    w = (w | w <<  2) & 0x09249249; /* w = uu-- 9--8 --7- -6-- 5--4 --3- -2-- 1--0 */
    return w;
    }

/* inverse of Spread */
uint16_t ulMC3Dcompact(uint32_t w)  {
	 w &=                  0x09249249;
	 w = (w ^ (w >>  2)) & 0x030c30c3;
	 w = (w ^ (w >>  4)) & 0x0f00f00f;
	 w = (w ^ (w >>  8)) & 0xff0000ff;
	 w = (w ^ (w >> 16)) & 0x0000ffff;
	 return (uint16_t)w;
    }

uint32_t ulMC3Dencode(uint16_t x, uint16_t y, uint16_t z)  {
   return ((ulMC3Dspread((uint32_t)x)) | (ulMC3Dspread((uint32_t)y) << 1) | (ulMC3Dspread((uint32_t)z) << 2));
   }

uint16_t ulMC3DdecodeX(uint32_t code) {
    return ulMC3Dcompact(code);
    }
    
uint16_t ulMC3DdecodeY(uint32_t code) {
    return ulMC3Dcompact(code >> 1);    
    }

uint16_t ulMC3DdecodeZ(uint32_t code) {
    return ulMC3Dcompact(code >> 2);    
    }

uint32_t ulMC3DgetX(uint32_t code) {
    return (code & MC3DMASK32X);    
    }
    
uint32_t ulMC3DgetY(uint32_t code) {
    return (code & MC3DMASK32Y);    
    }
    
uint32_t ulMC3DgetZ(uint32_t code) {
    return (code & MC3DMASK32Z);    
    }
    
/* Tesseral arithmetic */
uint32_t ulMC3Dxplusv(uint32_t p, uint32_t v)  {
    uint32_t xsum = (p | MC3DMASK32YZ) + v;
    return ((xsum & MC3DMASK32X) | (p & MC3DMASK32YZ)); 
    }

uint32_t ulMC3Dxminusv(uint32_t p, uint32_t v) {
    uint32_t xdif = (p & MC3DMASK32X) - v;
    return ((xdif & MC3DMASK32X) | (p & MC3DMASK32YZ));
    }

uint32_t ulMC3Dyplusv(uint32_t p, uint32_t v)  {
    uint32_t ysum = (p | MC3DMASK32XZ) + (v<< 1);
    return ((ysum & MC3DMASK32Y) | (p & MC3DMASK32XZ)); 
    }

uint32_t ulMC3Dyminusv(uint32_t p, uint32_t v) {
    uint32_t ydif = (p & MC3DMASK32Y) - (v<< 1);
    return ((ydif & MC3DMASK32Y) | (p & MC3DMASK32XZ));
    }

uint32_t ulMC3Dzplusv(uint32_t p, uint32_t v)  {
    uint32_t zsum = (p | MC3DMASK32XY) + (v<< 2);
    return ((zsum & MC3DMASK32Z) | (p & MC3DMASK32XY)); 
    }

uint32_t ulMC3Dzminusv(uint32_t p, uint32_t v) {
    uint32_t zdif = (p & MC3DMASK32Z) - (v<< 2);
    return ((zdif & MC3DMASK32Z) | (p & MC3DMASK32XY));
    }

uint32_t ulMC3Dxplusx(uint32_t p, uint32_t q)  {
    uint32_t xsum = (p | MC3DMASK32YZ) + (q & MC3DMASK32X);
    return ((xsum & MC3DMASK32X) | (p & MC3DMASK32YZ)); 
    }

uint32_t ulMC3Dxminusx(uint32_t p, uint32_t q) {
    uint32_t xdif = (p & MC3DMASK32X) - (q & MC3DMASK32X);
    return ((xdif & MC3DMASK32X) | (p & MC3DMASK32YZ));
    } 

uint32_t ulMC3Dyplusy(uint32_t p, uint32_t q)  {
    uint32_t ysum = (p | MC3DMASK32XZ) + (q & MC3DMASK32Y);
    return ((ysum & MC3DMASK32Y) | (p & MC3DMASK32XZ));
    }

uint32_t ulMC3Dyminusy(uint32_t p, uint32_t q) {
    uint32_t ydif = (p & MC3DMASK32Y) - (q & MC3DMASK32Y);
    return ((ydif & MC3DMASK32Y) | (p & MC3DMASK32XZ));
    } 

uint32_t ulMC3Dzplusz(uint32_t p, uint32_t q)  {
    uint32_t zsum = (p | MC3DMASK32XY) + (q & MC3DMASK32Z);
    return ((zsum & MC3DMASK32Z) | (p & MC3DMASK32XY)); 
    }

uint32_t ulMC3Dzminusz(uint32_t p, uint32_t q) {
    uint32_t zdif = (p & MC3DMASK32Z) - (q & MC3DMASK32Z);
    return ((zdif & MC3DMASK32Z) | (p & MC3DMASK32XY));
    }

uint32_t ulMC3DplusMC(uint32_t p, uint32_t q)  {
    uint32_t xsum = (p | MC3DMASK32YZ) + (q & MC3DMASK32X);
    uint32_t ysum = (p | MC3DMASK32XZ) + (q & MC3DMASK32Y);
    uint32_t zsum = (p | MC3DMASK32XY) + (q & MC3DMASK32Z);
    return ((xsum & MC3DMASK32X) | (ysum & MC3DMASK32Y) | (zsum & MC3DMASK32Z));
    }

uint32_t ulMC3DminusMC(uint32_t p, uint32_t q) {
    uint32_t xdif = (p & MC3DMASK32X) - (q & MC3DMASK32X);
    uint32_t ydif = (p & MC3DMASK32Y) - (q & MC3DMASK32Y);
    uint32_t zdif = (p & MC3DMASK32Z) - (q & MC3DMASK32Z);
    return ((xdif & MC3DMASK32X) | (ydif & MC3DMASK32Y) | (zdif & MC3DMASK32Z));
    }
    
uint32_t ulMC3Dplusv(uint32_t p, uint32_t v)  {
    uint32_t xsum = (p | MC3DMASK32YZ) + v;
    uint32_t ysum = (p | MC3DMASK32XZ) + (v<< 1);
    uint32_t zsum = (p | MC3DMASK32XY) + (v<< 2);
    return ((xsum & MC3DMASK32X) | (ysum & MC3DMASK32Y) | (zsum & MC3DMASK32Z));
    }

uint32_t ulMC3Dminusv(uint32_t p, uint32_t v) {
    uint32_t xdif = (p & MC3DMASK32X) - v;
    uint32_t ydif = (p & MC3DMASK32Y) - (v<< 1);
    uint32_t zdif = (p & MC3DMASK32Z) - (v<< 2);
    return ((xdif & MC3DMASK32X) | (ydif & MC3DMASK32Y) | (zdif & MC3DMASK32Z));
    }

uint32_t ulMC3Dhalfx(uint32_t p)  {
    uint32_t halfx = (p & MC3DMASK32X) >> 3;
    return ((halfx) | (p & MC3DMASK32YZ)); 
    }

uint32_t ulMC3Dhalfy(uint32_t p) {
    uint32_t halfy = (p & MC3DMASK32Y) >> 3;
    return ((halfy) | (p & MC3DMASK32XZ));
    }   
    
uint32_t ulMC3Dhalfz(uint32_t p) {
    uint32_t halfz = (p & MC3DMASK32Z) >> 3;
    return ((halfz) | (p & MC3DMASK32XY));
    } 

uint32_t ulMCMC3Dminxyz(uint32_t p, uint32_t q) {
    uint32_t xp = (p & MC3DMASK32X);
    uint32_t yp = (p & MC3DMASK32Y);
    uint32_t zp = (p & MC3DMASK32Z);
    uint32_t xq = (q & MC3DMASK32X);
    uint32_t yq = (q & MC3DMASK32Y);
    uint32_t zq = (q & MC3DMASK32Z);
    return ((xp > xq) ? xq : xp) + ((yp > yq) ? yq : yp) + ((zp > zq) ? zq : zp);
    }

uint32_t ulMCMC3Dmaxxyz(uint32_t p, uint32_t q) {
    uint32_t xp = (p & MC3DMASK32X);
    uint32_t yp = (p & MC3DMASK32Y);
    uint32_t zp = (p & MC3DMASK32Z);
    uint32_t xq = (q & MC3DMASK32X);
    uint32_t yq = (q & MC3DMASK32Y);
    uint32_t zq = (q & MC3DMASK32Z);
    return ((xp < xq) ? xq : xp) + ((yp < yq) ? yq : yp) + ((zp < zq) ? zq : zp);
    }

uint32_t ulMCMC3Dmidxyz(uint32_t p, uint32_t q) {
    uint32_t xyzmin = ulMCMC3Dminxyz(p,q);
    uint32_t xyzdif = ulMC3DminusMC(ulMCMC3Dmaxxyz(p,q),xyzmin);
    
    uint32_t xyzhaf = ulMC3Dhalfx(xyzdif);
    xyzhaf = ulMC3Dhalfy(xyzhaf);
    xyzhaf = ulMC3Dhalfz(xyzhaf);

    return ulMC3DplusMC(xyzmin,xyzhaf); 
    }

uint32_t ulMC3Dxplusv_o(uint32_t p, uint32_t v)  {
    uint32_t xsum = ((p | MC3DMASK32YZ) + v) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? ((xsum - MC3D32MAXX) & MC3DMASK32X) : 0); 
    }

uint32_t ulMC3Dxminusv_o(uint32_t p, uint32_t v) {
    uint32_t mp = (p & MC3DMASK32X);
    return ((v > mp) ? ((v - mp) & MC3DMASK32X) : 0); 
    }

uint32_t ulMC3Dyplusv_o(uint32_t p, uint32_t v)  {
    uint32_t yasx = ((p & MC3DMASK32Y)>> 1);
    uint32_t xsum = ((yasx | MC3DMASK32YZ) + v) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? (((xsum - MC3D32MAXX)<< 1) & MC3DMASK32Y) : 0); 
    }
    
uint32_t ulMC3Dyminusv_o(uint32_t p, uint32_t v) {
    uint32_t mp = (p & MC3DMASK32Y);
    uint32_t vy = v << 1;
    return ((vy > mp) ? ((vy - mp) & MC3DMASK32Y) : 0); 
    }

uint32_t ulMC3Dzplusv_o(uint32_t p, uint32_t v)  {
    uint32_t zasx = ((p & MC3DMASK32Z)>> 2);
    uint32_t xsum = ((zasx | MC3DMASK32YZ) + v) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? (((xsum - MC3D32MAXX)<< 2) & MC3DMASK32Z) : 0); 
    }

uint32_t ulMC3Dzminusv_o(uint32_t p, uint32_t v) {
    uint32_t mp = (p & MC3DMASK32Z);
    uint32_t vz = v << 2;
    return ((vz > mp) ? ((vz - mp) & MC3DMASK32Z) : 0); 
    }

uint32_t ulMC3Dxplusx_o(uint32_t p, uint32_t q)  {
    uint32_t xsum = ((p | MC3DMASK32YZ) + (q & MC3DMASK32X)) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? ((xsum - MC3D32MAXX) & MC3DMASK32X) : 0); 
    }  
  
uint32_t ulMC3Dxminusx_o(uint32_t p, uint32_t q) {
    uint32_t mp = (p & MC3DMASK32X);
    uint32_t mq = (q & MC3DMASK32X);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK32X) : 0); 
    }

uint32_t ulMC3Dyplusy_o(uint32_t p, uint32_t q)  {
    uint32_t rx = ((p & MC3DMASK32Y)>> 1);
    uint32_t sx = ((q & MC3DMASK32Y)>> 1);
    uint32_t xsum = ((rx | MC3DMASK32YZ) + (sx & MC3DMASK32X)) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? (((xsum - MC3D32MAXX) & MC3DMASK32X)<< 1) : 0); 
    }  

uint32_t ulMC3Dyminusy_o(uint32_t p, uint32_t q) {
    uint32_t mp = (p & MC3DMASK32Y);
    uint32_t mq = (q & MC3DMASK32Y);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK32Y) : 0); 
    }
    
uint32_t ulMC3Dzplusz_o(uint32_t p, uint32_t q)  {
    uint32_t rx = ((p & MC3DMASK32Z)>> 2);
    uint32_t sx = ((q & MC3DMASK32Z)>> 2);
    uint32_t xsum = ((rx | MC3DMASK32YZ) + (sx & MC3DMASK32X)) & MC3DMASK32X;
    return ((xsum > MC3D32MAXX) ? (((xsum - MC3D32MAXX) & MC3DMASK32X)<< 2) : 0); 
    }
    
uint32_t ulMC3Dzminusz_o(uint32_t p, uint32_t q) {
    uint32_t mp = (p & MC3DMASK32Z);
    uint32_t mq = (q & MC3DMASK32Z);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK32Z) : 0); 
    }

uint32_t ulMC3DplusMC_o(uint32_t p, uint32_t q) {
    uint32_t xo = ulMC3Dxplusx_o(p,q);
    uint32_t yo = ulMC3Dyplusy_o(p,q);
    uint32_t zo = ulMC3Dzplusz_o(p,q);
    return ((xo & MC3DMASK32X) | (yo & MC3DMASK32Y) | (zo & MC3DMASK32Z));
    }
    
uint32_t ulMC3DminusMC_o(uint32_t p, uint32_t q) {
    uint32_t xo = ulMC3Dxminusx_o(p,q);
    uint32_t yo = ulMC3Dyminusy_o(p,q);
    uint32_t zo = ulMC3Dzminusz_o(p,q);
    return ((xo & MC3DMASK32X) | (yo & MC3DMASK32Y) | (zo & MC3DMASK32Z));
    }

uint32_t ulMC3Dplusv_o(uint32_t p, uint32_t v) {
    uint32_t xo = ulMC3Dxplusv_o(p,v);
    uint32_t yo = ulMC3Dyplusv_o(p,v);
    uint32_t zo = ulMC3Dzplusv_o(p,v);
    return ((xo & MC3DMASK32X) | (yo & MC3DMASK32Y) | (zo & MC3DMASK32Z));
    } 
    
uint32_t ulMC3Dminusv_o(uint32_t p, uint32_t v) {
    uint32_t xo = ulMC3Dxminusv_o(p,v);
    uint32_t yo = ulMC3Dyminusv_o(p,v);
    uint32_t zo = ulMC3Dzminusv_o(p,v);
    return ((xo & MC3DMASK32X) | (yo & MC3DMASK32Y) | (zo & MC3DMASK32Z));
    } 


#endif

/*
#include <stdio.h>

int main() {

    uint16_t ax=600, ay=500, az=400, bx=300, by=200, bz=100, m = 451;
    
    uint32_t ae = ulMC3Dencode(ax,ay,az);
    uint32_t be = ulMC3Dencode(bx,by,bz);

    printf("X: %u | Y: %u | Z: %u\n", ulMC3DdecodeX(ae),ulMC3DdecodeY(ae),ulMC3DdecodeZ(ae));
    printf("X: %u | Y: %u | Z: %u\n", ulMC3DdecodeX(be),ulMC3DdecodeY(be),ulMC3DdecodeZ(be));

    uint32_t mp = ulMCMC3Dmidxyz(ae,be); 
    printf("mid- X: %u  | Y: %u | Z: %u\n", ulMC3DdecodeX(mp),ulMC3DdecodeY(mp),ulMC3DdecodeZ(mp));

    uint32_t mx = ulMC3Dminusv_o(be,ulMC3Dspread((uint32_t)m));
    printf("v_o- X: %u  | Y: %u | Z: %u\n", ulMC3DdecodeX(mx),ulMC3DdecodeY(mx),ulMC3DdecodeZ(mx));

    return 0;
    }
*/
