
#include <NakamaComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

namespace NakamaClientGem
{
    AZ_COMPONENT_IMPL(NakamaComponent, "NakamaComponent", "{629C555E-D148-442B-ADA9-9ED14ABB7539}");

    void NakamaComponent::Activate()
    {
        NakamaRequestBus::Handler::BusConnect(GetEntityId());
    }

    void NakamaComponent::Deactivate()
    {
        NakamaRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void NakamaComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<NakamaComponent, AZ::Component>()
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<NakamaComponent>("NakamaComponent", "[Nakama Client for O3DE]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Multiplayer")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {
            behaviorContext->Class<NakamaComponent>("Nakama Component")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaClient")
                ;
        }
    }

    void NakamaComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("NakamaComponentService"));
    }

    void NakamaComponent::GetIncompatibleServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
    }

    void NakamaComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void NakamaComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }
} // namespace NakamaClientGem
