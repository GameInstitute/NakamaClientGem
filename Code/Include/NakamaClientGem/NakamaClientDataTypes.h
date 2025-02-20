
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
#include <AzCore/Serialization/EditContext.h>

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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<RtClientDisconnectInfo>("RtClientDisconnectInfo", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtClientDisconnectInfo::code, "Code", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtClientDisconnectInfo::reason, "Reason", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtClientDisconnectInfo::remote, "Remote", "");
                }
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<RtClientDisconnectInfo>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("code", BehaviorValueProperty(&RtClientDisconnectInfo::code))
                    ->Property("reason", BehaviorValueProperty(&RtClientDisconnectInfo::reason))
                    ->Property("remote", BehaviorValueProperty(&RtClientDisconnectInfo::remote));
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<RtError>("RtError", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtError::code, "Code", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtError::message, "Message", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &RtError::context, "Context", "");
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<RtError>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("code", BehaviorValueProperty(&RtError::code))
                    ->Property("message", BehaviorValueProperty(&RtError::message))
                    ->Property("context", BehaviorValueProperty(&RtError::context));
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<ChannelMessage>("ChannelMessage", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::channelId, "ChannelId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::messageId, "MessageId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::code, "Code", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::senderId, "SenderId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::username, "Username", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::content, "Content", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::updateTime, "UpdateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::persistent, "Persistent", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::roomName, "RoomName", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::groupId, "GroupId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::userIdOne, "UserIdOne", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessage::userIdTwo, "UserIdTwo", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<ChannelMessage>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("channelId", BehaviorValueProperty(&ChannelMessage::channelId))
                    ->Property("messageId", BehaviorValueProperty(&ChannelMessage::messageId))
                    ->Property("code", BehaviorValueProperty(&ChannelMessage::code))
                    ->Property("senderId", BehaviorValueProperty(&ChannelMessage::senderId))
                    ->Property("username", BehaviorValueProperty(&ChannelMessage::username))
                    ->Property("content", BehaviorValueProperty(&ChannelMessage::content))
                    ->Property("createTime", BehaviorValueProperty(&ChannelMessage::createTime))
                    ->Property("updateTime", BehaviorValueProperty(&ChannelMessage::updateTime))
                    ->Property("persistent", BehaviorValueProperty(&ChannelMessage::persistent))
                    ->Property("roomName", BehaviorValueProperty(&ChannelMessage::roomName))
                    ->Property("groupId", BehaviorValueProperty(&ChannelMessage::groupId))
                    ->Property("userIdOne", BehaviorValueProperty(&ChannelMessage::userIdOne))
                    ->Property("userIdTwo", BehaviorValueProperty(&ChannelMessage::userIdTwo))
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

        static Nakama::NChannelMessage ToNakama(const ChannelMessage& message)
        {
            Nakama::NChannelMessage nMessage;
            nMessage.channelId = message.channelId.c_str();
            nMessage.messageId = message.messageId.c_str();
            nMessage.code = static_cast<int32_t>(message.code);
            nMessage.senderId = message.senderId.c_str();
            nMessage.username = message.username.c_str();
            nMessage.content = message.content.c_str();
            nMessage.createTime = static_cast<int64_t>(message.createTime);
            nMessage.updateTime = static_cast<int64_t>(message.updateTime);
            nMessage.persistent = message.persistent;
            nMessage.roomName = message.roomName.c_str();
            nMessage.groupId = message.groupId.c_str();
            nMessage.userIdOne = message.userIdOne.c_str();
            nMessage.userIdTwo = message.userIdTwo.c_str();
            return nMessage;
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<UserPresence>("UserPresence", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserPresence::userId, "UserId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserPresence::sessionId, "SessionId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserPresence::username, "Username", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserPresence::persistence, "Persistence", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserPresence::status, "Status", "")
                        ;
                }
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<UserPresence>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("userId", BehaviorValueProperty(&UserPresence::userId))
                    ->Property("sessionId", BehaviorValueProperty(&UserPresence::sessionId))
                    ->Property("username", BehaviorValueProperty(&UserPresence::username))
                    ->Property("persistence", BehaviorValueProperty(&UserPresence::persistence))
                    ->Property("status", BehaviorValueProperty(&UserPresence::status))
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

        static Nakama::NUserPresence ToNakama(const UserPresence& presence)
        {
            Nakama::NUserPresence nPresence;
            nPresence.userId = presence.userId.c_str();
            nPresence.sessionId = presence.sessionId.c_str();
            nPresence.username = presence.username.c_str();
            nPresence.persistence = presence.persistence;
            nPresence.status = presence.status.c_str();
            return nPresence;
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<ChannelPresenceEvent>("ChannelPresenceEvent", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::channelId, "ChannelId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::joins, "Joins", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::leaves, "Leaves", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::roomName,"RoomName", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::groupId, "GroupId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::userIdOne, "UserIdOne", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelPresenceEvent::userIdTwo, "UserIdTwo", "")
                        ;
                }

                if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
                {
                    behaviorContext->Class<ChannelPresenceEvent>()
                        ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                        ->Property("channelId", BehaviorValueProperty(&ChannelPresenceEvent::channelId))
                        ->Property("joins", BehaviorValueProperty(&ChannelPresenceEvent::joins))
                        ->Property("leaves", BehaviorValueProperty(&ChannelPresenceEvent::leaves))
                        ->Property("roomName", BehaviorValueProperty(&ChannelPresenceEvent::roomName))
                        ->Property("groupId", BehaviorValueProperty(&ChannelPresenceEvent::groupId))
                        ->Property("userIdOne", BehaviorValueProperty(&ChannelPresenceEvent::userIdOne))
                        ->Property("userIdTwo", BehaviorValueProperty(&ChannelPresenceEvent::userIdTwo))
                        ;
                }
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<MatchmakerUser>("MatchmakerUser", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerUser::presence, "Presence", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerUser::stringProperties, "StringProperties", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerUser::numericProperties, "NumericProperties", "")
                        ;
                }
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MatchmakerUser>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("presence", BehaviorValueProperty(&MatchmakerUser::presence))
                    ->Property("stringProperties", BehaviorValueProperty(&MatchmakerUser::stringProperties))
                    ->Property("numericProperties", BehaviorValueProperty(&MatchmakerUser::numericProperties))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<MatchmakerMatched>("MatchmakerMatched", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerMatched::ticket, "Ticket", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerMatched::matchId, "MatchId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerMatched::token, "Token", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerMatched::users, "Users", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchmakerMatched::self, "Self", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MatchmakerMatched>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("ticket", BehaviorValueProperty(&MatchmakerMatched::ticket))
                    ->Property("matchId", BehaviorValueProperty(&MatchmakerMatched::matchId))
                    ->Property("token", BehaviorValueProperty(&MatchmakerMatched::token))
                    ->Property("users", BehaviorValueProperty(&MatchmakerMatched::users))
                    ->Property("self", BehaviorValueProperty(&MatchmakerMatched::self))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<MatchData>("MatchData", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchData::matchId, "MatchId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchData::presence, "Presence", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchData::opCode, "OpCode", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchData::data, "Data", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MatchData>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("matchId", BehaviorValueProperty(&MatchData::matchId))
                    ->Property("presence", BehaviorValueProperty(&MatchData::presence))
                    ->Property("opCode", BehaviorValueProperty(&MatchData::opCode))
                    ->Property("data", BehaviorValueProperty(&MatchData::data))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<MatchPresenceEvent>("MatchPresenceEvent", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchPresenceEvent::matchId, "MatchId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchPresenceEvent::joins, "Joins", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchPresenceEvent::leaves, "Leaves", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MatchPresenceEvent>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("matchId", BehaviorValueProperty(&MatchPresenceEvent::matchId))
                    ->Property("joins", BehaviorValueProperty(&MatchPresenceEvent::joins))
                    ->Property("leaves", BehaviorValueProperty(&MatchPresenceEvent::leaves))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Notification>("Notification", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::subject, "Subject", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::content, "Content", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::code, "Code", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::senderId, "SenderId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Notification::persistent, "Persistent", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Notification>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Notification::id))
                    ->Property("subject", BehaviorValueProperty(&Notification::subject))
                    ->Property("content", BehaviorValueProperty(&Notification::content))
                    ->Property("code", BehaviorValueProperty(&Notification::code))
                    ->Property("senderId", BehaviorValueProperty(&Notification::senderId))
                    ->Property("createTime", BehaviorValueProperty(&Notification::createTime))
                    ->Property("persistent", BehaviorValueProperty(&Notification::persistent))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<NotificationList>("NotificationList", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &NotificationList::notifications, "Notifications", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &NotificationList::cacheableCursor, "CacheableCursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<NotificationList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("notifications", BehaviorValueProperty(&NotificationList::notifications))
                    ->Property("cacheableCursor", BehaviorValueProperty(&NotificationList::cacheableCursor))
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

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Party>("Party", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::open, "Open", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::maxSize, "MaxSize", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::self, "Self", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::leader, "Leader", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Party::presences, "Presences", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Party>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Party::id))
                    ->Property("open", BehaviorValueProperty(&Party::open))
                    ->Property("maxSize", BehaviorValueProperty(&Party::maxSize))
                    ->Property("self", BehaviorValueProperty(&Party::self))
                    ->Property("leader", BehaviorValueProperty(&Party::leader))
                    ->Property("presences", BehaviorValueProperty(&Party::presences))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyClose>("PartyClose", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyClose::id, "Id", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyClose>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&PartyClose::id))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyData>("PartyData", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyData::partyId, "PartyId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyData::presence, "Presence", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyData::opCode, "OpCode", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyData::data, "Data", "")
                       ;
                }
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyData>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("partyId", BehaviorValueProperty(&PartyData::partyId))
                    ->Property("presence", BehaviorValueProperty(&PartyData::presence))
                    ->Property("opCode", BehaviorValueProperty(&PartyData::opCode))
                    ->Property("data", BehaviorValueProperty(&PartyData::data))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyJoinRequest>("PartyJoinRequest", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyJoinRequest::partyId, "PartyId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyJoinRequest::presences, "Presences", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyJoinRequest>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("partyId", BehaviorValueProperty(&PartyJoinRequest::partyId))
                    ->Property("presences", BehaviorValueProperty(&PartyJoinRequest::presences))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyLeader>("PartyLeader", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyLeader::partyId, "PartyId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyLeader::presence, "Presence", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyLeader>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("partyId", BehaviorValueProperty(&PartyLeader::partyId))
                    ->Property("presence", BehaviorValueProperty(&PartyLeader::presence))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyMatchmakerTicket>("PartyMatchmakerTicket", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyMatchmakerTicket::partyId, "PartyId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyMatchmakerTicket::ticket, "Ticket", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyMatchmakerTicket>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("partyId", BehaviorValueProperty(&PartyMatchmakerTicket::partyId))
                    ->Property("ticket", BehaviorValueProperty(&PartyMatchmakerTicket::ticket))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<PartyPresenceEvent>("PartyPresenceEvent", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyPresenceEvent::partyId, "PartyId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyPresenceEvent::joins, "Joins", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &PartyPresenceEvent::leaves, "Leaves", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<PartyPresenceEvent>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("partyId", BehaviorValueProperty(&PartyPresenceEvent::partyId))
                    ->Property("joins", BehaviorValueProperty(&PartyPresenceEvent::joins))
                    ->Property("leaves", BehaviorValueProperty(&PartyPresenceEvent::leaves))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StatusPresenceEvent>("StatusPresenceEvent", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StatusPresenceEvent::joins, "Joins", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StatusPresenceEvent::leaves, "Leaves", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StatusPresenceEvent>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("joins", BehaviorValueProperty(&StatusPresenceEvent::joins))
                    ->Property("leaves", BehaviorValueProperty(&StatusPresenceEvent::leaves))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Stream>("Stream", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Stream::mode, "Mode", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Stream::subject, "Subject", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Stream::subcontext, "Subcontext", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Stream::label, "Label", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Stream>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("mode", BehaviorValueProperty(&Stream::mode))
                    ->Property("subject", BehaviorValueProperty(&Stream::subject))
                    ->Property("subcontext", BehaviorValueProperty(&Stream::subcontext))
                    ->Property("label", BehaviorValueProperty(&Stream::label))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StreamPresenceEvent>("StreamPresenceEvent", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamPresenceEvent::stream, "Stream", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamPresenceEvent::joins, "Joins", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamPresenceEvent::leaves, "Leaves", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StreamPresenceEvent>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("stream", BehaviorValueProperty(&StreamPresenceEvent::stream))
                    ->Property("joins", BehaviorValueProperty(&StreamPresenceEvent::joins))
                    ->Property("leaves", BehaviorValueProperty(&StreamPresenceEvent::leaves))
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
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StreamData>("StreamData", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamData::stream, "Stream", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamData::sender, "Sender", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StreamData::data, "Data", "")
                        ;
                }
            }

            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StreamData>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("stream", BehaviorValueProperty(&StreamData::stream))
                    ->Property("sender", BehaviorValueProperty(&StreamData::sender))
                    ->Property("data", BehaviorValueProperty(&StreamData::data))
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

    /// The object to store.
    struct StorageObjectWrite
    {
        AZ_TYPE_INFO(StorageObjectWrite, "{59C7240F-3EFE-4752-B6DE-8A7B61BBE047}");
        AZ_CLASS_ALLOCATOR(StorageObjectWrite, AZ::SystemAllocator, 0);
        StorageObjectWrite()
            : collection(), key(), value(), version(), permissionRead(0), permissionWrite(0)
        {
        }
        AZStd::string collection;                                   ///< The collection which stores the object.
        AZStd::string key;                                          ///< The key of the object within the collection.
        AZStd::string value;                                        ///< The value of the object. Must be JSON
        AZStd::string version;                                      ///< The version hash of the object to check. Possible values are: ["", "*", "#hash#"].
        AZ::u8 permissionRead;     ///< The read access permissions for the object.
        AZ::u8 permissionWrite;   ///< The write access permissions for the object.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StorageObjectWrite>()
                    ->Version(1)
                    ->Field("collection", &StorageObjectWrite::collection)
                    ->Field("key", &StorageObjectWrite::key)
                    ->Field("value", &StorageObjectWrite::value)
                    ->Field("version", &StorageObjectWrite::version)
                    ->Field("permissionRead", &StorageObjectWrite::permissionRead)
                    ->Field("permissionWrite", &StorageObjectWrite::permissionWrite)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StorageObjectWrite>("StorageObjectWrite", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::collection, "Collection", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::key, "Key", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::value, "Value", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::version, "Version", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::permissionRead, "Permission Read", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectWrite::permissionWrite, "Permission Write", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StorageObjectWrite>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("collection", BehaviorValueProperty(&StorageObjectWrite::collection))
                    ->Property("key", BehaviorValueProperty(&StorageObjectWrite::key))
                    ->Property("value", BehaviorValueProperty(&StorageObjectWrite::value))
                    ->Property("version", BehaviorValueProperty(&StorageObjectWrite::version))
                    ->Property("permissionRead", BehaviorValueProperty(&StorageObjectWrite::permissionRead))
                    ->Property("permissionWrite", BehaviorValueProperty(&StorageObjectWrite::permissionWrite))
                    ;
            }
        }

        static StorageObjectWrite FromNakama(const Nakama::NStorageObjectWrite& nWrite)
        {
            StorageObjectWrite write;
            write.collection = nWrite.collection.c_str();
            write.key = nWrite.key.c_str();
            write.value = nWrite.value.c_str();
            write.version = nWrite.version.c_str();
            if (nWrite.permissionRead.has_value())
                write.permissionRead = static_cast<AZ::u8>(nWrite.permissionRead.value());
            if (nWrite.permissionWrite.has_value())
                write.permissionWrite = static_cast<AZ::u8>(nWrite.permissionWrite.value());
            return write;
        }

        static Nakama::NStorageObjectWrite ToNakama(const StorageObjectWrite& write)
        {
            Nakama::NStorageObjectWrite nWrite;
            nWrite.collection = write.collection.c_str();
            nWrite.key = write.key.c_str();
            nWrite.value = write.value.c_str();
            nWrite.version = write.version.c_str();
            nWrite.permissionRead = static_cast<Nakama::NStoragePermissionRead>(write.permissionRead);
            nWrite.permissionWrite = static_cast<Nakama::NStoragePermissionWrite>(write.permissionWrite);
            return nWrite;
        }
    };

    /// Storage objects to get.
    struct ReadStorageObjectId
    {
        AZ_TYPE_INFO(ReadStorageObjectId, "{BA24BE90-DA1E-44C5-A5F9-FB3601D7FE72}");
        AZ_CLASS_ALLOCATOR(ReadStorageObjectId, AZ::SystemAllocator, 0);
        ReadStorageObjectId()
            : collection(), key(), userId()
        {
        }
        AZStd::string collection;     ///< The collection which stores the object.
        AZStd::string key;            ///< The key of the object within the collection.
        AZStd::string userId;         ///< The user owner of the object.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<ReadStorageObjectId>()
                    ->Version(1)
                    ->Field("collection", &ReadStorageObjectId::collection)
                    ->Field("key", &ReadStorageObjectId::key)
                    ->Field("userId", &ReadStorageObjectId::userId)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<ReadStorageObjectId>("ReadStorageObjectId", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ReadStorageObjectId::collection, "Collection", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ReadStorageObjectId::key, "Key", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ReadStorageObjectId::userId, "User Id", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<ReadStorageObjectId>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("collection", BehaviorValueProperty(&ReadStorageObjectId::collection))
                    ->Property("key", BehaviorValueProperty(&ReadStorageObjectId::key))
                    ->Property("userId", BehaviorValueProperty(&ReadStorageObjectId::userId))
                    ;
            }
        }

        static ReadStorageObjectId FromNakama(const Nakama::NReadStorageObjectId& nRead)
        {
            ReadStorageObjectId read;
            read.collection = nRead.collection.c_str();
            read.key = nRead.key.c_str();
            read.userId = nRead.userId.c_str();
            return read;
        }

        static Nakama::NReadStorageObjectId ToNakama(const ReadStorageObjectId& read)
        {
            Nakama::NReadStorageObjectId nRead;
            nRead.collection = read.collection.c_str();
            nRead.key = read.key.c_str();
            nRead.userId = read.userId.c_str();
            return nRead;
        }
    };

    /// Storage objects to delete.
    struct DeleteStorageObjectId
    {
        AZ_TYPE_INFO(DeleteStorageObjectId, "{0DA77A94-EC4E-4314-8FE6-991D90908C38}");
        AZ_CLASS_ALLOCATOR(DeleteStorageObjectId, AZ::SystemAllocator, 0);
        DeleteStorageObjectId()
            : collection(), key(), version()
        {
        }
        AZStd::string collection;     ///< The collection which stores the object.
        AZStd::string key;            ///< The key of the object within the collection.
        AZStd::string version;        ///< The version hash of the object.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<DeleteStorageObjectId>()
                    ->Version(1)
                    ->Field("collection", &DeleteStorageObjectId::collection)
                    ->Field("key", &DeleteStorageObjectId::key)
                    ->Field("version", &DeleteStorageObjectId::version)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<DeleteStorageObjectId>("DeleteStorageObjectId", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &DeleteStorageObjectId::collection, "Collection", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &DeleteStorageObjectId::key, "Key", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &DeleteStorageObjectId::version, "Version", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<DeleteStorageObjectId>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("collection", BehaviorValueProperty(&DeleteStorageObjectId::collection))
                    ->Property("key", BehaviorValueProperty(&DeleteStorageObjectId::key))
                    ->Property("version", BehaviorValueProperty(&DeleteStorageObjectId::version))
                    ;
            }
        }

        static DeleteStorageObjectId FromNakama(const Nakama::NDeleteStorageObjectId& nDelete)
        {
            DeleteStorageObjectId del;
            del.collection = nDelete.collection.c_str();
            del.key = nDelete.key.c_str();
            del.version = nDelete.version.c_str();
            return del;
        }

        static Nakama::NDeleteStorageObjectId ToNakama(const DeleteStorageObjectId& del)
        {
            Nakama::NDeleteStorageObjectId nDel;
            nDel.collection = del.collection.c_str();
            nDel.key = del.key.c_str();
            nDel.version = del.version.c_str();
            return nDel;
        }
    };

    /// A user in the server.
    struct User
    {
        AZ_TYPE_INFO(User, "{8D9D25BB-CCDE-4F91-8B96-F6EBB8AB5212}");
        AZ_CLASS_ALLOCATOR(User, AZ::SystemAllocator, 0);
        User()
            : id(), username(), displayName(), avatarUrl(), lang(), location(), timeZone(), metadata(), facebookId(), googleId(), gameCenterId(), appleId(), steamId()
        {
        }
        AZStd::string id;            ///< The id of the user's account.
        AZStd::string username;      ///< The username of the user's account.
        AZStd::string displayName;   ///< The display name of the user.
        AZStd::string avatarUrl;     ///< A URL for an avatar image.
        AZStd::string lang;          ///< The language expected to be a tag which follows the BCP-47 spec.
        AZStd::string location;      ///< The location set by the user.
        AZStd::string timeZone;      ///< The timezone set by the user.
        AZStd::string metadata;      ///< Additional information stored as a JSON object.
        AZStd::string facebookId;    ///< The Facebook id in the user's account.
        AZStd::string googleId;      ///< The Google id in the user's account.
        AZStd::string gameCenterId;  ///< The Apple Game Center in of the user's account.
        AZStd::string appleId;       ///< The Apple Sign In ID in the user's account.
        AZStd::string steamId;       ///< The Steam id in the user's account.
        bool online;       ///< Indicates whether the user is currently online.
        AZ::s32 edgeCount = 0;     ///< Number of related edges to this user (friends).
        AZ::u64 createdAt = 0;  ///< The UNIX time when the user was created.
        AZ::u64 updatedAt = 0;  ///< The UNIX time when the user was last updated.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<User>()
                    ->Version(1)
                    ->Field("id", &User::id)
                    ->Field("username", &User::username)
                    ->Field("displayName", &User::displayName)
                    ->Field("avatarUrl", &User::avatarUrl)
                    ->Field("lang", &User::lang)
                    ->Field("location", &User::location)
                    ->Field("timeZone", &User::timeZone)
                    ->Field("metadata", &User::metadata)
                    ->Field("facebookId", &User::facebookId)
                    ->Field("googleId", &User::googleId)
                    ->Field("gameCenterId", &User::gameCenterId)
                    ->Field("appleId", &User::appleId)
                    ->Field("steamId", &User::steamId)
                    ->Field("online", &User::online)
                    ->Field("edgeCount", &User::edgeCount)
                    ->Field("createdAt", &User::createdAt)
                    ->Field("updatedAt", &User::updatedAt)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<User>("User", "Description")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::username, "Username", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::displayName, "Display Name", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::avatarUrl, "Avatar URL", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::lang, "Lang", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::location, "Location", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::timeZone, "Time Zone", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::metadata, "Metadata", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::facebookId, "Facebook Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::googleId, "Google Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::gameCenterId, "Game Center Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default,&User::appleId, "Apple Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::steamId, "Steam Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::online, "Online", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::edgeCount, "Edge Count", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::createdAt, "Created At", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &User::updatedAt, "Updated At", "")
                        ;
                }
                if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
                {
                    behaviorContext->Class<User>()
                        ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                        ->Property("id", BehaviorValueProperty(&User::id))
                        ->Property("username", BehaviorValueProperty(&User::username))
                        ->Property("displayName", BehaviorValueProperty(&User::displayName))
                        ->Property("avatarUrl", BehaviorValueProperty(&User::avatarUrl))
                        ->Property("lang", BehaviorValueProperty(&User::lang))
                        ->Property("location", BehaviorValueProperty(&User::location))
                        ->Property("timeZone", BehaviorValueProperty(&User::timeZone))
                        ->Property("metadata", BehaviorValueProperty(&User::metadata))
                        ->Property("facebookId", BehaviorValueProperty(&User::facebookId))
                        ->Property("googleId", BehaviorValueProperty(&User::googleId))
                        ->Property("gameCenterId", BehaviorValueProperty(&User::gameCenterId))
                        ->Property("appleId", BehaviorValueProperty(&User::appleId))
                        ->Property("steamId", BehaviorValueProperty(&User::steamId))
                        ->Property("online", BehaviorValueProperty(&User::online))
                        ->Property("edgeCount", BehaviorValueProperty(&User::edgeCount))
                        ->Property("createdAt", BehaviorValueProperty(&User::createdAt))
                        ->Property("updatedAt", BehaviorValueProperty(&User::updatedAt))
                        ;
                }
            }
        }

        static User FromNakama(const Nakama::NUser& nUser)
        {
            User user;
            user.id = nUser.id.c_str();
            user.username = nUser.username.c_str();
            user.displayName = nUser.displayName.c_str();
            user.avatarUrl = nUser.avatarUrl.c_str();
            user.lang = nUser.lang.c_str();
            user.location = nUser.location.c_str();
            user.timeZone = nUser.timeZone.c_str();
            user.metadata = nUser.metadata.c_str();
            user.facebookId = nUser.facebookId.c_str();
            user.googleId = nUser.googleId.c_str();
            user.gameCenterId = nUser.gameCenterId.c_str();
            user.appleId = nUser.appleId.c_str();
            user.steamId = nUser.steamId.c_str();
            user.online = nUser.online;
            user.edgeCount = nUser.edgeCount;
            user.createdAt = nUser.createdAt;
            user.updatedAt = nUser.updatedAt;
            return user;
        }

        static Nakama::NUser ToNakama(const User& user)
        {
            Nakama::NUser nUser;
            nUser.id = user.id.c_str();
            nUser.username = user.username.c_str();
            nUser.displayName = user.displayName.c_str();
            nUser.avatarUrl = user.avatarUrl.c_str();
            nUser.lang = user.lang.c_str();
            nUser.location = user.location.c_str();
            nUser.timeZone = user.timeZone.c_str();
            nUser.metadata = user.metadata.c_str();
            nUser.facebookId = user.facebookId.c_str();
            nUser.googleId = user.googleId.c_str();
            nUser.gameCenterId = user.gameCenterId.c_str();
            nUser.appleId = user.appleId.c_str();
            nUser.steamId = user.steamId.c_str();
            nUser.online = user.online;
            nUser.edgeCount = user.edgeCount;
            nUser.createdAt = user.createdAt;
            nUser.updatedAt = user.updatedAt;
            return nUser;
        }
    };

    /// Used with authenticate/link/unlink and user.
    struct AccountDevice
    {
        AZ_TYPE_INFO(AccountDevice, "{4690FB29-B638-46CC-909D-AABE77CC5A57}");
        AZ_CLASS_ALLOCATOR(AccountDevice, AZ::SystemAllocator, 0);
        AccountDevice()
            : id(), vars()
        {
        }

        AZStd::string id;   ///< A device identifier. Should be obtained by a platform-specific device API.
        AZStringMap vars;  ///< Extra information that will be bundled in the session token.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<AccountDevice>()
                    ->Version(0)
                    ->Field("id", &AccountDevice::id)
                    ->Field("vars", &AccountDevice::vars)
                    ;
                if(auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<AccountDevice>("AccountDevice", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &AccountDevice::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &AccountDevice::vars, "Vars", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<AccountDevice>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&AccountDevice::id))
                    ->Property("vars", BehaviorValueProperty(&AccountDevice::vars))
                    ;
            }
        }

        static AccountDevice FromNakama(const Nakama::NAccountDevice& nDevice)
        {
            AccountDevice device;
            device.id = nDevice.id.c_str();
            if (nDevice.vars.size() != 0)
            {
                for (const auto& var : nDevice.vars)
                {
                    device.vars.push_back({ var.first.c_str(),var.second.c_str() });
                }
            }
            return device;
        }

        static Nakama::NAccountDevice ToNakama(const AccountDevice& device)
        {
            Nakama::NAccountDevice nDevice;
            nDevice.id = device.id.c_str();
            if (device.vars.size() != 0)
            {
                for (const auto& var : device.vars)
                {
                    nDevice.vars[var.first.c_str()] = var.second.c_str();
                }
            }
            return nDevice;
        }
    };

    /// A user with additional account details. Always the current user.
    struct Account 
    {
        AZ_TYPE_INFO(Account, "{417061FC-291E-4DE6-8696-2DBD68DDB8C6}");
        AZ_CLASS_ALLOCATOR(Account, AZ::SystemAllocator, 0);
        Account()
            : user(), wallet(), email(), devices(), customId(), verifyTime(), disableTime()
        {
        }

        User user;                                ///< The user object.
        AZStd::string wallet;                        ///< The user's wallet data.
        AZStd::string email;                         ///< The email address of the user.
        AZStd::vector<AccountDevice> devices;       ///< The devices which belong to the user's account.
        AZStd::string customId;                      ///< The custom id in the user's account.
        AZ::u64 verifyTime = 0;                 ///< The UNIX time when the user's email was verified.
        AZ::u64 disableTime = 0;                ///< The UNIX time when the user's account was disabled/banned.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Account>()
                    ->Version(0)
                    ->Field("user", &Account::user)
                    ->Field("wallet", &Account::wallet)
                    ->Field("email", &Account::email)
                    ->Field("devices", &Account::devices)
                    ->Field("customId", &Account::customId)
                    ->Field("verifyTime", &Account::verifyTime)
                    ->Field("disableTime", &Account::disableTime)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Account>("Account", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::user, "User", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::wallet, "Wallet", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::email, "Email", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::devices, "Devices","")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::customId, "CustomId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::verifyTime, "VerifyTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Account::disableTime, "DisableTime", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Account>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("user", BehaviorValueProperty(&Account::user))
                    ->Property("wallet", BehaviorValueProperty(&Account::wallet))
                    ->Property("email", BehaviorValueProperty(&Account::email))
                    ->Property("devices", BehaviorValueProperty(&Account::devices))
                    ->Property("customId", BehaviorValueProperty(&Account::customId))
                    ->Property("verifyTime", BehaviorValueProperty(&Account::verifyTime))
                    ->Property("disableTime", BehaviorValueProperty(&Account::disableTime))
                    ;
            }
        }

        static Account FromNakama(const Nakama::NAccount& nAccount)
        {
            Account account;
            account.user = User::FromNakama(nAccount.user);
            account.wallet = nAccount.wallet.c_str();
            account.email = nAccount.email.c_str();
            if (nAccount.devices.size() != 0)
            {
                for (const auto& device : nAccount.devices)
                {
                    account.devices.push_back(AccountDevice::FromNakama(device));
                }
            }
            account.customId = nAccount.customId.c_str();
            account.verifyTime = nAccount.verifyTime;
            account.disableTime = nAccount.disableTime;
            return account;
        }

        static Nakama::NAccount ToNakama(const Account& account)
        {
            Nakama::NAccount nAccount;
            nAccount.user = User::ToNakama(account.user);
            nAccount.wallet = account.wallet.c_str();
            nAccount.email = account.email.c_str();
            if (account.devices.size() != 0)
            {
                for (const auto& device : account.devices)
                {
                    nAccount.devices.push_back(AccountDevice::ToNakama(device));
                }
            }
            nAccount.customId = account.customId.c_str();
            nAccount.verifyTime = account.verifyTime;
            nAccount.disableTime = account.disableTime;
            return nAccount;
        }
    };

    /// A friend of a user.
    struct Friend
    {
        AZ_TYPE_INFO(Friend, "{5A96ACE4-CF91-43A3-93AA-622ABA5D20AB}");
        AZ_CLASS_ALLOCATOR(Friend, AZ::SystemAllocator, 0);
        Friend()
            : user(), state(), updateTime()
        {
        }

        User user;                           ///< The user object.
        AZ::u8 state;                          ///< The friend status.
        AZ::u64 updateTime = 0;            ///< Time of the latest relationship update.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Friend>()
                    ->Version(0)
                    ->Field("user", &Friend::user)
                    ->Field("state", &Friend::state)
                    ->Field("updateTime", &Friend::updateTime)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Friend>("Friend", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Friend::user, "User", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Friend::state, "State", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Friend::updateTime, "UpdateTime", "")
                        ;
                }                
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Friend>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("user", BehaviorValueProperty(&Friend::user))
                    ->Property("state", BehaviorValueProperty(&Friend::state))
                    ->Property("updateTime", BehaviorValueProperty(&Friend::updateTime))
                    ;
            }
        }

        static Friend FromNakama(const Nakama::NFriend& nFriend)
        {
            Friend friend_;
            friend_.user = User::FromNakama(nFriend.user);
            friend_.state = static_cast<AZ::u8>(nFriend.state);
            friend_.updateTime = nFriend.updateTime;
            return friend_;
        }

        static Nakama::NFriend ToNakama(const Friend& friend_)
        {
            Nakama::NFriend nFriend;
            nFriend.user = User::ToNakama(friend_.user);
            nFriend.state = static_cast<Nakama::NFriend::State>(friend_.state);
            nFriend.updateTime = friend_.updateTime;
            return nFriend;
        }
    };

    ///< A collection of zero or more friends of the user.
    struct FriendList
    {
        AZ_TYPE_INFO(FriendList, "{6F5C5929-6805-479D-8824-124AD64EEB3F}");
        AZ_CLASS_ALLOCATOR(FriendList, AZ::SystemAllocator, 0);
        FriendList()
            : friends(), cursor()
        {
        }

        AZStd::vector<Friend> friends;     ///< The Friend objects.
        AZStd::string cursor;               ///< Cursor for the next page of results, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<FriendList>()
                    ->Version(0)
                    ->Field("friends", &FriendList::friends)
                    ->Field("cursor", &FriendList::cursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<FriendList>("FriendList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &FriendList::friends, "Friends", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &FriendList::cursor, "Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<FriendList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("friends", BehaviorValueProperty(&FriendList::friends))
                    ->Property("cursor", BehaviorValueProperty(&FriendList::cursor))
                    ;
            }
        }

        static FriendList FromNakama(const Nakama::NFriendList& nFriendList)
        {
            FriendList friendList;
            if (nFriendList.friends.size() != 0)
            {
                for (const auto& friend_ : nFriendList.friends)
                {
                    friendList.friends.push_back(Friend::FromNakama(friend_));
                }
            }
            friendList.cursor = nFriendList.cursor.c_str();
            return friendList;
        }

        static Nakama::NFriendList ToNakama(const FriendList& friendList)
        {
            Nakama::NFriendList nFriendList;
            if (friendList.friends.size() != 0)
            {
                for (const auto& friend_ : friendList.friends)
                {
                    nFriendList.friends.push_back(Friend::ToNakama(friend_));
                }
            }
            nFriendList.cursor = friendList.cursor.c_str();
            return nFriendList;
        }
    };

    /// A group in the server.
    struct Group
    {
        AZ_TYPE_INFO(Group, "{3931BDEB-2696-4AD3-9BA6-E72DF9AF2C94}");
        AZ_CLASS_ALLOCATOR(Group, AZ::SystemAllocator, 0);
        Group()
            : id(), creatorId(), name(), description(), lang(), metadata(), avatarUrl(), open(), edgeCount(), maxCount(), createTime(), updateTime()
        {
        }

        AZStd::string id;              ///< The id of a group.
        AZStd::string creatorId;       ///< The id of the user who created the group.
        AZStd::string name;            ///< The unique name of the group.
        AZStd::string description;     ///< A description for the group.
        AZStd::string lang;            ///< The language expected to be a tag which follows the BCP-47 spec.
        AZStd::string metadata;        ///< Additional information stored as a JSON object.
        AZStd::string avatarUrl;       ///< A URL for an avatar image.
        bool open = false;           ///< Anyone can join open groups, otherwise only admins can accept members.
        AZ::s32 edgeCount = 0;       ///< The current count of all members in the group.
        AZ::s32 maxCount = 0;        ///< The maximum number of members allowed.
        AZ::u64 createTime = 0;   ///< The UNIX time when the group was created.
        AZ::u64 updateTime = 0;   ///< The UNIX time when the group was last updated.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Group>()
                    ->Version(0)
                    ->Field("id", &Group::id)
                    ->Field("creatorId", &Group::creatorId)
                    ->Field("name", &Group::name)
                    ->Field("description", &Group::description)
                    ->Field("lang", &Group::lang)
                    ->Field("metadata", &Group::metadata)
                    ->Field("avatarUrl", &Group::avatarUrl)
                    ->Field("open", &Group::open)
                    ->Field("edgeCount", &Group::edgeCount)
                    ->Field("maxCount", &Group::maxCount)
                    ->Field("createTime", &Group::createTime)
                    ->Field("updateTime", &Group::updateTime)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Group>("Group", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::creatorId, "CreatorId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::name, "Name", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::description, "Description", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::lang, "Lang", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::metadata, "Metadata", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::avatarUrl, "AvatarUrl", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::open, "Open", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::edgeCount, "EdgeCount", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::maxCount, "MaxCount", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Group::updateTime, "UpdateTime", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Group>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Group::id))
                    ->Property("creatorId", BehaviorValueProperty(&Group::creatorId))
                    ->Property("name", BehaviorValueProperty(&Group::name))
                    ->Property("description", BehaviorValueProperty(&Group::description))
                    ->Property("lang", BehaviorValueProperty(&Group::lang))
                    ->Property("metadata", BehaviorValueProperty(&Group::metadata))
                    ->Property("avatarUrl", BehaviorValueProperty(&Group::avatarUrl))
                    ->Property("open", BehaviorValueProperty(&Group::open))
                    ->Property("edgeCount", BehaviorValueProperty(&Group::edgeCount))
                    ->Property("maxCount", BehaviorValueProperty(&Group::maxCount))
                    ->Property("createTime", BehaviorValueProperty(&Group::createTime))
                    ->Property("updateTime", BehaviorValueProperty(&Group::updateTime))
                    ;
            }
        }

        static Group FromNakama(const Nakama::NGroup& nGroup)
        {
            Group group;
            group.id = nGroup.id.c_str();
            group.creatorId = nGroup.creatorId.c_str();
            group.name = nGroup.name.c_str();
            group.description = nGroup.description.c_str();
            group.lang = nGroup.lang.c_str();
            group.metadata = nGroup.metadata.c_str();
            group.avatarUrl = nGroup.avatarUrl.c_str();
            group.open = nGroup.open;
            group.edgeCount = nGroup.edgeCount;
            group.maxCount = nGroup.maxCount;
            group.createTime = nGroup.createTime;
            group.updateTime = nGroup.updateTime;
            return group;
        }

        static Nakama::NGroup ToNakama(const Group& group)
        {
            Nakama::NGroup nGroup;
            nGroup.id = group.id.c_str();
            nGroup.creatorId = group.creatorId.c_str();
            nGroup.name = group.name.c_str();
            nGroup.description = group.description.c_str();
            nGroup.lang = group.lang.c_str();
            nGroup.metadata = group.metadata.c_str();
            nGroup.avatarUrl = group.avatarUrl.c_str();
            nGroup.open = group.open;
            nGroup.edgeCount = group.edgeCount;
            nGroup.maxCount = group.maxCount;
            nGroup.createTime = group.createTime;
            nGroup.updateTime = group.updateTime;
            return nGroup;
        }
    };

    /// A single user-role pair.
    struct GroupUser
    {
        AZ_TYPE_INFO(GroupUser, "{9DC435A9-D492-4D68-B1A4-42885C3528A8}");
        AZ_CLASS_ALLOCATOR(GroupUser, AZ::SystemAllocator, 0);
        GroupUser()
            : user()
            , state(0)
        {
        }

        User user;            ///< User.
        AZ::u8 state; ///< Their relationship to the group.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<GroupUser>()
                    ->Version(0)
                    ->Field("user", &GroupUser::user)
                    ->Field("state", &GroupUser::state)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<GroupUser>("GroupUser", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupUser::user, "User", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupUser::state, "State", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<GroupUser>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("user", BehaviorValueProperty(&GroupUser::user))
                    ->Property("state", BehaviorValueProperty(&GroupUser::state))
                    ;
            }
        }

        static GroupUser FromNakama(const Nakama::NGroupUser& nGroupUser)
        {
            GroupUser groupUser;
            groupUser.user = User::FromNakama(nGroupUser.user);
            groupUser.state = static_cast<AZ::u8>(nGroupUser.state);
            return groupUser;
        }

        static Nakama::NGroupUser ToNakama(const GroupUser& groupUser)
        {
            Nakama::NGroupUser nGroupUser;
            nGroupUser.user = User::ToNakama(groupUser.user);
            nGroupUser.state = static_cast<Nakama::NUserGroupState>(groupUser.state);
            return nGroupUser;
        }
    };

    /// A list of users belonging to a group, along with their role.
    struct GroupUserList
    {
        AZ_TYPE_INFO(GroupUserList, "{CE7A9896-460A-4F3F-AAA4-2742DB483F2D}");
        AZ_CLASS_ALLOCATOR(GroupUserList, AZ::SystemAllocator, 0);
        GroupUserList()
            : groupUsers()
            , cursor()
        {
        }

        AZStd::vector<GroupUser> groupUsers;    ///< User-role pairs for a group.
        AZStd::string cursor;                    ///< Cursor for the next page of results, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<GroupUserList>()
                    ->Version(0)
                    ->Field("groupUsers", &GroupUserList::groupUsers)
                    ->Field("cursor", &GroupUserList::cursor)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<GroupUserList>("GroupUserList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupUserList::groupUsers, "GroupUsers", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupUserList::cursor, "Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<GroupUserList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("groupUsers", BehaviorValueProperty(&GroupUserList::groupUsers))
                    ->Property("cursor", BehaviorValueProperty(&GroupUserList::cursor))
                    ;
            }
        }

        static GroupUserList FromNakama(const Nakama::NGroupUserList& nGroupUserList)
        {
            GroupUserList groupUserList;
            if (nGroupUserList.groupUsers.size() != 0)
            {
                for (const auto& groupUser : nGroupUserList.groupUsers)
                {
                    groupUserList.groupUsers.push_back(GroupUser::FromNakama(groupUser));
                }
            }
            groupUserList.cursor = nGroupUserList.cursor.c_str();
            return groupUserList;
        }

        static Nakama::NGroupUserList ToNakama(const GroupUserList& groupUserList)
        {
            Nakama::NGroupUserList nGroupUserList;
            if (groupUserList.groupUsers.size() != 0)
            {
                for (const auto& groupUser : groupUserList.groupUsers)
                {
                    nGroupUserList.groupUsers.push_back(GroupUser::ToNakama(groupUser));
                }
            }
            nGroupUserList.cursor = groupUserList.cursor.c_str();
            return nGroupUserList;
        }
    };

    /// One or more groups returned from a listing operation.
    struct GroupList
    {
        AZ_TYPE_INFO(GroupList, "{CBB4338A-E94C-4E9B-8790-230DFECE8713}");
        AZ_CLASS_ALLOCATOR(GroupList, AZ::SystemAllocator, 0);
        GroupList()
            : groups()
            , cursor()
        {
        }

        AZStd::vector<Group> groups;   ///< One or more groups.
        AZStd::string cursor;           ///< A cursor used to get the next page.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<GroupList>()
                    ->Version(0)
                    ->Field("groups", &GroupList::groups)
                    ->Field("cursor", &GroupList::cursor)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<GroupList>("GroupList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupList::groups, "Groups", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &GroupList::cursor, "Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<GroupList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("groups", BehaviorValueProperty(&GroupList::groups))
                    ->Property("cursor", BehaviorValueProperty(&GroupList::cursor))
                    ;
            }
        }

        static GroupList FromNakama(const Nakama::NGroupList& nGroupList)
        {
            GroupList groupList;
            if (nGroupList.groups.size() != 0)
            {
                for (const auto& group : nGroupList.groups)
                {
                    groupList.groups.push_back(Group::FromNakama(group));
                }
            }
            groupList.cursor = nGroupList.cursor.c_str();
            return groupList;
        }

        static Nakama::NGroupList ToNakama(const GroupList& groupList)
        {
            Nakama::NGroupList nGroupList;
            if (groupList.groups.size() != 0)
            {
                for (const auto& group : groupList.groups)
                {
                    nGroupList.groups.push_back(Group::ToNakama(group));
                }
            }
            nGroupList.cursor = groupList.cursor.c_str();
            return nGroupList;
        }
    };

    /// A single group-role pair.
    struct UserGroup
    {
        AZ_TYPE_INFO(UserGroup, "{0E9F93A1-3E3D-459F-8483-9FD7CA0EFEC3}");
        AZ_CLASS_ALLOCATOR(UserGroup, AZ::SystemAllocator, 0);
        UserGroup()
            : group()
            , state(0)
        {
        }

        Group group;          ///< Group.
        AZ::u8 state; ///< The user's relationship to the group.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<UserGroup>()
                    ->Version(0)
                    ->Field("group", &UserGroup::group)
                    ->Field("state", &UserGroup::state)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<UserGroup>("UserGroup", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserGroup::group, "Group", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserGroup::state, "State", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<UserGroup>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("group", BehaviorValueProperty(&UserGroup::group))
                    ->Property("state", BehaviorValueProperty(&UserGroup::state))
                    ;
            }
        }

        static UserGroup FromNakama(const Nakama::NUserGroup& nUserGroup)
        {
            UserGroup userGroup;
            userGroup.group = Group::FromNakama(nUserGroup.group);
            userGroup.state = static_cast<AZ::u8>(nUserGroup.state);
            return userGroup;
        }

        static Nakama::NUserGroup ToNakama(const UserGroup& userGroup)
        {
            Nakama::NUserGroup nUserGroup;
            nUserGroup.group = Group::ToNakama(userGroup.group);
            nUserGroup.state = static_cast<Nakama::NUserGroupState>(userGroup.state);
            return nUserGroup;
        }
    };

    /// A list of groups belonging to a user, along with the user's role in each group.
    struct UserGroupList
    {
        AZ_TYPE_INFO(UserGroupList, "{F1C03091-35DF-439B-AD9F-129319BE1448}");
        AZ_CLASS_ALLOCATOR(UserGroupList, AZ::SystemAllocator, 0);
        UserGroupList()
            : userGroups()
            , cursor()
        {
        }
        AZStd::vector<UserGroup> userGroups;     ///< Group-role pairs for a user.
        AZStd::string cursor;                     ///< Cursor for the next page of results, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<UserGroupList>()
                    ->Version(0)
                    ->Field("userGroups", &UserGroupList::userGroups)
                    ->Field("cursor", &UserGroupList::cursor)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<UserGroupList>("UserGroupList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserGroupList::userGroups, "UserGroups", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &UserGroupList::cursor, "Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<UserGroupList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("userGroups", BehaviorValueProperty(&UserGroupList::userGroups))
                    ->Property("cursor", BehaviorValueProperty(&UserGroupList::cursor))
                    ;
            }
        }

        static UserGroupList FromNakama(const Nakama::NUserGroupList& nUserGroupList)
        {
            UserGroupList userGroupList;
            if (nUserGroupList.userGroups.size() != 0)
            {
                for (const auto& userGroup : nUserGroupList.userGroups)
                {
                    userGroupList.userGroups.push_back(UserGroup::FromNakama(userGroup));
                }
            }
            userGroupList.cursor = nUserGroupList.cursor.c_str();
            return userGroupList;
        }

        static Nakama::NUserGroupList ToNakama(const UserGroupList& userGroupList)
        {
            Nakama::NUserGroupList nUserGroupList;
            if (userGroupList.userGroups.size() != 0)
            {
                for (const auto& userGroup : userGroupList.userGroups)
                {
                    nUserGroupList.userGroups.push_back(UserGroup::ToNakama(userGroup));
                }
            }
            nUserGroupList.cursor = userGroupList.cursor.c_str();
            return nUserGroupList;
        }
    };

    /// Represents a complete leaderboard record with all scores and associated metadata.
    struct LeaderboardRecord
    {
        AZ_TYPE_INFO(LeaderboardRecord, "{A2959958-B000-4711-A471-E5596AAB3E3B}");
        AZ_CLASS_ALLOCATOR(LeaderboardRecord, AZ::SystemAllocator, 0);
        LeaderboardRecord()
            : leaderboardId(), ownerId(), username(), score(), subscore(), numScore(), maxNumScore(), metadata(), createTime(), updateTime(), expiryTime(), rank()
        {
        }

        AZStd::string leaderboardId;      ///< The ID of the leaderboard this score belongs to.
        AZStd::string ownerId;            ///< The ID of the score owner, usually a user or group.
        AZStd::string username;           ///< The username of the score owner, if the owner is a user.
        AZ::s64 score = 0;              ///< The score value.
        AZ::s64 subscore = 0;           ///< An optional subscore value.
        AZ::s32 numScore = 0;           ///< The number of submissions to this score record.
        AZ::u32 maxNumScore = 0;       ///< The maximum number of score updates allowed by the owner.
        AZStd::string metadata;           ///< Metadata.
        AZ::u64 createTime = 0;      ///< The UNIX time when the leaderboard record was created.
        AZ::u64 updateTime = 0;      ///< The UNIX time when the leaderboard record was updated.
        AZ::u64 expiryTime = 0;      ///< The UNIX time when the leaderboard record expires.
        AZ::s64 rank = 0;               ///< The rank of this record.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<LeaderboardRecord>()
                    ->Version(0)
                    ->Field("leaderboardId", &LeaderboardRecord::leaderboardId)
                    ->Field("ownerId", &LeaderboardRecord::ownerId)
                    ->Field("username", &LeaderboardRecord::username)
                    ->Field("score", &LeaderboardRecord::score)
                    ->Field("subscore", &LeaderboardRecord::subscore)
                    ->Field("numScore", &LeaderboardRecord::numScore)
                    ->Field("maxNumScore", &LeaderboardRecord::maxNumScore)
                    ->Field("metadata", &LeaderboardRecord::metadata)
                    ->Field("createTime", &LeaderboardRecord::createTime)
                    ->Field("updateTime", &LeaderboardRecord::updateTime)
                    ->Field("expiryTime", &LeaderboardRecord::expiryTime)
                    ->Field("rank", &LeaderboardRecord::rank)
                    ;

                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<LeaderboardRecord>("LeaderboardRecord", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::leaderboardId, "LeaderboardId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::ownerId, "OwnerId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::username, "Username", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::score, "Score", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::subscore, "Subscore", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::numScore, "NumScore", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::maxNumScore, "MaxNumScore", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::metadata, "Metadata", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::updateTime, "UpdateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::expiryTime, "ExpiryTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecord::rank, "Rank", "")
                        ;
                }           
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<LeaderboardRecord>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("leaderboardId", BehaviorValueProperty(&LeaderboardRecord::leaderboardId))
                    ->Property("ownerId", BehaviorValueProperty(&LeaderboardRecord::ownerId))
                    ->Property("username", BehaviorValueProperty(&LeaderboardRecord::username))
                    ->Property("score", BehaviorValueProperty(&LeaderboardRecord::score))
                    ->Property("subscore", BehaviorValueProperty(&LeaderboardRecord::subscore))
                    ->Property("numScore", BehaviorValueProperty(&LeaderboardRecord::numScore))
                    ->Property("maxNumScore", BehaviorValueProperty(&LeaderboardRecord::maxNumScore))
                    ->Property("metadata", BehaviorValueProperty(&LeaderboardRecord::metadata))
                    ->Property("createTime", BehaviorValueProperty(&LeaderboardRecord::createTime))
                    ->Property("updateTime", BehaviorValueProperty(&LeaderboardRecord::updateTime))
                    ->Property("expiryTime", BehaviorValueProperty(&LeaderboardRecord::expiryTime))
                    ->Property("rank", BehaviorValueProperty(&LeaderboardRecord::rank))
                    ;
            }
        }

        static LeaderboardRecord FromNakama(const Nakama::NLeaderboardRecord& nLeaderboardRecord)
        {
            LeaderboardRecord leaderboardRecord;
            leaderboardRecord.leaderboardId = nLeaderboardRecord.leaderboardId.c_str();
            leaderboardRecord.ownerId = nLeaderboardRecord.ownerId.c_str();
            leaderboardRecord.username = nLeaderboardRecord.username.c_str();
            leaderboardRecord.score = nLeaderboardRecord.score;
            leaderboardRecord.subscore = nLeaderboardRecord.subscore;
            leaderboardRecord.numScore = nLeaderboardRecord.numScore;
            leaderboardRecord.maxNumScore = nLeaderboardRecord.maxNumScore;
            leaderboardRecord.metadata = nLeaderboardRecord.metadata.c_str();
            leaderboardRecord.createTime = nLeaderboardRecord.createTime;
            leaderboardRecord.updateTime = nLeaderboardRecord.updateTime;
            leaderboardRecord.expiryTime = nLeaderboardRecord.expiryTime;
            leaderboardRecord.rank = nLeaderboardRecord.rank;
            return leaderboardRecord;
        }
        static Nakama::NLeaderboardRecord ToNakama(const LeaderboardRecord& leaderboardRecord)
        {
            Nakama::NLeaderboardRecord nLeaderboardRecord;
            nLeaderboardRecord.leaderboardId = leaderboardRecord.leaderboardId.c_str();
            nLeaderboardRecord.ownerId = leaderboardRecord.ownerId.c_str();
            nLeaderboardRecord.username = leaderboardRecord.username.c_str();
            nLeaderboardRecord.score = leaderboardRecord.score;
            nLeaderboardRecord.subscore = leaderboardRecord.subscore;
            nLeaderboardRecord.numScore = leaderboardRecord.numScore;
            nLeaderboardRecord.maxNumScore = leaderboardRecord.maxNumScore;
            nLeaderboardRecord.metadata = leaderboardRecord.metadata.c_str();
            nLeaderboardRecord.createTime = leaderboardRecord.createTime;
            nLeaderboardRecord.updateTime = leaderboardRecord.updateTime;
            nLeaderboardRecord.expiryTime = leaderboardRecord.expiryTime;
            nLeaderboardRecord.rank = leaderboardRecord.rank;
            return nLeaderboardRecord;
        }
    };

    /// A set of leaderboard records, may be part of a leaderboard records page or a batch of individual records.
    struct LeaderboardRecordList
    {
        AZ_TYPE_INFO(LeaderboardRecordList, "{3122D922-B564-48E5-A6E8-A9829CA1A6D0}");
        AZ_CLASS_ALLOCATOR(LeaderboardRecordList, AZ::SystemAllocator, 0);
        LeaderboardRecordList()
            : records{}, ownerRecords{}, nextCursor{}, prevCursor{}
        {
        }
        AZStd::vector<LeaderboardRecord> records;           ///< A list of leaderboard records.
        AZStd::vector<LeaderboardRecord> ownerRecords;      ///< A batched set of leaderboard records belonging to specified owners.
        AZStd::string nextCursor;                            ///< The cursor to send when retrieving the next page, if any.
        AZStd::string prevCursor;                            ///< The cursor to send when retrieving the previous page, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<LeaderboardRecordList>()
                    ->Version(0)
                    ->Field("records", &LeaderboardRecordList::records)
                    ->Field("ownerRecords", &LeaderboardRecordList::ownerRecords)
                    ->Field("nextCursor", &LeaderboardRecordList::nextCursor)
                    ->Field("prevCursor", &LeaderboardRecordList::prevCursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<LeaderboardRecordList>("LeaderboardRecordList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecordList::records)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecordList::ownerRecords)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecordList::nextCursor)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &LeaderboardRecordList::prevCursor)
                        ;                        
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<LeaderboardRecordList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("records", BehaviorValueProperty(&LeaderboardRecordList::records))
                    ->Property("ownerRecords", BehaviorValueProperty(&LeaderboardRecordList::ownerRecords))
                    ->Property("nextCursor", BehaviorValueProperty(&LeaderboardRecordList::nextCursor))
                    ->Property("prevCursor", BehaviorValueProperty(&LeaderboardRecordList::prevCursor))
                    ;
            }
        }

        static LeaderboardRecordList FromNakama(const Nakama::NLeaderboardRecordList& nLeaderboardRecordList)
        {
            LeaderboardRecordList leaderboardRecordList;
            if (nLeaderboardRecordList.records.size() != 0)
            {
                for (const auto& leaderboardRecord : nLeaderboardRecordList.records)
                {
                    leaderboardRecordList.records.push_back(LeaderboardRecord::FromNakama(leaderboardRecord));
                }
            }
            if (nLeaderboardRecordList.ownerRecords.size() != 0)
            {
                for (const auto& leaderboardRecord : nLeaderboardRecordList.ownerRecords)
                {
                    leaderboardRecordList.ownerRecords.push_back(LeaderboardRecord::FromNakama(leaderboardRecord));
                }
            }
            leaderboardRecordList.nextCursor = nLeaderboardRecordList.nextCursor.c_str();
            leaderboardRecordList.prevCursor = nLeaderboardRecordList.prevCursor.c_str();
            return leaderboardRecordList;
        }
        static Nakama::NLeaderboardRecordList ToNakama(const LeaderboardRecordList& leaderboardRecordList)
        {
            Nakama::NLeaderboardRecordList nLeaderboardRecordList;
            if (leaderboardRecordList.records.size() != 0)
            {
                for (const auto& leaderboardRecord : leaderboardRecordList.records)
                {
                    nLeaderboardRecordList.records.push_back(LeaderboardRecord::ToNakama(leaderboardRecord));
                }
            }
            if (leaderboardRecordList.ownerRecords.size() != 0)
            {
                for (const auto& leaderboardRecord : leaderboardRecordList.ownerRecords)
                {
                    nLeaderboardRecordList.ownerRecords.push_back(LeaderboardRecord::ToNakama(leaderboardRecord));
                }
            }
            nLeaderboardRecordList.nextCursor = leaderboardRecordList.nextCursor.c_str();
            nLeaderboardRecordList.prevCursor = leaderboardRecordList.prevCursor.c_str();
            return nLeaderboardRecordList;
        }
    };

    /// A tournament on the server.
    struct Tournament
    {
        AZ_TYPE_INFO(Tournament, "{57DB4342-9741-4E4E-B7BE-8D0B1B764F81}");
        AZ_CLASS_ALLOCATOR(Tournament, AZ::SystemAllocator, 0);
        Tournament()
            : id{}, title{}, description{}, category{}, sortOrder{}, size{}, maxSize{}, maxNumScore{}, canEnter{}, createTime{}
        {
        }
        AZStd::string id;                ///< The ID of the tournament.
        AZStd::string title;             ///< The title for the tournament.
        AZStd::string description;       ///< The description of the tournament. May be blank.
        AZ::u32 category = 0;         ///< The category of the tournament. e.g. "vip" could be category 1.
        AZ::u32 sortOrder = 0;        ///< ASC or DESC sort mode of scores in the tournament.
        AZ::u32 size = 0;             ///< The current number of players in the tournament.
        AZ::u32 maxSize = 0;          ///< The maximum number of players for the tournament.
        AZ::u32 maxNumScore = 0;      ///< The maximum score updates allowed per player for the current tournament.
        bool canEnter = false;         ///< True if the tournament is active and can enter. A computed value.
        AZ::u64 createTime = 0;     ///< The UNIX time when the tournament was created.
        AZ::u64 startTime = 0;      ///< The UNIX time when the tournament will start.
        AZ::u64 endTime = 0;        ///< The UNIX time when the tournament will be stopped.
        AZ::u32 endActive = 0;        ///< The UNIX time when the tournament stops being active until next reset. A computed value.
        AZ::u32 nextReset = 0;        ///< The UNIX time when the tournament is next playable. A computed value.
        AZ::u32 duration = 0;         ///< Duration of the tournament in seconds.
        AZ::u32 startActive = 0;      ///< The UNIX time when the tournament start being active. A computed value.
        AZStd::string metadata;          ///< Additional information stored as a JSON object.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Tournament>()
                    ->Version(1)
                    ->Field("id", &Tournament::id)
                    ->Field("title", &Tournament::title)
                    ->Field("description", &Tournament::description)
                    ->Field("category", &Tournament::category)
                    ->Field("sortOrder", &Tournament::sortOrder)
                    ->Field("size", &Tournament::size)
                    ->Field("maxSize", &Tournament::maxSize)
                    ->Field("maxNumScore", &Tournament::maxNumScore)
                    ->Field("canEnter", &Tournament::canEnter)
                    ->Field("createTime", &Tournament::createTime)
                    ->Field("startTime", &Tournament::startTime)
                    ->Field("endTime", &Tournament::endTime)
                    ->Field("endActive", &Tournament::endActive)
                    ->Field("nextReset", &Tournament::nextReset)
                    ->Field("duration", &Tournament::duration)
                    ->Field("startActive", &Tournament::startActive)
                    ->Field("metadata", &Tournament::metadata)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Tournament>("Tournament", "A tournament on the server.")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::id, "Id", "The ID of the tournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::title, "Title", "The title for the tournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::description, "Description", "The description of the tournament. Maybe blank.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::category, "Category", "The category of the tournament. e.g. \"vip\" could be category 1.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::sortOrder, "Sort Order", "ASC or DESC sort mode of scores in the tournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::size, "Size", "The current number of players in the tournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::maxSize, "Max Size", "The maximum number of players for thetournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::maxNumScore, "Max Num Score", "The maximum score updates allowed per player for the current tournament.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::canEnter, "Can Enter", "True if the tournament is active and can enter.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::createTime, "Create Time", "The UNIX time when the tournament was created.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::startTime, "Start Time", "The UNIX time when the tournament will start.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::endTime, "End Time", "The UNIX time when the tournament will be stopped.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::endActive, "End Active", "The UNIX time when the tournament stops being active until next reset.A computed value.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::nextReset, "Next Reset", "The UNIX time when the tournament is next playable.A computed value.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::duration, "Duration", "Duration of the tournament in seconds.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::startActive, "Start Active", "The UNIX time when the tournament start being active.A computed value.")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Tournament::metadata, "Metadata", "Additional information stored as a JSON object.")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Tournament>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Tournament::id))
                    ->Property("title", BehaviorValueProperty(&Tournament::title))
                    ->Property("description", BehaviorValueProperty(&Tournament::description))
                    ->Property("category", BehaviorValueProperty(&Tournament::category))
                    ->Property("sortOrder", BehaviorValueProperty(&Tournament::sortOrder))
                    ->Property("size", BehaviorValueProperty(&Tournament::size))
                    ->Property("maxSize", BehaviorValueProperty(&Tournament::maxSize))
                    ->Property("maxNumScore", BehaviorValueProperty(&Tournament::maxNumScore))
                    ->Property("canEnter", BehaviorValueProperty(&Tournament::canEnter))
                    ->Property("createTime", BehaviorValueProperty(&Tournament::createTime))
                    ->Property("startTime", BehaviorValueProperty(&Tournament::startTime))
                    ->Property("endTime", BehaviorValueProperty(&Tournament::endTime))
                    ->Property("endActive", BehaviorValueProperty(&Tournament::endActive))
                    ->Property("nextReset", BehaviorValueProperty(&Tournament::nextReset))
                    ->Property("duration", BehaviorValueProperty(&Tournament::duration))
                    ->Property("startActive", BehaviorValueProperty(&Tournament::startActive))
                    ->Property("metadata", BehaviorValueProperty(&Tournament::metadata))
                    ;
            }
        }

        static Tournament FromNakama(const Nakama::NTournament& nTournament)
        {
            Tournament tournament;
            tournament.id = nTournament.id.c_str();
            tournament.title = nTournament.title.c_str();
            tournament.description = nTournament.description.c_str();
            tournament.category = nTournament.category;
            tournament.sortOrder = nTournament.sortOrder;
            tournament.size = nTournament.size;
            tournament.maxSize = nTournament.maxSize;
            tournament.maxNumScore = nTournament.maxNumScore;
            tournament.canEnter = nTournament.canEnter;
            tournament.createTime = nTournament.createTime;
            tournament.startTime = nTournament.startTime;
            tournament.endTime = nTournament.endTime;
            tournament.endActive = nTournament.endActive;
            tournament.nextReset = nTournament.nextReset;
            tournament.duration = nTournament.duration;
            tournament.startActive = nTournament.startActive;
            tournament.metadata = nTournament.metadata.c_str();
            return tournament;
        }
        static Nakama::NTournament ToNakama(const Tournament& tournament)
        {
            Nakama::NTournament nTournament;
            nTournament.id = tournament.id.c_str();
            nTournament.title = tournament.title.c_str();
            nTournament.description = tournament.description.c_str();
            nTournament.category = tournament.category;
            nTournament.sortOrder = tournament.sortOrder;
            nTournament.size = tournament.size;
            nTournament.maxSize = tournament.maxSize;
            nTournament.maxNumScore = tournament.maxNumScore;
            nTournament.canEnter = tournament.canEnter;
            nTournament.createTime = tournament.createTime;
            nTournament.startTime = tournament.startTime;
            nTournament.endTime = tournament.endTime;
            nTournament.endActive = tournament.endActive;
            nTournament.nextReset = tournament.nextReset;
            nTournament.duration = tournament.duration;
            nTournament.startActive = tournament.startActive;
            nTournament.metadata = tournament.metadata.c_str();
            return nTournament;
        }
    };

    /// A list of tournaments.
    struct TournamentList
    {
        AZ_TYPE_INFO(TournamentList, "{8F45346E-F4E6-4E38-9E39-4AB4D56A3430}");
        AZ_CLASS_ALLOCATOR(TournamentList, AZ::SystemAllocator, 0);
        TournamentList()
            : tournaments{}, cursor{}
        {
        }
        AZStd::vector<Tournament> tournaments;     ///< The list of tournaments returned.
        AZStd::string cursor;                       ///< A pagination cursor (optional).

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<TournamentList>()
                    ->Version(0)
                    ->Field("tournaments", &TournamentList::tournaments)
                    ->Field("cursor", &TournamentList::cursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<TournamentList>("TournamentList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentList::tournaments, "Tournaments", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentList::cursor, "Cursor", "")
                        ;
                }
            }
            if(auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<TournamentList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("tournaments", BehaviorValueProperty(&TournamentList::tournaments))
                    ->Property("cursor", BehaviorValueProperty(&TournamentList::cursor))
                    ;
            }
        }

        static TournamentList FromNakama(const Nakama::NTournamentList& nTournamentList)
        {
            TournamentList tournamentList;
            if (nTournamentList.tournaments.size() != 0)
            {
                for (const auto& tournament : nTournamentList.tournaments)
                {
                    tournamentList.tournaments.push_back(Tournament::FromNakama(tournament));
                }
            }
            tournamentList.cursor = nTournamentList.cursor.c_str();
            return tournamentList;
        }
        static Nakama::NTournamentList ToNakama(const TournamentList& tournamentList)
        {
            Nakama::NTournamentList nTournamentList;
            if (tournamentList.tournaments.size() != 0)
            {
                for (const auto& tournament : tournamentList.tournaments)
                {
                    nTournamentList.tournaments.push_back(Tournament::ToNakama(tournament));
                }
            }
            nTournamentList.cursor = tournamentList.cursor.c_str();
            return nTournamentList;
        }
    };

    /// A set of tournament records which may be part of a tournament records page or a batch of individual records.
    struct TournamentRecordList
    {
        AZ_TYPE_INFO(TournamentRecordList, "{4E983965-0ACC-48AB-A4E3-21404EF92CB1}");
        AZ_CLASS_ALLOCATOR(TournamentRecordList, AZ::SystemAllocator, 0);
        TournamentRecordList()
            : records{}, ownerRecords{}, nextCursor{}, prevCursor{}
        {
        }
        AZStd::vector<LeaderboardRecord> records;           ///< A list of tournament records.
        AZStd::vector<LeaderboardRecord> ownerRecords;      ///< A batched set of tournament records belonging to specified owners.
        AZStd::string nextCursor;                            ///< The cursor to send when retireving the next page, if any.
        AZStd::string prevCursor;                            ///< The cursor to send when retrieving the previous page, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<TournamentRecordList>()
                    ->Version(0)
                    ->Field("records", &TournamentRecordList::records)
                    ->Field("ownerRecords", &TournamentRecordList::ownerRecords)
                    ->Field("nextCursor", &TournamentRecordList::nextCursor)
                    ->Field("prevCursor", &TournamentRecordList::prevCursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<TournamentRecordList>("TournamentRecordList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentRecordList::records, "Records", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentRecordList::ownerRecords, "Owner Records", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentRecordList::nextCursor, "Next Cursor", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &TournamentRecordList::prevCursor, "Prev Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<TournamentRecordList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("records", BehaviorValueProperty(&TournamentRecordList::records))
                    ->Property("ownerRecords", BehaviorValueProperty(&TournamentRecordList::ownerRecords))
                    ->Property("nextCursor", BehaviorValueProperty(&TournamentRecordList::nextCursor))
                    ->Property("prevCursor", BehaviorValueProperty(&TournamentRecordList::prevCursor))
                    ;
            }
        }

        static TournamentRecordList FromNakama(const Nakama::NTournamentRecordList& nTournamentRecordList)
        {
            TournamentRecordList tournamentRecordList;
            if (nTournamentRecordList.records.size() != 0)
            {
                for (const auto& record : nTournamentRecordList.records)
                {
                    tournamentRecordList.records.push_back(LeaderboardRecord::FromNakama(record));
                }
            }
            if (nTournamentRecordList.ownerRecords.size() != 0)
            {
                for (const auto& record : nTournamentRecordList.ownerRecords)
                {
                    tournamentRecordList.ownerRecords.push_back(LeaderboardRecord::FromNakama(record));
                }
            }
            tournamentRecordList.nextCursor = nTournamentRecordList.nextCursor.c_str();
            tournamentRecordList.prevCursor = nTournamentRecordList.prevCursor.c_str();
            return tournamentRecordList;
        }
        static Nakama::NTournamentRecordList ToNakama(const TournamentRecordList& tournamentRecordList)
        {
            Nakama::NTournamentRecordList nTournamentRecordList;
            if (tournamentRecordList.records.size() != 0)
            {
                for (const auto& record : tournamentRecordList.records)
                {
                    nTournamentRecordList.records.push_back(LeaderboardRecord::ToNakama(record));
                }
            }
            if (tournamentRecordList.ownerRecords.size() != 0)
            {
                for (const auto& record : tournamentRecordList.ownerRecords)
                {
                    nTournamentRecordList.ownerRecords.push_back(LeaderboardRecord::ToNakama(record));
                }
            }
            nTournamentRecordList.nextCursor = tournamentRecordList.nextCursor.c_str();
            nTournamentRecordList.prevCursor = tournamentRecordList.prevCursor.c_str();
            return nTournamentRecordList;
        }
    };
    /// Represents a realtime match.
    struct Match
    {
        AZ_TYPE_INFO(Match, "{6A7BC391-BD36-459F-B2E8-288B6DD37289}");
        AZ_CLASS_ALLOCATOR(Match, AZ::SystemAllocator, 0);
        Match()
            : matchId{}, authoritative{}, label{}, size{}, presences{}, self{}
        {
        }
        AZStd::string matchId;                     ///< The ID of the match, can be used to join.
        bool authoritative = false;              ///< True if it's an server-managed authoritative match, false otherwise.
        AZStd::string label;                       ///< Match label, if any.
        AZ::s32 size = 0;                        ///< Current number of users in the match.
        AZStd::vector<UserPresence> presences;    ///< The users currently in the match.
        UserPresence self;                      ///< A reference to the current user's presence in the match.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Match>()
                    ->Version(0)
                    ->Field("matchId", &Match::matchId)
                    ->Field("authoritative", &Match::authoritative)
                    ->Field("label", &Match::label)
                    ->Field("size", &Match::size)
                    ->Field("presences", &Match::presences)
                    ->Field("self", &Match::self)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Match>("Match", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::matchId, "Match Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::authoritative, "Authoritative", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::label, "Label","")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::size, "Size", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::presences, "Presences", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Match::self, "Self", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Match>("Match")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Attribute(AZ::Script::Attributes::Module, "nakama")
                    ->Constructor()
                    ->Property("matchId", BehaviorValueProperty(&Match::matchId))
                    ->Property("authoritative", BehaviorValueProperty(&Match::authoritative))
                    ->Property("label", BehaviorValueProperty(&Match::label))
                    ->Property("size", BehaviorValueProperty(&Match::size))
                    ->Property("presences", BehaviorValueProperty(&Match::presences))
                    ->Property("self", BehaviorValueProperty(&Match::self))
                    ;
            }
        }

        static Match FromNakama(const Nakama::NMatch& nMatch)
        {
            Match match;
            match.matchId = nMatch.matchId.c_str();
            match.authoritative = nMatch.authoritative;
            match.label = nMatch.label.c_str();
            match.size = nMatch.size;
            if (nMatch.presences.size() != 0)
            {
                for (const auto& presence : nMatch.presences)
                {
                    match.presences.push_back(UserPresence::FromNakama(presence));
                }
            }
            match.self = UserPresence::FromNakama(nMatch.self);
            return match;
        }
        static Nakama::NMatch ToNakama(const Match& match)
        {
            Nakama::NMatch nMatch;
            nMatch.matchId = match.matchId.c_str();
            nMatch.authoritative = match.authoritative;
            nMatch.label = match.label.c_str();
            nMatch.size = match.size;
            if (match.presences.size() != 0)
            {
                for (const auto& presence : match.presences)
                {
                    nMatch.presences.push_back(UserPresence::ToNakama(presence));
                }
            }
            nMatch.self = UserPresence::ToNakama(match.self);
            return nMatch;
        }
    };

    /// A list of realtime matches.
    struct MatchList
    {
        AZ_TYPE_INFO(MatchList, "{C3049E99-74F3-4905-9FA2-983FC903D2E8}");
        AZ_CLASS_ALLOCATOR(MatchList, AZ::SystemAllocator, 0);
        MatchList()
            : matches{}
        {
        }
        AZStd::vector<Match> matches;   ///< A number of matches corresponding to a list operation.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<MatchList>()
                    ->Version(0)
                    ->Field("matches", &MatchList::matches)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<MatchList>("MatchList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &MatchList::matches, "Matches", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<MatchList>("MatchList")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Attribute(AZ::Script::Attributes::Module, "nakama")
                    ->Constructor()
                    ->Property("matches", BehaviorValueProperty(&MatchList::matches))
                    ;
            }
        }
        static MatchList FromNakama(const Nakama::NMatchList& nMatchList)
        {
            MatchList matchList;
            if (nMatchList.matches.size() != 0)
            {
                for (const auto& match : nMatchList.matches)
                {
                    matchList.matches.push_back(Match::FromNakama(match));
                }
            }
            return matchList;
        }
        static Nakama::NMatchList ToNakama(const MatchList& matchList)
        {
            Nakama::NMatchList nMatchList;
            if (matchList.matches.size() != 0)
            {
                for (const auto& match : matchList.matches)
                {
                    nMatchList.matches.push_back(Match::ToNakama(match));
                }
            }
            return nMatchList;
        }
    };

    /// A list of channel messages, usually a result of a list operation.
    struct ChannelMessageList
    {
        AZ_TYPE_INFO(ChannelMessageList, "{C0B58BA2-E0AF-4CE3-930E-8EFA5010BA37}");
        AZ_CLASS_ALLOCATOR(ChannelMessageList, AZ::SystemAllocator, 0);
        ChannelMessageList()
            : messages{}, nextCursor{}, prevCursor{}
        {
        }

        AZStd::vector<ChannelMessage> messages;       ///< A list of messages.
        AZStd::string nextCursor;                      ///< The cursor to send when retireving the next page, if any.
        AZStd::string prevCursor;                      ///< The cursor to send when retrieving the previous page, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<ChannelMessageList>()
                    ->Version(0)
                    ->Field("messages", &ChannelMessageList::messages)
                    ->Field("nextCursor", &ChannelMessageList::nextCursor)
                    ->Field("prevCursor", &ChannelMessageList::prevCursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<ChannelMessageList>("ChannelMessageList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageList::messages, "Messages", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageList::nextCursor, "Next Cursor", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageList::prevCursor, "Prev Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<ChannelMessageList>("ChannelMessageList")
                    ->Attribute(AZ::Script::Attributes::Scope, AZ::Script::Attributes::ScopeFlags::Common)
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Constructor()
                    ->Property("messages", BehaviorValueProperty(&ChannelMessageList::messages))
                    ->Property("nextCursor", BehaviorValueProperty(&ChannelMessageList::nextCursor))
                    ->Property("prevCursor", BehaviorValueProperty(&ChannelMessageList::prevCursor))
                    ;
            }
        }

        static ChannelMessageList FromNakama(const Nakama::NChannelMessageList& nChannelMessageList)
        {
            ChannelMessageList channelMessageList;
            if (nChannelMessageList.messages.size() != 0)
            {
                for (const auto& message : nChannelMessageList.messages)
                {
                    channelMessageList.messages.push_back(ChannelMessage::FromNakama(message));
                }
            }
            channelMessageList.nextCursor = nChannelMessageList.nextCursor.c_str();
            channelMessageList.prevCursor = nChannelMessageList.prevCursor.c_str();
            return channelMessageList;
        }
        static Nakama::NChannelMessageList ToNakama(const ChannelMessageList& channelMessageList)
        {
            Nakama::NChannelMessageList nChannelMessageList;
            if (channelMessageList.messages.size() != 0)
            {
                for (const auto& message : channelMessageList.messages)
                {
                    nChannelMessageList.messages.push_back(ChannelMessage::ToNakama(message));
                }
            }
            nChannelMessageList.nextCursor = channelMessageList.nextCursor.c_str();
            nChannelMessageList.prevCursor = channelMessageList.prevCursor.c_str();
            return nChannelMessageList;
        }
    };

    /// An object within the storage engine.
    struct StorageObject
    {
        AZ_TYPE_INFO(StorageObject, "{72152825-61B6-4803-8B62-D9DE1471E8F5}");
        AZ_CLASS_ALLOCATOR(StorageObject, AZ::SystemAllocator, 0);
        StorageObject()
            : collection(), key(), userId(), value(), version(), permissionRead(), permissionWrite(), createTime(), updateTime()
        {
        }

        AZStd::string collection;                    ///< The collection which stores the object.
        AZStd::string key;                           ///< The key of the object within the collection.
        AZStd::string userId;                        ///< The user owner of the object.
        AZStd::string value;                         ///< The value of the object.
        AZStd::string version;                       ///< The version hash of the object.
        AZ::u8 permissionRead;     ///< The read access permissions for the object.
        AZ::u8 permissionWrite;   ///< The write access permissions for the object.
        AZ::u64 createTime = 0;                 ///< The UNIX time when the object was created.
        AZ::u64 updateTime = 0;                 ///< The UNIX time when the object was last updated.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StorageObject>()
                    ->Version(0)
                    ->Field("collection", &StorageObject::collection)
                    ->Field("key", &StorageObject::key)
                    ->Field("userId", &StorageObject::userId)
                    ->Field("value", &StorageObject::value)
                    ->Field("version", &StorageObject::version)
                    ->Field("permissionRead", &StorageObject::permissionRead)
                    ->Field("permissionWrite", &StorageObject::permissionWrite)
                    ->Field("createTime", &StorageObject::createTime)
                    ->Field("updateTime", &StorageObject::updateTime)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StorageObject>("StorageObject", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::collection, "Collection", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::key, "Key", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::userId, "UserId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::value, "Value", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::version, "Version", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::permissionRead, "PermissionRead", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::permissionWrite, "PermissionWrite", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObject::updateTime, "UpdateTime", "")
                        ;                
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StorageObject>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("collection", BehaviorValueProperty(&StorageObject::collection))
                    ->Property("key", BehaviorValueProperty(&StorageObject::key))
                    ->Property("userId", BehaviorValueProperty(&StorageObject::userId))
                    ->Property("value", BehaviorValueProperty(&StorageObject::value))
                    ->Property("version", BehaviorValueProperty(&StorageObject::version))
                    ->Property("permissionRead", BehaviorValueProperty(&StorageObject::permissionRead))
                    ->Property("permissionWrite", BehaviorValueProperty(&StorageObject::permissionWrite))
                    ->Property("createTime", BehaviorValueProperty(&StorageObject::createTime))
                    ->Property("updateTime", BehaviorValueProperty(&StorageObject::updateTime))
                    ;
            }
        }

        static StorageObject FromNakama(const Nakama::NStorageObject& nStorageObject)
        {
            StorageObject storageObject;
            storageObject.collection = nStorageObject.collection.c_str();
            storageObject.key = nStorageObject.key.c_str();
            storageObject.userId = nStorageObject.userId.c_str();
            storageObject.value = nStorageObject.value.c_str();
            storageObject.version = nStorageObject.version.c_str();
            storageObject.permissionRead = static_cast<AZ::u8>(nStorageObject.permissionRead);
            storageObject.permissionWrite = static_cast<AZ::u8>(nStorageObject.permissionWrite);
            storageObject.createTime = nStorageObject.createTime;
            storageObject.updateTime = nStorageObject.updateTime;
            return storageObject;
        }
        static Nakama::NStorageObject ToNakama(const StorageObject& storageObject)
        {
            Nakama::NStorageObject nStorageObject;
            nStorageObject.collection = storageObject.collection.c_str();
            nStorageObject.key = storageObject.key.c_str();
            nStorageObject.userId = storageObject.userId.c_str();
            nStorageObject.value = storageObject.value.c_str();
            nStorageObject.version = storageObject.version.c_str();
            nStorageObject.permissionRead = static_cast<Nakama::NStoragePermissionRead>(storageObject.permissionRead);
            nStorageObject.permissionWrite = static_cast<Nakama::NStoragePermissionWrite>(storageObject.permissionWrite);
            nStorageObject.createTime = storageObject.createTime;
            nStorageObject.updateTime = storageObject.updateTime;
            return nStorageObject;
        }
    };

    /// List of storage objects.
    struct StorageObjectList
    {
        AZ_TYPE_INFO(StorageObjectList, "{65375218-51CD-4A43-A21B-B48D8C7D0B1B}");
        AZ_CLASS_ALLOCATOR(StorageObjectList, AZ::SystemAllocator, 0);
        StorageObjectList()
            : objects(), cursor()
        {
        }
        AZStd::vector<StorageObject> objects;  ///< The list of storage objects.
        AZStd::string cursor;                   ///< The cursor for the next page of results, if any.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StorageObjectList>()
                    ->Version(0)
                    ->Field("objects", &StorageObjectList::objects)
                    ->Field("cursor", &StorageObjectList::cursor)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StorageObjectList>("StorageObjectList", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectList::objects, "Objects", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectList::cursor, "Cursor", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StorageObjectList>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("objects", BehaviorValueProperty(&StorageObjectList::objects))
                    ->Property("cursor", BehaviorValueProperty(&StorageObjectList::cursor))
                    ;
            }
        }

        static StorageObjectList FromNakama(const Nakama::NStorageObjectList& nStorageObjectList)
        {
            StorageObjectList storageObjectList;
            if (nStorageObjectList.objects.size() != 0)
            {
                for (const auto& object : nStorageObjectList.objects)
                {
                    storageObjectList.objects.push_back(StorageObject::FromNakama(object));
                }
            }
            storageObjectList.cursor = nStorageObjectList.cursor.c_str();
            return storageObjectList;
        }
        static Nakama::NStorageObjectList ToNakama(const StorageObjectList& storageObjectList)
        {
            Nakama::NStorageObjectList nStorageObjectList;
            if (storageObjectList.objects.size() != 0)
            {
                for (const auto& object : storageObjectList.objects)
                {
                    nStorageObjectList.objects.push_back(StorageObject::ToNakama(object));
                }
            }
            nStorageObjectList.cursor = storageObjectList.cursor.c_str();
            return nStorageObjectList;
        }
    };

    /// A storage acknowledgement.
    struct StorageObjectAck
    {
        AZ_TYPE_INFO(StorageObjectAck, "{0DF273C0-AAB8-46F3-AF2D-BE745ABD1B89}");
        AZ_CLASS_ALLOCATOR(StorageObjectAck, AZ::SystemAllocator, 0);
        StorageObjectAck()
            : collection(), key(), version(), userId()
        {
        }
        AZStd::string collection;                ///< The collection which stores the object.
        AZStd::string key;                       ///< The key of the object within the collection.
        AZStd::string version;                   ///< The version hash of the object.
        AZStd::string userId;                    ///< The owner of the object.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<StorageObjectAck>()
                    ->Version(0)
                    ->Field("collection", &StorageObjectAck::collection)
                    ->Field("key", &StorageObjectAck::key)
                    ->Field("version", &StorageObjectAck::version)
                    ->Field("userId", &StorageObjectAck::userId)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<StorageObjectAck>("StorageObjectAck", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectAck::collection, "Collection", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectAck::key, "Key", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default,&StorageObjectAck::version, "Version", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &StorageObjectAck::userId, "UserId", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<StorageObjectAck>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("collection", BehaviorValueProperty(&StorageObjectAck::collection))
                    ->Property("key", BehaviorValueProperty(&StorageObjectAck::key))
                    ->Property("version", BehaviorValueProperty(&StorageObjectAck::version))
                    ->Property("userId", BehaviorValueProperty(&StorageObjectAck::userId))
                    ;
            }
        }

        static StorageObjectAck FromNakama(const Nakama::NStorageObjectAck& nStorageObjectAck)
        {
            StorageObjectAck storageObjectAck;
            storageObjectAck.collection = nStorageObjectAck.collection.c_str();
            storageObjectAck.key = nStorageObjectAck.key.c_str();
            storageObjectAck.version = nStorageObjectAck.version.c_str();
            storageObjectAck.userId = nStorageObjectAck.userId.c_str();
            return storageObjectAck;
        }
        static Nakama::NStorageObjectAck ToNakama(const StorageObjectAck& storageObjectAck)
        {
            Nakama::NStorageObjectAck nStorageObjectAck;
            nStorageObjectAck.collection = storageObjectAck.collection.c_str();
            nStorageObjectAck.key = storageObjectAck.key.c_str();
            nStorageObjectAck.version = storageObjectAck.version.c_str();
            nStorageObjectAck.userId = storageObjectAck.userId.c_str();
            return nStorageObjectAck;
        }
    };

    struct Error
    {
        AZ_TYPE_INFO(Error, "{C32632F6-EC55-4922-91FB-0EA7D14D0DA0}");
        AZ_CLASS_ALLOCATOR(Error, AZ::SystemAllocator, 0);
        Error()
            : message(), code()
        {
        }

        AZStd::string message;
        AZ::s8 code;

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Error>()
                    ->Version(0)
                    ->Field("message", &Error::message)
                    ->Field("code", &Error::code)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Error>("Error", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Error::message, "Message", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Error::code, "Code", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Error>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("message", BehaviorValueProperty(&Error::message))
                    ->Property("code", BehaviorValueProperty(&Error::code))
                    ;
            }
        }

        static Error FromNakama(const Nakama::NError& nError)
        {
            Error error;
            error.message = nError.message.c_str();
            error.code = static_cast<AZ::s8>(nError.code);
            return error;
        }
    };

    /// Execute an Lua function on the server.
    struct Rpc
    {
        AZ_TYPE_INFO(Rpc, "{E35F5502-72F7-46E0-9DF8-32EC938CD861}");
        AZ_CLASS_ALLOCATOR(Rpc, AZ::SystemAllocator, 0);
        Rpc()
            : id(), payload(), httpKey()
        {
        }

        AZStd::string id;            ///< The identifier of the function.
        AZStd::string payload;       ///< The payload of the function which must be a JSON object.
        AZStd::string httpKey;       ///< The authentication key used when executed as a non-client HTTP request.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Rpc>()
                    ->Version(0)
                    ->Field("id", &Rpc::id)
                    ->Field("payload", &Rpc::payload)
                    ->Field("httpKey", &Rpc::httpKey)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Rpc>("Rpc", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Rpc::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Rpc::payload, "Payload", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Rpc::httpKey,"HttpKey", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Rpc>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Rpc::id))
                    ->Property("payload", BehaviorValueProperty(&Rpc::payload))
                    ->Property("httpKey", BehaviorValueProperty(&Rpc::httpKey))
                    ;
            }
        }

        static Rpc FromNakama(const Nakama::NRpc& nRpc)
        {
            Rpc rpc;
            rpc.id = nRpc.id.c_str();
            rpc.payload = nRpc.payload.c_str();
            rpc.httpKey = nRpc.httpKey.c_str();
            return rpc;
        }
    };

    /// A realtime chat channel.
    struct Channel
    {
        AZ_TYPE_INFO(Channel, "{42AD7722-776B-4105-837A-23C4AA6CC72E}");
        AZ_CLASS_ALLOCATOR(Channel, AZ::SystemAllocator, 0);
        Channel()
            : id(), presences(), self(), roomName(), groupId(), userIdOne(), userIdTwo()
        {
        }
        AZStd::string id;                           ///< The ID of the channel.
        AZStd::vector<UserPresence> presences;     ///< The users currently in the channel.
        UserPresence self;                       ///< A reference to the current user's presence in the channel.
        AZStd::string roomName;                     ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        AZStd::string groupId;                      ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        AZStd::string userIdOne;                    ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        AZStd::string userIdTwo;                    ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto* serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<Channel>()
                    ->Version(0)
                    ->Field("id", &Channel::id)
                    ->Field("presences", &Channel::presences)
                    ->Field("self", &Channel::self)
                    ->Field("roomName", &Channel::roomName)
                    ->Field("groupId", &Channel::groupId)
                    ->Field("userIdOne", &Channel::userIdOne)
                    ->Field("userIdTwo", &Channel::userIdTwo)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<Channel>("Channel", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::id, "Id", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::presences, "Presences", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::self, "Self", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::roomName, "RoomName", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::groupId, "GroupId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::userIdOne, "UserIdOne", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &Channel::userIdTwo, "UserIdTwo", "")
                        ;
                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<Channel>()
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("id", BehaviorValueProperty(&Channel::id))
                    ->Property("presences", BehaviorValueProperty(&Channel::presences))
                    ->Property("self", BehaviorValueProperty(&Channel::self))
                    ->Property("roomName", BehaviorValueProperty(&Channel::roomName))
                    ->Property("groupId", BehaviorValueProperty(&Channel::groupId))
                    ->Property("userIdOne", BehaviorValueProperty(&Channel::userIdOne))
                    ->Property("userIdTwo", BehaviorValueProperty(&Channel::userIdTwo))
                    ;
            }
        }

        static Channel FromNakama(const Nakama::NChannel& nChannel)
        {
            Channel channel;
            channel.id = nChannel.id.c_str();
            if (nChannel.presences.size() != 0)
            {
                for (auto& presence : nChannel.presences)
                {
                    channel.presences.push_back(UserPresence::FromNakama(presence));
                }
            }
            channel.self = UserPresence::FromNakama(nChannel.self);
            channel.roomName = nChannel.roomName.c_str();
            channel.groupId = nChannel.groupId.c_str();
            channel.userIdOne = nChannel.userIdOne.c_str();
            channel.userIdTwo = nChannel.userIdTwo.c_str();
            return channel;
        }
    };

    /// A receipt reply from a channel message send operation.
    struct ChannelMessageAck
    {
        AZ_TYPE_INFO(ChannelMessageAck, "{7EDF71AE-9406-4AD8-BDA1-F6F34B830592}");
        AZ_CLASS_ALLOCATOR(ChannelMessageAck, AZ::SystemAllocator, 0);
        ChannelMessageAck()
            : channelId(""), messageId(""), username(""), code(0), createTime(0), updateTime(0), persistent(false), roomName(""), groupId("")
        {
        }
        AZStd::string channelId;          ///< The channel the message was sent to.
        AZStd::string messageId;          ///< The unique ID assigned to the message.
        AZStd::string username;           ///< Username of the message sender.
        AZ::s32 code = 0;               ///< The code representing a message type or category.
        AZ::u64 createTime = 0;      ///< The UNIX time when the message was created.
        AZ::u64 updateTime = 0;      ///< The UNIX time when the message was last updated.
        bool persistent = false;        ///< True if the message was persisted to the channel's history, false otherwise.
        AZStd::string roomName;           ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        AZStd::string groupId;            ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        AZStd::string userIdOne;          ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        AZStd::string userIdTwo;          ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.

        static void Reflect(AZ::ReflectContext* context)
        {
            if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
            {
                serializeContext->Class<ChannelMessageAck>()
                    ->Version(1)
                    ->Field("channelId", &ChannelMessageAck::channelId)
                    ->Field("messageId", &ChannelMessageAck::messageId)
                    ->Field("username", &ChannelMessageAck::username)
                    ->Field("code", &ChannelMessageAck::code)
                    ->Field("createTime", &ChannelMessageAck::createTime)
                    ->Field("updateTime", &ChannelMessageAck::updateTime)
                    ->Field("persistent", &ChannelMessageAck::persistent)
                    ->Field("roomName", &ChannelMessageAck::roomName)
                    ->Field("groupId", &ChannelMessageAck::groupId)
                    ->Field("userIdOne", &ChannelMessageAck::userIdOne)
                    ->Field("userIdTwo", &ChannelMessageAck::userIdTwo)
                    ;
                if (auto editContext = serializeContext->GetEditContext())
                {
                    editContext->Class<ChannelMessageAck>("ChannelMessageAck", "")
                        ->ClassElement(AZ::Edit::ClassElements::EditorData, "")
                        ->Attribute(AZ::Edit::Attributes::AutoExpand, true)
                        ->Attribute(AZ::Edit::Attributes::Visibility, AZ::Edit::PropertyVisibility::ShowChildrenOnly)
                        ->Attribute(AZ::Edit::Attributes::NameLabelOverride, "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::channelId, "ChannelId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::messageId, "MessageId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::username, "Username", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::code, "Code", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::createTime, "CreateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::updateTime, "UpdateTime", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::persistent, "Persistent", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::roomName, "RoomName", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::groupId, "GroupId", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::userIdOne, "UserIdOne", "")
                        ->DataElement(AZ::Edit::UIHandlers::Default, &ChannelMessageAck::userIdTwo, "UserIdTwo", "")
                        ;

                }
            }
            if (auto behaviorContext = azrtti_cast<AZ::BehaviorContext*>(context))
            {
                behaviorContext->Class<ChannelMessageAck>("ChannelMessageAck")
                    ->Attribute(AZ::Script::Attributes::Category, "Nakama")
                    ->Property("channelId", BehaviorValueProperty(&ChannelMessageAck::channelId))
                    ->Property("messageId", BehaviorValueProperty(&ChannelMessageAck::messageId))
                    ->Property("username", BehaviorValueProperty(&ChannelMessageAck::username))
                    ->Property("code", BehaviorValueProperty(&ChannelMessageAck::code))
                    ->Property("createTime", BehaviorValueProperty(&ChannelMessageAck::createTime))
                    ->Property("updateTime", BehaviorValueProperty(&ChannelMessageAck::updateTime))
                    ->Property("persistent", BehaviorValueProperty(&ChannelMessageAck::persistent))
                    ->Property("roomName", BehaviorValueProperty(&ChannelMessageAck::roomName))
                    ->Property("groupId", BehaviorValueProperty(&ChannelMessageAck::groupId))
                    ->Property("userIdOne", BehaviorValueProperty(&ChannelMessageAck::userIdOne))
                    ->Property("userIdTwo", BehaviorValueProperty(&ChannelMessageAck::userIdTwo))
                    ;
            }
        }

        static ChannelMessageAck FromNakama(const Nakama::NChannelMessageAck& nChannelMessageAck)
        {
            ChannelMessageAck channelMessageAck;
            channelMessageAck.channelId = nChannelMessageAck.channelId.c_str();
            channelMessageAck.messageId = nChannelMessageAck.messageId.c_str();
            channelMessageAck.username = nChannelMessageAck.username.c_str();
            channelMessageAck.code = nChannelMessageAck.code;
            channelMessageAck.createTime = nChannelMessageAck.createTime;
            channelMessageAck.updateTime = nChannelMessageAck.updateTime;
            channelMessageAck.persistent = nChannelMessageAck.persistent;
            channelMessageAck.roomName = nChannelMessageAck.roomName.c_str();
            channelMessageAck.groupId = nChannelMessageAck.groupId.c_str();
            channelMessageAck.userIdOne = nChannelMessageAck.userIdOne.c_str();
            channelMessageAck.userIdTwo = nChannelMessageAck.userIdTwo.c_str();
            return channelMessageAck;
        }
        static Nakama::NChannelMessageAck ToNakama(const ChannelMessageAck& channelMessageAck)
        {
            return Nakama::NChannelMessageAck{
                channelMessageAck.channelId.c_str(),
                channelMessageAck.messageId.c_str(),
                channelMessageAck.username.c_str(),
                channelMessageAck.code,
                channelMessageAck.createTime,
                channelMessageAck.updateTime,
                channelMessageAck.persistent,
                channelMessageAck.roomName.c_str(),
                channelMessageAck.groupId.c_str(),
                channelMessageAck.userIdOne.c_str(),
                channelMessageAck.userIdTwo.c_str()
            };
        }
    };
} // namespace NakamaClientGem
