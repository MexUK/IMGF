#include "WebsitesWindowLayer.h"

using namespace imgf;

WebsitesWindowLayer::WebsitesWindowLayer(void)
{
}

// initialization
void					WebsitesWindowLayer::init(void)
{
	addButton(50, 250, 100, 20, "Close", "window2_button", 200);

	addText(50, 50, 600, 350, "IMG Factory Links\n\
\n\
IMG Factory Website: imgfactory.mvec.io\n\
IMG Factory Discussion: http://gtaforums.com/topic/896836-img-factory/\n\
IMG Factory Source Code (Partial - excludes core code): https://github.com/MexUK/IMGF\n\
\n\
Modding Links\n\
\n\
Format Documentation: gtamodding.com\n\
Format Documentation: gtamodding.ru\n\
Modding Discussion: gtaforums.com");
}