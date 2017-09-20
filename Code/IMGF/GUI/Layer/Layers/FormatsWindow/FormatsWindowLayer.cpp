#include "FormatsWindowLayer.h"

using namespace imgf;

FormatsWindowLayer::FormatsWindowLayer(void)
{
}

// initialization
void					FormatsWindowLayer::init(void)
{
	addButton(50, 450, 100, 20, "Close", "window2_button", 200);

	addText(50, 50, 500, 350, "Game Formats Supported:\n\
\n\
COL\n\
GTA III (PC), GTA VC (PC), GTA SA (PC)\n\
\n\
DAT Loader\n\
GTA III (PC), GTA VC (PC), GTA SA (PC)\n\
\n\
DFF\n\
GTA III (PC), GTA VC (PC), GTA SA (PC)\n\
\n\
IDE\n\
GTA III (PC), GTA VC (PC), GTA SA (PC)\n\
\n\
IMG\n\
GTA III (PC), GTA VC (PC), GTA SA (PC), GTA IV (PC)\n\
\n\
IPL\n\
GTA III (PC), GTA VC (PC), GTA SA (PC)\n\
\n\
TXD\n\
GTA III (PC), GTA VC (PC), GTA SA (PC), ? (PS2), ? (Android)\n\
\n\
WDR - Partial Support\n\
GTA IV (PC)\n\
\n\
WTD - Partial Support\n\
GTA IV (PC)");
}