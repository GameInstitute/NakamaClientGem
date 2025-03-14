
#include "NakamaClientGemModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <NakamaClientGem/NakamaClientGemTypeIds.h>

#include <Clients/NakamaClientGemSystemComponent.h>
#include <NakamaComponent.h>

namespace NakamaClientGem
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(NakamaClientGemModuleInterface,
        "NakamaClientGemModuleInterface", NakamaClientGemModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(NakamaClientGemModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(NakamaClientGemModuleInterface, AZ::SystemAllocator);

    NakamaClientGemModuleInterface::NakamaClientGemModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            NakamaClientGemSystemComponent::CreateDescriptor(),
            NakamaComponent::CreateDescriptor()
            });
    }

    AZ::ComponentTypeList NakamaClientGemModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<NakamaClientGemSystemComponent>(),
        };
    }
} // namespace NakamaClientGem
