
#include <AzCore/Serialization/SerializeContext.h>
#include "NakamaClientGemEditorSystemComponent.h"

#include <NakamaClientGem/NakamaClientGemTypeIds.h>

namespace NakamaClientGem
{
    AZ_COMPONENT_IMPL(NakamaClientGemEditorSystemComponent, "NakamaClientGemEditorSystemComponent",
        NakamaClientGemEditorSystemComponentTypeId, BaseSystemComponent);

    void NakamaClientGemEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<NakamaClientGemEditorSystemComponent, NakamaClientGemSystemComponent>()
                ->Version(0);
        }
    }

    NakamaClientGemEditorSystemComponent::NakamaClientGemEditorSystemComponent() = default;

    NakamaClientGemEditorSystemComponent::~NakamaClientGemEditorSystemComponent() = default;

    void NakamaClientGemEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("NakamaClientGemEditorService"));
    }

    void NakamaClientGemEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("NakamaClientGemEditorService"));
    }

    void NakamaClientGemEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
    }

    void NakamaClientGemEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void NakamaClientGemEditorSystemComponent::Activate()
    {
        NakamaClientGemSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void NakamaClientGemEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        NakamaClientGemSystemComponent::Deactivate();
    }

} // namespace NakamaClientGem
