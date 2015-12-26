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

#ifndef MZC3D64_H_
#define MZC3D64_H_

/* unsigned long long x,y,z Morton Z code encoding/decoding/manipulation */

#include <limits.h>
/* c header for uintXX_t */
#include <inttypes.h>

/* Morton Code bitMasks - beats looking at all the numbers
   64/3: only the first 21 bits are used */

#define MC3DMASK64X   0x1249249249249249
#define MC3DMASK64Y   0x2492492492492492
#define MC3DMASK64Z   0x4924924924924924

#define MC3DMASK64XY  (MC3DMASK64X | MC3DMASK64Y)
#define MC3DMASK64XZ  (MC3DMASK64X | MC3DMASK64Z)
#define MC3DMASK64YZ  (MC3DMASK64Y | MC3DMASK64Z)

/* ullMC3Dspread(2097151) - max for 21 bits */
#define MC3D64MAXX    1317624576693539401 

/* C++ crowd seems to hate defines: leave out #include <inttypes.h> 
#include <stdint.h>

const uint64_t MC3DMASK64X = 0x1249249249249249; 
const uint64_t MC3DMASK64Y = 0x2492492492492492; 
const uint64_t MC3DMASK64Z = 0x4924924924924924; 

const uint64_t MC3DMASK64XY = (MC3DMASK64X | MC3DMASK64Y);
const uint64_t MC3DMASK64XZ = (MC3DMASK64X | MC3DMASK64Z);
const uint64_t MC3DMASK64YZ = (MC3DMASK64Y | MC3DMASK64Z);

const uint64_t MC3D64MAXX = 1317624576693539401;
*/

/* Morton codes - Thanks to -
fgiesen.wordpress.com/2009/12/13/decoding-morton-codes/
www.forceflow.be/2013/10/07/morton-encodingdecoding-through-bit-interleaving-implementations/
gist.github.com/aavenel/a5349516aa33b7499eef */

/* push everything apart to make space - only the first 21 bits are used */
uint64_t ullMC3Dspread(uint64_t);

/* inverse of spread */
uint32_t ullMC3Dcompact(uint64_t);

/* put x,y,z coordinates into Morton code form */
uint64_t ullMC3Dencode(uint32_t, uint32_t, uint32_t);

/* get the original x / y / z coordinate from the Morton code */
uint32_t ullMC3DdecodeX(uint64_t);
uint32_t ullMC3DdecodeY(uint64_t);
uint32_t ullMC3DdecodeZ(uint64_t);

/* get the spread x / y / z coordinate from the Morton code */
uint64_t ullMC3DgetX(uint64_t);
uint64_t ullMC3DgetY(uint64_t);
uint64_t ullMC3DgetZ(uint64_t);

/* Tesseral arithmetic  - Thanks to -
   asgerhoedt.dk/?p=276
   cgi.csc.liv.ac.uk/~frans/OldResearch/dGKBIS/tesseral.html
   bitmath.blogspot.my/search?q=tesseral */

/* individual coordinates of two Morton codes */
uint64_t ullMC3Dxplusx(uint64_t, uint64_t);
uint64_t ullMC3Dxminusx(uint64_t, uint64_t);

uint64_t ullMC3Dyplusy(uint64_t, uint64_t);
uint64_t ullMC3Dyminusy(uint64_t, uint64_t);

uint64_t ullMC3Dzplusz(uint64_t, uint64_t);
uint64_t ullMC3Dzminusz(uint64_t, uint64_t);

/* all coordinates of two Morton codes */
uint64_t ullMC3DplusMC(uint64_t, uint64_t);
uint64_t ullMC3DminusMC(uint64_t, uint64_t);

/* coordinate +/- any number: first argument is a morton code, second is spread(v) 
   or to simply increment/decrement, pass 1 without spread() as the second argument */
uint64_t ullMC3Dxplusv(uint64_t, uint64_t);
uint64_t ullMC3Dxminusv(uint64_t, uint64_t);

uint64_t ullMC3Dyplusv(uint64_t, uint64_t);
uint64_t ullMC3Dyminusv(uint64_t, uint64_t);

uint64_t ullMC3Dzplusv(uint64_t, uint64_t);
uint64_t ullMC3Dzminusv(uint64_t, uint64_t);

/* all coordinates */
uint64_t ullMC3Dplusv(uint64_t, uint64_t);
uint64_t ullMC3Dminusv(uint64_t, uint64_t);

/* coordinate divided by 2 */
uint64_t ullMC3Dhalfx(uint64_t);
uint64_t ullMC3Dhalfy(uint64_t);
uint64_t ullMC3Dhalfz(uint64_t);

