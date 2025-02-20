
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
                ->Field("Server Host", &NakamaComponent::m_serverHost)
                ->Field("Server Port", &NakamaComponent::m_serverPort)
                ->Field("Server Key", &NakamaComponent::m_serverKey)
                ->Version(1)
                ;

            if (AZ::EditContext* editContext = serializeContext->GetEditContext())
            {
                editContext->Class<NakamaComponent>("NakamaComponent", "[Nakama Client for O3DE]")
                    ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                    ->Attribute(AZ::Edit::Attributes::Category, "Multiplayer")
                    ->Attribute(AZ::Edit::Attributes::Icon, "Icons/Components/Component_Placeholder.svg")
                    ->Attribute(AZ::Edit::Attributes::AppearsInAddComponentMenu, AZ_CRC_CE("Game"))
                    ->ClassElement(AZ::Edit::ClassElements::Group, "Server")
                    ->Attribute(AZ::Edit::Attributes::AutoExpand, false)
                    ->DataElement(nullptr,
                        &NakamaComponent::m_serverHost,
                        "Host", "Nakama Server Host")
                    ->DataElement(nullptr,
                        &NakamaComponent::m_serverPort,
                        "Port", "Nakama Server Port")
                    ->DataElement(nullptr,
                        &NakamaComponent::m_serverKey,
                        "Key", "Nakama Server Key")
                    ;
            }
        }

        if (AZ::BehaviorContext* behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
        {

            behaviorContext->Class<NakamaComponent>("Nakama Component")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaClient")
                ->Method("AuthenticateDevice",&NakamaComponent::AuthenticateDevice);
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
    void NakamaComponent::AuthenticateDevice(const AZStd::string& id, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        AZ_Warning("AuthenticateDevice", true, R"(%s %s %d %d)", id.c_str(), username.c_str(), create, vars.size());

        m_Client->authenticateDevice(
            id.c_str(),
            username.c_str(),
            create,
            {},
            [this](Nakama::NSessionPtr nSession)
            {
                OnAuthenticateSuccess(nSession);
            },
            [this](const Nakama::NError& nError)
            {
                OnAuthenticateFailed(nError);
            }
        );
    }
    void NakamaComponent::OnAuthenticateSuccess(const Nakama::NSessionPtr& session)
    {
        m_Session = session;
    }
    void NakamaComponent::OnAuthenticateFailed(const Nakama::NError&)
    {
    }
} // namespace NakamaClientGem
