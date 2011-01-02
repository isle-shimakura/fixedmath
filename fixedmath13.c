#include "fixedmath.h"

#define SIN_TABLE_LENGTH ((1<<13)/4)
static const uint16_t sin_table[] = {
	0x0000,0x0019,0x0032,0x004b,0x0064,0x007d,0x0096,0x00af,
	0x00c9,0x00e2,0x00fb,0x0114,0x012d,0x0146,0x015f,0x0178,
	0x0192,0x01ab,0x01c4,0x01dd,0x01f6,0x020f,0x0228,0x0242,
	0x025b,0x0274,0x028d,0x02a6,0x02bf,0x02d8,0x02f1,0x030b,
	0x0324,0x033d,0x0356,0x036f,0x0388,0x03a1,0x03ba,0x03d4,
	0x03ed,0x0406,0x041f,0x0438,0x0451,0x046a,0x0483,0x049c,
	0x04b6,0x04cf,0x04e8,0x0501,0x051a,0x0533,0x054c,0x0565,
	0x057f,0x0598,0x05b1,0x05ca,0x05e3,0x05fc,0x0615,0x062e,
	0x0647,0x0660,0x067a,0x0693,0x06ac,0x06c5,0x06de,0x06f7,
	0x0710,0x0729,0x0742,0x075b,0x0775,0x078e,0x07a7,0x07c0,
	0x07d9,0x07f2,0x080b,0x0824,0x083d,0x0856,0x086f,0x0888,
	0x08a2,0x08bb,0x08d4,0x08ed,0x0906,0x091f,0x0938,0x0951,
	0x096a,0x0983,0x099c,0x09b5,0x09ce,0x09e7,0x0a00,0x0a19,
	0x0a33,0x0a4c,0x0a65,0x0a7e,0x0a97,0x0ab0,0x0ac9,0x0ae2,
	0x0afb,0x0b14,0x0b2d,0x0b46,0x0b5f,0x0b78,0x0b91,0x0baa,
	0x0bc3,0x0bdc,0x0bf5,0x0c0e,0x0c27,0x0c40,0x0c59,0x0c72,
	0x0c8b,0x0ca4,0x0cbd,0x0cd6,0x0cef,0x0d08,0x0d21,0x0d3a,
	0x0d53,0x0d6c,0x0d85,0x0d9e,0x0db7,0x0dd0,0x0de9,0x0e02,
	0x0e1b,0x0e34,0x0e4d,0x0e66,0x0e7f,0x0e98,0x0eb1,0x0eca,
	0x0ee3,0x0efc,0x0f15,0x0f2e,0x0f47,0x0f60,0x0f79,0x0f92,
	0x0fab,0x0fc4,0x0fdd,0x0ff5,0x100e,0x1027,0x1040,0x1059,
	0x1072,0x108b,0x10a4,0x10bd,0x10d6,0x10ef,0x1108,0x1121,
	0x1139,0x1152,0x116b,0x1184,0x119d,0x11b6,0x11cf,0x11e8,
	0x1201,0x1219,0x1232,0x124b,0x1264,0x127d,0x1296,0x12af,
	0x12c8,0x12e0,0x12f9,0x1312,0x132b,0x1344,0x135d,0x1376,
	0x138e,0x13a7,0x13c0,0x13d9,0x13f2,0x140b,0x1423,0x143c,
	0x1455,0x146e,0x1487,0x149f,0x14b8,0x14d1,0x14ea,0x1503,
	0x151b,0x1534,0x154d,0x1566,0x157f,0x1597,0x15b0,0x15c9,
	0x15e2,0x15fa,0x1613,0x162c,0x1645,0x165d,0x1676,0x168f,
	0x16a8,0x16c0,0x16d9,0x16f2,0x170a,0x1723,0x173c,0x1755,
	0x176d,0x1786,0x179f,0x17b7,0x17d0,0x17e9,0x1802,0x181a,
	0x1833,0x184c,0x1864,0x187d,0x1896,0x18ae,0x18c7,0x18e0,
	0x18f8,0x1911,0x192a,0x1942,0x195b,0x1973,0x198c,0x19a5,
	0x19bd,0x19d6,0x19ef,0x1a07,0x1a20,0x1a38,0x1a51,0x1a6a,
	0x1a82,0x1a9b,0x1ab3,0x1acc,0x1ae4,0x1afd,0x1b16,0x1b2e,
	0x1b47,0x1b5f,0x1b78,0x1b90,0x1ba9,0x1bc1,0x1bda,0x1bf2,
	0x1c0b,0x1c24,0x1c3c,0x1c55,0x1c6d,0x1c86,0x1c9e,0x1cb7,
	0x1ccf,0x1ce8,0x1d00,0x1d18,0x1d31,0x1d49,0x1d62,0x1d7a,
	0x1d93,0x1dab,0x1dc4,0x1ddc,0x1df5,0x1e0d,0x1e25,0x1e3e,
	0x1e56,0x1e6f,0x1e87,0x1ea0,0x1eb8,0x1ed0,0x1ee9,0x1f01,
	0x1f19,0x1f32,0x1f4a,0x1f63,0x1f7b,0x1f93,0x1fac,0x1fc4,
	0x1fdc,0x1ff5,0x200d,0x2025,0x203e,0x2056,0x206e,0x2087,
	0x209f,0x20b7,0x20d0,0x20e8,0x2100,0x2118,0x2131,0x2149,
	0x2161,0x2179,0x2192,0x21aa,0x21c2,0x21da,0x21f3,0x220b,
	0x2223,0x223b,0x2254,0x226c,0x2284,0x229c,0x22b4,0x22cd,
	0x22e5,0x22fd,0x2315,0x232d,0x2345,0x235e,0x2376,0x238e,
	0x23a6,0x23be,0x23d6,0x23ee,0x2407,0x241f,0x2437,0x244f,
	0x2467,0x247f,0x2497,0x24af,0x24c7,0x24df,0x24f7,0x250f,
	0x2528,0x2540,0x2558,0x2570,0x2588,0x25a0,0x25b8,0x25d0,
	0x25e8,0x2600,0x2618,0x2630,0x2648,0x2660,0x2678,0x2690,
	0x26a8,0x26c0,0x26d8,0x26ef,0x2707,0x271f,0x2737,0x274f,
	0x2767,0x277f,0x2797,0x27af,0x27c7,0x27df,0x27f6,0x280e,
	0x2826,0x283e,0x2856,0x286e,0x2886,0x289d,0x28b5,0x28cd,
	0x28e5,0x28fd,0x2915,0x292c,0x2944,0x295c,0x2974,0x298b,
	0x29a3,0x29bb,0x29d3,0x29eb,0x2a02,0x2a1a,0x2a32,0x2a49,
	0x2a61,0x2a79,0x2a91,0x2aa8,0x2ac0,0x2ad8,0x2aef,0x2b07,
	0x2b1f,0x2b36,0x2b4e,0x2b66,0x2b7d,0x2b95,0x2bad,0x2bc4,
	0x2bdc,0x2bf3,0x2c0b,0x2c23,0x2c3a,0x2c52,0x2c69,0x2c81,
	0x2c98,0x2cb0,0x2cc8,0x2cdf,0x2cf7,0x2d0e,0x2d26,0x2d3d,
	0x2d55,0x2d6c,0x2d84,0x2d9b,0x2db3,0x2dca,0x2de2,0x2df9,
	0x2e11,0x2e28,0x2e3f,0x2e57,0x2e6e,0x2e86,0x2e9d,0x2eb5,
	0x2ecc,0x2ee3,0x2efb,0x2f12,0x2f29,0x2f41,0x2f58,0x2f6f,
	0x2f87,0x2f9e,0x2fb5,0x2fcd,0x2fe4,0x2ffb,0x3013,0x302a,
	0x3041,0x3059,0x3070,0x3087,0x309e,0x30b6,0x30cd,0x30e4,
	0x30fb,0x3112,0x312a,0x3141,0x3158,0x316f,0x3186,0x319e,
	0x31b5,0x31cc,0x31e3,0x31fa,0x3211,0x3228,0x3240,0x3257,
	0x326e,0x3285,0x329c,0x32b3,0x32ca,0x32e1,0x32f8,0x330f,
	0x3326,0x333d,0x3354,0x336b,0x3382,0x3399,0x33b0,0x33c7,
	0x33de,0x33f5,0x340c,0x3423,0x343a,0x3451,0x3468,0x347f,
	0x3496,0x34ad,0x34c4,0x34db,0x34f2,0x3508,0x351f,0x3536,
	0x354d,0x3564,0x357b,0x3592,0x35a8,0x35bf,0x35d6,0x35ed,
	0x3604,0x361a,0x3631,0x3648,0x365f,0x3675,0x368c,0x36a3,
	0x36ba,0x36d0,0x36e7,0x36fe,0x3714,0x372b,0x3742,0x3758,
	0x376f,0x3786,0x379c,0x37b3,0x37ca,0x37e0,0x37f7,0x380d,
	0x3824,0x383b,0x3851,0x3868,0x387e,0x3895,0x38ab,0x38c2,
	0x38d8,0x38ef,0x3906,0x391c,0x3932,0x3949,0x395f,0x3976,
	0x398c,0x39a3,0x39b9,0x39d0,0x39e6,0x39fd,0x3a13,0x3a29,
	0x3a40,0x3a56,0x3a6c,0x3a83,0x3a99,0x3aaf,0x3ac6,0x3adc,
	0x3af2,0x3b09,0x3b1f,0x3b35,0x3b4c,0x3b62,0x3b78,0x3b8e,
	0x3ba5,0x3bbb,0x3bd1,0x3be7,0x3bfd,0x3c14,0x3c2a,0x3c40,
	0x3c56,0x3c6c,0x3c83,0x3c99,0x3caf,0x3cc5,0x3cdb,0x3cf1,
	0x3d07,0x3d1d,0x3d33,0x3d49,0x3d60,0x3d76,0x3d8c,0x3da2,
	0x3db8,0x3dce,0x3de4,0x3dfa,0x3e10,0x3e26,0x3e3c,0x3e52,
	0x3e68,0x3e7d,0x3e93,0x3ea9,0x3ebf,0x3ed5,0x3eeb,0x3f01,
	0x3f17,0x3f2d,0x3f43,0x3f58,0x3f6e,0x3f84,0x3f9a,0x3fb0,
	0x3fc5,0x3fdb,0x3ff1,0x4007,0x401d,0x4032,0x4048,0x405e,
	0x4073,0x4089,0x409f,0x40b5,0x40ca,0x40e0,0x40f6,0x410b,
	0x4121,0x4136,0x414c,0x4162,0x4177,0x418d,0x41a2,0x41b8,
	0x41ce,0x41e3,0x41f9,0x420e,0x4224,0x4239,0x424f,0x4264,
	0x427a,0x428f,0x42a5,0x42ba,0x42d0,0x42e5,0x42fa,0x4310,
	0x4325,0x433b,0x4350,0x4365,0x437b,0x4390,0x43a5,0x43bb,
	0x43d0,0x43e5,0x43fb,0x4410,0x4425,0x443b,0x4450,0x4465,
	0x447a,0x4490,0x44a5,0x44ba,0x44cf,0x44e4,0x44fa,0x450f,
	0x4524,0x4539,0x454e,0x4563,0x4578,0x458d,0x45a3,0x45b8,
	0x45cd,0x45e2,0x45f7,0x460c,0x4621,0x4636,0x464b,0x4660,
	0x4675,0x468a,0x469f,0x46b4,0x46c9,0x46de,0x46f3,0x4708,
	0x471c,0x4731,0x4746,0x475b,0x4770,0x4785,0x479a,0x47ae,
	0x47c3,0x47d8,0x47ed,0x4802,0x4816,0x482b,0x4840,0x4855,
	0x4869,0x487e,0x4893,0x48a8,0x48bc,0x48d1,0x48e6,0x48fa,
	0x490f,0x4923,0x4938,0x494d,0x4961,0x4976,0x498a,0x499f,
	0x49b4,0x49c8,0x49dd,0x49f1,0x4a06,0x4a1a,0x4a2f,0x4a43,
	0x4a58,0x4a6c,0x4a81,0x4a95,0x4aa9,0x4abe,0x4ad2,0x4ae7,
	0x4afb,0x4b0f,0x4b24,0x4b38,0x4b4c,0x4b61,0x4b75,0x4b89,
	0x4b9e,0x4bb2,0x4bc6,0x4bda,0x4bef,0x4c03,0x4c17,0x4c2b,
	0x4c3f,0x4c54,0x4c68,0x4c7c,0x4c90,0x4ca4,0x4cb8,0x4ccc,
	0x4ce1,0x4cf5,0x4d09,0x4d1d,0x4d31,0x4d45,0x4d59,0x4d6d,
	0x4d81,0x4d95,0x4da9,0x4dbd,0x4dd1,0x4de5,0x4df9,0x4e0d,
	0x4e21,0x4e34,0x4e48,0x4e5c,0x4e70,0x4e84,0x4e98,0x4eac,
	0x4ebf,0x4ed3,0x4ee7,0x4efb,0x4f0f,0x4f22,0x4f36,0x4f4a,
	0x4f5e,0x4f71,0x4f85,0x4f99,0x4fac,0x4fc0,0x4fd4,0x4fe7,
	0x4ffb,0x500f,0x5022,0x5036,0x5049,0x505d,0x5070,0x5084,
	0x5097,0x50ab,0x50bf,0x50d2,0x50e5,0x50f9,0x510c,0x5120,
	0x5133,0x5147,0x515a,0x516e,0x5181,0x5194,0x51a8,0x51bb,
	0x51ce,0x51e2,0x51f5,0x5208,0x521c,0x522f,0x5242,0x5255,
	0x5269,0x527c,0x528f,0x52a2,0x52b5,0x52c9,0x52dc,0x52ef,
	0x5302,0x5315,0x5328,0x533b,0x534e,0x5362,0x5375,0x5388,
	0x539b,0x53ae,0x53c1,0x53d4,0x53e7,0x53fa,0x540d,0x5420,
	0x5433,0x5445,0x5458,0x546b,0x547e,0x5491,0x54a4,0x54b7,
	0x54ca,0x54dc,0x54ef,0x5502,0x5515,0x5528,0x553a,0x554d,
	0x5560,0x5572,0x5585,0x5598,0x55ab,0x55bd,0x55d0,0x55e3,
	0x55f5,0x5608,0x561a,0x562d,0x5640,0x5652,0x5665,0x5677,
	0x568a,0x569c,0x56af,0x56c1,0x56d4,0x56e6,0x56f9,0x570b,
	0x571d,0x5730,0x5742,0x5755,0x5767,0x5779,0x578c,0x579e,
	0x57b0,0x57c3,0x57d5,0x57e7,0x57f9,0x580c,0x581e,0x5830,
	0x5842,0x5855,0x5867,0x5879,0x588b,0x589d,0x58af,0x58c1,
	0x58d4,0x58e6,0x58f8,0x590a,0x591c,0x592e,0x5940,0x5952,
	0x5964,0x5976,0x5988,0x599a,0x59ac,0x59be,0x59d0,0x59e1,
	0x59f3,0x5a05,0x5a17,0x5a29,0x5a3b,0x5a4d,0x5a5e,0x5a70,
	0x5a82,0x5a94,0x5aa5,0x5ab7,0x5ac9,0x5adb,0x5aec,0x5afe,
	0x5b10,0x5b21,0x5b33,0x5b45,0x5b56,0x5b68,0x5b79,0x5b8b,
	0x5b9d,0x5bae,0x5bc0,0x5bd1,0x5be3,0x5bf4,0x5c06,0x5c17,
	0x5c29,0x5c3a,0x5c4b,0x5c5d,0x5c6e,0x5c80,0x5c91,0x5ca2,
	0x5cb4,0x5cc5,0x5cd6,0x5ce8,0x5cf9,0x5d0a,0x5d1b,0x5d2d,
	0x5d3e,0x5d4f,0x5d60,0x5d71,0x5d83,0x5d94,0x5da5,0x5db6,
	0x5dc7,0x5dd8,0x5de9,0x5dfa,0x5e0b,0x5e1c,0x5e2d,0x5e3f,
	0x5e50,0x5e60,0x5e71,0x5e82,0x5e93,0x5ea4,0x5eb5,0x5ec6,
	0x5ed7,0x5ee8,0x5ef9,0x5f0a,0x5f1a,0x5f2b,0x5f3c,0x5f4d,
	0x5f5e,0x5f6e,0x5f7f,0x5f90,0x5fa0,0x5fb1,0x5fc2,0x5fd3,
	0x5fe3,0x5ff4,0x6004,0x6015,0x6026,0x6036,0x6047,0x6057,
	0x6068,0x6078,0x6089,0x6099,0x60aa,0x60ba,0x60cb,0x60db,
	0x60ec,0x60fc,0x610d,0x611d,0x612d,0x613e,0x614e,0x615e,
	0x616f,0x617f,0x618f,0x619f,0x61b0,0x61c0,0x61d0,0x61e0,
	0x61f1,0x6201,0x6211,0x6221,0x6231,0x6241,0x6251,0x6261,
	0x6271,0x6282,0x6292,0x62a2,0x62b2,0x62c2,0x62d2,0x62e2,
	0x62f2,0x6301,0x6311,0x6321,0x6331,0x6341,0x6351,0x6361,
	0x6371,0x6380,0x6390,0x63a0,0x63b0,0x63c0,0x63cf,0x63df,
	0x63ef,0x63fe,0x640e,0x641e,0x642d,0x643d,0x644d,0x645c,
	0x646c,0x647b,0x648b,0x649b,0x64aa,0x64ba,0x64c9,0x64d9,
	0x64e8,0x64f7,0x6507,0x6516,0x6526,0x6535,0x6545,0x6554,
	0x6563,0x6573,0x6582,0x6591,0x65a0,0x65b0,0x65bf,0x65ce,
	0x65dd,0x65ed,0x65fc,0x660b,0x661a,0x6629,0x6639,0x6648,
	0x6657,0x6666,0x6675,0x6684,0x6693,0x66a2,0x66b1,0x66c0,
	0x66cf,0x66de,0x66ed,0x66fc,0x670b,0x671a,0x6729,0x6737,
	0x6746,0x6755,0x6764,0x6773,0x6782,0x6790,0x679f,0x67ae,
	0x67bd,0x67cb,0x67da,0x67e9,0x67f7,0x6806,0x6815,0x6823,
	0x6832,0x6840,0x684f,0x685e,0x686c,0x687b,0x6889,0x6898,
	0x68a6,0x68b5,0x68c3,0x68d1,0x68e0,0x68ee,0x68fd,0x690b,
	0x6919,0x6928,0x6936,0x6944,0x6953,0x6961,0x696f,0x697d,
	0x698c,0x699a,0x69a8,0x69b6,0x69c4,0x69d3,0x69e1,0x69ef,
	0x69fd,0x6a0b,0x6a19,0x6a27,0x6a35,0x6a43,0x6a51,0x6a5f,
	0x6a6d,0x6a7b,0x6a89,0x6a97,0x6aa5,0x6ab3,0x6ac1,0x6ace,
	0x6adc,0x6aea,0x6af8,0x6b06,0x6b13,0x6b21,0x6b2f,0x6b3d,
	0x6b4a,0x6b58,0x6b66,0x6b73,0x6b81,0x6b8f,0x6b9c,0x6baa,
	0x6bb8,0x6bc5,0x6bd3,0x6be0,0x6bee,0x6bfb,0x6c09,0x6c16,
	0x6c24,0x6c31,0x6c3f,0x6c4c,0x6c59,0x6c67,0x6c74,0x6c81,
	0x6c8f,0x6c9c,0x6ca9,0x6cb7,0x6cc4,0x6cd1,0x6cde,0x6cec,
	0x6cf9,0x6d06,0x6d13,0x6d20,0x6d2d,0x6d3a,0x6d48,0x6d55,
	0x6d62,0x6d6f,0x6d7c,0x6d89,0x6d96,0x6da3,0x6db0,0x6dbd,
	0x6dca,0x6dd6,0x6de3,0x6df0,0x6dfd,0x6e0a,0x6e17,0x6e24,
	0x6e30,0x6e3d,0x6e4a,0x6e57,0x6e63,0x6e70,0x6e7d,0x6e89,
	0x6e96,0x6ea3,0x6eaf,0x6ebc,0x6ec9,0x6ed5,0x6ee2,0x6eee,
	0x6efb,0x6f07,0x6f14,0x6f20,0x6f2d,0x6f39,0x6f46,0x6f52,
	0x6f5f,0x6f6b,0x6f77,0x6f84,0x6f90,0x6f9c,0x6fa9,0x6fb5,
	0x6fc1,0x6fcd,0x6fda,0x6fe6,0x6ff2,0x6ffe,0x700a,0x7016,
	0x7023,0x702f,0x703b,0x7047,0x7053,0x705f,0x706b,0x7077,
	0x7083,0x708f,0x709b,0x70a7,0x70b3,0x70bf,0x70cb,0x70d6,
	0x70e2,0x70ee,0x70fa,0x7106,0x7112,0x711d,0x7129,0x7135,
	0x7141,0x714c,0x7158,0x7164,0x716f,0x717b,0x7186,0x7192,
	0x719e,0x71a9,0x71b5,0x71c0,0x71cc,0x71d7,0x71e3,0x71ee,
	0x71fa,0x7205,0x7211,0x721c,0x7227,0x7233,0x723e,0x7249,
	0x7255,0x7260,0x726b,0x7276,0x7282,0x728d,0x7298,0x72a3,
	0x72af,0x72ba,0x72c5,0x72d0,0x72db,0x72e6,0x72f1,0x72fc,
	0x7307,0x7312,0x731d,0x7328,0x7333,0x733e,0x7349,0x7354,
	0x735f,0x736a,0x7375,0x737f,0x738a,0x7395,0x73a0,0x73ab,
	0x73b5,0x73c0,0x73cb,0x73d6,0x73e0,0x73eb,0x73f6,0x7400,
	0x740b,0x7415,0x7420,0x742b,0x7435,0x7440,0x744a,0x7455,
	0x745f,0x746a,0x7474,0x747e,0x7489,0x7493,0x749e,0x74a8,
	0x74b2,0x74bd,0x74c7,0x74d1,0x74db,0x74e6,0x74f0,0x74fa,
	0x7504,0x750f,0x7519,0x7523,0x752d,0x7537,0x7541,0x754b,
	0x7555,0x755f,0x7569,0x7573,0x757d,0x7587,0x7591,0x759b,
	0x75a5,0x75af,0x75b9,0x75c3,0x75cc,0x75d6,0x75e0,0x75ea,
	0x75f4,0x75fd,0x7607,0x7611,0x761b,0x7624,0x762e,0x7638,
	0x7641,0x764b,0x7654,0x765e,0x7668,0x7671,0x767b,0x7684,
	0x768e,0x7697,0x76a0,0x76aa,0x76b3,0x76bd,0x76c6,0x76cf,
	0x76d9,0x76e2,0x76eb,0x76f5,0x76fe,0x7707,0x7710,0x771a,
	0x7723,0x772c,0x7735,0x773e,0x7747,0x7751,0x775a,0x7763,
	0x776c,0x7775,0x777e,0x7787,0x7790,0x7799,0x77a2,0x77ab,
	0x77b4,0x77bc,0x77c5,0x77ce,0x77d7,0x77e0,0x77e9,0x77f1,
	0x77fa,0x7803,0x780c,0x7814,0x781d,0x7826,0x782e,0x7837,
	0x7840,0x7848,0x7851,0x7859,0x7862,0x786b,0x7873,0x787c,
	0x7884,0x788c,0x7895,0x789d,0x78a6,0x78ae,0x78b6,0x78bf,
	0x78c7,0x78cf,0x78d8,0x78e0,0x78e8,0x78f1,0x78f9,0x7901,
	0x7909,0x7911,0x7919,0x7922,0x792a,0x7932,0x793a,0x7942,
	0x794a,0x7952,0x795a,0x7962,0x796a,0x7972,0x797a,0x7982,
	0x798a,0x7992,0x7999,0x79a1,0x79a9,0x79b1,0x79b9,0x79c0,
	0x79c8,0x79d0,0x79d8,0x79df,0x79e7,0x79ef,0x79f6,0x79fe,
	0x7a05,0x7a0d,0x7a15,0x7a1c,0x7a24,0x7a2b,0x7a33,0x7a3a,
	0x7a42,0x7a49,0x7a50,0x7a58,0x7a5f,0x7a67,0x7a6e,0x7a75,
	0x7a7d,0x7a84,0x7a8b,0x7a92,0x7a9a,0x7aa1,0x7aa8,0x7aaf,
	0x7ab6,0x7abd,0x7ac5,0x7acc,0x7ad3,0x7ada,0x7ae1,0x7ae8,
	0x7aef,0x7af6,0x7afd,0x7b04,0x7b0b,0x7b12,0x7b19,0x7b1f,
	0x7b26,0x7b2d,0x7b34,0x7b3b,0x7b42,0x7b48,0x7b4f,0x7b56,
	0x7b5d,0x7b63,0x7b6a,0x7b71,0x7b77,0x7b7e,0x7b84,0x7b8b,
	0x7b92,0x7b98,0x7b9f,0x7ba5,0x7bac,0x7bb2,0x7bb9,0x7bbf,
	0x7bc5,0x7bcc,0x7bd2,0x7bd9,0x7bdf,0x7be5,0x7beb,0x7bf2,
	0x7bf8,0x7bfe,0x7c05,0x7c0b,0x7c11,0x7c17,0x7c1d,0x7c23,
	0x7c29,0x7c30,0x7c36,0x7c3c,0x7c42,0x7c48,0x7c4e,0x7c54,
	0x7c5a,0x7c60,0x7c66,0x7c6c,0x7c71,0x7c77,0x7c7d,0x7c83,
	0x7c89,0x7c8f,0x7c94,0x7c9a,0x7ca0,0x7ca6,0x7cab,0x7cb1,
	0x7cb7,0x7cbc,0x7cc2,0x7cc8,0x7ccd,0x7cd3,0x7cd8,0x7cde,
	0x7ce3,0x7ce9,0x7cee,0x7cf4,0x7cf9,0x7cff,0x7d04,0x7d09,
	0x7d0f,0x7d14,0x7d19,0x7d1f,0x7d24,0x7d29,0x7d2f,0x7d34,
	0x7d39,0x7d3e,0x7d43,0x7d49,0x7d4e,0x7d53,0x7d58,0x7d5d,
	0x7d62,0x7d67,0x7d6c,0x7d71,0x7d76,0x7d7b,0x7d80,0x7d85,
	0x7d8a,0x7d8f,0x7d94,0x7d98,0x7d9d,0x7da2,0x7da7,0x7dac,
	0x7db0,0x7db5,0x7dba,0x7dbf,0x7dc3,0x7dc8,0x7dcd,0x7dd1,
	0x7dd6,0x7dda,0x7ddf,0x7de4,0x7de8,0x7ded,0x7df1,0x7df6,
	0x7dfa,0x7dff,0x7e03,0x7e07,0x7e0c,0x7e10,0x7e14,0x7e19,
	0x7e1d,0x7e21,0x7e26,0x7e2a,0x7e2e,0x7e32,0x7e37,0x7e3b,
	0x7e3f,0x7e43,0x7e47,0x7e4b,0x7e4f,0x7e53,0x7e57,0x7e5b,
	0x7e5f,0x7e63,0x7e67,0x7e6b,0x7e6f,0x7e73,0x7e77,0x7e7b,
	0x7e7f,0x7e83,0x7e86,0x7e8a,0x7e8e,0x7e92,0x7e95,0x7e99,
	0x7e9d,0x7ea1,0x7ea4,0x7ea8,0x7eab,0x7eaf,0x7eb3,0x7eb6,
	0x7eba,0x7ebd,0x7ec1,0x7ec4,0x7ec8,0x7ecb,0x7ecf,0x7ed2,
	0x7ed5,0x7ed9,0x7edc,0x7edf,0x7ee3,0x7ee6,0x7ee9,0x7eed,
	0x7ef0,0x7ef3,0x7ef6,0x7ef9,0x7efd,0x7f00,0x7f03,0x7f06,
	0x7f09,0x7f0c,0x7f0f,0x7f12,0x7f15,0x7f18,0x7f1b,0x7f1e,
	0x7f21,0x7f24,0x7f27,0x7f2a,0x7f2d,0x7f2f,0x7f32,0x7f35,
	0x7f38,0x7f3b,0x7f3d,0x7f40,0x7f43,0x7f45,0x7f48,0x7f4b,
	0x7f4d,0x7f50,0x7f53,0x7f55,0x7f58,0x7f5a,0x7f5d,0x7f5f,
	0x7f62,0x7f64,0x7f67,0x7f69,0x7f6b,0x7f6e,0x7f70,0x7f72,
	0x7f75,0x7f77,0x7f79,0x7f7c,0x7f7e,0x7f80,0x7f82,0x7f85,
	0x7f87,0x7f89,0x7f8b,0x7f8d,0x7f8f,0x7f91,0x7f93,0x7f95,
	0x7f97,0x7f99,0x7f9b,0x7f9d,0x7f9f,0x7fa1,0x7fa3,0x7fa5,
	0x7fa7,0x7fa9,0x7faa,0x7fac,0x7fae,0x7fb0,0x7fb1,0x7fb3,
	0x7fb5,0x7fb7,0x7fb8,0x7fba,0x7fbc,0x7fbd,0x7fbf,0x7fc0,
	0x7fc2,0x7fc3,0x7fc5,0x7fc6,0x7fc8,0x7fc9,0x7fcb,0x7fcc,
	0x7fce,0x7fcf,0x7fd0,0x7fd2,0x7fd3,0x7fd4,0x7fd6,0x7fd7,
	0x7fd8,0x7fd9,0x7fda,0x7fdc,0x7fdd,0x7fde,0x7fdf,0x7fe0,
	0x7fe1,0x7fe2,0x7fe3,0x7fe4,0x7fe5,0x7fe6,0x7fe7,0x7fe8,
	0x7fe9,0x7fea,0x7feb,0x7fec,0x7fed,0x7fee,0x7fee,0x7fef,
	0x7ff0,0x7ff1,0x7ff2,0x7ff2,0x7ff3,0x7ff4,0x7ff4,0x7ff5,
	0x7ff6,0x7ff6,0x7ff7,0x7ff7,0x7ff8,0x7ff8,0x7ff9,0x7ff9,
	0x7ffa,0x7ffa,0x7ffb,0x7ffb,0x7ffc,0x7ffc,0x7ffc,0x7ffd,
	0x7ffd,0x7ffd,0x7ffe,0x7ffe,0x7ffe,0x7ffe,0x7fff,0x7fff,
	0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,0x7fff,
	0x8000
};

