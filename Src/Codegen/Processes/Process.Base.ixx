// Hazno - 2026

export module Atlas.Codegen.Process:Base;
import Atlas.Codegen;
import std;

export namespace Atlas::Codegen
{
	class Process
	{
		protected:
			bool m_shouldRun = false;

		public:
			virtual ~Process() = default;

			ATLAS_NODISCARD virtual constexpr const char* GetHelpArguments() = 0;

			ATLAS_NODISCARD virtual constexpr bool IsBlocking()
			{
				return false;
			}

			ATLAS_NODISCARD virtual bool ShouldRun(CodegenInstance* instance)
			{
				return m_shouldRun;
			}

			virtual void UpdateArguments(CodegenInstance* instance, const std::string& arg) = 0;
			virtual void Run(CodegenInstance* instance) = 0;
	};

	inline std::vector<std::shared_ptr<Process>>& GetProcesses()
	{
		static std::vector<std::shared_ptr<Process>> processes{};
		return processes;
	}
}
