// Hazno - 2026

export module Atlas.Game.STU.RTTI:STURegistry;
import :STUInfo;
import :STURegistryView;
import Atlas.Process;

export namespace Atlas::STU
{
	/**
	 *  <b> STURegistry </b> \n
	 *      Description TBC
	 *
	 *
	 *  \n
	 *  \n  Size:           0x10
	 *  \n  Factory:        N/A
	 *  \n  VT:             N/A
	 *  \n
	 */
	struct STURegistry
	{
		STURegistry* Next;
		STUInfo* Info;

		/////////////////////////////
		/// EXTENSIONS
		/////////////////////////////

		ATLAS_NODISCARD STUInfo* GetSTUInfoByHash(uint32 hash) const;

		ATLAS_NODISCARD STURegistryView Range() const;

		/**
		 * Get the singleton instance of the STURegistry list head.
		 * @return Pointer to the first STURegistry in the linked list.
		 */
		ATLAS_NODISCARD static STURegistry* Get();
		ATLAS_NODISCARD static STURegistry* Get(const Process::Module& module);
	};

	ATLAS_VALIDATE_SIZE(STURegistry, 0x10);
}
