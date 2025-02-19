/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#pragma once

#include <AzCore/Component/ComponentBus.h>
#include <AzCore/RTTI/BehaviorContext.h>
#include <AzCore/Math/Vector3.h>

namespace NakamaClientGem
{
    class NakamaClientComponentRequests : public AZ::ComponentBus
    {
    public:
        ~NakamaClientComponentRequests() override = default;

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
