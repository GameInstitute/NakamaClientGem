
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
namespace NakamaClientGem
{
    using AZStringMap = AZStd::vector<AZStd::pair<AZStd::string, AZStd::string>>;
    using AZStringDoubleMap = AZStd::vector<AZStd::pair<AZStd::string, double>>;

    struct RtClientDisconnectInfo
    {
        AZ_TYPE_INFO(RtClientDisconnectInfo, "{7A75E45C-C352-4300-BFB3-0057F11E3F01}");
        /// close code.
        /// https://developer.mozilla.org/en-US/docs/Web/API/CloseEvent
        AZ::u16 code = 0;

        /// close reason. Optional.
        AZStd::string reason;

        /// true if close was initiated by server.
        bool remote = false;

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
        AZ::s8 code = -100;      ///< The error code
        AZStd::string message;                          ///< A message in English to help developers debug the response.
        AZStringMap context;                           ///< Additional error details which may be different for each response.

        static RtError FromNakama(const Nakama::NRtError& nError)
        {
            RtError error;
            error.code = static_cast<AZ::s8>(nError.code);
            error.message = nError.message.c_str();
            if (nError.context.size() != 0)
            {
                for (auto kv : nError.context)
                {
                    error.context.push_back({kv.first.c_str(), kv.second.c_str() });
                }
            }
            return error;
        }
    };

    /// A message sent on a channel.
    struct ChannelMessage
    {
        AZ_TYPE_INFO(ChannelMessage, "{E6C749B9-15A3-4B22-AF69-257090B64ED8}");
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
    };

    /// A user session associated to a stream, usually through a list operation or a join/leave event.
    struct UserPresence
    {
        AZ_TYPE_INFO(UserPresence, "{236C7FE3-C74A-472B-84B9-914AA7F34891}");
        AZStd::string userId;             ///< The user this presence belongs to.
        AZStd::string sessionId;          ///< A unique session ID identifying the particular connection, because the user may have many.
        AZStd::string username;           ///< The username for display purposes.
        bool persistence = false;       ///< Whether this presence generates persistent data/messages, if applicable for the stream type.
        AZStd::string status;             ///< A user-set status message for this stream, if applicable.
    };

    /// A set of joins and leaves on a particular channel.
    struct ChannelPresenceEvent
    {
        AZ_TYPE_INFO(ChannelPresenceEvent, "{A39D9B25-B43C-4762-B1B4-947154C49E14}");
        AZStd::string channelId;                   ///< The channel identifier this event is for.
        AZStd::vector<UserPresence> joins;        ///< Presences joining the channel as part of this event, if any.
        AZStd::vector<UserPresence> leaves;       ///< Presences leaving the channel as part of this event, if any.
        AZStd::string roomName;                    ///< The name of the chat room, or an empty string if this message was not sent through a chat room.
        AZStd::string groupId;                     ///< The ID of the group, or an empty string if this message was not sent through a group channel.
        AZStd::string userIdOne;                   ///< The ID of the first DM user, or an empty string if this message was not sent through a DM chat.
        AZStd::string userIdTwo;                   ///< The ID of the second DM user, or an empty string if this message was not sent through a DM chat.
    };


    struct MatchmakerUser
    {
        AZ_TYPE_INFO(MatchmakerUser, "{2CC0027F-74CA-4FF2-9807-5A2A0C7816DD}");
        UserPresence presence;                  ///< User info.
        AZStringMap stringProperties;             ///< String properties.
        AZStringDoubleMap numericProperties;      ///< Numeric properties.
    };

    /// A successful matchmaking result.
    struct MatchmakerMatched
    {
        AZ_TYPE_INFO(MatchmakerMatched, "{517D1267-C331-42DE-9587-43E5D84B17C1}");
        AZStd::string ticket;                  ///< The matchmaking ticket that has completed.
        ///< The match token or match ID to join.
        AZStd::string matchId;                 ///< Match ID.
        AZStd::string token;                   ///< Match join token.
        AZStd::vector<MatchmakerUser> users;  ///< The users that have been matched together, and information about their matchmaking data.
        MatchmakerUser self;                ///< A reference to the current user and their properties.
    };

    /// Realtime match data received from the server.
    struct MatchData
    {
        AZ_TYPE_INFO(MatchData, "{88BCBC9F-1A1D-47FB-8FAA-F02B087D4B95}");
        AZStd::string matchId;       ///< The match unique ID.
        UserPresence presence;    ///< A reference to the user presence that sent this data, if any.
        AZ::s64 opCode;            ///< Op code value.
        AZStd::string data;               ///< Data payload, if any.
    };

    /// A set of joins and leaves on a particular realtime match.
    struct MatchPresenceEvent
    {
        AZ_TYPE_INFO(MatchPresenceEvent, "{336ABA9E-6100-4711-8657-5CC7F86CFED6}");
        AZStd::string matchId;                 /// The match unique ID.
        AZStd::vector<UserPresence> joins;    /// User presences that have just joined the match.
        AZStd::vector<UserPresence> leaves;   /// User presences that have just left the match.
    };

    /// A notification in the server.
    struct Notification
    {
        AZ_TYPE_INFO(Notification, "{9095DEFF-3E23-4AA0-AF74-FBFC8718D149}");
        AZStd::string id;                  ///< ID of the Notification.
        AZStd::string subject;             ///< Subject of the notification.
        AZStd::string content;             ///< Content of the notification in JSON.
        AZ::s32 code = 0;                ///< Category code for this notification.
        AZStd::string senderId;            ///< ID of the sender, if a user. Otherwise 'null'.
        AZ::u64 createTime = 0;       ///< The UNIX time when the notification was created.
        bool persistent = false;         ///< True if this notification was persisted to the database.
    };

