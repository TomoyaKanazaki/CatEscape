xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 44;
 2.50605;-0.02426;-107.09179;,
 2.50605;0.52935;-107.09179;,
 -0.58181;0.52935;-114.74072;,
 -0.58181;-0.02426;-114.74072;,
 0.32817;0.52935;-93.23397;,
 0.32817;-0.02426;-93.23397;,
 0.80389;0.52935;-79.27309;,
 0.80389;-0.02426;-79.27309;,
 0.91491;0.52935;-65.32639;,
 0.91491;-0.02426;-65.32639;,
 0.65618;0.52935;-51.39404;,
 0.65618;-0.02426;-51.39404;,
 0.11551;0.52935;-37.47264;,
 0.11551;-0.02426;-37.47264;,
 -0.70660;0.52935;-16.30506;,
 -0.70660;-0.02426;-16.30506;,
 -4.21847;4.36178;-16.39906;,
 -4.21847;-3.85670;-16.39906;,
 -4.29913;4.36178;-14.32265;,
 -4.29913;-3.85670;-14.32265;,
 -0.97806;1.62601;-14.05869;,
 -0.97806;-1.12094;-14.05869;,
 -1.81445;1.62601;7.47656;,
 -1.81445;-1.12094;7.47656;,
 1.52544;1.62601;7.60627;,
 1.52544;-1.12094;7.60627;,
 2.36181;1.62601;-13.92873;,
 2.36181;-1.12094;-13.92873;,
 5.69334;4.36178;-13.93456;,
 5.69334;-3.85670;-13.93456;,
 5.77399;4.36178;-16.01097;,
 5.77399;-3.85670;-16.01097;,
 2.67324;0.52935;-16.17380;,
 2.67324;-0.02426;-16.17380;,
 3.49536;0.52935;-37.34137;,
 3.49536;-0.02426;-37.34137;,
 4.03603;0.52935;-51.26277;,
 4.03603;-0.02426;-51.26277;,
 4.29476;0.52935;-65.19512;,
 4.29476;-0.02426;-65.19512;,
 4.18373;0.52935;-79.14182;,
 4.18373;-0.02426;-79.14182;,
 3.70802;0.52935;-93.10269;,
 3.70802;-0.02426;-93.10269;;
 
 42;
 4;3,2,1,0;,
 4;5,4,2,3;,
 4;7,6,4,5;,
 4;9,8,6,7;,
 4;11,10,8,9;,
 4;13,12,10,11;,
 4;15,14,12,13;,
 4;17,16,14,15;,
 4;19,18,16,17;,
 4;21,20,18,19;,
 4;23,22,20,21;,
 4;25,24,22,23;,
 4;27,26,24,25;,
 4;29,28,26,27;,
 4;31,30,28,29;,
 4;33,32,30,31;,
 4;35,34,32,33;,
 4;37,36,34,35;,
 4;39,38,36,37;,
 4;41,40,38,39;,
 4;43,42,40,41;,
 4;0,1,42,43;,
 4;20,22,24,26;,
 4;18,20,26,28;,
 4;16,18,28,30;,
 4;14,16,30,32;,
 4;12,14,32,34;,
 4;10,12,34,36;,
 4;8,10,36,38;,
 4;6,8,38,40;,
 4;4,6,40,42;,
 4;2,4,42,1;,
 4;23,21,27,25;,
 4;21,19,29,27;,
 4;19,17,31,29;,
 4;17,15,33,31;,
 4;15,13,35,33;,
 4;13,11,37,35;,
 4;11,9,39,37;,
 4;9,7,41,39;,
 4;7,5,43,41;,
 4;5,3,0,43;;
 
 MeshMaterialList {
  1;
  42;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV_BOSS.jpg";
   }
  }
 }
 MeshNormals {
  30;
  0.972584;0.000000;-0.232552;,
  0.927290;0.000000;-0.374345;,
  -0.999271;0.000000;0.038165;,
  -0.999779;0.000000;0.021010;,
  -0.999986;0.000000;-0.005304;,
  -0.999588;0.000000;-0.028689;,
  -0.999247;0.000000;-0.038808;,
  -0.999247;0.000000;-0.038809;,
  0.032782;-0.005528;-0.999447;,
  0.032782;0.005527;-0.999447;,
  -0.999246;0.000000;-0.038817;,
  -0.059044;-0.024677;0.997950;,
  -0.059044;0.024677;0.997950;,
  -0.999247;0.000000;-0.038809;,
  -0.038807;0.000000;0.999247;,
  0.999247;0.000000;0.038808;,
  -0.018534;-0.024677;0.999524;,
  -0.018534;0.024677;0.999524;,
  0.999247;0.000000;0.038812;,
  0.045625;-0.005528;-0.998943;,
  0.045625;0.005527;-0.998943;,
  0.999247;0.000000;0.038809;,
  0.999588;0.000000;0.028689;,
  0.999986;0.000000;0.005304;,
  0.999779;0.000000;-0.021010;,
  0.998207;0.000000;-0.059851;,
  -0.999106;0.000000;0.042274;,
  0.999247;0.000000;0.038809;,
  0.000000;1.000000;0.000000;,
  0.000000;-1.000000;0.000000;;
  42;
  4;1,1,0,0;,
  4;2,2,26,26;,
  4;3,3,2,2;,
  4;4,4,3,3;,
  4;5,5,4,4;,
  4;6,6,5,5;,
  4;7,7,6,6;,
  4;8,9,9,8;,
  4;10,10,10,10;,
  4;11,12,12,11;,
  4;13,13,13,13;,
  4;14,14,14,14;,
  4;15,15,15,15;,
  4;16,17,17,16;,
  4;18,18,18,18;,
  4;19,20,20,19;,
  4;21,21,27,27;,
  4;22,22,21,21;,
  4;23,23,22,22;,
  4;24,24,23,23;,
  4;25,25,24,24;,
  4;0,0,25,25;,
  4;28,28,28,28;,
  4;12,12,17,17;,
  4;28,28,28,28;,
  4;9,9,20,20;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;28,28,28,28;,
  4;29,29,29,29;,
  4;11,11,16,16;,
  4;29,29,29,29;,
  4;8,8,19,19;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;,
  4;29,29,29,29;;
 }
 MeshTextureCoords {
  44;
  0.908233;0.097167;,
  0.908233;0.097167;,
  0.932022;0.038662;,
  0.932022;0.038662;,
  0.928170;0.199176;,
  0.928170;0.199176;,
  0.926602;0.303313;,
  0.926602;0.303313;,
  0.927990;0.407158;,
  0.927990;0.407158;,
  0.932374;0.510706;,
  0.932374;0.510706;,
  0.939043;0.614028;,
  0.939043;0.614028;,
  0.949183;0.771130;,
  0.949183;0.771130;,
  0.977649;0.768628;,
  0.977649;0.768628;,
  0.978644;0.784039;,
  0.978644;0.784039;,
  0.951753;0.787707;,
  0.951753;0.787707;,
  0.962069;0.947538;,
  0.962069;0.947538;,
  0.935004;0.950217;,
  0.935004;0.950217;,
  0.924688;0.790388;,
  0.924688;0.790388;,
  0.897667;0.792054;,
  0.897667;0.792054;,
  0.896673;0.776643;,
  0.896673;0.776643;,
  0.921793;0.773841;,
  0.921793;0.773841;,
  0.911653;0.616739;,
  0.911653;0.616739;,
  0.904984;0.513417;,
  0.904984;0.513417;,
  0.900600;0.409869;,
  0.900600;0.409869;,
  0.899213;0.306024;,
  0.899213;0.306024;,
  0.900780;0.201887;,
  0.900780;0.201887;;
 }
}