/* element-wise min/max - diagonal corners of a box */
uint64_t ullMCMC3Dminxyz(uint64_t, uint64_t);
uint64_t ullMCMC3Dmaxxyz(uint64_t, uint64_t); 
/* center of element-wise min/max */ 
uint64_t ullMCMC3Dmidxyz(uint64_t, uint64_t);

/* (these ? zero : amount_out_of_bounds) as the designated coordinate */
uint64_t ullMC3Dxplusx_o(uint64_t, uint64_t);
uint64_t ullMC3Dxminusx_o(uint64_t, uint64_t);

uint64_t ullMC3Dyplusy_o(uint64_t, uint64_t);
uint64_t ullMC3Dyminusy_o(uint64_t, uint64_t);

uint64_t ullMC3Dzplusz_o(uint64_t, uint64_t);
uint64_t ullMC3Dzminusz_o(uint64_t, uint64_t);

uint64_t ullMC3DplusMC_o(uint64_t, uint64_t);
uint64_t ullMC3DminusMC_o(uint64_t, uint64_t);

/* use spread(v) as second argument, first is a morton code */
uint64_t ullMC3Dxplusv_o(uint64_t, uint64_t);
uint64_t ullMC3Dxminusv_o(uint64_t, uint64_t);

uint64_t ullMC3Dyplusv_o(uint64_t, uint64_t);
uint64_t ullMC3Dyminusv_o(uint64_t, uint64_t);

uint64_t ullMC3Dzplusv_o(uint64_t, uint64_t);
uint64_t ullMC3Dzminusv_o(uint64_t, uint64_t);

uint64_t ullMC3Dplusv_o(uint64_t, uint64_t);
uint64_t ullMC3Dminusv_o(uint64_t, uint64_t);


/* Morton codes */
uint64_t ullMC3Dspread(uint64_t w)  {
    w &=                0x00000000001fffff; 
    w = (w | w << 32) & 0x001f00000000ffff;  
    w = (w | w << 16) & 0x001f0000ff0000ff;  
    w = (w | w <<  8) & 0x010f00f00f00f00f; 
    w = (w | w <<  4) & 0x10c30c30c30c30c3; 
    w = (w | w <<  2) & 0x1249249249249249;
    return w;
    } 

/* inverse of Spread */
uint32_t ullMC3Dcompact(uint64_t w) {
    w &=                  0x1249249249249249;
    w = (w ^ (w >> 2))  & 0x30c30c30c30c30c3;
    w = (w ^ (w >> 4))  & 0xf00f00f00f00f00f;
    w = (w ^ (w >> 8))  & 0x00ff0000ff0000ff;
    w = (w ^ (w >> 16)) & 0x00ff00000000ffff;
    w = (w ^ (w >> 32)) & 0x00000000001fffff;
    return (uint32_t)w;
    }

uint64_t ullMC3Dencode(uint32_t x, uint32_t y, uint32_t z)  {
   return ((ullMC3Dspread((uint64_t)x)) | (ullMC3Dspread((uint64_t)y) << 1) | (ullMC3Dspread((uint64_t)z) << 2));
   }

uint32_t ullMC3DdecodeX(uint64_t code) {
    return ullMC3Dcompact(code);
    }
    
uint32_t ullMC3DdecodeY(uint64_t code) {
    return ullMC3Dcompact(code >> 1);    
    }

uint32_t ullMC3DdecodeZ(uint64_t code) {
    return ullMC3Dcompact(code >> 2);    
    }

uint64_t ullMC3DgetX(uint64_t code) {
    return (code & MC3DMASK64X);    
    }
    
uint64_t ullMC3DgetY(uint64_t code) {
    return (code & MC3DMASK64Y);    
    }
    
uint64_t ullMC3DgetZ(uint64_t code) {
    return (code & MC3DMASK64Z);    
    }
    
/* Tesseral arithmetic */
uint64_t ullMC3Dxplusv(uint64_t p, uint64_t v)  {
    uint64_t xsum = (p | MC3DMASK64YZ) + v;
    return ((xsum & MC3DMASK64X) | (p & MC3DMASK64YZ)); 
    }

uint64_t ullMC3Dxminusv(uint64_t p, uint64_t v) {
    uint64_t xdif = (p & MC3DMASK64X) - v;
    return ((xdif & MC3DMASK64X) | (p & MC3DMASK64YZ));
    }

uint64_t ullMC3Dyplusv(uint64_t p, uint64_t v)  {
    uint64_t ysum = (p | MC3DMASK64XZ) + (v<< 1);
    return ((ysum & MC3DMASK64Y) | (p & MC3DMASK64XZ)); 
    }

