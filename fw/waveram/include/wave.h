// Eleonora Chacon Taylor
// wavetable data 

#define N 512        // number of samples per wave

short int wave[N] =
{
0xaa6c,
0xbf69,
0x9f66,
0x6863,
0x3760,
0x235d,
0x3c5a,
0x8757,
0x0355,
0xa352,
0x5d50,
0x224e,
0xe84b,
0xaa49,
0x6947,
0x2945,
0xf042,
0xc440,
0xa93e,
0xa23c,
0xaa3a,
0xbe38,
0xd936,
0xf434,
0x0e33,
0x2531,
0x3d2f,
0x582d,
0x7b2b,
0xa829,
0xe127,
0x2526,
0x7024,
0xc022,
0x1221,
0x621f,
0xb11d,
0xff1b,
0x501a,
0xa618,
0x0317,
0x6815,
0xd613,
0x4a12,
0xc210,
0x3b0f,
0xb40d,
0x2b0c,
0xa20a,
0x1a09,
0x9607,
0x1806,
0xa104,
0x3003,
0xc401,
0x5c00,
0xf6fe,
0x8efd,
0x26fc,
0xbdfa,
0x56f9,
0xf1f7,
0x91f6,
0x36f5,
0xe2f3,
0x92f2,
0x45f1,
0xf9ef,
0xadee,
0x61ed,
0x14ec,
0xc7ea,
0x7de9,
0x37e8,
0xf6e6,
0xb9e5,
0x82e4,
0x4de3,
0x19e2,
0xe6e0,
0xb2df,
0x7dde,
0x49dd,
0x16dc,
0xe7da,
0xbcd9,
0x96d8,
0x75d7,
0x56d6,
0x38d5,
0x1bd4,
0xfdd2,
0xded1,
0xc0d0,
0xa3cf,
0x89ce,
0x73cd,
0x62cc,
0x55cb,
0x4aca,
0x41c9,
0x38c8,
0x2fc7,
0x25c6,
0x1cc5,
0x13c4,
0x0dc3,
0x0bc2,
0x0dc1,
0x13c0,
0x1cbf,
0x27be,
0x32bd,
0x3cbc,
0x46bb,
0x50ba,
0x5bb9,
0x69b8,
0x79b7,
0x8eb6,
0xa7b5,
0xc3b4,
0xe1b3,
0xffb2,
0x1db2,
0x3ab1,
0x57b0,
0x75af,
0x95ae,
0xb9ad,
0xe0ac,
0x0cac,
0x3bab,
0x6baa,
0x9ca9,
0xcda8,
0xfea7,
0x2ea7,
0x5fa6,
0x92a5,
0xc8a4,
0x02a4,
0x40a3,
0x82a2,
0xc5a1,
0x0aa1,
0x4ea0,
0x929f,
0xd59e,
0x199e,
0x5f9d,
0xa89c,
0xf69b,
0x479b,
0x9c9a,
0xf399,
0x4c99,
0xa498,
0xfc97,
0x5397,
0xab96,
0x0496,
0x6195,
0xc294,
0x2894,
0x9193,
0xfd92,
0x6a92,
0xd891,
0x4491,
0xb190,
0x1d90,
0x8b8f,
0xfd8e,
0x738e,
0xee8d,
0x6d8d,
0xef8c,
0x738c,
0xf78b,
0x7a8b,
0xfd8a,
0x808a,
0x058a,
0x8d89,
0x1989,
0xac88,
0x4388,
0xdd87,
0x7a87,
0x1787,
0xb486,
0x4f86,
0xeb85,
0x8885,
0x2985,
0xcf84,
0x7c84,
0x2e84,
0xe483,
0x9d83,
0x5783,
0x1083,
0xc882,
0x8082,
0x3a82,
0xf781,
0xbb81,
0x8681,
0x5881,
0x2f81,
0x0a81,
0xe680,
0xc180,
0x9b80,
0x7480,
0x5080,
0x3080,
0x1780,
0x0780,
0x0080,
0x0180,
0x0680,
0x0d80,
0x1480,
0x1880,
0x1c80,
0x2280,
0x2e80,
0x4380,
0x6580,
0x9380,
0xcc80,
0x0d81,
0x5181,
0x9481,
0xd481,
0x1382,
0x5582,
0x9e82,
0xf782,
0x6483,
0xe783,
0x7e84,
0x2485,
0xd085,
0x7c86,
0x2387,
0xc687,
0x6d88,
0x2889,
0x0b8a,
0x2e8b,
0xa48c,
0x7b8e,
0xb990,
0x5693,
0x4196,
0x6199,
0x989c,
0xc99f,
0xdda2,
0xc4a5,
0x79a8,
0xfdaa,
0x5dad,
0xa3af,
0xdeb1,
0x18b4,
0x56b6,
0x97b8,
0xd7ba,
0x10bd,
0x3cbf,
0x57c1,
0x5ec3,
0x56c5,
0x42c7,
0x27c9,
0x0ccb,
0xf2cc,
0xdbce,
0xc3d0,
0xa8d2,
0x85d4,
0x58d6,
0x1fd8,
0xdbd9,
0x90db,
0x40dd,
0xeede,
0x9ee0,
0x4fe2,
0x01e4,
0xb0e5,
0x5ae7,
0xfde8,
0x98ea,
0x2aec,
0xb6ed,
0x3eef,
0xc5f0,
0x4cf2,
0xd5f3,
0x5ef5,
0xe6f6,
0x6af8,
0xe8f9,
0x5ffb,
0xd0fc,
0x3cfe,
0xa4ff,
0x0a01,
0x7202,
0xda03,
0x4305,
0xaa06,
0x0f08,
0x6f09,
0xca0a,
0x1e0c,
0x6e0d,
0xbb0e,
0x0710,
0x5311,
0x9f12,
0xec13,
0x3915,
0x8316,
0xc917,
0x0a19,
0x471a,
0x7e1b,
0xb31c,
0xe71d,
0x1a1f,
0x4e20,
0x8321,
0xb722,
0xea23,
0x1925,
0x4426,
0x6a27,
0x8b28,
0xaa29,
0xc82a,
0xe52b,
0x032d,
0x222e,
0x402f,
0x5d30,
0x7731,
0x8d32,
0x9e33,
0xab34,
0xb635,
0xbf36,
0xc837,
0xd138,
0xdb39,
0xe43a,
0xed3b,
0xf33c,
0xf53d,
0xf33e,
0xed3f,
0xe440,
0xd941,
0xce42,
0xc443,
0xba44,
0xb045,
0xa546,
0x9747,
0x8748,
0x7249,
0x594a,
0x3d4b,
0x1f4c,
0x014d,
0xe34d,
0xc64e,
0xa94f,
0x8b50,
0x6b51,
0x4752,
0x2053,
0xf453,
0xc554,
0x9555,
0x6456,
0x3357,
0x0258,
0xd258,
0xa159,
0x6e5a,
0x385b,
0xfe5b,
0xc05c,
0x7e5d,
0x3b5e,
0xf65e,
0xb25f,
0x6e60,
0x2b61,
0xe761,
0xa162,
0x5863,
0x0a64,
0xb964,
0x6465,
0x0d66,
0xb466,
0x5c67,
0x0468,
0xad68,
0x5569,
0xfc69,
0x9f6a,
0x3e6b,
0xd86b,
0x6f6c,
0x036d,
0x966d,
0x286e,
0xbc6e,
0x4f6f,
0xe36f,
0x7570,
0x0371,
0x8d71,
0x1272,
0x9372,
0x1173,
0x8d73,
0x0974,
0x8674,
0x0375,
0x8075,
0xfb75,
0x7376,
0xe776,
0x5477,
0xbd77,
0x2378,
0x8678,
0xe978,
0x4c79,
0xb179,
0x157a,
0x787a,
0xd77a,
0x317b,
0x847b,
0xd27b,
0x1c7c,
0x637c,
0xa97c,
0xf07c,
0x387d,
0x807d,
0xc67d,
0x097e,
0x457e,
0x7a7e,
0xa87e,
0xd17e,
0xf67e,
0x1a7f,
0x3f7f,
0x657f,
0x8c7f,
0xb07f,
0xd07f,
0xe97f,
0xf97f,
0xff7f,
0xff7f,
0xfa7f,
0xf37f,
0xec7f,
0xe87f,
0xe47f,
0xde7f,
0xd27f,
0xbd7f,
0x9b7f,
0x6d7f,
0x347f,
0xf37e,
0xaf7e,
0x6c7e,
0x2c7e,
0xed7d,
0xab7d,
0x627d,
0x097d,
0x9c7c,
0x197c,
0x827b,
0xdc7a,
0x307a,
0x8479,
0xdd78,
0x3a78,
0x9377,
0xd876,
0xf575,
0xd274,
0x5c73,
0x8571,
0x476f
};
