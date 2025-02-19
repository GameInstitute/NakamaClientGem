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
            bool create = false,
            const AZStringMap& vars = {}
        ) = 0;
    };

    using NakamaClientComponentRequestBus = AZ::EBus<NakamaClientComponentRequests>;

    class NakamaClientNotifications
        : public AZ::ComponentBus
    {
    public:
        
    };

    using NakamaClientNotificationBus = AZ::EBus<NakamaClientNotifications>;

    class NakamaClientNotificationHandler
        : public NakamaClientNotificationBus::Handler
        , public AZ::BehaviorEBusHandler
    {
    public:
        //AZ_EBUS_BEHAVIOR_BINDER(NakamaClientNotificationHandler,            "{466288B5-762A-4CFA-A003-A6F0F8E6E653}");
        /*
        void OnCooldownDone() override
        {
            Call(FN_OnCooldownDone);
        }
        */
    };
} // namespace NakamaClient
