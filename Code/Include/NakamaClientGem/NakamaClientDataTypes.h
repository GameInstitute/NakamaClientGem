
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

    
} // namespace NakamaClientGem
