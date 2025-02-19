
#include "NakamaClientGemSystemComponent.h"

#include <NakamaClientGem/NakamaClientGemTypeIds.h>

#include <AzCore/Serialization/SerializeContext.h>

namespace NakamaClientGem
{
    AZ_COMPONENT_IMPL(NakamaClientGemSystemComponent, "NakamaClientGemSystemComponent",
        NakamaClientGemSystemComponentTypeId);

    void NakamaClientGemSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<NakamaClientGemSystemComponent, AZ::Component>()
                ->Version(0)
                ;
        }
    }

    void NakamaClientGemSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        provided.push_back(AZ_CRC_CE("NakamaClientGemService"));
    }

    void NakamaClientGemSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        incompatible.push_back(AZ_CRC_CE("NakamaClientGemService"));
    }

    void NakamaClientGemSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
    }

    void NakamaClientGemSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
    }

    NakamaClientGemSystemComponent::NakamaClientGemSystemComponent()
    {
        if (NakamaClientGemInterface::Get() == nullptr)
        {
            NakamaClientGemInterface::Register(this);
        }
    }

    NakamaClientGemSystemComponent::~NakamaClientGemSystemComponent()
    {
        if (NakamaClientGemInterface::Get() == this)
        {
            NakamaClientGemInterface::Unregister(this);
        }
    }

    void NakamaClientGemSystemComponent::Init()
    {
    }

    void NakamaClientGemSystemComponent::Activate()
    {
        NakamaClientGemRequestBus::Handler::BusConnect();
        AZ::TickBus::Handler::BusConnect();
    }

    void NakamaClientGemSystemComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusDisconnect();
        NakamaClientGemRequestBus::Handler::BusDisconnect();
    }

    void NakamaClientGemSystemComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
    }

} // namespace NakamaClientGem
