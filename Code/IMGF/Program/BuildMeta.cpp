#include "BuildMeta.h"

using namespace imgf;

BuildMeta::BuildMeta(void) :
	m_fCurrentVersion(0.0f),
	m_bIsAlphaBuild(false)
{
	m_strCurrentVersionString = "?";
}