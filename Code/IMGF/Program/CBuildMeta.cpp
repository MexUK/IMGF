#include "CBuildMeta.h"

using namespace imgf;

CBuildMeta::CBuildMeta(void) :
	m_fCurrentVersion(0.0f),
	m_bIsAlphaBuild(false)
{
	m_strCurrentVersionString = "?";
}