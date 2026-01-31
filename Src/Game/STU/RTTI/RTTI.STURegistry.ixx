// Hazno - 2026

export module Atlas.Game.STU.RTTI:STURegistry;
import :STUInfo;

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
        STURegistry*    Next;
        STUInfo*        Info;

        /////////////////////////////
        /// EXTENSIONS
        /////////////////////////////

        /**
         * Get the singleton instance of the STURegistry list head.
         * @return Pointer to the first STURegistry in the linked list.
         */
        [[nodiscard]] static STURegistry* Get();
        //[[nodiscard]] static STURegistry* Get(const Utility::Modules::ModuleBounds& module);

        [[nodiscard]] STUInfo* GetSTUInfoByHash(uint32 hash) const;

        //[[nodiscard]] STURegistryView Range() const;
    };

    ATLAS_VALIDATE_SIZE(STURegistry, 0x10);
}