    /// A collection of zero or more notifications.
    struct NotificationList
    {
        AZ_TYPE_INFO(NotificationList, "{FFC94E9A-883A-44CE-A8AD-4D61B543D2D5}");
        AZStd::vector<Notification> notifications;      ///< Collection of notifications.
        AZStd::string cacheableCursor;                   ///< Use this cursor to paginate notifications. Cache this to catch up to new notifications.
    };

    /// Information about a party.
    struct Party
    {
        AZ_TYPE_INFO(Party, "{F5221BAD-EA5C-4696-8DEC-C4AB8BA5C2D2}");
        AZStd::string id; /// The unique party identifier.

        bool open; /// True, if the party is open to join.

        int maxSize; /// The maximum number of party members.

        UserPresence self;  /// The current user in this party. i.e. Yourself.

        UserPresence leader; /// The current party leader.

        AZStd::vector<UserPresence> presences; /// All members currently in the party.
    };

    /// Information about a party close event.
    struct PartyClose
    {
        AZ_TYPE_INFO(PartyClose, "{1524429A-20FF-4773-8D73-664E0D405706}");
        AZStd::string id; /// The unique party identifier of the closing party.
    };

    /// Incoming party data delivered from the server.
    struct PartyData
    {
        AZ_TYPE_INFO(PartyData, "{296FDDB3-4629-4965-9094-810222471B53}");
        /// The ID of the party.
        AZStd::string partyId;

        /// A reference to the user presence that sent this data, if any.
        UserPresence presence;

        /// The operation code the message was sent with.
        AZ::s64 opCode;

        /// Data payload, if any.
        AZStd::string data;
    };

    /// Incoming notification for one or more new presences attempting to join the party.
    struct PartyJoinRequest
    {
        AZ_TYPE_INFO(PartyJoinRequest, "{198AA86B-14C7-4483-BEED-77DB89B33081}");
        /// The ID of the party to get a list of join requests for.
        AZStd::string partyId;

        /// Presences attempting to join, or who have joined.
        AZStd::vector<UserPresence> presences;
    };

    /// Announcement of a new party leader.
    struct PartyLeader
    {
        AZ_TYPE_INFO(PartyLeader, "{86BD5DD4-B583-4571-B416-4FC3F2AF0824}");
        /// The ID of the party to announce the new leader for.
        AZStd::string partyId;

        /// The presence of the new party leader.
        UserPresence presence;
    };

    /// A response from starting a new party matchmaking process.
    struct PartyMatchmakerTicket
    {
        AZ_TYPE_INFO(PartyMatchmakerTicket, "{EE001C44-FDD8-478D-97CB-71AA904BBC7D}");
        /// The ID of the party.
        AZStd::string partyId;

        /// The ticket that can be used to cancel matchmaking.
        AZStd::string ticket;
    };

    /// Presence update for a particular party.
    struct PartyPresenceEvent
    {
        AZ_TYPE_INFO(PartyPresenceEvent, "{69F8581F-33BD-438B-9B07-9A3061E952E8}");
        /// The ID of the party.
        AZStd::string partyId;

        /// The user presences that have just joined the party.
        AZStd::vector<UserPresence> joins;

        /// The user presences that have just left the party.
        AZStd::vector<UserPresence> leaves;
    };

    /// A batch of status updates for a given user.
    struct StatusPresenceEvent
    {
        AZ_TYPE_INFO(StatusPresenceEvent, "{69F8581F-33BD-438B-9B07-9A3061E952E8}");
        AZStd::vector<UserPresence> joins;    ///< New statuses for the user.
        AZStd::vector<UserPresence> leaves;   ///< Previous statuses for the user.
    };

    /// Represents identifying information for a stream.
    struct Stream
    {
        AZ_TYPE_INFO(Stream, "{3D51DCFD-F9BB-49DC-8091-7286BB60657E}");
        AZ::s32 mode = 0;               ///< Mode identifies the type of stream.
        AZStd::string subject;            ///< Subject is the primary identifier, if any.
        AZStd::string subcontext;         ///< Subcontext is a secondary identifier, if any.
        AZStd::string label;              ///< The label is an arbitrary identifying string, if the stream has one.
    };

    /// A set of joins and leaves on a particular stream.
    struct StreamPresenceEvent
    {
        AZ_TYPE_INFO(StreamPresenceEvent, "{98E87759-8989-4CF5-906B-E26B8D3AD761}");
        Stream stream;                      ///< The stream this event relates to.
        AZStd::vector<UserPresence> joins;    ///< Presences joining the stream as part of this event, if any.
        AZStd::vector<UserPresence> leaves;   ///< Presences leaving the stream as part of this event, if any.
    };

    /// A data message delivered over a stream.
    struct StreamData
    {
        AZ_TYPE_INFO(StreamData, "{EDB4A31C-2583-4006-858F-7CECD0CC4C8F}");
        Stream stream;          ///< The stream this data message relates to.
        UserPresence sender;    ///< The sender, if any.
        AZStd::string data;        ///< Arbitrary contents of the data message.
    };

    
} // namespace NakamaClientGem
