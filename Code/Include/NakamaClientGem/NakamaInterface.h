
#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include "NakamaClientDataTypes.h"

namespace NakamaClientGem
{
    class NakamaRequests
        : public AZ::ComponentBus
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaRequests, "{023D49B4-E555-4D02-8AFA-A570E6856427}");

        // Put your public request methods here.
        /**
          * Authenticate a user with a device id.
          *
          * @param id A device identifier usually obtained from a platform API.
          * @param username A username used to create the user. Defaults to empty string.
          * @param create True if the user should be created when authenticated. Defaults to false.
          * @param vars Extra information that will be bundled in the session token.
          */
        virtual void AuthenticateDevice(const AZStd::string& id, const AZStd::string& username, bool create = false, const AZStringMap& vars = {}) = 0;

        // Put notification events here. Examples:
        // void RegisterEvent(AZ::EventHandler<...> notifyHandler);
        // AZ::Event<...> m_notifyEvent1;

    };

    using NakamaRequestBus = AZ::EBus<NakamaRequests>;

    class NakamaNotifications
        : public AZ::EBusTraits
    {
    public:
        AZ_RTTI(NakamaClientGem::NakamaNotifications, "{254B173E-E851-4579-856F-B325C967D107}");

        static const AZ::EBusHandlerPolicy HandlerPolicy = AZ::EBusHandlerPolicy::Multiple;

        // Listener
        virtual void OnConnect() = 0;
        virtual void OnDisconnect(const RtClientDisconnectInfo& info) = 0;
        virtual void OnError(const RtError& error) = 0;
        virtual void OnChannelMessage(const ChannelMessage& message) = 0;
        virtual void OnChannelPresence(const ChannelPresenceEvent& presenceEvent) = 0;
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
        virtual void OnStatusPresence(const StatusPresenceEvent& presenceEvent) = 0;
        virtual void OnStreamPresence(const StreamPresenceEvent& presenceEvent) = 0;
        virtual void OnStreamData(const StreamData& data) = 0;

        virtual void OnAuthenticateSuccess(const AZStd::string& username,const AZStd::string& userId) = 0;
        virtual void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) = 0;

    };

    using NakamaNotificationBus = AZ::EBus<NakamaNotifications>;

    class NakamaNotificationHandler
        : public NakamaNotificationBus::Handler
        , public AZ::BehaviorEBusHandler {
    public:
        AZ_EBUS_BEHAVIOR_BINDER(
            NakamaNotificationHandler,
            "{9B3ABC85-8E49-44C7-9BF1-D2CC119DB8BF}",
            AZ::SystemAllocator, OnConnect, OnDisconnect, OnError, OnChannelMessage, OnChannelPresence, OnMatchmakerMatched, OnMatchData, OnMatchPresence, OnNotifications, OnParty, OnPartyClosed, OnPartyData, OnPartyJoinRequest, OnPartyLeader, OnPartyMatchmakerTicket, OnPartyPresence, OnStatusPresence, OnStreamPresence, OnStreamData,
            OnAuthenticateSuccess, OnAuthenticateFailed
        );

        // ÊÂ¼þÓ³Éä
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
        void OnChannelPresence(const ChannelPresenceEvent& presenceEvent) override 
        {
            Call(FN_OnChannelPresence, presenceEvent);
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
        void OnPartyPresence(const PartyPresenceEvent& partyPresence) override 
        {
            Call(FN_OnPartyPresence, partyPresence);
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

        void OnAuthenticateSuccess(const AZStd::string& username, const AZStd::string& userId) override 
        {
            Call(FN_OnAuthenticateSuccess, username, userId);
        }
        void OnAuthenticateFailed(AZ::s8 code, const AZStd::string& message) override 
        { 
            Call(FN_OnAuthenticateFailed, code, message);
        }
    };
} // namespace NakamaClientGem
