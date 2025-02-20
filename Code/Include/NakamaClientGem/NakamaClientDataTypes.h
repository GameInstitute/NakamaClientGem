
#pragma once
#include <nakama-cpp/data/NAccount.h>
#include <nakama-cpp/data/NAccountDevice.h>
#include <nakama-cpp/data/NChannelMessage.h>
#include <nakama-cpp/data/NChannelMessageList.h>
#include <nakama-cpp/data/NFriend.h>
#include <nakama-cpp/data/NFriendList.h>
#include <nakama-cpp/data/NGroup.h>
#include <nakama-cpp/data/NGroupList.h>
#include <nakama-cpp/data/NGroupUser.h>
#include <nakama-cpp/data/NGroupUserList.h>
#include <nakama-cpp/data/NLeaderboardRecord.h>
#include <nakama-cpp/data/NLeaderboardRecordList.h>
#include <nakama-cpp/data/NMatch.h>
#include <nakama-cpp/data/NMatchList.h>
#include <nakama-cpp/data/NNotification.h>
#include <nakama-cpp/data/NNotificationList.h>
#include <nakama-cpp/data/NRpc.h>
#include <nakama-cpp/data/NStorageObject.h>
#include <nakama-cpp/data/NStorageObjectAck.h>
#include <nakama-cpp/data/NStorageObjectId.h>
#include <nakama-cpp/data/NStorageObjectList.h>
#include <nakama-cpp/data/NStorageObjectWrite.h>
#include <nakama-cpp/data/NStoragePermissions.h>
#include <nakama-cpp/data/NTournament.h>
#include <nakama-cpp/data/NTournamentList.h>
#include <nakama-cpp/data/NTournamentRecordList.h>
#include <nakama-cpp/data/NUser.h>
#include <nakama-cpp/data/NUserGroup.h>
#include <nakama-cpp/data/NUserGroupList.h>
#include <nakama-cpp/data/NUsers.h>
#include <nakama-cpp/NError.h>

#include <nakama-cpp/realtime/rtdata/NChannel.h>
#include <nakama-cpp/realtime/rtdata/NChannelMessageAck.h>
#include <nakama-cpp/realtime/rtdata/NChannelPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NMatchData.h>
#include <nakama-cpp/realtime/rtdata/NMatchmakerMatched.h>
#include <nakama-cpp/realtime/rtdata/NMatchmakerTicket.h>
#include <nakama-cpp/realtime/rtdata/NMatchPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NParty.h>
#include <nakama-cpp/realtime/rtdata/NPartyClose.h>
#include <nakama-cpp/realtime/rtdata/NPartyData.h>
#include <nakama-cpp/realtime/rtdata/NPartyJoinRequest.h>
#include <nakama-cpp/realtime/rtdata/NPartyLeader.h>
#include <nakama-cpp/realtime/rtdata/NPartyMatchmakerTicket.h>
#include <nakama-cpp/realtime/rtdata/NPartyPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NRtError.h>
#include <nakama-cpp/realtime/rtdata/NRtException.h>
#include <nakama-cpp/realtime/rtdata/NStatus.h>
#include <nakama-cpp/realtime/rtdata/NStatusPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NStream.h>
#include <nakama-cpp/realtime/rtdata/NStreamData.h>
#include <nakama-cpp/realtime/rtdata/NStreamPresenceEvent.h>
#include <nakama-cpp/realtime/rtdata/NUserPresence.h>

#include <nakama-cpp/realtime/NRtClientDisconnectInfo.h>

#include <AzCore/std/string/string.h>
#include <AzCore/std/containers/vector.h>
#include <AzCore/std/containers/unordered_map.h>

#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/RTTI/ReflectContext.h>

namespace NakamaClientGem
{
    using AZStringMap = AZStd::vector<AZStd::pair<AZStd::string, AZStd::string>>;
    using AZStringDoubleMap = AZStd::vector<AZStd::pair<AZStd::string, double>>;

    AZStringMap AZStringMapFromNakama(const Nakama::NStringMap& nMap)
    {
        AZStringMap map;
        if (nMap.size() != 0)
        {
            for (auto kv : nMap)
            {
                map.push_back({ kv.first.c_str(), kv.second.c_str() });
            }
        }
        return map;
    }

    Nakama::NStringMap AZStringMapToNakama(const AZStringMap& aMap)
    {
        Nakama::NStringMap map;
        if (aMap.size() != 0)
        {
            for (auto kv : aMap)
            {
                map.emplace(kv.first.c_str(), kv.second.c_str());
            }
        }
        return map;
    }

