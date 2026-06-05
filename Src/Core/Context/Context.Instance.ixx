// Hazno - 2026

export module Atlas.Context:Instance;
import Atlas.Common;
import std;

export namespace Atlas
{
	class Context
	{
		public:
			const std::string Path;
			const uint32 Version;
	};
}