Fixed sin13(int x)
{
	Fixed retval;

#if 1 /* コンパイラの最適化に期待 */
	if (x < 0) {
		x = -(x + 1);
		x %= (M_PI * 2);
		x = (M_PI * 2 - 1) - x;
	}
	else {
		x %= (M_PI * 2);
	}
#else
	if (x < 0) {
		x = ~x;
		x &= (M_PI * 2 - 1);
		x = (M_PI * 2) - x;
	}
	else {
		x &= (M_PI * 2 - 1);
	}
#endif
	x >>= 2;

	if (x < SIN_TABLE_LENGTH) {
		retval.fixedValue = sin_table[x]<<1;
		return retval;
	}
	x -= SIN_TABLE_LENGTH;
	if (x < SIN_TABLE_LENGTH) {
		retval.fixedValue = sin_table[SIN_TABLE_LENGTH - x]<<1;
		return retval;
	}
	x -= SIN_TABLE_LENGTH;
	if (x < SIN_TABLE_LENGTH) {
		retval.fixedValue = -(sin_table[x]<<1);
		return retval;
	}
	x -= SIN_TABLE_LENGTH;
	retval.fixedValue = -(sin_table[SIN_TABLE_LENGTH - x]<<1);
	return retval;
}

Fixed cos13(int x)
{
	return sin13((M_PI / 2) - x);
}
