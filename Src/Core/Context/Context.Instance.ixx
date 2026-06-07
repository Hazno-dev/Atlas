// Hazno - 2026

export module Atlas.Context:Instance;
import :Platform;
import Atlas.Common;
import std;

export namespace Atlas
{
	struct Context
	{
		const uint32 Version;
		const Platform Platform;
	};
}
