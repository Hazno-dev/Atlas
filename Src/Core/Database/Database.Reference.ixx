// Hazno - 2026

export module Atlas.Database.Reference;

export namespace Atlas::DB
{
	template <typename T>
	class DataRef
	{
		const T* ptr = nullptr;

		public:
			constexpr DataRef() = default;

			constexpr explicit DataRef(const T* p) :
				ptr(p) {}

			constexpr const T* operator->() const noexcept
			{
				return ptr;
			}

			constexpr const T& operator*() const noexcept
			{
				return *ptr;
			}

			constexpr const T& get() const noexcept
			{
				return *ptr;
			}

			constexpr explicit operator bool() const noexcept
			{
				return ptr != nullptr;
			}
	};
}
