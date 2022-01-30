#include <stdbool.h>

#define __USE_INLINE__

#include <proto/exec.h>
#include <proto/dos.h>

#include "init.h"


int32 printStack(struct Hook *hook, struct Task *task, struct StackFrameMsg *frame)
{
	switch (frame->State)
	{
		case STACK_FRAME_DECODED:


			{
				struct DebugSymbol *symbol = ObtainDebugSymbol(frame->MemoryAddress,NULL);

				if (symbol)
				{
					Printf("Stack %p -> Address: %p, offset %p, SegmentNumber %p, SegmentOffset %p, Name: %s, BaseName: %s,FunctionName: %s\n", 
							frame->StackPointer, 
							frame->MemoryAddress,
							symbol -> Offset,
							symbol -> SegmentNumber,
							symbol -> SegmentOffset	,
							symbol -> Name ? symbol -> Name : "NULL",
							symbol -> SourceBaseName ? symbol -> SourceBaseName : "NULL" ,
							symbol -> SourceFunctionName ? symbol -> SourceFunctionName : "NULL" );

					ReleaseDebugSymbol(symbol);
				}
				else
				{
					Printf("Stack %p -> Address: %p\n",frame->StackPointer, frame->MemoryAddress);
				}
			}

			break;

		case STACK_FRAME_INVALID_BACKCHAIN_PTR:
			Printf("(%p) invalid backchain pointer\n",
			frame->StackPointer);
			break;

		case STACK_FRAME_TRASHED_MEMORY_LOOP:
			Printf("(%p) trashed memory loop\n",
			frame->StackPointer);
			break;

		case STACK_FRAME_BACKCHAIN_PTR_LOOP:
			Printf("(%p) backchain pointer loop\n",
			frame->StackPointer);
			break;

		default:
			Printf("Unknown state=%lu\n", frame->State);
	}

	return 0;  // Continue tracing.
}


struct Hook *hook;

void _(char *name)
{
	Forbid();
	struct Task *task = FindTask(name);
	if (task != NULL)
	{
		SuspendTask(task, 0);
		Permit();

		printf("Task: %08x\n",task);
		uint32 result = StackTrace(task, hook);

		RestartTask(task, 0);
	}
	else
	{
		Permit();
		Printf("Task not found %s\n",name);
	}
}

int main(int args, char *arg[])
{
	if (! init() ) shutdown(); 

	if (args == 2) 
	{
		Printf("Program %s\n",arg[1]);
		printf("IDebug: %08x\n",IDebug);

		hook = AllocSysObjectTags(ASOT_HOOK,  ASOHOOK_Entry, printStack, TAG_END);
		if (hook != NULL)
		{
			_( arg[1] );

			FreeSysObject(ASOT_HOOK, hook);
		}
	}
	else
	{
		Printf("\nFrozenAT V0.5\nCopyright Kjetil Hvalstrand\n");
		Printf("https://khval/khval/FrozenAt\n");
		Printf("MIT License\n\n");
		Printf("Usage:\nFozenAt ProgramName\n\n");
	}

	shutdown();
	return 0;
}

