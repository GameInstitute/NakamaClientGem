
#include <NakamaClientGem/NakamaClientGemTypeIds.h>
#include <NakamaClientGemModuleInterface.h>
#include "NakamaClientGemEditorSystemComponent.h"

namespace NakamaClientGem
{
    class NakamaClientGemEditorModule
        : public NakamaClientGemModuleInterface
    {
    public:
        AZ_RTTI(NakamaClientGemEditorModule, NakamaClientGemEditorModuleTypeId, NakamaClientGemModuleInterface);
        AZ_CLASS_ALLOCATOR(NakamaClientGemEditorModule, AZ::SystemAllocator);

        NakamaClientGemEditorModule()
        {
            // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
            // Add ALL components descriptors associated with this gem to m_descriptors.
            // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
            // This happens through the [MyComponent]::Reflect() function.
            m_descriptors.insert(m_descriptors.end(), {
                NakamaClientGemEditorSystemComponent::CreateDescriptor(),
            });
        }

        /**
         * Add required SystemComponents to the SystemEntity.
         * Non-SystemComponents should not be added here
         */
        AZ::ComponentTypeList GetRequiredSystemComponents() const override
        {
            return AZ::ComponentTypeList {
                azrtti_typeid<NakamaClientGemEditorSystemComponent>(),
            };
        }
    };
}// namespace NakamaClientGem

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME, _Editor), NakamaClientGem::NakamaClientGemEditorModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_NakamaClientGem_Editor, NakamaClientGem::NakamaClientGemEditorModule)
#endif
