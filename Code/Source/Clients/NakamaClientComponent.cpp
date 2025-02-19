#include "NakamaClientComponent.h"

namespace NakamaClientGem
{
	NakamaClientComponent::NakamaClientComponent()
	{
	}

	NakamaClientComponent::~NakamaClientComponent()
	{
	}

	void NakamaClientComponent::Reflect(AZ::ReflectContext* )
	{
		
	}

	void NakamaClientComponent::Init()
	{
	}

	void NakamaClientComponent::Activate()
	{
		AZ::TickBus::Handler::BusConnect();
		NakamaClientComponentRequestBus::Handler::BusConnect(GetEntityId());
	}

	void NakamaClientComponent::Deactivate()
	{
		AZ::TickBus::Handler::BusDisconnect();
		NakamaClientComponentRequestBus::Handler::BusDisconnect();
	}

	void NakamaClientComponent::GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType&)
	{
	}

	void NakamaClientComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
	{
		provided.push_back(AZ_CRC_CE("NakamaClientService"));
	}

	void NakamaClientComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
	{
		incompatible.push_back(AZ_CRC_CE("NakamaClientService"));
	}
	void NakamaClientComponent::OnTick(float, AZ::ScriptTimePoint)
	{
	}
}