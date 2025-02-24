
#include <NakamaComponent.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Serialization/EditContext.h>
#include <AzCore/RTTI/BehaviorContext.h>

#pragma warning(disable : 4100) // todo

namespace NakamaClientGem
{
    AZ_COMPONENT_IMPL(NakamaComponent, "NakamaComponent", "{629C555E-D148-442B-ADA9-9ED14ABB7539}");

    void NakamaComponent::Activate()
    {
        NakamaRequestBus::Handler::BusConnect(GetEntityId());
        AZ::TickBus::Handler::BusConnect();
    }

    void NakamaComponent::Deactivate()
    {
        AZ::TickBus::Handler::BusConnect();
        NakamaRequestBus::Handler::BusDisconnect(GetEntityId());
    }

    void NakamaComponent::ReflectDataTypes(AZ::ReflectContext* context)
    {
        RtClientDisconnectInfo::Reflect(context);
        RtError::Reflect(context);
        ChannelMessage::Reflect(context);
        UserPresence::Reflect(context);
        ChannelPresenceEvent::Reflect(context);
        MatchmakerUser::Reflect(context);
        MatchmakerMatched::Reflect(context);
        MatchData::Reflect(context);
        MatchPresenceEvent::Reflect(context);
        Notification::Reflect(context);
        NotificationList::Reflect(context);
        Party::Reflect(context);
        PartyClose::Reflect(context);
        PartyData::Reflect(context);
        PartyJoinRequest::Reflect(context);
        PartyLeader::Reflect(context);
        PartyMatchmakerTicket::Reflect(context);
        PartyPresenceEvent::Reflect(context);
        StatusPresenceEvent::Reflect(context);
        Stream::Reflect(context);
        StreamPresenceEvent::Reflect(context);
        StreamData::Reflect(context);
        StorageObjectWrite::Reflect(context);
        ReadStorageObjectId::Reflect(context);
        DeleteStorageObjectId::Reflect(context);
        User::Reflect(context);
        AccountDevice::Reflect(context);
        Account::Reflect(context);
        Friend::Reflect(context);
        FriendList::Reflect(context);
        Group::Reflect(context);
        GroupUser::Reflect(context);
        GroupList::Reflect(context);
        UserGroup::Reflect(context);
        UserGroupList::Reflect(context);
        LeaderboardRecord::Reflect(context);
        LeaderboardRecordList::Reflect(context);
        Tournament::Reflect(context);
        TournamentList::Reflect(context);
        TournamentRecordList::Reflect(context);
        Match::Reflect(context);
        MatchList::Reflect(context);
        ChannelMessageList::Reflect(context);
        StorageObject::Reflect(context);
        StorageObjectList::Reflect(context);
        StorageObjectAck::Reflect(context);
        Error::Reflect(context);
        Rpc::Reflect(context);
        PartyMatchmakerTicket::Reflect(context);
        Channel::Reflect(context);
        ChannelMessageAck::Reflect(context);
    }

