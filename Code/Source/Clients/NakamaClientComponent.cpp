#include "NakamaClientComponent.h"

#include <AzCore/Component/Entity.h>
#include <AzCore/Component/TransformBus.h>
#include <AzCore/Component/ComponentApplicationBus.h>
#include <AzCore/Serialization/EditContext.h>

namespace NakamaClientGem
{
	NakamaClientComponent::NakamaClientComponent()
	{
	}

	NakamaClientComponent::~NakamaClientComponent()
	{
	}

	void NakamaClientComponent::Reflect(AZ::ReflectContext* rc)
	{

		if (auto sc = azrtti_cast<AZ::SerializeContext*>(rc))
		{
			sc->Class<NakamaClientComponent, AZ::Component>()
				->Field("Server Host", &NakamaClientComponent::m_serverHost)
				->Field("Server Port", &NakamaClientComponent::m_serverPort)
				->Field("Server Key", &NakamaClientComponent::m_serverKey)
                ->Version(1)
                ;
			if (AZ::EditContext* ec = sc->GetEditContext())
			{
				using namespace AZ::Edit::Attributes;
				ec->Class<NakamaClientComponent>("Nakama Client",
					"First person character controller")
					->ClassElement(AZ::Edit::ClassElements::EditorData, "")
					->Attribute(AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
					->Attribute(Category, "Nakama Client")
					->ClassElement(AZ::Edit::ClassElements::Group, "Multiplayer")
					->Attribute(AZ::Edit::Attributes::AutoExpand, false)
					->DataElement(nullptr,
						&NakamaClientComponent::m_serverHost,
						"Server Host", "Nakama Server Host")
					->DataElement(nullptr,
						&NakamaClientComponent::m_serverPort,
						"Server Port", "Nakama Server Port")
					->DataElement(nullptr,
						&NakamaClientComponent::m_serverKey,
						"Server Key", "Nakama Server Key")
					;
			}
		}

		/*
		if (auto bc = azrtti_cast<AZ::BehaviorContext*>(rc))
		{

			bc->EBus<NakamaClientNotificationBus>("NakamaClientNotificationBus")
				->Handler<NakamaClientNotificationHandler>();

			bc->EBus<NakamaClientComponentRequestBus>("FirstPersonControllerComponentRequestBus")
				->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
				->Attribute(AZ::Script::Attributes::Module, "controller")
				->Attribute(AZ::Script::Attributes::Category, "First Person Controller")
				->Event("Get Pointer To Active Camera Entity", &NakamaClientComponentRequests::GetActiveCameraEntityPtr)
				->Event("Get Active Camera EntityId", &FirstPersonControllerComponentRequests::GetActiveCameraEntityId)
				;
				
		}*/
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