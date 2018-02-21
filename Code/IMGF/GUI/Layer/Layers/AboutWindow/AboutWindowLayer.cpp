#include "AboutWindowLayer.h"
#include "Program/BuildVersion.h"
#include "Static/String.h"

using namespace std;
using namespace bxcf;
using namespace imgf;

AboutWindowLayer::AboutWindowLayer(void)
{
}

// initialization
void					AboutWindowLayer::init(void)
{
	addButton(50, 570, 100, 20, "Close", "window2_button", 200);

	addText(50, 50, 550, 500, "Version: 2.0 (Build " + String::addNumberGrouping(IMGF_MINOR_BUILD_VERSION_STRING) + ")\n\
\n\
\n\
\n\
Information:\n\
\n\
IMG Factory is a modding tool for games, aiming to simplify mod development.\n\
Mex is the main programmer, X-Seti is the main feature designer.\n\
\n\
\n\
\n\
Credits:\n\
\n\
Mex (Programmer, Themes)\n\
X-Seti (Feature Planning, Themes)\n\
\n\
IgorX (IMGF 1 Texture Window Design & Tester)\n\
Leaf (Logo, Icon, Themes, Format Files)\n\
dkluin (Tester)\n\
cj2000 (Rare Format Documentation)\n\
\n\
gtamodding.com (Format Documentation)\n\
gtamodding.ru (Format Documentation)\n\
\n\
Third Party Code Referenced:\n\
- Spark IV Source Code (.WTD Format)\n\
- Moo Mapper Source Code (.DFF Format - Node Iteration for 3D Render)\n\
\n\
Third Party Code Used:\n\
- CRC, LZ4, LZO, ZLib, AES, CIniFile, STB, Squish DXT, happyhttp\n\
- DHPOBitmap, DXSDK, Freetype, GLEW, GLM, Google sparsehash");
}