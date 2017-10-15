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
IMG Factory is a tool to help modders change their games.\n\
\n\
The tool is created by Mex & X-Seti.\n\
Mex programmed the tool, X-Seti planned the features.\n\
\n\
\n\
\n\
Credits:\n\
\n\
Mex (Programmer, Themes)\n\
X-Seti (Feature Planning, Themes)\n\
\n\
cj2000 (Rare Format Documentation)\n\
dkluin (Tester)\n\
IgorX (Initial Texture Window Design & Tester)\n\
Leaf (Logo, Icon, Themes, Format Files)\n\
\n\
gtamodding.com (Format Documentation)\n\
gtamodding.ru (Format Documentation)\n\
\n\
Spark IV Source Code (.WTD Format)\n\
\n\
Third Party Code: CRC, LZ4, LZO, ZLib, AES, CIniFile, STB, Squish DXT, happyhttp");
}