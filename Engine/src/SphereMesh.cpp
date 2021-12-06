//----------------------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SphereMesh.h"

namespace Azul
{

	struct Vert_xyz
	{
		float x;
		float y;
		float z;
	};

	struct Vert_nxnynz
	{
		float nx;
		float ny;
		float nz;
	};

	struct Vert_uv
	{
		float u;
		float v;
	};

	struct Tri_index
	{
		unsigned int v0;
		unsigned int v1;
		unsigned int v2;
	};


	void SphereMesh::privCreateVAO(const char* const modelFileName)
	{
		// future proofing it for a file
		AZUL_UNUSED_VAR(modelFileName);

#define TRILIST_NUM_TRIANGLES (sizeof(triList)/sizeof(Tri_index))
#define SPHERE_DATA_NUM_VERTS (sizeof(sphereData_xyz)/sizeof(Vert_xyz))

		Vert_xyz  sphereData_xyz[121];
		Vert_uv   sphereData_uv[121];
		Vert_nxnynz sphereData_nxnynz[121];

		Tri_index triList[200];

		{
			triList[0].v0 = 0;
			triList[0].v1 = 1;
			triList[0].v2 = 2;

			triList[1].v0 = 1;
			triList[1].v1 = 3;
			triList[1].v2 = 2;

			triList[2].v0 = 2;
			triList[2].v1 = 3;
			triList[2].v2 = 4;

			triList[3].v0 = 3;
			triList[3].v1 = 5;
			triList[3].v2 = 4;

			triList[4].v0 = 4;
			triList[4].v1 = 5;
			triList[4].v2 = 6;

			triList[5].v0 = 5;
			triList[5].v1 = 7;
			triList[5].v2 = 6;

			triList[6].v0 = 6;
			triList[6].v1 = 7;
			triList[6].v2 = 8;

			triList[7].v0 = 7;
			triList[7].v1 = 9;
			triList[7].v2 = 8;

			triList[8].v0 = 8;
			triList[8].v1 = 9;
			triList[8].v2 = 10;

			triList[9].v0 = 9;
			triList[9].v1 = 11;
			triList[9].v2 = 10;

			triList[10].v0 = 10;
			triList[10].v1 = 11;
			triList[10].v2 = 12;

			triList[11].v0 = 11;
			triList[11].v1 = 13;
			triList[11].v2 = 12;

			triList[12].v0 = 12;
			triList[12].v1 = 13;
			triList[12].v2 = 14;

			triList[13].v0 = 13;
			triList[13].v1 = 15;
			triList[13].v2 = 14;

			triList[14].v0 = 14;
			triList[14].v1 = 15;
			triList[14].v2 = 16;

			triList[15].v0 = 15;
			triList[15].v1 = 17;
			triList[15].v2 = 16;

			triList[16].v0 = 16;
			triList[16].v1 = 17;
			triList[16].v2 = 18;

			triList[17].v0 = 17;
			triList[17].v1 = 19;
			triList[17].v2 = 18;

			triList[18].v0 = 18;
			triList[18].v1 = 19;
			triList[18].v2 = 20;

			triList[19].v0 = 19;
			triList[19].v1 = 21;
			triList[19].v2 = 20;

			triList[20].v0 = 1;
			triList[20].v1 = 22;
			triList[20].v2 = 3;

			triList[21].v0 = 22;
			triList[21].v1 = 23;
			triList[21].v2 = 3;

			triList[22].v0 = 3;
			triList[22].v1 = 23;
			triList[22].v2 = 5;

			triList[23].v0 = 23;
			triList[23].v1 = 24;
			triList[23].v2 = 5;

			triList[24].v0 = 5;
			triList[24].v1 = 24;
			triList[24].v2 = 7;

			triList[25].v0 = 24;
			triList[25].v1 = 25;
			triList[25].v2 = 7;

			triList[26].v0 = 7;
			triList[26].v1 = 25;
			triList[26].v2 = 9;

			triList[27].v0 = 25;
			triList[27].v1 = 26;
			triList[27].v2 = 9;

			triList[28].v0 = 9;
			triList[28].v1 = 26;
			triList[28].v2 = 11;

			triList[29].v0 = 26;
			triList[29].v1 = 27;
			triList[29].v2 = 11;

			triList[30].v0 = 11;
			triList[30].v1 = 27;
			triList[30].v2 = 13;

			triList[31].v0 = 27;
			triList[31].v1 = 28;
			triList[31].v2 = 13;

			triList[32].v0 = 13;
			triList[32].v1 = 28;
			triList[32].v2 = 15;

			triList[33].v0 = 28;
			triList[33].v1 = 29;
			triList[33].v2 = 15;

			triList[34].v0 = 15;
			triList[34].v1 = 29;
			triList[34].v2 = 17;

			triList[35].v0 = 29;
			triList[35].v1 = 30;
			triList[35].v2 = 17;

			triList[36].v0 = 17;
			triList[36].v1 = 30;
			triList[36].v2 = 19;

			triList[37].v0 = 30;
			triList[37].v1 = 31;
			triList[37].v2 = 19;

			triList[38].v0 = 19;
			triList[38].v1 = 31;
			triList[38].v2 = 21;

			triList[39].v0 = 31;
			triList[39].v1 = 32;
			triList[39].v2 = 21;

			triList[40].v0 = 22;
			triList[40].v1 = 33;
			triList[40].v2 = 23;

			triList[41].v0 = 33;
			triList[41].v1 = 34;
			triList[41].v2 = 23;

			triList[42].v0 = 23;
			triList[42].v1 = 34;
			triList[42].v2 = 24;

			triList[43].v0 = 34;
			triList[43].v1 = 35;
			triList[43].v2 = 24;

			triList[44].v0 = 24;
			triList[44].v1 = 35;
			triList[44].v2 = 25;

			triList[45].v0 = 35;
			triList[45].v1 = 36;
			triList[45].v2 = 25;

			triList[46].v0 = 25;
			triList[46].v1 = 36;
			triList[46].v2 = 26;

			triList[47].v0 = 36;
			triList[47].v1 = 37;
			triList[47].v2 = 26;

			triList[48].v0 = 26;
			triList[48].v1 = 37;
			triList[48].v2 = 27;

			triList[49].v0 = 37;
			triList[49].v1 = 38;
			triList[49].v2 = 27;

			triList[50].v0 = 27;
			triList[50].v1 = 38;
			triList[50].v2 = 28;

			triList[51].v0 = 38;
			triList[51].v1 = 39;
			triList[51].v2 = 28;

			triList[52].v0 = 28;
			triList[52].v1 = 39;
			triList[52].v2 = 29;

			triList[53].v0 = 39;
			triList[53].v1 = 40;
			triList[53].v2 = 29;

			triList[54].v0 = 29;
			triList[54].v1 = 40;
			triList[54].v2 = 30;

			triList[55].v0 = 40;
			triList[55].v1 = 41;
			triList[55].v2 = 30;

			triList[56].v0 = 30;
			triList[56].v1 = 41;
			triList[56].v2 = 31;

			triList[57].v0 = 41;
			triList[57].v1 = 42;
			triList[57].v2 = 31;

			triList[58].v0 = 31;
			triList[58].v1 = 42;
			triList[58].v2 = 32;

			triList[59].v0 = 42;
			triList[59].v1 = 43;
			triList[59].v2 = 32;

			triList[60].v0 = 33;
			triList[60].v1 = 44;
			triList[60].v2 = 34;

			triList[61].v0 = 44;
			triList[61].v1 = 45;
			triList[61].v2 = 34;

			triList[62].v0 = 34;
			triList[62].v1 = 45;
			triList[62].v2 = 35;

			triList[63].v0 = 45;
			triList[63].v1 = 46;
			triList[63].v2 = 35;

			triList[64].v0 = 35;
			triList[64].v1 = 46;
			triList[64].v2 = 36;

			triList[65].v0 = 46;
			triList[65].v1 = 47;
			triList[65].v2 = 36;

			triList[66].v0 = 36;
			triList[66].v1 = 47;
			triList[66].v2 = 37;

			triList[67].v0 = 47;
			triList[67].v1 = 48;
			triList[67].v2 = 37;

			triList[68].v0 = 37;
			triList[68].v1 = 48;
			triList[68].v2 = 38;

			triList[69].v0 = 48;
			triList[69].v1 = 49;
			triList[69].v2 = 38;

			triList[70].v0 = 38;
			triList[70].v1 = 49;
			triList[70].v2 = 39;

			triList[71].v0 = 49;
			triList[71].v1 = 50;
			triList[71].v2 = 39;

			triList[72].v0 = 39;
			triList[72].v1 = 50;
			triList[72].v2 = 40;

			triList[73].v0 = 50;
			triList[73].v1 = 51;
			triList[73].v2 = 40;

			triList[74].v0 = 40;
			triList[74].v1 = 51;
			triList[74].v2 = 41;

			triList[75].v0 = 51;
			triList[75].v1 = 52;
			triList[75].v2 = 41;

			triList[76].v0 = 41;
			triList[76].v1 = 52;
			triList[76].v2 = 42;

			triList[77].v0 = 52;
			triList[77].v1 = 53;
			triList[77].v2 = 42;

			triList[78].v0 = 42;
			triList[78].v1 = 53;
			triList[78].v2 = 43;

			triList[79].v0 = 53;
			triList[79].v1 = 54;
			triList[79].v2 = 43;

			triList[80].v0 = 44;
			triList[80].v1 = 55;
			triList[80].v2 = 45;

			triList[81].v0 = 55;
			triList[81].v1 = 56;
			triList[81].v2 = 45;

			triList[82].v0 = 45;
			triList[82].v1 = 56;
			triList[82].v2 = 46;

			triList[83].v0 = 56;
			triList[83].v1 = 57;
			triList[83].v2 = 46;

			triList[84].v0 = 46;
			triList[84].v1 = 57;
			triList[84].v2 = 47;

			triList[85].v0 = 57;
			triList[85].v1 = 58;
			triList[85].v2 = 47;

			triList[86].v0 = 47;
			triList[86].v1 = 58;
			triList[86].v2 = 48;

			triList[87].v0 = 58;
			triList[87].v1 = 59;
			triList[87].v2 = 48;

			triList[88].v0 = 48;
			triList[88].v1 = 59;
			triList[88].v2 = 49;

			triList[89].v0 = 59;
			triList[89].v1 = 60;
			triList[89].v2 = 49;

			triList[90].v0 = 49;
			triList[90].v1 = 60;
			triList[90].v2 = 50;

			triList[91].v0 = 60;
			triList[91].v1 = 61;
			triList[91].v2 = 50;

			triList[92].v0 = 50;
			triList[92].v1 = 61;
			triList[92].v2 = 51;

			triList[93].v0 = 61;
			triList[93].v1 = 62;
			triList[93].v2 = 51;

			triList[94].v0 = 51;
			triList[94].v1 = 62;
			triList[94].v2 = 52;

			triList[95].v0 = 62;
			triList[95].v1 = 63;
			triList[95].v2 = 52;

			triList[96].v0 = 52;
			triList[96].v1 = 63;
			triList[96].v2 = 53;

			triList[97].v0 = 63;
			triList[97].v1 = 64;
			triList[97].v2 = 53;

			triList[98].v0 = 53;
			triList[98].v1 = 64;
			triList[98].v2 = 54;

			triList[99].v0 = 64;
			triList[99].v1 = 65;
			triList[99].v2 = 54;

			triList[100].v0 = 55;
			triList[100].v1 = 66;
			triList[100].v2 = 56;

			triList[101].v0 = 66;
			triList[101].v1 = 67;
			triList[101].v2 = 56;

			triList[102].v0 = 56;
			triList[102].v1 = 67;
			triList[102].v2 = 57;

			triList[103].v0 = 67;
			triList[103].v1 = 68;
			triList[103].v2 = 57;

			triList[104].v0 = 57;
			triList[104].v1 = 68;
			triList[104].v2 = 58;

			triList[105].v0 = 68;
			triList[105].v1 = 69;
			triList[105].v2 = 58;

			triList[106].v0 = 58;
			triList[106].v1 = 69;
			triList[106].v2 = 59;

			triList[107].v0 = 69;
			triList[107].v1 = 70;
			triList[107].v2 = 59;

			triList[108].v0 = 59;
			triList[108].v1 = 70;
			triList[108].v2 = 60;

			triList[109].v0 = 70;
			triList[109].v1 = 71;
			triList[109].v2 = 60;

			triList[110].v0 = 60;
			triList[110].v1 = 71;
			triList[110].v2 = 61;

			triList[111].v0 = 71;
			triList[111].v1 = 72;
			triList[111].v2 = 61;

			triList[112].v0 = 61;
			triList[112].v1 = 72;
			triList[112].v2 = 62;

			triList[113].v0 = 72;
			triList[113].v1 = 73;
			triList[113].v2 = 62;

			triList[114].v0 = 62;
			triList[114].v1 = 73;
			triList[114].v2 = 63;

			triList[115].v0 = 73;
			triList[115].v1 = 74;
			triList[115].v2 = 63;

			triList[116].v0 = 63;
			triList[116].v1 = 74;
			triList[116].v2 = 64;

			triList[117].v0 = 74;
			triList[117].v1 = 75;
			triList[117].v2 = 64;

			triList[118].v0 = 64;
			triList[118].v1 = 75;
			triList[118].v2 = 65;

			triList[119].v0 = 75;
			triList[119].v1 = 76;
			triList[119].v2 = 65;

			triList[120].v0 = 66;
			triList[120].v1 = 77;
			triList[120].v2 = 67;

			triList[121].v0 = 77;
			triList[121].v1 = 78;
			triList[121].v2 = 67;

			triList[122].v0 = 67;
			triList[122].v1 = 78;
			triList[122].v2 = 68;

			triList[123].v0 = 78;
			triList[123].v1 = 79;
			triList[123].v2 = 68;

			triList[124].v0 = 68;
			triList[124].v1 = 79;
			triList[124].v2 = 69;

			triList[125].v0 = 79;
			triList[125].v1 = 80;
			triList[125].v2 = 69;

			triList[126].v0 = 69;
			triList[126].v1 = 80;
			triList[126].v2 = 70;

			triList[127].v0 = 80;
			triList[127].v1 = 81;
			triList[127].v2 = 70;

			triList[128].v0 = 70;
			triList[128].v1 = 81;
			triList[128].v2 = 71;

			triList[129].v0 = 81;
			triList[129].v1 = 82;
			triList[129].v2 = 71;

			triList[130].v0 = 71;
			triList[130].v1 = 82;
			triList[130].v2 = 72;

			triList[131].v0 = 82;
			triList[131].v1 = 83;
			triList[131].v2 = 72;

			triList[132].v0 = 72;
			triList[132].v1 = 83;
			triList[132].v2 = 73;

			triList[133].v0 = 83;
			triList[133].v1 = 84;
			triList[133].v2 = 73;

			triList[134].v0 = 73;
			triList[134].v1 = 84;
			triList[134].v2 = 74;

			triList[135].v0 = 84;
			triList[135].v1 = 85;
			triList[135].v2 = 74;

			triList[136].v0 = 74;
			triList[136].v1 = 85;
			triList[136].v2 = 75;

			triList[137].v0 = 85;
			triList[137].v1 = 86;
			triList[137].v2 = 75;

			triList[138].v0 = 75;
			triList[138].v1 = 86;
			triList[138].v2 = 76;

			triList[139].v0 = 86;
			triList[139].v1 = 87;
			triList[139].v2 = 76;

			triList[140].v0 = 77;
			triList[140].v1 = 88;
			triList[140].v2 = 78;

			triList[141].v0 = 88;
			triList[141].v1 = 89;
			triList[141].v2 = 78;

			triList[142].v0 = 78;
			triList[142].v1 = 89;
			triList[142].v2 = 79;

			triList[143].v0 = 89;
			triList[143].v1 = 90;
			triList[143].v2 = 79;

			triList[144].v0 = 79;
			triList[144].v1 = 90;
			triList[144].v2 = 80;

			triList[145].v0 = 90;
			triList[145].v1 = 91;
			triList[145].v2 = 80;

			triList[146].v0 = 80;
			triList[146].v1 = 91;
			triList[146].v2 = 81;

			triList[147].v0 = 91;
			triList[147].v1 = 92;
			triList[147].v2 = 81;

			triList[148].v0 = 81;
			triList[148].v1 = 92;
			triList[148].v2 = 82;

			triList[149].v0 = 92;
			triList[149].v1 = 93;
			triList[149].v2 = 82;

			triList[150].v0 = 82;
			triList[150].v1 = 93;
			triList[150].v2 = 83;

			triList[151].v0 = 93;
			triList[151].v1 = 94;
			triList[151].v2 = 83;

			triList[152].v0 = 83;
			triList[152].v1 = 94;
			triList[152].v2 = 84;

			triList[153].v0 = 94;
			triList[153].v1 = 95;
			triList[153].v2 = 84;

			triList[154].v0 = 84;
			triList[154].v1 = 95;
			triList[154].v2 = 85;

			triList[155].v0 = 95;
			triList[155].v1 = 96;
			triList[155].v2 = 85;

			triList[156].v0 = 85;
			triList[156].v1 = 96;
			triList[156].v2 = 86;

			triList[157].v0 = 96;
			triList[157].v1 = 97;
			triList[157].v2 = 86;

			triList[158].v0 = 86;
			triList[158].v1 = 97;
			triList[158].v2 = 87;

			triList[159].v0 = 97;
			triList[159].v1 = 98;
			triList[159].v2 = 87;

			triList[160].v0 = 88;
			triList[160].v1 = 99;
			triList[160].v2 = 89;

			triList[161].v0 = 99;
			triList[161].v1 = 100;
			triList[161].v2 = 89;

			triList[162].v0 = 89;
			triList[162].v1 = 100;
			triList[162].v2 = 90;

			triList[163].v0 = 100;
			triList[163].v1 = 101;
			triList[163].v2 = 90;

			triList[164].v0 = 90;
			triList[164].v1 = 101;
			triList[164].v2 = 91;

			triList[165].v0 = 101;
			triList[165].v1 = 102;
			triList[165].v2 = 91;

			triList[166].v0 = 91;
			triList[166].v1 = 102;
			triList[166].v2 = 92;

			triList[167].v0 = 102;
			triList[167].v1 = 103;
			triList[167].v2 = 92;

			triList[168].v0 = 92;
			triList[168].v1 = 103;
			triList[168].v2 = 93;

			triList[169].v0 = 103;
			triList[169].v1 = 104;
			triList[169].v2 = 93;

			triList[170].v0 = 93;
			triList[170].v1 = 104;
			triList[170].v2 = 94;

			triList[171].v0 = 104;
			triList[171].v1 = 105;
			triList[171].v2 = 94;

			triList[172].v0 = 94;
			triList[172].v1 = 105;
			triList[172].v2 = 95;

			triList[173].v0 = 105;
			triList[173].v1 = 106;
			triList[173].v2 = 95;

			triList[174].v0 = 95;
			triList[174].v1 = 106;
			triList[174].v2 = 96;

			triList[175].v0 = 106;
			triList[175].v1 = 107;
			triList[175].v2 = 96;

			triList[176].v0 = 96;
			triList[176].v1 = 107;
			triList[176].v2 = 97;

			triList[177].v0 = 107;
			triList[177].v1 = 108;
			triList[177].v2 = 97;

			triList[178].v0 = 97;
			triList[178].v1 = 108;
			triList[178].v2 = 98;

			triList[179].v0 = 108;
			triList[179].v1 = 109;
			triList[179].v2 = 98;

			triList[180].v0 = 99;
			triList[180].v1 = 110;
			triList[180].v2 = 100;

			triList[181].v0 = 110;
			triList[181].v1 = 111;
			triList[181].v2 = 100;

			triList[182].v0 = 100;
			triList[182].v1 = 111;
			triList[182].v2 = 101;

			triList[183].v0 = 111;
			triList[183].v1 = 112;
			triList[183].v2 = 101;

			triList[184].v0 = 101;
			triList[184].v1 = 112;
			triList[184].v2 = 102;

			triList[185].v0 = 112;
			triList[185].v1 = 113;
			triList[185].v2 = 102;

			triList[186].v0 = 102;
			triList[186].v1 = 113;
			triList[186].v2 = 103;

			triList[187].v0 = 113;
			triList[187].v1 = 114;
			triList[187].v2 = 103;

			triList[188].v0 = 103;
			triList[188].v1 = 114;
			triList[188].v2 = 104;

			triList[189].v0 = 114;
			triList[189].v1 = 115;
			triList[189].v2 = 104;

			triList[190].v0 = 104;
			triList[190].v1 = 115;
			triList[190].v2 = 105;

			triList[191].v0 = 115;
			triList[191].v1 = 116;
			triList[191].v2 = 105;

			triList[192].v0 = 105;
			triList[192].v1 = 116;
			triList[192].v2 = 106;

			triList[193].v0 = 116;
			triList[193].v1 = 117;
			triList[193].v2 = 106;

			triList[194].v0 = 106;
			triList[194].v1 = 117;
			triList[194].v2 = 107;

			triList[195].v0 = 117;
			triList[195].v1 = 118;
			triList[195].v2 = 107;

			triList[196].v0 = 107;
			triList[196].v1 = 118;
			triList[196].v2 = 108;

			triList[197].v0 = 118;
			triList[197].v1 = 119;
			triList[197].v2 = 108;

			triList[198].v0 = 108;
			triList[198].v1 = 119;
			triList[198].v2 = 109;

			triList[199].v0 = 119;
			triList[199].v1 = 120;
			triList[199].v2 = 109;
		}

		// XYZ
		{
		sphereData_xyz[0].x = 2.0f * -0.000000f;
		sphereData_xyz[0].y = 2.0f * 0.000000f;
		sphereData_xyz[0].z = 2.0f * 0.500000f;

		sphereData_xyz[1].x = 2.0f * -0.000000f;
		sphereData_xyz[1].y = 2.0f * 0.154509f;
		sphereData_xyz[1].z = 2.0f * 0.475528f;

		sphereData_xyz[2].x = 2.0f * -0.000000f;
		sphereData_xyz[2].y = 2.0f * 0.000000f;
		sphereData_xyz[2].z = 2.0f * 0.500000f;

		sphereData_xyz[3].x = 2.0f * -0.090818f;
		sphereData_xyz[3].y = 2.0f * 0.125000f;
		sphereData_xyz[3].z = 2.0f * 0.475528f;

		sphereData_xyz[4].x = 2.0f * -0.000000f;
		sphereData_xyz[4].y = 2.0f * 0.000000f;
		sphereData_xyz[4].z = 2.0f * 0.500000f;

		sphereData_xyz[5].x = 2.0f * -0.146946f;
		sphereData_xyz[5].y = 2.0f * 0.047746f;
		sphereData_xyz[5].z = 2.0f * 0.475528f;

		sphereData_xyz[6].x = 2.0f * -0.000000f;
		sphereData_xyz[6].y = 2.0f * -0.000000f;
		sphereData_xyz[6].z = 2.0f * 0.500000f;

		sphereData_xyz[7].x = 2.0f * -0.146946f;
		sphereData_xyz[7].y = 2.0f * -0.047746f;
		sphereData_xyz[7].z = 2.0f * 0.475528f;

		sphereData_xyz[8].x = 2.0f * -0.000000f;
		sphereData_xyz[8].y = 2.0f * -0.000000f;
		sphereData_xyz[8].z = 2.0f * 0.500000f;

		sphereData_xyz[9].x = 2.0f * -0.090818f;
		sphereData_xyz[9].y = 2.0f * -0.125000f;
		sphereData_xyz[9].z = 2.0f * 0.475528f;

		sphereData_xyz[10].x = 2.0f * 0.000000f;
		sphereData_xyz[10].y = 2.0f * -0.000000f;
		sphereData_xyz[10].z = 2.0f * 0.500000f;

		sphereData_xyz[11].x = 2.0f * 0.000000f;
		sphereData_xyz[11].y = 2.0f * -0.154509f;
		sphereData_xyz[11].z = 2.0f * 0.475528f;

		sphereData_xyz[12].x = 2.0f * 0.000000f;
		sphereData_xyz[12].y = 2.0f * -0.000000f;
		sphereData_xyz[12].z = 2.0f * 0.500000f;

		sphereData_xyz[13].x = 2.0f * 0.090818f;
		sphereData_xyz[13].y = 2.0f * -0.125000f;
		sphereData_xyz[13].z = 2.0f * 0.475528f;

		sphereData_xyz[14].x = 2.0f * 0.000000f;
		sphereData_xyz[14].y = 2.0f * -0.000000f;
		sphereData_xyz[14].z = 2.0f * 0.500000f;

		sphereData_xyz[15].x = 2.0f * 0.146946f;
		sphereData_xyz[15].y = 2.0f * -0.047746f;
		sphereData_xyz[15].z = 2.0f * 0.475528f;

		sphereData_xyz[16].x = 2.0f * 0.000000f;
		sphereData_xyz[16].y = 2.0f * 0.000000f;
		sphereData_xyz[16].z = 2.0f * 0.500000f;

		sphereData_xyz[17].x = 2.0f * 0.146946f;
		sphereData_xyz[17].y = 2.0f * 0.047746f;
		sphereData_xyz[17].z = 2.0f * 0.475528f;

		sphereData_xyz[18].x = 2.0f * 0.000000f;
		sphereData_xyz[18].y = 2.0f * 0.000000f;
		sphereData_xyz[18].z = 2.0f * 0.500000f;

		sphereData_xyz[19].x = 2.0f * 0.090818f;
		sphereData_xyz[19].y = 2.0f * 0.125000f;
		sphereData_xyz[19].z = 2.0f * 0.475528f;

		sphereData_xyz[20].x = 2.0f * -0.000000f;
		sphereData_xyz[20].y = 2.0f * 0.000000f;
		sphereData_xyz[20].z = 2.0f * 0.500000f;

		sphereData_xyz[21].x = 2.0f * -0.000000f;
		sphereData_xyz[21].y = 2.0f * 0.154509f;
		sphereData_xyz[21].z = 2.0f * 0.475528f;

		sphereData_xyz[22].x = 2.0f * -0.000000f;
		sphereData_xyz[22].y = 2.0f * 0.293893f;
		sphereData_xyz[22].z = 2.0f * 0.404509f;

		sphereData_xyz[23].x = 2.0f * -0.172746f;
		sphereData_xyz[23].y = 2.0f * 0.237764f;
		sphereData_xyz[23].z = 2.0f * 0.404509f;

		sphereData_xyz[24].x = 2.0f * -0.279509f;
		sphereData_xyz[24].y = 2.0f * 0.090818f;
		sphereData_xyz[24].z = 2.0f * 0.404509f;

		sphereData_xyz[25].x = 2.0f * -0.279508f;
		sphereData_xyz[25].y = 2.0f * -0.090818f;
		sphereData_xyz[25].z = 2.0f * 0.404509f;

		sphereData_xyz[26].x = 2.0f * -0.172746f;
		sphereData_xyz[26].y = 2.0f * -0.237764f;
		sphereData_xyz[26].z = 2.0f * 0.404509f;

		sphereData_xyz[27].x = 2.0f * 0.000000f;
		sphereData_xyz[27].y = 2.0f * -0.293893f;
		sphereData_xyz[27].z = 2.0f * 0.404509f;

		sphereData_xyz[28].x = 2.0f * 0.172746f;
		sphereData_xyz[28].y = 2.0f * -0.237764f;
		sphereData_xyz[28].z = 2.0f * 0.404509f;

		sphereData_xyz[29].x = 2.0f * 0.279508f;
		sphereData_xyz[29].y = 2.0f * -0.090818f;
		sphereData_xyz[29].z = 2.0f * 0.404509f;

		sphereData_xyz[30].x = 2.0f * 0.279508f;
		sphereData_xyz[30].y = 2.0f * 0.090818f;
		sphereData_xyz[30].z = 2.0f * 0.404509f;

		sphereData_xyz[31].x = 2.0f * 0.172746f;
		sphereData_xyz[31].y = 2.0f * 0.237764f;
		sphereData_xyz[31].z = 2.0f * 0.404509f;

		sphereData_xyz[32].x = 2.0f * -0.000000f;
		sphereData_xyz[32].y = 2.0f * 0.293893f;
		sphereData_xyz[32].z = 2.0f * 0.404509f;

		sphereData_xyz[33].x = 2.0f * -0.000000f;
		sphereData_xyz[33].y = 2.0f * 0.404509f;
		sphereData_xyz[33].z = 2.0f * 0.293893f;

		sphereData_xyz[34].x = 2.0f * -0.237764f;
		sphereData_xyz[34].y = 2.0f * 0.327254f;
		sphereData_xyz[34].z = 2.0f * 0.293893f;

		sphereData_xyz[35].x = 2.0f * -0.384710f;
		sphereData_xyz[35].y = 2.0f * 0.125000f;
		sphereData_xyz[35].z = 2.0f * 0.293893f;

		sphereData_xyz[36].x = 2.0f * -0.384710f;
		sphereData_xyz[36].y = 2.0f * -0.125000f;
		sphereData_xyz[36].z = 2.0f * 0.293893f;

		sphereData_xyz[37].x = 2.0f * -0.237764f;
		sphereData_xyz[37].y = 2.0f * -0.327254f;
		sphereData_xyz[37].z = 2.0f * 0.293893f;

		sphereData_xyz[38].x = 2.0f * 0.000000f;
		sphereData_xyz[38].y = 2.0f * -0.404509f;
		sphereData_xyz[38].z = 2.0f * 0.293893f;

		sphereData_xyz[39].x = 2.0f * 0.237764f;
		sphereData_xyz[39].y = 2.0f * -0.327254f;
		sphereData_xyz[39].z = 2.0f * 0.293893f;

		sphereData_xyz[40].x = 2.0f * 0.384710f;
		sphereData_xyz[40].y = 2.0f * -0.125000f;
		sphereData_xyz[40].z = 2.0f * 0.293893f;

		sphereData_xyz[41].x = 2.0f * 0.384710f;
		sphereData_xyz[41].y = 2.0f * 0.125000f;
		sphereData_xyz[41].z = 2.0f * 0.293893f;

		sphereData_xyz[42].x = 2.0f * 0.237764f;
		sphereData_xyz[42].y = 2.0f * 0.327254f;
		sphereData_xyz[42].z = 2.0f * 0.293893f;

		sphereData_xyz[43].x = 2.0f * -0.000000f;
		sphereData_xyz[43].y = 2.0f * 0.404509f;
		sphereData_xyz[43].z = 2.0f * 0.293893f;

		sphereData_xyz[44].x = 2.0f * -0.000000f;
		sphereData_xyz[44].y = 2.0f * 0.475528f;
		sphereData_xyz[44].z = 2.0f * 0.154508f;

		sphereData_xyz[45].x = 2.0f * -0.279509f;
		sphereData_xyz[45].y = 2.0f * 0.384710f;
		sphereData_xyz[45].z = 2.0f * 0.154508f;

		sphereData_xyz[46].x = 2.0f * -0.452254f;
		sphereData_xyz[46].y = 2.0f * 0.146946f;
		sphereData_xyz[46].z = 2.0f * 0.154508f;

		sphereData_xyz[47].x = 2.0f * -0.452254f;
		sphereData_xyz[47].y = 2.0f * -0.146946f;
		sphereData_xyz[47].z = 2.0f * 0.154508f;

		sphereData_xyz[48].x = 2.0f * -0.279508f;
		sphereData_xyz[48].y = 2.0f * -0.384710f;
		sphereData_xyz[48].z = 2.0f * 0.154508f;

		sphereData_xyz[49].x = 2.0f * 0.000000f;
		sphereData_xyz[49].y = 2.0f * -0.475528f;
		sphereData_xyz[49].z = 2.0f * 0.154508f;

		sphereData_xyz[50].x = 2.0f * 0.279509f;
		sphereData_xyz[50].y = 2.0f * -0.384710f;
		sphereData_xyz[50].z = 2.0f * 0.154508f;

		sphereData_xyz[51].x = 2.0f * 0.452254f;
		sphereData_xyz[51].y = 2.0f * -0.146946f;
		sphereData_xyz[51].z = 2.0f * 0.154508f;

		sphereData_xyz[52].x = 2.0f * 0.452254f;
		sphereData_xyz[52].y = 2.0f * 0.146946f;
		sphereData_xyz[52].z = 2.0f * 0.154508f;

		sphereData_xyz[53].x = 2.0f * 0.279508f;
		sphereData_xyz[53].y = 2.0f * 0.384711f;
		sphereData_xyz[53].z = 2.0f * 0.154508f;

		sphereData_xyz[54].x = 2.0f * -0.000000f;
		sphereData_xyz[54].y = 2.0f * 0.475528f;
		sphereData_xyz[54].z = 2.0f * 0.154508f;

		sphereData_xyz[55].x = 2.0f * -0.000000f;
		sphereData_xyz[55].y = 2.0f * 0.500000f;
		sphereData_xyz[55].z = 2.0f * -0.000000f;

		sphereData_xyz[56].x = 2.0f * -0.293893f;
		sphereData_xyz[56].y = 2.0f * 0.404509f;
		sphereData_xyz[56].z = 2.0f * -0.000000f;

		sphereData_xyz[57].x = 2.0f * -0.475528f;
		sphereData_xyz[57].y = 2.0f * 0.154508f;
		sphereData_xyz[57].z = 2.0f * -0.000000f;

		sphereData_xyz[58].x = 2.0f * -0.475528f;
		sphereData_xyz[58].y = 2.0f * -0.154509f;
		sphereData_xyz[58].z = 2.0f * -0.000000f;

		sphereData_xyz[59].x = 2.0f * -0.293893f;
		sphereData_xyz[59].y = 2.0f * -0.404509f;
		sphereData_xyz[59].z = 2.0f * -0.000000f;

		sphereData_xyz[60].x = 2.0f * 0.000000f;
		sphereData_xyz[60].y = 2.0f * -0.500000f;
		sphereData_xyz[60].z = 2.0f * -0.000000f;

		sphereData_xyz[61].x = 2.0f * 0.293893f;
		sphereData_xyz[61].y = 2.0f * -0.404508f;
		sphereData_xyz[61].z = 2.0f * -0.000000f;

		sphereData_xyz[62].x = 2.0f * 0.475528f;
		sphereData_xyz[62].y = 2.0f * -0.154509f;
		sphereData_xyz[62].z = 2.0f * -0.000000f;

		sphereData_xyz[63].x = 2.0f * 0.475528f;
		sphereData_xyz[63].y = 2.0f * 0.154509f;
		sphereData_xyz[63].z = 2.0f * -0.000000f;

		sphereData_xyz[64].x = 2.0f * 0.293892f;
		sphereData_xyz[64].y = 2.0f * 0.404509f;
		sphereData_xyz[64].z = 2.0f * -0.000000f;

		sphereData_xyz[65].x = 2.0f * -0.000000f;
		sphereData_xyz[65].y = 2.0f * 0.500000f;
		sphereData_xyz[65].z = 2.0f * -0.000000f;

		sphereData_xyz[66].x = 2.0f * -0.000000f;
		sphereData_xyz[66].y = 2.0f * 0.475528f;
		sphereData_xyz[66].z = 2.0f * -0.154509f;

		sphereData_xyz[67].x = 2.0f * -0.279508f;
		sphereData_xyz[67].y = 2.0f * 0.384710f;
		sphereData_xyz[67].z = 2.0f * -0.154509f;

		sphereData_xyz[68].x = 2.0f * -0.452254f;
		sphereData_xyz[68].y = 2.0f * 0.146946f;
		sphereData_xyz[68].z = 2.0f * -0.154509f;

		sphereData_xyz[69].x = 2.0f * -0.452254f;
		sphereData_xyz[69].y = 2.0f * -0.146946f;
		sphereData_xyz[69].z = 2.0f * -0.154509f;

		sphereData_xyz[70].x = 2.0f * -0.279508f;
		sphereData_xyz[70].y = 2.0f * -0.384710f;
		sphereData_xyz[70].z = 2.0f * -0.154509f;

		sphereData_xyz[71].x = 2.0f * 0.000000f;
		sphereData_xyz[71].y = 2.0f * -0.475528f;
		sphereData_xyz[71].z = 2.0f * -0.154509f;

		sphereData_xyz[72].x = 2.0f * 0.279509f;
		sphereData_xyz[72].y = 2.0f * -0.384710f;
		sphereData_xyz[72].z = 2.0f * -0.154509f;

		sphereData_xyz[73].x = 2.0f * 0.452254f;
		sphereData_xyz[73].y = 2.0f * -0.146946f;
		sphereData_xyz[73].z = 2.0f * -0.154509f;

		sphereData_xyz[74].x = 2.0f * 0.452254f;
		sphereData_xyz[74].y = 2.0f * 0.146946f;
		sphereData_xyz[74].z = 2.0f * -0.154509f;

		sphereData_xyz[75].x = 2.0f * 0.279508f;
		sphereData_xyz[75].y = 2.0f * 0.384711f;
		sphereData_xyz[75].z = 2.0f * -0.154509f;

		sphereData_xyz[76].x = 2.0f * -0.000000f;
		sphereData_xyz[76].y = 2.0f * 0.475528f;
		sphereData_xyz[76].z = 2.0f * -0.154509f;

		sphereData_xyz[77].x = 2.0f * -0.000000f;
		sphereData_xyz[77].y = 2.0f * 0.404509f;
		sphereData_xyz[77].z = 2.0f * -0.293893f;

		sphereData_xyz[78].x = 2.0f * -0.237764f;
		sphereData_xyz[78].y = 2.0f * 0.327254f;
		sphereData_xyz[78].z = 2.0f * -0.293893f;

		sphereData_xyz[79].x = 2.0f * -0.384710f;
		sphereData_xyz[79].y = 2.0f * 0.125000f;
		sphereData_xyz[79].z = 2.0f * -0.293893f;

		sphereData_xyz[80].x = 2.0f * -0.384710f;
		sphereData_xyz[80].y = 2.0f * -0.125000f;
		sphereData_xyz[80].z = 2.0f * -0.293893f;

		sphereData_xyz[81].x = 2.0f * -0.237764f;
		sphereData_xyz[81].y = 2.0f * -0.327254f;
		sphereData_xyz[81].z = 2.0f * -0.293893f;

		sphereData_xyz[82].x = 2.0f * 0.000000f;
		sphereData_xyz[82].y = 2.0f * -0.404509f;
		sphereData_xyz[82].z = 2.0f * -0.293893f;

		sphereData_xyz[83].x = 2.0f * 0.237764f;
		sphereData_xyz[83].y = 2.0f * -0.327254f;
		sphereData_xyz[83].z = 2.0f * -0.293893f;

		sphereData_xyz[84].x = 2.0f * 0.384710f;
		sphereData_xyz[84].y = 2.0f * -0.125000f;
		sphereData_xyz[84].z = 2.0f * -0.293893f;

		sphereData_xyz[85].x = 2.0f * 0.384710f;
		sphereData_xyz[85].y = 2.0f * 0.125000f;
		sphereData_xyz[85].z = 2.0f * -0.293893f;

		sphereData_xyz[86].x = 2.0f * 0.237764f;
		sphereData_xyz[86].y = 2.0f * 0.327254f;
		sphereData_xyz[86].z = 2.0f * -0.293893f;

		sphereData_xyz[87].x = 2.0f * -0.000000f;
		sphereData_xyz[87].y = 2.0f * 0.404509f;
		sphereData_xyz[87].z = 2.0f * -0.293893f;

		sphereData_xyz[88].x = 2.0f * -0.000000f;
		sphereData_xyz[88].y = 2.0f * 0.293893f;
		sphereData_xyz[88].z = 2.0f * -0.404509f;

		sphereData_xyz[89].x = 2.0f * -0.172746f;
		sphereData_xyz[89].y = 2.0f * 0.237764f;
		sphereData_xyz[89].z = 2.0f * -0.404509f;

		sphereData_xyz[90].x = 2.0f * -0.279508f;
		sphereData_xyz[90].y = 2.0f * 0.090818f;
		sphereData_xyz[90].z = 2.0f * -0.404509f;

		sphereData_xyz[91].x = 2.0f * -0.279508f;
		sphereData_xyz[91].y = 2.0f * -0.090818f;
		sphereData_xyz[91].z = 2.0f * -0.404509f;

		sphereData_xyz[92].x = 2.0f * -0.172746f;
		sphereData_xyz[92].y = 2.0f * -0.237764f;
		sphereData_xyz[92].z = 2.0f * -0.404509f;

		sphereData_xyz[93].x = 2.0f * 0.000000f;
		sphereData_xyz[93].y = 2.0f * -0.293893f;
		sphereData_xyz[93].z = 2.0f * -0.404509f;

		sphereData_xyz[94].x = 2.0f * 0.172746f;
		sphereData_xyz[94].y = 2.0f * -0.237764f;
		sphereData_xyz[94].z = 2.0f * -0.404509f;

		sphereData_xyz[95].x = 2.0f * 0.279508f;
		sphereData_xyz[95].y = 2.0f * -0.090818f;
		sphereData_xyz[95].z = 2.0f * -0.404509f;

		sphereData_xyz[96].x = 2.0f * 0.279508f;
		sphereData_xyz[96].y = 2.0f * 0.090818f;
		sphereData_xyz[96].z = 2.0f * -0.404509f;

		sphereData_xyz[97].x = 2.0f * 0.172746f;
		sphereData_xyz[97].y = 2.0f * 0.237764f;
		sphereData_xyz[97].z = 2.0f * -0.404509f;

		sphereData_xyz[98].x = 2.0f * -0.000000f;
		sphereData_xyz[98].y = 2.0f * 0.293893f;
		sphereData_xyz[98].z = 2.0f * -0.404509f;

		sphereData_xyz[99].x = 2.0f * -0.000000f;
		sphereData_xyz[99].y = 2.0f * 0.154508f;
		sphereData_xyz[99].z = 2.0f * -0.475528f;

		sphereData_xyz[100].x = 2.0f * -0.090818f;
		sphereData_xyz[100].y = 2.0f * 0.125000f;
		sphereData_xyz[100].z = 2.0f * -0.475528f;

		sphereData_xyz[101].x = 2.0f * -0.146946f;
		sphereData_xyz[101].y = 2.0f * 0.047746f;
		sphereData_xyz[101].z = 2.0f * -0.475528f;

		sphereData_xyz[102].x = 2.0f * -0.146946f;
		sphereData_xyz[102].y = 2.0f * -0.047746f;
		sphereData_xyz[102].z = 2.0f * -0.475528f;

		sphereData_xyz[103].x = 2.0f * -0.090818f;
		sphereData_xyz[103].y = 2.0f * -0.125000f;
		sphereData_xyz[103].z = 2.0f * -0.475528f;

		sphereData_xyz[104].x = 2.0f * 0.000000f;
		sphereData_xyz[104].y = 2.0f * -0.154508f;
		sphereData_xyz[104].z = 2.0f * -0.475528f;

		sphereData_xyz[105].x = 2.0f * 0.090818f;
		sphereData_xyz[105].y = 2.0f * -0.125000f;
		sphereData_xyz[105].z = 2.0f * -0.475528f;

		sphereData_xyz[106].x = 2.0f * 0.146946f;
		sphereData_xyz[106].y = 2.0f * -0.047746f;
		sphereData_xyz[106].z = 2.0f * -0.475528f;

		sphereData_xyz[107].x = 2.0f * 0.146946f;
		sphereData_xyz[107].y = 2.0f * 0.047746f;
		sphereData_xyz[107].z = 2.0f * -0.475528f;

		sphereData_xyz[108].x = 2.0f * 0.090818f;
		sphereData_xyz[108].y = 2.0f * 0.125000f;
		sphereData_xyz[108].z = 2.0f * -0.475528f;

		sphereData_xyz[109].x = 2.0f * -0.000000f;
		sphereData_xyz[109].y = 2.0f * 0.154508f;
		sphereData_xyz[109].z = 2.0f * -0.475528f;

		sphereData_xyz[110].x = 2.0f * 0.000000f;
		sphereData_xyz[110].y = 2.0f * -0.000000f;
		sphereData_xyz[110].z = 2.0f * -0.500000f;

		sphereData_xyz[111].x = 2.0f * 0.000000f;
		sphereData_xyz[111].y = 2.0f * -0.000000f;
		sphereData_xyz[111].z = 2.0f * -0.500000f;

		sphereData_xyz[112].x = 2.0f * 0.000000f;
		sphereData_xyz[112].y = 2.0f * -0.000000f;
		sphereData_xyz[112].z = 2.0f * -0.500000f;

		sphereData_xyz[113].x = 2.0f * 0.000000f;
		sphereData_xyz[113].y = 2.0f * 0.000000f;
		sphereData_xyz[113].z = 2.0f * -0.500000f;

		sphereData_xyz[114].x = 2.0f * 0.000000f;
		sphereData_xyz[114].y = 2.0f * 0.000000f;
		sphereData_xyz[114].z = 2.0f * -0.500000f;

		sphereData_xyz[115].x = 2.0f * -0.000000f;
		sphereData_xyz[115].y = 2.0f * 0.000000f;
		sphereData_xyz[115].z = 2.0f * -0.500000f;

		sphereData_xyz[116].x = 2.0f * -0.000000f;
		sphereData_xyz[116].y = 2.0f * 0.000000f;
		sphereData_xyz[116].z = 2.0f * -0.500000f;

		sphereData_xyz[117].x = 2.0f * -0.000000f;
		sphereData_xyz[117].y = 2.0f * 0.000000f;
		sphereData_xyz[117].z = 2.0f * -0.500000f;

		sphereData_xyz[118].x = 2.0f * -0.000000f;
		sphereData_xyz[118].y = 2.0f * -0.000000f;
		sphereData_xyz[118].z = 2.0f * -0.500000f;

		sphereData_xyz[119].x = 2.0f * -0.000000f;
		sphereData_xyz[119].y = 2.0f * -0.000000f;
		sphereData_xyz[119].z = 2.0f * -0.500000f;

		sphereData_xyz[120].x = 2.0f * 0.000000f;
		sphereData_xyz[120].y = 2.0f * -0.000000f;
		sphereData_xyz[120].z = 2.0f * -0.500000f;

		}

		{

			sphereData_nxnynz[0].nx = -0.000000f;
			sphereData_nxnynz[0].ny = 0.000000f;
			sphereData_nxnynz[0].nz = 1.000000f;

			sphereData_nxnynz[1].nx = -0.000000f;
			sphereData_nxnynz[1].ny = 0.309017f;
			sphereData_nxnynz[1].nz = 0.951057f;

			sphereData_nxnynz[2].nx = -0.000000f;
			sphereData_nxnynz[2].ny = 0.000000f;
			sphereData_nxnynz[2].nz = 1.000000f;

			sphereData_nxnynz[3].nx = -0.181636f;
			sphereData_nxnynz[3].ny = 0.250000f;
			sphereData_nxnynz[3].nz = 0.951057f;

			sphereData_nxnynz[4].nx = -0.000000f;
			sphereData_nxnynz[4].ny = 0.000000f;
			sphereData_nxnynz[4].nz = 1.000000f;

			sphereData_nxnynz[5].nx = -0.293893f;
			sphereData_nxnynz[5].ny = 0.095491f;
			sphereData_nxnynz[5].nz = 0.951057f;

			sphereData_nxnynz[6].nx = -0.000000f;
			sphereData_nxnynz[6].ny = -0.000000f;
			sphereData_nxnynz[6].nz = 1.000000f;

			sphereData_nxnynz[7].nx = -0.293893f;
			sphereData_nxnynz[7].ny = -0.095492f;
			sphereData_nxnynz[7].nz = 0.951057f;

			sphereData_nxnynz[8].nx = -0.000000f;
			sphereData_nxnynz[8].ny = -0.000000f;
			sphereData_nxnynz[8].nz = 1.000000f;

			sphereData_nxnynz[9].nx = -0.181636f;
			sphereData_nxnynz[9].ny = -0.250000f;
			sphereData_nxnynz[9].nz = 0.951057f;

			sphereData_nxnynz[10].nx = 0.000000f;
			sphereData_nxnynz[10].ny = -0.000000f;
			sphereData_nxnynz[10].nz = 1.000000f;

			sphereData_nxnynz[11].nx = 0.000000f;
			sphereData_nxnynz[11].ny = -0.309017f;
			sphereData_nxnynz[11].nz = 0.951057f;

			sphereData_nxnynz[12].nx = 0.000000f;
			sphereData_nxnynz[12].ny = -0.000000f;
			sphereData_nxnynz[12].nz = 1.000000f;

			sphereData_nxnynz[13].nx = 0.181636f;
			sphereData_nxnynz[13].ny = -0.250000f;
			sphereData_nxnynz[13].nz = 0.951057f;

			sphereData_nxnynz[14].nx = 0.000000f;
			sphereData_nxnynz[14].ny = -0.000000f;
			sphereData_nxnynz[14].nz = 1.000000f;

			sphereData_nxnynz[15].nx = 0.293893f;
			sphereData_nxnynz[15].ny = -0.095492f;
			sphereData_nxnynz[15].nz = 0.951057f;

			sphereData_nxnynz[16].nx = 0.000000f;
			sphereData_nxnynz[16].ny = 0.000000f;
			sphereData_nxnynz[16].nz = 1.000000f;

			sphereData_nxnynz[17].nx = 0.293893f;
			sphereData_nxnynz[17].ny = 0.095492f;
			sphereData_nxnynz[17].nz = 0.951057f;

			sphereData_nxnynz[18].nx = 0.000000f;
			sphereData_nxnynz[18].ny = 0.000000f;
			sphereData_nxnynz[18].nz = 1.000000f;

			sphereData_nxnynz[19].nx = 0.181636f;
			sphereData_nxnynz[19].ny = 0.250000f;
			sphereData_nxnynz[19].nz = 0.951057f;

			sphereData_nxnynz[20].nx = -0.000000f;
			sphereData_nxnynz[20].ny = 0.000000f;
			sphereData_nxnynz[20].nz = 1.000000f;

			sphereData_nxnynz[21].nx = -0.000000f;
			sphereData_nxnynz[21].ny = 0.309017f;
			sphereData_nxnynz[21].nz = 0.951057f;

			sphereData_nxnynz[22].nx = -0.000000f;
			sphereData_nxnynz[22].ny = 0.587785f;
			sphereData_nxnynz[22].nz = 0.809017f;

			sphereData_nxnynz[23].nx = -0.345491f;
			sphereData_nxnynz[23].ny = 0.475528f;
			sphereData_nxnynz[23].nz = 0.809017f;

			sphereData_nxnynz[24].nx = -0.559017f;
			sphereData_nxnynz[24].ny = 0.181636f;
			sphereData_nxnynz[24].nz = 0.809017f;

			sphereData_nxnynz[25].nx = -0.559017f;
			sphereData_nxnynz[25].ny = -0.181636f;
			sphereData_nxnynz[25].nz = 0.809017f;

			sphereData_nxnynz[26].nx = -0.345491f;
			sphereData_nxnynz[26].ny = -0.475528f;
			sphereData_nxnynz[26].nz = 0.809017f;

			sphereData_nxnynz[27].nx = 0.000000f;
			sphereData_nxnynz[27].ny = -0.587785f;
			sphereData_nxnynz[27].nz = 0.809017f;

			sphereData_nxnynz[28].nx = 0.345492f;
			sphereData_nxnynz[28].ny = -0.475528f;
			sphereData_nxnynz[28].nz = 0.809017f;

			sphereData_nxnynz[29].nx = 0.559017f;
			sphereData_nxnynz[29].ny = -0.181636f;
			sphereData_nxnynz[29].nz = 0.809017f;

			sphereData_nxnynz[30].nx = 0.559017f;
			sphereData_nxnynz[30].ny = 0.181636f;
			sphereData_nxnynz[30].nz = 0.809017f;

			sphereData_nxnynz[31].nx = 0.345491f;
			sphereData_nxnynz[31].ny = 0.475528f;
			sphereData_nxnynz[31].nz = 0.809017f;

			sphereData_nxnynz[32].nx = -0.000000f;
			sphereData_nxnynz[32].ny = 0.587785f;
			sphereData_nxnynz[32].nz = 0.809017f;

			sphereData_nxnynz[33].nx = -0.000000f;
			sphereData_nxnynz[33].ny = 0.809017f;
			sphereData_nxnynz[33].nz = 0.587785f;

			sphereData_nxnynz[34].nx = -0.475528f;
			sphereData_nxnynz[34].ny = 0.654509f;
			sphereData_nxnynz[34].nz = 0.587785f;

			sphereData_nxnynz[35].nx = -0.769421f;
			sphereData_nxnynz[35].ny = 0.250000f;
			sphereData_nxnynz[35].nz = 0.587785f;

			sphereData_nxnynz[36].nx = -0.769421f;
			sphereData_nxnynz[36].ny = -0.250000f;
			sphereData_nxnynz[36].nz = 0.587785f;

			sphereData_nxnynz[37].nx = -0.475528f;
			sphereData_nxnynz[37].ny = -0.654509f;
			sphereData_nxnynz[37].nz = 0.587785f;

			sphereData_nxnynz[38].nx = 0.000000f;
			sphereData_nxnynz[38].ny = -0.809017f;
			sphereData_nxnynz[38].nz = 0.587785f;

			sphereData_nxnynz[39].nx = 0.475528f;
			sphereData_nxnynz[39].ny = -0.654508f;
			sphereData_nxnynz[39].nz = 0.587785f;

			sphereData_nxnynz[40].nx = 0.769421f;
			sphereData_nxnynz[40].ny = -0.250000f;
			sphereData_nxnynz[40].nz = 0.587785f;

			sphereData_nxnynz[41].nx = 0.769421f;
			sphereData_nxnynz[41].ny = 0.250000f;
			sphereData_nxnynz[41].nz = 0.587785f;

			sphereData_nxnynz[42].nx = 0.475528f;
			sphereData_nxnynz[42].ny = 0.654509f;
			sphereData_nxnynz[42].nz = 0.587785f;

			sphereData_nxnynz[43].nx = -0.000000f;
			sphereData_nxnynz[43].ny = 0.809017f;
			sphereData_nxnynz[43].nz = 0.587785f;

			sphereData_nxnynz[44].nx = -0.000000f;
			sphereData_nxnynz[44].ny = 0.951057f;
			sphereData_nxnynz[44].nz = 0.309017f;

			sphereData_nxnynz[45].nx = -0.559017f;
			sphereData_nxnynz[45].ny = 0.769421f;
			sphereData_nxnynz[45].nz = 0.309017f;

			sphereData_nxnynz[46].nx = -0.904509f;
			sphereData_nxnynz[46].ny = 0.293893f;
			sphereData_nxnynz[46].nz = 0.309017f;

			sphereData_nxnynz[47].nx = -0.904508f;
			sphereData_nxnynz[47].ny = -0.293893f;
			sphereData_nxnynz[47].nz = 0.309017f;

			sphereData_nxnynz[48].nx = -0.559017f;
			sphereData_nxnynz[48].ny = -0.769421f;
			sphereData_nxnynz[48].nz = 0.309017f;

			sphereData_nxnynz[49].nx = 0.000000f;
			sphereData_nxnynz[49].ny = -0.951057f;
			sphereData_nxnynz[49].nz = 0.309017f;

			sphereData_nxnynz[50].nx = 0.559017f;
			sphereData_nxnynz[50].ny = -0.769421f;
			sphereData_nxnynz[50].nz = 0.309017f;

			sphereData_nxnynz[51].nx = 0.904508f;
			sphereData_nxnynz[51].ny = -0.293893f;
			sphereData_nxnynz[51].nz = 0.309017f;

			sphereData_nxnynz[52].nx = 0.904508f;
			sphereData_nxnynz[52].ny = 0.293893f;
			sphereData_nxnynz[52].nz = 0.309017f;

			sphereData_nxnynz[53].nx = 0.559017f;
			sphereData_nxnynz[53].ny = 0.769421f;
			sphereData_nxnynz[53].nz = 0.309017f;

			sphereData_nxnynz[54].nx = -0.000000f;
			sphereData_nxnynz[54].ny = 0.951057f;
			sphereData_nxnynz[54].nz = 0.309017f;

			sphereData_nxnynz[55].nx = -0.000000f;
			sphereData_nxnynz[55].ny = 1.000000f;
			sphereData_nxnynz[55].nz = -0.000000f;

			sphereData_nxnynz[56].nx = -0.587785f;
			sphereData_nxnynz[56].ny = 0.809017f;
			sphereData_nxnynz[56].nz = -0.000000f;

			sphereData_nxnynz[57].nx = -0.951057f;
			sphereData_nxnynz[57].ny = 0.309017f;
			sphereData_nxnynz[57].nz = -0.000000f;

			sphereData_nxnynz[58].nx = -0.951057f;
			sphereData_nxnynz[58].ny = -0.309017f;
			sphereData_nxnynz[58].nz = -0.000000f;

			sphereData_nxnynz[59].nx = -0.587785f;
			sphereData_nxnynz[59].ny = -0.809017f;
			sphereData_nxnynz[59].nz = -0.000000f;

			sphereData_nxnynz[60].nx = 0.000000f;
			sphereData_nxnynz[60].ny = -1.000000f;
			sphereData_nxnynz[60].nz = -0.000000f;

			sphereData_nxnynz[61].nx = 0.587785f;
			sphereData_nxnynz[61].ny = -0.809017f;
			sphereData_nxnynz[61].nz = -0.000000f;

			sphereData_nxnynz[62].nx = 0.951056f;
			sphereData_nxnynz[62].ny = -0.309017f;
			sphereData_nxnynz[62].nz = -0.000000f;

			sphereData_nxnynz[63].nx = 0.951056f;
			sphereData_nxnynz[63].ny = 0.309017f;
			sphereData_nxnynz[63].nz = -0.000000f;

			sphereData_nxnynz[64].nx = 0.587785f;
			sphereData_nxnynz[64].ny = 0.809017f;
			sphereData_nxnynz[64].nz = -0.000000f;

			sphereData_nxnynz[65].nx = -0.000000f;
			sphereData_nxnynz[65].ny = 1.000000f;
			sphereData_nxnynz[65].nz = -0.000000f;

			sphereData_nxnynz[66].nx = -0.000000f;
			sphereData_nxnynz[66].ny = 0.951057f;
			sphereData_nxnynz[66].nz = -0.309017f;

			sphereData_nxnynz[67].nx = -0.559017f;
			sphereData_nxnynz[67].ny = 0.769421f;
			sphereData_nxnynz[67].nz = -0.309017f;

			sphereData_nxnynz[68].nx = -0.904509f;
			sphereData_nxnynz[68].ny = 0.293893f;
			sphereData_nxnynz[68].nz = -0.309017f;

			sphereData_nxnynz[69].nx = -0.904509f;
			sphereData_nxnynz[69].ny = -0.293893f;
			sphereData_nxnynz[69].nz = -0.309017f;

			sphereData_nxnynz[70].nx = -0.559017f;
			sphereData_nxnynz[70].ny = -0.769421f;
			sphereData_nxnynz[70].nz = -0.309017f;

			sphereData_nxnynz[71].nx = 0.000000f;
			sphereData_nxnynz[71].ny = -0.951057f;
			sphereData_nxnynz[71].nz = -0.309017f;

			sphereData_nxnynz[72].nx = 0.559017f;
			sphereData_nxnynz[72].ny = -0.769421f;
			sphereData_nxnynz[72].nz = -0.309017f;

			sphereData_nxnynz[73].nx = 0.904509f;
			sphereData_nxnynz[73].ny = -0.293893f;
			sphereData_nxnynz[73].nz = -0.309017f;

			sphereData_nxnynz[74].nx = 0.904509f;
			sphereData_nxnynz[74].ny = 0.293893f;
			sphereData_nxnynz[74].nz = -0.309017f;

			sphereData_nxnynz[75].nx = 0.559017f;
			sphereData_nxnynz[75].ny = 0.769421f;
			sphereData_nxnynz[75].nz = -0.309017f;

			sphereData_nxnynz[76].nx = -0.000000f;
			sphereData_nxnynz[76].ny = 0.951057f;
			sphereData_nxnynz[76].nz = -0.309017f;

			sphereData_nxnynz[77].nx = -0.000000f;
			sphereData_nxnynz[77].ny = 0.809017f;
			sphereData_nxnynz[77].nz = -0.587785f;

			sphereData_nxnynz[78].nx = -0.475528f;
			sphereData_nxnynz[78].ny = 0.654509f;
			sphereData_nxnynz[78].nz = -0.587785f;

			sphereData_nxnynz[79].nx = -0.769421f;
			sphereData_nxnynz[79].ny = 0.250000f;
			sphereData_nxnynz[79].nz = -0.587785f;

			sphereData_nxnynz[80].nx = -0.769421f;
			sphereData_nxnynz[80].ny = -0.250000f;
			sphereData_nxnynz[80].nz = -0.587785f;

			sphereData_nxnynz[81].nx = -0.475528f;
			sphereData_nxnynz[81].ny = -0.654509f;
			sphereData_nxnynz[81].nz = -0.587785f;

			sphereData_nxnynz[82].nx = 0.000000f;
			sphereData_nxnynz[82].ny = -0.809017f;
			sphereData_nxnynz[82].nz = -0.587785f;

			sphereData_nxnynz[83].nx = 0.475528f;
			sphereData_nxnynz[83].ny = -0.654508f;
			sphereData_nxnynz[83].nz = -0.587785f;

			sphereData_nxnynz[84].nx = 0.769421f;
			sphereData_nxnynz[84].ny = -0.250000f;
			sphereData_nxnynz[84].nz = -0.587785f;

			sphereData_nxnynz[85].nx = 0.769421f;
			sphereData_nxnynz[85].ny = 0.250000f;
			sphereData_nxnynz[85].nz = -0.587785f;

			sphereData_nxnynz[86].nx = 0.475528f;
			sphereData_nxnynz[86].ny = 0.654509f;
			sphereData_nxnynz[86].nz = -0.587785f;

			sphereData_nxnynz[87].nx = -0.000000f;
			sphereData_nxnynz[87].ny = 0.809017f;
			sphereData_nxnynz[87].nz = -0.587785f;

			sphereData_nxnynz[88].nx = -0.000000f;
			sphereData_nxnynz[88].ny = 0.587785f;
			sphereData_nxnynz[88].nz = -0.809017f;

			sphereData_nxnynz[89].nx = -0.345491f;
			sphereData_nxnynz[89].ny = 0.475528f;
			sphereData_nxnynz[89].nz = -0.809017f;

			sphereData_nxnynz[90].nx = -0.559017f;
			sphereData_nxnynz[90].ny = 0.181636f;
			sphereData_nxnynz[90].nz = -0.809017f;

			sphereData_nxnynz[91].nx = -0.559017f;
			sphereData_nxnynz[91].ny = -0.181636f;
			sphereData_nxnynz[91].nz = -0.809017f;

			sphereData_nxnynz[92].nx = -0.345491f;
			sphereData_nxnynz[92].ny = -0.475528f;
			sphereData_nxnynz[92].nz = -0.809017f;

			sphereData_nxnynz[93].nx = 0.000000f;
			sphereData_nxnynz[93].ny = -0.587785f;
			sphereData_nxnynz[93].nz = -0.809017f;

			sphereData_nxnynz[94].nx = 0.345492f;
			sphereData_nxnynz[94].ny = -0.475528f;
			sphereData_nxnynz[94].nz = -0.809017f;

			sphereData_nxnynz[95].nx = 0.559017f;
			sphereData_nxnynz[95].ny = -0.181636f;
			sphereData_nxnynz[95].nz = -0.809017f;

			sphereData_nxnynz[96].nx = 0.559017f;
			sphereData_nxnynz[96].ny = 0.181636f;
			sphereData_nxnynz[96].nz = -0.809017f;

			sphereData_nxnynz[97].nx = 0.345491f;
			sphereData_nxnynz[97].ny = 0.475528f;
			sphereData_nxnynz[97].nz = -0.809017f;

			sphereData_nxnynz[98].nx = -0.000000f;
			sphereData_nxnynz[98].ny = 0.587785f;
			sphereData_nxnynz[98].nz = -0.809017f;

			sphereData_nxnynz[99].nx = -0.000000f;
			sphereData_nxnynz[99].ny = 0.309017f;
			sphereData_nxnynz[99].nz = -0.951057f;

			sphereData_nxnynz[100].nx = -0.181636f;
			sphereData_nxnynz[100].ny = 0.250000f;
			sphereData_nxnynz[100].nz = -0.951057f;

			sphereData_nxnynz[101].nx = -0.293892f;
			sphereData_nxnynz[101].ny = 0.095491f;
			sphereData_nxnynz[101].nz = -0.951057f;

			sphereData_nxnynz[102].nx = -0.293892f;
			sphereData_nxnynz[102].ny = -0.095491f;
			sphereData_nxnynz[102].nz = -0.951057f;

			sphereData_nxnynz[103].nx = -0.181635f;
			sphereData_nxnynz[103].ny = -0.250000f;
			sphereData_nxnynz[103].nz = -0.951057f;

			sphereData_nxnynz[104].nx = 0.000000f;
			sphereData_nxnynz[104].ny = -0.309017f;
			sphereData_nxnynz[104].nz = -0.951057f;

			sphereData_nxnynz[105].nx = 0.181636f;
			sphereData_nxnynz[105].ny = -0.250000f;
			sphereData_nxnynz[105].nz = -0.951057f;

			sphereData_nxnynz[106].nx = 0.293892f;
			sphereData_nxnynz[106].ny = -0.095491f;
			sphereData_nxnynz[106].nz = -0.951057f;

			sphereData_nxnynz[107].nx = 0.293892f;
			sphereData_nxnynz[107].ny = 0.095491f;
			sphereData_nxnynz[107].nz = -0.951057f;

			sphereData_nxnynz[108].nx = 0.181635f;
			sphereData_nxnynz[108].ny = 0.250000f;
			sphereData_nxnynz[108].nz = -0.951057f;

			sphereData_nxnynz[109].nx = -0.000000f;
			sphereData_nxnynz[109].ny = 0.309017f;
			sphereData_nxnynz[109].nz = -0.951057f;

			sphereData_nxnynz[110].nx = 0.000000f;
			sphereData_nxnynz[110].ny = -0.000000f;
			sphereData_nxnynz[110].nz = -1.000000f;

			sphereData_nxnynz[111].nx = 0.000000f;
			sphereData_nxnynz[111].ny = -0.000000f;
			sphereData_nxnynz[111].nz = -1.000000f;

			sphereData_nxnynz[112].nx = 0.000000f;
			sphereData_nxnynz[112].ny = -0.000000f;
			sphereData_nxnynz[112].nz = -1.000000f;

			sphereData_nxnynz[113].nx = 0.000000f;
			sphereData_nxnynz[113].ny = 0.000000f;
			sphereData_nxnynz[113].nz = -1.000000f;

			sphereData_nxnynz[114].nx = 0.000000f;
			sphereData_nxnynz[114].ny = 0.000000f;
			sphereData_nxnynz[114].nz = -1.000000f;

			sphereData_nxnynz[115].nx = -0.000000f;
			sphereData_nxnynz[115].ny = 0.000000f;
			sphereData_nxnynz[115].nz = -1.000000f;

			sphereData_nxnynz[116].nx = -0.000000f;
			sphereData_nxnynz[116].ny = 0.000000f;
			sphereData_nxnynz[116].nz = -1.000000f;

			sphereData_nxnynz[117].nx = -0.000000f;
			sphereData_nxnynz[117].ny = 0.000000f;
			sphereData_nxnynz[117].nz = -1.000000f;

			sphereData_nxnynz[118].nx = -0.000000f;
			sphereData_nxnynz[118].ny = -0.000000f;
			sphereData_nxnynz[118].nz = -1.000000f;

			sphereData_nxnynz[119].nx = -0.000000f;
			sphereData_nxnynz[119].ny = -0.000000f;
			sphereData_nxnynz[119].nz = -1.000000f;

			sphereData_nxnynz[120].nx = 0.000000f;
			sphereData_nxnynz[120].ny = -0.000000f;
			sphereData_nxnynz[120].nz = -1.000000f;

		}

		{

			sphereData_uv[0].u = 0.000000f;
			sphereData_uv[0].v = 1.000000f;

			sphereData_uv[1].u = 0.000000f;
			sphereData_uv[1].v = 0.900000f;

			sphereData_uv[2].u = 0.100000f;
			sphereData_uv[2].v = 1.000000f;

			sphereData_uv[3].u = 0.100000f;
			sphereData_uv[3].v = 0.900000f;

			sphereData_uv[4].u = 0.200000f;
			sphereData_uv[4].v = 1.000000f;

			sphereData_uv[5].u = 0.200000f;
			sphereData_uv[5].v = 0.900000f;

			sphereData_uv[6].u = 0.300000f;
			sphereData_uv[6].v = 1.000000f;

			sphereData_uv[7].u = 0.300000f;
			sphereData_uv[7].v = 0.900000f;

			sphereData_uv[8].u = 0.400000f;
			sphereData_uv[8].v = 1.000000f;

			sphereData_uv[9].u = 0.400000f;
			sphereData_uv[9].v = 0.900000f;

			sphereData_uv[10].u = 0.500000f;
			sphereData_uv[10].v = 1.000000f;

			sphereData_uv[11].u = 0.500000f;
			sphereData_uv[11].v = 0.900000f;

			sphereData_uv[12].u = 0.600000f;
			sphereData_uv[12].v = 1.000000f;

			sphereData_uv[13].u = 0.600000f;
			sphereData_uv[13].v = 0.900000f;

			sphereData_uv[14].u = 0.700000f;
			sphereData_uv[14].v = 1.000000f;

			sphereData_uv[15].u = 0.700000f;
			sphereData_uv[15].v = 0.900000f;

			sphereData_uv[16].u = 0.800000f;
			sphereData_uv[16].v = 1.000000f;

			sphereData_uv[17].u = 0.800000f;
			sphereData_uv[17].v = 0.900000f;

			sphereData_uv[18].u = 0.900000f;
			sphereData_uv[18].v = 1.000000f;

			sphereData_uv[19].u = 0.900000f;
			sphereData_uv[19].v = 0.900000f;

			sphereData_uv[20].u = 1.000000f;
			sphereData_uv[20].v = 1.000000f;

			sphereData_uv[21].u = 1.000000f;
			sphereData_uv[21].v = 0.900000f;

			sphereData_uv[22].u = 0.000000f;
			sphereData_uv[22].v = 0.800000f;

			sphereData_uv[23].u = 0.100000f;
			sphereData_uv[23].v = 0.800000f;

			sphereData_uv[24].u = 0.200000f;
			sphereData_uv[24].v = 0.800000f;

			sphereData_uv[25].u = 0.300000f;
			sphereData_uv[25].v = 0.800000f;

			sphereData_uv[26].u = 0.400000f;
			sphereData_uv[26].v = 0.800000f;

			sphereData_uv[27].u = 0.500000f;
			sphereData_uv[27].v = 0.800000f;

			sphereData_uv[28].u = 0.600000f;
			sphereData_uv[28].v = 0.800000f;

			sphereData_uv[29].u = 0.700000f;
			sphereData_uv[29].v = 0.800000f;

			sphereData_uv[30].u = 0.800000f;
			sphereData_uv[30].v = 0.800000f;

			sphereData_uv[31].u = 0.900000f;
			sphereData_uv[31].v = 0.800000f;

			sphereData_uv[32].u = 1.000000f;
			sphereData_uv[32].v = 0.800000f;

			sphereData_uv[33].u = 0.000000f;
			sphereData_uv[33].v = 0.700000f;

			sphereData_uv[34].u = 0.100000f;
			sphereData_uv[34].v = 0.700000f;

			sphereData_uv[35].u = 0.200000f;
			sphereData_uv[35].v = 0.700000f;

			sphereData_uv[36].u = 0.300000f;
			sphereData_uv[36].v = 0.700000f;

			sphereData_uv[37].u = 0.400000f;
			sphereData_uv[37].v = 0.700000f;

			sphereData_uv[38].u = 0.500000f;
			sphereData_uv[38].v = 0.700000f;

			sphereData_uv[39].u = 0.600000f;
			sphereData_uv[39].v = 0.700000f;

			sphereData_uv[40].u = 0.700000f;
			sphereData_uv[40].v = 0.700000f;

			sphereData_uv[41].u = 0.800000f;
			sphereData_uv[41].v = 0.700000f;

			sphereData_uv[42].u = 0.900000f;
			sphereData_uv[42].v = 0.700000f;

			sphereData_uv[43].u = 1.000000f;
			sphereData_uv[43].v = 0.700000f;

			sphereData_uv[44].u = 0.000000f;
			sphereData_uv[44].v = 0.600000f;

			sphereData_uv[45].u = 0.100000f;
			sphereData_uv[45].v = 0.600000f;

			sphereData_uv[46].u = 0.200000f;
			sphereData_uv[46].v = 0.600000f;

			sphereData_uv[47].u = 0.300000f;
			sphereData_uv[47].v = 0.600000f;

			sphereData_uv[48].u = 0.400000f;
			sphereData_uv[48].v = 0.600000f;

			sphereData_uv[49].u = 0.500000f;
			sphereData_uv[49].v = 0.600000f;

			sphereData_uv[50].u = 0.600000f;
			sphereData_uv[50].v = 0.600000f;

			sphereData_uv[51].u = 0.700000f;
			sphereData_uv[51].v = 0.600000f;

			sphereData_uv[52].u = 0.800000f;
			sphereData_uv[52].v = 0.600000f;

			sphereData_uv[53].u = 0.900000f;
			sphereData_uv[53].v = 0.600000f;

			sphereData_uv[54].u = 1.000000f;
			sphereData_uv[54].v = 0.600000f;

			sphereData_uv[55].u = 0.000000f;
			sphereData_uv[55].v = 0.500000f;

			sphereData_uv[56].u = 0.100000f;
			sphereData_uv[56].v = 0.500000f;

			sphereData_uv[57].u = 0.200000f;
			sphereData_uv[57].v = 0.500000f;

			sphereData_uv[58].u = 0.300000f;
			sphereData_uv[58].v = 0.500000f;

			sphereData_uv[59].u = 0.400000f;
			sphereData_uv[59].v = 0.500000f;

			sphereData_uv[60].u = 0.500000f;
			sphereData_uv[60].v = 0.500000f;

			sphereData_uv[61].u = 0.600000f;
			sphereData_uv[61].v = 0.500000f;

			sphereData_uv[62].u = 0.700000f;
			sphereData_uv[62].v = 0.500000f;

			sphereData_uv[63].u = 0.800000f;
			sphereData_uv[63].v = 0.500000f;

			sphereData_uv[64].u = 0.900000f;
			sphereData_uv[64].v = 0.500000f;

			sphereData_uv[65].u = 1.000000f;
			sphereData_uv[65].v = 0.500000f;

			sphereData_uv[66].u = 0.000000f;
			sphereData_uv[66].v = 0.400000f;

			sphereData_uv[67].u = 0.100000f;
			sphereData_uv[67].v = 0.400000f;

			sphereData_uv[68].u = 0.200000f;
			sphereData_uv[68].v = 0.400000f;

			sphereData_uv[69].u = 0.300000f;
			sphereData_uv[69].v = 0.400000f;

			sphereData_uv[70].u = 0.400000f;
			sphereData_uv[70].v = 0.400000f;

			sphereData_uv[71].u = 0.500000f;
			sphereData_uv[71].v = 0.400000f;

			sphereData_uv[72].u = 0.600000f;
			sphereData_uv[72].v = 0.400000f;

			sphereData_uv[73].u = 0.700000f;
			sphereData_uv[73].v = 0.400000f;

			sphereData_uv[74].u = 0.800000f;
			sphereData_uv[74].v = 0.400000f;

			sphereData_uv[75].u = 0.900000f;
			sphereData_uv[75].v = 0.400000f;

			sphereData_uv[76].u = 1.000000f;
			sphereData_uv[76].v = 0.400000f;

			sphereData_uv[77].u = 0.000000f;
			sphereData_uv[77].v = 0.300000f;

			sphereData_uv[78].u = 0.100000f;
			sphereData_uv[78].v = 0.300000f;

			sphereData_uv[79].u = 0.200000f;
			sphereData_uv[79].v = 0.300000f;

			sphereData_uv[80].u = 0.300000f;
			sphereData_uv[80].v = 0.300000f;

			sphereData_uv[81].u = 0.400000f;
			sphereData_uv[81].v = 0.300000f;

			sphereData_uv[82].u = 0.500000f;
			sphereData_uv[82].v = 0.300000f;

			sphereData_uv[83].u = 0.600000f;
			sphereData_uv[83].v = 0.300000f;

			sphereData_uv[84].u = 0.700000f;
			sphereData_uv[84].v = 0.300000f;

			sphereData_uv[85].u = 0.800000f;
			sphereData_uv[85].v = 0.300000f;

			sphereData_uv[86].u = 0.900000f;
			sphereData_uv[86].v = 0.300000f;

			sphereData_uv[87].u = 1.000000f;
			sphereData_uv[87].v = 0.300000f;

			sphereData_uv[88].u = 0.000000f;
			sphereData_uv[88].v = 0.200000f;

			sphereData_uv[89].u = 0.100000f;
			sphereData_uv[89].v = 0.200000f;

			sphereData_uv[90].u = 0.200000f;
			sphereData_uv[90].v = 0.200000f;

			sphereData_uv[91].u = 0.300000f;
			sphereData_uv[91].v = 0.200000f;

			sphereData_uv[92].u = 0.400000f;
			sphereData_uv[92].v = 0.200000f;

			sphereData_uv[93].u = 0.500000f;
			sphereData_uv[93].v = 0.200000f;

			sphereData_uv[94].u = 0.600000f;
			sphereData_uv[94].v = 0.200000f;

			sphereData_uv[95].u = 0.700000f;
			sphereData_uv[95].v = 0.200000f;

			sphereData_uv[96].u = 0.800000f;
			sphereData_uv[96].v = 0.200000f;

			sphereData_uv[97].u = 0.900000f;
			sphereData_uv[97].v = 0.200000f;

			sphereData_uv[98].u = 1.000000f;
			sphereData_uv[98].v = 0.200000f;

			sphereData_uv[99].u = 0.000000f;
			sphereData_uv[99].v = 0.100000f;

			sphereData_uv[100].u = 0.100000f;
			sphereData_uv[100].v = 0.100000f;

			sphereData_uv[101].u = 0.200000f;
			sphereData_uv[101].v = 0.100000f;

			sphereData_uv[102].u = 0.300000f;
			sphereData_uv[102].v = 0.100000f;

			sphereData_uv[103].u = 0.400000f;
			sphereData_uv[103].v = 0.100000f;

			sphereData_uv[104].u = 0.500000f;
			sphereData_uv[104].v = 0.100000f;

			sphereData_uv[105].u = 0.600000f;
			sphereData_uv[105].v = 0.100000f;

			sphereData_uv[106].u = 0.700000f;
			sphereData_uv[106].v = 0.100000f;

			sphereData_uv[107].u = 0.800000f;
			sphereData_uv[107].v = 0.100000f;

			sphereData_uv[108].u = 0.900000f;
			sphereData_uv[108].v = 0.100000f;

			sphereData_uv[109].u = 1.000000f;
			sphereData_uv[109].v = 0.100000f;

			sphereData_uv[110].u = 0.000000f;
			sphereData_uv[110].v = -0.000000f;

			sphereData_uv[111].u = 0.100000f;
			sphereData_uv[111].v = -0.000000f;

			sphereData_uv[112].u = 0.200000f;
			sphereData_uv[112].v = -0.000000f;

			sphereData_uv[113].u = 0.300000f;
			sphereData_uv[113].v = -0.000000f;

			sphereData_uv[114].u = 0.400000f;
			sphereData_uv[114].v = -0.000000f;

			sphereData_uv[115].u = 0.500000f;
			sphereData_uv[115].v = -0.000000f;

			sphereData_uv[116].u = 0.600000f;
			sphereData_uv[116].v = -0.000000f;

			sphereData_uv[117].u = 0.700000f;
			sphereData_uv[117].v = -0.000000f;

			sphereData_uv[118].u = 0.800000f;
			sphereData_uv[118].v = -0.000000f;

			sphereData_uv[119].u = 0.900000f;
			sphereData_uv[119].v = -0.000000f;

			sphereData_uv[120].u = 1.000000f;
			sphereData_uv[120].v = -0.000000f;
		}

		this->numVerts = SPHERE_DATA_NUM_VERTS;
		this->numTris = TRILIST_NUM_TRIANGLES;

		// Create a VAO
		glGenVertexArrays(1, &this->vao);
		assert(this->vao != 0);
		glBindVertexArray(this->vao);

		// Create a VBO
		glGenBuffers(1, &this->vbo_verts);
		assert(this->vbo_verts != 0);

		glGenBuffers(1, &this->vbo_norms);
		assert(this->vbo_norms != 0);

		glGenBuffers(1, &this->vbo_texts);
		assert(this->vbo_texts != 0);

		glGenBuffers(1, &this->vbo_index);
		assert(this->vbo_index != 0);


		// Load the verts data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_verts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_xyz) * this->numVerts), sphereData_xyz, GL_STATIC_DRAW);

		// Vert data is location: 0  (used in vertex shader)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_xyz), 0);
		glEnableVertexAttribArray(0);

		// Load the norms data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_norms);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_nxnynz) * this->numVerts), sphereData_nxnynz, GL_STATIC_DRAW);

		// normals data in location 1 (used in vertex shader
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vert_nxnynz), 0);
		glEnableVertexAttribArray(1);

		// Load the texts data: ---------------------------------------------------------

		glBindBuffer(GL_ARRAY_BUFFER, this->vbo_texts);

		// load the data to the GPU
		glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Vert_uv) * this->numVerts), sphereData_uv, GL_STATIC_DRAW);

		// Texture data is location: 2  (used in vertex shader)
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vert_uv), 0);
		glEnableVertexAttribArray(2);

		// Load the index data: ---------------------------------------------------------

		// Bind our 2nd VBO as being the active buffer and storing index ) 
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_index);

		// Copy the index data to our buffer 
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)(sizeof(Tri_index) * this->numTris), triList, GL_STATIC_DRAW);

	}


	SphereMesh::SphereMesh(const char* const modelFileName)
		: Mesh()
	{
		this->privCreateVAO(modelFileName);
	}

	SphereMesh::~SphereMesh()
	{
		// remove anything dynamic here
	}

}

// --- End of File ---