    void NakamaComponent::Reflect(AZ::ReflectContext* context)
    {
        // Reflect datatypes before bus
        ReflectDataTypes(context);

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
            behaviorContext->EBus<NakamaListenerNotificationBus>("NakamaListenerNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaListenerNotification") 
                ->Handler<NakamaListenerNotificationHandler>();
            behaviorContext->EBus<NakamaAccountNotificationBus>("NakamaAccountNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaAccountNotification") 
                ->Handler<NakamaAccountNotificationHandler>();
            behaviorContext->EBus<NakamaFriendsNotificationBus>("NakamaFriendsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaFriendsNotification") 
                ->Handler<NakamaFriendsNotificationHandler>();
            behaviorContext->EBus<NakamaGroupsNotificationBus>("NakamaGroupsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaGroupsNotification") 
                ->Handler<NakamaGroupsNotificationHandler>();
            behaviorContext->EBus<NakamaLeaderboardsNotificationBus>("NakamaLeaderboardsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaLeaderboardsNotification") 
                ->Handler<NakamaLeaderboardsNotificationHandler>();
            behaviorContext->EBus<NakamaMatchesNotificationBus>("NakamaMatchesNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaMatchesNotification") 
                ->Handler<NakamaMatchesNotificationHandler>();
            behaviorContext->EBus<NakamaNotificationsNotificationBus>("NakamaNotificationsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaNotificationsNotification") 
                ->Handler<NakamaNotificationsNotificationHandler>();
            behaviorContext->EBus<NakamaChatNotificationBus>("NakamaChatNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaChatNotification") 
                ->Handler<NakamaChatNotificationHandler>();
            behaviorContext->EBus<NakamaStorageObjectsNotificationBus>("NakamaStorageObjectsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaStorageObjectsNotification") 
                ->Handler<NakamaStorageObjectsNotificationHandler>();
            behaviorContext->EBus<NakamaTournamentsNotificationBus>("NakamaTournamentsNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaTournamentsNotification") 
                ->Handler<NakamaTournamentsNotificationHandler>();
            behaviorContext->EBus<NakamaRpcNotificationBus>("NakamaRpcNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaRpcNotification") 
                ->Handler<NakamaRpcNotificationHandler>();
            behaviorContext->EBus<NakamaPartyNotificationBus>("NakamaPartyNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaPartyNotification") 
                ->Handler<NakamaPartyNotificationHandler>();
            behaviorContext->EBus<NakamaMatchmakerNotificationBus>("NakamaMatchmakerNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaMatchmakerNotification") 
                ->Handler<NakamaMatchmakerNotificationHandler>();

            behaviorContext->Class<NakamaComponent>("Nakama")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaClient")
                ->Method("AuthenticateDevice",&NakamaComponent::AuthenticateDevice)
                ->Method("AuthenticateEmail",&NakamaComponent::AuthenticateEmail)
                ->Method("AuthenticateFacebook", &NakamaComponent::AuthenticateFacebook)
                ->Method("AuthenticateGoogle", &NakamaComponent::AuthenticateGoogle)
                ->Method("AuthenticateGameCenter", &NakamaComponent::AuthenticateGameCenter)
                ->Method("AuthenticateApple", &NakamaComponent::AuthenticateApple)
                ->Method("AuthenticateCustom", &NakamaComponent::AuthenticateCustom)
                ->Method("AuthenticateSteam", &NakamaComponent::AuthenticateSteam)
                ->Method("linkFacebook", &NakamaComponent::linkFacebook)
                ->Method("linkEmail", &NakamaComponent::linkEmail)
                ->Method("linkDevice", &NakamaComponent::linkDevice)
                ->Method("linkGoogle", &NakamaComponent::linkGoogle)
                ->Method("linkGameCenter", &NakamaComponent::linkGameCenter)
                ->Method("linkApple", &NakamaComponent::linkApple)
                ->Method("linkSteam", &NakamaComponent::linkSteam)
                ->Method("linkCustom", &NakamaComponent::linkCustom)
                ->Method("unlinkFacebook", &NakamaComponent::unlinkFacebook)
                ->Method("unlinkEmail", &NakamaComponent::unlinkEmail)
                ->Method("unlinkGoogle", &NakamaComponent::unlinkGoogle)
                ->Method("unlinkGameCenter", &NakamaComponent::unlinkGameCenter)
                ->Method("unlinkApple", &NakamaComponent::unlinkApple)
                ->Method("unlinkSteam", &NakamaComponent::unlinkSteam)
                ->Method("unlinkDevice", &NakamaComponent::unlinkDevice)
                ->Method("unlinkCustom", &NakamaComponent::unlinkCustom)
                ->Method("importFacebookFriends", &NakamaComponent::importFacebookFriends)
                ->Method("getAccount", &NakamaComponent::getAccount)
                ->Method("updateAccount", &NakamaComponent::updateAccount)
                ->Method("getUsers", &NakamaComponent::getUsers)
                ->Method("addFriends", &NakamaComponent::addFriends)
                ->Method("deleteFriends", &NakamaComponent::deleteFriends)
                ->Method("blockFriends", &NakamaComponent::blockFriends)
                ->Method("listFriends", &NakamaComponent::listFriends)
                ->Method("createGroup", &NakamaComponent::createGroup)
                ->Method("deleteGroup", &NakamaComponent::deleteGroup)
                ->Method("addGroupUsers", &NakamaComponent::addGroupUsers)
                ->Method("listGroupUsers", &NakamaComponent::listGroupUsers)
                ->Method("kickGroupUsers", &NakamaComponent::kickGroupUsers)
                ->Method("joinGroup", &NakamaComponent::joinGroup)
                ->Method("leaveGroup", &NakamaComponent::leaveGroup)
                ->Method("listGroups", &NakamaComponent::listGroups)
                ->Method("listUserGroups", &NakamaComponent::listUserGroups)
                ->Method("listUserGroupsWithId", &NakamaComponent::listUserGroupsWithId)
                ->Method("promoteGroupUsers", &NakamaComponent::promoteGroupUsers)
                ->Method("demoteGroupUsers", &NakamaComponent::demoteGroupUsers)
                ->Method("updateGroup", &NakamaComponent::updateGroup)
                ->Method("listLeaderboardRecords", &NakamaComponent::listLeaderboardRecords)
                ->Method("listLeaderboardRecordsAroundOwner", &NakamaComponent::listLeaderboardRecordsAroundOwner)
                ->Method("writeLeaderboardRecord", &NakamaComponent::writeLeaderboardRecord)
                ->Method("deleteLeaderboardRecord", &NakamaComponent::deleteLeaderboardRecord)
                ->Method("writeTournamentRecord", &NakamaComponent::writeTournamentRecord)
                ->Method("listTournaments", &NakamaComponent::listTournaments)
                ->Method("listTournamentRecords", &NakamaComponent::listTournamentRecords)
                ->Method("listTournamentRecordsAroundOwner", &NakamaComponent::listTournamentRecordsAroundOwner)
                ->Method("joinTournament", &NakamaComponent::joinTournament)
                ->Method("listMatches", &NakamaComponent::listMatches)
                ->Method("listNotifications", &NakamaComponent::listNotifications)
                ->Method("deleteNotifications", &NakamaComponent::deleteNotifications)
                ->Method("listChannelMessages", &NakamaComponent::listChannelMessages)
                ->Method("listStorageObjects", &NakamaComponent::listStorageObjects)
                ->Method("listUsersStorageObjects", &NakamaComponent::listUsersStorageObjects)
                ->Method("writeStorageObjects", &NakamaComponent::writeStorageObjects)
                ->Method("readStorageObjects", &NakamaComponent::readStorageObjects)
                ->Method("deleteStorageObjects", &NakamaComponent::deleteStorageObjects)
                ->Method("rpc", &NakamaComponent::rpc)
                ->Method("rpcWithId", &NakamaComponent::rpcWithId)
                ->Method("joinChat", &NakamaComponent::joinChat)
                ->Method("leaveChat", &NakamaComponent::leaveChat)
                ->Method("writeChatMessage", &NakamaComponent::writeChatMessage)
                ->Method("updateChatMessage", &NakamaComponent::updateChatMessage)
                ->Method("removeChatMessage", &NakamaComponent::removeChatMessage)
                ->Method("createMatch", &NakamaComponent::createMatch)
                ->Method("joinMatch", &NakamaComponent::joinMatch)
                ->Method("joinMatchByToken", &NakamaComponent::joinMatchByToken)
                ->Method("leaveMatch", &NakamaComponent::leaveMatch)
                ->Method("addMatchmaker", &NakamaComponent::addMatchmaker)
                ->Method("removeMatchmaker", &NakamaComponent::removeMatchmaker)
                ->Method("sendMatchData", &NakamaComponent::sendMatchData)
                ->Method("followUsers", &NakamaComponent::followUsers)
                ->Method("unfollowUsers", &NakamaComponent::unfollowUsers)
                ->Method("updateStatus", &NakamaComponent::updateStatus)
                ->Method("rtRpc", &NakamaComponent::rtRpc)
                ->Method("acceptPartyMember", &NakamaComponent::acceptPartyMember)
                ->Method("addMatchmakerParty", &NakamaComponent::addMatchmakerParty)
                ->Method("closeParty", &NakamaComponent::closeParty)
                ->Method("createParty", &NakamaComponent::createParty)
                ->Method("joinParty", &NakamaComponent::joinParty)
                ->Method("leaveParty", &NakamaComponent::leaveParty)
                ->Method("listPartyJoinRequests", &NakamaComponent::listPartyJoinRequests)
                ->Method("promotePartyMember", &NakamaComponent::promotePartyMember)
                ->Method("removeMatchmakerParty", &NakamaComponent::removeMatchmakerParty)
                ->Method("removePartyMember", &NakamaComponent::removePartyMember)
                ->Method("sendPartyData", &NakamaComponent::sendPartyData)
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
    void NakamaComponent::OnTick([[maybe_unused]] float deltaTime, [[maybe_unused]] AZ::ScriptTimePoint time)
    {
        if (m_Client)
            m_Client->tick();
        if (m_RtClient)
            m_RtClient->tick();

        if (!m_Session)
            return;

        if (m_Session->getExpireTime() > getUnixTimestampMs() + 5000)
        {
            authenticateRefresh();
        }
    }
    void NakamaComponent::AuthenticateDevice(const AZStd::string& id, const AZStd::string& username, bool create, const AZStringMap& vars)
    {        
        Nakama::opt::optional<std::string> nUsername;
        if (!username.empty())
            nUsername = username.c_str();
        else
            nUsername = Nakama::opt::nullopt;
        m_Client->authenticateDevice(
            id.c_str(),
            nUsername,
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateEmail(const AZStd::string& email, const AZStd::string& password, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateEmail(
            email.c_str(),
            password.c_str(),
            username.c_str(),
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateFacebook(const AZStd::string& accessToken, const AZStd::string& username, bool create, bool importFriends, const AZStringMap& vars)
    {
        m_Client->authenticateFacebook(
            accessToken.c_str(),
            username.c_str(),
            create,
            importFriends,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateGoogle(const AZStd::string& accessToken, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateGoogle(
            accessToken.c_str(),
            username.c_str(),
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZStd::sys_time_t timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateGameCenter(
            playerId.c_str(),
            bundleId.c_str(),
            timestampSeconds,
            salt.c_str(),
            signature.c_str(),
            publicKeyUrl.c_str(),
            username.c_str(),
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateApple(const AZStd::string& token, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateApple(
            token.c_str(),
            username.c_str(),
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateCustom(const AZStd::string& id, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateCustom(
            id.c_str(),
            username.c_str(),
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::AuthenticateSteam(const AZStd::string& token, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        Nakama::opt::optional<std::string> nUsername;
        if (!username.empty())
            nUsername = username.c_str();
        else
            nUsername = Nakama::opt::nullopt;
        m_Client->authenticateDevice(
            token.c_str(),
            nUsername,
            create,
            AZStringMapToNakama(vars),
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
    void NakamaComponent::authenticateRefresh()
    {
        if (m_RtClient->isConnected())
        {
            m_Client->authenticateRefresh(m_Session,
                [this](Nakama::NSessionPtr nSession) {
                    m_Session = nSession;
                },
                [](const Nakama::NError& nError) {
                    NakamaListenerNotificationBus::Broadcast(
                        &NakamaListenerNotificationBus::Events::OnError, 
                        Error::FromNakama(nError));
                });
        }
    }
    void NakamaComponent::linkFacebook(const AZStd::string& accessToken, bool importFriends)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkFacebook(
            m_Session,
            accessToken.c_str(),
            importFriends,
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkEmail(const AZStd::string& email, const AZStd::string& password)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkFacebook(
            m_Session,
            email.c_str(),
            password.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkDevice(const AZStd::string& id)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkDevice(
            m_Session,
            id.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkGoogle(const AZStd::string& accessToken)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkGoogle(
            m_Session,
            accessToken.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZ::u64 timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkGameCenter(
            m_Session,
            playerId.c_str(),
            bundleId.c_str(),
            timestampSeconds,
            salt.c_str(),
            signature.c_str(),
            publicKeyUrl.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkApple(const AZStd::string& token)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkApple(
            m_Session,
            token.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkSteam(const AZStd::string& token)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkSteam(
            m_Session,
            token.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::linkCustom(const AZStd::string& id)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->linkCustom(
            m_Session,
            id.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkFacebook(const AZStd::string& accessToken)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkFacebook(
            m_Session,
            accessToken.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkEmail(const AZStd::string& email, const AZStd::string& password)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkEmail(
            m_Session,
            email.c_str(),
            password.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkGoogle(const AZStd::string& accessToken)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkGoogle(
            m_Session,
            accessToken.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZ::u64 timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkGameCenter(
            m_Session,
            playerId.c_str(),
            bundleId.c_str(),
            timestampSeconds,
            salt.c_str(),
            signature.c_str(),
            publicKeyUrl.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkApple(const AZStd::string& token)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkApple(
            m_Session,
            token.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkSteam(const AZStd::string& token)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkSteam(
            m_Session,
            token.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkDevice(const AZStd::string& id)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkDevice(
            m_Session,
            id.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::unlinkCustom(const AZStd::string& id)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->unlinkCustom(
            m_Session,
            id.c_str(),
            [this]()
            {
                OnLinkSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnLinkFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::importFacebookFriends(const AZStd::string& token, bool reset)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->importFacebookFriends(
            m_Session,
            token.c_str(),
            reset,
            [this]()
            {
                OnImportFacebookFriendsSuccess();
            },
            [this](const Nakama::NError& nError)
            {
                OnImportFacebookFriendsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::getAccount()
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->getAccount(
            m_Session,
            [this](const Nakama::NAccount& account)
            {
                OnGetAccountSuccess(Account::FromNakama(account));
            },
            [this](const Nakama::NError& nError)
            {
                OnGetAccountFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::updateAccount(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        Nakama::opt::optional<std::string> n_username = Nakama::opt::nullopt;
        if (!username.empty())
        {
            n_username = username.c_str();
        }
        Nakama::opt::optional<std::string> n_displayName = Nakama::opt::nullopt;
        if (!displayName.empty())
        {
            n_displayName = displayName.c_str();
        }
        Nakama::opt::optional<std::string> n_avatarUrl = Nakama::opt::nullopt;
        if (!avatarUrl.empty())
        {
            n_avatarUrl = avatarUrl.c_str();
        }
        Nakama::opt::optional<std::string> n_langTag = Nakama::opt::nullopt;
        if (!langTag.empty())
        {
            n_langTag = langTag.c_str();
        }
        Nakama::opt::optional<std::string> n_location = Nakama::opt::nullopt;
        if (!location.empty())
        {
            n_location = location.c_str();
        }
        Nakama::opt::optional<std::string> n_timezone = Nakama::opt::nullopt;
        if (!timezone.empty())
        {
            n_timezone = timezone.c_str();
        }
        m_Client->updateAccount(
            m_Session,
            n_username,
            n_displayName,
            n_avatarUrl,
            n_langTag,
            n_location,
            n_timezone,
            [this, username, displayName, avatarUrl, langTag, location, timezone]()
            {
                OnUpdateAccountSuccess(username, displayName, avatarUrl, langTag, location, timezone);
            },
            [this](const Nakama::NError& nError)
            {
                OnUpdateAccountFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::getUsers(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames, const AZStd::vector<AZStd::string>& facebookIds)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        std::vector<std::string> n_usernames;
        if (usernames.size() > 0)
        {
            for (auto& username : usernames)
            {
                n_usernames.push_back(username.c_str());
            }
        }
        std::vector<std::string> n_facebookIds;
        if (facebookIds.size() > 0)
        {
            for (auto& facebookId : facebookIds)
            {
                n_facebookIds.push_back(facebookId.c_str());
            }
        }

        m_Client->getUsers(
            m_Session,
            n_ids,
            n_usernames,
            n_facebookIds,
            [this](const Nakama::NUsers& nUsers)
            {
                AZStd::vector<User> users;
                if (nUsers.users.size() > 0)
                {
                    for (auto& user : nUsers.users)
                    {
                        users.push_back(User::FromNakama(user));
                    }
                }
                OnGetUsersSuccess(users);
            },
            [this](const Nakama::NError& nError)
            {
                OnGetUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::addFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        std::vector<std::string> n_usernames;
        if (usernames.size() > 0)
        {
            for (auto& username : usernames)
            {
                n_usernames.push_back(username.c_str());
            }
        }
        m_Client->addFriends(
            m_Session,
            n_ids,
            n_usernames,
            [this, ids, usernames]()
            {
                OnAddFriendsSuccess(ids, usernames);
            },
            [this](const Nakama::NError& nError)
            {
                OnAddFriendsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::deleteFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        std::vector<std::string> n_usernames;
        if (usernames.size() > 0)
        {
            for (auto& username : usernames)
            {
                n_usernames.push_back(username.c_str());
            }
        }
        m_Client->deleteFriends(
            m_Session,
            n_ids,
            n_usernames,
            [this, ids, usernames]()
            {
                OnDeleteFriendsSuccess(ids, usernames);
            },
            [this](const Nakama::NError& nError)
            {
                OnDeleteFriendsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::blockFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        std::vector<std::string> n_usernames;
        if (usernames.size() > 0)
        {
            for (auto& username : usernames)
            {
                n_usernames.push_back(username.c_str());
            }
        }
        m_Client->blockFriends(
            m_Session,
            n_ids,
            n_usernames,
            [this, ids, usernames]()
            {
                OnBlockFriendsSuccess(ids, usernames);
            },
            [this](const Nakama::NError& nError)
            {
                OnBlockFriendsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listFriends(AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listFriends(
            m_Session,
            limit,
            static_cast<Nakama::NFriend::State>(state),
            cursor.c_str(),
            [this, limit, state, cursor](Nakama::NFriendListPtr nFriends)
            {
                AZStd::vector<Friend> friends;
                if (nFriends->friends.size() > 0)
                {
                    for (auto& friend_ : nFriends->friends)
                    {
                        friends.push_back(Friend::FromNakama(friend_));
                    }
                }
                OnListFriendsSuccess(friends, limit, state, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListFriendsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::createGroup(const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open, AZ::s32 maxCount)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->createGroup(
            m_Session,
            name.c_str(),
            description.c_str(),
            avatarUrl.c_str(),
            langTag.c_str(),
            open,
            maxCount,
            [this](const Nakama::NGroup& nGroup)
            {
                OnCreateGroupSuccess(Group::FromNakama(nGroup));
            },
            [this](const Nakama::NError& nError)
            {
                OnCreateGroupFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::deleteGroup(const AZStd::string& groupId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->deleteGroup(
            m_Session,
            groupId.c_str(),
            [this, groupId]()
            {
                OnDeleteGroupSuccess(groupId);
            },
            [this](const Nakama::NError& nError)
            {
                OnDeleteGroupFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::addGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        m_Client->addGroupUsers(
            m_Session,
            groupId.c_str(),
            n_ids,
            [this, groupId, ids]()
            {
                OnAddGroupUsersSuccess(groupId, ids);
            },
            [this](const Nakama::NError& nError)
            {
                OnAddGroupUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listGroupUsers(const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listGroupUsers(
            m_Session,
            groupId.c_str(),
            limit,
            static_cast<Nakama::NUserGroupState>(state),
            cursor.c_str(),
            [this, groupId, limit, state, cursor](Nakama::NGroupUserListPtr nGroupUsers)
            {
                GroupUserList userList = GroupUserList::FromNakama(*nGroupUsers);
                OnListGroupUsersSuccess(userList, groupId,  limit, state, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListGroupUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::kickGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        m_Client->kickGroupUsers(
            m_Session,
            groupId.c_str(),
            n_ids,
            [this, groupId, ids]()
            {
                OnKickGroupUsersSuccess(groupId, ids);
            },
            [this](const Nakama::NError& nError)
            {
                OnKickGroupUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::joinGroup(const AZStd::string& groupId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->joinGroup(
            m_Session,
            groupId.c_str(),
            [this, groupId]()
            {
                OnJoinGroupSuccess(groupId);
            },
            [this](const Nakama::NError& nError)
            {
                OnJoinGroupFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::leaveGroup(const AZStd::string& groupId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->leaveGroup(
            m_Session,
            groupId.c_str(),
            [this, groupId]()
            {
                OnLeaveGroupSuccess(groupId);
            },
            [this](const Nakama::NError& nError)
            {
                OnLeaveGroupFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listGroups(const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listGroups(
            m_Session,
            name.c_str(),
            limit,
            cursor.c_str(),
            [this, name, limit, cursor](Nakama::NGroupListPtr nGroups)
            {
                GroupList groupList = GroupList::FromNakama(*nGroups);
                OnListGroupsSuccess(groupList, name, limit, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListGroupsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listUserGroups(AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listUserGroups(
            m_Session,
            limit,
            static_cast<Nakama::NUserGroupState>(state),
            cursor.c_str(),
            [this, limit, state, cursor](Nakama::NUserGroupListPtr nUserGroups)
            {
                UserGroupList userGroupList = UserGroupList::FromNakama(*nUserGroups);
                OnListUserGroupsSuccess(userGroupList, limit, state, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListUserGroupsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listUserGroupsWithId(const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listUserGroups(
            m_Session,
            userId.c_str(),
            limit,
            static_cast<Nakama::NUserGroupState>(state),
            cursor.c_str(),
            [this, userId, limit, state, cursor](Nakama::NUserGroupListPtr nUserGroups)
            {
                UserGroupList userGroupList = UserGroupList::FromNakama(*nUserGroups);
                OnListUserGroupsWithIdSuccess(userGroupList, userId, limit, state, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListUserGroupsWithIdFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::promoteGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        m_Client->promoteGroupUsers(
            m_Session,
            groupId.c_str(),
            n_ids,
            [this, groupId, ids]()
            {
                OnPromoteGroupUsersSuccess(groupId, ids);
            },
            [this](const Nakama::NError& nError)
            {
                OnPromoteGroupUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::demoteGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ids;
        if (ids.size() > 0)
        {
            for (auto& id : ids)
            {
                n_ids.push_back(id.c_str());
            }
        }
        m_Client->demoteGroupUsers(
            m_Session,
            groupId.c_str(),
            n_ids,
            [this, groupId, ids]()
            {
                OnDemoteGroupUsersSuccess(groupId, ids);
            },
            [this](const Nakama::NError& nError)
            {
                OnDemoteGroupUsersFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::updateGroup(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->updateGroup(
            m_Session,
            groupId.c_str(),
            name.c_str(),
            description.c_str(),
            avatarUrl.c_str(),
            langTag.c_str(),
            open,
            [this, groupId, name, description, avatarUrl, langTag, open]()
            {
                OnUpdateGroupSuccess(groupId, name, description, avatarUrl, langTag, open);
            },
            [this](const Nakama::NError& nError)
            {
                OnUpdateGroupFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listLeaderboardRecords(const AZStd::string& leaderboardId, const AZStd::vector<AZStd::string>& ownerIds, AZ::s32 limit, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ownerIds;
        if (ownerIds.size() > 0)
        {
            for (auto& ownerId : ownerIds)
            {
                n_ownerIds.push_back(ownerId.c_str());
            }
        }
        m_Client->listLeaderboardRecords(
            m_Session,
            leaderboardId.c_str(),
            n_ownerIds,
            limit,
            cursor.c_str(),
            [this, leaderboardId, ownerIds, limit, cursor](Nakama::NLeaderboardRecordListPtr nLeaderboardRecords)
            {
                LeaderboardRecordList leaderboardRecordList = LeaderboardRecordList::FromNakama(*nLeaderboardRecords);
                OnListLeaderboardRecordsSuccess(leaderboardRecordList, leaderboardId, ownerIds, limit, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListLeaderboardRecordsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listLeaderboardRecordsAroundOwner(const AZStd::string& leaderboardId, const AZStd::string& ownerId, AZ::s32 limit)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listLeaderboardRecordsAroundOwner(
            m_Session,
            leaderboardId.c_str(),
            ownerId.c_str(),
            limit,
            [this, leaderboardId, ownerId, limit](Nakama::NLeaderboardRecordListPtr nLeaderboardRecords)
            {
                LeaderboardRecordList leaderboardRecordList = LeaderboardRecordList::FromNakama(*nLeaderboardRecords);
                OnListLeaderboardRecordsAroundOwnerSuccess(leaderboardRecordList, leaderboardId, ownerId, limit);
            },
            [this](const Nakama::NError& nError)
            {
                OnListLeaderboardRecordsAroundOwnerFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::writeLeaderboardRecord(const AZStd::string& leaderboardId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->writeLeaderboardRecord(
            m_Session,
            leaderboardId.c_str(),
            score,
            subscore,
            metadata.c_str(),
            [this, leaderboardId, score, subscore, metadata](Nakama::NLeaderboardRecord record)
            {
                LeaderboardRecord leaderboardRecord = LeaderboardRecord::FromNakama(record);
                OnWriteLeaderboardRecordSuccess(leaderboardRecord, leaderboardId, score, subscore, metadata);
            },
            [this](const Nakama::NError& nError)
            {
                OnWriteLeaderboardRecordFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::deleteLeaderboardRecord(const AZStd::string& leaderboardId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->deleteLeaderboardRecord(
            m_Session,
            leaderboardId.c_str(),
            [this, leaderboardId]()
            {
                OnDeleteLeaderboardRecordSuccess(leaderboardId);
            },
            [this](const Nakama::NError& nError)
            {
                OnDeleteLeaderboardRecordFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::writeTournamentRecord(const AZStd::string& tournamentId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->writeTournamentRecord(
            m_Session,
            tournamentId.c_str(),
            score,
            subscore,
            metadata.c_str(),
            [this](Nakama::NLeaderboardRecord record)
            {
                OnWriteTournamentRecordSuccess(LeaderboardRecord::FromNakama(record));
            },
            [this](const Nakama::NError& nError)
            {
                OnWriteTournamentRecordFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listTournaments(AZ::u32 categoryStart, AZ::u32 categoryEnd, AZ::u32 startTime, AZ::u32 endTime, AZ::s32 limit, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listTournaments(
            m_Session,
            categoryStart,
            categoryEnd,
            startTime,
            endTime,
            limit,
            cursor.c_str(),
            [this, categoryStart, categoryEnd, startTime, endTime, limit, cursor](Nakama::NTournamentListPtr nTournamentList)
            {
                TournamentList tournamentList = TournamentList::FromNakama(*nTournamentList);
                OnListTournamentsSuccess(tournamentList, categoryStart, categoryEnd, startTime, endTime, limit, cursor);
            },
            [this](const Nakama::NError& nError)
            {
                OnListTournamentsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listTournamentRecords(const AZStd::string& tournamentId, AZ::s32 limit, const AZStd::string& cursor, const AZStd::vector<AZStd::string>& ownerIds)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<std::string> n_ownerIds;
        if (ownerIds.size() > 0)
        {
            for (const auto& ownerId : ownerIds)
            {
                n_ownerIds.push_back(ownerId.c_str());
            }
        }
        m_Client->listTournamentRecords(
            m_Session,
            tournamentId.c_str(),
            limit,
            cursor.c_str(),
            n_ownerIds,
            [this, tournamentId, limit, cursor, ownerIds](Nakama::NTournamentRecordListPtr nTournamentRecordList)
            {
                TournamentRecordList tournamentRecordList = TournamentRecordList::FromNakama(*nTournamentRecordList);
                OnListTournamentRecordsSuccess(tournamentRecordList, tournamentId, limit, cursor, ownerIds);
            },
            [this](const Nakama::NError& nError)
            {
                OnListTournamentRecordsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listTournamentRecordsAroundOwner(const AZStd::string& tournamentId, const AZStd::string& ownerId, AZ::s32 limit)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listTournamentRecordsAroundOwner(
            m_Session,
            tournamentId.c_str(),
            ownerId.c_str(),
            limit,
            [this, tournamentId, ownerId, limit](Nakama::NTournamentRecordListPtr nTournamentRecordList)
            {
                TournamentRecordList tournamentRecordList = TournamentRecordList::FromNakama(*nTournamentRecordList);
                OnListTournamentRecordsAroundOwnerSuccess(tournamentRecordList, tournamentId, ownerId, limit);
            },
            [this](const Nakama::NError& nError)
            {
                OnListTournamentRecordsAroundOwnerFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::joinTournament(const AZStd::string& tournamentId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->joinTournament(
            m_Session,
            tournamentId.c_str(),
            [this, tournamentId]()
            {
                OnJoinTournamentSuccess(tournamentId);
            },
            [this](const Nakama::NError& nError)
            {
                OnJoinTournamentFailed(Error::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::listMatches(AZ::s32 min_size, AZ::s32 max_size, AZ::s32 limit, const AZStd::string& label, const AZStd::string& query, bool authoritative)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listMatches(
            m_Session,
            min_size,
            max_size,
            limit,
            label.c_str(),
            query.c_str(),
            authoritative,
            [this, min_size, max_size, limit, label, query, authoritative](Nakama::NMatchListPtr nMatchList)
            {
                MatchList matchList = MatchList::FromNakama(*nMatchList);
                OnListMatchesSuccess(matchList, min_size, max_size, limit, label, query, authoritative);
            },
            [this](const Nakama::NError& nError)
            {
                OnListMatchesFailed(Error::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::createMatch()
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->createMatch(
            [this](const Nakama::NMatch& nMatch)
            {
                Match match = Match::FromNakama(nMatch);
                OnCreateMatchSuccess(match);
            },
            [this](const Nakama::NRtError& nError)
            {
                OnCreateMatchFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::joinMatch(const AZStd::string& matchId, const AZStringMap& metadata)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }

        m_RtClient->joinMatch(
            matchId.c_str(),
            AZStringMapToNakama(metadata),
            [this](const Nakama::NMatch& nMatch)
            {
                Match match = Match::FromNakama(nMatch);
                OnJoinMatchSuccess(match);
            },
            [this](const Nakama::NRtError& nError)
            {
                OnJoinMatchFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::joinMatchByToken(const AZStd::string& token)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->joinMatchByToken(
            token.c_str(),
            [this](const Nakama::NMatch& nMatch)
            {
                OnJoinMatchByTokenSuccess(Match::FromNakama(nMatch));
            },
            [this](const Nakama::NRtError& nError)
            {
                OnJoinMatchByTokenFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::leaveMatch(const AZStd::string& matchId)
    {
		if (!m_Session)
		{
			OnUnauthenticated();
			return;
		}
		if (!m_RtClient->isConnected())
		{
			OnRtClientNotConnected();
			return;
		}
		m_RtClient->leaveMatch(
			matchId.c_str(),
			[this, matchId]()
			{
				OnLeaveMatchSuccess(matchId);
			},
			[this](const Nakama::NRtError& nError)
			{
				OnLeaveMatchFailed(RtError::FromNakama(nError));
			}
		);
    }

    void NakamaComponent::sendMatchData(const AZStd::string& matchId, AZ::s64 opCode, const AZStd::string& data, const AZStd::vector<UserPresence>& presences)
    {
		if (!m_Session)
		{
			OnUnauthenticated();
			return;
		}
		if (!m_RtClient->isConnected())
		{
			OnRtClientNotConnected();
			return;
		}
		std::vector<Nakama::NUserPresence> nPresences;
		for (const auto& presence : presences)
		{
			nPresences.push_back(UserPresence::ToNakama(presence));
		}
		m_RtClient->sendMatchData(
			matchId.c_str(),
			opCode,
			data.c_str(),
			nPresences
		);
    }

    void NakamaComponent::listNotifications(AZ::s32 limit, const AZStd::string& cacheableCursor)
    {
		if (!m_Session)
		{
			OnUnauthenticated();
			return;
		}
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
		m_Client->listNotifications(
			m_Session,
			limit,
			cacheableCursor.c_str(),
			[this, limit, cacheableCursor](Nakama::NNotificationListPtr nNotificationList)
			{
				NotificationList notificationList = NotificationList::FromNakama(*nNotificationList);
				OnListNotificationsSuccess(notificationList, limit, cacheableCursor);
			},
			[this](const Nakama::NError& nError)
			{
				OnListNotificationsFailed(Error::FromNakama(nError));
			}
		);
    }

    void NakamaComponent::deleteNotifications(const AZStd::vector<AZStd::string>& notificationIds)
    {
        if (!m_Session)
        {
			OnUnauthenticated();
			return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
		std::vector<std::string> n_notificationIds;
		if (notificationIds.size() > 0)
		{
			for (auto& notificationId : notificationIds)
			{
				n_notificationIds.push_back(notificationId.c_str());
			}
		}
        m_Client->deleteNotifications(
            m_Session,
            n_notificationIds,
            [this, notificationIds]()
            {
                OnDeleteNotificationsSuccess(notificationIds);
            },
            [this](const Nakama::NError& nError)
            {
                OnDeleteNotificationsFailed(Error::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::listChannelMessages(const AZStd::string& channelId, AZ::s32 limit, const AZStd::string& cursor, bool forward)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listChannelMessages(
            m_Session,
            channelId.c_str(),
            limit,
            cursor.c_str(),
            forward,
            [this](Nakama::NChannelMessageListPtr messageList)
            {
                OnListChannelMessagesSuccess(ChannelMessageList::FromNakama(*messageList));
            },
            [this](const Nakama::NError& nError)
            {
                OnListChannelMessagesFailed(Error::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::joinChat(const AZStd::string& target, AZ::u8 channelType, bool persistence, bool hidden)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->joinChat(
            target.c_str(),
            static_cast<Nakama::NChannelType>(channelType),
            persistence,
            hidden,
            [this](Nakama::NChannelPtr nChannel)
            {
                OnJoinChatSuccess(Channel::FromNakama(*nChannel));
            },
            [this](const Nakama::NRtError& nError)
            {
                OnJoinChatFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::leaveChat(const AZStd::string& channelId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->leaveChat(
            channelId.c_str(),
            [this, channelId]()
            {
                OnLeaveChatSuccess(channelId);
            },
            [this](const Nakama::NRtError& nError)
            {
                OnLeaveChatFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::writeChatMessage(const AZStd::string& channelId, const AZStd::string& content)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->writeChatMessage(
            channelId.c_str(),
            content.c_str(),
            [this](const Nakama::NChannelMessageAck& nAck)
            {
                OnWriteChatMessageSuccess(ChannelMessageAck::FromNakama(nAck));
            },
            [this](const Nakama::NRtError& nError)
            {
                OnWriteChatMessageFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::updateChatMessage(const AZStd::string& channelId, const AZStd::string& messageId, const AZStd::string& content)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->updateChatMessage(
            channelId.c_str(),
            messageId.c_str(),
            content.c_str(),
            [this](const Nakama::NChannelMessageAck& nAck)
            {
                OnUpdateChatMessageSuccess(ChannelMessageAck::FromNakama(nAck));
            },
            [this](const Nakama::NRtError& nError)
            {
                OnUpdateChatMessageFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::removeChatMessage(const AZStd::string& channelId, const AZStd::string& messageId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->removeChatMessage(
            channelId.c_str(),
            messageId.c_str(),
            [this](const Nakama::NChannelMessageAck& nAck)
            {
                OnRemoveChatMessageSuccess(ChannelMessageAck::FromNakama(nAck));
            },
            [this](const Nakama::NRtError& nError)
            {
                OnRemoveChatMessageFailed(RtError::FromNakama(nError));
            }
        );
    }

    void NakamaComponent::sendPartyData(const AZStd::string& partyId, AZ::s32 opCode, AZStd::string& data)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::NBytes nData = data.c_str();
        m_RtClient->sendPartyData(
            partyId.c_str(),
            opCode,
            nData
        );
    }

    void NakamaComponent::OnConnect()
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnConnect
        );
    }
    void NakamaComponent::OnDisconnect(const RtClientDisconnectInfo& info)
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnDisconnect,
            info
        );
    }
    void NakamaComponent::OnAuthenticateSuccess(const Nakama::NSessionPtr& session)
    {
        m_Session = session;

        m_Listener.setConnectCallback([this]() {
            OnConnect();
            });
        m_Listener.setDisconnectCallback([this](const Nakama::NRtClientDisconnectInfo& nInfo) {
            OnDisconnect(RtClientDisconnectInfo::FromNakama(nInfo));
            });

        m_Listener.setErrorCallback([](const Nakama::NRtError& nError) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnRtError,
                RtError::FromNakama(nError)
            );
            });
        m_Listener.setChannelMessageCallback([](const Nakama::NChannelMessage& nMessage) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnChannelMessage, 
                ChannelMessage::FromNakama(nMessage)
            );
            });
        m_Listener.setChannelPresenceCallback([](const Nakama::NChannelPresenceEvent& nEvent) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnChannelPresence,
                ChannelPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setMatchmakerMatchedCallback([](Nakama::NMatchmakerMatchedPtr matchedPtr) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnMatchmakerMatched, 
                MatchmakerMatched::FromNakama(*matchedPtr));
            });
        m_Listener.setMatchDataCallback([](const Nakama::NMatchData& nData) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnMatchData, 
                MatchData::FromNakama(nData));
            });
        m_Listener.setMatchPresenceCallback([](const Nakama::NMatchPresenceEvent& nEvent) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnMatchPresence,
                MatchPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setNotificationsCallback([](const Nakama::NNotificationList& nList) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnNotifications, 
                NotificationList::FromNakama(nList));
            });
        m_Listener.setPartyCallback([](const Nakama::NParty& nParty) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnParty, 
                Party::FromNakama(nParty));
            });
        m_Listener.setPartyCloseCallback([](const Nakama::NPartyClose& nPartyClose) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyClosed, 
                PartyClose::FromNakama(nPartyClose));
            });
        m_Listener.setPartyDataCallback([](const Nakama::NPartyData& nData) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyData, 
                PartyData::FromNakama(nData));
            });
        m_Listener.setPartyJoinRequestCallback([](const Nakama::NPartyJoinRequest& nRequest) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyJoinRequest, 
                PartyJoinRequest::FromNakama(nRequest));
            });
        m_Listener.setPartyLeaderCallback([](const Nakama::NPartyLeader& nLeader) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyLeader, 
                PartyLeader::FromNakama(nLeader));
            });
        m_Listener.setPartyMatchmakerTicketCallback([](const Nakama::NPartyMatchmakerTicket& nTicket) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyMatchmakerTicket, 
                PartyMatchmakerTicket::FromNakama(nTicket));
            });
        m_Listener.setPartyPresenceCallback([](const Nakama::NPartyPresenceEvent& nEvent) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnPartyPresence, 
                PartyPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStatusPresenceCallback([](const Nakama::NStatusPresenceEvent& nEvent) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnStatusPresence, 
                StatusPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStreamPresenceCallback([](const Nakama::NStreamPresenceEvent& nEvent) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnStreamPresence, 
                StreamPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStreamDataCallback([](const Nakama::NStreamData& nData) {
            NakamaListenerNotificationBus::Broadcast(
                &NakamaListenerNotificationBus::Events::OnStreamData, 
                StreamData::FromNakama(nData));
            });

        m_RtClient->setListener(&m_Listener);

        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnAuthenticateSuccess,
            m_Session->getUsername().c_str(),
            m_Session->getUserId().c_str()
        );

        m_RtClient->connect(m_Session, true);
    }
    void NakamaComponent::OnAuthenticateFailed(const Nakama::NError& error)
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnAuthenticateFailed,
            static_cast<AZ::s8>(error.code),
            error.message.c_str()
        );
    }
    void NakamaComponent::OnLinkSuccess()
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnLinkSuccess
        );
    }
    void NakamaComponent::OnLinkFailed(const Error& error)
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnLinkFailed,
            error
        );
    }
    void NakamaComponent::OnUnlinkSuccess()
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnUnlinkSuccess
        );
    }
    void NakamaComponent::OnUnlinkFailed(const Error& error)
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnUnlinkFailed,
            error
        );
    }
    void NakamaComponent::OnImportFacebookFriendsSuccess()
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnImportFacebookFriendsSuccess
        );
    }
    void NakamaComponent::OnImportFacebookFriendsFailed(const Error& error)
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnImportFacebookFriendsFailed,
            error
        );
    }
    void NakamaComponent::OnUnauthenticated()
    {
        NakamaListenerNotificationBus::Broadcast(
            &NakamaListenerNotificationBus::Events::OnUnauthenticated
        );
    }
    void NakamaComponent::OnGetAccountSuccess(const Account& account)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnGetAccountSuccess,
            account
        );
    }
    void NakamaComponent::OnGetAccountFailed(const Error& error)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnGetAccountFailed,
            error
        );
    }
    void NakamaComponent::OnUpdateAccountSuccess(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnUpdateAccountSuccess,
            username,
            displayName,
            avatarUrl,
            langTag,
            location,
            timezone
        );
    }
    void NakamaComponent::OnUpdateAccountFailed(const Error& error)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnUpdateAccountFailed,
            error
        );
    }
    void NakamaComponent::OnGetUsersSuccess(const AZStd::vector<User>& users)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnGetUsersSuccess,
            users
        );
    }
    void NakamaComponent::OnGetUsersFailed(const Error& error)
    {
        NakamaAccountNotificationBus::Broadcast(
            &NakamaAccountNotificationBus::Events::OnGetUsersFailed,
            error
        );
    }
    void NakamaComponent::OnAddFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnAddFriendsSuccess,
            ids,
            usernames
        );
    }
    void NakamaComponent::OnAddFriendsFailed(const Error& error)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnAddFriendsFailed,
            error
        );
    }
    void NakamaComponent::OnDeleteFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnDeleteFriendsSuccess,
            ids,
            usernames
        );
    }
    void NakamaComponent::OnDeleteFriendsFailed(const Error& error)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnDeleteFriendsFailed,
            error
        );
    }
    void NakamaComponent::OnBlockFriendsSuccess(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnBlockFriendsSuccess,
            ids,
            usernames
        );
    }
    void NakamaComponent::OnBlockFriendsFailed(const Error& error)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnBlockFriendsFailed,
            error
        );
    }
    void NakamaComponent::OnListFriendsSuccess(const AZStd::vector<Friend>& friends, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnListFriendsSuccess,
            friends,
            limit,
            state,
            cursor
        );
    }
    void NakamaComponent::OnListFriendsFailed(const Error& error)
    {
        NakamaFriendsNotificationBus::Broadcast(
            &NakamaFriendsNotificationBus::Events::OnListFriendsFailed,
            error
        );
    }
    void NakamaComponent::OnCreateGroupSuccess(const Group& group)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnCreateGroupSuccess,
            group
        );
    }
    void NakamaComponent::OnCreateGroupFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnCreateGroupFailed,
            error
        );
    }
    void NakamaComponent::OnDeleteGroupSuccess(const AZStd::string& groupId)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnDeleteGroupSuccess,
            groupId
        );
    }
    void NakamaComponent::OnDeleteGroupFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnDeleteGroupFailed,
            error
        );
    }
    void NakamaComponent::OnAddGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnAddGroupUsersSuccess,
            groupId,
            ids
        );
    }
    void NakamaComponent::OnAddGroupUsersFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnAddGroupUsersFailed,
            error
        );
    }
    void NakamaComponent::OnListGroupUsersSuccess(const GroupUserList& users, const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListGroupUsersSuccess,
            users,
            groupId,
            limit,
            state,
            cursor
        );
    }
    void NakamaComponent::OnListGroupUsersFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListGroupUsersFailed,
            error
        );
    }
    void NakamaComponent::OnKickGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnKickGroupUsersSuccess,
            groupId,
            ids
        );
    }
    void NakamaComponent::OnKickGroupUsersFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnKickGroupUsersFailed,
            error
        );
    }
    void NakamaComponent::OnJoinGroupSuccess(const AZStd::string& groupId)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnJoinGroupSuccess,
            groupId
        );
    }
    void NakamaComponent::OnJoinGroupFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnJoinGroupFailed,
            error
        );
    }
    void NakamaComponent::OnLeaveGroupSuccess(const AZStd::string& groupId)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnLeaveGroupSuccess,
            groupId
        );
    }
    void NakamaComponent::OnLeaveGroupFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnLeaveGroupFailed,
            error
        );
    }
    void NakamaComponent::OnListGroupsSuccess(const GroupList& groups, const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListGroupsSuccess,
            groups,
            name,
            limit,
            cursor
        );
    }
    void NakamaComponent::OnListGroupsFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListGroupsFailed,
            error
        );
    }
    void NakamaComponent::OnListUserGroupsSuccess(const UserGroupList& groups, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListUserGroupsSuccess,
            groups,
            limit,
            state,
            cursor
        );
    }
    void NakamaComponent::OnListUserGroupsFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListUserGroupsFailed,
            error
        );
    }
    void NakamaComponent::OnListUserGroupsWithIdSuccess(const UserGroupList& groups, const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListUserGroupsWithIdSuccess,
            groups,
            userId,
            limit,
            state,
            cursor
        );
    }
    void NakamaComponent::OnListUserGroupsWithIdFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnListUserGroupsWithIdFailed,
            error
        );
    }
    void NakamaComponent::OnPromoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnPromoteGroupUsersSuccess,
            groupId,
            ids
        );
    }
    void NakamaComponent::OnPromoteGroupUsersFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnPromoteGroupUsersFailed,
            error
        );
    }
    void NakamaComponent::OnDemoteGroupUsersSuccess(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnDemoteGroupUsersSuccess,
            groupId,
            ids
        );
    }
    void NakamaComponent::OnDemoteGroupUsersFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnDemoteGroupUsersFailed,
            error
        );
    }
    void NakamaComponent::OnUpdateGroupSuccess(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnUpdateGroupSuccess,
            groupId,
            name,
            description,
            avatarUrl,
            langTag,
            open
        );
    }
    void NakamaComponent::OnUpdateGroupFailed(const Error& error)
    {
        NakamaGroupsNotificationBus::Broadcast(
            &NakamaGroupsNotificationBus::Events::OnUpdateGroupFailed,
            error
        );
    }
    void NakamaComponent::OnListLeaderboardRecordsSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::vector<AZStd::string>& ownerIds, AZ::s32 limit, const AZStd::string& cursor)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnListLeaderboardRecordsSuccess,
            records,
            leaderboardId,
            ownerIds,
            limit,
            cursor
        );
    }
    void NakamaComponent::OnListLeaderboardRecordsFailed(const Error& error)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnListLeaderboardRecordsFailed,
            error
        );
    }
    void NakamaComponent::OnListLeaderboardRecordsAroundOwnerSuccess(const LeaderboardRecordList& records, const AZStd::string& leaderboardId, const AZStd::string& ownerId, AZ::s32 limit)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnListLeaderboardRecordsAroundOwnerSuccess,
            records,
            leaderboardId,
            ownerId,
            limit
        );
    }
    void NakamaComponent::OnListLeaderboardRecordsAroundOwnerFailed(const Error& error)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnListLeaderboardRecordsAroundOwnerFailed,
            error
        );
    }
    void NakamaComponent::OnWriteLeaderboardRecordSuccess(const LeaderboardRecord& record, const AZStd::string& leaderboardId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnWriteLeaderboardRecordSuccess,
            record,
            leaderboardId,
            score,
            subscore,
            metadata
        );
    }
    void NakamaComponent::OnWriteLeaderboardRecordFailed(const Error& error)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnWriteLeaderboardRecordFailed,
            error
        );
    }
    void NakamaComponent::OnDeleteLeaderboardRecordSuccess(const AZStd::string& leaderboardId)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnDeleteLeaderboardRecordSuccess,
            leaderboardId
        );
    }
    void NakamaComponent::OnDeleteLeaderboardRecordFailed(const Error& error)
    {
        NakamaLeaderboardsNotificationBus::Broadcast(
            &NakamaLeaderboardsNotificationBus::Events::OnDeleteLeaderboardRecordFailed,
            error
        );
    }
    void NakamaComponent::OnWriteTournamentRecordSuccess(const LeaderboardRecord& record)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnWriteTournamentRecordSuccess,
            record
        );
    }
    void NakamaComponent::OnWriteTournamentRecordFailed(const Error& error)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnWriteTournamentRecordFailed,
            error
        );
    }
    void NakamaComponent::OnListTournamentsSuccess(const TournamentList& tournaments, AZ::u32 categoryStart, AZ::u32 categoryEnd, AZ::u32 startTime, AZ::u32 endTime, AZ::s32 limit, const AZStd::string& cursor)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentsSuccess,
            tournaments,
            categoryStart,
            categoryEnd,
            startTime,
            endTime,
            limit,
            cursor
        );
    }
    void NakamaComponent::OnListTournamentsFailed(const Error& error)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentsFailed,
            error
        );
    }
    void NakamaComponent::OnListTournamentRecordsSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, AZ::s32 limit, const AZStd::string& cursor, const AZStd::vector<AZStd::string>& ownerIds)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentRecordsSuccess,
            records,
            tournamentId,
            limit,
            cursor,
            ownerIds
        );
    }
    void NakamaComponent::OnListTournamentRecordsFailed(const Error& error)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentRecordsFailed,
            error
        );
    }
    void NakamaComponent::OnListTournamentRecordsAroundOwnerSuccess(const TournamentRecordList& records, const AZStd::string& tournamentId, const AZStd::string& ownerId, AZ::s32 limit)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentRecordsAroundOwnerSuccess,
            records,
            tournamentId,
            ownerId,
            limit
        );
    }
    void NakamaComponent::OnListTournamentRecordsAroundOwnerFailed(const Error& error)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnListTournamentRecordsAroundOwnerFailed,
            error
        );
    }
    void NakamaComponent::OnJoinTournamentSuccess(const AZStd::string& tournamentId)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnJoinTournamentSuccess,
            tournamentId
        );
    }
    void NakamaComponent::OnJoinTournamentFailed(const Error& error)
    {
        NakamaTournamentsNotificationBus::Broadcast(
            &NakamaTournamentsNotificationBus::Events::OnJoinTournamentFailed,
            error
        );
    }
    void NakamaComponent::OnRtClientNotConnected()
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnRtClientNotConnected
		);
    }
    void NakamaComponent::OnListMatchesSuccess(const MatchList& matchList, AZ::s32 min_size, AZ::s32 max_size, AZ::s32 limit, const AZStd::string& label, const AZStd::string& query, bool authoritative)
    {
        NakamaMatchesNotificationBus::Broadcast(
            &NakamaMatchesNotificationBus::Events::OnListMatchesSuccess,
            matchList,
            min_size,
            max_size,
            limit,
            label,
            query,
            authoritative
        );
    }
    void NakamaComponent::OnListMatchesFailed(const Error& error)
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnListMatchesFailed,
			error
		);
    }
    void NakamaComponent::OnCreateMatchSuccess(const Match& match)
    {
        NakamaMatchesNotificationBus::Broadcast(
            &NakamaMatchesNotificationBus::Events::OnCreateMatchSuccess,
            match
        );
    }
    void NakamaComponent::OnCreateMatchFailed(const RtError& error)
    {
        NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnCreateMatchFailed,
			error
		);
    }
    void NakamaComponent::OnJoinMatchSuccess(const Match& match)
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnJoinMatchSuccess,
			match
		);
    }
    void NakamaComponent::OnJoinMatchFailed(const RtError& error)
    {
        NakamaMatchesNotificationBus::Broadcast(
            &NakamaMatchesNotificationBus::Events::OnJoinMatchFailed,
            error
        );
    }
    void NakamaComponent::OnJoinMatchByTokenSuccess(const Match& match)
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnJoinMatchByTokenSuccess,
			match
		);
    }
    void NakamaComponent::OnJoinMatchByTokenFailed(const RtError& error)
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnJoinMatchByTokenFailed,
			error
		);
    }
    void NakamaComponent::OnLeaveMatchSuccess(const AZStd::string& matchId)
    {
        NakamaMatchesNotificationBus::Broadcast(
            &NakamaMatchesNotificationBus::Events::OnLeaveMatchSuccess,
            matchId
        );
    }
    void NakamaComponent::OnLeaveMatchFailed(const RtError& error)
    {
		NakamaMatchesNotificationBus::Broadcast(
			&NakamaMatchesNotificationBus::Events::OnLeaveMatchFailed,
			error
		);
    }
    void NakamaComponent::OnListNotificationsSuccess(const NotificationList& notifications, AZ::s32 limit, const AZStd::string& cacheableCursor)
    {
        NakamaNotificationsNotificationBus::Broadcast(
			&NakamaNotificationsNotificationBus::Events::OnListNotificationsSuccess,
            notifications,
            limit,
            cacheableCursor
        );
    }
    void NakamaComponent::OnListNotificationsFailed(const Error& error)
    {
        NakamaNotificationsNotificationBus::Broadcast(
            &NakamaNotificationsNotificationBus::Events::OnListNotificationsFailed,
            error
        );
    }
    void NakamaComponent::OnDeleteNotificationsSuccess(const AZStd::vector<AZStd::string>& notificationIds)
    {
		NakamaNotificationsNotificationBus::Broadcast(
			&NakamaNotificationsNotificationBus::Events::OnDeleteNotificationsSuccess,
			notificationIds
		);
    }
    void NakamaComponent::OnDeleteNotificationsFailed(const Error& error)
    {
        NakamaNotificationsNotificationBus::Broadcast(
            &NakamaNotificationsNotificationBus::Events::OnDeleteNotificationsFailed,
            error
        );
    }
    void NakamaComponent::OnRpcSuccess(const Rpc& rpc)
    {
        NakamaRpcNotificationBus::Broadcast(
            &NakamaRpcNotificationBus::Events::OnRpcSuccess,
            rpc
        );
    }
    void NakamaComponent::OnRpcFailed(const Error& error)
    {
		NakamaRpcNotificationBus::Broadcast(
			&NakamaRpcNotificationBus::Events::OnRpcFailed,
			error
		);
    }
    void NakamaComponent::OnRpcWithIdSuccess(const Rpc& rpc)
    {
		NakamaRpcNotificationBus::Broadcast(
			&NakamaRpcNotificationBus::Events::OnRpcWithIdSuccess,
			rpc
		);
    }
    void NakamaComponent::OnRpcWithIdFailed(const Error& error)
    {
        NakamaRpcNotificationBus::Broadcast(
            &NakamaRpcNotificationBus::Events::OnRpcWithIdFailed,
            error
        );
    }
    void NakamaComponent::OnRtRpcSuccess(const Rpc& rpc)
    {
        NakamaRpcNotificationBus::Broadcast(
            &NakamaRpcNotificationBus::Events::OnRtRpcSuccess,
            rpc
        );
    }
    void NakamaComponent::OnRtRpcFailed(const RtError& error)
    {
		NakamaRpcNotificationBus::Broadcast(
			&NakamaRpcNotificationBus::Events::OnRtRpcFailed,
			error
		);
    }
    void NakamaComponent::OnAddMatchmakerSuccess(const AZStd::string& ticket)
    {
        NakamaMatchmakerNotificationBus::Broadcast(
            &NakamaMatchmakerNotificationBus::Events::OnAddMatchmakerSuccess,
            ticket
        );
    }
    void NakamaComponent::OnAddMatchmakerFailed(const RtError& error)
    {
		NakamaMatchmakerNotificationBus::Broadcast(
			&NakamaMatchmakerNotificationBus::Events::OnAddMatchmakerFailed,
			error
		);
    }
    void NakamaComponent::OnRemoveMatchmakerSuccess(const AZStd::string& ticket)
    {
		NakamaMatchmakerNotificationBus::Broadcast(
			&NakamaMatchmakerNotificationBus::Events::OnRemoveMatchmakerSuccess,
			ticket
		);
    }
    void NakamaComponent::OnRemoveMatchmakerFailed(const RtError& error)
    {
        NakamaMatchmakerNotificationBus::Broadcast(
            &NakamaMatchmakerNotificationBus::Events::OnRemoveMatchmakerFailed,
            error
        );
    }
    void NakamaComponent::OnFollowUsersSuccess(const AZStd::vector<UserPresence>& presences)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnFollowUsersSuccess,
            presences
        );
    }
    void NakamaComponent::OnFollowUsersFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnFollowUsersFailed,
            error
        );
    }
    void NakamaComponent::OnUnfollowUsersSuccess(const AZStd::vector<AZStd::string>& userIds)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnUnfollowUsersSuccess,
			userIds
		);
    }
    void NakamaComponent::OnUnfollowUsersFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnUnfollowUsersFailed,
			error
		);
    }
    void NakamaComponent::OnUpdateStatusSuccess(const AZStd::string& status)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnUpdateStatusSuccess,
			status
		);
    }
    void NakamaComponent::OnUpdateStatusFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnUpdateStatusFailed,
            error
        );
    }
    void NakamaComponent::OnAcceptPartyMemberSuccess(const AZStd::string& partyId, const UserPresence& presence)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnAcceptPartyMemberSuccess,
            partyId,
            presence
        );
    }
    void NakamaComponent::OnAcceptPartyMemberFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnAcceptPartyMemberFailed,
			error
		);
    }
    void NakamaComponent::OnAddMatchmakerPartySuccess(const PartyMatchmakerTicket& ticket)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnAddMatchmakerPartySuccess,
			ticket
		);
    }
    void NakamaComponent::OnAddMatchmakerPartyFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnAddMatchmakerPartyFailed,
            error
        );
    }
    void NakamaComponent::OnClosePartySuccess(const AZStd::string& partyId)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnClosePartySuccess,
            partyId
        );
    }
    void NakamaComponent::OnClosePartyFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnClosePartyFailed,
            error
        );
    }
    void NakamaComponent::OnCreatePartySuccess(const Party& party)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnCreatePartySuccess,
			party
		);
    }
    void NakamaComponent::OnCreatePartyFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnCreatePartyFailed,
			error
		);
    }
    void NakamaComponent::OnJoinPartySuccess(const AZStd::string& partyId)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnJoinPartySuccess,
			partyId
		);
    }
    void NakamaComponent::OnJoinPartyFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnJoinPartyFailed,
            error
        );
    }
    void NakamaComponent::OnLeavePartySuccess(const AZStd::string& partyId)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnLeavePartySuccess,
            partyId
        );
    }
    void NakamaComponent::OnLeavePartyFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnLeavePartyFailed,
			error
		);
    }
    void NakamaComponent::OnListPartyJoinRequestsSuccess(const PartyJoinRequest& request)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnListPartyJoinRequestsSuccess,
			request
		);
    }
    void NakamaComponent::OnListPartyJoinRequestsFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnListPartyJoinRequestsFailed,
			error
		);
    }
    void NakamaComponent::OnPromotePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnPromotePartyMemberSuccess,
            partyId,
            partyMember
        );
    }
    void NakamaComponent::OnPromotePartyMemberFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnPromotePartyMemberFailed,
            error
        );
    }
    void NakamaComponent::OnRemoveMatchmakerPartySuccess(const AZStd::string& partyId, const AZStd::string& ticket)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnRemoveMatchmakerPartySuccess,
			partyId,
			ticket
		);
    }
    void NakamaComponent::OnRemoveMatchmakerPartyFailed(const RtError& error)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnRemoveMatchmakerPartyFailed,
			error
		);
    }
    void NakamaComponent::OnRemovePartyMemberSuccess(const AZStd::string& partyId, const UserPresence& partyMember)
    {
		NakamaPartyNotificationBus::Broadcast(
			&NakamaPartyNotificationBus::Events::OnRemovePartyMemberSuccess,
			partyId,
			partyMember
		);
    }
    void NakamaComponent::OnRemovePartyMemberFailed(const RtError& error)
    {
        NakamaPartyNotificationBus::Broadcast(
            &NakamaPartyNotificationBus::Events::OnRemovePartyMemberFailed,
            error
        );
    }
    void NakamaComponent::OnListStorageObjectsSuccess(const StorageObjectList& objectList)
    {
        NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnListStorageObjectsSuccess,
			objectList
		);
    }
    void NakamaComponent::OnListStorageObjectsFailed(const Error& error)
    {
		NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnListStorageObjectsFailed,
			error
		);
    }
    void NakamaComponent::OnListUsersStorageObjectsSuccess(const StorageObjectList& objectList)
    {
        NakamaStorageObjectsNotificationBus::Broadcast(
            &NakamaStorageObjectsNotificationBus::Events::OnListUsersStorageObjectsSuccess,
            objectList
        );
    }
    void NakamaComponent::OnListUsersStorageObjectsFailed(const Error& error)
    {
		NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnListUsersStorageObjectsFailed,
			error
		);
    }
    void NakamaComponent::OnWriteStorageObjectsSuccess(const AZStd::vector<StorageObjectAck>& objectAcks)
    {
        NakamaStorageObjectsNotificationBus::Broadcast(
            &NakamaStorageObjectsNotificationBus::Events::OnWriteStorageObjectsSuccess,
            objectAcks
        );
    }
    void NakamaComponent::OnWriteStorageObjectsFailed(const Error& error)
    {
        NakamaStorageObjectsNotificationBus::Broadcast(
            &NakamaStorageObjectsNotificationBus::Events::OnWriteStorageObjectsFailed,
            error
        );
    }
    void NakamaComponent::OnReadStorageObjectsSuccess(const AZStd::vector<StorageObject>& objects)
    {
		NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnReadStorageObjectsSuccess,
			objects
		);
    }
    void NakamaComponent::OnReadStorageObjectsFailed(const Error& error)
    {
		NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnReadStorageObjectsFailed,
			error
		);
    }
    void NakamaComponent::OnDeleteStorageObjectsSuccess(const AZStd::vector<DeleteStorageObjectId>& objectIds)
    {
        NakamaStorageObjectsNotificationBus::Broadcast(
            &NakamaStorageObjectsNotificationBus::Events::OnDeleteStorageObjectsSuccess,
            objectIds
        );
    }
    void NakamaComponent::OnDeleteStorageObjectsFailed(const Error& error)
    {
		NakamaStorageObjectsNotificationBus::Broadcast(
			&NakamaStorageObjectsNotificationBus::Events::OnDeleteStorageObjectsFailed,
			error
		);
    }
    void NakamaComponent::OnListChannelMessagesSuccess(const ChannelMessageList& messageList)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnListChannelMessagesSuccess,
            messageList
        );
    }
    void NakamaComponent::OnListChannelMessagesFailed(const Error& error)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnListChannelMessagesFailed,
			error
		);
    }
    void NakamaComponent::OnJoinChatSuccess(const Channel& channel)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnJoinChatSuccess,
			channel
		);
    }
    void NakamaComponent::OnJoinChatFailed(const RtError& error)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnJoinChatFailed,
            error
        );
    }
    void NakamaComponent::OnLeaveChatSuccess(const AZStd::string& channelId)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnLeaveChatSuccess,
			channelId
		);
    }
    void NakamaComponent::OnLeaveChatFailed(const RtError& error)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnLeaveChatFailed,
			error
		);
    }
    void NakamaComponent::OnWriteChatMessageSuccess(const ChannelMessageAck& ack)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnWriteChatMessageSuccess,
            ack
        );
    }
    void NakamaComponent::OnWriteChatMessageFailed(const RtError& error)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnWriteChatMessageFailed,
            error
        );
    }
    void NakamaComponent::OnUpdateChatMessageSuccess(const ChannelMessageAck& ack)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnUpdateChatMessageSuccess,
			ack
		);
    }
    void NakamaComponent::OnUpdateChatMessageFailed(const RtError& error)
    {
		NakamaChatNotificationBus::Broadcast(
			&NakamaChatNotificationBus::Events::OnUpdateChatMessageFailed,
			error
		);
    }
    void NakamaComponent::OnRemoveChatMessageSuccess(const ChannelMessageAck& ack)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnRemoveChatMessageSuccess,
            ack
        );
    }
    void NakamaComponent::OnRemoveChatMessageFailed(const RtError& error)
    {
        NakamaChatNotificationBus::Broadcast(
            &NakamaChatNotificationBus::Events::OnRemoveChatMessageFailed,
            error
        );
    }
    void NakamaComponent::rpc(const AZStd::string& id, const AZStd::string& payload)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        Nakama::opt::optional<std::string> n_payload = Nakama::opt::nullopt;
		if (!payload.empty())
		{
			n_payload = payload.c_str();
		}
        m_Client->rpc(
            m_Session,
            id.c_str(),
            n_payload,
            [this](const Nakama::NRpc& nRpc) {
                OnRpcSuccess(Rpc::FromNakama(nRpc));
            },
			[this](const Nakama::NError& nError) {
                OnRpcFailed(Error::FromNakama(nError));
			}
       );
    }
    void NakamaComponent::rpcWithId(const AZStd::string& http_key, const AZStd::string& id, const AZStd::string& payload)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        Nakama::opt::optional<std::string> n_payload = Nakama::opt::nullopt;
        if (!payload.empty())
        {
            n_payload = payload.c_str();
        }
        m_Client->rpc(
            http_key.c_str(),
            id.c_str(),
            n_payload,
            [this](const Nakama::NRpc& nRpc) {
                OnRpcWithIdSuccess(Rpc::FromNakama(nRpc));
            },
            [this](const Nakama::NError& nError) {
                OnRpcWithIdFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::rtRpc(const AZStd::string& id, const AZStd::string& payload)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::opt::optional<std::string> n_payload = Nakama::opt::nullopt;
        if (!payload.empty())
        {
            n_payload = payload.c_str();
        }
        m_RtClient->rpc(
            id.c_str(),
            n_payload,
			[this](const Nakama::NRpc& nRpc) {
				OnRtRpcSuccess(Rpc::FromNakama(nRpc));
			},
            [this](const Nakama::NRtError& nError) {
                OnRtRpcFailed(RtError::FromNakama(nError));
            }
            );
    }
    void NakamaComponent::addMatchmaker(AZ::s32 minCount, AZ::s32 maxCount, const AZStd::string& query, const AZStringMap& stringProperties, const AZStringDoubleMap& numericProperties, AZ::s32 countMultiple)
    {
		if (!m_Session)
		{
			OnUnauthenticated();
			return;
		}
		if (!m_RtClient->isConnected())
		{
			OnRtClientNotConnected();
			return;
		}
        Nakama::opt::optional<int32_t> n_minCount = Nakama::opt::nullopt;
		if (minCount > 0)
		{
			n_minCount = minCount;
		}
        Nakama::opt::optional<int32_t> n_maxCount = Nakama::opt::nullopt;
        if (maxCount > 0)
        {
            n_maxCount = maxCount;
        }
        Nakama::opt::optional<std::string> n_query = Nakama::opt::nullopt;
		if (!query.empty())
		{
			n_query = query.c_str();
		}
        Nakama::NStringMap n_stringProperties = AZStringMapToNakama(stringProperties);
		Nakama::NStringDoubleMap n_numericProperties = AZStringDoubleMapToNakama(numericProperties);
        Nakama::opt::optional<int32_t> n_countMultiple = Nakama::opt::nullopt;
        if (countMultiple > 0)
        {
            n_countMultiple = countMultiple;
        }
		m_RtClient->addMatchmaker(
            n_minCount,
            n_maxCount,
            n_query,
            n_stringProperties,
            n_numericProperties,
            n_countMultiple,
			[this](const Nakama::NMatchmakerTicket& nTicket) {
				OnAddMatchmakerSuccess(nTicket.ticket.c_str());
			},
			[this](const Nakama::NRtError& nError) {
				OnAddMatchmakerFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::removeMatchmaker(const AZStd::string& ticket)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->removeMatchmaker(
            ticket.c_str(),
            [this, ticket]() {
                OnRemoveMatchmakerSuccess(ticket);
            },
            [this](const Nakama::NRtError& nError) {
                OnRemoveMatchmakerFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::followUsers(const AZStd::vector<AZStd::string>& userIds)
    {
		if (!m_Session)
		{
			OnUnauthenticated();
			return;
		}
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        std::vector<std::string> n_userIds;
        if (userIds.size() > 0)
        {
            for (auto userId : userIds)
            {
                n_userIds.push_back(userId.c_str());
            }
        }
		m_RtClient->followUsers(
            n_userIds,
			[this](const Nakama::NStatus& nStatus) {
                AZStd::vector<UserPresence> presences;
                if (nStatus.presences.size() > 0)
                {
                    for (auto presence : nStatus.presences)
                    {
                        presences.push_back(UserPresence::FromNakama(presence));
                    }
                }
				OnFollowUsersSuccess(presences);
			},
			[this](const Nakama::NRtError& nError) {
				OnFollowUsersFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::unfollowUsers(const AZStd::vector<AZStd::string>& userIds)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        std::vector<std::string> n_userIds;
        if (userIds.size() > 0)
        {
            for (auto userId : userIds)
            {
                n_userIds.push_back(userId.c_str());
            }
        }
        m_RtClient->unfollowUsers(
            n_userIds,
            [this, userIds]() {
                OnUnfollowUsersSuccess(userIds);
            },
            [this](const Nakama::NRtError& nError) {
                OnUnfollowUsersFailed(RtError::FromNakama(nError));
            }
        );

    }
    void NakamaComponent::updateStatus(const AZStd::string& status)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->updateStatus(
            status.c_str(),
            [this, status]() {
                OnUpdateStatusSuccess(status);
            },
            [this](const Nakama::NRtError& nError) {
                OnUpdateStatusFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::acceptPartyMember(const AZStd::string& partyId, const UserPresence& presence)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::NUserPresence nUserPresence = UserPresence::ToNakama(presence);
		m_RtClient->acceptPartyMember(
			partyId.c_str(),
            nUserPresence,
			[this, partyId, presence]() {
				OnAcceptPartyMemberSuccess(partyId, presence);
			},
			[this](const Nakama::NRtError& nError) {
				OnAcceptPartyMemberFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::addMatchmakerParty(const AZStd::string& partyId, const AZStd::string& query, AZ::s32 minCount, AZ::s32 maxCount, const AZStringMap& stringProperties, const AZStringDoubleMap& numericProperties, AZ::s32 countMultiple)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::NStringMap n_stringProperties = AZStringMapToNakama(stringProperties);
        Nakama::NStringDoubleMap n_numericProperties = AZStringDoubleMapToNakama(numericProperties);
        m_RtClient->addMatchmakerParty(
            partyId.c_str(),
            query.c_str(),
            minCount,
            maxCount,
            n_stringProperties,
            n_numericProperties,
            countMultiple,
            [this](const Nakama::NPartyMatchmakerTicket& nTicket) {
                OnAddMatchmakerPartySuccess(PartyMatchmakerTicket::FromNakama(nTicket));
            },
            [this](const Nakama::NRtError& nError) {
                OnAddMatchmakerPartyFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::closeParty(const AZStd::string& partyId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->closeParty(
            partyId.c_str(),
            [this, partyId]() {
                OnClosePartySuccess(partyId);
            },
            [this](const Nakama::NRtError& nError) {
                OnClosePartyFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::createParty(bool open, AZ::s32 maxSize)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
		m_RtClient->createParty(
			open,
			maxSize,
			[this](const Nakama::NParty& nParty) {
				OnCreatePartySuccess(Party::FromNakama(nParty));
			},
			[this](const Nakama::NRtError& nError) {
				OnCreatePartyFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::joinParty(const AZStd::string& partyId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
		m_RtClient->joinParty(
			partyId.c_str(),
			[this, partyId]() {
				OnJoinPartySuccess(partyId);
			},
			[this](const Nakama::NRtError& nError) {
				OnJoinPartyFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::leaveParty(const AZStd::string& partyId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->leaveParty(
            partyId.c_str(),
            [this, partyId]() {
                OnLeavePartySuccess(partyId);
            },
            [this](const Nakama::NRtError& nError) {
                OnLeavePartyFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listPartyJoinRequests(const AZStd::string& partyId)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        m_RtClient->listPartyJoinRequests(
            partyId.c_str(),
            [this](const Nakama::NPartyJoinRequest& joinRequest) {
                OnListPartyJoinRequestsSuccess(PartyJoinRequest::FromNakama(joinRequest));
            },
            [this](const Nakama::NRtError& nError) {
                OnListPartyJoinRequestsFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::promotePartyMember(const AZStd::string& partyId, const UserPresence& partyMember)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::NUserPresence nPartyMember = UserPresence::ToNakama(partyMember);
        m_RtClient->promotePartyMember(
            partyId.c_str(),
            nPartyMember,
            [this, partyId, partyMember]() {
                OnPromotePartyMemberSuccess(partyId, partyMember);
            },
            [this](const Nakama::NRtError& nError) {
                OnPromotePartyMemberFailed(RtError::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::removeMatchmakerParty(const AZStd::string& partyId, const AZStd::string& ticket)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
		m_RtClient->removeMatchmakerParty(
			partyId.c_str(),
			ticket.c_str(),
			[this, partyId, ticket]() {
				OnRemoveMatchmakerPartySuccess(partyId, ticket);
			},
			[this](const Nakama::NRtError& nError) {
				OnRemoveMatchmakerPartyFailed(RtError::FromNakama(nError));
			}
		);
    }
    void NakamaComponent::removePartyMember(const AZStd::string& partyId, const UserPresence& partyMember)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        if (!m_RtClient->isConnected())
        {
            OnRtClientNotConnected();
            return;
        }
        Nakama::NUserPresence nPartyMember = UserPresence::ToNakama(partyMember);
        m_RtClient->removePartyMember(
            partyId.c_str(),
            nPartyMember,
            [this, partyId, partyMember]() {
				OnRemovePartyMemberSuccess(partyId, partyMember);
            },
			[this](const Nakama::NRtError& nError) {
				OnRemovePartyMemberFailed(RtError::FromNakama(nError));
			}
        );
    }
    void NakamaComponent::listStorageObjects(const AZStd::string& collection, AZ::s32 limit, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listStorageObjects(
            m_Session,
            collection.c_str(),
            limit,
            cursor.c_str(),
            [this](Nakama::NStorageObjectListPtr objectList) {
                OnListStorageObjectsSuccess(StorageObjectList::FromNakama(*objectList));
            },
            [this](const Nakama::NError& nError) {
                OnListStorageObjectsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::listUsersStorageObjects(const AZStd::string& collection, const AZStd::string& userId, AZ::s32 limit, const AZStd::string& cursor)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        m_Client->listUsersStorageObjects(
            m_Session,
            collection.c_str(),
            userId.c_str(),
            limit,
            cursor.c_str(),
            [this](Nakama::NStorageObjectListPtr objectList) {
                OnListUsersStorageObjectsSuccess(StorageObjectList::FromNakama(*objectList));
            },
            [this](const Nakama::NError& nError) {
                OnListUsersStorageObjectsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::writeStorageObjects(const AZStd::vector<StorageObjectWrite>& objects)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<Nakama::NStorageObjectWrite> n_objects;
        if (objects.size() > 0)
        {
            for (auto objectWrite : objects)
            {
				n_objects.push_back(StorageObjectWrite::ToNakama(objectWrite));
            }
        }
        m_Client->writeStorageObjects(
            m_Session,
            n_objects,
            [this](const Nakama::NStorageObjectAcks& nAcks)
            {
                AZStd::vector<StorageObjectAck> acks;
                if (nAcks.size() > 0)
                {
                    for (auto ack : nAcks)
                    {
                        acks.push_back(StorageObjectAck::FromNakama(ack));
                    }
                }
                OnWriteStorageObjectsSuccess(acks);
            },
            [this](const Nakama::NError& nError) {
                OnWriteStorageObjectsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::readStorageObjects(const AZStd::vector<ReadStorageObjectId>& objectIds)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
		std::vector<Nakama::NReadStorageObjectId> n_objectIds;
        if (objectIds.size() > 0)
        {
            for (auto objectId : objectIds)
            {
                n_objectIds.push_back(ReadStorageObjectId::ToNakama(objectId));
            }
        }
        m_Client->readStorageObjects(
            m_Session,
            n_objectIds,
            [this](const Nakama::NStorageObjects& nObjects)
            {
                AZStd::vector<StorageObject> objects;
                if (nObjects.size() > 0)
                {
                    for (auto storageObject : nObjects)
                    {
						objects.push_back(StorageObject::FromNakama(storageObject));
                    }
                }
                OnReadStorageObjectsSuccess(objects);
            },
            [this](const Nakama::NError& nError) {
                OnReadStorageObjectsFailed(Error::FromNakama(nError));
            }
        );
    }
    void NakamaComponent::deleteStorageObjects(const AZStd::vector<DeleteStorageObjectId>& objectIds)
    {
        if (!m_Session)
        {
            OnUnauthenticated();
            return;
        }
        std::vector<Nakama::NDeleteStorageObjectId> n_objectIds;
        if (objectIds.size() > 0)
        {
            for (auto objectId : objectIds)
            {
                n_objectIds.push_back(DeleteStorageObjectId::ToNakama(objectId));
            }
        }
        m_Client->deleteStorageObjects(
            m_Session,
            n_objectIds,
            [this, objectIds]() {
                OnDeleteStorageObjectsSuccess(objectIds);
            },
            [this](const Nakama::NError& nError) {
                OnDeleteStorageObjectsFailed(Error::FromNakama(nError));
            }
        );
    }
} // namespace NakamaClientGem
