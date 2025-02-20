
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
            behaviorContext->EBus<NakamaNotificationBus>("NakamaNotification")
                ->Attribute(AZ::Script::Attributes::Category, "NakamaNotification") 
                ->Handler<NakamaNotificationHandler>();

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
    void NakamaComponent::AuthenticateEmail(const AZStd::string& email, const AZStd::string& password, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
        m_Client->authenticateEmail(
            email.c_str(),
            password.c_str(),
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
    void NakamaComponent::AuthenticateFacebook(const AZStd::string& accessToken, const AZStd::string& username, bool create, bool importFriends, const AZStringMap& vars)
    {
    }
    void NakamaComponent::AuthenticateGoogle(const AZStd::string& accessToken, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
    }
    void NakamaComponent::AuthenticateGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZStd::sys_time_t timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
    }
    void NakamaComponent::AuthenticateApple(const AZStd::string& token, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
    }
    void NakamaComponent::AuthenticateCustom(const AZStd::string& id, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
    }
    void NakamaComponent::AuthenticateSteam(const AZStd::string& token, const AZStd::string& username, bool create, const AZStringMap& vars)
    {
    }
    void NakamaComponent::authenticateRefresh()
    {
        if (m_RtClient->isConnected())
        {
            m_Client->authenticateRefresh(m_Session,
                [this](Nakama::NSessionPtr nSession) {
                    m_Session = nSession;
                },
                [](const Nakama::NError&) {
                    // Todo
                });
        }
    }
    void NakamaComponent::linkFacebook(const AZStd::string& accessToken, bool importFriends)
    {
    }
    void NakamaComponent::linkEmail(const AZStd::string& email, const AZStd::string& password)
    {
    }
    void NakamaComponent::linkDevice(const AZStd::string& id)
    {
    }
    void NakamaComponent::linkGoogle(const AZStd::string& accessToken)
    {
    }
    void NakamaComponent::linkGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZ::u64 timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl)
    {
    }
    void NakamaComponent::linkApple(const AZStd::string& token)
    {
    }
    void NakamaComponent::linkSteam(const AZStd::string& token)
    {
    }
    void NakamaComponent::linkCustom(const AZStd::string& id)
    {
    }
    void NakamaComponent::unlinkFacebook(const AZStd::string& accessToken)
    {
    }
    void NakamaComponent::unlinkEmail(const AZStd::string& email, const AZStd::string& password)
    {
    }
    void NakamaComponent::unlinkGoogle(const AZStd::string& accessToken)
    {
    }
    void NakamaComponent::unlinkGameCenter(const AZStd::string& playerId, const AZStd::string& bundleId, AZ::u64 timestampSeconds, const AZStd::string& salt, const AZStd::string& signature, const AZStd::string& publicKeyUrl)
    {
    }
    void NakamaComponent::unlinkApple(const AZStd::string& token)
    {
    }
    void NakamaComponent::unlinkSteam(const AZStd::string& token)
    {
    }
    void NakamaComponent::unlinkDevice(const AZStd::string& id)
    {
    }
    void NakamaComponent::unlinkCustom(const AZStd::string& id)
    {
    }
    void NakamaComponent::importFacebookFriends(const AZStd::string& token, bool reset)
    {
    }
    void NakamaComponent::getAccount()
    {
    }
    void NakamaComponent::updateAccount(const AZStd::string& username, const AZStd::string& displayName, const AZStd::string& avatarUrl, const AZStd::string& langTag, const AZStd::string& location, const AZStd::string& timezone)
    {
    }
    void NakamaComponent::getUsers(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames, const AZStd::vector<AZStd::string>& facebookIds)
    {
    }
    void NakamaComponent::addFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
    }
    void NakamaComponent::deleteFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
    }
    void NakamaComponent::blockFriends(const AZStd::vector<AZStd::string>& ids, const AZStd::vector<AZStd::string>& usernames)
    {
    }
    void NakamaComponent::listFriends(AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::createGroup(const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open, AZ::s32 maxCount)
    {
    }
    void NakamaComponent::deleteGroup(const AZStd::string& groupId)
    {
    }
    void NakamaComponent::addGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
    }
    void NakamaComponent::listGroupUsers(const AZStd::string& groupId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::kickGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
    }
    void NakamaComponent::joinGroup(const AZStd::string& groupId)
    {
    }
    void NakamaComponent::leaveGroup(const AZStd::string& groupId)
    {
    }
    void NakamaComponent::listGroups(const AZStd::string& name, AZ::s32 limit, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::listUserGroups(AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::listUserGroupsWithId(const AZStd::string& userId, AZ::s32 limit, AZ::u8 state, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::promoteGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
    }
    void NakamaComponent::demoteGroupUsers(const AZStd::string& groupId, const AZStd::vector<AZStd::string>& ids)
    {
    }
    void NakamaComponent::updateGroup(const AZStd::string& groupId, const AZStd::string& name, const AZStd::string& description, const AZStd::string& avatarUrl, const AZStd::string& langTag, bool open)
    {
    }
    void NakamaComponent::listLeaderboardRecords(const AZStd::string& leaderboardId, const AZStd::vector<AZStd::string>& ownerIds, AZ::s32 limit, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::listLeaderboardRecordsAroundOwner(const AZStd::string& leaderboardId, const AZStd::string& ownerId, AZ::s32 limit)
    {
    }
    void NakamaComponent::writeLeaderboardRecord(const AZStd::string& leaderboardId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata)
    {
    }
    void NakamaComponent::deleteLeaderboardRecord(const AZStd::string& leaderboardId)
    {
    }
    void NakamaComponent::writeTournamentRecord(const AZStd::string& tournamentId, AZ::s64 score, AZ::s64 subscore, AZStd::string metadata)
    {
    }
    void NakamaComponent::listTournaments(AZ::u32 categoryStart, AZ::u32 categoryEnd, AZ::u32 startTime, AZ::u32 endTime, AZ::s32 limit, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::listTournamentRecords(const AZStd::string& tournamentId, AZ::s32 limit, const AZStd::string& cursor, const AZStd::vector<AZStd::string>& ownerIds)
    {
    }
    void NakamaComponent::listTournamentRecordsAroundOwner(const AZStd::string& tournamentId, const AZStd::string& ownerId, AZ::s32 limit)
    {
    }
    void NakamaComponent::joinTournament(const AZStd::string& tournamentId)
    {
    }
    void NakamaComponent::listMatches(AZ::s32 min_size, AZ::s32 max_size, AZ::s32 limit, const AZStd::string& label, const AZStd::string& query, bool authoritative)
    {
    }
    void NakamaComponent::listNotifications(AZ::s32 limit, const AZStd::string& cacheableCursor)
    {
    }
    void NakamaComponent::deleteNotifications(const AZStd::vector<AZStd::string>& notificationIds)
    {
    }
    void NakamaComponent::listChannelMessages(const AZStd::string& channelId, AZ::s32 limit, const AZStd::string& cursor, bool forward)
    {
    }
    void NakamaComponent::listStorageObjects(const AZStd::string& collection, AZ::s32 limit, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::listUsersStorageObjects(const AZStd::string& collection, const AZStd::string& userId, AZ::s32 limit, const AZStd::string& cursor)
    {
    }
    void NakamaComponent::writeStorageObjects(const AZStd::vector<StorageObjectWrite>& objects)
    {
    }
    void NakamaComponent::readStorageObjects(const AZStd::vector<ReadStorageObjectId>& objectIds)
    {
    }
    void NakamaComponent::deleteStorageObjects(const AZStd::vector<DeleteStorageObjectId>& objectIds)
    {
    }
    void NakamaComponent::rpc(const AZStd::string& id, const AZStd::string& payload)
    {
    }
    void NakamaComponent::rpcWithId(const AZStd::string& http_key, const AZStd::string& id, const AZStd::string& payload)
    {
    }
    void NakamaComponent::joinChat(const AZStd::string& target, AZ::u8 channelType, bool persistence, bool hidden)
    {
    }
    void NakamaComponent::leaveChat(const AZStd::string& channelId)
    {
    }
    void NakamaComponent::writeChatMessage(const AZStd::string& channelId, const AZStd::string& content)
    {
    }
    void NakamaComponent::updateChatMessage(const AZStd::string& channelId, const AZStd::string& messageId, const AZStd::string& content)
    {
    }
    void NakamaComponent::removeChatMessage(const AZStd::string& channelId, const AZStd::string& messageId)
    {
    }
    void NakamaComponent::createMatch()
    {
    }
    void NakamaComponent::joinMatch(const AZStd::string& matchId, const AZStringMap& metadata)
    {
    }
    void NakamaComponent::joinMatchByToken(const AZStd::string& token)
    {
    }
    void NakamaComponent::leaveMatch(const AZStd::string& matchId)
    {
    }
    void NakamaComponent::addMatchmaker(AZ::s32 minCount, AZ::s32 maxCount, const AZStd::string& query, const AZStringMap& stringProperties, const AZStringDoubleMap& numericProperties, AZ::s32 countMultiple)
    {
    }
    void NakamaComponent::removeMatchmaker(const AZStd::string& ticket)
    {
    }
    void NakamaComponent::sendMatchData(const AZStd::string& matchId, AZ::s64 opCode, const AZStd::string& data, const AZStd::vector<UserPresence>& presences)
    {
    }
    void NakamaComponent::followUsers(const AZStd::vector<AZStd::string>& userIds)
    {
    }
    void NakamaComponent::unfollowUsers(const AZStd::vector<AZStd::string>& userIds)
    {
    }
    void NakamaComponent::updateStatus(const AZStd::string& status)
    {
    }
    void NakamaComponent::rtRpc(const AZStd::string& id, const AZStd::string& payload)
    {
    }
    void NakamaComponent::acceptPartyMember(const AZStd::string& partyId, UserPresence& presence)
    {
    }
    void NakamaComponent::addMatchmakerParty(const AZStd::string& partyId, const AZStd::string& query, AZ::s32 minCount, AZ::s32 maxCount, const AZStringMap& stringProperties, const AZStringDoubleMap& numericProperties, AZ::s32 countMultiple)
    {
    }
    void NakamaComponent::closeParty(const AZStd::string& partyId)
    {
    }
    void NakamaComponent::createParty(bool open, AZ::s32 maxSize)
    {
    }
    void NakamaComponent::joinParty(const AZStd::string& partyId)
    {
    }
    void NakamaComponent::leaveParty(const AZStd::string& partyId)
    {
    }
    void NakamaComponent::listPartyJoinRequests(const AZStd::string& partyId)
    {
    }
    void NakamaComponent::promotePartyMember(const AZStd::string& partyId, UserPresence& partyMember)
    {
    }
    void NakamaComponent::removeMatchmakerParty(const AZStd::string& partyId, const AZStd::string& ticket)
    {
    }
    void NakamaComponent::removePartyMember(const AZStd::string& partyId, UserPresence& presence)
    {
    }
    void NakamaComponent::sendPartyData(const AZStd::string& partyId, AZ::s32 opCode, AZStd::string& data)
    {
    }
    void NakamaComponent::OnConnect()
    {
        NakamaNotificationBus::Broadcast(
            &NakamaNotificationBus::Events::OnConnect
        );
    }
    void NakamaComponent::OnDisconnect(const RtClientDisconnectInfo& info)
    {
        NakamaNotificationBus::Broadcast(
            &NakamaNotificationBus::Events::OnDisconnect,
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
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnError,
                RtError::FromNakama(nError)
            );
            });
        m_Listener.setChannelMessageCallback([](const Nakama::NChannelMessage& nMessage) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnChannelMessage, 
                ChannelMessage::FromNakama(nMessage)
            );
            });
        m_Listener.setChannelPresenceCallback([](const Nakama::NChannelPresenceEvent& nEvent) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnChannelPresence,
                ChannelPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setMatchmakerMatchedCallback([](Nakama::NMatchmakerMatchedPtr matchedPtr) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnMatchmakerMatched, 
                MatchmakerMatched::FromNakama(*matchedPtr));
            });
        m_Listener.setMatchDataCallback([](const Nakama::NMatchData& nData) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnMatchData, 
                MatchData::FromNakama(nData));
            });
        m_Listener.setMatchPresenceCallback([](const Nakama::NMatchPresenceEvent& nEvent) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnMatchPresence,
                MatchPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setNotificationsCallback([](const Nakama::NNotificationList& nList) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnNotifications, 
                NotificationList::FromNakama(nList));
            });
        m_Listener.setPartyCallback([](const Nakama::NParty& nParty) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnParty, 
                Party::FromNakama(nParty));
            });
        m_Listener.setPartyCloseCallback([](const Nakama::NPartyClose& nPartyClose) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyClosed, 
                PartyClose::FromNakama(nPartyClose));
            });
        m_Listener.setPartyDataCallback([](const Nakama::NPartyData& nData) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyData, 
                PartyData::FromNakama(nData));
            });
        m_Listener.setPartyJoinRequestCallback([](const Nakama::NPartyJoinRequest& nRequest) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyJoinRequest, 
                PartyJoinRequest::FromNakama(nRequest));
            });
        m_Listener.setPartyLeaderCallback([](const Nakama::NPartyLeader& nLeader) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyLeader, 
                PartyLeader::FromNakama(nLeader));
            });
        m_Listener.setPartyMatchmakerTicketCallback([](const Nakama::NPartyMatchmakerTicket& nTicket) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyMatchmakerTicket, 
                PartyMatchmakerTicket::FromNakama(nTicket));
            });
        m_Listener.setPartyPresenceCallback([](const Nakama::NPartyPresenceEvent& nEvent) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnPartyPresence, 
                PartyPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStatusPresenceCallback([](const Nakama::NStatusPresenceEvent& nEvent) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnStatusPresence, 
                StatusPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStreamPresenceCallback([](const Nakama::NStreamPresenceEvent& nEvent) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnStreamPresence, 
                StreamPresenceEvent::FromNakama(nEvent));
            });
        m_Listener.setStreamDataCallback([](const Nakama::NStreamData& nData) {
            NakamaNotificationBus::Broadcast(
                &NakamaNotificationBus::Events::OnStreamData, 
                StreamData::FromNakama(nData));
            });

        m_RtClient->setListener(&m_Listener);

        NakamaNotificationBus::Broadcast(
            &NakamaNotificationBus::Events::OnAuthenticateSuccess,
            m_Session->getUsername().c_str(),
            m_Session->getUserId().c_str()
        );

        m_RtClient->connect(m_Session, true);
    }
    void NakamaComponent::OnAuthenticateFailed(const Nakama::NError& error)
    {
        NakamaNotificationBus::Broadcast(
            &NakamaNotificationBus::Events::OnAuthenticateFailed,
            static_cast<AZ::s8>(error.code),
            error.message.c_str()
        );
    }
} // namespace NakamaClientGem
