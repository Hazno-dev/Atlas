// Hazno - 2026

export module Atlas.Common:Utility;
import :Type;


/**
 * Determine if any flags are set in the given enum value.
 * @tparam t_enum Enum Type
 * @param value Current enum value.
 * @param flags Target flag(s) to evaluate.
 * @return True if any of the specified flags are set, false otherwise.
 */
export template <Cpt_EnumIntegral t_enum>
bool constexpr HasAnyFlags(const t_enum value, const t_enum flags)
{
	return (value & flags) != 0;
}

/**
 * Determine if all the flags are set in the given enum value.
 * @tparam t_enum Enum Type
 * @param value Current enum value.
 * @param flags Target flag(s) to evaluate.
 * @return True if all the specified flags are set, false otherwise.
 */
export template <Cpt_EnumIntegral t_enum>
bool constexpr HasAllFlags(const t_enum value, const t_enum flags)
{
	return (value & flags) == flags;
}
