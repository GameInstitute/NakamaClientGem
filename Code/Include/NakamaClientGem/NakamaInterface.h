
#pragma once

#include <AzCore/Component/ComponentBus.h>

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

} // namespace NakamaClientGem