    AZStringDoubleMap AZStringDoubleMapFromNakama(const Nakama::NStringDoubleMap& nMap)
    {
        AZStringDoubleMap map;
        if (nMap.size() != 0)
        {
            for (auto kv : nMap)
            {
                map.push_back({ kv.first.c_str(), kv.second });
            }
        }
        return map;
    }

    Nakama::NStringDoubleMap AZStringDoubleMapToNakama(const AZStringDoubleMap& aMap)
    {
        Nakama::NStringDoubleMap map;
        if (aMap.size() != 0)
        {
            for (auto kv : aMap)
            {
                map.emplace(kv.first.c_str(), kv.second);
            }
        }
        return map;
    }

    struct RtClientDisconnectInfo
    {
        AZ_TYPE_INFO(RtClientDisconnectInfo, "{7A75E45C-C352-4300-BFB3-0057F11E3F01}");

        AZ_CLASS_ALLOCATOR(RtClientDisconnectInfo, AZ::SystemAllocator, 0);
        RtClientDisconnectInfo()
            : code(0), reason(), remote(false)
        {
        }

        /// close code.
        /// https://developer.mozilla.org/en-US/docs/Web/API/CloseEvent
        AZ::u16 code = 0;

        /// close reason. Optional.
        AZStd::string reason;

