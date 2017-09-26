#include "AboutWindowLayer.h"

using namespace imgf;

AboutWindowLayer::AboutWindowLayer(void)
{
}

// initialization
void					AboutWindowLayer::init(void)
{
	addButton(50, 570, 100, 20, "Close", "window2_button", 200);

	addText(50, 50, 550, 500, "Version: 2.0\n\
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
Mex (Programmer)\n\
X-Seti (Feature Planning)\n\
\n\
cj2000 (Rare Format Documentation)\n\
\n\
IgorX (Tester)\n\
dkluin (Tester)\n\
\n\
gtamodding.com (Format Documentation)\n\
gtamodding.ru (Format Documentation)\n\
\n\
Spark IV Source Code (.WTD Format)\n\
\n\
Third Party Code: CRC, LZ4, LZO, ZLib, AES, CIniFile, STB, Squish DXT, happyhttp");
}