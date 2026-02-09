// Hazno - 2026

export module Atlas.Codegen.Command:Base;
import Atlas.Codegen;
import std;

inline constexpr auto c_helpGap = "	";

export namespace Atlas::Codegen
{
	class Command
	{
		protected:
			bool m_shouldRun = false;

		public:
			virtual ~Command() = default;

			ATLAS_NODISCARD virtual constexpr void PrintHelpArguments() = 0;

			ATLAS_NODISCARD virtual constexpr bool IsBlocking()
			{
				return false;
			}

			ATLAS_NODISCARD virtual bool ShouldRun(CodegenInstance* instance)
			{
				return m_shouldRun;
			}

			virtual bool UpdateArguments(CodegenInstance* instance, const std::string& arg) = 0;
			virtual void Run(CodegenInstance* instance) = 0;
	};

	inline std::vector<std::shared_ptr<Command>>& GetCommands()
	{
		static std::vector<std::shared_ptr<Command>> commands{};
		return commands;
	}
}