uint64_t ullMC3Dyminusv(uint64_t p, uint64_t v) {
    uint64_t ydif = (p & MC3DMASK64Y) - (v<< 1);
    return ((ydif & MC3DMASK64Y) | (p & MC3DMASK64XZ));
    }

uint64_t ullMC3Dzplusv(uint64_t p, uint64_t v)  {
    uint64_t zsum = (p | MC3DMASK64XY) + (v<< 2);
    return ((zsum & MC3DMASK64Z) | (p & MC3DMASK64XY)); 
    }

uint64_t ullMC3Dzminusv(uint64_t p, uint64_t v) {
    uint64_t zdif = (p & MC3DMASK64Z) - (v<< 2);
    return ((zdif & MC3DMASK64Z) | (p & MC3DMASK64XY));
    }

uint64_t ullMC3Dxplusx(uint64_t p, uint64_t q)  {
    uint64_t xsum = (p | MC3DMASK64YZ) + (q & MC3DMASK64X);
    return ((xsum & MC3DMASK64X) | (p & MC3DMASK64YZ)); 
    }

uint64_t ullMC3Dxminusx(uint64_t p, uint64_t q) {
    uint64_t xdif = (p & MC3DMASK64X) - (q & MC3DMASK64X);
    return ((xdif & MC3DMASK64X) | (p & MC3DMASK64YZ));
    } 

uint64_t ullMC3Dyplusy(uint64_t p, uint64_t q)  {
    uint64_t ysum = (p | MC3DMASK64XZ) + (q & MC3DMASK64Y);
    return ((ysum & MC3DMASK64Y) | (p & MC3DMASK64XZ));
    }

uint64_t ullMC3Dyminusy(uint64_t p, uint64_t q) {
    uint64_t ydif = (p & MC3DMASK64Y) - (q & MC3DMASK64Y);
    return ((ydif & MC3DMASK64Y) | (p & MC3DMASK64XZ));
    } 

uint64_t ullMC3Dzplusz(uint64_t p, uint64_t q)  {
    uint64_t zsum = (p | MC3DMASK64XY) + (q & MC3DMASK64Z);
    return ((zsum & MC3DMASK64Z) | (p & MC3DMASK64XY)); 
    }

uint64_t ullMC3Dzminusz(uint64_t p, uint64_t q) {
    uint64_t zdif = (p & MC3DMASK64Z) - (q & MC3DMASK64Z);
    return ((zdif & MC3DMASK64Z) | (p & MC3DMASK64XY));
    }

uint64_t ullMC3DplusMC(uint64_t p, uint64_t q)  {
    uint64_t xsum = (p | MC3DMASK64YZ) + (q & MC3DMASK64X);
    uint64_t ysum = (p | MC3DMASK64XZ) + (q & MC3DMASK64Y);
    uint64_t zsum = (p | MC3DMASK64XY) + (q & MC3DMASK64Z);
    return ((xsum & MC3DMASK64X) | (ysum & MC3DMASK64Y) | (zsum & MC3DMASK64Z));
    }

uint64_t ullMC3DminusMC(uint64_t p, uint64_t q) {
    uint64_t xdif = (p & MC3DMASK64X) - (q & MC3DMASK64X);
    uint64_t ydif = (p & MC3DMASK64Y) - (q & MC3DMASK64Y);
    uint64_t zdif = (p & MC3DMASK64Z) - (q & MC3DMASK64Z);
    return ((xdif & MC3DMASK64X) | (ydif & MC3DMASK64Y) | (zdif & MC3DMASK64Z));
    }
    
uint64_t ullMC3Dplusv(uint64_t p, uint64_t v)  {
    uint64_t xsum = (p | MC3DMASK64YZ) + v;
    uint64_t ysum = (p | MC3DMASK64XZ) + (v<< 1);
    uint64_t zsum = (p | MC3DMASK64XY) + (v<< 2);
    return ((xsum & MC3DMASK64X) | (ysum & MC3DMASK64Y) | (zsum & MC3DMASK64Z));
    }

uint64_t ullMC3Dminusv(uint64_t p, uint64_t v) {
    uint64_t xdif = (p & MC3DMASK64X) - v;
    uint64_t ydif = (p & MC3DMASK64Y) - (v<< 1);
    uint64_t zdif = (p & MC3DMASK64Z) - (v<< 2);
    return ((xdif & MC3DMASK64X) | (ydif & MC3DMASK64Y) | (zdif & MC3DMASK64Z));
    }