        /// true if close was initiated by server.
        bool remote = false;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<RtClientDisconnectInfo>()
                    ->Version(1)
                    ->Field("code", &RtClientDisconnectInfo::code)
                    ->Field("reason", &RtClientDisconnectInfo::reason)
                    ->Field("remote", &RtClientDisconnectInfo::remote)
                    ;
            }
        }


        static RtClientDisconnectInfo FromNakama(const Nakama::NRtClientDisconnectInfo& nInfo)
        {
            RtClientDisconnectInfo info;
            info.code = static_cast<AZ::u16>(nInfo.code);
            info.reason = nInfo.reason.c_str();
            info.remote = nInfo.remote;
            return info;
        }
    };

    struct RtError
    {
        AZ_TYPE_INFO(RtError, "{C88C27B3-E865-40C1-8692-87F7174FB303}");
        AZ_CLASS_ALLOCATOR(RtError, AZ::SystemAllocator, 0);
        RtError()
            : code(-100), message(), context({})
        {
        }

        AZ::s8 code = -100;      ///< The error code
        AZStd::string message;                          ///< A message in English to help developers debug the response.
        AZStringMap context;                           ///< Additional error details which may be different for each response.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<RtError>()
                    ->Version(1)
                    ->Field("code", &RtError::code)
                    ->Field("message", &RtError::message)
                    ->Field("context", &RtError::context)
                    ;
            }
        }

        static RtError FromNakama(const Nakama::NRtError& nError)
        {
            RtError error;
            error.code = static_cast<AZ::s8>(nError.code);
            error.message = nError.message.c_str();
            error.context = AZStringMapFromNakama(nError.context);
            return error;
        }
    };

    /// A message sent on a channel.
    struct ChannelMessage
    {
        AZ_TYPE_INFO(ChannelMessage, "{E6C749B9-15A3-4B22-AF69-257090B64ED8}");
        AZ_CLASS_ALLOCATOR(ChannelMessage, AZ::SystemAllocator, 0);
        ChannelMessage()
            : channelId(), messageId(), code(0), senderId(), username(), content(), createTime(0), updateTime(0), persistent(false), roomName(), groupId(), userIdOne(), userIdTwo()
        {
        }

        AZStd::string channelId;         ///< The channel this message belongs to.
        AZStd::string messageId;         ///< The unique ID of this message.
        AZ::s32 code = 0;              ///< The code representing a message type or category.
        AZStd::string senderId;          ///< Message sender, usually a user ID.
        AZStd::string username;          ///< The username of the message sender, if any.
        AZStd::string content;           ///< The content payload.
        AZ::u64 createTime = 0;     ///< The UNIX time when the message was created.
        AZ::u64 updateTime = 0;     ///< The UNIX time when the message was last updated.
        bool persistent = false;       ///< True if the message was persisted to the channel's history, false otherwise.
        AZStd::string roomName;          ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        AZStd::string groupId;           ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        AZStd::string userIdOne;         ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        AZStd::string userIdTwo;         ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<ChannelMessage>()
                    ->Version(1)
                    ->Field("channelId", &ChannelMessage::channelId)
                    ->Field("messageId", &ChannelMessage::messageId)
                    ->Field("code", &ChannelMessage::code)
                    ->Field("senderId", &ChannelMessage::senderId)
                    ->Field("username", &ChannelMessage::username)
                    ->Field("content", &ChannelMessage::content)
                    ->Field("createTime", &ChannelMessage::createTime)
                    ->Field("updateTime", &ChannelMessage::updateTime)
                    ->Field("persistent", &ChannelMessage::persistent)
                    ->Field("roomName", &ChannelMessage::roomName)
                    ->Field("groupId", &ChannelMessage::groupId)
                    ->Field("userIdOne", &ChannelMessage::userIdOne)
                    ->Field("userIdTwo", &ChannelMessage::userIdTwo)
                    ;
            }
        }

        static ChannelMessage FromNakama(const Nakama::NChannelMessage& nMessage)
        {
            ChannelMessage message;
            message.channelId = nMessage.channelId.c_str();
            message.messageId = nMessage.messageId.c_str();
            message.code = static_cast<AZ::s32>(nMessage.code);
            message.senderId = nMessage.senderId.c_str();
            message.username = nMessage.username.c_str();
            message.content = nMessage.content.c_str();
            message.createTime = static_cast<AZ::u64>(nMessage.createTime);
            message.updateTime = static_cast<AZ::u64>(nMessage.updateTime);
            message.persistent = nMessage.persistent;
            message.roomName = nMessage.roomName.c_str();
            message.groupId = nMessage.groupId.c_str();
            message.userIdOne = nMessage.userIdOne.c_str();
            message.userIdTwo = nMessage.userIdTwo.c_str();
            return message;
        }
    };

    /// A user session associated to a stream, usually through a list operation or a join/leave event.
    struct UserPresence
    {
        AZ_TYPE_INFO(UserPresence, "{236C7FE3-C74A-472B-84B9-914AA7F34891}");
        AZ_CLASS_ALLOCATOR(UserPresence, AZ::SystemAllocator, 0);
        UserPresence()
            : userId(), sessionId(), username(), persistence(false), status()
        {
        }

        AZStd::string userId;             ///< The user this presence belongs to.
        AZStd::string sessionId;          ///< A unique session ID identifying the particular connection, because the user may have many.
        AZStd::string username;           ///< The username for display purposes.
        bool persistence = false;       ///< Whether this presence generates persistent data/messages, if applicable for the stream type.
        AZStd::string status;             ///< A user-set status message for this stream, if applicable.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<UserPresence>()
                    ->Version(1)
                    ->Field("userId", &UserPresence::userId)
                    ->Field("sessionId", &UserPresence::sessionId)
                    ->Field("username", &UserPresence::username)
                    ->Field("persistence", &UserPresence::persistence)
                    ->Field("status", &UserPresence::status)
                    ;
            }
        }

        static UserPresence FromNakama(const Nakama::NUserPresence& nPresence)
        {
            UserPresence presence;
            presence.userId = nPresence.userId.c_str();
            presence.sessionId = nPresence.sessionId.c_str();
            presence.username = nPresence.username.c_str();
            presence.persistence = nPresence.persistence;
            presence.status = nPresence.status.c_str();
            return presence;
        }
    };

    /// A set of joins and leaves on a particular channel.
    struct ChannelPresenceEvent
    {
        AZ_TYPE_INFO(ChannelPresenceEvent, "{A39D9B25-B43C-4762-B1B4-947154C49E14}");
        AZ_CLASS_ALLOCATOR(ChannelPresenceEvent, AZ::SystemAllocator, 0);
        ChannelPresenceEvent()
            : channelId(), joins(), leaves(), roomName(), groupId(), userIdOne(), userIdTwo()
        {
        }
        AZStd::string channelId;                   ///< The channel identifier this event is for.
        AZStd::vector<UserPresence> joins;        ///< Presences joining the channel as part of this event, if any.
        AZStd::vector<UserPresence> leaves;       ///< Presences leaving the channel as part of this event, if any.
        AZStd::string roomName;                    ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        AZStd::string groupId;                     ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        AZStd::string userIdOne;                   ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        AZStd::string userIdTwo;                   ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<ChannelPresenceEvent>()
                    ->Version(1)
                    ->Field("channelId", &ChannelPresenceEvent::channelId)
                    ->Field("joins", &ChannelPresenceEvent::joins)
                    ->Field("leaves", &ChannelPresenceEvent::leaves)
                    ->Field("roomName", &ChannelPresenceEvent::roomName)
                    ->Field("groupId", &ChannelPresenceEvent::groupId)
                    ->Field("userIdOne", &ChannelPresenceEvent::userIdOne)
                    ->Field("userIdTwo", &ChannelPresenceEvent::userIdTwo)
                    ;
            }
        }

        static ChannelPresenceEvent FromNakama(const Nakama::NChannelPresenceEvent& nEvent)
        {
            ChannelPresenceEvent event;
            event.channelId = nEvent.channelId.c_str();
            if (nEvent.joins.size() != 0)
            {
                for (const auto& nJoin : nEvent.joins)
                {
                    event.joins.push_back(UserPresence::FromNakama(nJoin));
                }
            }
            if (nEvent.leaves.size() != 0)
            {
                for (const auto& nLeave : nEvent.leaves)
                {
                    event.leaves.push_back(UserPresence::FromNakama(nLeave));
                }
            }
            event.roomName = nEvent.roomName.c_str();
            event.groupId = nEvent.groupId.c_str();
            event.userIdOne = nEvent.userIdOne.c_str();
            event.userIdTwo = nEvent.userIdTwo.c_str();
            return event;
        }
    };


    struct MatchmakerUser
    {
        AZ_TYPE_INFO(MatchmakerUser, "{2CC0027F-74CA-4FF2-9807-5A2A0C7816DD}");
        AZ_CLASS_ALLOCATOR(MatchmakerUser, AZ::SystemAllocator, 0);
        MatchmakerUser()
            : presence(), stringProperties(), numericProperties()
        {
        }
        UserPresence presence;                  ///< User info.
        AZStringMap stringProperties;             ///< String properties.
        AZStringDoubleMap numericProperties;      ///< Numeric properties.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MatchmakerUser>()
                    ->Version(1)
                    ->Field("presence", &MatchmakerUser::presence)
                    ->Field("stringProperties", &MatchmakerUser::stringProperties)
                    ->Field("numericProperties", &MatchmakerUser::numericProperties)
                    ;
            }
        }

        static MatchmakerUser FromNakama(const Nakama::NMatchmakerUser& nUser)
        {
            MatchmakerUser user;
            user.presence = UserPresence::FromNakama(nUser.presence);
            user.stringProperties = AZStringMapFromNakama(nUser.stringProperties);
            user.numericProperties = AZStringDoubleMapFromNakama(nUser.numericProperties);
            return user;
        }
    };

    /// A successful matchmaking result.
    struct MatchmakerMatched
    {
        AZ_TYPE_INFO(MatchmakerMatched, "{517D1267-C331-42DE-9587-43E5D84B17C1}");
        AZ_CLASS_ALLOCATOR(MatchmakerMatched, AZ::SystemAllocator, 0);
        MatchmakerMatched()
            : ticket(), matchId(), token(), users(), self()
        {
        }
        AZStd::string ticket;                  ///< The matchmaking ticket that has completed.
        ///< The match token or match ID to join.
        AZStd::string matchId;                 ///< Match ID.
        AZStd::string token;                   ///< Match join token.
        AZStd::vector<MatchmakerUser> users;  ///< The users that have been matched together, and information about their matchmaking data.
        MatchmakerUser self;                ///< A reference to the current user and their properties.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MatchmakerMatched>()
                    ->Version(1)
                    ->Field("ticket", &MatchmakerMatched::ticket)
                    ->Field("matchId", &MatchmakerMatched::matchId)
                    ->Field("token", &MatchmakerMatched::token)
                    ->Field("users", &MatchmakerMatched::users)
                    ->Field("self", &MatchmakerMatched::self)
                    ;
            }
        }

        static MatchmakerMatched FromNakama(const Nakama::NMatchmakerMatched& nMatched)
        {
            MatchmakerMatched matched;
            matched.ticket = nMatched.ticket.c_str();
            matched.matchId = nMatched.matchId.c_str();
            matched.token = nMatched.token.c_str();
            if (nMatched.users.size() != 0)
            {
                for (const auto& nUser : nMatched.users)
                {
                    matched.users.push_back(MatchmakerUser::FromNakama(nUser));
                }
            }
            matched.self = MatchmakerUser::FromNakama(nMatched.self);
            return matched;
        }
    };

    /// Realtime match data received from the server.
    struct MatchData
    {
        AZ_TYPE_INFO(MatchData, "{88BCBC9F-1A1D-47FB-8FAA-F02B087D4B95}");
        AZ_CLASS_ALLOCATOR(MatchData, AZ::SystemAllocator, 0);
        MatchData()
            : matchId(), presence(), opCode(0), data()
        {
        }

        AZStd::string matchId;       ///< The match unique ID.
        UserPresence presence;    ///< A reference to the user presence that sent this data, if any.
        AZ::s64 opCode;            ///< Op code value.
        AZStd::string data;               ///< Data payload, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MatchData>()
                    ->Version(1)
                    ->Field("matchId", &MatchData::matchId)
                    ->Field("presence", &MatchData::presence)
                    ->Field("opCode", &MatchData::opCode)
                    ->Field("data", &MatchData::data)
                    ;
            }
        }

        static MatchData FromNakama(const Nakama::NMatchData& nData)
        {
            MatchData data;
            data.matchId = nData.matchId.c_str();
            data.presence = UserPresence::FromNakama(nData.presence);
            data.opCode = nData.opCode;
            data.data = nData.data.c_str();
            return data;
        }
    };

    /// A set of joins and leaves on a particular realtime match.
    struct MatchPresenceEvent
    {
        AZ_TYPE_INFO(MatchPresenceEvent, "{336ABA9E-6100-4711-8657-5CC7F86CFED6}");
        AZ_CLASS_ALLOCATOR(MatchData, AZ::SystemAllocator, 0);
        MatchPresenceEvent()
            : matchId(), joins(), leaves(0)
        {
        }

        AZStd::string matchId;                 /// The match unique ID.
        AZStd::vector<UserPresence> joins;    /// User presences that have just joined the match.
        AZStd::vector<UserPresence> leaves;   /// User presences that have just left the match.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MatchPresenceEvent>()
                    ->Version(1)
                    ->Field("matchId", &MatchPresenceEvent::matchId)
                    ->Field("joins", &MatchPresenceEvent::joins)
                    ->Field("leaves", &MatchPresenceEvent::leaves)
                    ;
            }
        }

        static MatchPresenceEvent FromNakama(const Nakama::NMatchPresenceEvent& nEvent)
        {
            MatchPresenceEvent event;
            event.matchId = nEvent.matchId.c_str();
            if (nEvent.joins.size() != 0)
            {
                for (const auto& nJoin : nEvent.joins)
                {
                    event.joins.push_back(UserPresence::FromNakama(nJoin));
                }
            }
            if (nEvent.leaves.size() != 0)
            {
                for (const auto& nLeave : nEvent.leaves)
                {
                    event.leaves.push_back(UserPresence::FromNakama(nLeave));
                }
            }
            return event;
        }
    };

    /// A notification in the server.
    struct Notification
    {
        AZ_TYPE_INFO(Notification, "{9095DEFF-3E23-4AA0-AF74-FBFC8718D149}");
        AZ_CLASS_ALLOCATOR(Notification, AZ::SystemAllocator, 0);
        Notification()
            : id(), subject(), content(), code(0), senderId(), createTime(0), persistent(false)
        {
        }

        AZStd::string id;                  ///< ID of the Notification.
        AZStd::string subject;             ///< Subject of the notification.
        AZStd::string content;             ///< Content of the notification in JSON.
        AZ::s32 code = 0;                ///< Category code for this notification.
        AZStd::string senderId;            ///< ID of the sender, if a user. Otherwise 'null'.
        AZ::u64 createTime = 0;       ///< The UNIX time when the notification was created.
        bool persistent = false;         ///< True if this notification was persisted to the database.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Notification>()
                    ->Version(1)
                    ->Field("id", &Notification::id)
                    ->Field("subject", &Notification::subject)
                    ->Field("content", &Notification::content)
                    ->Field("code", &Notification::code)
                    ->Field("senderId", &Notification::senderId)
                    ->Field("createTime", &Notification::createTime)
                    ->Field("persistent", &Notification::persistent)
                    ;
            }
        }

        static Notification FromNakama(const Nakama::NNotification& nNotification)
        {
            Notification notification;
            notification.id = nNotification.id.c_str();
            notification.subject = nNotification.subject.c_str();
            notification.content = nNotification.content.c_str();
            notification.code = nNotification.code;
            notification.senderId = nNotification.senderId.c_str();
            notification.createTime = nNotification.createTime;
            notification.persistent = nNotification.persistent;
            return notification;
        }
    };

    /// A collection of zero or more notifications.
    struct NotificationList
    {
        AZ_TYPE_INFO(NotificationList, "{FFC94E9A-883A-44CE-A8AD-4D61B543D2D5}");
        AZ_CLASS_ALLOCATOR(NotificationList, AZ::SystemAllocator, 0);
        NotificationList()
            : notifications(), cacheableCursor()
        {
        }

        AZStd::vector<Notification> notifications;      ///< Collection of notifications.
        AZStd::string cacheableCursor;                   ///< Use this cursor to paginate notifications. Cache this to catch up to new notifications.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<NotificationList>()
                    ->Version(1)
                    ->Field("notifications", &NotificationList::notifications)
                    ->Field("cacheableCursor", &NotificationList::cacheableCursor)
                    ;
            }
        }

        static NotificationList FromNakama(const Nakama::NNotificationList& nList)
        {
            NotificationList list;
            if (nList.notifications.size() != 0)
            {
                for (const auto& nNotification : nList.notifications)
                {
                    list.notifications.push_back(Notification::FromNakama(nNotification));
                }
            }
            list.cacheableCursor = nList.cacheableCursor.c_str();
            return list;
        }
    };

    /// Information about a party.
    struct Party
    {
        AZ_TYPE_INFO(Party, "{F5221BAD-EA5C-4696-8DEC-C4AB8BA5C2D2}");
        AZ_CLASS_ALLOCATOR(Party, AZ::SystemAllocator, 0);
        Party()
            : id(), open(false), maxSize(0), self(), leader(), presences()
        {
        }

        AZStd::string id; /// The unique party identifier.

        bool open; /// True, if the party is open to join.

        int maxSize; /// The maximum number of party members.

        UserPresence self;  /// The current user in this party. i.e. Yourself.

        UserPresence leader; /// The current party leader.

        AZStd::vector<UserPresence> presences; /// All members currently in the party.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Party>()
                    ->Version(1)
                    ->Field("id", &Party::id)
                    ->Field("open", &Party::open)
                    ->Field("maxSize", &Party::maxSize)
                    ->Field("self", &Party::self)
                    ->Field("leader", &Party::leader)
                    ->Field("presences", &Party::presences)
                    ;
            }
        }

        static Party FromNakama(const Nakama::NParty& nParty)
        {
            Party party;
            party.id = nParty.id.c_str();
            party.open = nParty.open;
            party.maxSize = nParty.maxSize;
            party.self = UserPresence::FromNakama(nParty.self);
            party.leader = UserPresence::FromNakama(nParty.leader);
            if (nParty.presences.size() != 0)
            {
                for (const auto& nPresence : nParty.presences)
                {
                    party.presences.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            return party;
        }
    };

    /// Information about a party close event.
    struct PartyClose
    {
        AZ_TYPE_INFO(PartyClose, "{1524429A-20FF-4773-8D73-664E0D405706}");
        AZ_CLASS_ALLOCATOR(PartyClose, AZ::SystemAllocator, 0);
        PartyClose()
            : id()
        {
        }
        AZStd::string id; /// The unique party identifier of the closing party.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyClose>()
                    ->Version(1)
                    ->Field("id", &PartyClose::id)
                    ;
            }
        }

        static PartyClose FromNakama(const Nakama::NPartyClose& nClose)
        {
            PartyClose close;
            close.id = nClose.id.c_str();
            return close;
        }
    };

    /// Incoming party data delivered from the server.
    struct PartyData
    {
        AZ_TYPE_INFO(PartyData, "{296FDDB3-4629-4965-9094-810222471B53}");
        AZ_CLASS_ALLOCATOR(PartyData, AZ::SystemAllocator, 0);
        PartyData()
            : partyId(), presence(), opCode(0), data()
        {
        }
        /// The ID of the party.
        AZStd::string partyId;

        /// A reference to the user presence that sent this data, if any.
        UserPresence presence;

        /// The operation code the message was sent with.
        AZ::s64 opCode;

        /// Data payload, if any.
        AZStd::string data;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyData>()
                    ->Version(1)
                    ->Field("partyId", &PartyData::partyId)
                    ->Field("presence", &PartyData::presence)
                    ->Field("opCode", &PartyData::opCode)
                    ->Field("data", &PartyData::data)
                    ;
            }
        }

        static PartyData FromNakama(const Nakama::NPartyData& nData)
        {
            PartyData data;
            data.partyId = nData.partyId.c_str();
            data.presence = UserPresence::FromNakama(nData.presence);
            data.opCode = nData.opCode;
            data.data = nData.data.c_str();
            return data;
        }
    };

    /// Incoming notification for one or more new presences attempting to join the party.
    struct PartyJoinRequest
    {
        AZ_TYPE_INFO(PartyJoinRequest, "{198AA86B-14C7-4483-BEED-77DB89B33081}");
        AZ_CLASS_ALLOCATOR(PartyJoinRequest, AZ::SystemAllocator, 0);
        PartyJoinRequest()
            : partyId(), presences()
        {
        }
        /// The ID of the party to get a list of join requests for.
        AZStd::string partyId;

        /// Presences attempting to join, or who have joined.
        AZStd::vector<UserPresence> presences;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyJoinRequest>()
                    ->Version(1)
                    ->Field("partyId", &PartyJoinRequest::partyId)
                    ->Field("presences", &PartyJoinRequest::presences)
                    ;
            }
        }

        static PartyJoinRequest FromNakama(const Nakama::NPartyJoinRequest& nRequest)
        {
            PartyJoinRequest request;
            request.partyId = nRequest.partyId.c_str();
            if (nRequest.presences.size() != 0)
            {
                for (const auto& nPresence : nRequest.presences)
                {
                    request.presences.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            return request;
        }
    };

    /// Announcement of a new party leader.
    struct PartyLeader
    {
        AZ_TYPE_INFO(PartyLeader, "{86BD5DD4-B583-4571-B416-4FC3F2AF0824}");
        AZ_CLASS_ALLOCATOR(PartyLeader, AZ::SystemAllocator, 0);
        PartyLeader()
            : partyId(), presence()
        {
        }
        /// The ID of the party to announce the new leader for.
        AZStd::string partyId;

        /// The presence of the new party leader.
        UserPresence presence;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyLeader>()
                    ->Version(1)
                    ->Field("partyId", &PartyLeader::partyId)
                    ->Field("presence", &PartyLeader::presence)
                    ;
            }
        }

        static PartyLeader FromNakama(const Nakama::NPartyLeader& nLeader)
        {
            PartyLeader leader;
            leader.partyId = nLeader.partyId.c_str();
            leader.presence = UserPresence::FromNakama(nLeader.presence);
            return leader;
        }
    };

    /// A response from starting a new party matchmaking process.
    struct PartyMatchmakerTicket
    {
        AZ_TYPE_INFO(PartyMatchmakerTicket, "{EE001C44-FDD8-478D-97CB-71AA904BBC7D}");
        AZ_CLASS_ALLOCATOR(PartyMatchmakerTicket, AZ::SystemAllocator, 0);
        PartyMatchmakerTicket()
            : partyId(), ticket()
        {
        }
        /// The ID of the party.
        AZStd::string partyId;

        /// The ticket that can be used to cancel matchmaking.
        AZStd::string ticket;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyMatchmakerTicket>()
                    ->Version(1)
                    ->Field("partyId", &PartyMatchmakerTicket::partyId)
                    ->Field("ticket", &PartyMatchmakerTicket::ticket)
                    ;
            }
        }

        static PartyMatchmakerTicket FromNakama(const Nakama::NPartyMatchmakerTicket& nTicket)
        {
            PartyMatchmakerTicket ticket;
            ticket.partyId = nTicket.partyId.c_str();
            ticket.ticket = nTicket.ticket.c_str();
            return ticket;
        }
    };

    /// Presence update for a particular party.
    struct PartyPresenceEvent
    {
        AZ_TYPE_INFO(PartyPresenceEvent, "{69F8581F-33BD-438B-9B07-9A3061E952E8}");
        AZ_CLASS_ALLOCATOR(PartyPresenceEvent, AZ::SystemAllocator, 0);
        PartyPresenceEvent()
            : partyId(), joins(), leaves()
        {
        }
        /// The ID of the party.
        AZStd::string partyId;

        /// The user presences that have just joined the party.
        AZStd::vector<UserPresence> joins;

        /// The user presences that have just left the party.
        AZStd::vector<UserPresence> leaves;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<PartyPresenceEvent>()
                    ->Version(1)
                    ->Field("partyId", &PartyPresenceEvent::partyId)
                    ->Field("joins", &PartyPresenceEvent::joins)
                    ->Field("leaves", &PartyPresenceEvent::leaves)
                    ;
            }
        }
        static PartyPresenceEvent FromNakama(const Nakama::NPartyPresenceEvent& nEvent)
        {
            PartyPresenceEvent presence;
            presence.partyId = nEvent.partyId.c_str();
            if (nEvent.joins.size() != 0)
            {
                for (const auto& nPresence : nEvent.joins)
                {
                    presence.joins.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            if (nEvent.leaves.size() != 0)
            {
                for (const auto& nPresence : nEvent.leaves)
                {
                    presence.leaves.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            return presence;
        }
    };

    /// A batch of status updates for a given user.
    struct StatusPresenceEvent
    {
        AZ_TYPE_INFO(StatusPresenceEvent, "{69F8581F-33BD-438B-9B07-9A3061E952E8}");
        AZ_CLASS_ALLOCATOR(StatusPresenceEvent, AZ::SystemAllocator, 0);
        StatusPresenceEvent()
            : joins(), leaves()
        {
        }
        AZStd::vector<UserPresence> joins;    ///< New statuses for the user.
        AZStd::vector<UserPresence> leaves;   ///< Previous statuses for the user.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StatusPresenceEvent>()
                    ->Version(1)
                    ->Field("joins", &StatusPresenceEvent::joins)
                    ->Field("leaves", &StatusPresenceEvent::leaves)
                    ;
            }
        }

        static StatusPresenceEvent FromNakama(const Nakama::NStatusPresenceEvent& nEvent)
        {
            StatusPresenceEvent presence;
            if (nEvent.joins.size() != 0)
            {
                for (const auto& nPresence : nEvent.joins)
                {
                    presence.joins.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            if (nEvent.leaves.size() != 0)
            {
                for (const auto& nPresence : nEvent.leaves)
                {
                    presence.leaves.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            return presence;
        }
    };

    /// Represents identifying information for a stream.
    struct Stream
    {
        AZ_TYPE_INFO(Stream, "{3D51DCFD-F9BB-49DC-8091-7286BB60657E}");
        AZ_CLASS_ALLOCATOR(Stream, AZ::SystemAllocator, 0);
        Stream()
            : mode(0)
        {
        }
        AZ::s32 mode = 0;               ///< Mode identifies the type of stream.
        AZStd::string subject;            ///< Subject is the primary identifier, if any.
        AZStd::string subcontext;         ///< Subcontext is a secondary identifier, if any.
        AZStd::string label;              ///< The label is an arbitrary identifying string, if the stream has one.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Stream>()
                    ->Version(1)
                    ->Field("mode", &Stream::mode)
                    ->Field("subject", &Stream::subject)
                    ->Field("subcontext", &Stream::subcontext)
                    ->Field("label", &Stream::label)
                    ;
            }
        }

        static Stream FromNakama(const Nakama::NStream& nStream)
        {
            Stream stream;
            stream.mode = nStream.mode;
            stream.subject = nStream.subject.c_str();
            stream.subcontext = nStream.subcontext.c_str();
            stream.label = nStream.label.c_str();
            return stream;
        }
    };

    /// A set of joins and leaves on a particular stream.
    struct StreamPresenceEvent
    {
        AZ_TYPE_INFO(StreamPresenceEvent, "{98E87759-8989-4CF5-906B-E26B8D3AD761}");
        AZ_CLASS_ALLOCATOR(StreamPresenceEvent, AZ::SystemAllocator, 0);
        StreamPresenceEvent()
            : stream()
        {
        }
        Stream stream;                      ///< The stream this event relates to.
        AZStd::vector<UserPresence> joins;    ///< Presences joining the stream as part of this event, if any.
        AZStd::vector<UserPresence> leaves;   ///< Presences leaving the stream as part of this event, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StreamPresenceEvent>()
                    ->Version(1)
                    ->Field("stream", &StreamPresenceEvent::stream)
                    ->Field("joins", &StreamPresenceEvent::joins)
                    ->Field("leaves", &StreamPresenceEvent::leaves)
                    ;
            }
        }

        static StreamPresenceEvent FromNakama(const Nakama::NStreamPresenceEvent& nEvent)
        {
            StreamPresenceEvent presence;
            presence.stream = Stream::FromNakama(nEvent.stream);
            if (nEvent.joins.size() != 0)
            {
                for (const auto& nPresence : nEvent.joins)
                {
                    presence.joins.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            if (nEvent.leaves.size() != 0)
            {
                for (const auto& nPresence : nEvent.leaves)
                {
                    presence.leaves.push_back(UserPresence::FromNakama(nPresence));
                }
            }
            return presence;
        }
    };

    /// A data message delivered over a stream.
    struct StreamData
    {
        AZ_TYPE_INFO(StreamData, "{EDB4A31C-2583-4006-858F-7CECD0CC4C8F}");
        AZ_CLASS_ALLOCATOR(StreamData, AZ::SystemAllocator, 0);
        StreamData()
            : stream()
        {
        }
        Stream stream;          ///< The stream this data message relates to.
        UserPresence sender;    ///< The sender, if any.
        AZStd::string data;        ///< Arbitrary contents of the data message.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StreamData>()
                    ->Version(1)
                    ->Field("stream", &StreamData::stream)
                    ->Field("sender", &StreamData::sender)
                    ->Field("data", &StreamData::data)
                    ;
            }
        }

        static StreamData FromNakama(const Nakama::NStreamData& nData)
        {
            StreamData data;
            data.stream = Stream::FromNakama(nData.stream);
            data.sender = UserPresence::FromNakama(nData.sender);
            data.data = nData.data.c_str();
            return data;
        }
    };

    
} // namespace NakamaClientGem
