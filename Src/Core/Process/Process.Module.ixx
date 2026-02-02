// Hazno - 2026

module;

#include <Windows.h>
#include <tlhelp32.h>

export module Atlas.Process:Module;
import Atlas.Common;

export namespace Atlas::Process
{
	struct Module
	{
		private:
			uint64 m_base;
			uint64 m_end;
			uint64 m_size;
			std::string m_name;

		public:
			explicit Module(MODULEENTRY32 modEntry);

			ATLAS_NODISCARD uint64 RVA(uint64 absolute) const;

			template <class t_ret = uint64, class t_input> requires Cpt_Integral<t_input>
			ATLAS_NODISCARD t_ret RVA(t_input absolute) const
			{
				if constexpr (std::is_same_v<t_ret, uint64>) {
					return RVA(ToUInt64(absolute));
				} else {
					return reinterpret_cast<t_ret>(RVA(ToUInt64(absolute)));
				}
			}

			ATLAS_NODISCARD uint64 VA(uint64 relative) const;

			template <class t_ret = uint64, class t_input> requires Cpt_Integral<t_input>
			ATLAS_NODISCARD t_ret VA(t_input relative) const
			{
				if constexpr (std::is_same_v<t_ret, uint64>) {
					return VA(ToUInt64(relative));
				} else {
					return reinterpret_cast<t_ret>(VA(ToUInt64(relative)));
				}
			}

			ATLAS_NODISCARD uint64 Base() const
			{
				return m_base;
			}

			ATLAS_NODISCARD uint64 End() const
			{
				return m_end;
			}

			ATLAS_NODISCARD uint64 Size() const
			{
				return m_size;
			}

			ATLAS_NODISCARD const std::string& Name() const
			{
				return m_name;
			}
	};

	const Module& GetProcessModule();
	const Module& GetSelfModule();
	const Module* GetModuleForAddress(uint64 addr);

	template <class t_input> requires Cpt_Integral<t_input>
	const Module* GetModuleForAddress(t_input addr)
	{
		return GetModuleForAddress(ToUInt64(addr));
	}
}

namespace Atlas::Process
{
	void InitializeModules();
	void UninitializeModules();
}
