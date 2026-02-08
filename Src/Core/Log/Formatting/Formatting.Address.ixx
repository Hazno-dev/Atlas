// Hazno - 2026

// ReSharper disable CppInconsistentNaming
export module Atlas.Log.Formatting:Address;
import Atlas.Common;
import Atlas.Process;
import std;
import fmt;

export namespace Atlas::Logs::Format
{
	struct Address
	{
		uint64 Value;

		explicit Address(const uint64 val) :
			Value(val) {}

		template <Cpt_Ptr t_ptr>
		explicit Address(t_ptr val) :
			Value(reinterpret_cast<uint64>(val)) {}
	};
}

export namespace fmt
{
	template <>
	struct formatter<Atlas::Logs::Format::Address> : formatter<std::string>
	{
		private:
			bool m_showModule = true; //N == Dont try print module
			bool m_showValue = false; //V == Also show decimal value
			int m_len = 16;

		public:
			constexpr auto parse(const parse_context<>& ctx)
			{
				auto it = ctx.begin();

				for (const auto end = ctx.end(); it != end && *it != '}'; it++) {
					switch (*it) {
						case 'n':
							m_showModule = false;
							continue;
						case 'v':
							m_showValue = true;
							continue;
						default:
							return ctx.begin();
					}
				}

				//TODO: Length parse

				return it;
			}

			auto format(const Atlas::Logs::Format::Address& s, const format_context& ctx) const
			{
				const auto addr = s.Value;
				auto out = ctx.out();

				auto end = format_to(out, "0x{:0{}X}", addr, m_len);

				if (m_showValue) {
					end = format_to(out, " {:0>10}", addr);
				}

				if (m_showModule) {
					if (const auto m = Atlas::Process::GetModuleForAddress(addr)) {
						end = format_to(out, " ({}+0x{:08X})", m->Name(), m->RVA(addr));
					}
				}

				return end;
			}
	};
}
