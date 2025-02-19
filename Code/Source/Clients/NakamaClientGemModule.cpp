
#include <NakamaClientGem/NakamaClientGemTypeIds.h>
#include <NakamaClientGemModuleInterface.h>
#include "NakamaClientGemSystemComponent.h"

namespace NakamaClientGem
{
    class NakamaClientGemModule
        : public NakamaClientGemModuleInterface
    {
    public:
        AZ_RTTI(NakamaClientGemModule, NakamaClientGemModuleTypeId, NakamaClientGemModuleInterface);
        AZ_CLASS_ALLOCATOR(NakamaClientGemModule, AZ::SystemAllocator);
    };
}// namespace NakamaClientGem

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), NakamaClientGem::NakamaClientGemModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_NakamaClientGem, NakamaClientGem::NakamaClientGemModule)
#endif
