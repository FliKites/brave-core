/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_COMPONENTS_DECENTRALIZED_DNS_CORE_UTILS_H_
#define BRAVE_COMPONENTS_DECENTRALIZED_DNS_CORE_UTILS_H_

#include "base/strings/string_piece.h"
#include "brave/components/decentralized_dns/core/constants.h"

class GURL;
class PrefService;
class PrefRegistrySimple;

namespace decentralized_dns {

void RegisterLocalStatePrefs(PrefRegistrySimple* registry);
void MigrateObsoleteLocalStatePrefs(PrefService* local_state);

bool IsUnstoppableDomainsTLD(const base::StringPiece& host);
bool IsUnstoppableDomainsResolveMethodAsk(PrefService* local_state);
bool IsUnstoppableDomainsResolveMethodEnabled(PrefService* local_state);

bool IsENSTLD(const base::StringPiece& host);
bool IsENSResolveMethodAsk(PrefService* local_state);
bool IsENSResolveMethodEnabled(PrefService* local_state);

void SetEnsOffchainResolveMethod(PrefService* local_state,
                                 EnsOffchainResolveMethod method);
EnsOffchainResolveMethod GetEnsOffchainResolveMethod(PrefService* local_state);

bool IsSnsTLD(const base::StringPiece& host);
bool IsSnsResolveMethodAsk(PrefService* local_state);
bool IsSnsResolveMethodEnabled(PrefService* local_state);

}  // namespace decentralized_dns

#endif  // BRAVE_COMPONENTS_DECENTRALIZED_DNS_CORE_UTILS_H_
