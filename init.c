#include <stdbool.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <proto/dos.h>

#include "init.h"

struct DebugIFace		*IDebug = NULL;

bool init()
{
	IDebug = GetInterface( SysBase, "Debug" , 1, TAG_END );
	if (!IDebug) return false;

	return true;
}

void shutdown()
{
	if (IDebug) DropInterface(IDebug);
	IDebug = NULL;
}