uint64_t ullMC3Dhalfx(uint64_t p)  {
    uint64_t halfx = (p & MC3DMASK64X) >> 3;
    return ((halfx) | (p & MC3DMASK64YZ)); 
    }

uint64_t ullMC3Dhalfy(uint64_t p) {
    uint64_t halfy = (p & MC3DMASK64Y) >> 3;
    return ((halfy) | (p & MC3DMASK64XZ));
    }   
    
uint64_t ullMC3Dhalfz(uint64_t p) {
    uint64_t halfz = (p & MC3DMASK64Z) >> 3;
    return ((halfz) | (p & MC3DMASK64XY));
    } 

uint64_t ullMCMC3Dminxyz(uint64_t p, uint64_t q) {
    uint64_t xp = (p & MC3DMASK64X);
    uint64_t yp = (p & MC3DMASK64Y);
    uint64_t zp = (p & MC3DMASK64Z);
    uint64_t xq = (q & MC3DMASK64X);
    uint64_t yq = (q & MC3DMASK64Y);
    uint64_t zq = (q & MC3DMASK64Z);
    return ((xp > xq) ? xq : xp) + ((yp > yq) ? yq : yp) + ((zp > zq) ? zq : zp);
    }

uint64_t ullMCMC3Dmaxxyz(uint64_t p, uint64_t q) {
    uint64_t xp = (p & MC3DMASK64X);
    uint64_t yp = (p & MC3DMASK64Y);
    uint64_t zp = (p & MC3DMASK64Z);
    uint64_t xq = (q & MC3DMASK64X);
    uint64_t yq = (q & MC3DMASK64Y);
    uint64_t zq = (q & MC3DMASK64Z);
    return ((xp < xq) ? xq : xp) + ((yp < yq) ? yq : yp) + ((zp < zq) ? zq : zp);
    }

uint64_t ullMCMC3Dmidxyz(uint64_t p, uint64_t q) {
    uint64_t xyzmin = ullMCMC3Dminxyz(p,q);
    uint64_t xyzdif = ullMC3DminusMC(ullMCMC3Dmaxxyz(p,q),xyzmin);
    
    uint64_t xyzhaf = ullMC3Dhalfx(xyzdif);
    xyzhaf = ullMC3Dhalfy(xyzhaf);
    xyzhaf = ullMC3Dhalfz(xyzhaf);

    return ullMC3DplusMC(xyzmin,xyzhaf); 
    }

uint64_t ullMC3Dxplusv_o(uint64_t p, uint64_t v)  {
    uint64_t xsum = ((p | MC3DMASK64YZ) + v) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? ((xsum - MC3D64MAXX) & MC3DMASK64X) : 0); 
    }

uint64_t ullMC3Dxminusv_o(uint64_t p, uint64_t v) {
    uint64_t mp = (p & MC3DMASK64X);
    return ((v > mp) ? ((v - mp) & MC3DMASK64X) : 0); 
    }

uint64_t ullMC3Dyplusv_o(uint64_t p, uint64_t v)  {
    uint64_t yasx = ((p & MC3DMASK64Y)>> 1);
    uint64_t xsum = ((yasx | MC3DMASK64YZ) + v) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? (((xsum - MC3D64MAXX)<< 1) & MC3DMASK64Y) : 0); 
    }
    
uint64_t ullMC3Dyminusv_o(uint64_t p, uint64_t v) {
    uint64_t mp = (p & MC3DMASK64Y);
    uint64_t vy = v << 1;
    return ((vy > mp) ? ((vy - mp) & MC3DMASK64Y) : 0); 
    }

uint64_t ullMC3Dzplusv_o(uint64_t p, uint64_t v)  {
    uint64_t zasx = ((p & MC3DMASK64Z)>> 2);
    uint64_t xsum = ((zasx | MC3DMASK64YZ) + v) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? (((xsum - MC3D64MAXX)<< 2) & MC3DMASK64Z) : 0); 
    }

uint64_t ullMC3Dzminusv_o(uint64_t p, uint64_t v) {
    uint64_t mp = (p & MC3DMASK64Z);
    uint64_t vz = v << 2;
    return ((vz > mp) ? ((vz - mp) & MC3DMASK64Z) : 0); 
    }

uint64_t ullMC3Dxplusx_o(uint64_t p, uint64_t q)  {
    uint64_t xsum = ((p | MC3DMASK64YZ) + (q & MC3DMASK64X)) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? ((xsum - MC3D64MAXX) & MC3DMASK64X) : 0); 
    }  
  
uint64_t ullMC3Dxminusx_o(uint64_t p, uint64_t q) {
    uint64_t mp = (p & MC3DMASK64X);
    uint64_t mq = (q & MC3DMASK64X);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK64X) : 0); 
    }

