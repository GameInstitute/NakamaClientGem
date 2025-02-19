/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Math/Vector3.h>

#include "NakamaClientDataTypes.h"

namespace NakamaClientGem
{
    class NakamaClientComponentRequests : public AZ::ComponentBus
    {
    public:
        ~NakamaClientComponentRequests() override = default;

        /**
          * Authenticate a user with a device id.
          *
          * @param id A device identifier usually obtained from a platform API.
          * @param username A username used to create the user. Defaults to empty string.
          * @param create True if the user should be created when authenticated. Defaults to false.
          * @param vars Extra information that will be bundled in the session token.
          */
        virtual void AuthenticateDevice(
            const AZStd::string& id,
            const AZStd::string& username,
            bool create = false
        ) = 0;
    };

    using NakamaClientComponentRequestBus = AZ::EBus<NakamaClientComponentRequests>;

    class NakamaClientNotifications
        : public AZ::ComponentBus
    {
    public:
        // Listener
        virtual void OnConnect() = 0;
        virtual void OnDisconnect(const RtClientDisconnectInfo& info) = 0;
        virtual void OnError(const RtError& error) = 0;
        virtual void OnChannelMessage(const ChannelMessage& message) = 0;
        virtual void OnChannelPresence(const ChannelPresenceEvent& presence) = 0;
        virtual void OnMatchmakerMatched(const MatchmakerMatched& matched) = 0;
        virtual void OnMatchData(const MatchData& matchData) = 0;
        virtual void OnMatchPresence(const MatchPresenceEvent& matchPresence) = 0;
        virtual void OnNotifications(const NotificationList& notifications) = 0;
        virtual void OnParty(const Party& party) = 0;
        virtual void OnPartyClosed(const PartyClose& partyClosed) = 0;
        virtual void OnPartyData(const PartyData& partyData) = 0;
        virtual void OnPartyJoinRequest(const PartyJoinRequest& partyJoinRequest) = 0;
        virtual void OnPartyLeader(const PartyLeader& partyLeader) = 0;
        virtual void OnPartyMatchmakerTicket(const PartyMatchmakerTicket& partyMatchmakerTicket) = 0;
        virtual void OnPartyPresence(const PartyPresenceEvent& partyPresence) = 0;
        virtual void OnStatusPresence(const StatusPresenceEvent& presence) = 0;
        virtual void OnStreamPresence(const StreamPresenceEvent& presence) = 0;
        virtual void OnStreamData(const StreamData& data) = 0;

        virtual void OnAuthenticateSuccess() = 0;
        virtual void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) = 0;

    };

    using NakamaClientNotificationBus = AZ::EBus<NakamaClientNotifications>;

    class NakamaClientNotificationHandler
        : public NakamaClientNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(NakamaClientNotificationHandler,"{DF61DB90-7AC5-40E5-BA01-54B0C0100FA8}",
            AZ::SystemAllocator, OnConnect, OnDisconnect, OnError, OnChannelMessage, OnChannelPresence, OnMatchmakerMatched, OnMatchData, OnMatchPresence, OnNotifications, OnParty, OnPartyClosed, OnPartyData, OnPartyJoinRequest, OnPartyLeader, OnPartyMatchmakerTicket, OnPartyPresence, OnStatusPresence, OnStreamPresence, OnStreamData, OnAuthenticateSuccess, OnAuthenticateFailed);
  
        void OnConnect() override 
        {
            Call(FN_OnConnect);
        }
        void OnDisconnect(const RtClientDisconnectInfo& info) override
        {
            Call(FN_OnDisconnect, info);
        }
        void OnError(const RtError& error) override
        {
            Call(FN_OnError, error);
        }
        void OnChannelMessage(const ChannelMessage& message) override 
        {
            Call(FN_OnChannelMessage, message);
        }
        void OnChannelPresence(const ChannelPresenceEvent& presence) override
        {
            Call(FN_OnChannelPresence, presence);
        }
        void OnMatchmakerMatched(const MatchmakerMatched& matched) override
        {
            Call(FN_OnMatchmakerMatched, matched);
        }
        void OnMatchData(const MatchData& matchData) override
        {
            Call(FN_OnMatchData, matchData);
        }
        void OnMatchPresence(const MatchPresenceEvent& matchPresence) override
        {
            Call(FN_OnMatchPresence, matchPresence);
        }
        void OnNotifications(const NotificationList& notifications) override
        {
            Call(FN_OnNotifications, notifications);
        }
        void OnParty(const Party& party) override
        {
            Call(FN_OnParty, party);
        }
        void OnPartyClosed(const PartyClose& partyClosed) override
        {
            Call(FN_OnPartyClosed, partyClosed);
        }
        void OnPartyData(const PartyData& partyData) override 
        {
            Call(FN_OnPartyData, partyData);
        }
        void OnPartyJoinRequest(const PartyJoinRequest& partyJoinRequest) override 
        {
            Call(FN_OnPartyJoinRequest, partyJoinRequest);
        }
        void OnPartyLeader(const PartyLeader& partyLeader) override 
        {
            Call(FN_OnPartyLeader, partyLeader);
        }
        void OnPartyMatchmakerTicket(const PartyMatchmakerTicket& partyMatchmakerTicket) override 
        {
            Call(FN_OnPartyMatchmakerTicket, partyMatchmakerTicket);
        }
        void OnPartyPresence(const PartyPresenceEvent& presenceEvent) override
        {
            Call(FN_OnPartyPresence, presenceEvent);
        }
        void OnStatusPresence(const StatusPresenceEvent& presenceEvent) override
        {
            Call(FN_OnStatusPresence, presenceEvent);
        }
        void OnStreamPresence(const StreamPresenceEvent& presenceEvent) override
        {
            Call(FN_OnStreamPresence, presenceEvent);
        }
        void OnStreamData(const StreamData& data) override
        {
            Call(FN_OnStreamData, data);
        }

        void OnAuthenticateSuccess() override
        {
            Call(FN_OnAuthenticateSuccess);
        }

        void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) override
        {
            Call(FN_OnAuthenticateFailed, code, message);
        }
    };
} // namespace NakamaClient