uint64_t ullMC3Dyplusy_o(uint64_t p, uint64_t q)  {
    uint64_t rx = ((p & MC3DMASK64Y)>> 1);
    uint64_t sx = ((q & MC3DMASK64Y)>> 1);
    uint64_t xsum = ((rx | MC3DMASK64YZ) + (sx & MC3DMASK64X)) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? (((xsum - MC3D64MAXX) & MC3DMASK64X)<< 1) : 0); 
    }  

uint64_t ullMC3Dyminusy_o(uint64_t p, uint64_t q) {
    uint64_t mp = (p & MC3DMASK64Y);
    uint64_t mq = (q & MC3DMASK64Y);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK64Y) : 0); 
    }
    
uint64_t ullMC3Dzplusz_o(uint64_t p, uint64_t q)  {
    uint64_t rx = ((p & MC3DMASK64Z)>> 2);
    uint64_t sx = ((q & MC3DMASK64Z)>> 2);
    uint64_t xsum = ((rx | MC3DMASK64YZ) + (sx & MC3DMASK64X)) & MC3DMASK64X;
    return ((xsum > MC3D64MAXX) ? (((xsum - MC3D64MAXX) & MC3DMASK64X)<< 2) : 0); 
    }
    
uint64_t ullMC3Dzminusz_o(uint64_t p, uint64_t q) {
    uint64_t mp = (p & MC3DMASK64Z);
    uint64_t mq = (q & MC3DMASK64Z);
    return ((mq > mp) ? ((mq - mp) & MC3DMASK64Z) : 0); 
    }

uint64_t ullMC3DplusMC_o(uint64_t p, uint64_t q) {
    uint64_t xo = ullMC3Dxplusx_o(p,q);
    uint64_t yo = ullMC3Dyplusy_o(p,q);
    uint64_t zo = ullMC3Dzplusz_o(p,q);
    return ((xo & MC3DMASK64X) | (yo & MC3DMASK64Y) | (zo & MC3DMASK64Z));
    }
    
uint64_t ullMC3DminusMC_o(uint64_t p, uint64_t q) {
    uint64_t xo = ullMC3Dxminusx_o(p,q);
    uint64_t yo = ullMC3Dyminusy_o(p,q);
    uint64_t zo = ullMC3Dzminusz_o(p,q);
    return ((xo & MC3DMASK64X) | (yo & MC3DMASK64Y) | (zo & MC3DMASK64Z));
    }

uint64_t ullMC3Dplusv_o(uint64_t p, uint64_t v) {
    uint64_t xo = ullMC3Dxplusv_o(p,v);
    uint64_t yo = ullMC3Dyplusv_o(p,v);
    uint64_t zo = ullMC3Dzplusv_o(p,v);
    return ((xo & MC3DMASK64X) | (yo & MC3DMASK64Y) | (zo & MC3DMASK64Z));
    } 
    
uint64_t ullMC3Dminusv_o(uint64_t p, uint64_t v) {
    uint64_t xo = ullMC3Dxminusv_o(p,v);
    uint64_t yo = ullMC3Dyminusv_o(p,v);
    uint64_t zo = ullMC3Dzminusv_o(p,v);
    return ((xo & MC3DMASK64X) | (yo & MC3DMASK64Y) | (zo & MC3DMASK64Z));
    } 


#endif

/*
#include <stdio.h>

int main() {

    uint32_t ax=600, ay=500, az=400, bx=300, by=200, bz=100, m = 451;
    
    uint64_t ae = ullMC3Dencode(ax,ay,az);
    uint64_t be = ullMC3Dencode(bx,by,bz);

    printf("X: %u | Y: %u | Z: %u\n", ullMC3DdecodeX(ae),ullMC3DdecodeY(ae),ullMC3DdecodeZ(ae));
    printf("X: %u | Y: %u | Z: %u\n", ullMC3DdecodeX(be),ullMC3DdecodeY(be),ullMC3DdecodeZ(be));

    uint64_t mp = ullMCMC3Dmidxyz(ae,be); 
    printf("mid- X: %u  | Y: %u | Z: %u\n", ullMC3DdecodeX(mp),ullMC3DdecodeY(mp),ullMC3DdecodeZ(mp));

    uint64_t mx = ullMC3Dminusv_o(be,ullMC3Dspread((uint64_t)m));
    printf("v_o- X: %u  | Y: %u | Z: %u\n", ullMC3DdecodeX(mx),ullMC3DdecodeY(mx),ullMC3DdecodeZ(mx));
    
    return 0;
    }
*/
